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

#ifndef FLIR_SPINNAKER_INTERFACE_EVENT_HANDLER_H
#define FLIR_SPINNAKER_INTERFACE_EVENT_HANDLER_H

#include "Interface/IInterfaceEventHandler.h"

namespace Spinnaker
{
    /**
     * @defgroup SpinnakerEventClasses Spinnaker EventHandler Classes
     */
    /*@{*/

    /**
     *  @defgroup InterfaceEventHandler_h InterfaceEventHandler Class
     */
    /*@{*/

    /**
     * @brief A handler to device arrival and removal events on all interfaces.
     */

    class SPINNAKER_API InterfaceEventHandler : public IInterfaceEventHandler
    {
      public:
        /**
         * Default constructor.
         */
        InterfaceEventHandler();

        /**
         * Virtual destructor.
         */
        virtual ~InterfaceEventHandler();

        /**
         * Device arrival event callback.
         */
        virtual void OnDeviceArrival(uint64_t serialNumber) = 0;

        /**
         * Callback to the device removal event.
         *
         * @param serialNumber The serial number of the removed device
         */
        virtual void OnDeviceRemoval(uint64_t serialNumber) = 0;

      protected:
        /**
         * Assignment operator.
         */
        InterfaceEventHandler& operator=(const InterfaceEventHandler&);
    };
    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_INTERFACE_EVENT_HANDLER_H