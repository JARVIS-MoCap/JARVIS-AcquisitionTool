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

#ifndef SPINNAKER_GENAPI_EVENTADAPTER_H
#define SPINNAKER_GENAPI_EVENTADAPTER_H

#include "Types.h"
#include "INodeMap.h"
#include "EventPort.h"

namespace Spinnaker
{
    namespace GenApi
    {

        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup EventAdapter_h EventAdapter Class
         */
        /*@{*/

        /**
         * @brief Delivers Events to ports
         */
        class SPINNAKER_API CEventAdapter
        {

          public:
            /**
             * Constructor
             */
            CEventAdapter(INodeMap* pNodeMap = NULL);

            /**
             * Destructor
             */
            virtual ~CEventAdapter();

            /**
             * Attaches to a node map and retrieves the chunk ports
             */
            virtual void AttachNodeMap(INodeMap* pNodeMap);

            /**
             * Detaches from the node emap
             */
            virtual void DetachNodeMap();

            /**
             * Deliver message
             */
            virtual void DeliverMessage(const uint8_t msg[], uint32_t numBytes) = 0;

          protected:
            void* m_pEventAdapter;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // SPINNAKER_GENAPI_EVENTADAPTER_H
