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

#ifndef SPINNAKER_PORTIMPL_H
#define SPINNAKER_PORTIMPL_H

#include "Types.h"
#include "IPortConstruct.h"
#include "IPortRecorder.h"
#include "Pointer.h"

#pragma warning(push)
#pragma warning(                                                                                                       \
    disable : 4251) // enApi::CPortImpl::m_ptrPort' : class 'GenApi::CPointer<T>' needs to have dll-interface
#pragma warning(disable : 4068) // unknown pragma; refers to BullsEyeCoverage

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup PortImpl_h PortImpl Class
         */
        /*@{*/

        //*************************************************************
        // CPortImpl class
        //*************************************************************

        /**
         * @brief Standard implementation for a port
         */
        class SPINNAKER_API CPortImpl : public IPortConstruct, public IPortReplay
        {
          public:
            /**
             * Constructor
             */
            CPortImpl()
            {
            }

            /**
             * Destructor
             */
            virtual ~CPortImpl()
            {
            }

            /*---------------------------------------------------------------*/
            // IBase ==> You need to override this method
            /*---------------------------------------------------------------*/

            /**
             * Get the access mode of the node
             */
            /*!
             * Driver closed => NI, Driver open => RW, analyzing a struct, RO
             */
            virtual EAccessMode GetAccessMode() const = 0;

            /*---------------------------------------------------------------*/
            // IPort ==> You need to override these methods
            /*---------------------------------------------------------------*/

            /**
             * Reads a chunk of bytes from the port
             */
            virtual void Read(void* pBuffer, int64_t Address, int64_t Length) = 0;

            /**
             * Writes a chunk of bytes to the port
             */
            virtual void Write(const void* pBuffer, int64_t Address, int64_t Length) = 0;

            //---------------------------------------------------------------
            // IPortConstruct implementation (without IPort & IBase)
            //---------------------------------------------------------------

            /**
             * Sets pointer the real port implementation; this function may called only once
             */
            virtual void SetPortImpl(IPort* pPort)
            {
                m_ptrPort = pPort;
                assert(m_ptrPort.IsValid());
            }

/**
 * Determines if the port adapter must perform an endianness swap
 */
#pragma BullseyeCoverage off
            virtual EYesNo GetSwapEndianess()
            {
                return No;
            }
#pragma BullseyeCoverage on

            //---------------------------------------------------------------
            // IPortReplay implementation
            //---------------------------------------------------------------

            /**
             * sends the commands to the camera.
             */
            /*! the default implementation just walks the list and issues each command
            using the WriteRegister method. Depending on the capabilities of
            the transport layer the implementation can however use a special command
            which sends all register write commands as one package.
            */
            virtual void Replay(IPortWriteList* pPortRecorder, bool Invalidate = true)
            {
                if (pPortRecorder)
                    pPortRecorder->Replay(this);

                if (Invalidate)
                    InvalidateNode();
            }

            // Invalidate the node
            void InvalidateNode()
            {
                if (m_ptrPort.IsValid())
                    m_ptrPort->InvalidateNode();
            }

          protected:
            /**
             * Pointer to the node holding a reference to this implementation
             */
            CNodePtr m_ptrPort;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#pragma warning(pop)
#endif // ifndef SPINNAKER_PORTIMPL_H
