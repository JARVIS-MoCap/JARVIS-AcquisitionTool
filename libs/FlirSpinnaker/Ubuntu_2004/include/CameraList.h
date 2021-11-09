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

#ifndef FLIR_SPINNAKER_CAMERALIST_H
#define FLIR_SPINNAKER_CAMERALIST_H

#include "Interface/ICameraList.h"

namespace Spinnaker
{
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

    class SPINNAKER_API CameraList : public ICameraList
    {
      public:
        /**
         * Default constructor.
         */
        CameraList(void);

        /**
         * Virtual destructor.
         */
        virtual ~CameraList(void);

        /**
         * Copy constructor
         */
        CameraList(const CameraList& iface);

        /**
         * Assignment operator.
         */
        CameraList& operator=(const CameraList& iface);

        /**
         * Array subscription operators.
         */
        CameraPtr operator[](unsigned int index);

        /**
         * Returns the size of the camera list.  The size is the number
         * of Camera objects stored in the list.
         *
         * @return An integer that represents the list size.
         */
        unsigned int GetSize() const;

        /**
         * Returns a pointer to a camera object at the "index". This function will throw
         * a Spinnaker exception with SPINNAKER_ERR_INVALID_PARAMETER error if the input
         * index is out of range.
         *
         * @param index The index at which to retrieve the camera object
         *
         * @return A pointer to a camera object.
         */
        CameraPtr GetByIndex(unsigned int index) const;

        /**
         * Returns a pointer to a camera object with the specified serial number. This
         * function will return a NULL CameraPtr if no matching camera serial is found.
         *
         * @param serialNumber The serial number of the camera object to retrieve
         *
         * @return A pointer to a camera object.
         */
        CameraPtr GetBySerial(std::string serialNumber) const;

        /**
        * Returns a pointer to a camera object with the specified device identifier. This
        * function will return a NULL CameraPtr if no matching device identifier is found.
        *
        * @param deviceID The unique device identifier of the camera object to retrieve
        *
        * @return A pointer to a camera object.
        */
        CameraPtr GetByDeviceID(std::string deviceID) const;

        /**
         * Clears the list of cameras and destroys their corresponding reference counted
         * objects. This is necessary in order to clean up the parent interface.
         * It is important that the camera list is destroyed or is cleared before calling
         * system->ReleaseInstance() or else the call to system->ReleaseInstance()
         * will result in an error message thrown that a reference to the camera
         * is still held.
         *
         * @see System:ReleaseInstance()
         */
        void Clear();

        /**
         * Removes a camera at "index" and destroys its corresponding reference counted
         * object. This function will throw a Spinnaker exception with
         * SPINNAKER_ERR_INVALID_PARAMETER error if the input index is out of range.
         *
         * @param index The index at which to remove the Camera object
         */
        void RemoveByIndex(unsigned int index);

        /**
         * Removes a camera using its serial number and destroys its corresponding reference counted
         * object. This function will throw a Spinnaker exception with SPINNAKER_ERR_NOT_AVAILABLE
         * error if no matching camera serial is found.
         *
         * @param serialNumber The serial number of the Camera object to remove
         */
        void RemoveBySerial(std::string serialNumber);

        /**
        * Removes a camera using its unique device identifier and destroys its corresponding reference counted
        * object. This function will throw a Spinnaker exception with SPINNAKER_ERR_NOT_AVAILABLE
        * error if no matching device identifier is found.
        *
        * @param deviceID The unique device identifier of the camera object to retrieve
        */
        void RemoveByDeviceID(std::string deviceID);

        /**
         * Appends a camera list to the current list.
         *
         * @param otherList The other list to append to this list
         */
        void Append(CameraList& otherList);
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_CAMERALIST_H