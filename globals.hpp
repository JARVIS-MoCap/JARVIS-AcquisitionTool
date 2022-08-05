/*******************************************************************************
 * File:        globals.hpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef GLOBALS_H
#define GLOBALS_H

#include <QAction>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QTime>
#include <QToolButton>
#include <iostream>
#include <stdint.h>

#define NUM_CAMS 16

inline void delayl(int ms) {
    // delay function that doesn't interrupt the QEventLoop
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//----- Structs Definitions ----//
enum statusType { Connecting, Ready, Streaming, Warning, Error };
enum RecorderType { RawRecorderType, BaseRecorderType, CudaRecorderType };
enum PixelFormat {
    BayerRG8,
    BayerGB8,
    BayerGR8,
    BayerBG8,
    BGR8,
    RGB8,
    Mono8,
    YCbCr422
};
extern QMap<statusType, QIcon> statusIcons;
extern QMap<statusType, QString> statusTexts;

// Not have this live in global forever please, thank you <3!
struct GlobalSettings {
    QString recorderType = "Cuda Recorder";
    bool recordVideos = true;
    int jpegQualityFactor = 95;
    bool metadataEnabled = true;
    int streamingSubsamplingRatio = 4;
    bool streamingEnabled = true;
    int recordingSubsamplingRatio = 2;
};
extern GlobalSettings globalSettings;

typedef struct frameSize_t {
    unsigned int width;
    unsigned int height;
} frameSize_t;

typedef uint frameRate_t;

typedef struct AcquisitionSpecs {
    bool record = false;
    QDir recordingDir;
    RecorderType recorderType;
    int frameRate;
    frameSize_t frameSize;
    int streamingSamplingRatio = 2;
    PixelFormat pixelFormat;
} AcquisitionSpecs;

struct CameraSettings {
    bool loadDefaults = true;
    bool useExternalTrigger = true;
    bool exposureAuto = false;
    float exposureTime = 2.0;
    bool gainAuto = false;
    float gain = 10.0;
};

typedef struct statusLog {
    statusType type;
    QTime *time;
    QString message;
} statusLog;

void createToolBarButton(QToolButton *button, QAction *action, QIcon icon,
                         bool enabled = true, bool checkable = false,
                         QSize minSize = QSize(20, 20));


#endif
