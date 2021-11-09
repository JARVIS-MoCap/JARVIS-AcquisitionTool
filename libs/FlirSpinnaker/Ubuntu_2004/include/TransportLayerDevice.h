//=============================================================================
// Copyright (c) 2001-2020 FLIR Systems, Inc. All Rights Reserved.
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
   
/* Auto-generated file. Do not modify. */

#ifndef FLIR_SPINNAKER_TRANSPORTLAYERDEVICE_H
#define FLIR_SPINNAKER_TRANSPORTLAYERDEVICE_H

#include "SpinnakerPlatform.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include "TransportLayerDefs.h"
#include <string>

namespace Spinnaker
{
	/**
	* @defgroup SpinnakerQuickSpinClasses Spinnaker QuickSpin Classes
	*/
	/*@{*/

	/**
	* @defgroup TransportLayerDevice_h TransportLayerDevice Class
	*/
	/*@{*/

	/**
	*@brief Part of the QuickSpin API to provide access to camera information without having to first initialize the camera.
	*/

	class SPINNAKER_API TransportLayerDevice
	{
	public:
		TransportLayerDevice(GenApi::INodeMap *nodeMapTLDevice);
		~TransportLayerDevice();

	protected:
		TransportLayerDevice();

	private:
		TransportLayerDevice(const TransportLayerDevice&);
		TransportLayerDevice& operator=(const TransportLayerDevice&);
		TransportLayerDevice& operator=(GenApi::INodeMap &);

	public:
		/**
		 * Description: Interface-wide unique identifier of this device.
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceID;

		/**
		 * Description: Serial number of the remote device.
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceSerialNumber;

		/**
		 * Description: Name of the remote device vendor.
		 * Visibility: Beginner
		 */
		GenApi::IString &DeviceVendorName;

		/**
		 * Description: Name of the remote device model.
		 * Visibility: Beginner
		 */
		GenApi::IString &DeviceModelName;

		/**
		 * Description: Transport layer type of the device.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceTypeEnum> &DeviceType;

		/**
		 * Description: User readable name of the device. If this is not defined in the device this should be "VENDOR MODEL (ID)".
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceDisplayName;

		/**
		 * Description: Gets the access status the transport layer Producer has on the device.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<DeviceAccessStatusEnum> &DeviceAccessStatus;

		/**
		 * Description: Version of the device.
		 * Visibility: Beginner
		 */
		GenApi::IString &DeviceVersion;

		/**
		 * Description: User Defined Name.
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceUserID;

		/**
		 * Description: Version of the device driver.
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceDriverVersion;

		/**
		 * Description: Indicates whether the device is in updater mode.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &DeviceIsUpdater;

		/**
		 * Description: Controls the device access privilege of an application.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<GevCCPEnum> &GevCCP;

		/**
		 * Description: Sets the location to load GUI XML.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<GUIXMLLocationEnum> &GUIXMLLocation;

		/**
		 * Description: GUI XML Path.
		 * Visibility: Beginner
		 */
		GenApi::IString &GUIXMLPath;

		/**
		 * Description: Sets the location to load GenICam XML.
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<GenICamXMLLocationEnum> &GenICamXMLLocation;

		/**
		 * Description: GenICam XML Path.
		 * Visibility: Beginner
		 */
		GenApi::IString &GenICamXMLPath;

		/**
		 * Description: Current IP address of the GVCP interface of the selected remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceIPAddress;

		/**
		 * Description: Current subnet mask of the GVCP interface of the selected remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceSubnetMask;

		/**
		 * Description: 48-bit MAC address of the GVCP interface of the selected remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceMACAddress;

		/**
		 * Description: Current gateway IP address of the GVCP interface of the remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceGateway;

		/**
		 * Description: Indicates the speed of transmission negotiated by the given network interface in Mbps.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DeviceLinkSpeed;

		/**
		 * Description:  Major version of the specification.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevVersionMajor;

		/**
		 * Description:  Minor version of the specification.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevVersionMinor;

		/**
		 * Description: This represents the endianness of all device's registers (bootstrap registers and manufacturer-specific registers).
		 * Visibility: Expert
		 */
		GenApi::IBoolean &GevDeviceModeIsBigEndian;

		/**
		 * Description: The timeout in us for read/write operations to the camera.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceReadAndWriteTimeout;

		/**
		 * Description: Maximum number of times to retry a read/write operation.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceMaximumRetryCount;

		/**
		 * Description: Current IP port of the GVCP interface of the selected remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDevicePort;

		/**
		 * Description: Discovers and updates the maximum packet size that can be safely used by the device on the current interface.
		 * Visibility: Expert
		 */
		GenApi::ICommand &GevDeviceDiscoverMaximumPacketSize;

		/**
		 * Description: The maximum packet size that can be safely used by the device on the current interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceMaximumPacketSize;

		/**
		 * Description: Indicates whether the device is on the wrong subnet.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &GevDeviceIsWrongSubnet;

		/**
		 * Description: Forces the camera to be on the same subnet as its corresponding interface.
		 * Visibility: Expert
		 */
		GenApi::ICommand &GevDeviceAutoForceIP;

		/**
		 * Description: Apply the force IP settings (GevDeviceForceIPAddress, GevDeviceForceSubnetMask and GevDeviceForceGateway) in the Device using ForceIP command.
		 * Visibility: Expert
		 */
		GenApi::ICommand &GevDeviceForceIP;

		/**
		 * Description: Static IP address to set for the GVCP interface of the remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceForceIPAddress;

		/**
		 * Description: Static subnet mask to set for GVCP interface of the remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceForceSubnetMask;

		/**
		 * Description: Static gateway IP address to set for the GVCP interface of the remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceForceGateway;

		/**
		 * Description: Controls and indicates if the device is operating in as a Multicast Monitor.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &DeviceMulticastMonitorMode;

		/**
		 * Description: Identifies the endianness handling mode.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceEndianessMechanismEnum> &DeviceEndianessMechanism;

		/**
		 * Description: 
		 * Visibility: Invisible
		 */
		GenApi::IString &DeviceInstanceId;

		/**
		 * Description: Device Location.
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceLocation;

		/**
		 * Description: The USB Speed that the device is currently operating at.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceCurrentSpeedEnum> &DeviceCurrentSpeed;

		/**
		 * Description: Indicates whether the device is communicating in U3V Protocol.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &DeviceU3VProtocol;


	protected:
		friend class CameraBase;
		friend class ICameraBase;
		friend class CameraInternal;

	};
	/*@}*/

	/*@}*/

}
#endif // FLIR_SPINNAKER_TRANSPORTLAYERDEVICE_H