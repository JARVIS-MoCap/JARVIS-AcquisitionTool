/*------------------------------------------------------------
 *  acquisitionmode.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <stdint.h>
#include <QCoreApplication>
#include <QTime>
#include <QToolButton>
#include <QAction>
#include <QDir>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/calib3d.hpp>

#define NUM_CAMS 12

inline void delayl(int ms) {
	//delay function that doesn't interrupt the QEventLoop
	QTime dieTime = QTime::currentTime().addMSecs(ms);
	while (QTime::currentTime() < dieTime) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//----- Structs Definitions ----//
enum statusType {Connecting, Ready, Streaming, Warning, Error};
enum RecorderType {RawRecorderType, BaseRecorderType, CudaRecorderType};
enum PixelFormat {PixelFormat_BayerRG8};
extern QMap<statusType, QIcon> statusIcons;
extern QMap<statusType, QString> statusTexts;

//Not have this live in global forever please, thank you <3!
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


typedef struct statusLog {
	statusType type;
	QTime *time;
	QString message;
} statusLog;

typedef struct CameraIntrinsics {
	cv::Mat cameraMatrix;
	cv::Mat distortionCoefficients;
} CameraIntrinsics;

void createToolBarButton(QToolButton * button, QAction* action, QIcon icon,
			bool enabled = true, bool checkable = false, QSize minSize = QSize(20,20));

#endif
