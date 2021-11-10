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

#ifndef SPINNAKER_GENAPI_EVENTADAPTERGEV_H
#define SPINNAKER_GENAPI_EVENTADAPTERGEV_H

#include "EventAdapter.h"

namespace Spinnaker
{
    namespace GenApi
    {
        // Declaration of GigE Vision Event message structures

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
         * @brief header of a GVCP request packet
         */
        typedef struct PACK_STRUCT GVCP_REQUEST_HEADER
        {
            uint8_t Magic;
            uint8_t Flags;
            uint16_t Command;
            uint16_t Length;
            uint16_t ReqId;
        } GVCP_REQUEST_HEADER;

        /**
         * @brief layout of a GVCP event item (common to all types)
         */
        typedef struct PACK_STRUCT GVCP_EVENT_ITEM_BASIC
        {
            uint16_t ReservedOrEventSize;
            uint16_t EventId;
        } GVCP_EVENT_ITEM_BASIC;

        /**
         * @brief layout of a GVCP event item (Extended ID flag not set)
         */
        typedef struct PACK_STRUCT GVCP_EVENT_ITEM
        {
            uint16_t ReservedOrEventSize;
            uint16_t EventId;
            uint16_t StreamChannelId;
            uint16_t BlockId;
            uint32_t TimestampHigh;
            uint32_t TimestampLow;
        } GVCP_EVENT_ITEM;

        /**
         * @brief Layout of a GVCP event request packet (Extended ID flag not set)
         */
        typedef struct PACK_STRUCT GVCP_EVENT_REQUEST
        {
            GVCP_REQUEST_HEADER Header;
            GVCP_EVENT_ITEM Items[1];
        } GVCP_EVENT_REQUEST;

        /**
         * @brief Layout of a GVCP event data request packet (Extended ID flag not set)
         */
        typedef struct PACK_STRUCT GVCP_EVENTDATA_REQUEST
        {
            GVCP_REQUEST_HEADER Header;
            GVCP_EVENT_ITEM Event;
            uint32_t Data[1];
        } GVCP_EVENTDATA_REQUEST;

        /**
         * @brief layout of a GVCP event item (Extended ID flag set)
         */
        typedef struct PACK_STRUCT GVCP_EVENT_ITEM_EXTENDED_ID
        {
            uint16_t ReservedOrEventSize;
            uint16_t EventId;
            uint16_t StreamChannelId;
            uint16_t BlockId;
            uint32_t BlockId64High;
            uint32_t BlockId64Low;
            uint32_t TimestampHigh;
            uint32_t TimestampLow;
        } GVCP_EVENT_ITEM_EXTENDED_ID;

        /**
         * @brief Layout of a GVCP event request packet (Extended ID flag set)
         */
        typedef struct PACK_STRUCT GVCP_EVENT_REQUEST_EXTENDED_ID
        {
            GVCP_REQUEST_HEADER Header;
            GVCP_EVENT_ITEM_EXTENDED_ID Items[1];
        } GVCP_EVENT_REQUEST_EXTENDED_ID;

        /**
         * @brief Layout of a GVCP event data request packet (Extended ID flag set)
         */
        typedef struct PACK_STRUCT GVCP_EVENTDATA_REQUEST_EXTENDED_ID
        {
            GVCP_REQUEST_HEADER Header;
            GVCP_EVENT_ITEM_EXTENDED_ID Event;
            uint32_t Data[1];
        } GVCP_EVENTDATA_REQUEST_EXTENDED_ID;

        const uint8_t COMMAND_MAGIC = 0x42;

        typedef enum GVCP_MESSAGE_TAGS
        {
            TAG_EVENT_CMD = 0xc0,
            TAG_EVENTDATA_CMD = 0xc2
        } GVCP_MESSAGE_TAGS;
        // restore the previous packing
#pragma pack(pop)

        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */

        /*@{*/

        /**
         *  @defgroup EventAdapterGEV_h EventAdapterGEV Class
         */

        /*@{*/

        /**
         * @brief Connects a GigE Event to a node map
         */
        class SPINNAKER_API CEventAdapterGEV : public CEventAdapter
        {
          public:
            /**
             * Constructor
             */
            CEventAdapterGEV(INodeMap* pNodeMap = NULL);

            /**
             * Destructor
             */
            virtual ~CEventAdapterGEV();

            virtual void DeliverMessage(const uint8_t msg[], uint32_t numBytes);

            /**
             * Delivers the Events listed in the Event packet
             */
            void DeliverEventMessage(const GVCP_EVENT_REQUEST* pEvent);

            /**
             * Delivers the Event + Data listed in the EventData packet
             */
            void DeliverEventMessage(const GVCP_EVENTDATA_REQUEST* pEventData);
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // SPINNAKER_GENAPI_EVENTADAPTERGEV_H
