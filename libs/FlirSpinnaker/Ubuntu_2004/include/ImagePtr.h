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

#ifndef FLIR_SPINNAKER_IMAGE_PTR_H
#define FLIR_SPINNAKER_IMAGE_PTR_H

#include "SpinnakerPlatform.h"
#include "BasePtr.h"
#include "Interface/IImage.h"

namespace Spinnaker
{
    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */

    /*@{*/

    /**
     *  @defgroup ImagePtr_h ImagePtr Class
     *
     */

    /*@{*/

    /**
     * @brief A reference tracked pointer to an image object.  When the ImagePtr goes out of scope,
     *        it will trigger an auto release of the image from the stream.
     */

    class SPINNAKER_API ImagePtr : public BasePtr<IImage>
    {
      public:
        /**
         * Default constructor.
         */
        ImagePtr();

        /**
         * Default constructor with argument.
         */
        ImagePtr(const int /*nMustBeNull*/);

        /**
         * Default constructor with argument.
         */
        ImagePtr(const long /*nMustBeNull*/);

        /**
         * Default constructor with argument.
         */
        ImagePtr(const std::nullptr_t /*nullPtr*/);

        /**
         * Virtual destructor.
         */
        virtual ~ImagePtr(void);

        /**
         * Assignment operator.
         */
        virtual ImagePtr& operator=(const ImagePtr&);
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_IMAGE_PTR_H