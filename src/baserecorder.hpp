/*------------------------------------------------------------
 *  basedrecorder.hpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef BASERECORDER_H
#define BASERECORDER_H

#include "globals.hpp"
#include "recordinginterface.hpp"


class BaseRecoder : public RecordingInterface {
	Q_OBJECT
	public:
		explicit BaseRecoder(const QString& cameraName, const AcquisitionSpecs& acquisitionSpecs);
		QPixmap recordFrame(uchar* frame);
};

#endif
