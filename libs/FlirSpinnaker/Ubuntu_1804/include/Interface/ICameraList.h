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

#ifndef FLIR_SPINNAKER_ICAMERALIST_H
#define FLIR_SPINNAKER_ICAMERALIST_H

#include "SpinnakerPlatform.h"
#include "SpinnakerDefs.h"
#include "Camera.h"
#include "CameraPtr.h"

namespace Spinnaker
{
    class CameraList;
    class CameraPtr;
    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */

    /*@{*/

    /**
     *  @defgroup CameraList_h Camera List Class
     */

    /*@{*/

    /**
     * @brief Used to hold a list of camera objects.
     */
    class SPINNAKER_API ICameraList
    {
      public:
        virtual ~ICameraList(){};

        virtual CameraPtr operator[](unsigned int index) = 0;
        virtual unsigned int GetSize() const = 0;
        virtual CameraPtr GetByIndex(unsigned int index) const = 0;
        virtual CameraPtr GetBySerial(std::string serialNumber) const = 0;
        virtual CameraPtr GetByDeviceID(std::string deviceID) const = 0;
        virtual void Clear() = 0;
        virtual void RemoveBySerial(std::string serialNumber) = 0;
        virtual void RemoveByIndex(unsigned int index) = 0;
        virtual void RemoveByDeviceID(std::string deviceID) = 0;
        virtual void Append(CameraList& otherList) = 0;

      protected:
        friend class InterfaceImpl;
        friend class CameraListImpl;
        struct CameraListData; // Forward declaration
        CameraListData* m_pCameraListData;

        ICameraList(){};
        ICameraList(const ICameraList&){};
        ICameraList& operator=(const ICameraList&);
    };

    /*@}*/

    /*@}*/

} // namespace Spinnaker

#endif