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


SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent, Qt::Window) {
	this->resize(600,600);
	this->setMinimumSize(500,550);
	settings = new QSettings();
	setWindowTitle("Settings");
	QGridLayout *layout = new QGridLayout(this);

	QGroupBox *recorderSettingsBox = new QGroupBox("Recorder Settings");
	QGridLayout *recordersettingslayout = new QGridLayout(recorderSettingsBox);

	QGroupBox *streamingSettingsBox = new QGroupBox("Straming Settings");
	QGridLayout *streamingsettingslayout = new QGridLayout(recorderSettingsBox);

	closeButton = new QPushButton("Close");
	closeButton->setMinimumSize(30,30);
	connect(closeButton, &QPushButton::clicked, this, &SettingsWindow::hide);

	layout->addWidget(recorderSettingsBox,0,0);
	layout->addWidget(streamingSettingsBox,1,0);
	layout->addWidget(closeButton,2,0, Qt::AlignRight);


	//recorderSettings
	LabelWithToolTip *recorderTypeLabel = new LabelWithToolTip("Recorder Type");
	recorderTypeBox = new QComboBox(this);
#ifdef USE_CUDA
	recorderTypeBox->addItem("Cuda Recorder");
#endif
	recorderTypeBox->addItem("Base Recorder");

	recordersettingslayout->addWidget(recorderTypeLabel,0,0);
	recordersettingslayout->addWidget(recorderTypeBox,0,1);


	// QComboBox *imageOrVideoSelectorBox;
	// QSpinBox *jpegQualityEdit;
	//
	// //streamingSettings
	// QComboBox *streamingSubsamplingRatio;
	// ToggleSwitch *streamingEnabledSwitch;
	// QComboBox *recordingSubsamplingRatio;


	loadSettings();
}


void SettingsWindow::loadSettings() {
	settings->beginGroup("Settings");
	settings->beginGroup("RecorderSettings");
	settings->endGroup();
	settings->beginGroup("StreamingSettings");
	settings->endGroup();
}
