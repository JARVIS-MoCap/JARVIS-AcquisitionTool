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

#ifndef SPINNAKER_GENAPI_INTEGERNODE_H
#define SPINNAKER_GENAPI_INTEGERNODE_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "GCString.h"
#include "ISelector.h"
#include "INode.h"
#include "ValueNode.h"
#include "IInteger.h"
#include "IFloat.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4250) // C4250 - 'class1' : inherits 'class2::member' via dominance
#pragma warning(disable : 4251) // XXX needs to have dll-interface to be used by clients of class YYY
#pragma warning(disable : 4275) // non dll-interface structXXX used as base
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
         *  @defgroup IntegerNode_h IntegerNode Class
         */
        /*@{*/

        /**
         * @brief Interface for string properties
         */
        class SPINNAKER_API IntegerNode : virtual public IInteger, virtual public ValueNode
        {
          public:
            struct NodeImpl;
            IntegerNode();

            IntegerNode(std::shared_ptr<Node::NodeImpl> pInteger);

            virtual ~IntegerNode();

            /**
             * Set node value
             *
             * @param Value The value to set
             * @param Verify Enables AccessMode and Range verification (default = true)
             */
            virtual void SetValue(int64_t Value, bool Verify = true);

            /**
             * Set node value
             */
            virtual IInteger& operator=(int64_t Value);

            /**
             * Get node value
             *
             * @param Verify Enables Range verification (default = false). The AccessMode is always checked
             * @param IgnoreCache If true the value is read ignoring any caches (default = false)
             * @return The value read
             */
            virtual int64_t GetValue(bool Verify = false, bool IgnoreCache = false);

            /**
             * Get node value
             */
            virtual int64_t operator()();

            /**
             * Get node value
             */
            virtual int64_t operator*();

            /**
             * Get minimum value allowed
             */
            virtual int64_t GetMin();

            /**
             * Get maximum value allowed
             */
            virtual int64_t GetMax();

            /**
             * Get increment mode
             */
            virtual EIncMode GetIncMode();

            /**
             * Get increment
             */
            virtual int64_t GetInc();

            /**
             * Get list of valid value
             */
            virtual int64_autovector_t GetListOfValidValues(bool bounded = true);

            /**
             * Get recommended representation
             */
            virtual ERepresentation GetRepresentation();

            /**
             * Get the physical unit name
             */
            virtual GenICam::gcstring GetUnit();

            /**
             * gets the interface of an alias node.
             */
            virtual IFloat* GetFloatAlias();

            /**
             * Restrict minimum value
             */
            virtual void ImposeMin(int64_t Value);

            /**
             * Restrict maximum value
             */
            virtual void ImposeMax(int64_t Value);

            /**
             * overload SetReference for Integer
             */
            virtual void SetReference(INode* pBase);

          private:
            std::shared_ptr<Node::NodeImpl> m_pInteger;
        };

        typedef IntegerNode CIntegerRef;

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // SPINNAKER_GENAPI_INTEGERNODE_H