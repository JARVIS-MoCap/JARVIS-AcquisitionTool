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

#ifndef SPINNAKER_GENAPI_CHUNKADAPTERU3V_H
#define SPINNAKER_GENAPI_CHUNKADAPTERU3V_H

#include "ChunkAdapter.h"

namespace Spinnaker
{
    namespace GenApi
    {
        // Declaration of USB3 Vision Chunk trailer

        // make sure everything is properly packed
#pragma pack(push, 1)

        /**
         * @brief header of a GVCP request packet
         */
        typedef struct U3V_CHUNK_TRAILER
        {
            uint32_t ChunkID;
            uint32_t ChunkLength;
        } U3V_CHUNK_TRAILER;

        // restore the previous packing
#pragma pack(pop)

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup ChunkAdapterU3V_h ChunkAdapterU3V Class
         */
        /*@{*/

        /**
         * @brief Connects a chunked U3V buffer to a node map.
         */
        class SPINNAKER_API CChunkAdapterU3V : public CChunkAdapter
        {

          public:
            /**
             * Constructor.
             */
            CChunkAdapterU3V(INodeMap* pNodeMap = NULL, int64_t MaxChunkCacheSize = -1);

            /**
             * Destructor.
             */
            virtual ~CChunkAdapterU3V();

            /**
             * Checks if a buffer contains chunks in a known format.
             */
            virtual bool CheckBufferLayout(uint8_t* pBuffer, int64_t BufferLength);

            /**
             * Attaches a buffer to the matching ChunkPort.
             */
            virtual void AttachBuffer(
                uint8_t* pBuffer,
                int64_t BufferLength,
                AttachStatistics_t* pAttachStatistics = NULL);
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // SPINNAKER_GENAPI_CHUNKADAPTERU3V_H
