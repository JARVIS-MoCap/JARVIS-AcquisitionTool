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
#include <QThread>
#include <QTimer>
#include <limits.h>

#define GET_COBS_PACKET_TIMEOUT 1000
#define RECEIVEWORKER_TERMINATE_TIMEOUT 2000
#define GET_COBS_PACKET_BUFFER_SIZE 255
#define CHECK_CONNECTED_DELAY_MSEC 100
#define INIT_SETUP_DELAY_MSEC 1500

ArduinoTriggerWorker::ArduinoTriggerWorker(const QString &deviceName)
    : QObject{} {
    serialInterface = new SerialInterface(deviceName, this);
    serialPeer = new SerialPeer(serialInterface);

    connect(serialInterface, &SerialInterface::serialReadReadySignal, this,
            &ArduinoTriggerWorker::recvSlot);

    connect(serialPeer, &SerialPeer::statusUpdated, this,
            &ArduinoTriggerWorker::statusUpdated);

    connect(serialPeer, &SerialPeer::provideTriggerdata, this,
            &ArduinoTriggerWorker::provideTriggerdata);

    QTimer *initSetupTimer = new QTimer(this);
    initSetupTimer->setSingleShot(true);
    connect(initSetupTimer, &QTimer::timeout, [=]() {
        emit statusUpdated(Ready, "Connected");
        sendSetupSlot(0, 0, 0);
        initSetupTimer->deleteLater();
    });

    emit statusUpdated(Connecting, "Connecting...");
    QTimer *checkConnectionTimer = new QTimer(this);
    checkConnectionTimer->setSingleShot(true);
    connect(checkConnectionTimer, &QTimer::timeout, [=]() {
        if (serialInterface->isConnected()) {
            initSetupTimer->start(
                INIT_SETUP_DELAY_MSEC); // TODO Use thread started Signal
        } else {
            emit statusUpdated(Error, "Connection Failed!");
        }
        checkConnectionTimer->deleteLater();
    });
    checkConnectionTimer->start(
        CHECK_CONNECTED_DELAY_MSEC); // TODO Use QSerial connected Signal
}

ArduinoTriggerWorker::~ArduinoTriggerWorker() {
    delete serialInterface;
    delete serialPeer;
}

void ArduinoTriggerWorker::sendSetupSlot(int cmdDelay, int frameRate,
                                         int frameLimit, bool syncRisingEdge,
                                         bool resetCounter) {
    SetupStruct setup;
    setup.delay_us = cmdDelay;
    setup.pulse_hz = frameRate;
    setup.pulse_limit = frameLimit;
    setup.flags = RESET_COUNTER ? resetCounter : 0;
    setup.flags |= SYNC_RISING_EDGE ? syncRisingEdge : 0;

    serialPeer->sendSetup(&setup);
}

void ArduinoTriggerWorker::recvSlot() {
    uint8_t receive_buffer[GET_COBS_PACKET_BUFFER_SIZE];
    unsigned int receive_buffer_len = 0;
    do {
        receive_buffer_len = serialInterface->get_cobs_packet(
            reinterpret_cast<char *>(receive_buffer),
            GET_COBS_PACKET_BUFFER_SIZE, GET_COBS_PACKET_TIMEOUT);

        if (receive_buffer_len < MIN_LENGTH_MESSAGE) {
            return;
        }

        serialPeer->handleCobsMessage(receive_buffer, receive_buffer_len);
    } while (receive_buffer_len >= MIN_LENGTH_MESSAGE);
}

ArduinoTrigger::ArduinoTrigger(const QString &deviceName)
    : TriggerInterface{arduinoTrigger} {
    createSettings();

    workerClass = new ArduinoTriggerWorker(deviceName);
    workerClass->moveToThread(&workerThread);
    workerThread.start();

    connect(workerClass, &ArduinoTriggerWorker::statusUpdated, this,
            &ArduinoTrigger::statusUpdated);

    connect(workerClass, &ArduinoTriggerWorker::provideTriggerdata, this,
            &ArduinoTrigger::provideTriggerdata);

    connect(this, &ArduinoTrigger::sendSetupSignal, workerClass,
            &ArduinoTriggerWorker::sendSetupSlot);
}

void ArduinoTrigger::enable() {
    emit sendSetupSignal(m_cmdDelay, m_frameRate, m_frameLimit,
                         m_syncRisingEdge, true);
}

void ArduinoTrigger::pause(bool state) {
    if (state) {
        // Pause
        emit sendSetupSignal(0, 0, 0, m_syncRisingEdge, false);
    } else {
        // Continue
        emit sendSetupSignal(m_cmdDelay, m_frameRate, m_frameLimit,
                             m_syncRisingEdge, false);
    }
}

void ArduinoTrigger::disable() {
    emit sendSetupSignal(0, 0, 0, m_syncRisingEdge, false);
}

ArduinoTrigger::~ArduinoTrigger() {

    qDebug() << "Trying to stop TriggerCOM";
    workerThread.requestInterruption();
    workerThread.quit();
    workerThread.wait();

    // TODO: call super class destructor
    delete workerClass;
    delete m_triggerSettings;
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

    BoolNode *syncRisingEdgeNode =
        new BoolNode(arduinoTriggerNode, "SyncRisingEdge");
    syncRisingEdgeNode->setDescription(
        "Selects wether to sync to the rising or the falling edge.");
    syncRisingEdgeNode->setValue(false);

    m_triggerSettingsRootNode->addChild(arduinoTriggerNode);
    arduinoTriggerNode->addChild(frameRateNode);
    arduinoTriggerNode->addChild(frameLimitNode);
    arduinoTriggerNode->addChild(cmdDelayNode);
    arduinoTriggerNode->addChild(syncRisingEdgeNode);

    m_triggerSettings =
        new SettingsObject(this, "Trigger Settings", m_triggerSettingsRootNode);

    connect(m_triggerSettings, &SettingsObject::settingChanged, this,
            &ArduinoTrigger::settingChangedSlot);
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
    if (name == "SyncRisingEdge") {
        m_syncRisingEdge = val.toInt() ? true : false;
    }
}

void ArduinoTrigger::changeSimpleSetting(const QString &setting,
                                         const QString &value) {
    qDebug() << setting << ", " << value;
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
    if (setting == "SyncRisingEdge") {
        m_syncRisingEdge = value.toInt() ? true : false;
        static_cast<BoolNode *>(m_triggerSettings->findNode("SyncRisingEdge"))
            ->setValue(m_syncRisingEdge);
    }
}
