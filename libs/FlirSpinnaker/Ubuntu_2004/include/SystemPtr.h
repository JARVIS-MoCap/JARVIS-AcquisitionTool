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

#ifndef FLIR_SPINNAKER_SYSTEM_PTR_H
#define FLIR_SPINNAKER_SYSTEM_PTR_H

#include "SpinnakerPlatform.h"
#include "BasePtr.h"
#include "System.h"

namespace Spinnaker
{
    class ISystem;

    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /*@{*/

    /**
     *  @defgroup SystemPtr_h SystemPtr Class
     */
    /*@{*/

    /**
     * @brief A reference tracked pointer to a system object.
     */

    class SPINNAKER_API SystemPtr : public BasePtr<ISystem>
    {
      public:
        //! Default constructor
        SystemPtr(){};

        //! Copy constructor
        SystemPtr(const int /*nMustBeNull*/){};

        //! Copy constructor
        SystemPtr(const long /*nMustBeNull*/){};

        //! Copy constructor
        SystemPtr(const std::nullptr_t /*nullPtr*/){};

        //! Virtual destructor
        virtual ~SystemPtr(void){};
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_SYSTEM_PTR_H