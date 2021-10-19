/*****************************************************************
	* File:			  settingswindow.cpp
	* Created: 	  23. October 2020
	* Author:		  Timo Hueser
	* Contact: 	  timo.hueser@gmail.com
	* Copyright:  2021 Timo Hueser
	* License:    GPL v3.0
	*****************************************************************/

#include "settingswindow.hpp"
#include "labelwithtooltip.hpp"

#include <QSpinBox>
#include <QColorDialog>
#include <QGroupBox>

GlobalSettings globalSettings;

SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent, Qt::Window) {
	this->resize(500,400);
	this->setMinimumSize(500,400);
	settings = new QSettings();
	setWindowTitle("Settings");
	QGridLayout *layout = new QGridLayout(this);

	QGroupBox *recorderSettingsBox = new QGroupBox("Recorder Settings");
	recorderSettingsBox->setStyleSheet("QGroupBox{background-color:rgb(34, 36, 40)}");
	QGridLayout *recordersettingslayout = new QGridLayout(recorderSettingsBox);

	QGroupBox *streamingSettingsBox = new QGroupBox("Streaming Settings");
	streamingSettingsBox->setStyleSheet("QGroupBox{background-color:rgb(34, 36, 40)}");
	QGridLayout *streamingsettingslayout = new QGridLayout(streamingSettingsBox);

	closeButton = new QPushButton("Close");
	closeButton->setMinimumSize(30,30);
	connect(closeButton, &QPushButton::clicked, this, &SettingsWindow::hide);

	layout->addWidget(recorderSettingsBox,0,0);
	layout->addWidget(streamingSettingsBox,1,0);
	layout->addWidget(closeButton,2,0, Qt::AlignRight);


	//recorderSettings
	LabelWithToolTip *recorderTypeLabel = new LabelWithToolTip("Recorder Type");
	recorderTypeBox = new QComboBox(this);
	recorderTypeBox->setMaximumSize(150,30);
#ifdef USE_CUDA
	recorderTypeBox->addItem("Cuda Recorder");
#endif
	recorderTypeBox->addItem("Base Recorder");
	connect(recorderTypeBox, &QComboBox::currentTextChanged, this, &SettingsWindow::recorderTypeChangedSlot);
	LabelWithToolTip *imageOrVideoLabel = new LabelWithToolTip("Recording Format");
	imageOrVideoSelectorBox = new QComboBox(this);
	imageOrVideoSelectorBox->setMaximumSize(150,30);
	imageOrVideoSelectorBox->addItem("Videos");
	imageOrVideoSelectorBox->addItem("Images");
	connect(imageOrVideoSelectorBox, &QComboBox::currentTextChanged, this, &SettingsWindow::imageOrVideoSelectorChangedSlot);
	LabelWithToolTip *jpegQualityLabel = new LabelWithToolTip("JPEG Quality Factor");
	jpegQualityEdit = new QSpinBox();
	jpegQualityEdit->setRange(0,100);
	jpegQualityEdit->setValue(95);
	connect(jpegQualityEdit, QOverload<int>::of(&QSpinBox::valueChanged), this, &SettingsWindow::jpegQualityChangedSlot);

	recordersettingslayout->addWidget(recorderTypeLabel,0,0);
	recordersettingslayout->addWidget(recorderTypeBox,0,1);
	recordersettingslayout->addWidget(imageOrVideoLabel,1,0);
	recordersettingslayout->addWidget(imageOrVideoSelectorBox,1,1);
	recordersettingslayout->addWidget(jpegQualityLabel,2,0);
	recordersettingslayout->addWidget(jpegQualityEdit,2,1);

	LabelWithToolTip *streamingSubsamplingRatioLabel = new LabelWithToolTip("Streaming Subsampling Ratio");
	streamingSubsamplingRatioBox = new QComboBox(this);
	streamingSubsamplingRatioBox->setMaximumSize(100,30);
	streamingSubsamplingRatioBox->addItem("1");
	streamingSubsamplingRatioBox->addItem("2");
	streamingSubsamplingRatioBox->addItem("4");
	streamingSubsamplingRatioBox->addItem("8");
	streamingSubsamplingRatioBox->addItem("16");
	connect(streamingSubsamplingRatioBox, &QComboBox::currentTextChanged, this, &SettingsWindow::streamingSubsamplingRatioChangedSlot);

	LabelWithToolTip *streamingEnabledLabel = new LabelWithToolTip("Streaming enabled during Recording");
	streamingEnabledSwitch = new ToggleSwitch();
	streamingEnabledSwitch->setMaximumSize(80,20);
	streamingEnabledSwitch->setToggled(true);
	connect(streamingEnabledSwitch, &ToggleSwitch::toggled, this, &SettingsWindow::streamingEnableToggledSlot);
	LabelWithToolTip *recordingSubsamplingRatioLabel = new LabelWithToolTip("Recording Subsampling Ratio");
	recordingSubsamplingRatioBox = new QComboBox(this);
	recordingSubsamplingRatioBox->setMaximumSize(100,30);
	recordingSubsamplingRatioBox->addItem("1");
	recordingSubsamplingRatioBox->addItem("2");
	recordingSubsamplingRatioBox->addItem("4");
	recordingSubsamplingRatioBox->addItem("8");
	recordingSubsamplingRatioBox->addItem("16");
	connect(recordingSubsamplingRatioBox, &QComboBox::currentTextChanged, this, &SettingsWindow::recordingSubsamplingRatioChangedSlot);

	streamingsettingslayout->addWidget(streamingSubsamplingRatioLabel,0,0);
	streamingsettingslayout->addWidget(streamingSubsamplingRatioBox,0,1);
	streamingsettingslayout->addWidget(streamingEnabledLabel,1,0);
	streamingsettingslayout->addWidget(streamingEnabledSwitch,1,1);
	streamingsettingslayout->addWidget(recordingSubsamplingRatioLabel,2,0);
	streamingsettingslayout->addWidget(recordingSubsamplingRatioBox,2,1);

	loadSettings();
}


void SettingsWindow::loadSettings() {
	settings->beginGroup("Settings");
	settings->beginGroup("RecorderSettings");
	settings->endGroup();
	settings->beginGroup("StreamingSettings");
	settings->endGroup();
}

void SettingsWindow::updateSettings() {
	std::cout << "Updated settingd" << std::endl;
}

void SettingsWindow::recorderTypeChangedSlot(const QString& type) {
	globalSettings.recorderType = type;
	updateSettings();
}


void SettingsWindow::imageOrVideoSelectorChangedSlot(const QString& type) {
	if (type == "Videos") {
		globalSettings.recordVideos = true;
	}
	else {
		globalSettings.recordVideos = false;
	}
	updateSettings();
}


void SettingsWindow::jpegQualityChangedSlot(int val) {
	globalSettings.jpegQualityFactor = val;
	updateSettings();
}


void SettingsWindow::streamingSubsamplingRatioChangedSlot(const QString &ratio) {
	globalSettings.streamingSubsamplingRatio = ratio.toInt();
	updateSettings();
}

void SettingsWindow::streamingEnableToggledSlot(bool toggle) {
	recordingSubsamplingRatioBox->setEnabled(toggle);
	globalSettings.streamingEnabled = toggle;
	updateSettings();
}

void SettingsWindow::recordingSubsamplingRatioChangedSlot(const QString &ratio) {
	globalSettings.recordingSubsamplingRatio = ratio.toInt();
	updateSettings();
}
