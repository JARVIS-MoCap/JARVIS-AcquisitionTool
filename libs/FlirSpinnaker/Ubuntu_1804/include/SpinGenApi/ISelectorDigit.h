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

#ifndef SPINNAKER_GENAPI_ISELECTORDIGIT_H
#define SPINNAKER_GENAPI_ISELECTORDIGIT_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Container.h"

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiInterfaces Spinnaker GenApi Interfaces
         */
        /*@{*/

        /**
         *  @defgroup ISelectorDigit_h ISelectorDigit Interface
         */
        /*@{*/

        /**
         * Interface of a "digit" of the "counter" formed by the selector set
         */
        interface SPINNAKER_API_ABSTRACT ISelectorDigit
        {
            /**
             * @brief Sets digit to start value
             * @return true if the resulting value is valid
             */
            virtual bool SetFirst() = 0;

            /**
             * @brief Sets digit to next value
             * @param Tick if false the counter does not tick (but realize it could have)
             * @return true if the resulting value is valid
             */
            virtual bool SetNext(bool Tick = true) = 0;

            /**
             * Restores the selectors' values found at creation
             */
            virtual void Restore() = 0;

            /**
             * Returns a string representation of the digit
             */
            virtual GenICam::gcstring ToString() = 0;

            /**
             * Retrieves an ordered list of selectors
             */
            virtual void GetSelectorList(
                FeatureList_t & SelectorList, /*!> List to contain the selector pointer*/
                bool Incremental = false      /*!> if true only seletor changed since the last GetNext are contained*/
                ) = 0;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif
