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

#ifndef FLIR_SPINNAKER_IIMAGE_H
#define FLIR_SPINNAKER_IIMAGE_H

#include "SpinGenApi/GCTypes.h"
#include "SpinGenApi/GCString.h"
#include "SpinnakerPlatform.h"
#include "CameraDefs.h"
#include "SpinnakerDefs.h"
#include "ChunkData.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4996)
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace Spinnaker
{
    class ImageStatistics;
    class ImagePtr;
    enum PixelFormatEnums;

    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /*@{*/

    /**
     *  @defgroup IImage_h IImage Class
     */
    /*@{*/

    /**
     * @brief The interface file for Image.
     */

    class SPINNAKER_API IImage
    {
      public:
        virtual ~IImage(){};

        virtual ColorProcessingAlgorithm GetColorProcessing() const = 0;
        virtual ImagePtr Convert(PixelFormatEnums format, ColorProcessingAlgorithm colorAlgorithm = DEFAULT) const = 0;
        virtual void Convert(
            ImagePtr destinationImage,
            PixelFormatEnums format,
            ColorProcessingAlgorithm colorAlgorithm = DEFAULT) const = 0;
        virtual void ResetImage(
            size_t width,
            size_t height,
            size_t offsetX,
            size_t offsetY,
            PixelFormatEnums pixelFormat) = 0;
        virtual void ResetImage(
            size_t width,
            size_t height,
            size_t offsetX,
            size_t offsetY,
            PixelFormatEnums pixelFormat,
            void* pData) = 0;
        virtual void Release() = 0;
        virtual uint64_t GetID() const = 0;
        virtual void* GetData() const = 0;
        virtual void* GetPrivateData() const = 0;
        virtual float GetDataAbsoluteMax() const = 0;
        virtual float GetDataAbsoluteMin() const = 0;
        virtual size_t GetBufferSize() const = 0;
        virtual void DeepCopy(const ImagePtr pSrcImage) = 0;
        virtual size_t GetWidth() const = 0;
        virtual size_t GetHeight() const = 0;
        virtual size_t GetStride() const = 0;
        virtual size_t GetBitsPerPixel() const = 0;
        virtual size_t GetNumChannels() const = 0;
        virtual size_t GetXOffset() const = 0;
        virtual size_t GetYOffset() const = 0;
        virtual size_t GetXPadding() const = 0;
        virtual size_t GetYPadding() const = 0;
        virtual uint64_t GetFrameID() const = 0;
        virtual size_t GetPayloadType() const = 0;
        virtual PayloadTypeInfoIDs GetTLPayloadType() const = 0;
        virtual uint64_t GetTLPixelFormat() const = 0;
        virtual PixelFormatNamespaceID GetTLPixelFormatNamespace() const = 0;
        virtual GenICam::gcstring GetPixelFormatName() const = 0;
        virtual PixelFormatEnums GetPixelFormat() const = 0;
        virtual PixelFormatIntType GetPixelFormatIntType() const = 0;
        virtual bool IsIncomplete() const = 0;
        virtual size_t GetValidPayloadSize() const = 0;
        virtual uint64_t GetChunkLayoutId() const = 0;
        virtual uint64_t GetTimeStamp() const = 0;
        virtual void Save(const char* pFilename, ImageFileFormat format = FROM_FILE_EXT) = 0;
        virtual void Save(const char* pFilename, PNGOption& pOption) = 0;
        virtual void Save(const char* pFilename, PPMOption& pOption) = 0;
        virtual void Save(const char* pFilename, PGMOption& pOption) = 0;
        virtual void Save(const char* pFilename, TIFFOption& pOption) = 0;
        virtual void Save(const char* pFilename, JPEGOption& pOption) = 0;
        virtual void Save(const char* pFilename, JPG2Option& pOption) = 0;
        virtual void Save(const char* pFilename, BMPOption& pOption) = 0;
        virtual const ChunkData& GetChunkData() const = 0;
        virtual void CalculateStatistics(ImageStatistics& pStatistics) = 0;
        virtual bool HasCRC() const = 0;
        virtual bool CheckCRC() const = 0;
        virtual size_t GetImageSize() const = 0;
        virtual bool IsInUse() = 0;
        virtual ImageStatus GetImageStatus() const = 0;

      protected:
        friend class Stream;

        IImage(){};
        struct ImageData;
        virtual ImageData* GetImageData() const = 0;
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#ifdef _MSC_VER
#pragma warning(pop)
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#endif // FLIR_SPINNAKER_IIMAGE_H