/*------------------------------------------------------------
 *  baserecorder.cpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "cudarecorder.hpp"
#include <sstream>
#include <opencv2/core.hpp>
#include <chrono>

CudaRecorder::CudaRecorder(const QString& cameraName, const AcquisitionSpecs& acquisitionSpecs)
			: RecordingInterface{cameraName, acquisitionSpecs} {
	if (acquisitionSpecs.record) {
		acquisitionSpecs.recordingDir.mkdir(cameraName);
		m_recordingDir = acquisitionSpecs.recordingDir;
		m_recordingDir.cd(cameraName);
	}
	m_cudaJPEGEncoder = new CudaJPEGEncoder(acquisitionSpecs.frameSize.width, acquisitionSpecs.frameSize.height, acquisitionSpecs.streamingSamplingRatio);
}

CudaRecorder::~CudaRecorder() {
	delete m_cudaJPEGEncoder;
}

QImage CudaRecorder::recordFrame(uchar * frame) {
	std::stringstream fileName;
	fileName << m_recordingDir.path().toStdString() << "/Frame_" << m_frameCount << ".jpg";
	std::string outName = fileName.str();
	uchar * img_data = m_cudaJPEGEncoder->encodeImage(frame, outName, m_acquisitionSpecs.record);
	QImage img = QImage(img_data, m_acquisitionSpecs.frameSize.width/m_acquisitionSpecs.streamingSamplingRatio, m_acquisitionSpecs.frameSize.height/m_acquisitionSpecs.streamingSamplingRatio, QImage::Format_RGB888);
	//QPixmap pix = QPixmap();
	//pix.convertFromImage(img);
	//std::cout << m_frameCount << std::endl;
	m_frameCount++;
	return img;
}
