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

#ifndef SPINNAKER_GENAPI_PORTNODE_H
#define SPINNAKER_GENAPI_PORTNODE_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "Base.h"
#include "INode.h"
#include "IPort.h"
#include "GCString.h"
#include "Node.h"
#include "Pointer.h"

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
         *  @defgroup PortNode_h PortNode Class
         */
        /*@{*/

        //*************************************************************
        // IValue interface
        //*************************************************************

        /**
         * @brief Interface for value properties
         */
        class SPINNAKER_API PortNode : virtual public IPortConstruct,
                                       virtual public IChunkPort,
                                       virtual public IPortRecorder,
                                       virtual public Node
        {
          public:
            struct NodeImpl;
            /**
             * Constructor
             */
            PortNode();

            /**
             * constructor with GenICam IValue
             */
            PortNode(std::shared_ptr<Node::NodeImpl> pValue);

            /**
             * Destructor
             */
            ~PortNode();

            //-------------------------------------------------------------
            // IPort implementation
            //-------------------------------------------------------------

            /**
             * Reads a chunk of bytes from the port
             */
            virtual void Read(void* pBuffer, int64_t Address, int64_t Length);

            /**
             * Writes a chunk of bytes to the port
             */
            virtual void Write(const void* pBuffer, int64_t Address, int64_t Length);

            //-------------------------------------------------------------
            // IPortConstruct implementation
            //-------------------------------------------------------------

            /**
             * Sets pointer the real port implementation; this function may called only once
             */
            void SetPortImpl(IPort* pPort);

            /**
             * Determines if the port adapter must perform an endianess swap
             */
            virtual EYesNo GetSwapEndianess();

            //-------------------------------------------------------------
            // IChunkPort implementation
            //-------------------------------------------------------------

            /**
             * Get the Id of the chunk the port should be attached to
             */
            virtual Spinnaker::GenICam::gcstring GetChunkID() const;

            /**
             * Indicates if the chunk a adapter must hold a cached version of the chunk data
             */
            virtual EYesNo CacheChunkData() const;

            //-------------------------------------------------------------
            // IPortRecorder implementation
            //-------------------------------------------------------------

            /**
             * Starts logging all WriteRegister commands to a list
             */
            virtual void StartRecording(IPortWriteList* pPortRecorder);

            /**
             * Stops recording
             */
            virtual void StopRecording();

            //-------------------------------------------------------------
            // IPortReplay implementation
            //-------------------------------------------------------------

            /**
             * Sends the commands to the camera.
             */
            /*! The default implementation just walks the list and issues each command
                using the WriteRegister method. Depending on the capabilities of
                the transport layer the implementation can however use a special command
                which sends all register write commands as one package.
            */
            virtual void Replay(IPortWriteList* pPortRecorder, bool Invalidate = true);

            /**
             * overload SetReference for Value
             */
            virtual void SetReference(INode* pBase);

            using Node::SetReference;

            /**
             * overload SetReference for Value
             */
            virtual void SetReference(IPort* pBase);

            /**
             * overload SetReference for Value
             */
            virtual void SetReference(IChunkPort* pBase);

            std::shared_ptr<Node::NodeImpl> GetPortHandle()
            {
                return m_pPort;
            }

          private:
            std::shared_ptr<Node::NodeImpl> m_pPort;
        };

        typedef PortNode CPortRef;

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // ifndef SPINNAKER_GENAPI_PORTNODE_H
