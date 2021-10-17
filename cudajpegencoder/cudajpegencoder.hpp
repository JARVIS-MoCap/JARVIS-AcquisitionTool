/*------------------------------------------------------------
 *  cudajpegencoder.hpp
 *  Created: 20. November 2020
 *  Author:   Timo Hueser
 *  Email:    timo.hueser at gmail.com
 *------------------------------------------------------------*/

#ifndef NVJPEGENCODER_H
#define NVJPEGENCODER_H

#include <cuda_runtime_api.h>
#include "helper_nvJPEG.hpp"

#include <npp.h>
#include <nppi.h>

// #include <nppidei.h>
// #include <nppif.h>
// #include <nppig.h>
// #include <nppim.h>
// #include <nppist.h>
// #include <nppisu.h>
// #include <nppitc.h>
// #include <npps.h>


int nvJPEGEncode();

class CudaJPEGEncoder {
  public:
    explicit CudaJPEGEncoder(int width, int height, const std::string videoPath, int frameRate,
          bool saveRecording, int format, int streamingSamplingRatio = 1);
    ~CudaJPEGEncoder();
    unsigned char * encodeImage(unsigned char *frameData, std::string &output_filename);

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
    bool m_saveRecording;
    int m_format;
    int m_streamingSamplingRatio;

    nvjpegEncoderParams_t encode_params;
    nvjpegHandle_t nvjpeg_handle;
    nvjpegJpegState_t jpeg_state;
    nvjpegEncoderState_t encoder_state;
    nvjpegOutputFormat_t output_format = NVJPEG_OUTPUT_RGB;
    nvjpegInputFormat_t input_format = NVJPEG_INPUT_RGBI;
    unsigned char * pBuffer = NULL;
    unsigned char * pBuffer2 = NULL;
    unsigned char * pBuffer3 = NULL;
    unsigned char * data_pinned;
    unsigned char * receive_data_pinned;

    NppiSize fullSize;
    NppiRect fullRect;
    NppiSize fullSize16;
    NppiRect fullRect16;
    NppiSize streamingSize;
    NppiRect streamingRect;

    FILE *m_pipeout;

};


#endif
