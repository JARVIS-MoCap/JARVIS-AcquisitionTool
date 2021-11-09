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

#ifndef FLIR_SPINNAKER_ICAMERABASE_H
#define FLIR_SPINNAKER_ICAMERABASE_H

#include "TransportLayerStream.h"
#include "TransportLayerDevice.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include "SpinnakerPlatform.h"

#include "EventHandler.h"
#include "SpinnakerDefs.h"

namespace Spinnaker
{
    class ImagePtr;
    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /*@{*/

    /**
     *  @defgroup ICameraBase_h Camera Base Interface Class
     */
    /*@{*/

    /**
     * @brief The interface file for base class for the camera object.
     */

    class SPINNAKER_API ICameraBase
    {
      public:
        virtual ~ICameraBase(void){};

        virtual void Init() = 0;
        virtual void DeInit() = 0;
        virtual bool IsInitialized() = 0;
        virtual bool IsValid() = 0;
        virtual GenApi::INodeMap& GetNodeMap() const = 0;
        virtual GenApi::INodeMap& GetTLDeviceNodeMap() const = 0;
        virtual GenApi::INodeMap& GetTLStreamNodeMap() const = 0;
        virtual GenApi::EAccessMode GetAccessMode() const = 0;
        virtual void ReadPort(uint64_t iAddress, void* pBuffer, size_t iSize) = 0;
        virtual void WritePort(uint64_t iAddress, const void* pBuffer, size_t iSize) = 0;
        virtual void BeginAcquisition() = 0;
        virtual void EndAcquisition() = 0;

        virtual BufferOwnership GetBufferOwnership() const = 0;
        virtual void SetBufferOwnership(const BufferOwnership mode) = 0;
        virtual uint64_t GetUserBufferCount() const = 0;
        virtual uint64_t GetUserBufferSize() const = 0;
        virtual uint64_t GetUserBufferTotalSize() const = 0;
        virtual void SetUserBuffers(void* const pMemBuffers, uint64_t totalSize) = 0;
        virtual void SetUserBuffers(
            void** const ppMemBuffers,
            const uint64_t bufferCount,
            const uint64_t bufferSize) = 0;

        virtual ImagePtr GetNextImage(uint64_t grabTimeout = EVENT_TIMEOUT_INFINITE, uint64_t streamID = 0) = 0;
        virtual GenICam::gcstring GetUniqueID() = 0;
        virtual bool IsStreaming() const = 0;
        virtual GenICam::gcstring GetGuiXml() const = 0;
        virtual void RegisterEventHandler(EventHandler& evtHandlerToRegister) = 0;
        virtual void RegisterEventHandler(EventHandler& evtHandlerToRegister, const GenICam::gcstring& eventName) = 0;
        virtual void UnregisterEventHandler(EventHandler& evtHandlerToUnregister) = 0;
        virtual unsigned int GetNumImagesInUse() = 0;
        virtual unsigned int GetNumDataStreams() = 0;
        virtual unsigned int DiscoverMaxPacketSize() = 0;
        virtual void ForceIP() = 0;

        /**
         * Gets vital camera information by connecting to the camera's
         * bootstrap registers. These nodes also access host software
         * modules and the nodes can be used without having to call
         * Init() on the camera.
         */
        TransportLayerDevice TLDevice;

        /**
         * Gets information about the stream data by connecting to
         * the camera's bootstrap registers.  These nodes also access
         * host software modules and the nodes can be used without
         * having to call Init() on the camera.
         */
        TransportLayerStream TLStream;

      protected:
        friend class CameraInternal;
        friend class InterfaceImpl;
        struct CameraBaseData; // Forward declaration
        CameraBaseData* m_pCameraBaseData;

        ICameraBase(){};
        ICameraBase(const ICameraBase&){};
        ICameraBase& operator=(const ICameraBase&);
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker
#endif /* FLIR_SPINNAKER_ICAMERABASE_H */
