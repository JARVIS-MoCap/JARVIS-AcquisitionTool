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

#ifndef SPINNAKER_GENAPI_ENUMNODE_H
#define SPINNAKER_GENAPI_ENUMNODE_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "GCString.h"
#include "ISelector.h"
#include "INode.h"
#include "ValueNode.h"
#include "IEnumeration.h"
#include "IEnumEntry.h"

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
         *  @defgroup EnumNode_h EnumNode Class
         */
        /*@{*/

        /**
         * @brief Interface for string properties
         */
        class SPINNAKER_API EnumNode : virtual public IEnumeration, virtual public ValueNode
        {
          public:
            struct NodeImpl;
            EnumNode();

            EnumNode(std::shared_ptr<Node::NodeImpl> pEnumeration);

            virtual ~EnumNode();

            /**
             * Get list of symbolic Values
             */
            virtual void GetSymbolics(StringList_t& Symbolics);

            /**
             * Get list of entry nodes
             */
            virtual void GetEntries(NodeList_t& Entries);

            /**
             * Set string node value
             */
            virtual IEnumeration& operator=(const GenICam::gcstring& ValueStr);

            /**
             * Set integer node value
             *
             * @param Value The value to set
             * @param Verify Enables AccessMode and Range verification (default = true)
             */
            virtual void SetIntValue(int64_t Value, bool Verify = true);

            /**
             * Get string node value
             */
            virtual GenICam::gcstring operator*();

            /**
             * Get integer node value
             *
             * @param Verify Enables Range verification (default = false). The AccessMode is always checked
             * @param IgnoreCache If true the value is read ignoring any caches (default = false)
             * @return The value read
             */
            virtual int64_t GetIntValue(bool Verify = false, bool IgnoreCache = false);

            /**
             * Get an entry node by name
             */
            virtual IEnumEntry* GetEntryByName(const GenICam::gcstring& Symbolic);

            /**
             * Get an entry node by its IntValue
             */
            virtual IEnumEntry* GetEntry(const int64_t IntValue);

            /**
             * Get the current entry
             */
            virtual IEnumEntry* GetCurrentEntry(bool Verify = false, bool IgnoreCache = false);

            /**
             * overload SetReference for Enumeration
             */
            virtual void SetReference(INode* pBase);

          protected:
            std::shared_ptr<Node::NodeImpl> m_pEnumeration;
        };

        typedef EnumNode CEnumerationRef;

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // SPINNAKER_GENAPI_ENUMNODE_H