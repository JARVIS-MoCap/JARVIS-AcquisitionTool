/*******************************************************************************
 * File:			  acquisitionmode.hpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "acquisitionmode.hpp"
#include "streamingwidget.hpp"


AcquisitionMode::AcquisitionMode(QMainWindow *parent) : QMainWindow(parent) {
	controlBar = new ControlBar(this);
	this->addToolBar(controlBar);

	camSelector = new CamSelectorWindow(parent);
	this->addDockWidget(Qt::LeftDockWidgetArea, camSelector);
	this->resizeDocks({camSelector}, {175}, Qt::Vertical);


	camSettingsWindow = new CameraSettingsWindow(parent, nullptr);
	this->addDockWidget(Qt::LeftDockWidgetArea, camSettingsWindow);

	triggerSettingsWindow = new TriggerSettingsWindow(parent);
	this->addDockWidget(Qt::LeftDockWidgetArea, triggerSettingsWindow);
	this->tabifyDockWidget(camSettingsWindow, triggerSettingsWindow);

	monitoringWindow = new MonitoringWindow(parent);
	this->addDockWidget(Qt::LeftDockWidgetArea, monitoringWindow);
	this->tabifyDockWidget(camSettingsWindow, monitoringWindow);

	camSettingsWindow->raise();

	streamingWidget = new StreamingWidget(this);
	this->setCentralWidget(streamingWidget);

	//--- SIGNAL-SLOT Connections ---//
	//-> Incoming Signals
	connect(camSelector, &CamSelectorWindow::cameraSelected,
					this, &AcquisitionMode::camSelectedSlot);
	connect(camSettingsWindow, &CameraSettingsWindow::setupAllCamerasButtonClicked,
					this, &AcquisitionMode::setupAllCamerasClickedSlot);

	//<- Outgoing Signals
	connect(this, &AcquisitionMode::camListChanged,
					camSelector, &CamSelectorWindow::updateListSlot);
	connect(this, &AcquisitionMode::camListChanged,
					monitoringWindow, &MonitoringWindow::updateListSlot);
	connect(this, &AcquisitionMode::statusUpdated,
					camSelector, &CamSelectorWindow::statusUpdatedSlot);
	connect(this, &AcquisitionMode::camListChanged,
					controlBar, &ControlBar::updateListSlot);
	connect(this, &AcquisitionMode::camAdded,
					controlBar, &ControlBar::camAddedSlot);
	//<-> Relayed Signals
	connect(controlBar, &ControlBar::updateStreamingPanels,
					streamingWidget, &StreamingWidget::updateStreamingPanelsSlot);
	connect(controlBar, &ControlBar::acquisitionStarted,
					streamingWidget, &StreamingWidget::acquisitionStartedSlot);
	connect(camSelector, &CamSelectorWindow::camVisibilityToggled,
					controlBar, &ControlBar::camVisibilityToggledSlot);
	connect(streamingWidget, &StreamingWidget::togglePanel,
					controlBar, &ControlBar::camVisibilityToggledSlot);
	connect(streamingWidget, &StreamingWidget::togglePanel,
					camSelector, &CamSelectorWindow::camVisibilityToggledSlot);
}


void AcquisitionMode::camSelectedSlot(CameraInterface *cam) {
	if (cam == nullptr) {
		camSettingsWindow->setSettingsObjectSlot(nullptr);
	}
	else {
		camSettingsWindow->setSettingsObjectSlot(cam->cameraSettings());
	}
}


void AcquisitionMode::triggerInstanceChangedSlot() {
	if (TriggerInterface::triggerInstance == nullptr)
				triggerSettingsWindow->setSettingsObjectSlot(nullptr);
	else triggerSettingsWindow->setSettingsObjectSlot(
				TriggerInterface::triggerInstance->triggerSettings());
}


void AcquisitionMode::loadCameraPresetSlot(SettingsObject* activeSettings) {
	CameraInterface *cam = static_cast<CameraInterface*>(
				activeSettings->parent());
}

void AcquisitionMode::setupAllCamerasClickedSlot(const CameraSettings &cameraSettings) {
	for(const auto &cam : CameraInterface::cameraList) {
		if (cam->isStreaming()) {
			return;
		}
	}
	for(const auto &cam : CameraInterface::cameraList) {
		cam->setupCamera(cameraSettings);
	}
}
