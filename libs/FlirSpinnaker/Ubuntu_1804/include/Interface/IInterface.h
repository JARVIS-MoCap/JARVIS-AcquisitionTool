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

#ifndef FLIR_SPINNAKER_IINTERFACE_H
#define FLIR_SPINNAKER_IINTERFACE_H

#include "SpinnakerPlatform.h"
#include "SpinnakerDefs.h"
#include "CameraList.h"
#include "EventHandler.h"
#include "TransportLayerInterface.h"

namespace Spinnaker
{
    /**
     * @defgroup SpinnakerClasses Spinnaker Classes
     */
    /*@{*/

    /**
     * @defgroup IInterface_h IInterface Class
     */
    /*@{*/

    /**
     * @brief The interface file for Interface.
     */

    class SPINNAKER_API IInterface
    {
      public:
        virtual ~IInterface(){};

        virtual CameraList GetCameras(bool updateCameras = true) const = 0;
        virtual bool UpdateCameras() = 0;
        virtual GenApi::INodeMap& GetTLNodeMap() const = 0;
        virtual void RegisterEventHandler(EventHandler& evtHandlerToRegister) = 0;
        virtual void UnregisterEventHandler(EventHandler& evtHandlerToUnregister) = 0;
        virtual bool IsInUse() const = 0;
        virtual void SendActionCommand(
            unsigned int deviceKey,
            unsigned int groupKey,
            unsigned int groupMask,
            unsigned long long actionTime = 0,
            unsigned int* pResultSize = 0,
            ActionCommandResult results[] = NULL) const = 0;
        virtual bool IsValid() = 0;

        /*
         * Gets vital interface information without connecting to the XML through
         * transport layer specific bootstrap registers.
         */
        TransportLayerInterface TLInterface;

      protected:
        friend class InterfaceInternal;
        friend class SystemImpl;
        struct InterfaceData; // Forward declaration
        InterfaceData* m_pInterfaceData;

        IInterface(){};
        IInterface(const IInterface&){};
        IInterface& operator=(const IInterface&);
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_IINTERFACE_H
