/*******************************************************************************
 * File:        arduinotrigger.cpp
 * Created:     03. October 2021
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "arduinotrigger.hpp"
#include "arduinoserialpeer.hpp"

#include <QApplication>
#include <QTimer>

ArduinoTrigger::ArduinoTrigger(const QString &deviceName)
    : TriggerInterface{arduinoTrigger} {
    createSettings();
    serialInterface = new SerialInterface(deviceName);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(intitialStatusSlot()));
    timer->setSingleShot(true);
    timer->start(100);
}

ArduinoTrigger::~ArduinoTrigger() {
    delete serialInterface;
    delete m_triggerSettings;
}

void ArduinoTrigger::intitialStatusSlot() {
    if (serialInterface->isConnected()) {
        emit statusUpdated(Ready, "");
    } else {
        emit statusUpdated(Error, "Connection Failed!");
    }
}

void ArduinoTrigger::createSettings() {
    m_triggerSettingsRootNode = new RootNode("");

    CategoryNode *arduinoTriggerNode =
        new CategoryNode(m_triggerSettingsRootNode, "ArduinoTrigger");
    arduinoTriggerNode->setDescription("Arduino Trigger Settings");

    IntNode *frameRateNode = new IntNode(arduinoTriggerNode, "FrameRate");
    frameRateNode->setDescription("Recording Frame Rate.");
    frameRateNode->setValue(100);

    m_triggerSettingsRootNode->addChild(arduinoTriggerNode);
    arduinoTriggerNode->addChild(frameRateNode);

    m_triggerSettings =
        new SettingsObject(this, "Trigger Settings", m_triggerSettingsRootNode);

    connect(m_triggerSettings, &SettingsObject::settingChanged, this,
            &ArduinoTrigger::settingChangedSlot);
}

void ArduinoTrigger::enable() { serialInterface->write(m_frameRate); }

void ArduinoTrigger::disable() { serialInterface->write(0); }

void ArduinoTrigger::settingChangedSlot(const QString &name,
                                        QList<QString> subMenus,
                                        SettingsNode::nodeType type,
                                        const QString &val, bool update) {
    if (name == "FrameRate") {
        m_frameRate = val.toInt();
    }
}

void ArduinoTrigger::changeSimpleSetting(const QString &setting,
                                         const QString &value) {
    std::cout << setting.toStdString() << ", " << value.toStdString()
              << std::endl;
    if (setting == "FrameRate") {
        m_frameRate = value.toInt();
        static_cast<IntNode *>(m_triggerSettings->findNode("FrameRate"))
            ->setValue(m_frameRate);
    }
}
