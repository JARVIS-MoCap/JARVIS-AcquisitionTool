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

#ifndef FLIR_SPINNAKER_SYSTEM_H
#define FLIR_SPINNAKER_SYSTEM_H

#include "Interface/ISystem.h"

namespace Spinnaker
{
    // Forward declaration of implementation class
    class SystemImpl;
    class SystemPtr;
    class LoggingEventHandler;

    // Define macros for getting Spinnaker library version
#define FLIR_SPINNAKER_VERSION_MAJOR 2
#define FLIR_SPINNAKER_VERSION_MINOR 2
#define FLIR_SPINNAKER_VERSION_TYPE  0
#define FLIR_SPINNAKER_VERSION_BUILD 48

    /**
     * @defgroup SpinnakerClasses Spinnaker Classes
     */
    /*@{*/

    /**
     * @defgroup System_h System Class
     */
    /*@{*/

    /**
     * @brief The system object is used to retrieve the list of interfaces and cameras available.
     */

    class SPINNAKER_API System : public ISystem
    {
      public:
        /**
         * Returns a pointer to a Singleton instance of a System object.
         * The System object may be used to get cameras or interfaces.
         * When an application is done using the cameras it is necessary
         * to free the System by calling ReleaseInstance().
         *
         * @see ReleaseInstance()
         *
         * @return A const ref to a system object.
         */
        static SystemPtr GetInstance();

        /**
         * Default destructor.
         */
        virtual ~System();

        /**
         * This call releases the instance of the System Singleton for
         * this process.  After successfully releasing the System instance
         * the pointer returned by GetInstance() will be invalid.  Calling
         * ReleaseInstance while a camera reference is still held will throw
         * an error of type SPINNAKER_ERR_RESOURCE_IN_USE.
         *
         * @see Error
         * @see GetInstance()
         *
         */
        virtual void ReleaseInstance();

        /**
         * Returns a list of interfaces available on the system.  This call
         * returns GigE and Usb2 and Usb3 interfaces. Note that on MacOS only
         * active GigE interfaces will be stored in the returned InterfaceList.
         *
         * @see UpdateInterfaceList()
         *
         * @param updateInterface Determines whether or not UpdateInterfaceList() is called before getting available
         * interfaces
         *
         * @return An InterfaceList object that contains a list of all interfaces.
         */
        virtual InterfaceList GetInterfaces(bool updateInterface = true);

        /**
         * Returns a list of cameras that are available on the system.  This call
         * returns both GigE Vision and Usb3 Vision cameras from all interfaces.
         * The camera list object will reference count the cameras it returns.  It
         * is important that the camera list is destroyed or is cleared before calling
         * system->ReleaseInstance() or else the call to system->ReleaseInstance()
         * will result in an error message thrown that a reference to the camera
         * is still held.
         *
         * @see ReleaseInstance()
         *
         * @see CameraList::Clear()
         *
         * @param updateInterfaces Determines whether or not updateInterfaceList() is called before getting cameras
         *                         from available interfaces on the system
         *
         * @param updateCameras Determines whether or not UpdateCameras() is called before getting cameras from
         *                      available interfaces on the system
         *
         * @return An CameraList object that contains a list of all cameras.
         */
        virtual CameraList GetCameras(bool updateInterfaces = true, bool updateCameras = true);

        /**
         * Updates the list of cameras on the system. Note that System::GetCameras()
         * internally calls UpdateCameras() for each interface it enumerates.  If the list
         * changed between this call and the last time UpdateCameras was called then the return
         * value will be true, otherwise it is false.
         *
         * @see GetCameras()
         *
         * @param updateInterfaces Determines whether or not UpdateInterfaceList() is called before updating cameras
         *                         for available interfaces on the system
         *
         * @return True if cameras changed on interface and false otherwise.
         */
        virtual bool UpdateCameras(bool updateInterfaces = true);

        /**
         * Updates the list of interfaces on the system. If desired, local copies
         * of InterfaceList should be updated by calling GetInterfaces.
         *
         * @see GetInterfaces()
         */
        virtual void UpdateInterfaceList();

        /**
         * Registers an event handler for the system
         *
         * @param evtHandlerToRegister The event handler to register for the system
         *
         */
        void RegisterEventHandler(EventHandler& evtHandlerToRegister);

        /**
         * Unregisters an event handler for the system
         *
         * @param evtHandlerToUnregister The event handler to unregister from the system
         *
         */
        void UnregisterEventHandler(EventHandler& evtHandlerToUnregister);

        /**
         * Registers event handlers for all available interfaces that are found on the system
         * If new interfaces are detected by the system after RegisterInterfaceEventHandler() is called, those interfaces will
         * be automatically registered with this event.
         * Note that only GEV interface arrivals and removals are currently handled.
         *
         * @param evtHandlerToRegister The event handler to register for the available interfaces
         * @param updateInterface Determines whether or not UpdateInterfaceList() is called before registering event for
         *                        available interfaces on the system
         */
        virtual void RegisterInterfaceEventHandler(EventHandler& evtHandlerToRegister, bool updateInterface = true);

        /**
         * Unregisters event handlers for all available interfaces that are found on the system
         *
         * @param evtHandlerToUnregister The event handler to unregister from the available interfaces
         */
        void UnregisterInterfaceEventHandler(EventHandler& evtHandlerToUnregister);

        /**
         * Registers a logging event.
         *
         * @param handler The logging event handler to register
         */
        virtual void RegisterLoggingEventHandler(LoggingEventHandler& handler);

        /**
         * Unregisters all previously registered logging events.
         *
         */
        virtual void UnregisterAllLoggingEventHandlers();

        /**
         * Unregisters a logging event.
         *
         * @param handler The logging event handler to unregister
         */
        virtual void UnregisterLoggingEventHandler(LoggingEventHandler& handler);

        /**
         * Sets a threshold priority level for logging event. Logging events
         * below such level will not trigger callbacks.
         *
         * Spinnaker uses five levels of logging:
         *	- Error		- failures that are non-recoverable without user intervention.
         *	- Warning	- failures that are recoverable without user intervention.
         *	- Notice	- information about events such as camera arrival and removal, initialization and
         *                deinitialization, starting and stopping image acquisition, and feature modification.
         *	- Info		- information about recurring events that are generated regularly such as information on
         *                individual images.
         *	- Debug		- information that can be used to troubleshoot the system.
         *
         *
         * @see SpinnakerLogLevel
         *
         * @param level The threshold level
         */
        virtual void SetLoggingEventPriorityLevel(SpinnakerLogLevel level);

        /**
         * Retrieves the current logging event priority level.
         *
         * Spinnaker uses five levels of logging:
         *	- Error		- failures that are non-recoverable without user intervention.
         *	- Warning	- failures that are recoverable without user intervention.
         *	- Notice	- information about events such as camera arrival and removal, initialization and
         *                deinitialization, starting and stopping image acquisition, and feature modification.
         *	- Info		- information about recurring events that are generated regularly such as information on
         *                individual images.
         *	- Debug		- information that can be used to troubleshoot the system.
         *
         * @see SpinnakerLogLevel
         *
         * @return Level The threshold level
         */
        virtual SpinnakerLogLevel GetLoggingEventPriorityLevel();

        /**
         * Checks if the system is in use by any interface or camera objects.
         *
         * @return Returns true if the system is in use and false otherwise.
         */
        virtual bool IsInUse();

        /**
         * Broadcast an Action Command to all devices on system
         *
         * @param deviceKey The Action Command's device key
         * @param groupKey The Action Command's group key
         * @param groupMask The Action Command's group mask
         * @param actionTime (Optional) Time when to assert a future action. Zero means immediate action.
         * @param pResultSize (Optional) The number of results in the results array. The value passed should be equal to
         * the expected number of devices that acknowledge the command. Returns the number of received results. If this
         * parameter is 0 or NULL, the function will return as soon as the command has been broadcasted.
         * @param results (Optional) An Array with *pResultSize elements to hold the action command result status. The
         * buffer is filled starting from index 0. If received results are less than expected number of devices that
         * acknowledge the command, remaining results are not changed. If received results are more than expected number
         * of devices that acknowledge the command, extra results are ignored and not appended to array. This parameter
         * is ignored if pResultSize is 0. Thus this parameter can be NULL if pResultSize is 0 or NULL.
         *
         */
        virtual void SendActionCommand(
            unsigned int deviceKey,
            unsigned int groupKey,
            unsigned int groupMask,
            unsigned long long actionTime = 0,
            unsigned int* pResultSize = 0,
            ActionCommandResult results[] = NULL);

        /**
         * Get current library version of Spinnaker.
         *
         * @return A struct containing the current version of Spinnaker (major, minor, type, build).
         */
        virtual const LibraryVersion GetLibraryVersion();

        /**
         * Gets a reference to the system node map. The system must be initialized by a call to System::GetInstance()
         * first before a node map reference can be successfully acquired.
         *
         * @return  A reference to the System INodeMap.
         */
        virtual GenApi::INodeMap& GetTLNodeMap() const;

      protected:
        /**
         * Default constructor.
         */
        System();

      private:
        /**
         * Copy constructor.
         */
        System(const System&);

        /**
         * Assignment operator.
         */
        System& operator=(const System&);
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_SYSTEM_H
