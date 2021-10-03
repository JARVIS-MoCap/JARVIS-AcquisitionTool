/*------------------------------------------------------------
 *  camtestconfig.cpp
 *  Created:  23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "globals.hpp"
#include "camtestconfig.hpp"
#include "testcamera.hpp"


#include <QGridLayout>

CamTestConfig::CamTestConfig(QWidget *parent) : CamConfigInterface(parent) {
  configEditBox = new QGroupBox(this);
  QGridLayout *configeditlayout = new QGridLayout(configEditBox);
  QLabel *example1Label = new QLabel("Example 1", configEditBox);
  example1Edit = new QLineEdit(this);
  QLabel *example2Label = new QLabel("Example 2", configEditBox);
  example2Edit = new QLineEdit(this);
  configeditlayout->addWidget(example1Label,0,0);
  configeditlayout->addWidget(example1Edit,0,1);
  configeditlayout->addWidget(example2Label,1,0);
  configeditlayout->addWidget(example2Edit,1,1);

  configInfoBox = new QGroupBox("Test Camera", this);
  QGridLayout *configinfolayout = new QGridLayout(configInfoBox);
  QLabel *example1InfoLabel = new QLabel("Example 1", configInfoBox);
  example1Info = new QLineEdit(configInfoBox);
  example1Info->setReadOnly(true);
  QLabel *example2InfoLabel = new QLabel("Example 2", configInfoBox);
  example2Info = new QLineEdit(configInfoBox);
  example2Info->setReadOnly(true);
  configinfolayout->addWidget(example1InfoLabel,0,0);
  configinfolayout->addWidget(example1Info,0,1);
  configinfolayout->addWidget(example2InfoLabel,1,0);
  configinfolayout->addWidget(example2Info,1,1);
}

void CamTestConfig::confirmConfigClicked() {
  example1Info->setText(example1Edit->text());
  example2Info->setText(example2Edit->text());
}


void CamTestConfig::loadPreset(QSettings *settings) {
  example1Info->setText(settings->value("example1Info").toString());
  example2Info->setText(settings->value("example2Info").toString());
}


void CamTestConfig::savePreset(QSettings *settings) {
  settings->setValue("example1Info", example1Info->text());
  settings->setValue("example2Info", example2Info->text());
}

CameraInterface* CamTestConfig::getCamera(const QString &cameraName) {
  return new TestCamera(cameraName, example1Info->text(), example2Info->text());
}
