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

#ifndef SPINNAKER_GENAPI_ENUMNODET_H
#define SPINNAKER_GENAPI_ENUMNODET_H

#include "SpinnakerPlatform.h"
#include "GCString.h"
#include "INode.h"
#include "EnumNode.h"
#include "IEnumeration.h"
#include "IEnumerationT.h"
#include "IEnumEntry.h"
#include "Node.h"

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
         *  @defgroup EnumNodeT_h EnumNodeT Class
         */
        /*@{*/

        /**
         * @brief Interface for string properties
         */
        template <class EnumT>
        class SPINNAKER_API CEnumerationTRef : virtual public IEnumerationT<EnumT>, public virtual EnumNode
        {
          public:
            struct NodeImpl;
            CEnumerationTRef();

            CEnumerationTRef(std::shared_ptr<Node::NodeImpl> pEnumeration);

            virtual ~CEnumerationTRef();

            /**
             * Set node value
             *
             * @param Value The value to set
             * @param Verify Enables AccessMode and Range verification (default = true)
             */
            virtual void SetValue(EnumT Value, bool Verify = true);

            /**
             * Set node value
             */
            virtual IEnumeration& operator=(EnumT Value);

            /**
             * Get node value
             *
             * @param Verify Enables Range verification (default = false). The AccessMode is always checked
             * @param IgnoreCache If true the value is read ignoring any caches (default = false)
             * @return The value read
             */
            virtual EnumT GetValue(bool Verify = false, bool IgnoreCache = false);

            /**
             * Get node value
             */
            virtual EnumT operator()();

            /**
             * Set node value
             *
             * Note : the operator= is not inherited thus the operator= versions
             * from IEnumeration must be implemented again
             */
            virtual IEnumeration& operator=(const GenICam::gcstring& ValueStr);

            /**
             * returns the EnumEntry object belonging to the Value
             */
            virtual IEnumEntry* GetEntry(const EnumT Value);

            /**
             * Get an entry node by its IntValue
             */
            virtual IEnumEntry* GetEntry(const int64_t IntValue);

            /**
             * Get the current entry
             */
            virtual IEnumEntry* GetCurrentEntry(bool Verify = false, bool IgnoreCache = false);

            /**
             * overload SetReference for EnumerationT
             */
            virtual void SetReference(INode* pBase);

            /**
             * sets the Enum value corresponding to a value
             */
            virtual void SetEnumReference(int Index, GenICam::gcstring Name);

            /**
             * sets the number of enum values
             */
            virtual void SetNumEnums(int NumEnums);

          private:
            std::shared_ptr<Node::NodeImpl> m_pEnumerationT;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // SPINNAKER_GENAPI_ENUMNODET_H