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
  updateCamIDsButton = new QPushButton(this);
  updateCamIDsButton->setIcon(QIcon::fromTheme("update"));
  updateCamIDsButton->setMinimumSize(25,25);
  updateCamIDsButton->setMaximumSize(25,25);
  connect(updateCamIDsButton, &QPushButton::clicked,
          this, &FlirChameleonConfig::updateCamIDs);
  configeditlayout->addWidget(camIDLabel,0,0);
  configeditlayout->addWidget(camIDCombo,0,1);
  configeditlayout->addWidget(updateCamIDsButton,0,2);


  configInfoBox = new QGroupBox("Flir Chameleon", this);
  QGridLayout *configinfolayout = new QGridLayout(configInfoBox);
  QLabel *camIDInfoLabel = new QLabel("Device ID", configInfoBox);
  camIDInfo = new QLineEdit(configInfoBox);
  camIDInfo->setReadOnly(true);
  configinfolayout->addWidget(camIDInfoLabel,0,0);
  configinfolayout->addWidget(camIDInfo,0,1);
}


void FlirChameleonConfig::updateDeviceIDs() {
  camIDCombo->clear();
  QList<QString> cameraIds = configBackend->getCameraIDs();
  camIDCombo->addItems(cameraIds);
}


bool FlirChameleonConfig::confirmConfigClicked() {
  if (camIDCombo->currentText() != "" && configBackend->checkCamList()) {
    camIDInfo->setText(camIDCombo->currentText());
    return true;
  }
  else {
    return false;
  }
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

void FlirChameleonConfig::updateCamIDs() {
    configBackend->updateIDs();
    updateDeviceIDs();
}
