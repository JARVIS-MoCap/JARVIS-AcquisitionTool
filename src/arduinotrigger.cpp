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
#include "cobs.hpp"

#include <QApplication>
#include <QTimer>

ArduinoTrigger::ArduinoTrigger(const QString &deviceName)
    : TriggerInterface{arduinoTrigger} {
    createSettings();
    serialInterface = new SerialInterface(deviceName);

    serialPeer = new SerialPeer();
    serialPeer->setPacketSender(this, [](void *them, const uint8_t *buffer,
                                         size_t size) {
        ArduinoTrigger *this_class = (ArduinoTrigger *)them;

        const char *cobs_buffer = (const char *)malloc(size);
        unsigned int cobs_buffer_len = 0;
        memcpy((void *)cobs_buffer, buffer, size);
        cobs_buffer_len =
            cobs::encode((uint8_t *)cobs_buffer, (const size_t)size);
        this_class->serialInterface->writeBuffer(cobs_buffer, cobs_buffer_len);
        free((void *)cobs_buffer);
    });

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

void ArduinoTrigger::enable() {
    serialInterface->write(m_frameRate);

    SetupStruct setup;

    setup.delay_us = 0;
    setup.pulse_hz = m_frameRate;
    setup.pulse_limit = 0;
    serialPeer->getSetup(&setup);
}

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
