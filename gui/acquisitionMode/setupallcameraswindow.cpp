/*******************************************************************************
 * File:			  setupallcameraswindow.cpp
 * Created: 	  06. January 2022
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "setupallcameraswindow.hpp"
#include "labelwithtooltip.hpp"

#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QMessageBox>
#include <QGroupBox>
#include <QScrollArea>


SetupAllCamerasWindow::SetupAllCamerasWindow(QWidget *parent) :
      QDialog(parent) {
  setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	settings = new QSettings();
  loadSettings();
	setMinimumSize(400,400);
	setWindowTitle("Setup All Cameras");
  QGridLayout *layout = new QGridLayout(this);
  layout->setSpacing(20);
  QGroupBox *settingsBox = new QGroupBox("Camera Settings");
  settingsBox->setStyleSheet(
        "QGroupBox{background-color:rgb(34, 36, 40)}");
  QGridLayout *settingslayout = new QGridLayout(settingsBox);

  QLabel *generalLabel = new QLabel("General");
  generalLabel->setFont(QFont("Sans Serif", 12, QFont::Bold));
  LabelWithToolTip *loadDefaultLabel = new LabelWithToolTip("  Load Defaults before Setup");
  loadDefaultUserSetToggle = new ToggleSwitch();
  loadDefaultUserSetToggle->setMinimumSize(70,22);
  loadDefaultUserSetToggle->setMaximumSize(70,22);
  loadDefaultUserSetToggle->setToggled(m_cameraSettings.loadDefaults);
  LabelWithToolTip *externalTriggerLabel = new LabelWithToolTip("  Setup for External Trigger");
  externalTriggerToggle = new ToggleSwitch();
  externalTriggerToggle->setMinimumSize(70,22);
  externalTriggerToggle->setMaximumSize(70,22);
  externalTriggerToggle->setToggled(m_cameraSettings.useExternalTrigger);
  QLabel *exposureLabel = new QLabel("Exposure Control");
  exposureLabel->setFont(QFont("Sans Serif", 12, QFont::Bold));
  LabelWithToolTip *exposureAutoLabel = new LabelWithToolTip("  Exposure Auto");
  exposureAutoToggle = new ToggleSwitch();
  exposureAutoToggle->setMinimumSize(70,22);
  exposureAutoToggle->setMaximumSize(70,22);
  exposureAutoToggle->setToggled(m_cameraSettings.exposureAuto);
  connect(exposureAutoToggle, &ToggleSwitch::toggled, this, &SetupAllCamerasWindow::exposureAutoToggledSlot);
  LabelWithToolTip *exposureValueLabel = new LabelWithToolTip("  Exposure Time [ms]");
  exposureEdit = new QDoubleSpinBox();
  exposureEdit->setValue(m_cameraSettings.exposureTime);

  QLabel *gainLabel = new QLabel("Gain Control");
  gainLabel->setFont(QFont("Sans Serif", 12, QFont::Bold));
  LabelWithToolTip *gainAutoLabel = new LabelWithToolTip("  Gain Auto");
  gainAutoToggle = new ToggleSwitch();
  gainAutoToggle->setMinimumSize(70,22);
  gainAutoToggle->setMaximumSize(70,22);
  gainAutoToggle->setToggled(m_cameraSettings.gainAuto);
  connect(gainAutoToggle, &ToggleSwitch::toggled, this, &SetupAllCamerasWindow::gainAutoToggledSlot);
  LabelWithToolTip *gainValueLabel = new LabelWithToolTip("  Gain [dB]");
  gainEdit = new QDoubleSpinBox();
  gainEdit->setValue(m_cameraSettings.gain);
  //LabelWithToolTip *pixelFormatLabel = new QLabel("Pixel Format");
  //pixelFormatBox = new QComboBox();
  //pixelFormatBox->addItem("BayerRG8");
  setupButton = new QPushButton("Setup");
  setupButton->setIcon(QIcon::fromTheme("start"));
  setupButton->setMinimumSize(100,30);
  setupButton->setMaximumSize(100,30);
  connect(setupButton, &QPushButton::clicked, this, &SetupAllCamerasWindow::setupButtonClickedSlot);

  int i = 0;
  settingslayout->addWidget(generalLabel, i++,0,1,2);
  settingslayout->addWidget(loadDefaultLabel, i,0);
  settingslayout->addWidget(loadDefaultUserSetToggle, i++,1);
  settingslayout->addWidget(externalTriggerLabel,i,0);
  settingslayout->addWidget(externalTriggerToggle, i++,1);
  settingslayout->addWidget(exposureLabel, i++,0,1,2);
  settingslayout->addWidget(exposureAutoLabel,i,0);
  settingslayout->addWidget(exposureAutoToggle, i++,1);
  settingslayout->addWidget(exposureValueLabel,i,0);
  settingslayout->addWidget(exposureEdit, i++,1);
  settingslayout->addWidget(gainLabel, i++,0,1,2);
  settingslayout->addWidget(gainAutoLabel,i,0);
  settingslayout->addWidget(gainAutoToggle, i++,1);
  settingslayout->addWidget(gainValueLabel,i,0);
  settingslayout->addWidget(gainEdit, i++,1);

  layout->addWidget(settingsBox,0,0);
  layout->addWidget(setupButton, 1, 0, Qt::AlignRight);
}


void SetupAllCamerasWindow::loadSettings() {
  settings->beginGroup("AllCameraSetup");
	if (settings->contains("LoadDefaults")) {
		m_cameraSettings.loadDefaults = settings->value("LoadDefaults").toBool();
	}
  if (settings->contains("UseExternalTrigger")) {
    m_cameraSettings.useExternalTrigger = settings->value("UseExternalTrigger").toBool();
  }
  if (settings->contains("ExposureAuto")) {
    m_cameraSettings.exposureAuto = settings->value("ExposureAuto").toBool();
  }
  if (settings->contains("ExposureTime")) {
    m_cameraSettings.exposureTime = settings->value("ExposureTime").toFloat();
  }
  if (settings->contains("GainAuto")) {
    m_cameraSettings.gainAuto = settings->value("GainAuto").toBool();
  }
  if (settings->contains("GainTime")) {
    m_cameraSettings.gain = settings->value("GainTime").toFloat();
  }
  settings->endGroup();
}

void SetupAllCamerasWindow::saveSettings() {
  settings->beginGroup("AllCameraSetup");
	settings->setValue("LoadDefaults", m_cameraSettings.loadDefaults);
	settings->setValue("UseExternalTrigger", m_cameraSettings.useExternalTrigger);
  settings->setValue("ExposureAuto", m_cameraSettings.exposureAuto);
  settings->setValue("ExposureTime", m_cameraSettings.exposureTime);
  settings->setValue("GainAuto", m_cameraSettings.gainAuto);
  settings->setValue("GainTime", m_cameraSettings.gain);
  settings->endGroup();
}

void SetupAllCamerasWindow::setupButtonClickedSlot() {
  m_cameraSettings.loadDefaults = loadDefaultUserSetToggle->isToggled();
  m_cameraSettings.useExternalTrigger = externalTriggerToggle->isToggled();
  m_cameraSettings.exposureAuto = exposureAutoToggle->isToggled();
  m_cameraSettings.exposureTime = exposureEdit->value();
  m_cameraSettings.gainAuto = gainAutoToggle->isToggled();
  m_cameraSettings.gain = gainEdit->value();
  saveSettings();
  emit accept();
}

void SetupAllCamerasWindow::exposureAutoToggledSlot(bool toggle) {
  exposureEdit->setEnabled(!toggle);
}


void SetupAllCamerasWindow::gainAutoToggledSlot(bool toggle) {
  gainEdit->setEnabled(!toggle);
}
