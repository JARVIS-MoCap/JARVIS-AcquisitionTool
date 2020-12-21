/*------------------------------------------------------------
 *  recordinginterface.hpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef RECORDINGINTERFACE_H
#define RECORDINGINTERFACE_H

#include "globals.hpp"


class RecordingInterface : public QObject {
	Q_OBJECT
	public:
		explicit RecordingInterface(const QString& cameraName, const AcquisitionSpecs& acquisitionSpecs)
					: m_cameraName{cameraName}, m_acquisitionSpecs{acquisitionSpecs} { }

		virtual QPixmap recordFrame(uchar* frame) = 0;

	protected:
		const QString m_cameraName;
		const AcquisitionSpecs m_acquisitionSpecs;
		int m_frameCount = 0;
		QDir m_recordingDir;
};

#endif
