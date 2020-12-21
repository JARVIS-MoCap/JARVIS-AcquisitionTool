/*------------------------------------------------------------
 *  calibrationcontrolbar.cpp
 *  Created:  27. October 2020
 *  Author:   Timo Hüser
 * *------------------------------------------------------------*/

#include "calibrationcontrolbar.hpp"

#include <QTimer>

CalibrationControlBar::CalibrationControlBar(QWidget *parent) : QToolBar(parent) {
	settings = new QSettings();
	this->setStyleSheet("QToolBar {border-bottom: 2px solid palette(window);}");
	this->setFixedHeight(60);
	this->setMovable(false);

	startButton = new QToolButton(this);
	startAction = new QAction(this);
	createToolBarButton(startButton, startAction, QIcon("icons/start.png"), true,
											true, QSize(50,50));
	connect(startAction, &QAction::toggled, this, &CalibrationControlBar::startClickedSlot);
	pauseButton = new QToolButton(this);
	pauseAction = new QAction(this);
	createToolBarButton(pauseButton, pauseAction, QIcon("icons/pause.png"), false,
											true, QSize(50,50));
	connect(pauseAction, &QAction::toggled, this, &CalibrationControlBar::pauseClickedSlot);
	stopButton = new QToolButton(this);
	stopAction = new QAction(this);
	createToolBarButton(stopButton, stopAction, QIcon("icons/stop.png"), false,
											false, QSize(50,50));
	connect(stopAction, &QAction::triggered, this, &CalibrationControlBar::stopClickedSlot);
	recordingTimeLabel = new QLabel(this);
	recordingTimer = new QTimer(this);
	recordingTime = new QTime(0,0);
	recordingTimeLabel->setText(recordingTime->toString("mm:ss:zzz"));
	connect(recordingTimer,&QTimer::timeout, this, &CalibrationControlBar::recordingTimerSlot);

	QWidget *spacerLeft = new QWidget();
	spacerLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	counterLabel = new QLabel("Detected Checkerboards: ");
	counterLabel->setFont(fonts["big"]);
	counterEdit = new QLineEdit("0");
	counterEdit->setFont(fonts["big"]);
	counterEdit->setMaximumSize(100,100);
	counterEdit->setReadOnly(true);

	QWidget *spacerRight = new QWidget();
	spacerRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	calibrateButton = new QPushButton("Calibrate");
	calibrateButton->setMinimumSize(QSize(50,50));
	calibrateButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	calibrateButton->setEnabled(false);
	connect(calibrateButton, &QPushButton::clicked, this, &CalibrationControlBar::calibrateClicked);

	recalibrateButton = new QPushButton("Recalibrate");
	recalibrateButton->setMinimumSize(QSize(50,50));
	recalibrateButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	recalibrateButton->setEnabled(false);
	connect(recalibrateButton, &QPushButton::clicked, this, &CalibrationControlBar::calibrateClicked);

	resetButton = new QPushButton("Reset");
	resetButton->setMinimumSize(QSize(50,50));
	resetButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	resetButton->setEnabled(false);
	connect(resetButton, &QPushButton::clicked, this, &CalibrationControlBar::resetClickedSlot);

	saveButton = new QPushButton("Save");
	saveButton->setMinimumSize(QSize(50,50));
	saveButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	saveButton->setEnabled(false);
	//connect(resetButton, &QPushButton::clicked, this, &CalibrationControlBar::resetClicked);

	this->addWidget(startButton);
	this->addWidget(pauseButton);
	this->addWidget(stopButton);
	this->addSeparator();
	this->addWidget(recordingTimeLabel);
	this->addWidget(spacerLeft);
	this->addWidget(counterLabel);
	this->addWidget(counterEdit);
	this->addWidget(spacerRight);
	calibrateAction = this->addWidget(calibrateButton);
	recalibrateAction = this->addWidget(recalibrateButton);
	resetAction = this->addWidget(resetButton);
	saveAction = this->addWidget(saveButton);
	recalibrateAction->setVisible(false);
	resetAction->setVisible(false);
	saveAction->setVisible(false);

}

void CalibrationControlBar::activateCalibrateButton() {
	calibrateButton->setEnabled(true);
}

void CalibrationControlBar::counterChangedSlot(int count) {
	counterEdit->setText(QString::number(count));
}

void CalibrationControlBar::calibrationFinishedSlot() {
	calibrateAction->setVisible(false);
	recalibrateAction->setVisible(true);
	resetAction->setVisible(true);
	saveAction->setVisible(true);
}

void CalibrationControlBar::startClickedSlot(bool toggled) {
	if (toggled) {
		AcquisitionSpecs acquisitionSpecs;
		acquisitionSpecs.frameRate = 100; //TODO: not hard code those values
		acquisitionSpecs.recorderType = BaseRecorderType;
		emit startAcquisition(acquisitionSpecs);
		startAction->setEnabled(false);
		pauseAction->setEnabled(true);
		stopAction->setEnabled(true);
		recordingTimer->start(100);
	}
}


void CalibrationControlBar::pauseClickedSlot(bool toggled) {
	if (toggled) {
		recordingTimer->stop();
	}
	else {
		recordingTimer->start(100);
	}
}


void CalibrationControlBar::stopClickedSlot() {
	emit stopAcquisition();
	startAction->setChecked(false);
	pauseAction->setChecked(false);
	startAction->setEnabled(true);
	pauseAction->setEnabled(false);
	stopAction->setEnabled(false);
	recordingTimer->stop();
	recordingTime->setHMS(0,0,0);
	recordingTimeLabel->setText(recordingTime->toString("mm:ss:zzz"));
}


void CalibrationControlBar::recordingTimerSlot() {
	*recordingTime = recordingTime->addMSecs(100);
	recordingTimeLabel->setText(recordingTime->toString("mm:ss:zzz"));
}

void CalibrationControlBar::resetClickedSlot() {
	recalibrateAction->setVisible(false);
	resetAction->setVisible(false);
	saveAction->setVisible(false);
	calibrateAction->setVisible(true);
	calibrateButton->setEnabled(false);
	counterEdit->setText("0");
	emit resetClicked();
}
