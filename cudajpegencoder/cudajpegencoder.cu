/*------------------------------------------------------------
 *  cudajpegencoder.cu
 *  Created: 20. November 2020
 *  Author:   Timo Hueser
 *  Email:    timo.hueser at gmail.com
 *------------------------------------------------------------*/

#include "cudajpegencoder.hpp"

int dev_malloc(void **p, size_t s) { return (int)cudaMalloc(p, s); }
int dev_free(void *p) { return (int)cudaFree(p); }

CudaJPEGEncoder::CudaJPEGEncoder(int width, int height, int streamingSamplingRatio) : m_frameWidth {width}, m_frameHeight{height}, m_streamingSamplingRatio{streamingSamplingRatio} {
  encode_params_t params;
  params.dev = 0;         //Device number of GPU to be used
  params.quality = 95;    //JPEG compression quality factor
  params.format = "yuv";
  params.huf = 0;

  cudaDeviceProp props;
  checkCudaErrors(cudaGetDeviceProperties(&props, params.dev));
  printf("Using GPU %d (%s, %d SMs, %d th/SM max, CC %d.%d, ECC %s)\n",
       params.dev, props.name, props.multiProcessorCount,
       props.maxThreadsPerMultiProcessor, props.major, props.minor,
       props.ECCEnabled ? "on" : "off");

  nvjpegDevAllocator_t dev_allocator = {&dev_malloc, &dev_free};
  checkCudaErrors(nvjpegCreate(NVJPEG_BACKEND_DEFAULT, &dev_allocator, &nvjpeg_handle));
  checkCudaErrors(nvjpegJpegStateCreate(nvjpeg_handle, &jpeg_state));
  checkCudaErrors(nvjpegEncoderStateCreate(nvjpeg_handle, &encoder_state, NULL));
  checkCudaErrors(nvjpegEncoderParamsCreate(nvjpeg_handle, &encode_params, NULL));
  checkCudaErrors(nvjpegEncoderParamsSetQuality(encode_params, params.quality, NULL));
  checkCudaErrors(nvjpegEncoderParamsSetOptimizedHuffman(encode_params, params.huf, NULL));
  checkCudaErrors(nvjpegEncoderParamsSetSamplingFactors(encode_params, NVJPEG_CSS_420, NULL));

  //Allocation of memory on GPU and host
  checkCudaErrors(cudaMallocHost((void**)&data_pinned, m_frameWidth * m_frameHeight) );
  checkCudaErrors(cudaMallocHost((void**)&receive_data_pinned, m_frameWidth * m_frameHeight*3) );
  checkCudaErrors(cudaMalloc(&pBuffer, m_frameWidth * m_frameHeight));
  checkCudaErrors(cudaMalloc(&pBuffer2, m_frameWidth * m_frameHeight * 3));
  checkCudaErrors(cudaMalloc(&pBuffer3, m_frameWidth/m_streamingSamplingRatio * m_frameHeight/m_streamingSamplingRatio * 3));

  //Setup of NPP image parameters for color space conversion and subsampling
  fullSize.width = m_frameWidth;
  fullSize.height = m_frameHeight;
  fullRect.x = 0;
  fullRect.y=0;
  fullRect.width=m_frameWidth;
  fullRect.height=m_frameHeight;

  streamingSize.width = m_frameWidth/m_streamingSamplingRatio;
  streamingSize.height = m_frameHeight/m_streamingSamplingRatio;
  streamingRect.x = 0;
  streamingRect.y=0;
  streamingRect.width=m_frameWidth/m_streamingSamplingRatio;
  streamingRect.height=m_frameHeight/m_streamingSamplingRatio;

}

CudaJPEGEncoder::~CudaJPEGEncoder() {
  checkCudaErrors(cudaFree(pBuffer));
  checkCudaErrors(nvjpegEncoderParamsDestroy(encode_params));
  checkCudaErrors(nvjpegEncoderStateDestroy(encoder_state));
  checkCudaErrors(nvjpegJpegStateDestroy(jpeg_state));
  checkCudaErrors(nvjpegDestroy(nvjpeg_handle));
}


unsigned char * CudaJPEGEncoder::encodeImage(unsigned char * frameData, std::string &output_filename, bool saveRecording) {
    memcpy(data_pinned, frameData, m_frameWidth * m_frameHeight);
    cudaMemcpy(pBuffer, data_pinned, m_frameWidth * m_frameHeight, cudaMemcpyHostToDevice);

    NppStreamContext stream;
    nppGetStreamContext (&stream);

    //Conversion from BayerRG8 to RGB888
    nppiCFAToRGB_8u_C1C3R_Ctx (pBuffer, m_frameWidth, fullSize, fullRect, pBuffer2, m_frameWidth*3,
       NPPI_BAYER_RGGB, NPPI_INTER_UNDEFINED, stream);

    //Resizing of RGB image for streaming
    nppiResize_8u_C3R_Ctx(pBuffer2, m_frameWidth*3, fullSize, fullRect, pBuffer3, m_frameWidth/m_streamingSamplingRatio*3, streamingSize, streamingRect, NPPI_INTER_CUBIC, stream);


    if (saveRecording) {
      nvjpegImage_t imgdesc2 =
      {
          {
              pBuffer2,
              pBuffer2 + m_frameWidth*m_frameHeight,
              pBuffer2 + m_frameWidth*m_frameHeight*2,

          },
          {
              (unsigned int)m_frameWidth*3,
              (unsigned int)m_frameWidth,
              (unsigned int)m_frameWidth,
          }
      };

      nvjpegEncodeImage(nvjpeg_handle, encoder_state, encode_params, &imgdesc2,
              input_format, m_frameWidth, m_frameHeight, NULL);

      std::vector<unsigned char> obuffer;
      size_t length;

      //This call only retrieves the size of the compressed image
      nvjpegEncodeRetrieveBitstream(nvjpeg_handle, encoder_state, NULL,
            &length, NULL);
        obuffer.resize(length);

      //Stream compressed image in resized buffer
      nvjpegEncodeRetrieveBitstream(nvjpeg_handle, encoder_state, obuffer.data(),
              &length, NULL);

      //Write jpeg image to file
      std::ofstream outputFile(output_filename.c_str(), std::ios::out | std::ios::binary);
      outputFile.write(reinterpret_cast<const char *>(obuffer.data()), static_cast<int>(length));
  }

  cudaMemcpy(receive_data_pinned, pBuffer3, m_frameWidth/m_streamingSamplingRatio * m_frameHeight/m_streamingSamplingRatio*3, cudaMemcpyDeviceToHost);

  return receive_data_pinned;
}
