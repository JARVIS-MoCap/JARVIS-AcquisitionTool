/*------------------------------------------------------------
 *  baserecorder.cpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "baserecorder.hpp"

BaseRecoder::BaseRecoder(const QString& cameraName, const AcquisitionSpecs& acquisitionSpecs)
			: RecordingInterface{cameraName, acquisitionSpecs} {
	std::cout << "Creating Baserecoder" << std::endl;
	if (m_acquisitionSpecs.record) {
		acquisitionSpecs.recordingDir.mkdir(cameraName);
		m_recordingDir = acquisitionSpecs.recordingDir;
		m_recordingDir.cd(cameraName);
	}
}

QImage BaseRecoder::recordFrame(uchar * frame) {
	QImage img = QImage(frame,m_acquisitionSpecs.frameSize.width,m_acquisitionSpecs.frameSize.height, QImage::Format_RGB888);
	//QPixmap pix;
	//pix.convertFromImage(img);
	if (m_acquisitionSpecs.record) {
		std::cout << (m_recordingDir.path() + "/Frame_" + QString::number(m_frameCount) + ".jpg").toStdString() << std::endl;
		img.save(m_recordingDir.path() + "/Frame_" + QString::number(m_frameCount) + ".jpg", "JPG", 95);
	}
	m_frameCount++;
	return img;
}
