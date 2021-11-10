//=============================================================================
// Copyright (c) 2001-2020 FLIR Systems, Inc. All Rights Reserved.
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

#ifndef FLIR_SPINNAKER_ISTREAM_H
#define FLIR_SPINNAKER_ISTREAM_H

#include "ImageEventHandler.h"
#include "EventProcessor.h"

namespace Spinnaker
{
    class Port;
    class TransportLayerStream;
    class ImagePtr;
    class IGenTLStream;

    class IDataStream
    {

      public:
        virtual ~IDataStream(){};
        virtual StreamTypeEnum GetStreamType() const = 0;

        virtual void AnnounceImage(size_t size) = 0;
        virtual void AnnounceImage(size_t size, void* pPrivate) = 0;
        virtual void AnnounceImage(size_t size, void* pData, void* pPrivate) = 0;
        virtual void RevokeImages() = 0;
        virtual void StartStream(const unsigned int stream_index = 0) = 0;
        virtual void StopStream() = 0;
        virtual ImagePtr GetNextImage(uint64_t grabTimeout) = 0;
        virtual ImagePtr GetNextImageInternal(void** ppPrivate, uint64_t grabTimeout) = 0;
        virtual void ReleaseImage(const uint64_t imageID) = 0;
        virtual void FlushQueueAllDiscard() = 0;
        virtual bool IsStreaming() = 0;
        virtual void KillBufferEvent() = 0;
        virtual bool IsImageInUse(const uint64_t imageID) = 0;
        virtual unsigned int GetNumImagesInUse() const = 0;

        virtual size_t GetStreamInfoSizeType(GenTL::STREAM_INFO_CMD iInfoCmd) = 0;
        virtual bool GetStreamInfoBool8Type(GenTL::STREAM_INFO_CMD iInfoCmd) = 0;

        // Buffer
        virtual void* GetBufferInfoPtrType(GenTL::BUFFER_HANDLE hBuffer, GenTL::BUFFER_INFO_CMD iInfoCmd) = 0;
        virtual size_t GetBufferInfoSizeType(GenTL::BUFFER_HANDLE hBuffer, GenTL::BUFFER_INFO_CMD iInfoCmd) = 0;
        virtual uint64_t GetBufferInfoUInt64Type(GenTL::BUFFER_HANDLE hBuffer, GenTL::BUFFER_INFO_CMD iInfoCmd) = 0;
        virtual bool GetBufferInfoBool8Type(GenTL::BUFFER_HANDLE hBuffer, GenTL::BUFFER_INFO_CMD iInfoCmd) = 0;

        // Events
        virtual void RegisterImageEventHandler(
            IImageEventHandler& imageEventHandler,
            EventPollingOptions pollingOption) = 0;
        virtual void UnregisterImageEventHandler(IImageEventHandler& imageEventHandler) = 0;
        virtual void WaitOnImageEvent(uint64_t timeout) = 0;

        // Chunks
        virtual void InitChunkAdapter(GenApi::INodeMap& nodemap) = 0;
        virtual void CleanupChunkAdapter() = 0;
        virtual GenTL::GC_ERROR GetBufferChunkData(
            GenTL::BUFFER_HANDLE hBuffer,
            GenTL::SINGLE_CHUNK_DATA* pChunkData,
            size_t* piNumChunks) = 0;
        virtual void AttachBuffer(uint8_t* pBuffer, GenApi::SingleChunkData_t* ChunkData, int64_t NumChunks) = 0;
        virtual bool IsCRCCheckEnabled() const = 0;

        virtual GenApi::INodeMap& GetNodeMap() const = 0;
        virtual GenApi::INodeMap* GetDeviceNodeMap() const = 0;

        virtual Port& GetPort() const = 0;

        virtual const TransportLayerStream& TransportLayerStreamInfo() const = 0;

      protected:
        IDataStream(){};
    };
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_ISTREAM_H