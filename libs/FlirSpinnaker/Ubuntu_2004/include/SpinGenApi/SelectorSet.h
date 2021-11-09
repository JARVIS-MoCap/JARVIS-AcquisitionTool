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

#ifndef SPINNAKER_GENAPI_SELECTORSET_H
#define SPINNAKER_GENAPI_SELECTORSET_H

#include "INode.h"
#include "Node.h"
#include "Base.h"
#include "Pointer.h"

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup SelectorSet_h SelectorSet Class
         */
        /*@{*/

        /**
         * The set of selectors selecting a given node
         */
        class SPINNAKER_API CSelectorSet : virtual public Node
        {
          public:
            /**
             * Constructor
             */
            CSelectorSet(IBase* pBase /*!> Feature selected by the selector set*/
            );

            /**
             * Destructor
             */
            ~CSelectorSet();

            /**
             * returns true if no selectors are present
             */
            bool IsEmpty();

            // Implementation of ISelectorDigit
          public:
            virtual bool SetFirst();
            virtual bool SetNext(bool Tick = true);
            virtual void Restore();
            virtual GenICam::gcstring ToString();
            virtual void GetSelectorList(FeatureList_t& SelectorList, bool Incremental = false);

          private:
            INode* m_pNode;
            void* m_pSelectorSet;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker
#endif
