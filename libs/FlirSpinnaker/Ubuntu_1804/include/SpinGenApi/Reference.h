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

#ifndef SPINNAKER_GENAPI_REFERENCE_H
#define SPINNAKER_GENAPI_REFERENCE_H

#include "Types.h"
#include "SpinnakerPlatform.h"
#include "GCString.h"

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiInterfaces Spinnaker GenApi Interfaces
         */
        /*@{*/

        interface IBase;

        /**
         *  @defgroup Reference_h Reference Interfaces
         */
        /*@{*/

        //*************************************************************
        // IReference interface
        //*************************************************************

        /**
         * @brief Interface to construct a reference
         */
        interface SPINNAKER_API_ABSTRACT IReference
        {
            /**
             * sets the implementation to a reference
             */
            virtual void SetReference(INode * pBase) = 0;
        };

        /*@}*/

        /**
         *  @defgroup Reference_h Reference Interfaces
         */
        /*@{*/

        //*************************************************************
        // IEnumReference interface
        //*************************************************************

        /**
         * @brief Interface to construct an enum reference
         */
        interface SPINNAKER_API_ABSTRACT IEnumReference
        {
            /**
             * sets the Enum value corresponding to a value
             */
            virtual void SetEnumReference(int Index, GenICam::gcstring Name) = 0;

            /**
             * sets the number of enum values
             */
            virtual void SetNumEnums(int NumEnums) = 0;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // ifndef SPINNAKER_GENAPI_REFERENCE_H
