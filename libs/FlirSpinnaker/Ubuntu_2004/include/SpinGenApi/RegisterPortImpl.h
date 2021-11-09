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

#ifndef SPINNAKER_GENAPI_REGISTERPORTIMPL_H
#define SPINNAKER_GENAPI_REGISTERPORTIMPL_H

#include "PortImpl.h"
#include "Log.h"
#include "Compatibility.h"

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup RegisterPortImpl_h RegisterPortImpl Class
         */
        /*@{*/

        //*************************************************************
        // CRegisterPortImpl class
        //*************************************************************

        /**
         * @brief Standard implementation for a port using a register based transport layer
         */
        class CRegisterPortImpl : public CPortImpl
        {
          public:
            /**
             * Constructor
             */
            CRegisterPortImpl(int MaxNumQuadlets = 1, bool TransportLayerSwapsEndianess = false){};

            /**
             * Destructor
             */
            virtual ~CRegisterPortImpl(){};

            //---------------------------------------------------------------
            // IBase ==> You need to override this method
            //---------------------------------------------------------------

            /**
             * Get the access mode of the node
             */
            /*!
             * Driver closed => NI, Driver open => RW, analyzing a struct, RO
             */
            virtual EAccessMode GetAccessMode() const = 0;

            //---------------------------------------------------------------
            // IRegisterPort ==> You need to override these methods
            //---------------------------------------------------------------

            /**
             * Reads an array of quadlets from the port
             */
            virtual void ReadRegister(uint32_t* pRegisters, int64_t Address, int64_t Length) = 0;

            /**
             * Writes an array of quadlets to the port
             */
            virtual void WriteRegister(const uint32_t* pRegisters, int64_t Address, int64_t Length) = 0;

            //---------------------------------------------------------------
            // IPort
            //---------------------------------------------------------------

            /**
             * Reads a chunk of bytes from the port
             */
            virtual void Read(void* pBuffer, int64_t Address, int64_t Length){};

            /**
             * Writes a chunk of bytes to the port
             */
            virtual void Write(const void* pBuffer, int64_t Address, int64_t Length){};

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
            };
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // ifndef SPINNAKER_GENAPI_REGISTERPORTIMPL_H
