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

#ifndef FLIR_SPINNAKER_INTERFACE_PTR_H
#define FLIR_SPINNAKER_INTERFACE_PTR_H

#include "SpinnakerPlatform.h"
#include "BasePtr.h"
#include "Interface.h"

namespace Spinnaker
{
    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */

    /*@{*/

    /**
     *  @defgroup InterfacePtr_h InterfacePtr Class
     */

    /*@{*/

    /**
     * @brief A reference tracked pointer to the interface object.
     */

    class SPINNAKER_API InterfacePtr : public BasePtr<IInterface>
    {
      public:
        /**
         * Default Constructor
         */
        InterfacePtr() throw() : BasePtr<IInterface>()
        {
        }

        /**
         * Default Constructor with argument
         */
        InterfacePtr(const int /*nMustBeNull*/) throw() : BasePtr<IInterface>()
        {
        }

        InterfacePtr(const long /*nMustBeNull*/) throw() : BasePtr<IInterface>()
        {
        }

        InterfacePtr(const std::nullptr_t /*nullPtr*/) throw() : BasePtr<IInterface>()
        {
        }
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_INTERFACE_PTR_H