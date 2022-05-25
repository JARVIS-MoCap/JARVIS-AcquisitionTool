/*******************************************************************************
 * File:        triggertestconfig.cpp
 * Created:     03. October 2021
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "triggertestconfig.hpp"
#include "globals.hpp"
#include "testtrigger.hpp"

#include <QGridLayout>
#include <QLabel>

TriggerTestConfig::TriggerTestConfig(QWidget *parent)
    : TriggerConfigInterface(parent) {
    configEditBox = new QGroupBox(this);
    QGridLayout *configeditlayout = new QGridLayout(configEditBox);
    QLabel *example1Label = new QLabel("Example 1", configEditBox);
    example1Edit = new QLineEdit(this);
    QLabel *example2Label = new QLabel("Example 2", configEditBox);
    example2Edit = new QLineEdit(this);
    configeditlayout->addWidget(example1Label, 0, 0);
    configeditlayout->addWidget(example1Edit, 0, 1);
    configeditlayout->addWidget(example2Label, 1, 0);
    configeditlayout->addWidget(example2Edit, 1, 1);

    configInfoBox = new QGroupBox("Test Trigger", this);
    QGridLayout *configinfolayout = new QGridLayout(configInfoBox);
    QLabel *example1InfoLabel = new QLabel("Example 1", configInfoBox);
    example1Info = new QLineEdit(configInfoBox);
    example1Info->setReadOnly(true);
    QLabel *example2InfoLabel = new QLabel("Example 2", configInfoBox);
    example2Info = new QLineEdit(configInfoBox);
    example2Info->setReadOnly(true);
    configinfolayout->addWidget(example1InfoLabel, 0, 0);
    configinfolayout->addWidget(example1Info, 0, 1);
    configinfolayout->addWidget(example2InfoLabel, 1, 0);
    configinfolayout->addWidget(example2Info, 1, 1);
}

bool TriggerTestConfig::confirmConfigClicked() {
    example1Info->setText(example1Edit->text());
    example2Info->setText(example2Edit->text());
    return true;
}

void TriggerTestConfig::loadPreset(QSettings *settings) {
    example1Info->setText(settings->value("example1Info").toString());
    example2Info->setText(settings->value("example2Info").toString());
}

void TriggerTestConfig::savePreset(QSettings *settings) {
    settings->setValue("example1Info", example1Info->text());
    settings->setValue("example2Info", example2Info->text());
}

TriggerInterface *TriggerTestConfig::getTrigger() {
    return new TestTrigger(example1Info->text(), example2Info->text());
}
