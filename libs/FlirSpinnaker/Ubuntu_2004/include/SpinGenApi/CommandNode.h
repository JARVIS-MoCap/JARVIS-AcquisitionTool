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

#ifndef SPINNAKER_GENAPI_COMMANDNODE_H
#define SPINNAKER_GENAPI_COMMANDNODE_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "GCString.h"
#include "ISelector.h"
#include "INode.h"
#include "ValueNode.h"
#include "ICommand.h"

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
         *  @defgroup CommandNode_h CommandNode Class
         */
        /*@{*/

        /**
         * @brief Interface for string properties
         */
        class SPINNAKER_API CommandNode : virtual public ICommand, virtual public ValueNode
        {
          public:
            struct NodeImpl;

            CommandNode();

            CommandNode(std::shared_ptr<Node::NodeImpl> pCommand);

            virtual ~CommandNode();

            /**
             * Execute the command
             *
             * @param Verify Enables AccessMode and Range verification (default = true)
             */
            virtual void Execute(bool Verify = true);

            /**
             * Execute the command
             */
            virtual void operator()();

            /**
             * Query whether the command is executed
             *
             * @param Verify Enables Range verification (default = false). The AccessMode is always checked
             * @return True if the Execute command has finished; false otherwise
             */
            virtual bool IsDone(bool Verify = true);

            /**
             * overload SetReference for Value
             */
            virtual void SetReference(INode* pBase);

          private:
            std::shared_ptr<Node::NodeImpl> m_pCommand;
        };

        typedef CommandNode CCommandRef;

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // SPINNAKER_GENAPI_COMMANDNODE_H