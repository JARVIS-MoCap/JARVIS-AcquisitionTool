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
#include "cobs.hpp"

#include <QQueue>
#include <bitset>
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

size_t SerialPeer::msgToCobs(uint8_t *cobs_buffer, message *msg_buffer,
                             size_t size) {
    uint8_t tmp_buffer[SERIAL_PEER_MAX_BUFFER_SIZE +
                       SERIAL_PEER_DELIMITER_OVERHEAD +
                       SERIAL_PEER_COBS_OVERHEAD];
    int tmp_buffer_len;

    if (size >= SERIAL_PEER_MAX_BUFFER_SIZE) {
        return 0;
    }

    // First Byte is reserved for COBS overhead byte
    memcpy(static_cast<void *>(tmp_buffer + SERIAL_PEER_COBS_OVERHEAD),
           msg_buffer, size);

    tmp_buffer_len = cobs::encode(
        (uint8_t *)tmp_buffer, (const size_t)size + SERIAL_PEER_COBS_OVERHEAD);
    tmp_buffer[tmp_buffer_len++] = 0; // Message delimiter

    memcpy(static_cast<void *>(cobs_buffer), tmp_buffer, tmp_buffer_len);

    return tmp_buffer_len;
}

size_t SerialPeer::cobsToMsg(message_t *msg_buffer, uint8_t *cobs_buffer,
                             size_t size) {
    uint8_t tmp_buffer[SERIAL_PEER_MAX_BUFFER_SIZE +
                       SERIAL_PEER_DELIMITER_OVERHEAD +
                       SERIAL_PEER_COBS_OVERHEAD];
    int tmp_buffer_size;

    if (size >= SERIAL_PEER_MAX_BUFFER_SIZE + SERIAL_PEER_DELIMITER_OVERHEAD +
                    SERIAL_PEER_COBS_OVERHEAD) {
        return 0;
    }

    memcpy(static_cast<void *>(tmp_buffer), static_cast<void *>(cobs_buffer),
           size - SERIAL_PEER_DELIMITER_OVERHEAD);

    tmp_buffer_size = cobs::decode((uint8_t *)tmp_buffer,
                                   size - SERIAL_PEER_DELIMITER_OVERHEAD);

    memcpy(static_cast<void *>(msg_buffer),
           static_cast<void *>(tmp_buffer + SERIAL_PEER_COBS_OVERHEAD),
           tmp_buffer_size);
    return tmp_buffer_size;
}

uint8_t SerialPeer::handleCobsMessage(uint8_t *cobs_buffer, size_t size) {
    uint8_t msg_buffer[SERIAL_PEER_MAX_BUFFER_SIZE];
    int msg_buffer_size;

    msg_buffer_size =
        cobsToMsg(reinterpret_cast<message *>(&msg_buffer), cobs_buffer, size);

    if (msg_buffer_size != size - 2) {
        std::cout << "cobsToMsg Error" << std::endl;
    }
    return handleMessage(msg_buffer, msg_buffer_size);
}

uint8_t SerialPeer::handleMessage(uint8_t *msg_buffer, size_t size) {
    // Variables
    uint8_t error_flags = 0;
    message *type_message;
    type_message = reinterpret_cast<message *>(msg_buffer);

    uint8_t length = type_message->header.length;
    if (size < MIN_LENGTH_MESSAGE || size - LENGTH_MSG_HEADER != length) {
        error_flags |= SERIAL_PEER_ERROR_LENGTH;
    }
    uint8_t *payload = type_message->value;
    uint8_t crc = this->calculateCrc(payload, length);
    if (type_message->header.crc != crc) {
        error_flags |= SERIAL_PEER_ERROR_CRC;
    }

    switch (type_message->header.type) {
    case TYPE_ECHO:
        sendMessage(type_message, size);
        break;
    case TYPE_SETUP:
        // Not implemented
        error_flags |= SERIAL_PEER_ERROR_NOT_IMPLEMENTED;
        break;
    case TYPE_INPUTS:
        if (size != LENGTH_INPUT_STATE_MESSAGE) {
            error_flags |= SERIAL_PEER_ERROR_LENGTH;
            break;
        }
        handleInput(reinterpret_cast<input_state_message *>(msg_buffer));
        break;
    case TYPE_ACK:
        std::cout << "Got ack" << std::endl;
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
                                  length, size, MIN_LENGTH_MESSAGE);
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
    while (m_ack_queue->length() &&
           QDateTime::currentMSecsSinceEpoch() - m_ack_queue->last() >
               ACK_TIMEOUT_MS) {
        emit statusUpdated(Error, QString::fromStdString("Error: Missed ACK"));
        m_ack_queue->dequeue();
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

    std::bitset<8> inputs_state_bits(msg->inputs_state);
    std::cout << "Got inputs: " << inputs_state_bits << " - " << msg->pulse_id
              << " - " << msg->uptime_us << std::endl;
    sendAck();
}

void SerialPeer::sendSetup(SetupStruct *setup) {
    setup_message msg;

    msg.pulse_hz = setup->pulse_hz;
    msg.delay_us = htonl(setup->delay_us);
    msg.pulse_limit = htonl(setup->pulse_limit);

    msg.header.type = TYPE_SETUP;
    msg.header.length = LENGTH_SETUP_MESSAGE - LENGTH_MSG_HEADER;
    msg.header.crc = calculateCrc(reinterpret_cast<message *>(&msg)->value,
                                  msg.header.length);

    expectAck();
    sendMessage((message *)&msg, LENGTH_SETUP_MESSAGE);
}

void SerialPeer::sendMessage(message *buffer, size_t size) {
    uint8_t cobs_buffer[SERIAL_PEER_MAX_BUFFER_SIZE +
                        SERIAL_PEER_DELIMITER_OVERHEAD +
                        SERIAL_PEER_COBS_OVERHEAD];
    size_t cobs_buffer_len = msgToCobs(cobs_buffer, buffer, size);

    m_serialInterface->writeBuffer((const char *)(cobs_buffer),
                                   cobs_buffer_len);

    std::cout << "Serial send" << std::endl;
}

void SerialPeer::sendAck() {
    ack_message msg;

    msg.header.type = TYPE_ACK;
    msg.header.length = 0;
    msg.header.crc = 0;

    sendMessage(static_cast<message *>(&msg), LENGTH_ACK_MESSAGE);
}
