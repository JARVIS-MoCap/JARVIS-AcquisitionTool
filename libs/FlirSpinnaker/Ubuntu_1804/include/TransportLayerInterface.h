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

#ifndef FLIR_SPINNAKER_TRANSPORTLAYERINTERFACE_H
#define FLIR_SPINNAKER_TRANSPORTLAYERINTERFACE_H

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
	* @defgroup TransportLayerInterface_h TransportLayerInterface Class
	*/
	/*@{*/

	/**
	*@brief Part of the QuickSpin API to provide access to camera information without having to first initialize the camera.
	*/

	class SPINNAKER_API TransportLayerInterface
	{
	public:
		TransportLayerInterface(GenApi::INodeMap *nodeMapTLDevice);
		~TransportLayerInterface();

	protected:
		TransportLayerInterface();

	private:
		TransportLayerInterface(const TransportLayerInterface&);
		TransportLayerInterface& operator=(const TransportLayerInterface&);
		TransportLayerInterface& operator=(GenApi::INodeMap &);

	public:
		/**
		 * Description: Transport layer Producer wide unique identifier of the selected interface.
		 * Visibility: Expert
		 */
		GenApi::IString &InterfaceID;

		/**
		 * Description: User readable name of the selected interface.
		 * Visibility: Expert
		 */
		GenApi::IString &InterfaceDisplayName;

		/**
		 * Description: Transport layer type of the interface.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<InterfaceTypeEnum> &InterfaceType;

		/**
		 * Description: Selector for the different gateway entries for this interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceGatewaySelector;

		/**
		 * Description: IP address of the selected gateway entry of this interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceGateway;

		/**
		 * Description: 48-bit MAC address of this interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceMACAddress;

		/**
		 * Description: Selector for the subnet of this interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceSubnetSelector;

		/**
		 * Description: IP address of the selected subnet of this interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceSubnetIPAddress;

		/**
		 * Description: Subnet mask of the selected subnet of this interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceSubnetMask;

		/**
		 * Description: Transmit link speed of this interface in bits per second.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceTransmitLinkSpeed;

		/**
		 * Description: Receive link speed of this interface in bits per second.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceReceiveLinkSpeed;

		/**
		 * Description: Maximum transmission unit of this interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceMTU;

		/**
		 * Description: Reports and controls the interface's power over Ethernet status.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<POEStatusEnum> &POEStatus;

		/**
		 * Description: Reports whether FLIR Light Weight Filter Driver is enabled or not.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<FilterDriverStatusEnum> &FilterDriverStatus;

		/**
		 * Description: Key to authorize the action for the device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevActionDeviceKey;

		/**
		 * Description: Provides the key that the device will use to validate the action on reception of the action protocol message.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevActionGroupKey;

		/**
		 * Description: Provides the mask that the device will use to validate the action on reception of the action protocol message.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevActionGroupMask;

		/**
		 * Description: Provides the time in nanoseconds when the action is to be executed.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevActionTime;

		/**
		 * Description: Issues an Action Command to attached GEV devices on interface.
		 * Visibility: Expert
		 */
		GenApi::ICommand &ActionCommand;

		/**
		 * Description: Unlocks devices for internal use.
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceUnlock;

		/**
		 * Description: Updates the internal device list.
		 * Visibility: Expert
		 */
		GenApi::ICommand &DeviceUpdateList;

		/**
		 * Description: Number of compatible devices detected on current interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DeviceCount;

		/**
		 * Description: Selector for the different devices on this interface. This value only changes on execution of "DeviceUpdateList". The selector is 0-based in order to match the index of the C interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &DeviceSelector;

		/**
		 * Description: Interface wide unique identifier of the selected device. This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceID;

		/**
		 * Description: Name of the device vendor. This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceVendorName;

		/**
		 * Description: Name of the device model. This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceModelName;

		/**
		 * Description: Serial number of the selected remote device.
		 * Visibility: Expert
		 */
		GenApi::IString &DeviceSerialNumber;

		/**
		 * Description: Gives the device's access status at the moment of the last execution of "DeviceUpdateList". This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<DeviceAccessStatusEnum> &DeviceAccessStatus;

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
		 * Description: Current gateway IP address of the GVCP interface of the selected remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceGateway;

		/**
		 * Description: 48-bit MAC address of the GVCP interface of the selected remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceMACAddress;

		/**
		 * Description: Number of incompatible devices detected on current interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &IncompatibleDeviceCount;

		/**
		 * Description: Selector for the devices that are not compatible with Spinnaker on this interface. This value only changes on execution of "DeviceUpdateList". The selector is 0-based in order to match the index of the C interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &IncompatibleDeviceSelector;

		/**
		 * Description: Interface wide unique identifier of the selected incompatible device. This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IString &IncompatibleDeviceID;

		/**
		 * Description: Name of the incompatible device vendor. This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IString &IncompatibleDeviceVendorName;

		/**
		 * Description: Name of the incompatible device model. This value only changes on execution of "DeviceUpdateList".
		 * Visibility: Expert
		 */
		GenApi::IString &IncompatibleDeviceModelName;

		/**
		 * Description: Current IP address of the GVCP interface of the selected remote incompatible device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &IncompatibleGevDeviceIPAddress;

		/**
		 * Description: Current subnet mask of the GVCP interface of the selected remote incompatible device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &IncompatibleGevDeviceSubnetMask;

		/**
		 * Description: 48-bit MAC address of the GVCP interface of the selected remote incompatible device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &IncompatibleGevDeviceMACAddress;

		/**
		 * Description: Apply the force IP settings (GevDeviceForceIPAddress, GevDeviceForceSubnetMask and GevDeviceForceGateway) in the selected remote device using ForceIP command.
		 * Visibility: Expert
		 */
		GenApi::ICommand &GevDeviceForceIP;

		/**
		 * Description: Static IP address to set for the GVCP interface of the selected remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceForceIPAddress;

		/**
		 * Description: Static subnet mask to set for GVCP interface of the selected remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceForceSubnetMask;

		/**
		 * Description: Static gateway IP address to set for the GVCP interface of the selected remote device.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevDeviceForceGateway;

		/**
		 * Description: Automatically forces the selected remote device to an IP Address on the same subnet as the GVCP interface.
		 * Visibility: Expert
		 */
		GenApi::ICommand &GevDeviceAutoForceIP;

		/**
		 * Description: User readable name of the interface's host adapter.
		 * Visibility: Expert
		 */
		GenApi::IString &HostAdapterName;

		/**
		 * Description: User readable name of the host adapter's vendor.
		 * Visibility: Expert
		 */
		GenApi::IString &HostAdapterVendor;

		/**
		 * Description: Driver version of the interface's host adapter.
		 * Visibility: Expert
		 */
		GenApi::IString &HostAdapterDriverVersion;


	protected:
		friend class Interface;
		friend class IInterface;
		friend class InterfaceInternal;

	};
	/*@}*/

	/*@}*/

}
#endif // FLIR_SPINNAKER_TRANSPORTLAYERINTERFACE_H