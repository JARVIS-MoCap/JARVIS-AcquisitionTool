#ifndef _SERIAL_PEER_H // To make sure you don't declare the function more than
                       // once by including the header multiple times.
#define _SERIAL_PEER_H

#include "arduinoserialmessages.hpp"
#include "globals.hpp"
#include "serialinterface.hpp"
#include <QMutex>

#define htons(x) (((x) << 8 & 0xFF00) | ((x) >> 8 & 0x00FF))
#define ntohs(x) htons(x)

#define htonl(x)                                                               \
    (((x) << 24 & 0xFF000000UL) | ((x) << 8 & 0x00FF0000UL) |                  \
     ((x) >> 8 & 0x0000FF00UL) | ((x) >> 24 & 0x000000FFUL))
#define ntohl(x) htonl(x)

#define SERIAL_PEER_MAX_BUFFER_SIZE (0xFF)
#define SERIAL_PEER_COBS_OVERHEAD (1)
#define SERIAL_PEER_DELIMITER_OVERHEAD (1)
struct setup_struct_t {
    uint32_t delay_us;    // delay until first pulse
    uint32_t pulse_limit; // 0 -> unlimited pulses
    uint8_t pulse_hz;     // Frequency in herz 1-255; 0 -> OFF
    uint8_t flags;        // booleans see setup_flags
};
typedef struct setup_struct_t SetupStruct;
#define LENGTH_SETUP_STRUCT sizeof(SetupStruct)

enum SERIAL_PEER_ERROR_CODE {
    SERIAL_PEER_ERROR_LENGTH = 1 << 0,
    SERIAL_PEER_ERROR_CRC = 1 << 1,
    SERIAL_PEER_ERROR_NOT_IMPLEMENTED = 1 << 2,
    SERIAL_PEER_ERROR_UNKNOWN_PACKET = 1 << 3,
    SERIAL_PEER_ERROR_ACK_TIMEOUT = 1 << 4,
    SERIAL_PEER_ERROR_MCU = 1 << 5,
};
class SerialPeer : public QObject {
    Q_OBJECT
  public:
    typedef void (*PacketSenderFunction)(const uint8_t *buffer, size_t size);
    typedef void (*PacketSenderFunctionClass)(void *them, const uint8_t *buffer,
                                              size_t size);

    void setPacketSender(PacketSenderFunction sendPacketFunction) {
        _sendPacketFunction = sendPacketFunction;
        _sendClassPacketFunction = nullptr;
        _callback_class = nullptr;
    }
    void setPacketSender(void *them,
                         PacketSenderFunctionClass sendPacketFunction) {
        _sendPacketFunction = nullptr;
        _sendClassPacketFunction = sendPacketFunction;
        _callback_class = them;
    }

    SerialPeer(SerialInterface *serialInterface);
    ~SerialPeer();
    uint8_t handleCobsMessage(uint8_t *cobs_buffer, size_t size);
    uint8_t handleMessage(uint8_t *msg_buffer, size_t size);
    void sendSetup(SetupStruct *setup);
    void handleInput(input_state_message *msg);
    void sendMessage(message *buffer, size_t size);
    void sendAck();
    void expectAck();
    bool checkAck();

  signals:
    void statusUpdated(statusType status, const QString &statusMessage);

  private:
    uint8_t calculateCrc(uint8_t *payload, size_t len);
    size_t msgToCobs(uint8_t *cobs_buffer, message_t *msg_buffer, size_t size);
    size_t cobsToMsg(message_t *msg_buffer, uint8_t *cobs_buffer, size_t size);

    PacketSenderFunction _sendPacketFunction = nullptr;
    PacketSenderFunctionClass _sendClassPacketFunction = nullptr;
    void *_callback_class = nullptr;

    // Jarvis stuff
    QQueue<qint64> *m_ack_queue;
    QMutex m_ack_queue_mutex;
    SerialInterface *m_serialInterface;
};

#endif
