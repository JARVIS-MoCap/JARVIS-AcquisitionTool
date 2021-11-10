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

#ifndef FLIR_SPINNAKER_TRANSPORTLAYERSYSTEM_H
#define FLIR_SPINNAKER_TRANSPORTLAYERSYSTEM_H

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
	* @defgroup TransportLayerSystem_h TransportLayerSystem Class
	*/
	/*@{*/

	/**
	*@brief Part of the QuickSpin API to provide access to camera information without having to first initialize the camera.
	*/

	class SPINNAKER_API TransportLayerSystem
	{
	public:
		TransportLayerSystem(GenApi::INodeMap *nodeMapTLDevice);
		~TransportLayerSystem();

	protected:
		TransportLayerSystem();

	private:
		TransportLayerSystem(const TransportLayerSystem&);
		TransportLayerSystem& operator=(const TransportLayerSystem&);
		TransportLayerSystem& operator=(GenApi::INodeMap &);

	public:
		/**
		 * Description: Enables or disables enumeration of GEV Interfaces.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &EnumerateGEVInterfaces;

		/**
		 * Description: Unique identifier of the GenTL Producer like a GUID.
		 * Visibility: Expert
		 */
		GenApi::IString &TLID;

		/**
		 * Description: Name of the GenTL Producer vendor.
		 * Visibility: Beginner
		 */
		GenApi::IString &TLVendorName;

		/**
		 * Description: Name of the GenTL Producer to distinguish different kinds of GenTL Producer implementations from one vendor.
		 * Visibility: Beginner
		 */
		GenApi::IString &TLModelName;

		/**
		 * Description: Vendor specific version string.
		 * Visibility: Beginner
		 */
		GenApi::IString &TLVersion;

		/**
		 * Description: Filename including extension of the GenTL Producer.
		 * Visibility: Expert
		 */
		GenApi::IString &TLFileName;

		/**
		 * Description: User readable name of the GenTL Producer.
		 * Visibility: Expert
		 */
		GenApi::IString &TLDisplayName;

		/**
		 * Description: Full path to the GenTL Producer including filename and extension.
		 * Visibility: Expert
		 */
		GenApi::IString &TLPath;

		/**
		 * Description: Transport layer type of the GenTL Producer implementation.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<TLTypeEnum> &TLType;

		/**
		 * Description: Major version number of the GenTL specification the GenTL Producer implementation complies with.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GenTLVersionMajor;

		/**
		 * Description: Minor version number of the GenTL specification the GenTL Producer implementation complies with.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GenTLVersionMinor;

		/**
		 * Description: Major version number of the GenTL Standard Features Naming Convention that was used to create the GenTL Producer`s XML.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GenTLSFNCVersionMajor;

		/**
		 * Description: Minor version number of the GenTL Standard Features Naming Convention that was used to create the GenTL Producer`s XML.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GenTLSFNCVersionMinor;

		/**
		 * Description: Sub minor version number of the GenTL Standard Features Naming Convention that was used to create the GenTL Producer`s XML.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GenTLSFNCVersionSubMinor;

		/**
		 * Description: Major version number of the GigE Vision specification the GenTL Producer implementation complies to.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevVersionMajor;

		/**
		 * Description: Minor version number of the GigE Vision specification the GenTL Producer implementation complies to.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevVersionMinor;

		/**
		 * Description: Updates the internal list of the interfaces. This feature is readable even if the execution cannot be performed immediately. The command then returns and the status can be polled. This function interacts with the TLUpdateInterfaceList function of the GenTL producer. It is up to the GenTL consumer to handle access in case both methods are used.
		 * Visibility: Beginner
		 */
		GenApi::ICommand &InterfaceUpdateList;

		/**
		 * Description: Selector for the different GenTL Producer interfaces. This interface list only changes on execution of "InterfaceUpdateList". The selector is 0-based in order to match the index of the C interface.
		 * Visibility: Beginner
		 */
		GenApi::IInteger &InterfaceSelector;

		/**
		 * Description: GenTL Producer wide unique identifier of the selected interface.
		 * Visibility: Beginner
		 */
		GenApi::IString &InterfaceID;

		/**
		 * Description: A user-friendly name of the selected Interface.
		 * Visibility: Beginner
		 */
		GenApi::IString &InterfaceDisplayName;

		/**
		 * Description: 48-bit MAC address of the selected interface. Note that for a GenTL Producer implementation supporting GigE Vision this feature is mandatory.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceMACAddress;

		/**
		 * Description: IP address of the first subnet of the selected interface. Note that for a GenTL Producer implementation supporting GigE Vision this feature is mandatory.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceDefaultIPAddress;

		/**
		 * Description: Subnet mask of the first subnet of the selected interface. Note that for a GenTL Producer implementation supporting GigE Vision this feature is mandatory.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceDefaultSubnetMask;

		/**
		 * Description: Gateway of the selected interface.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevInterfaceDefaultGateway;


	protected:
		friend class System;
		friend class ISystem;
		friend class SystemPtrInternal;
	};
	/*@}*/

	/*@}*/

}
#endif // FLIR_SPINNAKER_TRANSPORTLAYERSYSTEM_H