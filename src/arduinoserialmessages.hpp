#ifndef _SERIAL_MESSAGES_H
#define _SERIAL_MESSAGES_H

#include <cstddef>
#include <cstdint>

#pragma pack(                                                                  \
    push, 1) // Ensure that there is no byte alignment in protocol structures

enum message_type {
    TYPE_ECHO, // for debugging
    TYPE_SETUP,
    TYPE_INPUTS,
    TYPE_ACK,
    TYPE_TXT,
    TYPE_ERROR,
};

enum setup_flags {
    RESET_COUNTER = 1 << 0,
    SYNC_RISING_EDGE = 1 << 1,
};

// +-------+-------+-------+-------+
// |  type | length| crc   |   X   |
// +-------+-------+-------+-------+
struct header_t {
    uint8_t type;
    uint8_t length;
    uint8_t crc;
};
typedef struct header_t msg_header;
#define LENGTH_MSG_HEADER sizeof(msg_header)

// +-------+-------+-------+-------+
// |         header        | val_0 |
// +-------+-------+-------+-------+
// |              ...              |
// +-------+-------+-------+-------+
struct message_t {
    msg_header header;
    uint8_t value[];
};
#define MIN_LENGTH_MESSAGE LENGTH_MSG_HEADER
typedef struct message_t message;
#define LENGTH_ACK_MESSAGE MIN_LENGTH_MESSAGE
typedef struct message_t ack_message;
#define MIN_LENGTH_ERROR_MESSAGE MIN_LENGTH_MESSAGE
typedef struct message_t error_message;
#define MIN_LENGTH_TXT_MESSAGE MIN_LENGTH_MESSAGE
typedef struct message_t txt_message;

// +-------+-------+-------+-------+
// |         header        | is_se |
// +-------+-------+-------+-------+
// |           uptime_us           |
// +-------+-------+-------+-------+
// |           pulse_id            |
// +-------+-------+-------+-------+
struct input_state_message_t {
    msg_header header;
    uint8_t inputs_state;
    uint32_t uptime_us;
    uint32_t pulse_id;
};
typedef struct input_state_message_t input_state_message;
#define LENGTH_INPUT_STATE_MESSAGE sizeof(input_state_message)

// +-------+-------+-------+-------+
// |         header        | pe_hz |
// +-------+-------+-------+-------+
// |          pulse_limit          |
// +-------+-------+-------+-------+
// |           delay_us            |
// +-------+-------+-------+-------+
struct setup_message_t {
    msg_header header;
    uint8_t pulse_hz;     // Frequency in herz 1-255; 0 -> OFF
    uint32_t pulse_limit; // 0 -> unlimited pulses
    uint32_t delay_us;    // delay until first pulse
    uint8_t flags;        // booleans see setup_flags
};
typedef struct setup_message_t setup_message;
#define LENGTH_SETUP_MESSAGE sizeof(setup_message)

#pragma pack(pop)

#endif