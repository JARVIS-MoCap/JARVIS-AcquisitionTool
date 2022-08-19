/*******************************************************************************
 * File:        settingswindow.cpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "settingswindow.hpp"
#include "labelwithtooltip.hpp"

#include <QColorDialog>
#include <QGroupBox>
#include <QSpinBox>

GlobalSettings globalSettings;

SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent, Qt::Window) {
    this->resize(550, 400);
    this->setMinimumSize(500, 400);
    settings = new QSettings();
    setWindowTitle("Settings");
    QGridLayout *layout = new QGridLayout(this);

    mainWidget = new QWidget(this);
    QGridLayout *mainlayout = new QGridLayout(mainWidget);
    QGroupBox *recorderSettingsBox = new QGroupBox("Recorder Settings");
    recorderSettingsBox->setStyleSheet(
        "QGroupBox{background-color:rgb(34, 36, 40)}");
    QGridLayout *recordersettingslayout = new QGridLayout(recorderSettingsBox);

    QGroupBox *streamingSettingsBox = new QGroupBox("Streaming Settings");
    streamingSettingsBox->setStyleSheet(
        "QGroupBox{background-color:rgb(34, 36, 40)}");
    QGridLayout *streamingsettingslayout =
        new QGridLayout(streamingSettingsBox);
    mainlayout->addWidget(recorderSettingsBox, 0, 0);
    mainlayout->addWidget(streamingSettingsBox, 1, 0);

    advancedWidget = new QWidget(this);
    QGridLayout *advancedlayout = new QGridLayout(advancedWidget);

    hardwareCheckWidget = new HardwareCheck();

    infoWidget = new QWidget(this);
    QLabel *versionLabel = new QLabel("Version:");
    QLabel *versionText = new QLabel(this);
    versionText->setFont(QFont("Sans Serif", 12, QFont::Bold));
    versionText->setText(VERSION_STRING);
    versionText->setTextInteractionFlags(Qt::TextSelectableByMouse);
    versionText->setCursor(QCursor(Qt::IBeamCursor));
	QGridLayout *infolayout = new QGridLayout(infoWidget);
	QLabel *licenceText = new QLabel("Published under the LGPL v2.1 (2022)");
		QWidget *infoSpacer = new QWidget();
	infoSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	infolayout->addWidget(versionLabel,0,0);
	infolayout->addWidget(versionText,0,1);
	infolayout->addWidget(infoSpacer,1,0,1,2);
	infolayout->addWidget(licenceText,2,0,1,2);

    tabWidget = new QTabWidget();
	tabWidget->addTab(mainWidget, "Main");
	tabWidget->addTab(advancedWidget, "Advanced");
    tabWidget->addTab(hardwareCheckWidget, "Hadware Check");
    tabWidget->addTab(infoWidget, "Info");


    closeButton = new QPushButton("Close");
    closeButton->setMinimumSize(30, 30);
    connect(closeButton, &QPushButton::clicked, this, &SettingsWindow::hide);

    layout->addWidget(tabWidget,0,0);
    layout->addWidget(closeButton, 1, 0, Qt::AlignRight);

    // recorderSettings
    LabelWithToolTip *recorderTypeLabel = new LabelWithToolTip(
        "Recorder Type",
        "The Cuda Recorder uses GPU acceleration for compression. "
        "The Base Recorder does not require a GPU.");
    recorderTypeBox = new QComboBox(this);
    recorderTypeBox->setMaximumSize(150, 30);
#ifdef USE_CUDA
    recorderTypeBox->addItem("Cuda Recorder");
#endif
    recorderTypeBox->addItem("Base Recorder");
    connect(recorderTypeBox, &QComboBox::currentTextChanged, this,
            &SettingsWindow::recorderTypeChangedSlot);
    LabelWithToolTip *imageOrVideoLabel = new LabelWithToolTip(
        "Recording Format", "Select if you want to save videos or images. "
                            "Currently only videos are implemented.");
    imageOrVideoSelectorBox = new QComboBox(this);
    imageOrVideoSelectorBox->setMaximumSize(150, 30);
    imageOrVideoSelectorBox->addItem("Videos");
    // imageOrVideoSelectorBox->addItem("Images");
    connect(imageOrVideoSelectorBox, &QComboBox::currentTextChanged, this,
            &SettingsWindow::imageOrVideoSelectorChangedSlot);
    LabelWithToolTip *jpegQualityLabel = new LabelWithToolTip(
        "JPEG Quality Factor",
        "Quality factor for JPEG compression. "
        "Higher numbers give higher quality but slow down compression.");

    jpegQualityEdit = new QSpinBox();
    jpegQualityEdit->setRange(0, 100);
    jpegQualityEdit->setValue(95);
    connect(jpegQualityEdit, QOverload<int>::of(&QSpinBox::valueChanged), this,
            &SettingsWindow::jpegQualityChangedSlot);

    LabelWithToolTip *metadataLabel = new LabelWithToolTip(
        "Create Frame-Metadate file",
        "For each recording, all created metadata is saved as a CSV file."
        "The file is created in the same folder as the video files.");
    metadataEnabledSwitch = new ToggleSwitch();
    metadataEnabledSwitch->setMaximumSize(50, 20);
    metadataEnabledSwitch->setToggled(true);
    connect(metadataEnabledSwitch, &ToggleSwitch::toggled, this,
            &SettingsWindow::metadataEnableToggledSlot);

    recordersettingslayout->addWidget(recorderTypeLabel, 0, 0);
    recordersettingslayout->addWidget(recorderTypeBox, 0, 1);
    recordersettingslayout->addWidget(imageOrVideoLabel, 1, 0);
    recordersettingslayout->addWidget(imageOrVideoSelectorBox, 1, 1);
    recordersettingslayout->addWidget(jpegQualityLabel, 2, 0);
    recordersettingslayout->addWidget(jpegQualityEdit, 2, 1);
    recordersettingslayout->addWidget(metadataLabel, 3, 0);
    recordersettingslayout->addWidget(metadataEnabledSwitch, 3, 1);

    LabelWithToolTip *streamingSubsamplingRatioLabel = new LabelWithToolTip(
        "Streaming Subsampling Ratio",
        "Displayed camera images get scaled down by the selected factor during "
        "streaming.");
    streamingSubsamplingRatioBox = new QComboBox(this);
    streamingSubsamplingRatioBox->setMaximumSize(100, 30);
    streamingSubsamplingRatioBox->addItem("1");
    streamingSubsamplingRatioBox->addItem("2");
    streamingSubsamplingRatioBox->addItem("4");
    streamingSubsamplingRatioBox->addItem("8");
    streamingSubsamplingRatioBox->addItem("16");
    connect(streamingSubsamplingRatioBox, &QComboBox::currentTextChanged, this,
            &SettingsWindow::streamingSubsamplingRatioChangedSlot);

    LabelWithToolTip *streamingEnabledLabel = new LabelWithToolTip(
        "Streaming enabled during Recording",
        "If this is unselected no live view of your cameras is available during"
        " recording. Recording at slightly higher frame rates are possible.");
    streamingEnabledSwitch = new ToggleSwitch();
    streamingEnabledSwitch->setMaximumSize(50, 20);
    streamingEnabledSwitch->setToggled(true);
    connect(streamingEnabledSwitch, &ToggleSwitch::toggled, this,
            &SettingsWindow::streamingEnableToggledSlot);
    LabelWithToolTip *recordingSubsamplingRatioLabel = new LabelWithToolTip(
        "Recording Subsampling Ratio",
        "Displayed camera images get scaled down by the selected factor during "
        "recording.");
    recordingSubsamplingRatioBox = new QComboBox(this);
    recordingSubsamplingRatioBox->setMaximumSize(100, 30);
    recordingSubsamplingRatioBox->addItem("1");
    recordingSubsamplingRatioBox->addItem("2");
    recordingSubsamplingRatioBox->addItem("4");
    recordingSubsamplingRatioBox->addItem("8");
    recordingSubsamplingRatioBox->addItem("16");
    connect(recordingSubsamplingRatioBox, &QComboBox::currentTextChanged, this,
            &SettingsWindow::recordingSubsamplingRatioChangedSlot);

    streamingsettingslayout->addWidget(streamingSubsamplingRatioLabel, 0, 0);
    streamingsettingslayout->addWidget(streamingSubsamplingRatioBox, 0, 1);
    streamingsettingslayout->addWidget(streamingEnabledLabel, 1, 0);
    streamingsettingslayout->addWidget(streamingEnabledSwitch, 1, 1);
    streamingsettingslayout->addWidget(recordingSubsamplingRatioLabel, 2, 0);
    streamingsettingslayout->addWidget(recordingSubsamplingRatioBox, 2, 1);

    loadSettings();
}

void SettingsWindow::loadSettings() {
    settings->beginGroup("GlobalSettings");
    settings->beginGroup("RecorderSettings");
    if (settings->contains("RecorderType")) {
        recorderTypeBox->setCurrentText(
            settings->value("RecorderType").toString());
    } else {
        recorderTypeBox->setCurrentText("Cuda Recorder");
    }
    globalSettings.recorderType = recorderTypeBox->currentText();
    jpegQualityEdit->setEnabled(recorderTypeBox->currentText() ==
                                "Cuda Recorder");

    if (settings->contains("ImageOrVideo")) {
        imageOrVideoSelectorBox->setCurrentText(
            settings->value("ImageOrVideo").toString());
    } else {
        imageOrVideoSelectorBox->setCurrentText("Videos");
    }
    globalSettings.recordVideos =
        settings->value("ImageOrVideo").toString() == "Videos";

    if (settings->contains("jpegQualityFactor")) {
        jpegQualityEdit->setValue(settings->value("jpegQualityFactor").toInt());
    } else {
        jpegQualityEdit->setValue(95);
    }
    globalSettings.jpegQualityFactor = jpegQualityEdit->value();
    settings->endGroup();
    settings->beginGroup("StreamingSettings");

    if (settings->contains("StreamingSubsamplingRatio")) {
        streamingSubsamplingRatioBox->setCurrentText(
            settings->value("StreamingSubsamplingRatio").toString());
    } else {
        streamingSubsamplingRatioBox->setCurrentText("2");
    }
    globalSettings.streamingSubsamplingRatio =
        streamingSubsamplingRatioBox->currentText().toInt();

    if (settings->contains("StreamingEnabled")) {
        streamingEnabledSwitch->setToggled(
            settings->value("StreamingEnabled").toBool());
    } else {
        streamingEnabledSwitch->setToggled(true);
    }
    recordingSubsamplingRatioBox->setEnabled(
        streamingEnabledSwitch->isToggled());
    globalSettings.streamingEnabled = streamingEnabledSwitch->isToggled();

    if (settings->contains("RecordingSubsamplingRatio")) {
        recordingSubsamplingRatioBox->setCurrentText(
            settings->value("RecordingSubsamplingRatio").toString());
    } else {
        recordingSubsamplingRatioBox->setCurrentText("4");
    }
    globalSettings.recordingSubsamplingRatio =
        recordingSubsamplingRatioBox->currentText().toInt();

    settings->endGroup();
    settings->endGroup();
}

void SettingsWindow::updateSettings() {
    settings->beginGroup("GlobalSettings");
    settings->beginGroup("RecorderSettings");
    settings->setValue("RecorderType", recorderTypeBox->currentText());
    settings->setValue("ImageOrVideo", imageOrVideoSelectorBox->currentText());
    settings->setValue("jpegQualityFactor", jpegQualityEdit->value());
    settings->setValue("MetadataEnabled", metadataEnabledSwitch->isToggled());
    settings->endGroup();
    settings->beginGroup("StreamingSettings");
    settings->setValue("StreamingSubsamplingRatio",
                       streamingSubsamplingRatioBox->currentText());
    settings->setValue("StreamingEnabled", streamingEnabledSwitch->isToggled());
    settings->setValue("RecordingSubsamplingRatio",
                       recordingSubsamplingRatioBox->currentText());
    settings->endGroup();
    settings->endGroup();
}

void SettingsWindow::recorderTypeChangedSlot(const QString &type) {
    globalSettings.recorderType = type;
    jpegQualityEdit->setEnabled(type == "Cuda Recorder");
    updateSettings();
}

void SettingsWindow::imageOrVideoSelectorChangedSlot(const QString &type) {
    if (type == "Videos") {
        globalSettings.recordVideos = true;
    } else {
        globalSettings.recordVideos = false;
    }
    updateSettings();
}

void SettingsWindow::jpegQualityChangedSlot(int val) {
    globalSettings.jpegQualityFactor = val;
    updateSettings();
}
void SettingsWindow::metadataEnableToggledSlot(bool toggle) {
    globalSettings.metadataEnabled = toggle;
    updateSettings();
}

void SettingsWindow::streamingSubsamplingRatioChangedSlot(
    const QString &ratio) {
    globalSettings.streamingSubsamplingRatio = ratio.toInt();
    updateSettings();
}

void SettingsWindow::streamingEnableToggledSlot(bool toggle) {
    recordingSubsamplingRatioBox->setEnabled(toggle);
    globalSettings.streamingEnabled = toggle;
    updateSettings();
}

void SettingsWindow::recordingSubsamplingRatioChangedSlot(
    const QString &ratio) {
    globalSettings.recordingSubsamplingRatio = ratio.toInt();
    updateSettings();
}
