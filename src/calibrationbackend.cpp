/*------------------------------------------------------------
 *  calibrationbackend.cpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "calibrationbackend.hpp"

#include <chrono>


void CalibrationWorker::process() {
	if (m_pixCue->size() > 0) {
		QPixmap pix = m_pixCue->takeFirst();
		cv::Size patternsize(9,6);
		std::vector< cv::Point2f > corners;
		cv::Mat gray;
		QImage input = pix.toImage().convertToFormat(QImage::Format_RGB888);
		cv::Mat img = cv::Mat(1024, 1280, CV_8UC3, input.bits());
		cv::Mat img_small;
		cvtColor(img, gray, cv:: COLOR_BGR2GRAY);
		auto t1 = std::chrono::high_resolution_clock::now();
		bool patternfound = cv::findChessboardCornersSB(gray, patternsize, corners, cv::CALIB_CB_EXHAUSTIVE);
		cv::drawChessboardCorners(img, patternsize, cv::Mat(corners), patternfound);
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
		std::cout << duration << std::endl;
		QImage qimg = QImage(img.data,1280,1024, QImage::Format_RGB888);
		pix.convertFromImage(qimg);
		QVector<QPoint> streamCorners;
		for (const auto& pt : corners) {
			streamCorners.append(QPoint(pt.x,pt.y));
		}
		emit streamCheckerBoardImage(pix, patternfound, streamCorners);
	}
}


CalibrationBackend::CalibrationBackend(QObject *parent) {
	m_cue = new QList<QPixmap>();
	m_worker = new CalibrationWorker(m_cue);
	m_worker->moveToThread(&workerThread);
	connect(this, &CalibrationBackend::process, m_worker, &CalibrationWorker::process);
	connect(m_worker, &CalibrationWorker::streamCheckerBoardImage, this, &CalibrationBackend::streamCheckerBoardImageSlot);
	connect(&workerThread, &QThread::finished, m_worker, &CalibrationWorker::deleteLater);
	workerThread.start();

	patternsize = cv::Size(9,6);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 9; j++)
			objPattern.push_back(cv::Point3f((float)j * 25.4, (float)i * 25.4, 0));

}

void CalibrationBackend::calibrate() {
	cv::Mat stdI, stdE;
	std::vector< cv::Mat > rvecs, tvecs;
	calibrateCamera(objectPointsIntrinsics, imagePointsIntrinsics, cv::Size(1024, 1280), m_cameraIntrinsics.cameraMatrix,
				m_cameraIntrinsics.distortionCoefficients, rvecs, tvecs, stdI, stdE, reproErrorsIntrinsics);
	emit calibrationFinished();
	std::cout << m_cameraIntrinsics.cameraMatrix << std::endl;
}

void CalibrationBackend::clearDataSlot() {
	objectPointsIntrinsics.clear();
	imagePointsIntrinsics.clear();
	reproErrorsIntrinsics.clear();
}

void CalibrationBackend::imageStreamSlot(QPixmap pix) {
	m_cue->append(pix);
	emit process();

}


void CalibrationBackend::streamCheckerBoardImageSlot(QPixmap pix, bool patternfound, QVector<QPoint> corners) {
	if (patternfound) {
		std::vector<cv::Point2f> cvCorners;
		for (const auto& corner : corners) {
			cvCorners.push_back(cv::Point2f(corner.x(), corner.y()));
		}
		imagePointsIntrinsics.push_back(cvCorners);
		objectPointsIntrinsics.push_back(objPattern);
		emit counterChanged(imagePointsIntrinsics.size());
	}
	emit streamCheckerBoardImage(pix);
}
