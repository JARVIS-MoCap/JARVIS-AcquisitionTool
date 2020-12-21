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
	serialInterface = new SerialInterface();
	settings = new QSettings();
	QString saveDirSettings = settings->value("recordingSaveFolder").toString();
	if (saveDirSettings == "") saveDirSettings = "../Savefiles";
	saveFileDir = QDir(saveDirSettings);
	this->setStyleSheet("QToolBar {border-bottom: 2px solid palette(window);}");
	this->setFixedHeight(60);
	this->setMovable(false);

	recordButton = new QToolButton(this);
	recordAction = new QAction(this);
	createToolBarButton(recordButton, recordAction, QIcon("icons/record.png"),
											true, true, QSize(50,50));
	connect(recordAction, &QAction::toggled, this, &ControlBar::recordClickedSlot);
	startButton = new QToolButton(this);
	startAction = new QAction(this);
	createToolBarButton(startButton, startAction, QIcon("icons/start.png"), true,
											true, QSize(50,50));
	connect(startAction, &QAction::toggled, this, &ControlBar::startClickedSlot);
	pauseButton = new QToolButton(this);
	pauseAction = new QAction(this);
	createToolBarButton(pauseButton, pauseAction, QIcon("icons/pause.png"), false,
											true, QSize(50,50));
	connect(pauseAction, &QAction::toggled, this, &ControlBar::pauseClickedSlot);
	stopButton = new QToolButton(this);
	stopAction = new QAction(this);
	createToolBarButton(stopButton, stopAction, QIcon("icons/stop.png"), false,
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
	createToolBarButton(saveFolderButton, saveFolderAction, QIcon("icons/folder.png"), true,
											false, QSize(50,50));
	connect(saveFolderAction, &QAction::triggered, this, &ControlBar::saveFolderClickedSlot);
	timeStampButton = new QToolButton(this);
	timeStampAction = new QAction(this);
	createToolBarButton(timeStampButton, timeStampAction, QIcon("icons/timestamp.png"), true,
											false, QSize(50,50));
	connect(timeStampAction, &QAction::triggered, this, &ControlBar::openTimeStampWindow);

	QWidget *spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	iconList["Default"] = QIcon("icons/panels/default.png");
	iconList["DefaultActive"] = QIcon("icons/panels/default_active.png");
	iconList["OneBig"] = QIcon("icons/panels/oneBig.png");
	iconList["OneBigActive"] = QIcon("icons/panels/oneBig_active.png");
	iconList["TwoBig"] = QIcon("icons/panels/twoBig.png");
	iconList["TwoBigActive"] = QIcon("icons/panels/twoBig_active.png");
	iconList["FourBig"] = QIcon("icons/panels/fourBig.png");
	iconList["FourBigActive"] = QIcon("icons/panels/fourBig_active.png");

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
	this->addSeparator();
	this->addWidget(timeStampButton);
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
		acquisitionSpecs.frameRate = 100;
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
		serialInterface->write(10);
	}
}


void ControlBar::startClickedSlot(bool toggled) {
	if (toggled) {
		AcquisitionSpecs acquisitionSpecs;
		acquisitionSpecs.frameRate = 100; //TODO: not hard code those values
		acquisitionSpecs.recorderType = CudaRecorderType;
		emit startAcquisition(acquisitionSpecs);
		startAction->setEnabled(false);
		recordAction->setEnabled(false);
		pauseAction->setEnabled(true);
		stopAction->setEnabled(true);
		recordingTimer->start(100);
		QTimer *timer = new QTimer(this);
		connect(timer, &QTimer::timeout, this, &ControlBar::startTrigger);
		timer->setSingleShot(true);
		timer->start(100);
	}
}

void ControlBar::startTrigger() {
	serialInterface->write(50);
}


void ControlBar::pauseClickedSlot(bool toggled) {
	if (toggled) {
		recordingTimer->stop();
		serialInterface->write(0);
	}
	else {
		recordingTimer->start(100);
		serialInterface->write(50);
	}
}


void ControlBar::stopClickedSlot() {
	serialInterface->write(0);
	delayl(100);
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
