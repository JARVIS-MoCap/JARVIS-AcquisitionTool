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

#ifndef SPINNAKER_GENAPI_IENUMENTRY_H
#define SPINNAKER_GENAPI_IENUMENTRY_H

#include "GCString.h"
#include "SpinnakerPlatform.h"
#include "IValue.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4251) // XXX needs to have dll-interface to be used by clients of class YYY
#endif

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiInterfaces Spinnaker GenApi Interfaces
         */
        /*@{*/

        /**
         *  @defgroup IEnumEntry_h IEnumEntry Interface
         */
        /*@{*/

        //*************************************************************
        // IEnumEntry interface
        //*************************************************************

        /**
         * @brief Interface of single enum value
         */
        /*! Maps of Enum Values to symbolic values */
        interface SPINNAKER_API_ABSTRACT IEnumEntry : virtual public IValue
        {

          public:
            /**
             * Get numeric enum value
             */
            virtual int64_t GetValue() = 0;

            /**
             * Get symbolic enum value
             */
            virtual GenICam::gcstring GetSymbolic() const = 0;

            /**
             * Get double number associated with the entry
             */
            virtual double GetNumericValue() = 0;

            /**
             * Indicates if the corresponding EnumEntry is self clearing
             */
            virtual bool IsSelfClearing() = 0;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // ifndef SPINNAKER_GENAPI_IENUMENTRY_H
