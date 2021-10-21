/*------------------------------------------------------------
 *  baserecorder.cpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "baserecorder.hpp"

BaseRecoder::BaseRecoder(const QString& cameraName, const AcquisitionSpecs& acquisitionSpecs)
			: RecordingInterface{cameraName, acquisitionSpecs} {
	std::cout << "Creating Baserecoder" << std::endl;
	std::string outvideoName_str;
	if (m_acquisitionSpecs.record) {
		m_recordingDir = acquisitionSpecs.recordingDir;
		if (true) {
			std::stringstream videoName;
			videoName << m_recordingDir.path().toStdString() << "/" << cameraName.toStdString() << ".avi";
			outvideoName_str = videoName.str();
			m_videoWriter = new cv::VideoWriter(outvideoName_str,cv::VideoWriter::fourcc('M','J','P','G'),m_acquisitionSpecs.frameRate, cv::Size(m_acquisitionSpecs.frameSize.width,m_acquisitionSpecs.frameSize.height));
		}
		else {
			acquisitionSpecs.recordingDir.mkdir(cameraName);
			m_recordingDir.cd(cameraName);
		}
	}
}

BaseRecoder::~BaseRecoder() {
	if (m_acquisitionSpecs.record) {
		m_videoWriter->release();
	}
}


QImage BaseRecoder::recordFrame(uchar * frame) {
  cv::Mat img_bayer(m_acquisitionSpecs.frameSize.height,m_acquisitionSpecs.frameSize.width,CV_8UC1,frame,cv::Mat::AUTO_STEP);
	cv::Mat img_cv, img_stream;
	cv::cvtColor(img_bayer, img_cv, cv::COLOR_BayerBG2BGR);
	cv::resize(img_cv, img_stream, cv::Size(m_acquisitionSpecs.frameSize.width/m_acquisitionSpecs.streamingSamplingRatio, m_acquisitionSpecs.frameSize.height/m_acquisitionSpecs.streamingSamplingRatio), cv::INTER_LINEAR);
	cv::cvtColor(img_stream, img_stream, cv::COLOR_BGR2RGB);
	QImage img = QImage(img_stream.data,m_acquisitionSpecs.frameSize.width/m_acquisitionSpecs.streamingSamplingRatio,m_acquisitionSpecs.frameSize.height/m_acquisitionSpecs.streamingSamplingRatio, QImage::Format_RGB888);
	//QPixmap pix;
	//pix.convertFromImage(img);
	if (m_acquisitionSpecs.record) {
		m_videoWriter->write(img_cv);
		//img.save(m_recordingDir.path() + "/Frame_" + QString::number(m_frameCount) + ".jpg", "JPG", 95);
	}
	m_frameCount++;
	return img;
}
