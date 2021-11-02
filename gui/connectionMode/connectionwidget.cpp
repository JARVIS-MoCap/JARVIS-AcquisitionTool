/*******************************************************************************
 * File:			  connectinwidget.cpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "connectionwidget.hpp"
#include "camerainterface.hpp"
#include "testcamera.hpp"
#include "flirchameleon.hpp"
#include "triggerinterface.hpp"
#include "testtrigger.hpp"
#include "flirconfigbackend.hpp"
#include "flirchameleonconfig.hpp"

#include <QMessageBox>


ConnectionWidget::ConnectionWidget(QWidget *parent) :
			QWidget(parent, Qt::Window) {
	settings = new QSettings();
	this->setFocusPolicy(Qt::StrongFocus);
	camLoadPresetsWindow = new PresetsWindow(&camPresets, "load",
				"connectionMode/camPresets");
	camSavePresetsWindow = new PresetsWindow(&camPresets, "save",
				"connectionMode/camPresets");
	connect(camLoadPresetsWindow, &PresetsWindow::loadPreset,
					this, &ConnectionWidget::camLoadPresetSlot);
	connect(camSavePresetsWindow, &PresetsWindow::savePreset,
					this, &ConnectionWidget::camSavePresetSlot);
	triggerLoadPresetsWindow = new PresetsWindow(&triggerPresets, "load",
				"connectionMode/triggerPresets");
	triggerSavePresetsWindow = new PresetsWindow(&triggerPresets, "save",
				"connectionMode/triggerPresets");
	connect(triggerLoadPresetsWindow, &PresetsWindow::loadPreset,
					this, &ConnectionWidget::triggerLoadPresetSlot);
	connect(triggerSavePresetsWindow, &PresetsWindow::savePreset,
					this, &ConnectionWidget::triggerSavePresetSlot);

	QGridLayout *layout = new QGridLayout(this);

	//Camera Widget
	camWidget = new QWidget(this);
	QGridLayout *camlayout = new QGridLayout(camWidget);
	camPanelWidget = new QWidget(camWidget);
	camPanelWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	campanellayout = new QGridLayout(camPanelWidget);
	campanellayout->setContentsMargins(0, 11, 0, 11);
	camToolBar = new QToolBar(camWidget);
	camToolBar->setFixedHeight(45);
	camToolBar->setIconSize(QSize(35,35));
	QLabel *camLabel = new QLabel("Cameras", camToolBar);
	camLabel->setFont(QFont("Sans Serif", 12, QFont::Bold));
	QWidget *spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	autoDetectCamerasButton = new QToolButton(camToolBar);
	autoDetectCamerasAction = new QAction(camToolBar);
	createToolBarButton(autoDetectCamerasButton, autoDetectCamerasAction,
					QIcon::fromTheme("detect_cameras"), true, false, QSize(40,40));
	autoDetectCamerasButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	autoDetectCamerasAction->setIconText("Auto Detect Cameras");
	connect(autoDetectCamerasAction, &QAction::triggered,
					this, &ConnectionWidget::autoDetectCamerasClicked);
	camSavePresetButton = new QToolButton(camToolBar);
	camSavePresetAction = new QAction(camToolBar);
	createToolBarButton(camSavePresetButton, camSavePresetAction,
					QIcon::fromTheme("upload"), true, false, QSize(40,40));
	connect(camSavePresetAction, &QAction::triggered,
					this, &ConnectionWidget::camSavePresetsClickedSlot);
	camLoadPresetButton = new QToolButton(camToolBar);
	camLoadPresetAction = new QAction(camToolBar);
	createToolBarButton(camLoadPresetButton, camLoadPresetAction,
				QIcon::fromTheme("download"), true, false, QSize(40,40));
	connect(camLoadPresetAction, &QAction::triggered,
				this, &ConnectionWidget::camLoadPresetsClickedSlot);
	camToolBar->addWidget(camLabel);
	camToolBar->addWidget(spacer);
	camToolBar->addWidget(autoDetectCamerasButton);
	camToolBar->addWidget(camSavePresetButton);
	camToolBar->addWidget(camLoadPresetButton);
	int idx = 0;
	for (auto &camPanel : camPanels) {
		camPanel = new CamConnectionPanel(this);
		campanellayout->addWidget(camPanel, idx/(NUM_CAMS/4), idx%(NUM_CAMS/4));
		idx++;
		connect(camPanel, &CamConnectionPanel::camListChanged,
						this, &ConnectionWidget::camListChangedSlot);
		connect(camPanel, &CamConnectionPanel::camAdded,
						this, &ConnectionWidget::camAddedSlot);
		connect(camPanel, &CamConnectionPanel::statusUpdated,
						this, &ConnectionWidget::statusUpdatedSlot);
		connect(this, &ConnectionWidget::camListChanged,
						camPanel, &CamConnectionPanel::otherCamListChanged);
	}
	camlayout->addWidget(camToolBar,0,0);
	camlayout->addWidget(camPanelWidget,1,0);
	camlayout->setSpacing(0);
	camlayout->setContentsMargins(0, 0, 11, 0);

	//Trigger Widget
	triggerWidget = new QWidget(this);
	triggerWidget->setMaximumSize(350,10000);
	triggerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QGridLayout *triggerlayout = new QGridLayout(triggerWidget);
	triggerlayout->setMargin(0);
	triggerPanelWidget = new QWidget(triggerWidget);
	triggerpanellayout = new QGridLayout(triggerPanelWidget);
	triggerpanellayout->setContentsMargins(0, 11, 0, 11);
	triggerToolBar = new QToolBar(triggerWidget);
	triggerToolBar->setFixedHeight(45);
	triggerToolBar->setIconSize(QSize(35,35));
	QLabel *triggerLabel = new QLabel("Trigger", triggerToolBar);
	triggerLabel->setFont(QFont("Sans Serif", 12, QFont::Bold));
	QWidget *triggerSpacer = new QWidget();
	triggerSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	triggerSavePresetButton = new QToolButton(triggerToolBar);
	triggerSavePresetAction = new QAction(triggerToolBar);
	createToolBarButton(triggerSavePresetButton, triggerSavePresetAction,
				QIcon::fromTheme("upload"), true, false, QSize(40,40));
	connect(triggerSavePresetAction, &QAction::triggered,
					this, &ConnectionWidget::triggerSavePresetsClickedSlot);
	triggerLoadPresetButton = new QToolButton(triggerToolBar);
	triggerLoadPresetAction = new QAction(triggerToolBar);
	createToolBarButton(triggerLoadPresetButton, triggerLoadPresetAction,
				QIcon::fromTheme("download"), true, false, QSize(40,40));
	connect(triggerLoadPresetAction, &QAction::triggered,
					this, &ConnectionWidget::triggerLoadPresetsClickedSlot);
	triggerToolBar->addWidget(triggerLabel);
	triggerToolBar->addWidget(triggerSpacer);
	triggerToolBar->addWidget(triggerSavePresetButton);
	triggerToolBar->addWidget(triggerLoadPresetButton);
	triggerPanel = new TriggerConnectionPanel(this);
	connect(triggerPanel, &TriggerConnectionPanel::triggerInstanceChanged,
					this, &ConnectionWidget::triggerInstanceChangedSlot);
	triggerpanellayout->addWidget(triggerPanel,0, 0);

	triggerlayout->addWidget(triggerToolBar,0,0);
	triggerlayout->addWidget(triggerPanelWidget,1,0);
	triggerlayout->setSpacing(0);
	triggerlayout->setContentsMargins(11, 0, 0, 0);

	layout->addWidget(camWidget,0,0);
	layout->addWidget(triggerWidget,0,1);
	layout->setSpacing(0);
}


void ConnectionWidget::camListChangedSlot() {
	emit camListChanged();
}


void ConnectionWidget::camAddedSlot(CameraInterface * cam) {
	emit camAdded(cam);
}


void ConnectionWidget::triggerInstanceChangedSlot() {
	emit triggerInstanceChanged();
}


void ConnectionWidget::statusUpdatedSlot(CameraInterface* cam,
			statusType status, QString statusMsg) {
	emit statusUpdated(cam,status,statusMsg);
}


void ConnectionWidget::camLoadPresetsClickedSlot() {
	camLoadPresetsWindow->updateListSlot();
	camLoadPresetsWindow->show();
}


void ConnectionWidget::camSavePresetsClickedSlot() {
	camSavePresetsWindow->updateListSlot();
	camSavePresetsWindow->show();
}


void ConnectionWidget::camLoadPresetSlot(QString preset) {
	settings->beginGroup(preset);
	int idx = 0;
	for (auto &camPanel : camPanels) {
		delete camPanel;
		camPanel = new CamConnectionPanel(this);
		campanellayout->addWidget(camPanel, idx/(NUM_CAMS/4), idx%(NUM_CAMS/4));
		connect(camPanel, &CamConnectionPanel::camListChanged,
						this, &ConnectionWidget::camListChangedSlot);
		connect(camPanel, &CamConnectionPanel::camAdded,
						this, &ConnectionWidget::camAddedSlot);
		connect(camPanel, &CamConnectionPanel::statusUpdated,
						this, &ConnectionWidget::statusUpdatedSlot);
		settings->beginGroup("Panel_" + QString::number(idx++));
		if (settings->value("isConfigured").toBool()) {
			camPanel->camTypeCombo->setCurrentText(settings->
							value("cameraType").toString());
			QString cameraName = settings->value("cameraName").toString();

			camPanel->camConfigInterface->loadPreset(settings);
			camPanel->camera = camPanel->camConfigInterface->getCamera(cameraName);
			connect(camPanel->camera, &CameraInterface::statusUpdated,
							camPanel, &CamConnectionPanel::statusUpdatedSlot);
			camPanel->infoToolBarLabel->setText(cameraName);
			CameraInterface::cameraList.append(camPanel->camera);

			statusLog statusLog;
			statusLog.type = Connecting;
			statusLog.time = new QTime(0,0);
			statusLog.time->restart();
			statusLog.message = "";
			camPanel->statusLogWindow->statusLogList.push_back(statusLog);
			camPanel->stackWidget->setCurrentIndex(2);
			emit camAdded(camPanel->camera);
		}
		settings->endGroup();
	}
	emit camListChanged();
	settings->endGroup();
}


void ConnectionWidget::camSavePresetSlot(QString preset) {
	settings->beginGroup(preset);
	int idx = 0;
	for (const auto &camPanel : camPanels) {
		settings->beginGroup("Panel_" + QString::number(idx++));
		settings->setValue("isConfigured",
					camPanel->stackWidget->currentIndex() != 0);
		settings->setValue("cameraName", camPanel->infoToolBarLabel->text());
		settings->setValue("cameraType", camPanel->camTypeCombo->currentText());
		camPanel->camConfigInterface->savePreset(settings);
		settings->endGroup();
	}
	settings->endGroup();
}


void ConnectionWidget::triggerLoadPresetsClickedSlot() {
	triggerLoadPresetsWindow->updateListSlot();
	triggerLoadPresetsWindow->show();
}


void ConnectionWidget::triggerSavePresetsClickedSlot() {
	triggerSavePresetsWindow->updateListSlot();
	triggerSavePresetsWindow->show();
}


void ConnectionWidget::triggerLoadPresetSlot(QString preset) {
	settings->beginGroup(preset);
	delete triggerPanel;
	triggerPanel = new TriggerConnectionPanel(this);
	triggerpanellayout->addWidget(triggerPanel, 0, 0);
	connect(triggerPanel, &TriggerConnectionPanel::triggerInstanceChanged,
					this, &ConnectionWidget::triggerInstanceChangedSlot);
	if (settings->value("isConfigured").toBool()) {
		/*triggerPanel->example1Info->setText(settings->value("example1Info").toString());
		triggerPanel->example2Info->setText(settings->value("example2Info").toString());
		triggerPanel->triggerTypeCombo->setCurrentText(settings->value("triggerType").toString());
		if (triggerPanel->triggerTypeCombo->currentText() == "Test Trigger") {
			TriggerInterface::triggerInstance = new TestTrigger(triggerPanel->example1Info->text().toInt(), triggerPanel->example2Info->text());
			connect(TriggerInterface::triggerInstance, SIGNAL(statusUpdated(statusType, QString)), triggerPanel, SLOT(statusUpdatedSlot(statusType, QString)));
		}*/
		statusLog statusLog;
		statusLog.type = Connecting;
		statusLog.time = new QTime(0,0);
		statusLog.time->restart();
		statusLog.message = "";
		triggerPanel->statusLogWindow->statusLogList.push_back(statusLog);
		triggerPanel->stackWidget->setCurrentIndex(2);
		emit triggerInstanceChanged();
	}
	settings->endGroup();
}


void ConnectionWidget::triggerSavePresetSlot(QString preset) {
	settings->beginGroup(preset);
	settings->setValue("isConfigured",
				triggerPanel->stackWidget->currentIndex() != 0);
	/*settings->setValue("example1Info", triggerPanel->example1Info->text());
	settings->setValue("example2Info", triggerPanel->example2Info->text());*/
	settings->setValue("triggerType",
				triggerPanel->triggerTypeCombo->currentText());
	settings->endGroup();
}


void ConnectionWidget::autoDetectCamerasClicked() {
	if (CameraInterface::cameraList.size() != 0) {
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, "",
					"Auto detect Cameras? All currently connected Cameras will "
					"be removed!\n", QMessageBox::Yes|QMessageBox::No);

		if (reply == QMessageBox::No) {
			return;
		}
	}
	for (auto &camPanel : camPanels) {
		delete camPanel;
	}
	int idx = 0;
	FlirConfigBackend *configBackend = FlirConfigBackend::getInstance();
	QList<QString> flirCameraList = configBackend->getCameraIDs();
	for (auto &camPanel : camPanels) {
		camPanel = new CamConnectionPanel(this);
		campanellayout->addWidget(camPanel, idx/(NUM_CAMS/3), idx%(NUM_CAMS/3));
		connect(camPanel, &CamConnectionPanel::camListChanged,
						this, &ConnectionWidget::camListChangedSlot);
		connect(camPanel, &CamConnectionPanel::camAdded,
						this, &ConnectionWidget::camAddedSlot);
		connect(camPanel, &CamConnectionPanel::statusUpdated,
						this, &ConnectionWidget::statusUpdatedSlot);

		if(idx < flirCameraList.size()) {
			camPanel->camTypeCombo->setCurrentText("FLIR Chameleon");
			QString cameraName = "Camera_" + QString::number(idx);
			static_cast<FlirChameleonConfig*>(camPanel->camConfigInterface)->
						camIDInfo->setText(flirCameraList[idx]);
			camPanel->camera = camPanel->camConfigInterface->getCamera(cameraName);
			connect(camPanel->camera, &CameraInterface::statusUpdated,
							camPanel, &CamConnectionPanel::statusUpdatedSlot);
			camPanel->infoToolBarLabel->setText(cameraName);
			CameraInterface::cameraList.append(camPanel->camera);

			statusLog statusLog;
			statusLog.type = Connecting;
			statusLog.time = new QTime(0,0);
			statusLog.time->restart();
			statusLog.message = "";
			camPanel->statusLogWindow->statusLogList.push_back(statusLog);
			camPanel->stackWidget->setCurrentIndex(2);
			emit camAdded(camPanel->camera);
		}
		idx++;
	}
	emit camListChanged();
}
