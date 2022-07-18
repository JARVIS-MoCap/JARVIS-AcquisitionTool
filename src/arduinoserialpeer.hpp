#ifndef _SERIAL_PEER_H // To make sure you don't declare the function more than
                       // once by including the header multiple times.
#define _SERIAL_PEER_H

#include "arduinoserialmessages.hpp"

#define htons(x) (((x) << 8 & 0xFF00) | ((x) >> 8 & 0x00FF))
#define ntohs(x) htons(x)

#define htonl(x)                                                               \
    (((x) << 24 & 0xFF000000UL) | ((x) << 8 & 0x00FF0000UL) |                  \
     ((x) >> 8 & 0x0000FF00UL) | ((x) >> 24 & 0x000000FFUL))
#define ntohl(x) htonl(x)

#define SERIAL_PEER_MAX_BUFFER_SIZE (0xFF - MIN_LENGTH_ERROR_MESSAGE)
struct setup_struct_t {
    uint32_t delay_us;    // delay until first pulse
    uint32_t pulse_limit; // 0 -> unlimited pulses
    uint8_t pulse_hz;     // Frequency in herz 1-255; 0 -> OFF
};
typedef struct setup_struct_t SetupStruct;
#define LENGTH_SETUP_STRUCT sizeof(SetupStruct)

enum SERIAL_PEER_ERROR_CODE {
    SERIAL_PEER_ERROR_LENGTH = 1 << 0,
    SERIAL_PEER_ERROR_CRC = 1 << 1,
    SERIAL_PEER_ERROR_NOT_IMPLEMENTED = 1 << 2,
    SERIAL_PEER_ERROR_UNKNOWN_PACKET = 1 << 3,

};
class SerialPeer {

  public:
    typedef void (*PacketSenderFunction)(const uint8_t *buffer, size_t size);

    void setPacketSender(PacketSenderFunction sendPacketFunction) {
        _sendPacketFunction = sendPacketFunction;
    }

    SerialPeer();
    uint8_t handleMessage(uint8_t *msg, size_t len);
    uint8_t getSetup(SetupStruct *setup);
    void handleSetup(setup_message *msg, size_t len);

    void sendMessage(uint8_t *msg, size_t len);
    void sendInputs(uint32_t uptime_us, uint32_t pulse_id,
                    uint8_t inputs_state);
    void sendError(uint8_t *msg, uint8_t len);
    void sendTxt(uint8_t *msg, uint8_t len);
    void sendAck();

  private:
    void _sendTypedMessage(uint8_t type, uint8_t *msg, uint8_t len);
    uint8_t calculateCrc(uint8_t *payload, size_t len);
    uint8_t _buffer[SERIAL_PEER_MAX_BUFFER_SIZE];
    SetupStruct _setup;
    uint8_t _setup_changed = false;
    PacketSenderFunction _sendPacketFunction = nullptr;
};

#endif
