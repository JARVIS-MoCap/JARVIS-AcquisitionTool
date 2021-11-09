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

#ifndef SPINNAKER_GENAPI_IREGISTER_H
#define SPINNAKER_GENAPI_IREGISTER_H

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
         *  @defgroup SpinnakerGenApiInterfaces Spinnaker GenApi Interfaces
         */
        /*@{*/

        /**
         *  @defgroup IRegister_h IRegister Interfaces
         */
        /*@{*/

        //*************************************************************
        // IRegister interface
        //*************************************************************

        /**
         * @brief Interface for registers
         */
        interface SPINNAKER_API_ABSTRACT IRegister : virtual public IValue
        {
            /**
             * Set the register's contents
             *!
             * @param pBuffer The buffer containing the data to set
             * @param Length The number of bytes in pBuffer
             * @param Verify Enables AccessMode and Range verification (default = true)
             */
            virtual void Set(const uint8_t* pBuffer, int64_t Length, bool Verify = true) = 0;

            /**
             * Fills a buffer with the register's contents
             *
             * @param pBuffer The buffer receiving the data to read
             * @param Length The number of bytes to retrieve
             * @param Verify Enables Range verification (default = false). The AccessMode is always checked
             * @param IgnoreCache If true the value is read ignoring any caches (default = false)
             * @return The value read
             */
            virtual void Get(uint8_t * pBuffer, int64_t Length, bool Verify = false, bool IgnoreCache = false) = 0;

            /**
             * Retrieves the Length of the register [Bytes]
             */
            virtual int64_t GetLength() = 0;

            /**
             * Retrieves the Address of the register
             */
            virtual int64_t GetAddress() = 0;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // ifndef SPINNAKER_GENAPI_IREGISTER_H
