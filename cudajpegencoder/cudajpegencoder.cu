#include "cudajpegencoder.hpp"
#include <opencv2/core.hpp>
#include <npp.h>
#include <nppi.h>
#include <nppcore.h>


int dev_malloc(void **p, size_t s) { return (int)cudaMalloc(p, s); }
int dev_free(void *p) { return (int)cudaFree(p); }

CudaJPEGEncoder::CudaJPEGEncoder(int width, int height) : m_frameWidth {width}, m_frameHeight{height} {
  int pidx;
  encode_params_t params;
  params.output_dir = "encode_output";
  params.dev = 0;
  params.quality = 95;
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
  // sample input parameters
  checkCudaErrors(nvjpegEncoderParamsSetQuality(encode_params, params.quality, NULL));
  checkCudaErrors(nvjpegEncoderParamsSetOptimizedHuffman(encode_params, params.huf, NULL));
  //oformat = NVJPEG_OUTPUT_YUV;
  int error_code = 1;
  checkCudaErrors(nvjpegEncoderParamsSetSamplingFactors(encode_params, NVJPEG_CSS_420, NULL));

  checkCudaErrors(cudaMallocHost((void**)&data_pinned, m_frameWidth * m_frameHeight) ); // host pinned
  checkCudaErrors(cudaMallocHost((void**)&receive_data_pinned, m_frameWidth * m_frameHeight*3) ); // host pinned
  cudaError_t eCopy = cudaMalloc(&pBuffer, m_frameWidth * m_frameHeight);
  eCopy = cudaMalloc(&pBuffer2, m_frameWidth * m_frameHeight * 3);
}

CudaJPEGEncoder::~CudaJPEGEncoder() {
  std::cout << "Destroying CudaJPEGEncoder!" << std::endl;
  checkCudaErrors(cudaFree(pBuffer));
  checkCudaErrors(nvjpegEncoderParamsDestroy(encode_params));
  checkCudaErrors(nvjpegEncoderStateDestroy(encoder_state));
  checkCudaErrors(nvjpegJpegStateDestroy(jpeg_state));
  checkCudaErrors(nvjpegDestroy(nvjpeg_handle));
}


uchar * CudaJPEGEncoder::encodeImage(uchar * frameData, std::string &output_filename, bool saveRecording) {
    memcpy(data_pinned, frameData, m_frameWidth * m_frameHeight);
    cudaMemcpy(pBuffer, data_pinned, m_frameWidth * m_frameHeight, cudaMemcpyHostToDevice);

    NppiSize size;
    size.width = m_frameWidth;
    size.height = m_frameHeight;
    NppiRect rect;
    rect.x = 0;
    rect.y=0;
    rect.width=m_frameWidth;
    rect.height=m_frameHeight;
    NppStreamContext stream;
    nppGetStreamContext (&stream);

    NppStatus error  =  nppiCFAToRGB_8u_C1C3R_Ctx (pBuffer, m_frameWidth, size, rect, pBuffer2, m_frameWidth*3,
       NPPI_BAYER_RGGB, NPPI_INTER_UNDEFINED, stream);
    cudaMemcpy(receive_data_pinned, pBuffer2, m_frameWidth * m_frameHeight*3, cudaMemcpyDeviceToHost);

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

nvjpegEncodeImage(nvjpeg_handle,
          encoder_state,
          encode_params,
          &imgdesc2,
          input_format,
          m_frameWidth,
          m_frameHeight,
          NULL);
    std::vector<unsigned char> obuffer;
    size_t length;

  nvjpegEncodeRetrieveBitstream(
        nvjpeg_handle,
        encoder_state,
        NULL,
        &length,
        NULL);
    obuffer.resize(length);


nvjpegEncodeRetrieveBitstream(
        nvjpeg_handle,
        encoder_state,
        obuffer.data(),
        &length,
        NULL);

      std::ofstream outputFile(output_filename.c_str(), std::ios::out | std::ios::binary);
      outputFile.write(reinterpret_cast<const char *>(obuffer.data()), static_cast<int>(length));
    }

    return receive_data_pinned;
}
