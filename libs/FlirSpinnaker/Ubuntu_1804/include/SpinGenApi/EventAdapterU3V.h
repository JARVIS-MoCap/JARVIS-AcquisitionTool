//=============================================================================
// Copyright (c) 2001-2019 FLIR Systems, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

#ifndef SPINNAKER_GENAPI_EVENTADAPTERU3V_H
#define SPINNAKER_GENAPI_EVENTADAPTERU3V_H

#include "EventAdapter.h"

namespace Spinnaker
{
    namespace GenApi
    {
        // Declaration of USB3 Vision / GenCP Event message structures

        // some useful macros
#if defined(_MSC_VER) || defined(SWIG)
#define PACK_STRUCT
#elif defined(__GNUC__)
        // While gcc-4 understands #pragma pack,
        // gcc-3 does not
#define PACK_STRUCT __attribute__((packed))
#else
#error Unknown platform
#endif

        // make sure everything is properly packed
#pragma pack(push, 1)

        /**
         * @brief U3V/GenCP command header
         */
        typedef struct PACK_STRUCT U3V_COMMAND_HEADER
        {
            uint32_t Prefix;
            // CCD
            uint16_t Flags;
            uint16_t CommandId;
            uint16_t Length;
            uint16_t ReqId;
        } U3V_COMMAND_HEADER;

        /**
         * @brief U3V/GenCP EVENT_CMD specific command data
         */
        typedef struct PACK_STRUCT U3V_EVENT_DATA
        {
            // SCD
            uint16_t Reserved;
            uint16_t EventId;
            uint64_t Timestamp;
            // Deliberately not mentioning the (optional?) variable sized data
        } U3V_EVENT_DATA;

        /**
         * @brief Entire event data message (without the variable-sized data field)
         */
        typedef struct PACK_STRUCT U3V_EVENT_MESSAGE
        {
            U3V_COMMAND_HEADER CommandHeader;
            U3V_EVENT_DATA EventData;
        } U3V_EVENT_MESSAGE;

        const uint32_t U3V_EVENT_PREFIX = 0x45563355;
        const uint16_t GENCP_EVENT_CMD_ID = 0x0C00;
        const size_t GENCP_COMMAND_HEADER_SIZE = sizeof(U3V_COMMAND_HEADER);
        const size_t GENCP_EVENT_BASIC_SIZE = sizeof(U3V_EVENT_MESSAGE);

        // restore the previous packing
#pragma pack(pop)

        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup EventAdapterU3V_h EventAdapterU3V Class
         */
        /*@{*/

        /**
         * @brief Connects a U3V Event to a node map
         */
        class SPINNAKER_API CEventAdapterU3V : public CEventAdapter
        {
          public:
            /**
             * Constructor
             */
            CEventAdapterU3V(INodeMap* pNodeMap = NULL);

            /**
             * Destructor
             */
            virtual ~CEventAdapterU3V();

            virtual void DeliverMessage(const uint8_t msg[], uint32_t numBytes);

            /**
             * Delivers the Event + Data listed in the packet
             */
            void DeliverEventMessage(const U3V_EVENT_MESSAGE* pEventMessage);
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // SPINNAKER_GENAPI_EVENTADAPTERU3V_H
