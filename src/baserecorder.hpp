/*******************************************************************************
 * File:			  basedrecorder.hpp
 * Created: 	  05. June 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/


#ifndef BASERECORDER_H
#define BASERECORDER_H

#include "globals.hpp"
#include "recordinginterface.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>


class BaseRecoder : public RecordingInterface {
	Q_OBJECT

	public:
		explicit BaseRecoder(const QString& cameraName,
					const AcquisitionSpecs& acquisitionSpecs);
		~BaseRecoder();
		QImage recordFrame(uchar* frame);

	private:
			cv::VideoWriter *m_videoWriter;
};

#endif
