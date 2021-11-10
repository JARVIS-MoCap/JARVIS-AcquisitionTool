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

#ifndef SPINNAKER_GENAPI_CHUNKADAPTER_H
#define SPINNAKER_GENAPI_CHUNKADAPTER_H

#include "Types.h"
#include "INodeMap.h"

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         * @brief Delivers information about the attached chunks and nodes.
         */
        typedef struct AttachStatistics_t
        {
            /**
             * Number of chunk ports found in the node map.
             */
            int NumChunkPorts;

            /**
             * Number of chunks found in the buffer.
             */
            int NumChunks;

            /**
             * Number of chunks from the buffer attached to a chunk port.
             */
            int NumAttachedChunks;
        } AttachStatistics_t;

        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup ChunkAdapter_h ChunkAdapter Class
         */
        /*@{*/

        /**
         * @brief Connects a chunked buffer to a node map
         */
        class SPINNAKER_API CChunkAdapter
        {

          public:
            /**
             * Destructor.
             */
            virtual ~CChunkAdapter();

            /**
             * Attaches to a node map and retrieves the chunk ports.
             */
            void AttachNodeMap(INodeMap* pNodeMap);

            /**
             * Detaches from the node map.
             */
            void DetachNodeMap();

            /**
             * Checks if a buffer contains chunks in a known format.
             */
            // Implement that for a specific buffer layout
            virtual bool CheckBufferLayout(uint8_t* pBuffer, int64_t BufferLength) = 0;

            /**
             * Attaches a buffer to the matching ChunkPort.
             */
            // Implement that for a specific buffer layout
            virtual void AttachBuffer(
                uint8_t* pBuffer,
                int64_t BufferLength,
                AttachStatistics_t* pAttachStatistics = NULL) = 0;

            /**
             * Detaches a buffer.
             */
            void DetachBuffer();

            /**
             * Updates the base address of the buffer.
             */
            void UpdateBuffer(uint8_t* pBaseAddress);

            /**
             * Clears the chunk caches.
             */
            void ClearCaches();

          protected:
            /**
             * Serves as default constructor.
             */
            CChunkAdapter(INodeMap* pNodeMap = NULL, int64_t MaxChunkCacheSize = -1);

            void* m_pChunkAdapter;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // SPINNAKER_GENAPI_CHUNKADAPTER_H
