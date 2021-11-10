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

#ifndef FLIR_SPINNAKER_INTERFACE_REMOVAL_EVENT_HANDLER_H
#define FLIR_SPINNAKER_INTERFACE_REMOVAL_EVENT_HANDLER_H

#include "Interface/IInterfaceRemovalEventHandler.h"

namespace Spinnaker
{
    /**
     * @defgroup SpinnakerEventClasses Spinnaker EventHandler Classes
     */

    /*@{*/

    /**
     *  @defgroup InterfaceRemovalEventHandler_h InterfaceRemovalEventHandler Class
     */

    /*@{*/

    /**
     * @brief An event handler for capturing the interface removal event. Note that only GEV interface removals are
     * currently handled.
     */

    class SPINNAKER_API InterfaceRemovalEventHandler : public IInterfaceRemovalEventHandler
    {
      public:
        /**
         * Default Constructor
         */
        InterfaceRemovalEventHandler();

        /**
         * Virtual Destructor
         */
        virtual ~InterfaceRemovalEventHandler();

        /**
         * Interface removal event callback. Note that only GEV interface removals are currently handled.
         *
         * @param interfaceID The ID of the interface removed
         */
        virtual void OnInterfaceRemoval(std::string interfaceID) = 0;

      protected:
        /**
         * Assignment operator.
         */
        InterfaceRemovalEventHandler& operator=(const InterfaceRemovalEventHandler&);
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_INTERFACE_REMOVAL_EVENT_HANDLER_H