/*------------------------------------------------------------
 *  calibrationtool.cpp
 *  Created:  11. November 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "calibrationtool.hpp"

#include <QLabel>
#include <QToolBar>

CalibrationStreamingWidget::CalibrationStreamingWidget(QWidget *parent) : QWidget(parent) {
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout = new QGridLayout(this);
	layout->setMargin(0);
	layout->setSpacing(8);
	streamingPanel = new StreamingPanel(nullptr, this);
	layout->addWidget(streamingPanel,0,0, Qt::AlignCenter);
}

void CalibrationStreamingWidget::resizeStreamingPanel() {
	int maxHeight = this->size().height();
	int maxWidth = this->size().width();
	int toolBarHeight = 25;
	float aspectRatio = 1280.0/1024.0;
	int width,height;
	if ((maxHeight-toolBarHeight)*aspectRatio > maxWidth) {
		width = maxWidth;
		height = width/aspectRatio+toolBarHeight;
	}
	else {
		height = maxHeight;
		width =	(height-toolBarHeight)*aspectRatio;
	}
	streamingPanel->setMaximumSize(width, height);
	streamingPanel->setSize(width,height);
	streamingPanel->imgViewer->setSize(width,height-toolBarHeight);
	streamingPanel->imgViewer->setMaximumSize(width, height-toolBarHeight);
	streamingPanel->imgViewer->setMinimumSize(width, height-toolBarHeight);
	streamingPanel->imgViewer->fitToScreen(1280);
	streamingPanel->imgViewer->setMinimumSize(200,0);
}



//---- Calibration Tool ----//
CalibrationTool::CalibrationTool(QWidget *parent) : QMainWindow(parent) {
	settings = new QSettings();
	calibrationStreamingWidget = new CalibrationStreamingWidget();
	this->setCentralWidget(calibrationStreamingWidget);

	calibrationBackend = new CalibrationBackend();

	calibrationControlBar = new CalibrationControlBar();
	this->addToolBar(calibrationControlBar);
	calibrationSettingsWindow  = new CalibrationSettingsWindow();
	this->addDockWidget(Qt::BottomDockWidgetArea, calibrationSettingsWindow);

	coverageMapWindow  = new CoverageMapWindow();
	this->addDockWidget(Qt::BottomDockWidgetArea, coverageMapWindow);

	calibrationStatisticsWindow  = new CalibrationStatisticsWindow();
	this->addDockWidget(Qt::BottomDockWidgetArea, calibrationStatisticsWindow);
	this->resizeDocks({calibrationStatisticsWindow}, {300}, Qt::Horizontal);

	connect(calibrationControlBar, &CalibrationControlBar::stopAcquisition, this, &CalibrationTool::stopAcquisitionSlot);
	connect(calibrationControlBar, &CalibrationControlBar::calibrateClicked, this, &CalibrationTool::calibrateClickedSlot);
	connect(calibrationControlBar, &CalibrationControlBar::resetClicked, calibrationBackend, &CalibrationBackend::clearDataSlot);
	connect(calibrationControlBar, &CalibrationControlBar::resetClicked, calibrationStatisticsWindow, &CalibrationStatisticsWindow::clearDataSlot);
	connect(calibrationStatisticsWindow, &CalibrationStatisticsWindow::counterChanged, calibrationControlBar, &CalibrationControlBar::counterChangedSlot);
	connect(calibrationBackend, &CalibrationBackend::counterChanged, calibrationControlBar, &CalibrationControlBar::counterChangedSlot);
	connect(calibrationBackend, &CalibrationBackend::calibrationFinished, this, &CalibrationTool::calibrationFinishedSlot);
	connect(calibrationBackend, &CalibrationBackend::calibrationFinished, calibrationControlBar, &CalibrationControlBar::calibrationFinishedSlot);
	connect(this, &CalibrationTool::activateCalibrateButton, calibrationControlBar, &CalibrationControlBar::activateCalibrateButton);
}

void CalibrationTool::cameraSelectedSlot(CameraInterface *camera) {
	std::cout << camera->cameraName().toStdString() << std::endl;
	calibrationStreamingWidget->streamingPanel->setCamera(camera);
	disconnect(calibrationBackend, &CalibrationBackend::streamCheckerBoardImage, calibrationStreamingWidget->streamingPanel->imgViewer, &ImageViewer::setPixmap);

	if (m_camera != nullptr) {
		disconnect(m_camera, &CameraInterface::streamImage, calibrationBackend, &CalibrationBackend::imageStreamSlot);
		disconnect(calibrationControlBar, &CalibrationControlBar::startAcquisition, m_camera, &CameraInterface::startAcquisitionSlot);
		disconnect(calibrationControlBar, &CalibrationControlBar::stopAcquisition, m_camera, &CameraInterface::stopAcquisitionSlot);
	}
	m_camera = camera;
	connect(calibrationControlBar, &CalibrationControlBar::startAcquisition, m_camera, &CameraInterface::startAcquisitionSlot);
	connect(calibrationControlBar, &CalibrationControlBar::stopAcquisition, m_camera, &CameraInterface::stopAcquisitionSlot);
	connect(m_camera, &CameraInterface::streamImage, calibrationBackend, &CalibrationBackend::imageStreamSlot);
	connect(calibrationBackend, &CalibrationBackend::streamCheckerBoardImage, calibrationStreamingWidget->streamingPanel->imgViewer, &ImageViewer::setPixmap);
}

void CalibrationTool::stopAcquisitionSlot() {
	if (calibrationBackend->numberIntrinsics() != 0) {
		std::cout << "stopping" << std::endl;
		emit activateCalibrateButton();
	}
}

void CalibrationTool::calibrateClickedSlot() {
	std::cout << "Calibrate Clicked!" << std::endl;
	calibrationBackend->calibrate();
}

void CalibrationTool::calibrationFinishedSlot() {
	calibrationStatisticsWindow->setData(&calibrationBackend->reproErrorsIntrinsics,
					&calibrationBackend->objectPointsIntrinsics, &calibrationBackend->imagePointsIntrinsics);
}
