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

#ifndef SPINNAKER_GENAPI_INODEMAP_H
#define SPINNAKER_GENAPI_INODEMAP_H

#include "GCString.h"
#include "INode.h"
#include "IPort.h"
#include "Synch.h"
#include "Container.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4251) // XXX needs to have dll-interface to be used by clients of class YYY
#endif

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiInterfaces Spinnaker GenApi Interfaces
         */
        /*@{*/

        /**
         *  @defgroup INodeMap_h INodeMap Interface
         */
        /*@{*/

        //*************************************************************
        // INodeMap interface
        //*************************************************************

        /**
         * @brief Interface to access the node map
         */
        interface SPINNAKER_API_ABSTRACT INodeMap
        {
            /**
             * Retrieves all nodes in the node map
             */
            virtual void GetNodes(NodeList_t & Nodes) const = 0;

            /**
             * Retrieves the node from the central map by Name
             */
            virtual INode* GetNode(const GenICam::gcstring& Name) const = 0;

            /**
             * Invalidates all nodes
             */
            virtual void InvalidateNodes() const = 0;

            /**
             * Connects a port to a port node with given name
             */
            virtual bool Connect(IPort * pPort, const GenICam::gcstring& PortName) const = 0;

            /**
             * Connects a port to the standard port "Device"
             */
            virtual bool Connect(IPort * pPort) const = 0;

            /**
             * Get device name
             * The device name identifies a device instance, e.g. for debugging purposes.
             * The default is "Device".
             */
            virtual GenICam::gcstring GetDeviceName() = 0;

            /**
             * Fires nodes which have a polling time
             */
            virtual void Poll(int64_t ElapsedTime) = 0;

            /**
             * Returns the lock which guards the node map
             */
            virtual CLock& GetLock() const = 0;

            /**
             * Get the number of nodes in the map
             */
            virtual uint64_t GetNumNodes() const = 0;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // ifndef SPINNAKER_GENAPI_INODEMAP_H
