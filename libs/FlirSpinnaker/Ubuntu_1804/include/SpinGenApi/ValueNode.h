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

#ifndef SPINNAKER_GENAPI_VALUENODE_H
#define SPINNAKER_GENAPI_VALUENODE_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "INode.h"
#include "IValue.h"
#include "GCString.h"
#include "Node.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4251) // XXX needs to have dll-interface to be used by clients of class YYY
#pragma warning(disable : 4250) // C4250 - 'class1' : inherits 'class2::member' via dominance
#pragma warning(disable : 4275) // warning C4275: non dll-interface struct 'Spinnaker::GenApi::IValue' used as base for
                                // dll-interface class 'Spinnaker::GenApi::Value'
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
         *  @defgroup ValueNode_h ValueNode Class
         */
        /*@{*/

        //*************************************************************
        // IValue interface
        //*************************************************************

        /**
         * @brief Interface for value properties
         */
        class SPINNAKER_API ValueNode : virtual public IValue, virtual public Node
        {
          public:
            struct NodeImpl;
            /**
             * Constructor*/
            ValueNode();

            /**
             * constructor with GenICam IValue*/
            ValueNode(std::shared_ptr<Node::NodeImpl> pValue);

            /**
             * Destructor*/
            ~ValueNode();

            virtual INode* GetNode();

            /**
             * Get content of the node as string
             *
             * @param Verify Enables Range verification (default = false). The AccessMode is always checked
             * @param IgnoreCache If true the value is read ignoring any caches (default = false)
             * @return The value read
             */
            virtual GenICam::gcstring ToString(bool Verify = false, bool IgnoreCache = false);

            /**
             * Set content of the node as string
             *
             * @param ValueStr The value to set
             * @param Verify Enables AccessMode and Range verification (default = true)
             */
            virtual void FromString(const GenICam::gcstring& ValueStr, bool Verify = true);

            /**
             * Checks if the value comes from cache or is requested from another node
             */
            virtual bool IsValueCacheValid() const;

            /**
             * overload SetReference for Value
             */
            virtual void SetReference(INode* pBase);

          private:
            std::shared_ptr<Node::NodeImpl> m_pIValue;
        };

        typedef ValueNode CValueRef;

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // ifndef SPINNAKER_GENAPI_VALUENODE_H