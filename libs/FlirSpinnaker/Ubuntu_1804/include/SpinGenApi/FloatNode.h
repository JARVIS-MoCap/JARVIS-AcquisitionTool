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

#ifndef SPINNAKER_GENAPI_FLOATNODE_H
#define SPINNAKER_GENAPI_FLOATNODE_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "GCString.h"
#include "ISelector.h"
#include "INode.h"
#include "ValueNode.h"
#include "IFloat.h"
#include "IInteger.h"
#include "IEnumeration.h"

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
         *  @defgroup FloatNode_h FloatNode Class
         */
        /*@{*/

        /**
         * @brief Interface for string properties
         */
        class SPINNAKER_API FloatNode : virtual public IFloat, virtual public ValueNode
        {
          public:
            struct NodeImpl;
            FloatNode();

            FloatNode(std::shared_ptr<Node::NodeImpl> pFloat);

            virtual ~FloatNode();

            /**
             * Set node value
             *
             * @param Value The value to set
             * @param Verify Enables AccessMode and Range verification (default = true)
             */
            virtual void SetValue(double Value, bool Verify = true);

            /**
             * Set node value
             */
            virtual IFloat& operator=(double Value);

            /**
             * Get node value
             *
             * @param Verify Enables Range verification (default = false). The AccessMode is always checked
             * @param IgnoreCache If true the value is read ignoring any caches (default = false)
             * @return The value read
             */
            virtual double GetValue(bool Verify = false, bool IgnoreCache = false);

            /**
             * Get node value
             */
            virtual double operator()();

            /**
             * Get node value
             */
            virtual double operator*();

            /**
             * Get minimum value allowed
             */
            virtual double GetMin();

            /**
             * Get maximum value allowed
             */
            virtual double GetMax();

            /**
             * True if the float has a constant increment
             */
            virtual bool HasInc();

            /**
             * Get increment mode
             */
            virtual EIncMode GetIncMode();

            /**
             * Get the constant increment if there is any
             */
            virtual double GetInc();

            /**
             * Get list of valid value
             */
            virtual double_autovector_t GetListOfValidValues(bool bounded = true);

            /**
             * Get recommended representation
             */
            virtual ERepresentation GetRepresentation();

            /**
             * Get the physical unit name
             */
            virtual GenICam::gcstring GetUnit() const;

            /**
             * Get the way the float should be converted to a string
             */
            virtual EDisplayNotation GetDisplayNotation() const;

            /**
             * Get the precision to be used when converting the float to a string
             */
            virtual int64_t GetDisplayPrecision() const;

            /**
             * gets the interface of an alias node.
             */
            IInteger* GetIntAlias();

            /**
             * gets the interface of an alias node.
             */
            IEnumeration* GetEnumAlias();

            /**
             * Restrict minimum value
             */
            virtual void ImposeMin(double Value);

            /**
             * Restrict maximum value
             */
            virtual void ImposeMax(double Value);

            /**
             * overload SetReference for Float
             */
            virtual void SetReference(INode* pBase);

          private:
            std::shared_ptr<Node::NodeImpl> m_pFloat;
        };

        typedef FloatNode CFloatRef;

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // SPINNAKER_GENAPI_FLOATNODE_H