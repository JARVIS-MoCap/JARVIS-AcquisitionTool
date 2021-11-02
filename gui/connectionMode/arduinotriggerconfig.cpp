/*******************************************************************************
 * File:			  arduinotriggerconfig.cpp
 * Created: 	  03. October 2021
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "globals.hpp"
#include "arduinotriggerconfig.hpp"
#include "arduinotrigger.hpp"

#include <QGridLayout>
#include <QLabel>


ArduinoTriggerConfig::ArduinoTriggerConfig(QWidget *parent) :
      TriggerConfigInterface(parent) {
  configBackend = ArduinoConfigBackend::getInstance();
  availableDevices = configBackend->getAvailableDevices();

  configEditBox = new QGroupBox(this);
  QGridLayout *configeditlayout = new QGridLayout(configEditBox);
  QLabel *deviceNameLabel = new QLabel("Device Name", configEditBox);
  deviceNameCombo = new QComboBox(this);
  for (const auto& device : availableDevices) {
    if (device != "") {
      deviceNameCombo->addItem(device);
    }
  }
  updateDeviceNamesButton = new QPushButton(this);
  updateDeviceNamesButton->setIcon(QIcon::fromTheme("update"));
  updateDeviceNamesButton->setMinimumSize(25,25);
  updateDeviceNamesButton->setMaximumSize(25,25);
  connect(updateDeviceNamesButton, &QPushButton::clicked,
          this, &ArduinoTriggerConfig::updateDeviceNamesSlot);
  configeditlayout->addWidget(deviceNameLabel,0,0);
  configeditlayout->addWidget(deviceNameCombo,0,1);
  configeditlayout->addWidget(updateDeviceNamesButton,0,2);

  configInfoBox = new QGroupBox("Arduino Trigger", this);
  QGridLayout *configinfolayout = new QGridLayout(configInfoBox);
  QLabel *deviceNameInfoLabel = new QLabel("Device Name", configInfoBox);
  deviceNameInfo = new QLineEdit(configInfoBox);
  deviceNameInfo->setReadOnly(true);
  configinfolayout->addWidget(deviceNameInfoLabel,0,0);
  configinfolayout->addWidget(deviceNameInfo,0,1);
}


bool ArduinoTriggerConfig::confirmConfigClicked() {
  if (deviceNameCombo->currentText() != "") {
    deviceNameInfo->setText(deviceNameCombo->currentText());
    return true;
  }
  return false;
}


void ArduinoTriggerConfig::loadPreset(QSettings *settings) {
  deviceNameInfo->setText(settings->value("DeviceName").toString());
}


void ArduinoTriggerConfig::savePreset(QSettings *settings) {
  settings->setValue("DeviceName", deviceNameInfo->text());
}


TriggerInterface* ArduinoTriggerConfig::getTrigger() {
  return new ArduinoTrigger(deviceNameInfo->text());
}


void ArduinoTriggerConfig::updateDeviceNamesSlot() {
  availableDevices = configBackend->getAvailableDevices();
  deviceNameCombo->clear();
  for (const auto& device : availableDevices) {
    if (device != "") {
      deviceNameCombo->addItem(device);
    }
  }
}
