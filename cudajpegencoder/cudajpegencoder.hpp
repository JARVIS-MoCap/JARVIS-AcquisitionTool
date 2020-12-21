#ifndef NVJPEGENCODER_H
#define NVJPEGENCODER_H

#include <cuda_runtime_api.h>
#include "helper_nvJPEG.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

int nvJPEGEncode();


class CudaJPEGEncoder {
  public:
    explicit CudaJPEGEncoder(int width, int height);
    ~CudaJPEGEncoder();
    uchar * encodeImage(uchar *frameData, std::string &output_filename, bool saveRecording = false);

  private:
    struct encode_params_t {
      std::string input_dir;
      std::string output_dir;
      std::string format;
      std::string subsampling;
      int quality;
      int huf;
      int dev;
    };

    int m_frameHeight;
    int m_frameWidth;

    nvjpegEncoderParams_t encode_params;
    nvjpegHandle_t nvjpeg_handle;
    nvjpegJpegState_t jpeg_state;
    nvjpegEncoderState_t encoder_state;
    nvjpegOutputFormat_t output_format = NVJPEG_OUTPUT_RGB;
    nvjpegInputFormat_t input_format = NVJPEG_INPUT_RGBI;
    unsigned char * pBuffer = NULL;
    unsigned char * pBuffer2 = NULL;
    unsigned char * data_pinned;
    unsigned char * receive_data_pinned;

};


#endif
