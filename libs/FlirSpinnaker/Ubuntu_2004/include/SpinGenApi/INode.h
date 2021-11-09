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

#ifndef SPINNAKER_GENAPI_INODE_H
#define SPINNAKER_GENAPI_INODE_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "GCString.h"
#include "Container.h"
#include "ISelector.h"
#include "Reference.h"

#include "GCStringVector.h"
#include <assert.h>

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
         *  @defgroup SpinnakerGenApiInterfaces Spinnaker GenApi Interfaces
         */
        /*@{*/

        interface INode;
        interface INodeMap;

        /**
         * @brief a list of node references
         */
        typedef node_vector NodeList_t;

        /**
         * @brief the callback handle for nodes
         */
        typedef intptr_t CallbackHandleType;

        class CNodeCallback;

        /**
         *  @defgroup INode_h INode Interface
         */
        /*@{*/

        //*************************************************************
        // INode interface
        //*************************************************************

        /**
         * @brief Interface common to all nodes
         */
        interface SPINNAKER_API_ABSTRACT INode : virtual public ISelector, virtual public IReference
        {
            /**
             * Get node name
             */
            virtual GenICam::gcstring GetName(bool FullQualified = false) const = 0;

            /**
             * Get name space
             */
            virtual GenApi::ENameSpace GetNameSpace() const = 0;

            /**
             * Get the recommended visibility of the node
             */
            virtual EVisibility GetVisibility() const = 0;

            /**
             * Indicates that the node's value may have changed.
             * Fires the callback on this and all dependent nodes
             */
            virtual void InvalidateNode() = 0;

            /**
             * Is the node value cacheable
             */
            virtual bool IsCachable() const = 0;

            /**
             * True if the AccessMode can be cached
             */
            virtual EYesNo IsAccessModeCacheable() const = 0;

            /**
             * Get Caching Mode
             */
            virtual ECachingMode GetCachingMode() const = 0;

            /**
             * recommended polling time (for non-cacheable nodes)
             */
            virtual int64_t GetPollingTime() const = 0;

            /**
             * Get a short description of the node
             */
            virtual GenICam::gcstring GetToolTip() const = 0;

            /**
             * Get a long description of the node
             */
            virtual GenICam::gcstring GetDescription() const = 0;

            /**
             * Get a name string for display
             */
            virtual GenICam::gcstring GetDisplayName() const = 0;

            /**
             * Get a name of the device
             */
            virtual GenICam::gcstring GetDeviceName() const = 0;

            /**
             * @brief Get all nodes this node directly depends on.
             * @param[out] Children List of children nodes
             * @param LinkType The link type
             */
            virtual void GetChildren(GenApi::NodeList_t & Children, ELinkType LinkType = ctReadingChildren) const = 0;

            /**
             * @brief Gets all nodes this node is directly depending on
             * @param[out] Parents List of parent nodes
             */
            virtual void GetParents(GenApi::NodeList_t & Parents) const = 0;

            /**
             * Register change callback
             * Takes ownership of the CNodeCallback object
             */
            virtual CallbackHandleType RegisterCallback(CNodeCallback * pCallback) = 0;

            /**
             * De register change callback
             * Destroys CNodeCallback object
             * @return true if the callback handle was valid
             */
            virtual bool DeregisterCallback(CallbackHandleType hCallback) = 0;

            /**
             * Retrieves the central node map
             */
            virtual INodeMap* GetNodeMap() const = 0;

            /**
             * Get the EventId of the node
             */
            virtual GenICam::gcstring GetEventID() const = 0;

            /**
             * True if the node is streamable
             */
            virtual bool IsStreamable() const = 0;

            /**
             * Returns a list of the names all properties set during initialization
             */
            virtual void GetPropertyNames(GenICam::gcstring_vector & PropertyNames) const = 0;

            /**
             * Retrieves a property plus an additional attribute by name
             * If a property has multiple values/attribute they come with Tabs as delimiters
             */
            virtual bool GetProperty(
                const GenICam::gcstring& PropertyName,
                GenICam::gcstring& ValueStr,
                GenICam::gcstring& AttributeStr) = 0;

            /**
             * Imposes an access mode to the natural access mode of the node
             */
            virtual void ImposeAccessMode(EAccessMode ImposedAccessMode) = 0;

            /**
             * Imposes a visibility  to the natural visibility of the node
             */
            virtual void ImposeVisibility(EVisibility ImposedVisibility) = 0;

            /**
             * Retrieves the a node which describes the same feature in a different way
             */
            virtual INode* GetAlias() const = 0;

            /**
             * Retrieves the a node which describes the same feature so that it can be casted
             */
            virtual INode* GetCastAlias() const = 0;

            /**
             * Gets a URL pointing to the documentation of that feature
             */
            virtual GenICam::gcstring GetDocuURL() const = 0;

            /**
             * True if the node should not be used any more
             */
            virtual bool IsDeprecated() const = 0;

            /**
             * Get the type of the main interface of a node
             */
            virtual EInterfaceType GetPrincipalInterfaceType() const = 0;

            /**
             * True if the node can be reached via category nodes from a category node named "Root"
             */
            virtual bool IsFeature() const = 0;

            // helpers
            virtual bool operator==(int nullPtr) const = 0;

            virtual bool operator!=(int nullPtr) const = 0;
        };

        /**
         * \addtogroup INode_h INode Class
         * \{
         */

        /**
         * Tests if readable
         */
        inline bool IsReadable(EAccessMode AccessMode)
        {
            return RO == AccessMode || RW == AccessMode;
        }

        /**
         * Checks if a node is readable
         */
        inline bool IsReadable(const IBase* p)
        {
            return (p != NULL) && IsReadable(p->GetAccessMode());
        }

        /**
         * Checks if a node is readable
         */
        inline bool IsReadable(const IBase& r)
        {
            return IsReadable(r.GetAccessMode());
        }

        /**
         * Tests if writable
         */
        inline bool IsWritable(EAccessMode AccessMode)
        {
            return WO == AccessMode || RW == AccessMode;
        }

        /**
         * Checks if a node is writable
         */
        inline bool IsWritable(const IBase* p)
        {
            return (p != NULL) && IsWritable(p->GetAccessMode());
        }

        /**
         * Checks if a node is writable
         */
        inline bool IsWritable(const IBase& r)
        {
            return IsWritable(r.GetAccessMode());
        }

        /**
         * Tests if implemented
         */
        inline bool IsImplemented(EAccessMode AccessMode)
        {
            return AccessMode != NI;
        }

        /**
         * Checks if a node is implemented
         */
        inline bool IsImplemented(const IBase* p)
        {
            return (p != NULL) && IsImplemented(p->GetAccessMode());
        }

        /**
         * Checks if a node is implemented
         */
        inline bool IsImplemented(const IBase& r)
        {
            return IsImplemented(&r);
        }

        /**
         * Tests if available
         */
        inline bool IsAvailable(EAccessMode AccessMode)
        {
            return !(AccessMode == NA || AccessMode == NI);
        }

        /**
         * Checks if a node is available
         */
        inline bool IsAvailable(const IBase* p)
        {
            return (p != NULL) && IsAvailable(p->GetAccessMode());
        }

        /**
         * Checks if a node is available
         */
        inline bool IsAvailable(const IBase& r)
        {
            return IsAvailable(r.GetAccessMode());
        }

        /**
         * @brief Computes which access mode the two guards allow together
         */
        inline EAccessMode Combine(EAccessMode Peter, EAccessMode Paul)
        {
            assert(Peter != _UndefinedAccesMode);
            assert(Paul != _UndefinedAccesMode);

            if (Peter == NI || Paul == NI)
                return NI;
            else if (Peter == NA || Paul == NA)
                return NA;
            else if ((Peter == RO && Paul == WO) || (Peter == WO && Paul == RO))
                return NA;
            else if (Peter == WO || Paul == WO)
                return WO;
            else if (Peter == RO || Paul == RO)
                return RO;
            else
                return RW;
        }

        /**
         * Tests Visibility
         * CAVE : this relies on the EVisibility enum's coding
         */
        inline bool IsVisible(EVisibility Visibility, EVisibility MaxVisiblity)
        {
            return (Visibility <= MaxVisiblity);
        }

        /**
         * Computes which visibility the two guards allow together
         */
        inline EVisibility Combine(EVisibility Peter, EVisibility Paul)
        {
            assert(Peter != _UndefinedVisibility);
            assert(Paul != _UndefinedVisibility);

            if (Peter == Invisible || Paul == Invisible)
                return Invisible;
            else if (Peter == Guru || Paul == Guru)
                return Guru;
            else if (Peter == Expert || Paul == Expert)
                return Expert;
            else
                return Beginner;
        }

        /**
         * Tests Cacheability
         */
        inline bool IsCacheable(ECachingMode CachingMode)
        {
            return (CachingMode != NoCache);
        }

        /**
         * Computes which CachingMode results from a combination
         */
        inline ECachingMode Combine(ECachingMode Peter, ECachingMode Paul)
        {
            assert(Peter != _UndefinedCachingMode);
            assert(Paul != _UndefinedCachingMode);

            if (Peter == NoCache || Paul == NoCache)
                return NoCache;
            else if (Peter == WriteAround || Paul == WriteAround)
                return WriteAround;
            else
                return WriteThrough;
        }

        /**
         * \}
         */

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif
