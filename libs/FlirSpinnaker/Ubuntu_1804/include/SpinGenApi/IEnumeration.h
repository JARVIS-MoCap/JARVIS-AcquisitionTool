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

#ifndef SPINNAKER_GENAPI_IENUMERATION_H
#define SPINNAKER_GENAPI_IENUMERATION_H

//#include "GCStringVector.h"
#include "SpinnakerPlatform.h"
#include "IEnumEntry.h"
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
         *  @defgroup IEnumeration_h IEnumeration Interface
         */
        /*@{*/

        //*************************************************************
        // Enumeration interface
        //*************************************************************

        /**
         * @brief Interface for enumeration properties
         */
        interface SPINNAKER_API_ABSTRACT IEnumeration : virtual public IValue
        {
            /**
             * Get list of symbolic Values
             */
            virtual void GetSymbolics(StringList_t & Symbolics) = 0;

            /**
             * Get list of entry nodes
             */
            virtual void GetEntries(NodeList_t & Entries) = 0;

            /**
             * Set string node value
             */
            virtual IEnumeration& operator=(const GenICam::gcstring& ValueStr) = 0;

            /**
             * Set integer node value
             *
             * @param Value The value to set
             * @param Verify Enables AccessMode and Range verification (default = true)
             */
            virtual void SetIntValue(int64_t Value, bool Verify = true) = 0;

            /**
             * Get string node value
             */
            virtual GenICam::gcstring operator*() = 0;

            /**
             * Get integer node value
             *
             * @param Verify Enables Range verification (default = false). The AccessMode is always checked
             * @param IgnoreCache If true the value is read ignoring any caches (default = false)
             * @return The value read
             */
            virtual int64_t GetIntValue(bool Verify = false, bool IgnoreCache = false) = 0;

            /**
             * Get an entry node by name
             */
            virtual IEnumEntry* GetEntryByName(const GenICam::gcstring& Symbolic) = 0;

            /**
             * Get an entry node by its IntValue
             */
            virtual IEnumEntry* GetEntry(const int64_t IntValue) = 0;

            /**
             * Get the current entry
             */
            virtual IEnumEntry* GetCurrentEntry(bool Verify = false, bool IgnoreCache = false) = 0;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // ifndef SPINNAKER_GENAPI_IENUMERATION_H
