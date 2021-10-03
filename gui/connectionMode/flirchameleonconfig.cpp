/*****************************************************************
 * File:			  flirchameleonconfig.cpp
 * Created: 	  03. October 2021
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     GPL v3.0
 *****************************************************************/

#include "globals.hpp"
#include "flirchameleonconfig.hpp"
#include "flirchameleon.hpp"

#include <QGridLayout>
#include <QLabel>


FlirChameleonConfig::FlirChameleonConfig(QWidget *parent) :
      CamConfigInterface(parent) {
  configBackend = FlirConfigBackend::getInstance();

  configEditBox = new QGroupBox(this);
  QGridLayout *configeditlayout = new QGridLayout(configEditBox);
  QLabel *camIDLabel = new QLabel("Device ID", configEditBox);
  camIDCombo = new QComboBox(this);
  updateDeviceIDs();
  configeditlayout->addWidget(camIDLabel,0,0);
  configeditlayout->addWidget(camIDCombo,0,1);

  configInfoBox = new QGroupBox("Flir Chameleon", this);
  QGridLayout *configinfolayout = new QGridLayout(configInfoBox);
  QLabel *camIDInfoLabel = new QLabel("Device ID", configInfoBox);
  camIDInfo = new QLineEdit(configInfoBox);
  camIDInfo->setReadOnly(true);
  configinfolayout->addWidget(camIDInfoLabel,0,0);
  configinfolayout->addWidget(camIDInfo,0,1);
}


void FlirChameleonConfig::updateDeviceIDs() {
  QList<QString> cameraIds = configBackend->getCameraIDs();
  camIDCombo->addItems(cameraIds);
}


void FlirChameleonConfig::confirmConfigClicked() {
  camIDInfo->setText(camIDCombo->currentText());
}


void	FlirChameleonConfig::loadPreset(QSettings *settings) {
  camIDInfo->setText(settings->value("camIDInfo").toString());
}


void FlirChameleonConfig::savePreset(QSettings *settings) {
  settings->setValue("camIDInfo", camIDInfo->text());
}


CameraInterface* FlirChameleonConfig::getCamera(const QString &cameraName) {
  return new FLIRChameleon(cameraName, camIDInfo->text());
}
