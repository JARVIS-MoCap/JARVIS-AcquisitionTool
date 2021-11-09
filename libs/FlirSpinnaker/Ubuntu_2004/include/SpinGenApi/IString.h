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

#ifndef SPINNAKER_GENAPI_ISTRING_H
#define SPINNAKER_GENAPI_ISTRING_H

#include "GCString.h"
#include "SpinnakerPlatform.h"
#include "Types.h"
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
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup IString_h IString Class
         */
        /*@{*/

        //*************************************************************
        // IString interface
        //*************************************************************

        /**
         * @brief Interface for string properties
         */
        interface SPINNAKER_API_ABSTRACT IString : virtual public IValue
        {
            /**
             * Set node value
             *
             * @param Value The value to set
             * @param Verify Enables AccessMode and Range verification (default = true)
             */
            virtual void SetValue(const GenICam::gcstring& Value, bool Verify = true) = 0;

            /**
             * Set node value
             */
            virtual IString& operator=(const GenICam::gcstring& Value) = 0;

            /**
             * Get node value
             *
             * @param Verify Enables Range verification (default = false). The AccessMode is always checked
             * @param IgnoreCache If true the value is read ignoring any caches (default = false)
             * @return The value read
             */
            virtual GenICam::gcstring GetValue(bool Verify = false, bool IgnoreCache = false) = 0;

            /**
             * Get node value
             */
            virtual GenICam::gcstring operator()() = 0;

            /**
             * Get node value
             */
            virtual GenICam::gcstring operator*() = 0;

            /**
             * Retrieves the maximum length of the string in bytes
             */
            virtual int64_t GetMaxLength() = 0;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // ifndef SPINNAKER_GENAPI_ISTRING_H
