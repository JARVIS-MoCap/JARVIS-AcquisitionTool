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

#ifndef FLIR_SPINNAKER_CAMERABASE_H
#define FLIR_SPINNAKER_CAMERABASE_H

#include "Interface/ICameraBase.h"

namespace Spinnaker
{
    class ImagePtr;

    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /*@{*/

    /**
     *  @defgroup CameraBase_h Camera Base Class
     */
    /*@{*/

    /**
     * @brief The base class for the camera object.
     */

    class SPINNAKER_API CameraBase : public ICameraBase
    {
      public:
        /**
         * Virtual Destructor
         */
        virtual ~CameraBase(void);

        /**
         * Init
         * Connect to camera, retrieve XML and generate node map.
         * This function needs to be called before any camera related
         * API calls such as BeginAcquisition(), EndAcquisition(),
         * GetNodeMap(), GetNextImage().
         *
         * @see BeginAcquisition()
         * @see EndAcquisition()
         * @see GetNodeMap()
         * @see GetNextImage()
         */
        void Init();

        /**
         * DeInit
         * Disconnect camera port and free GenICam node map and
         * GUI XML. Do not call more functions that access the remote
         * device such as WritePort/ReadPort after calling DeInit();
         * Events should also be unregistered before calling camera DeInit().
         * Otherwise an exception will be thrown in the DeInit() call and require
         * the user to unregister events before the camera can be re-initialized again.
         *
         * @see Init()
         * @see UnregisterEventHandler(EventHandler & evtHandlerToUnregister)
         */
        void DeInit();

        /**
         * IsInitialized
         * Checks if camera is initialized. This function needs to return
         * true in order to retrieve a valid NodeMap from the GetNodeMap()
         * call.
         *
         * @see GetNodeMap()
         *
         * @return If camera is initialized or not
         */
        bool IsInitialized();

        /**
         * IsValid
         * Checks a flag to determine if camera is still valid for use.
         *
         * @return If camera is valid or not
         */
        bool IsValid();

        /**
         * GetNodeMap
         * Gets a reference to the node map that is generated from a GenICam
         * XML file.  The camera must be initialized by a call to Init() first
         * before a node map reference can be successfully acquired.
         *
         * @see Init()
         *
         * @return  A reference to the INodeMap.
         */
        GenApi::INodeMap& GetNodeMap() const;

        /**
         * GetTLDeviceNodeMap
         * Gets a reference to the node map that is generated from a GenICam
         * XML file for the GenTL Device module.  The camera does not need to be
         * initialized before acquiring this node map.
         *
         * @return  A reference to the INodeMap.
         */
        GenApi::INodeMap& GetTLDeviceNodeMap() const;

        /**
         * GetTLStreamNodeMap
         * Gets a reference to the node map that is generated from a GenICam
         * XML file for the GenTL Stream module.  The camera does not need to be
         * initialized before acquiring this node map.
         *
         * @return  A reference to the INodeMap.
         */
        GenApi::INodeMap& GetTLStreamNodeMap() const;

        /**
         * GetAccessMode
         * Returns the access mode that the software has on the Camera.
         * The camera does not need to be initialized before calling this function.
         *
         * @see Init()
         *
         * @return An enumeration value indicating the access mode
         */
        GenApi::EAccessMode GetAccessMode() const;

        /*
         * ReadPort
         * Reads a remote port on a physical Camera. This function can be used to read
         * registers on Cameras.
         *
         * Caution: Only perform direct read/write to a register if the register isn't
         *          supported in the device nodemap. Otherwise the camera and nodemap
         *          may be left in an undefined state after the register read/write.
         *
         * @see WritePort()
         *
         * @param iAddress A 64 bit address to a register on the camera
         * @param pBuffer A pointer to a data buffer that will store result
         * @param iSize Number of bytes to read
         */
        void ReadPort(uint64_t iAddress, void* pBuffer, size_t iSize);

        /*
         * WritePort
         * Writes a remote port on a physical Camera. This function can be used to write
         * registers on Cameras.
         *
         * Caution: Only perform direct read/write to a register if the register isn't
         *          supported in the device nodemap. Otherwise the camera and nodemap
         *          may be left in an undefined state after the register read/write.
         *
         * @see ReadPort()
         *
         * @param iAddress A 64 bit address to a register on the camera
         * @param pBuffer A pointer to a data buffer that will be written
         * @param iSize Number of bytes to write
         */
        void WritePort(uint64_t iAddress, const void* pBuffer, size_t iSize);

        /**
         * BeginAcquisition
         * Starts the image acquisition engine. The camera must be initialized via
         * a call to Init() before starting an acquisition.
         *
         * @see Init()
         */
        void BeginAcquisition();

        /**
         * EndAcquisition
         * Stops the image acquisition engine.  If EndAcquisition() is called
         * without a prior call to BeginAcquisition() an error message
         * "Camera is not started" will be thrown. All Images that were
         * acquired using GetNextImage() need to be released first using image->Release()
         * before calling EndAcquisition().  All buffers in the input pool and
         * output queue will be discarded when EndAcquisition() is called.
         *
         * @see Init()
         * @see BeginAcquisition()
         * @see GetNextImage( grabTimeout )
         * @see Image::Release()
         */
        void EndAcquisition();

        /**
         * GetBufferOwnership
         * Gets data buffer ownership.  The data buffers can be owned by System or User.
         * If the system owns the buffers, the memory required for the buffers are
         * allocated and freed by the library.  If user owns the buffers, the user is
         * responsible for allocating and ultimately freeing the memory.  By default,
         * data buffers are owned by the library.
         *
         * @see SetBufferOwnership()
         * @see SetUserBuffers()
         *
         * @return Buffer ownership (system or user)
         */
        BufferOwnership GetBufferOwnership() const;

        /**
         * SetBufferOwnership
         * Sets data buffer ownership.  The data buffers can be owned by System or User.
         * If the system owns the buffers, the memory required for the buffers are
         * allocated and freed by the library.  If user owns the buffers, the user is
         * responsible for allocating and ultimately freeing the memory.  By default,
         * data buffers are owned by the library.
         *
         * @see GetBufferOwnership()
         * @see SetUserBuffers()
         *
         * @param mode System owned or User owned buffers
         */
        void SetBufferOwnership(const BufferOwnership mode);

        /**
         * GetUserBufferCount
         * Gets the number of user memory buffers.
         * This will throw an exception if user memory buffer has not been set.  If the
         * user memory is contiguous, this will throw an exception unless
         * BeginAcquisition() has been called.
         *
         * @see BeginAcquisition()
         * @see SetUserBuffers()
         *
         * @return The number of user memory buffers
         */
        uint64_t GetUserBufferCount() const;

        /**
         * GetUserBufferSize
         * Gets the size of one user memory buffer (in bytes).
         * This will throw an exception if user memory buffer has not been set.  If the
         * user memory is contiguous, this will throw an exception unless
         * BeginAcquisition() has been called.  To prevent image tearing when working
         * with USB3 cameras, the size of each buffer should be equal to:
         *     ((unsigned int) (bufferSize + 1024 - 1) / 1024) * 1024
         * where 1024 is the USB3 packet size.
         *
         * @see BeginAcquisition()
         * @see SetUserBuffers()
         *
         * @return The size of one user memory buffer (in bytes)
         */
        uint64_t GetUserBufferSize() const;

        /**
         * GetUserBufferTotalSize
         * Gets the total size of all the user memory buffers (in bytes).
         * This will throw an exception if user memory buffer has not been set.  The
         * total size should be GetUserBufferSize() multiplied by GetUserBufferCount()
         * or larger.
         *
         * @see GetUserBufferCount()
         * @see GetUserBufferSize()
         * @see SetUserBuffers()
         *
         * @return The total size of all the user memory buffers (in bytes)
         */
        uint64_t GetUserBufferTotalSize() const;

        /**
         * SetUserBuffers
         * Specify contiguous user allocated memory to use as data buffers.
         * To prevent image tearing when working with USB3 cameras, the size of each
         * buffer should be equal to:
         *     ((unsigned int) (bufferSize + 1024 - 1) / 1024) * 1024
         * where 1024 is the USB3 packet size.
         *
         * @see GetBufferOwnership()
         * @see SetBufferOwnership()
         * @see GetUserBufferCount()
         * @see GetUserBufferSize()
         * @see GetUserBufferTotalSize()
         *
         * @param pMemBuffers Pointer to memory buffers to be written to
         * @param totalSize The total size of the memory allocated for the user buffers (in bytes)
         */
        void SetUserBuffers(void* const pMemBuffers, uint64_t totalSize);

        /**
         * SetUserBuffers
         * Specify non-contiguous user allocated memory to use as data buffers.
         * Each pointer to a buffer must have enough memory to hold one image. To prevent
         * image tearing when working with USB3 cameras, the size of each buffer should be
         * equal to:
         *     ((unsigned int) (bufferSize + 1024 - 1) / 1024) * 1024
         * where 1024 is the USB3 packet size.
         *
         * @see GetBufferOwnership()
         * @see SetBufferOwnership()
         * @see GetUserBufferCount()
         * @see GetUserBufferSize()
         * @see GetUserBufferTotalSize()
         *
         * @param ppMemBuffers Pointer to pointers that each point to a single user memory buffer to be written to
         * @param bufferCount The number of user memory buffers
         * @param bufferSize The size of the memory allocated for each user buffer (in bytes)
         */
        void SetUserBuffers(void** const ppMemBuffers, const uint64_t bufferCount, const uint64_t bufferSize);

        /**
         * GetNextImage
         * Gets the next image that was received by the transport layer.  This function
         * will block indefinitely until an image arrives. Most cameras support one stream
         * so the default streamID is 0 but if a camera supports multiple streams
         * the user can input the streamID to select from which stream to grab images
         *
         * @see Init()
         * @see BeginAcquisition()
         * @see EndAcquisition()
         *
         * @param grabTimeout a 64bit value that represents a timeout in milliseconds
         * @param streamID The stream to grab the image.
         * @return pointer to an Image object
         */
        ImagePtr GetNextImage(uint64_t grabTimeout = EVENT_TIMEOUT_INFINITE, uint64_t streamID = 0);

        /**
         * GetUniqueID
         * This returns a unique id string that identifies the camera.  This is the
         * camera serial number.
         *
         * @return string that uniquely identifies the camera (serial number)
         */
        GenICam::gcstring GetUniqueID();

        /**
         * IsStreaming
         * Returns true if the camera is currently streaming or false if it
         * is not.
         *
         * @see Init()
         *
         * @return returns true if camera is streaming and false otherwise.
         */
        bool IsStreaming() const;

        /**
         * Returns the GUI XML that can be passed into the Spinnaker GUI framework
         *
         * @return GenICam::gcstring that represents the uncompressed GUI XML file
         */
        GenICam::gcstring GetGuiXml() const;

        /**
         * RegisterEventHandler(EventHandler &)
         * Registers a specific event handler for the camera.  The camera has to be initialized first
         * with a call to Init() before registering handlers for events.
         *
         * @see Init()
         *
         * @param evtHandlerToRegister The event handler to register for the camera
         */
        void RegisterEventHandler(EventHandler& evtHandlerToRegister);

        /**
         * RegisterEventHandler(EventHandler &, const GenICam::gcstring&)
         * Registers a specific event handler for the camera
         *
         * @see Init()
         *
         * @param evtHandlerToRegister The event handler to register for the camera
         * @param eventName The event name to register
         */
        void RegisterEventHandler(EventHandler& evtHandlerToRegister, const GenICam::gcstring& eventName);

        /**
         * UnregisterEventHandler
         * Unregisters an event handler for the camera
         * Event handlers should be unregistered first before calling camera DeInit().
         * Otherwise an exception will be thrown in the DeInit() call and require
         * the user to unregister event handlers before the camera can be re-initialized again.
         *
         * @see DeInit()
         *
         * @param evtHandlerToUnregister The event handler to unregister from the camera
         */
        void UnregisterEventHandler(EventHandler& evtHandlerToUnregister);

        /**
         * GetNumImagesInUse
         * Returns the number of images that are currently in use.  Each of
         * the images that are currently in use must be cleaned up with
         * a call to image->Release() before calling system->ReleaseInstance().
         *
         * @return The number of images that needs to be cleaned up.
         */
        unsigned int GetNumImagesInUse();

        /**
         * GetNumDataStreams
         * Returns the number of streams that a device supports.
         *
         * @return The number of data streams
         */
        unsigned int GetNumDataStreams();

        /**
         * DiscoverMaxPacketSize
         * Returns the largest packet size that can be safely used on the interface that device is connected to
         *
         * @return The maximum packet size returned.
         */
        unsigned int DiscoverMaxPacketSize();

        /**
         * ForceIP
         * Forces the camera to be on the same subnet as its corresponding interface.
         */
        void ForceIP();

      protected:
        /**
         * Default constructor.
         */
        CameraBase(void);

        /**
         * Copy constructor.
         */
        CameraBase(const CameraBase& /*cam*/);

        /**
         * Assignment operator.
         */
        CameraBase& operator=(const CameraBase& /*cam*/);

        friend class InterfaceImpl;
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_CAMERABASE_H