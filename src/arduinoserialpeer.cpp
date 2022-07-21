/*******************************************************************************
 * File:        main.cpp
 * Created:     18. July 2022
 * Author:      Louis Frank
 * Contact:     singulosta@gmail.com
 * Copyright:   2021 Louis Frank
 * License:     LGPL v3.0
 ******************************************************************************/

#include "arduinoserialpeer.hpp"
#include "arduinoserialmessages.hpp"

#include <QQueue>
#include <cstdio>
#include <cstring>
#include <iostream>

#define ACK_TIMEOUT_MS 200

SerialPeer::SerialPeer(SerialInterface *serialInterface)
    : QObject(), m_serialInterface{serialInterface} {
    m_ack_queue = new QQueue<qint64>();
}

SerialPeer::~SerialPeer() { delete m_ack_queue; }

uint8_t SerialPeer::calculateCrc(uint8_t *buffer, size_t len) {
    uint8_t crc = 0;
    for (uint8_t i = 0; i < len; i++) {
        crc += buffer[i];
    }
    return crc;
}

uint8_t SerialPeer::handleMessage(uint8_t *msg, size_t len) {
    // Variables
    uint8_t error_flags = 0;
    message *type_message;
    type_message = (message *)msg;

    uint8_t length = type_message->header.length;
    if (len < MIN_LENGTH_MESSAGE || len - LENGTH_MSG_HEADER != length) {
        error_flags |= SERIAL_PEER_ERROR_LENGTH;
    }
    uint8_t *payload = type_message->value;
    uint8_t crc = this->calculateCrc(payload, length);
    if (type_message->header.crc != crc) {
        error_flags |= SERIAL_PEER_ERROR_CRC;
    }

    switch (type_message->header.type) {
    case TYPE_ECHO:
        this->_buffer[0] = TYPE_ECHO;
        memcpy(this->_buffer, type_message, len);
        sendMessage((uint8_t *)type_message, len);
        break;
    case TYPE_SETUP:
        // Not implemented
        error_flags |= SERIAL_PEER_ERROR_NOT_IMPLEMENTED;
        break;
    case TYPE_INPUTS:
        if (len != LENGTH_INPUT_STATE_MESSAGE) {
            error_flags |= SERIAL_PEER_ERROR_LENGTH;
            break;
        }
        handleInput((input_state_message *)msg);
        break;
    case TYPE_ACK:
        // Not implemented
        if (checkAck()) {
            error_flags |= SERIAL_PEER_ERROR_ACK_TIMEOUT;
            break;
        }
        emit statusUpdated(Ready, QString::fromStdString("Got ACK"));
        break;
    case TYPE_ERROR:
        // Not implemented
        checkAck();
        error_flags |= SERIAL_PEER_ERROR_MCU;
        emit statusUpdated(
            Error, QString::fromStdString("Trigger Error: ") +
                       QString::fromUtf8((const char *)type_message->value,
                                         (int)length));
        break;
    default:
        // unknown packet type
        error_flags |= SERIAL_PEER_ERROR_UNKNOWN_PACKET;
        break;
    }
    if (error_flags) {
        uint8_t error_str[SERIAL_PEER_MAX_BUFFER_SIZE];
        uint16_t error_len = 0;

        if (error_flags & SERIAL_PEER_ERROR_CRC) {
            error_len +=
                snprintf((char *)error_str + error_len,
                         SERIAL_PEER_MAX_BUFFER_SIZE - error_len,
                         " # CRC ERROR / header.crc: %d / calc crc: %d",
                         type_message->header.crc, crc);
        }
        if (error_flags & SERIAL_PEER_ERROR_LENGTH) {
            error_len += snprintf((char *)error_str + error_len,
                                  SERIAL_PEER_MAX_BUFFER_SIZE - error_len,
                                  " # LENGHT ERROR / header.length: %d / len: "
                                  "%lu / MIN_LENGTH_MESSAGE: %lu",
                                  length, len, MIN_LENGTH_MESSAGE);
        }
        if (error_flags & SERIAL_PEER_ERROR_NOT_IMPLEMENTED) {
            error_len += snprintf((char *)error_str + error_len,
                                  SERIAL_PEER_MAX_BUFFER_SIZE - error_len,
                                  " # NOT IMPLEMENTED ERROR / header.type %d",
                                  type_message->header.type);
        }
        if (error_flags & SERIAL_PEER_ERROR_UNKNOWN_PACKET) {
            error_len += snprintf((char *)error_str + error_len,
                                  SERIAL_PEER_MAX_BUFFER_SIZE - error_len,
                                  " # UNKNOWN PACKET ERROR / header.type: %d",
                                  type_message->header.type);
        }
        if (error_flags & SERIAL_PEER_ERROR_ACK_TIMEOUT) {
            error_len += snprintf((char *)error_str + error_len,
                                  SERIAL_PEER_MAX_BUFFER_SIZE - error_len,
                                  " # ACK TIMEOUT ERROR");
        }
        if (error_flags & SERIAL_PEER_ERROR_MCU) {
            error_len += snprintf((char *)error_str + error_len,
                                  SERIAL_PEER_MAX_BUFFER_SIZE - error_len,
                                  " # ERROR MCU ERROR");
        }

        std::cout << "Error: " << ((char *)error_str) << std::endl;
        emit statusUpdated(Error, QString::fromStdString(((char *)error_str)));
    }

    return error_flags;
}

void SerialPeer::expectAck() {
    m_ack_queue_mutex.lock();
    forever {
        if (m_ack_queue->length() &&
            QDateTime::currentMSecsSinceEpoch() - m_ack_queue->last() >
                ACK_TIMEOUT_MS) {
            emit statusUpdated(Error,
                               QString::fromStdString("Error: Missed ACK"));
            m_ack_queue->dequeue();
        } else {
            break;
        }
    }
    m_ack_queue->enqueue(QDateTime::currentMSecsSinceEpoch());
    m_ack_queue_mutex.unlock();
}
bool SerialPeer::checkAck() {
    qint64 ack_timestamp_ms = 0;
    qint64 now_ms = 0;
    qint64 diff_ms = 0;

    m_ack_queue_mutex.lock();
    if (!m_ack_queue->empty()) {
        ack_timestamp_ms = m_ack_queue->dequeue();
    }
    m_ack_queue_mutex.unlock();

    now_ms = QDateTime::currentMSecsSinceEpoch();
    diff_ms = now_ms - ack_timestamp_ms;
    return (diff_ms > ACK_TIMEOUT_MS);
}

void SerialPeer::handleInput(input_state_message *msg) {
    std::cout << "Got inputs: " << msg->inputs_state << " - " << msg->pulse_id
              << " - " << msg->uptime_us << std::endl;
}

void SerialPeer::sendSetup(SetupStruct *setup) {

    setup_message *msg;
    msg = (setup_message *)this->_buffer;

    msg->pulse_hz = setup->pulse_hz;
    msg->delay_us = htonl(setup->delay_us);
    msg->pulse_limit = htonl(setup->pulse_limit);

    msg->header.type = TYPE_SETUP;
    msg->header.length = LENGTH_SETUP_MESSAGE - LENGTH_MSG_HEADER;
    msg->header.crc = calculateCrc(((message *)msg)->value, msg->header.length);

    expectAck();
    sendMessage((uint8_t *)msg, LENGTH_SETUP_MESSAGE);
}

void SerialPeer::sendMessage(uint8_t *msg, size_t len) {
    if (_callback_class && _sendClassPacketFunction) {
        this->_sendClassPacketFunction(_callback_class, msg, len);
        return;
    }
    if (_sendPacketFunction) {
        this->_sendPacketFunction(msg, len);
        return;
    }
    std::cout << "Error: sendMessage" << std::endl;
}

void SerialPeer::sendAck() {
    ack_message *msg;
    msg = (ack_message *)this->_buffer;

    msg->header.type = TYPE_ACK;
    msg->header.length = 0;
    msg->header.crc = 0;

    sendMessage((uint8_t *)msg, LENGTH_ACK_MESSAGE);
}

void SerialPeer::sendError(uint8_t *value, uint8_t len) {
    _sendTypedMessage(TYPE_ERROR, value, len);
}

void SerialPeer::sendTxt(uint8_t *value, uint8_t len) {
    _sendTypedMessage(TYPE_TXT, value, len);
}

void SerialPeer::_sendTypedMessage(uint8_t type, uint8_t *value, uint8_t len) {
    message *msg;
    msg = (message *)this->_buffer;

    memcpy(msg->value, value, len);

    msg->header.type = type;
    msg->header.length = len;
    msg->header.crc = calculateCrc(msg->value, msg->header.length);

    sendMessage((uint8_t *)msg, MIN_LENGTH_TXT_MESSAGE + len);
}

void SerialPeer::sendInputs(uint32_t uptime_us, uint32_t pulse_id,
                            uint8_t inputs_state) {
    input_state_message *msg;
    msg = (input_state_message *)this->_buffer;

    msg->uptime_us = uptime_us;
    msg->pulse_id = pulse_id;
    msg->inputs_state = inputs_state;

    msg->header.type = TYPE_INPUTS;
    msg->header.length = LENGTH_INPUT_STATE_MESSAGE - LENGTH_MSG_HEADER;
    msg->header.crc = calculateCrc(((message *)msg)->value, msg->header.length);

    sendMessage((uint8_t *)msg, LENGTH_INPUT_STATE_MESSAGE);
}
