/*------------------------------------------------------------
 *  acquisitionmode.cpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "acquisitionmode.hpp"
#include "streamingwidget.hpp"

AcquisitionMode::AcquisitionMode(QMainWindow *parent) : QMainWindow(parent) {
	controlBar = new ControlBar(this);
	this->addToolBar(controlBar);

	timeStampWindow = new TimeStampWindow(parent);
	this->addDockWidget(Qt::LeftDockWidgetArea, timeStampWindow);
	timeStampWindow->hide();

	camSelector = new CamSelectorWindow(parent);
	this->addDockWidget(Qt::LeftDockWidgetArea, camSelector);
	this->resizeDocks({camSelector}, {175}, Qt::Vertical);


	camSettingsWindow = new SettingsWindow(parent, "Camera Settings", nullptr, "cameraSettings");
	this->addDockWidget(Qt::LeftDockWidgetArea, camSettingsWindow);

	triggerSettingsWindow = new SettingsWindow(parent, "Trigger Settings");
	this->addDockWidget(Qt::LeftDockWidgetArea, triggerSettingsWindow);
	this->tabifyDockWidget(camSettingsWindow, triggerSettingsWindow);
	camSettingsWindow->raise();

	streamingWidget = new StreamingWidget(this);
	this->setCentralWidget(streamingWidget);

	//--- SIGNAL-SLOT Connections ---//
	//-> Incoming Signals
	connect(camSelector, &CamSelectorWindow::cameraSelected, this, &AcquisitionMode::camSelectedSlot);
	//connect(camSettingsWindow, &SettingsWindow::loadPreset, this, &AcquisitionMode::loadCameraPresetSlot);
	connect(controlBar, &ControlBar::openTimeStampWindow, this, &AcquisitionMode::openTimeStampWindowSlot);

	//<- Outgoing Signals
	connect(this, &AcquisitionMode::camListChanged, camSelector, &CamSelectorWindow::updateListSlot);
	connect(this, &AcquisitionMode::statusUpdated, camSelector, &CamSelectorWindow::statusUpdatedSlot);
	connect(this, &AcquisitionMode::camListChanged, controlBar, &ControlBar::updateListSlot);
	connect(this, &AcquisitionMode::camAdded, controlBar, &ControlBar::camAddedSlot);
	//<-> Relayed Signals
	connect(controlBar, &ControlBar::updateStreamingPanels, streamingWidget, &StreamingWidget::updateStreamingPanelsSlot);
	connect(controlBar, &ControlBar::acquisitionStarted, streamingWidget, &StreamingWidget::acquisitionStartedSlot);
	connect(camSelector, &CamSelectorWindow::camVisibilityToggled, controlBar, &ControlBar::camVisibilityToggledSlot);
	connect(streamingWidget, &StreamingWidget::togglePanel, controlBar, &ControlBar::camVisibilityToggledSlot);
	connect(streamingWidget, &StreamingWidget::togglePanel, camSelector, &CamSelectorWindow::camVisibilityToggledSlot);
	connect(controlBar, &ControlBar::recordingInfoFileCreated, timeStampWindow, &TimeStampWindow::recordingInfoFileCreatedSlot);
	connect(controlBar, &ControlBar::stopAcquisition, timeStampWindow, &TimeStampWindow::acquisitionStoppedSlot);
}


void AcquisitionMode::camSelectedSlot(CameraInterface *cam) {
	if (cam == nullptr) camSettingsWindow->setSettingsObjectSlot(nullptr);
	else {
		camSettingsWindow->setSettingsObjectSlot(cam->cameraSettings());
	}
}

void AcquisitionMode::triggerInstanceChangedSlot() {
	if (TriggerInterface::triggerInstance == nullptr) triggerSettingsWindow->setSettingsObjectSlot(nullptr);
	else triggerSettingsWindow->setSettingsObjectSlot(TriggerInterface::triggerInstance->triggerSettings());
}

void AcquisitionMode::loadCameraPresetSlot(settingsObject* activeSettings) {
	CameraInterface *cam = static_cast<CameraInterface*>(activeSettings->parent());
	//cam->loadPreset();
}

void AcquisitionMode::openTimeStampWindowSlot() {
	if (!timeStampWindow->isVisible()) {
		timeStampWindow->show();
		timeStampWindow->setFloating(true);
		timeStampWindow->resize(800,600);
	}
}
