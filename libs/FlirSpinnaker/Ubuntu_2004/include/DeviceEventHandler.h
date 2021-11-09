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

#ifndef FLIR_SPINNAKER_DEVICE_EVENT_HANDLER_H
#define FLIR_SPINNAKER_DEVICE_EVENT_HANDLER_H

#include "Interface/IDeviceEventHandler.h"

namespace Spinnaker
{
    /**
     *  @defgroup SpinnakerEventClasses Spinnaker EventHandler Classes
     */
    /*@{*/

    /**
     *  @defgroup DeviceEventHandler_h DeviceEventHandler Class
     */
    /*@{*/

    /**
     * @brief A handler to device events.
     */

    class SPINNAKER_API DeviceEventHandler : public IDeviceEventHandler
    {
      public:
        /**
         * Default constructor.
         */
        DeviceEventHandler();

        /**
         * Virtual destructor.
         */
        virtual ~DeviceEventHandler();

        /**
         * Device event callback.
         *
         * @param eventName The name of the event
         */
        virtual void OnDeviceEvent(Spinnaker::GenICam::gcstring eventName) = 0;

        /**
         * Get the ID of the device event.
         *
         * @return The device event ID
         */
        uint64_t GetDeviceEventId() const;

        /**
         * Get the name of the device event.
         *
         * @return The device event name
         */
        GenICam::gcstring GetDeviceEventName() const;

      protected:
        /**
         * Assignment operator.
         */
        DeviceEventHandler& operator=(const DeviceEventHandler&);
    };
    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_DEVICE_EVENT_HANDLER_H