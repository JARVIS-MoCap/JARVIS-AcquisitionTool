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

#ifndef SPINNAKER_GENAPI_IENUMERATIONT_H
#define SPINNAKER_GENAPI_IENUMERATIONT_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Pointer.h"
#include "IEnumeration.h"
#include <vector>
//#include "GenApi/Compatibility.h"

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiInterfaces Spinnaker GenApi Interfaces
         */
        /*@{*/

        /**
         *  @defgroup IEnumerationT_h IEnumerationT Interface
         */
        /*@{*/

        //*************************************************************
        // Enumeration template interface
        //*************************************************************

        /**
         * @brief Interface for enumeration properties
         */
        template <typename EnumT>
        interface SPINNAKER_API_ABSTRACT IEnumerationT : virtual public IEnumeration, virtual public IEnumReference
        {
            /**
             * Set node value
             *
             * @param Value The value to set
             * @param Verify Enables AccessMode and Range verification (default = true)
             */
            virtual void SetValue(EnumT Value, bool Verify = true) = 0;

            /**
             * Set node value
             */
            virtual IEnumeration& operator=(EnumT Value) = 0;

            /**
             * Get node value
             *
             * @param Verify Enables Range verification (default = false). The AccessMode is always checked
             * @param IgnoreCache If true the value is read ignoring any caches (default = false)
             * @return The value read
             */
            virtual EnumT GetValue(bool Verify = false, bool IgnoreCache = false) = 0;

            /**
             * Get node value
             */
            virtual EnumT operator()() = 0;

            /**
             * Set node value
             *
             * Note : the operator= is not inherited thus the operator= versions
             * from IEnumeration must be implemented again
             */
            virtual IEnumeration& operator=(const GenICam::gcstring& ValueStr) = 0;

            /**
             * Get an entry node by its IntValue
             */
            virtual IEnumEntry* GetEntry(const int64_t IntValue) = 0;

            /**
             * returns the EnumEntry object belonging to the Value
             */
            virtual IEnumEntry* GetEntry(const EnumT Value) = 0;

            /**
             * Get the current entry
             */
            virtual IEnumEntry* GetCurrentEntry(bool Verify = false, bool IgnoreCache = false) = 0;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // ifndef SPINNAKER_GENAPI_IENUMERATIONT_H
