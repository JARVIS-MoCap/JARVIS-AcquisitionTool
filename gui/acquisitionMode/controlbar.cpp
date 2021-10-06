/*------------------------------------------------------------
 *  controlbar.cpp
 *  Created:  27. October 2020
 *  Author:   Timo Hüser
 * *------------------------------------------------------------*/

#include "controlbar.hpp"
#include "camselectorwindow.hpp"

#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>


ControlBar::ControlBar(QWidget *parent) : QToolBar(parent) {
	settings = new QSettings();
	QString saveDirSettings = settings->value("recordingSaveFolder").toString();
	if (saveDirSettings == "") saveDirSettings = "../Savefiles";
	saveFileDir = QDir(saveDirSettings);
	this->setStyleSheet("QToolBar {border-bottom: 2px solid palette(window);}");
	this->setFixedHeight(60);
	this->setMovable(false);

	recordButton = new QToolButton(this);
	recordAction = new QAction(this);
	createToolBarButton(recordButton, recordAction, QIcon::fromTheme("record"),
											true, true, QSize(50,50));
	connect(recordAction, &QAction::toggled, this, &ControlBar::recordClickedSlot);
	startButton = new QToolButton(this);
	startAction = new QAction(this);
	createToolBarButton(startButton, startAction, QIcon::fromTheme("start"), true,
											true, QSize(50,50));
	connect(startAction, &QAction::toggled, this, &ControlBar::startClickedSlot);
	pauseButton = new QToolButton(this);
	pauseAction = new QAction(this);
	createToolBarButton(pauseButton, pauseAction, QIcon::fromTheme("pause"), false,
											true, QSize(50,50));
	connect(pauseAction, &QAction::toggled, this, &ControlBar::pauseClickedSlot);
	stopButton = new QToolButton(this);
	stopAction = new QAction(this);
	createToolBarButton(stopButton, stopAction, QIcon::fromTheme("stop"), false,
											false, QSize(50,50));
	connect(stopAction, &QAction::triggered, this, &ControlBar::stopClickedSlot);
	recordingTimeLabel = new QLabel(this);
	recordingTimer = new QTimer(this);
	recordingTime = new QTime(0,0);
	startTime = new QTime(0,0);
	recordingTimeLabel->setText(recordingTime->toString("mm:ss:zzz"));
	connect(recordingTimer,&QTimer::timeout, this, &ControlBar::recordingTimerSlot);
	recordingNameEdit = new QLineEdit(this);
	recordingNameEdit->setStyleSheet("QLineEdit{background-color: palette(window);}");
	recordingNameEdit->setPlaceholderText("Recording Name");
	recordingNameEdit->setMaximumSize(300,30);
	saveFolderButton = new QToolButton(this);
	saveFolderAction = new QAction(this);
	createToolBarButton(saveFolderButton, saveFolderAction, QIcon::fromTheme("folder"), true,
											false, QSize(50,50));
	connect(saveFolderAction, &QAction::triggered, this, &ControlBar::saveFolderClickedSlot);

	QWidget *spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	iconList["Default"] = QIcon::fromTheme("panels/default");
	iconList["DefaultActive"] = QIcon::fromTheme("panels/default_active");
	iconList["OneBig"] = QIcon::fromTheme("panels/oneBig");
	iconList["OneBigActive"] = QIcon::fromTheme("panels/oneBig_active");
	iconList["TwoBig"] = QIcon::fromTheme("panels/twoBig");
	iconList["TwoBigActive"] = QIcon::fromTheme("panels/twoBig_active");
	iconList["FourBig"] = QIcon::fromTheme("panels/fourBig");
	iconList["FourBigActive"] = QIcon::fromTheme("panels/fourBig_active");

	m_activeLayout = StreamingWidget::Default;
	defaultButton = new QToolButton(this);
	defaultAction = new QAction(this);
	createToolBarButton(defaultButton, defaultAction, iconList["DefaultActive"],
											true, false, QSize(50,50));
	connect(defaultAction, &QAction::triggered, this, &ControlBar::defaultLayoutSlot);
	oneBigButton = new QToolButton(this);
	oneBigAction = new QAction(this);
	createToolBarButton(oneBigButton, oneBigAction, iconList["OneBig"],
											true, false, QSize(50,50));
	connect(oneBigAction, &QAction::triggered, this, &ControlBar::oneBigLayoutSlot);
	twoBigButton = new QToolButton(this);
	twoBigAction = new QAction(this);
	createToolBarButton(twoBigButton, twoBigAction, iconList["TwoBig"],
											true, false, QSize(50,50));
	connect(twoBigAction, &QAction::triggered, this, &ControlBar::twoBigLayoutSlot);
	fourBigButton = new QToolButton(this);
	fourBigAction = new QAction(this);
	createToolBarButton(fourBigButton, fourBigAction, iconList["FourBig"],
											true, false, QSize(50,50));
	connect(fourBigAction, &QAction::triggered, this, &ControlBar::fourBigLayoutSlot);

	this->addWidget(recordButton);
	this->addSeparator();
	this->addWidget(startButton);
	this->addWidget(pauseButton);
	this->addWidget(stopButton);
	this->addSeparator();
	this->addWidget(recordingTimeLabel);
	this->addSeparator();
	this->addWidget(recordingNameEdit);
	this->addWidget(saveFolderButton);
	this->addWidget(spacer);
	defaultVisAction = this->addWidget(defaultButton);
	oneBigVisAction = this->addWidget(oneBigButton);
	twoBigVisAction = this->addWidget(twoBigButton);
	fourBigVisAction = this->addWidget(fourBigButton);
	oneBigVisAction->setVisible(false);
	twoBigVisAction->setVisible(false);
	fourBigVisAction->setVisible(false);
}


void ControlBar::recordClickedSlot(bool toggled) {
	if (toggled) {
		QString recordingName = recordingNameEdit->text();
		if (recordingNameEdit->text() == "") {
			recordingName = "Recording_" + QDateTime::currentDateTime().toString("yyyy-MM-ddThhmmss");
		}
		if (saveFileDir.exists(recordingName) || !saveFileDir.mkpath(recordingName)) {
			recordAction->setChecked(false);
			QMessageBox msgBox;
			msgBox.setText("Recording name already taken.\n Tipp: Leave blank for default timestamped name.");
			msgBox.exec();
			return;
		}
		QDir recordingDir = saveFileDir;
		recordingDir.cd(recordingName);
		AcquisitionSpecs acquisitionSpecs;
		acquisitionSpecs.record = true; //TODO: not hard code those values
		acquisitionSpecs.recordingDir = recordingDir;
		acquisitionSpecs.recorderType =CudaRecorderType;
		acquisitionSpecs.frameRate = TriggerInterface::triggerInstance->getFrameRate();
		acquisitionSpecs.streamingSamplingRatio = 4;
		m_recordingInfoFile = new QFile(recordingDir.filePath("RecordingInfo.txt"));
		if (m_recordingInfoFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
			QTextStream out(m_recordingInfoFile);
			out << "Store Recodringspecs here\n\n";
			m_recordingInfoFile->close();
		}
		emit recordingInfoFileCreated(m_recordingInfoFile, recordingTime);
		emit startAcquisition(acquisitionSpecs);
		startAction->setEnabled(false);
		recordAction->setEnabled(false);
		pauseAction->setEnabled(true);
		stopAction->setEnabled(true);
		recordingTimer->start(100);
		startTime->restart();

		bool trigger = false;
		while (!trigger) {
			trigger = true;
			for (const auto& cam : CameraInterface::cameraList) {
				if (!cam->isStreaming()) trigger = false;
			}
		}
		emit acquisitionStarted(320); 	//TODO: this is very temporary, this needs to be done by camerainterface
		TriggerInterface::triggerInstance->enable();
	}
}


void ControlBar::startClickedSlot(bool toggled) {
	if (toggled) {
		AcquisitionSpecs acquisitionSpecs;
		acquisitionSpecs.frameRate = TriggerInterface::triggerInstance->getFrameRate();
		acquisitionSpecs.recorderType = CudaRecorderType;
		acquisitionSpecs.streamingSamplingRatio = 2;
		emit startAcquisition(acquisitionSpecs);
		startAction->setEnabled(false);
		recordAction->setEnabled(false);
		pauseAction->setEnabled(true);
		stopAction->setEnabled(true);
		recordingTimer->start(100);
		emit acquisitionStarted(640); 	//TODO: this is very temporary, this needs to be done by camerainterface
		TriggerInterface::triggerInstance->enable();
	}
}


void ControlBar::pauseClickedSlot(bool toggled) {
	if (toggled) {
		recordingTimer->stop();
		TriggerInterface::triggerInstance->disable();
	}
	else {
		recordingTimer->start(100);
		TriggerInterface::triggerInstance->enable();
	}
}


void ControlBar::stopClickedSlot() {
	TriggerInterface::triggerInstance->disable();
	emit stopAcquisition();
	recordAction->setChecked(false);
	startAction->setChecked(false);
	pauseAction->setChecked(false);
	recordAction->setEnabled(true);
	startAction->setEnabled(true);
	pauseAction->setEnabled(false);
	stopAction->setEnabled(false);
	recordingTimer->stop();
	recordingTime->setHMS(0,0,0);
	recordingTimeLabel->setText(recordingTime->toString("mm:ss:zzz"));
}


void ControlBar::recordingTimerSlot() {
	*recordingTime = recordingTime->addMSecs(100);
	recordingTimeLabel->setText(recordingTime->toString("mm:ss:zzz"));
}

void ControlBar::saveFolderClickedSlot() {
	QString dir = QFileDialog::getExistingDirectory(this,"Recording Folder", saveFileDir.path(),
				QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	std::cout << dir.toStdString() << std::endl;
	if (dir != "") saveFileDir.setPath(dir);
	settings->setValue("recordingSaveFolder", dir);
}

void ControlBar::updateListSlot() {
	CamSelectorWindow::camVisibilityMap.clear();
	for (const auto cam : CameraInterface::cameraList) {
		CamSelectorWindow::camVisibilityMap[cam] = true;
	}
	m_activeLayout = StreamingWidget::Default;
	defaultAction->setIcon(iconList["DefaultActive"]);
	oneBigAction->setIcon(iconList["OneBig"]);
	twoBigAction->setIcon(iconList["TwoBig"]);
	fourBigAction->setIcon(iconList["FourBig"]);
	defaultVisAction->setVisible(true);
	oneBigVisAction->setVisible(CamSelectorWindow::camVisibilityMap.size() > 2);
	twoBigVisAction->setVisible(CamSelectorWindow::camVisibilityMap.size() > 4);
	fourBigVisAction->setVisible(CamSelectorWindow::camVisibilityMap.size() > 6);
	emit updateStreamingPanels(m_activeLayout);
}

void ControlBar::camAddedSlot(CameraInterface *cam) {
	connect(this, &ControlBar::startAcquisition, cam, &CameraInterface::startAcquisitionSlot);
	connect(this, &ControlBar::stopAcquisition, cam, &CameraInterface::stopAcquisitionSlot);
}

void ControlBar::camVisibilityToggledSlot(CameraInterface * cam, bool toggled) {
	m_activeLayout = StreamingWidget::Default;
	defaultAction->setIcon(iconList["DefaultActive"]);
	oneBigAction->setIcon(iconList["OneBig"]);
	twoBigAction->setIcon(iconList["TwoBig"]);
	fourBigAction->setIcon(iconList["FourBig"]);
	defaultVisAction->setVisible(true);
	CamSelectorWindow::camVisibilityMap[cam] = toggled;
	QMapIterator<CameraInterface *, bool> it(CamSelectorWindow::camVisibilityMap);
	int count = 0;
	while (it.hasNext()) {
	    it.next();
			if (it.value()) count++;
	}
	oneBigVisAction->setVisible(count > 2);
	twoBigVisAction->setVisible(count > 4);
	fourBigVisAction->setVisible(count > 6);
	emit updateStreamingPanels(m_activeLayout);
}

void ControlBar::defaultLayoutSlot() {
	if (m_activeLayout == StreamingWidget::Default) return;
	m_activeLayout = StreamingWidget::Default;
	defaultAction->setIcon(iconList["DefaultActive"]);
	oneBigAction->setIcon(iconList["OneBig"]);
	twoBigAction->setIcon(iconList["TwoBig"]);
	fourBigAction->setIcon(iconList["FourBig"]);
	emit updateStreamingPanels(m_activeLayout);
}

void ControlBar::oneBigLayoutSlot() {
	if (m_activeLayout == StreamingWidget::OneBig) return;
	m_activeLayout = StreamingWidget::OneBig;
	defaultAction->setIcon(iconList["Default"]);
	oneBigAction->setIcon(iconList["OneBigActive"]);
	twoBigAction->setIcon(iconList["TwoBig"]);
	fourBigAction->setIcon(iconList["FourBig"]);
	emit updateStreamingPanels(m_activeLayout);
}

void ControlBar::twoBigLayoutSlot() {
	if (m_activeLayout == StreamingWidget::TwoBig) return;
	m_activeLayout = StreamingWidget::TwoBig;
	defaultAction->setIcon(iconList["Default"]);
	oneBigAction->setIcon(iconList["OneBig"]);
	twoBigAction->setIcon(iconList["TwoBigActive"]);
	fourBigAction->setIcon(iconList["FourBig"]);
	emit updateStreamingPanels(m_activeLayout);
}

void ControlBar::fourBigLayoutSlot() {
	if (m_activeLayout == StreamingWidget::FourBig) return;
	m_activeLayout = StreamingWidget::FourBig;
	defaultAction->setIcon(iconList["Default"]);
	oneBigAction->setIcon(iconList["OneBig"]);
	twoBigAction->setIcon(iconList["TwoBig"]);
	fourBigAction->setIcon(iconList["FourBigActive"]);
	emit updateStreamingPanels(m_activeLayout);
}
