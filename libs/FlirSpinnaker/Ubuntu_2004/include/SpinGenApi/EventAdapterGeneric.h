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

#ifndef SPINNAKER_GENAPI_EVENTADAPTERGENERIC_H
#define SPINNAKER_GENAPI_EVENTADAPTERGENERIC_H

#include "EventAdapter.h"

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup EventAdapterGeneric_h EventAdapterGeneric Class
         */
        /*@{*/

        /**
         * @brief Connects a generic event to a node map
         */
        class SPINNAKER_API CEventAdapterGeneric : public CEventAdapter
        {
          public:
            /**
             * Constructor
             */
            CEventAdapterGeneric(INodeMap* pNodeMap = NULL);

            /**
             * Destructor
             */
            virtual ~CEventAdapterGeneric();

            // Does not have implementation, use the version with EventID
            virtual void DeliverMessage(const uint8_t msg[], uint32_t numBytes);

            virtual void DeliverMessage(const uint8_t msg[], uint32_t numBytes, const GenICam::gcstring& EventID);

            virtual void DeliverMessage(const uint8_t msg[], uint32_t numBytes, uint64_t EventID);
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // SPINNAKER_GENAPI_EVENTADAPTERGENERIC_H
