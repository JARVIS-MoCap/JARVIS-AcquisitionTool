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

#ifndef FLIR_SPINNAKER_IDEVICE_REMOVAL_EVENT_HANDLER_H
#define FLIR_SPINNAKER_IDEVICE_REMOVAL_EVENT_HANDLER_H

#include "EventHandler.h"
#include "SpinnakerPlatform.h"

namespace Spinnaker
{
    class IDeviceRemovalEventHandler : public virtual EventHandler
    {
      public:
        virtual ~IDeviceRemovalEventHandler(){};
        virtual void OnDeviceRemoval(uint64_t serialNumber) = 0;

      protected:
        IDeviceRemovalEventHandler(){};
        IDeviceRemovalEventHandler(const IDeviceRemovalEventHandler&){};
        IDeviceRemovalEventHandler& operator=(const IDeviceRemovalEventHandler&);
    };
} // namespace Spinnaker

#endif /* FLIR_SPINNAKER_IDEVICE_REMOVAL_EVENT_HANDLER_H */