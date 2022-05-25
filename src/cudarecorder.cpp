/*******************************************************************************
 * File:        cudarecorder.cpp
 * Created:     05. June 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "cudarecorder.hpp"
#include <chrono>
#include <opencv2/core.hpp>
#include <sstream>

CudaRecorder::CudaRecorder(const QString &cameraName,
                           const AcquisitionSpecs &acquisitionSpecs)
    : RecordingInterface{cameraName, acquisitionSpecs} {
    std::string outvideoName_str;
    if (acquisitionSpecs.record) {
        m_recordingDir = acquisitionSpecs.recordingDir;
        if (true) {
            std::stringstream videoName;
            videoName << m_recordingDir.path().toStdString() << "/"
                      << cameraName.toStdString() << ".avi";
            outvideoName_str = videoName.str();
        } else {
            acquisitionSpecs.recordingDir.mkdir(cameraName);
            m_recordingDir.cd(cameraName);
        }
    }
    CudaJPEGEncoder::CudaJPEGEncoderConfig encoderConfig;
    encoderConfig.width = m_acquisitionSpecs.frameSize.width;
    encoderConfig.height = m_acquisitionSpecs.frameSize.height;
    encoderConfig.frameRate = m_acquisitionSpecs.frameRate;
    encoderConfig.pixelFormat = m_acquisitionSpecs.pixelFormat;
    encoderConfig.saveRecording = m_acquisitionSpecs.record;
    encoderConfig.videoPath = outvideoName_str;
    encoderConfig.streamingEnabled =
        !m_acquisitionSpecs.record || globalSettings.streamingEnabled;
    encoderConfig.streamingSamplingRatio =
        m_acquisitionSpecs.streamingSamplingRatio;
    encoderConfig.jpegQualityFactor = globalSettings.jpegQualityFactor;

    m_cudaJPEGEncoder = new CudaJPEGEncoder(encoderConfig);
}

CudaRecorder::~CudaRecorder() { delete m_cudaJPEGEncoder; }

QImage CudaRecorder::recordFrame(uchar *frame) {
    // std::stringstream fileName;
    // fileName << m_recordingDir.path().toStdString()
    //<< "/Frame_" << m_frameCount << ".jpg";
    // std::string outName = fileName.str();
    uchar *img_data = m_cudaJPEGEncoder->encodeImage(frame);
    QImage img = QImage(img_data,
                        m_acquisitionSpecs.frameSize.width /
                            m_acquisitionSpecs.streamingSamplingRatio,
                        m_acquisitionSpecs.frameSize.height /
                            m_acquisitionSpecs.streamingSamplingRatio,
                        QImage::Format_RGB888);
    m_frameCount++;
    return img;
}
