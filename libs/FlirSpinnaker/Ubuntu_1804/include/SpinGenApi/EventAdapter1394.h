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

#ifndef SPINNAKER_GENAPI_EVENTADAPTER1394_H
#define SPINNAKER_GENAPI_EVENTADAPTER1394_H

#if _MSC_VER > 1000
#pragma once
#endif

#include "EventAdapter.h"

namespace Spinnaker
{
    namespace GenApi
    {
        // the opaque event data on IEEE 1394
        struct EventData1394;

        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup EventAdapter1394_h EventAdapter1394 Class
         */
        /*@{*/

        /**
         * @brief Distribute the events to the node map
         */
        class SPINNAKER_API CEventAdapter1394 : public CEventAdapter
        {
          public:
            /**
             * constructor
             */
            explicit CEventAdapter1394(INodeMap* pNodeMap = NULL);

            virtual ~CEventAdapter1394();

          public:
            virtual void DeliverMessage(const uint8_t msg[], uint32_t numBytes);

            /**
             * distributes events to node map
             */
            void DeliverEventMessage(EventData1394& Event, uint32_t numBytes);

          private:
            /**
             * not implemented: copy constructor
             */
            CEventAdapter1394(const CEventAdapter1394&);

            /**
             * not implemented: assignment operator
             */
            CEventAdapter1394& operator=(const CEventAdapter1394&);
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker
#endif // SPINNAKER_GENAPI_EVENTADAPTER1394_H
