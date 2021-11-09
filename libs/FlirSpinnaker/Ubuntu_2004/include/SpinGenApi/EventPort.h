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

#ifndef SPINNAKER_GENAPI_EVENTPORT_H
#define SPINNAKER_GENAPI_EVENTPORT_H

#include "Types.h"
#include "INodeMap.h"
#include "INode.h"
#include "IPortConstruct.h"
#include "Pointer.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4068) // unknown pragma; refers to BullsEyeCoverage
#pragma warning(disable : 4251) // XXX needs to have dll-interface to be used by clients of class YYY
#endif

namespace Spinnaker
{
    namespace GenApi
    {

        class PortAdapter;

        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup EventPort_h EventPort Class
         */
        /*@{*/

        /**
         * @brief Port attachable to an event
         */
        class SPINNAKER_API CEventPort : public IPortConstruct
        {

          public:
            /**
             * Constructor; can attach to a node
             */
            CEventPort(INode* pNode = NULL);

            /**
             * Destructor; detaches from the port
             */
            ~CEventPort();

            //-------------------------------------------------------------
            // IPortConstruct implementation
            //-------------------------------------------------------------

            /**
             *    Get    the    access mode    of the node
             */
            virtual EAccessMode GetAccessMode() const;

            /**
             * Get the type of the main interface of a node
             */
            virtual EInterfaceType GetPrincipalInterfaceType() const;

            /**
             * Reads a chunk of bytes from the port
             */
            virtual void Read(void* pBuffer, int64_t Address, int64_t Length);

            /**
             * Writes a chunk of bytes to the port
             */
            virtual void Write(const void* pBuffer, int64_t Address, int64_t Length);

            /**
             * Called from the port node to give the chunk port a pointer to itself
             */
            virtual void SetPortImpl(::Spinnaker::GenApi::IPort* pPort);

            /**
             * Determines if the port adapter must perform an endianness swap
             */
#ifdef _WIN32
#pragma BullseyeCoverage off
#endif
            virtual EYesNo GetSwapEndianess()
            {
                return No;
            }
#ifdef _WIN32
#pragma BullseyeCoverage on
#endif

            //---------------------------------------------------------------
            // Implementation
            //---------------------------------------------------------------

            // Invalidates the chunk port node
            void InvalidateNode();

            //-------------------------------------------------------------
            // Initializing
            //-------------------------------------------------------------

            /**
             * Attaches to the Node
             */
            bool AttachNode(::Spinnaker::GenApi::INode* pNode);

            /**
             * Detaches from the Node
             */
            void DetachNode();

            /**
             * Gets the EventID length
             */
            int GetEventIDLength();

            /**
             * Checks if a EventID matches
             */
            bool CheckEventID(uint8_t* pEventIDBuffer, int EventIDLength);

            /**
             * Checks if a EventID matches, version using uint64_t ID representation
             */
            bool CheckEventID(uint64_t EventID);

            /**
             * Attaches the an Event to the EventPort
             */
            void AttachEvent(uint8_t* pBaseAddress, int64_t Length);

            /**
             * Detaches the Event from the EventPort
             */
            void DetachEvent();

          protected:
            CNodePtr m_pNode;

            std::shared_ptr<PortAdapter> m_pPortAdapter;

            void* m_pEventPort;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // SPINNAKER_GENAPI_EVENTPORT_H
