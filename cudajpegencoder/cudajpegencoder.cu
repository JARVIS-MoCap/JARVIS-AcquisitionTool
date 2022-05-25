/*******************************************************************************
 * File:          cudajpegencoder.cpp
 * Created:       20. November 2020
 * Author:        Timo Hueser
 * Contact:       timo.hueser@gmail.com
 * Copyright:     2021 Timo Hueser
 * License:       LGPL v3.0
 ******************************************************************************/

#include "cudajpegencoder.hpp"

int dev_malloc(void **p, size_t s) { return (int)cudaMalloc(p, s); }
int dev_free(void *p) { return (int)cudaFree(p); }


CudaJPEGEncoder::CudaJPEGEncoder(CudaJPEGEncoderConfig encoderConfig) :
      m_encoderConfig(encoderConfig) {
  encode_params_t params;
  params.dev = 0;         //Device number of GPU to be used
  params.quality = m_encoderConfig.jpegQualityFactor;
  params.format = "yuv";
  params.huf = 0;

  cudaDeviceProp props;
  checkCudaErrors(cudaGetDeviceProperties(&props, params.dev));
  printf("Using GPU %d (%s, %d SMs, %d th/SM max, CC %d.%d, ECC %s)\n",
       params.dev, props.name, props.multiProcessorCount,
       props.maxThreadsPerMultiProcessor, props.major, props.minor,
       props.ECCEnabled ? "on" : "off");

  nvjpegDevAllocator_t dev_allocator = {&dev_malloc, &dev_free};

  checkCudaErrors(nvjpegCreate(NVJPEG_BACKEND_DEFAULT, &dev_allocator,
        &nvjpeg_handle));
  checkCudaErrors(nvjpegJpegStateCreate(nvjpeg_handle,
        &jpeg_state));
  checkCudaErrors(nvjpegEncoderStateCreate(nvjpeg_handle, &encoder_state,
        NULL));
  checkCudaErrors(nvjpegEncoderParamsCreate(nvjpeg_handle, &encode_params,
        NULL));
  checkCudaErrors(nvjpegEncoderParamsSetQuality(encode_params, params.quality,
        NULL));
  checkCudaErrors(nvjpegEncoderParamsSetOptimizedHuffman(encode_params,
        params.huf, NULL));
  checkCudaErrors(nvjpegEncoderParamsSetSamplingFactors(encode_params,
        NVJPEG_CSS_420, NULL));

  //Allocation of memory on GPU and host
  if (m_encoderConfig.pixelFormat == BayerRG8 ||
      m_encoderConfig.pixelFormat == BayerGB8 ||
      m_encoderConfig.pixelFormat == BayerGR8 ||
      m_encoderConfig.pixelFormat == BayerBG8 ||
      m_encoderConfig.pixelFormat == Mono8) {
    checkCudaErrors(cudaMallocHost((void**)&data_pinned,
          m_encoderConfig.width * m_encoderConfig.height) );
    checkCudaErrors(cudaMalloc(&pBuffer,
          m_encoderConfig.width * m_encoderConfig.height));
  }

  else if (m_encoderConfig.pixelFormat == BGR8 || m_encoderConfig.pixelFormat == RGB8){
    checkCudaErrors(cudaMallocHost((void**)&data_pinned,
          m_encoderConfig.width * m_encoderConfig.height * 3));
    checkCudaErrors(cudaMalloc(&pBuffer,
          m_encoderConfig.width * m_encoderConfig.height * 3));
  }

  else if (m_encoderConfig.pixelFormat == YCbCr422) {
    checkCudaErrors(cudaMallocHost((void**)&data_pinned,
          m_encoderConfig.width * m_encoderConfig.height * 2) );
    checkCudaErrors(cudaMalloc(&pBuffer,
          m_encoderConfig.width * m_encoderConfig.height * 2));
  }

  checkCudaErrors(cudaMallocHost((void**)&receive_data_pinned,
        m_encoderConfig.width * m_encoderConfig.height * 3) );
  checkCudaErrors(cudaMalloc(&pBuffer2,
        m_encoderConfig.width * m_encoderConfig.height * 3));
  checkCudaErrors(cudaMalloc(&pBuffer3,
        m_encoderConfig.width/m_encoderConfig.streamingSamplingRatio *
        m_encoderConfig.height/m_encoderConfig.streamingSamplingRatio * 3));

  //Setup of NPP image parameters for color space conversion and subsampling
  fullSize.width = m_encoderConfig.width;
  fullSize.height = m_encoderConfig.height;
  fullRect.x = 0;
  fullRect.y= 0;
  fullRect.width = m_encoderConfig.width;
  fullRect.height = m_encoderConfig.height;

  streamingSize.width = m_encoderConfig.width /
                        m_encoderConfig.streamingSamplingRatio;
  streamingSize.height = m_encoderConfig.height /
                         m_encoderConfig.streamingSamplingRatio;
  streamingRect.x = 0;
  streamingRect.y = 0;
  streamingRect.width = m_encoderConfig.width /
                        m_encoderConfig.streamingSamplingRatio;
  streamingRect.height = m_encoderConfig.height /
                         m_encoderConfig.streamingSamplingRatio;

  if (m_encoderConfig.saveRecording) {
    std::string FFMPEGCommandString =
          "ffmpeg -hide_banner -loglevel error -y -f image2pipe -r " +
          std::to_string(m_encoderConfig.frameRate) +
          " -i pipe: -codec copy " + m_encoderConfig.videoPath;
    char* FFMPEGCommand = const_cast<char*>(FFMPEGCommandString.c_str());
    m_pipeout = popen(FFMPEGCommand, "w");
  }
}

CudaJPEGEncoder::~CudaJPEGEncoder() {
  checkCudaErrors(cudaFree(pBuffer));
  checkCudaErrors(nvjpegEncoderParamsDestroy(encode_params));
  checkCudaErrors(nvjpegEncoderStateDestroy(encoder_state));
  checkCudaErrors(nvjpegJpegStateDestroy(jpeg_state));
  checkCudaErrors(nvjpegDestroy(nvjpeg_handle));

  if (m_encoderConfig.saveRecording) {
    fflush(m_pipeout);
    pclose(m_pipeout);
  }
}


unsigned char * CudaJPEGEncoder::encodeImage(unsigned char * frameData) {
  if (m_encoderConfig.pixelFormat == BayerRG8 ||
      m_encoderConfig.pixelFormat == BayerGB8 ||
      m_encoderConfig.pixelFormat == BayerGR8 ||
      m_encoderConfig.pixelFormat == BayerBG8 ||
      m_encoderConfig.pixelFormat == Mono8) {
    memcpy(data_pinned, frameData,
          m_encoderConfig.width * m_encoderConfig.height);
    cudaMemcpy(pBuffer, data_pinned,
          m_encoderConfig.width * m_encoderConfig.height,
          cudaMemcpyHostToDevice);
  }

  else if (m_encoderConfig.pixelFormat == BGR8 || m_encoderConfig.pixelFormat == RGB8) {
    memcpy(data_pinned, frameData,
          m_encoderConfig.width * m_encoderConfig.height * 3);
    cudaMemcpy(pBuffer, data_pinned,
          m_encoderConfig.width * m_encoderConfig.height * 3,
          cudaMemcpyHostToDevice);
  }

  else if (m_encoderConfig.pixelFormat == YCbCr422) {
    memcpy(data_pinned, frameData,
          m_encoderConfig.width * m_encoderConfig.height * 2);
    cudaMemcpy(pBuffer, data_pinned,
          m_encoderConfig.width * m_encoderConfig.height * 2,
          cudaMemcpyHostToDevice);
  }

    NppStreamContext stream;
    nppGetStreamContext (&stream);

    //Conversion from BayerRG8 to RGB888
    if(m_encoderConfig.pixelFormat == BayerRG8 ||
      m_encoderConfig.pixelFormat == Mono8) {
      nppiCFAToRGB_8u_C1C3R_Ctx (pBuffer, m_encoderConfig.width,
            fullSize, fullRect, pBuffer2, m_encoderConfig.width*3,
            NPPI_BAYER_RGGB, NPPI_INTER_UNDEFINED, stream);
    }

    else if(m_encoderConfig.pixelFormat == BayerGB8) {
      nppiCFAToRGB_8u_C1C3R_Ctx (pBuffer, m_encoderConfig.width,
            fullSize, fullRect, pBuffer2, m_encoderConfig.width*3,
            NPPI_BAYER_GBRG, NPPI_INTER_UNDEFINED, stream);
    }

    else if(m_encoderConfig.pixelFormat == BayerGR8) {
      nppiCFAToRGB_8u_C1C3R_Ctx (pBuffer, m_encoderConfig.width, fullSize,
            fullRect, pBuffer2, m_encoderConfig.width*3,
            NPPI_BAYER_GRBG, NPPI_INTER_UNDEFINED, stream);
    }

    else if(m_encoderConfig.pixelFormat == BayerBG8) {
      nppiCFAToRGB_8u_C1C3R_Ctx (pBuffer, m_encoderConfig.width,
            fullSize, fullRect, pBuffer2, m_encoderConfig.width*3,
            NPPI_BAYER_BGGR, NPPI_INTER_UNDEFINED, stream);
    }

    else if (m_encoderConfig.pixelFormat == BGR8) {
      Npp32f aTwist[3][4] = {{0,0,1,0},{0,1,0,0},{1,0,0,0}};
      nppiColorTwist32f_8u_C3R_Ctx(pBuffer, m_encoderConfig.width*3,
            pBuffer2, m_encoderConfig.width*3, fullSize, aTwist, stream);
    }
    else if (m_encoderConfig.pixelFormat == RGB8) {
      Npp32f aTwist[3][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0}};
      nppiColorTwist32f_8u_C3R_Ctx(pBuffer, m_encoderConfig.width*3,
            pBuffer2, m_encoderConfig.width*3, fullSize, aTwist, stream);
    }

    else if (m_encoderConfig.pixelFormat == YCbCr422) {
      nppiYUV422ToRGB_8u_C2C3R_Ctx(pBuffer, m_encoderConfig.width*2,
            pBuffer2, m_encoderConfig.width*3, fullSize, stream);
    }

    if (m_encoderConfig.streamingEnabled) {
      //Resizing of RGB image for streaming
      nppiResize_8u_C3R_Ctx(pBuffer2, m_encoderConfig.width*3, fullSize,
            fullRect, pBuffer3,
            m_encoderConfig.width / m_encoderConfig.streamingSamplingRatio*3,
            streamingSize, streamingRect, NPPI_INTER_CUBIC, stream);
    }

    if (m_encoderConfig.saveRecording) {
      nvjpegImage_t imgdesc2 =
      {
          {
              pBuffer2,
              pBuffer2 + m_encoderConfig.width*m_encoderConfig.height,
              pBuffer2 + m_encoderConfig.width*m_encoderConfig.height*2,
          },
          {
              (unsigned int)m_encoderConfig.width*3,
              (unsigned int)m_encoderConfig.width,
              (unsigned int)m_encoderConfig.width,
          }
      };

      nvjpegEncodeImage(nvjpeg_handle, encoder_state, encode_params, &imgdesc2,
              input_format, m_encoderConfig.width, m_encoderConfig.height,
              NULL);

      std::vector<unsigned char> obuffer;
      size_t length;

      //This call only retrieves the size of the compressed image
      nvjpegEncodeRetrieveBitstream(nvjpeg_handle, encoder_state, NULL,
            &length, NULL);
        obuffer.resize(length);

      //Stream compressed image in resized buffer
      nvjpegEncodeRetrieveBitstream(nvjpeg_handle, encoder_state,
            obuffer.data(), &length, NULL);

      //Write jpeg image to file
      //std::ofstream outputFile(output_filename.c_str(),
      //      std::ios::out | std::ios::binary);
      //outputFile.write(reinterpret_cast<const char *>(obuffer.data()),
      //      static_cast<int>(length));
      fwrite(reinterpret_cast<const char *>(obuffer.data()), 1 ,
            static_cast<int>(length), m_pipeout);
  }

  if (m_encoderConfig.streamingEnabled) {
    cudaMemcpy(receive_data_pinned, pBuffer3,
          m_encoderConfig.width / m_encoderConfig.streamingSamplingRatio *
          m_encoderConfig.height/m_encoderConfig.streamingSamplingRatio*3,
          cudaMemcpyDeviceToHost);
  }

  return receive_data_pinned;
}
