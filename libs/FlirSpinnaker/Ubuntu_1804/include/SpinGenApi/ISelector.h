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
#ifndef SPINNAKER_GENAPI_ISELECTOR_H
#define SPINNAKER_GENAPI_ISELECTOR_H

#if defined(_MSC_VER) && (_MSC_VER > 1200)
#pragma once
#endif // _MSC_VER > 1200

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "Container.h"

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
         *  @defgroup ISelector_h ISelector Interface
         */
        /*@{*/

        /**
         * @brief Interface for groups of features selected by a single one
         */
        interface SPINNAKER_API_ABSTRACT ISelector : virtual public IBase
        {
            /**
             * true if this feature selects a group of features
             */
            virtual bool IsSelector() const = 0;

            /**
             * retrieve the group of selected features
             */
            virtual void GetSelectedFeatures(FeatureList_t&) const = 0;

            /**
             * retrieve the group of features selecting this node
             */
            virtual void GetSelectingFeatures(FeatureList_t&) const = 0;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // SPINNAKER_GENAPI_ISELECTOR_H
