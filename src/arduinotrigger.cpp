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
#include <limits.h>

#define GET_COBS_PACKET_TIMEOUT 1000
#define RECEIVEWORKER_TERMINATE_TIMEOUT 2000
#define GET_COBS_PACKET_BUFFER_SIZE 255

#define TRIGGER_DEBUG false
#define TRIGGER_DEBUG_LOOKATME_BUFFER_SIZE 15

ReceiveWorker::ReceiveWorker(SerialPeer *serialPeer,
                             SerialInterface *serialInterface)
    : QThread{}, m_serialPeer{serialPeer}, m_serialInterface{serialInterface} {}

ReceiveWorker::~ReceiveWorker() {}

void ReceiveWorker::run() {
    while (!isInterruptionRequested()) {
        char receive_buffer[GET_COBS_PACKET_BUFFER_SIZE];
        unsigned int receive_buffer_len = 0;
        receive_buffer_len = m_serialInterface->get_cobs_packet(
            receive_buffer, GET_COBS_PACKET_BUFFER_SIZE,
            GET_COBS_PACKET_TIMEOUT);
        if (receive_buffer_len < LENGTH_MSG_HEADER + 1) {
            continue;
        }

        cobs::decode((uint8_t *)receive_buffer, receive_buffer_len);

        m_serialPeer->handleMessage((uint8_t *)receive_buffer + 1,
                                    receive_buffer_len - 1);
    }
    std::cout << "Receive Worker ended" << std::endl;
}

ArduinoTrigger::ArduinoTrigger(const QString &deviceName)
    : TriggerInterface{arduinoTrigger} {
    createSettings();
    serialInterface = new SerialInterface(deviceName);

    serialPeer = new SerialPeer(serialInterface);
    connect(serialPeer, &SerialPeer::statusUpdated, this,
            &ArduinoTrigger::statusUpdated);
    serialPeer->setPacketSender(this, [](void *them, const uint8_t *buffer,
                                         size_t size) {
        ArduinoTrigger *this_class = static_cast<ArduinoTrigger *>(them);

#if TRIGGER_DEBUG
        uint8_t lookatme_buffer[TRIGGER_DEBUG_LOOKATME_BUFFER_SIZE];
        memset((void *)lookatme_buffer, 'N',
               TRIGGER_DEBUG_LOOKATME_BUFFER_SIZE);
        memcpy((void *)lookatme_buffer, buffer,
               std::min((unsigned long)TRIGGER_DEBUG_LOOKATME_BUFFER_SIZE,
                        (unsigned long)size));
#endif

        char *cobs_buffer = (char *)malloc(size + 2);
        unsigned int cobs_buffer_len = 0;
        memcpy((void *)(cobs_buffer + 1), buffer,
               size); // First Byte is reserved for COBS overhead byte
        cobs_buffer_len =
            cobs::encode((uint8_t *)cobs_buffer, (const size_t)size + 1);
        cobs_buffer[cobs_buffer_len++] = 0; // Message delimiter

#if TRIGGER_DEBUG
        uint8_t lookatme_cobs_buffer[TRIGGER_DEBUG_LOOKATME_BUFFER_SIZE];
        memset((void *)lookatme_cobs_buffer, 'N',
               TRIGGER_DEBUG_LOOKATME_BUFFER_SIZE);
        memcpy((void *)lookatme_cobs_buffer, cobs_buffer,
               std::min((unsigned long)TRIGGER_DEBUG_LOOKATME_BUFFER_SIZE,
                        (unsigned long)cobs_buffer_len));

        setup_message *setup = (setup_message *)lookatme_buffer;
#endif

        this_class->serialInterface->writeBuffer(cobs_buffer, cobs_buffer_len);
        free((void *)cobs_buffer);

        std::cout << "Serial send" << std::endl;
    });

    receiveWorker = new ReceiveWorker(serialPeer, serialInterface);
    receiveWorker->start();

    disable();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(intitialStatusSlot()));

    timer->setSingleShot(true);
    timer->start(100);
}

ArduinoTrigger::~ArduinoTrigger() {

    // TODO: call super class destructor

    receiveWorker->requestInterruption();
    if (!receiveWorker->wait(RECEIVEWORKER_TERMINATE_TIMEOUT)) {
        receiveWorker->terminate();
    }

    delete serialInterface;
    delete serialPeer;
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
    frameRateNode->setMinValue(std::numeric_limits<uint8_t>::min());
    frameRateNode->setMaxValue(std::numeric_limits<uint8_t>::max());

    IntNode *frameLimitNode = new IntNode(arduinoTriggerNode, "FrameLimit");
    frameLimitNode->setDescription(
        "Maximum number of triggers to be generated. "
        "Set the value to 0 for unlimited frames.");
    frameLimitNode->setValue(0);
    frameLimitNode->setMinValue(std::numeric_limits<uint32_t>::min());
    frameLimitNode->setMaxValue(std::numeric_limits<uint32_t>::max());

    IntNode *cmdDelayNode = new IntNode(arduinoTriggerNode, "CmdDelay");
    cmdDelayNode->setDescription(
        "Duration in us until the trigger updates its config.");
    cmdDelayNode->setValue(0);
    cmdDelayNode->setMinValue(std::numeric_limits<uint32_t>::min());
    cmdDelayNode->setMaxValue(std::numeric_limits<uint32_t>::max());

    m_triggerSettingsRootNode->addChild(arduinoTriggerNode);
    arduinoTriggerNode->addChild(frameRateNode);
    arduinoTriggerNode->addChild(frameLimitNode);
    arduinoTriggerNode->addChild(cmdDelayNode);

    m_triggerSettings =
        new SettingsObject(this, "Trigger Settings", m_triggerSettingsRootNode);

    connect(m_triggerSettings, &SettingsObject::settingChanged, this,
            &ArduinoTrigger::settingChangedSlot);
}

void ArduinoTrigger::enable() {
    SetupStruct setup;
    setup.delay_us = m_cmdDelay;
    setup.pulse_hz = m_frameRate;
    setup.pulse_limit = m_frameLimit;
    serialPeer->sendSetup(&setup);
}

void ArduinoTrigger::disable() {
    SetupStruct setup;
    setup.delay_us = 0;
    setup.pulse_hz = 0;
    setup.pulse_limit = 0;
    serialPeer->sendSetup(&setup);
}

void ArduinoTrigger::settingChangedSlot(const QString &name,
                                        QList<QString> subMenus,
                                        SettingsNode::nodeType type,
                                        const QString &val, bool update) {
    if (name == "FrameRate") {
        m_frameRate = val.toInt();
    }
    if (name == "FrameLimit") {
        m_frameLimit = val.toInt();
    }
    if (name == "CmdDelay") {
        m_cmdDelay = val.toInt();
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
    if (setting == "FrameLimit") {
        m_frameLimit = value.toDouble();
        static_cast<IntNode *>(m_triggerSettings->findNode("FrameLimit"))
            ->setValue(m_frameLimit);
    }
    if (setting == "CmdDelay") {
        m_cmdDelay = value.toDouble();
        static_cast<IntNode *>(m_triggerSettings->findNode("CmdDelay"))
            ->setValue(m_cmdDelay);
    }
}
