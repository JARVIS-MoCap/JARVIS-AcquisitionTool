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

#ifndef FLIR_SPINNAKER_INTERFACE_ARRIVAL_EVENT_HANDLER_H
#define FLIR_SPINNAKER_INTERFACE_ARRIVAL_EVENT_HANDLER_H

#include "Interface/IInterfaceArrivalEventHandler.h"

namespace Spinnaker
{
    /**
     *  @defgroup SpinnakerEventClasses Spinnaker EventHandler Classes
     */

    /*@{*/

    /**
     *  @defgroup InterfaceArrivalEventHandler_h InterfaceArrivalEventHandler Class
     */

    /*@{*/

    /**
     * @brief An event handler for capturing the interface arrival event. Note that only GEV interface arrivals are
     * currently handled.
     */
    class SPINNAKER_API InterfaceArrivalEventHandler : public IInterfaceArrivalEventHandler
    {
      public:
        /**
         * Default constructor.
         */
        InterfaceArrivalEventHandler();

        /**
         * Virtual destructor.
         */
        virtual ~InterfaceArrivalEventHandler();

        /**
         * Interface arrival event callback. Note that only GEV interface arrivals are currently handled.
         *
         * @param interfaceID The ID of the interface that arrived
         */
        virtual void OnInterfaceArrival(std::string interfaceID) = 0;

      protected:
        /**
         * Assignment operator.
         */
        InterfaceArrivalEventHandler& operator=(const InterfaceArrivalEventHandler&);
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_INTERFACE_ARRIVAL_EVENT_HANDLER_H