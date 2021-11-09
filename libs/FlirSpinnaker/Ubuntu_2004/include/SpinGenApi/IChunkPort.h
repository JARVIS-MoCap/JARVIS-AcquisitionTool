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

#ifndef SPINNAKER_GENAPI_ICHUNKPORT_H
#define SPINNAKER_GENAPI_ICHUNKPORT_H

#include "GCString.h"
#include "SpinnakerPlatform.h"
#include "Types.h"
#include "IPort.h"

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
         *  @defgroup IChunkPort_h IChunkPort Interface
         */
        /*@{*/

        //*************************************************************
        // IChunkPort interface
        //*************************************************************

        /**
         * Address of a int64_t pseudo register containing the base address of the chunk (MAX_INT64)
         */
#define CHUNK_BASE_ADDRESS_REGISTER GC_INT64_MAX

        /**
         * Lenght of the CHUNK_BASE_ADDRESS_REGISTER pseudo register
         */
#define CHUNK_BASE_ADDRESS_REGISTER_LEN 8

        /**
         * Address of a int64_t pseudo register containing the length of the chunk
         */
#ifndef CHUNK_LENGTH_REGISTER
#define CHUNK_LENGTH_REGISTER (GC_INT64_MAX - 15)
#endif

        /**
         * Lenght of the CHUNK_LENGTH_REGISTER pseudo register
         */
#define CHUNK_LENGTH_REGISTER_LEN 8

        /**
         * @brief Interface for ports attached to a chunk
         */
        interface SPINNAKER_API_ABSTRACT IChunkPort : virtual public IPort
        {
            /**
             * Get the Id of the chunk the port should be attached to
             */
            virtual GenICam::gcstring GetChunkID() const = 0;

            /**
             * Indicates if the chunk a adapter must hold a cached version of the chunk data
             */
            virtual EYesNo CacheChunkData() const = 0;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // ifndef SPINNAKER_GENAPI_ICHUNKPORT_H
