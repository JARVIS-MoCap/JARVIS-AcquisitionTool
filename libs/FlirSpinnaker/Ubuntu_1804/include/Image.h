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

#ifndef FLIR_SPINNAKER_IMAGE_H
#define FLIR_SPINNAKER_IMAGE_H

#include "Interface/IImage.h"

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

    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /*@{*/

    /**
     *  @defgroup Image_h Image Class
     */
    /*@{*/

    /**
     * @brief The image object class.
     */

    class SPINNAKER_API Image : public IImage
    {

      public:
        /**
         * Create an image object.
         */
        static ImagePtr Create();

        /**
         * Create an image object that is a deep copy of the input image.
         *
         * @param image The input image to copy
         */
        static ImagePtr Create(const ImagePtr image);

        /**
         * Create an image object with the specified parameters.
         *
         * @param width The image width in pixels
         * @param height The image height in pixels
         * @param offsetX The image X offset
         * @param offsetY The image Y offset
         * @param pixelFormat The image pixel format
         * @param pData The image data
         */
        static ImagePtr Create(
            size_t width,
            size_t height,
            size_t offsetX,
            size_t offsetY,
            Spinnaker::PixelFormatEnums pixelFormat,
            void* pData);

        /**
         * Virtual destructor.
         */
        virtual ~Image();

        /**
         * Sets the default color processing algorithm.  This method will be
         * used for any image with the DEFAULT algorithm set. The method used
         * is determined at the time of the Convert() call, therefore the most
         * recent execution of this function will take precedence. The default
         * setting is shared within the current process.
         *
         * @param colorAlgorithm The color processing algorithm to set.
         *
         * @see GetDefaultColorProcessing()
         */
        static void SetDefaultColorProcessing(ColorProcessingAlgorithm colorAlgorithm);

        /**
         * Gets the default color processing algorithm.
         *
         * @see SetDefaultColorProcessing()
         *
         * @return The default color processing algorithm.
         */
        static ColorProcessingAlgorithm GetDefaultColorProcessing();

        /**
         * Gets the color algorithm used to produce the image.
         *
         * @see Convert()
         *
         * @return The color processing algorithm used to produce the image.
         */
        ColorProcessingAlgorithm GetColorProcessing() const;

        /**
         * Converts the current image buffer to the specified output pixel format and
         * stores the result in the specified image. The destination image
         * does not need to be configured in any way before the call is made.
         *
         * @see PixelFormatEnums
         *
         * @param format Output format of the converted image.
         * @param colorAlgorithm Optional color processing algorithm for producing the converted image
         * @return The converted image.
         */
        ImagePtr Convert(Spinnaker::PixelFormatEnums format, ColorProcessingAlgorithm colorAlgorithm = DEFAULT) const;

        /**
         * Converts the current image buffer to the specified output pixel format and
         * stores the result in the specified destination image. The destination image
         * buffer size must be sufficient to store the converted image data.
         *
         * @see Create(size_t width, size_t height, size_t offsetX, size_t offsetY, Spinnaker::PixelFormatEnums
         * pixelFormat, void* pData)
         *
         * @param destinationImage Destination image where the converted output result will be stored.
         * @param format Output format of the converted image.
         * @param colorAlgorithm Optional color processing algorithm for producing the converted image.
         */
        void Convert(
            ImagePtr destinationImage,
            Spinnaker::PixelFormatEnums format,
            ColorProcessingAlgorithm colorAlgorithm = DEFAULT) const;

        /**
         * Sets new dimensions of the image object and allocates memory.
         *
         * @param width The width of image in pixels to set.
         * @param height The height of image in pixels to set.
         * @param offsetX The x offset in pixels to set.
         * @param offsetY The y offset in pixels  to set.
         * @param pixelFormat Pixel format to set.
         */
        void ResetImage(
            size_t width,
            size_t height,
            size_t offsetX,
            size_t offsetY,
            Spinnaker::PixelFormatEnums pixelFormat);

        /**
         * Sets new dimensions of the image object.
         *
         * @param width The width of image in pixels to set.
         * @param height The height of image in pixels to set.
         * @param offsetX The x offset in pixels to set.
         * @param offsetY The y offset in pixels to set.
         * @param pixelFormat Pixel format to set.
         * @param pData Pointer to the image buffer.
         */
        void ResetImage(
            size_t width,
            size_t height,
            size_t offsetX,
            size_t offsetY,
            Spinnaker::PixelFormatEnums pixelFormat,
            void* pData);

        /*
         * Releases an image that was acquired by calling camera->GetNextImage().
         *
         * @see Init()
         * @see CameraBase::GetNextImage( grabTimeout )
         */
        void Release();

        /**
         * Gets a unique ID for this image.  Each image in a steam will have
         * a unique ID to help identify it.
         *
         * @return The 64 bit unique id for this image.
         */
        uint64_t GetID() const;

        /**
         * Gets a pointer to the data associated with the image. This function
         * is considered unsafe. The pointer returned could be invalidated if
         * the buffer is released. The pointer may also be
         * invalidated if the Image object is passed to
         * Image::Release().
         *
         * @return A pointer to the image data.
         */
        void* GetData() const;

        /**
         * Get the value for which no image data will exceed.
         *
         * @return the maximim theoretical image data value
         */
        float GetDataAbsoluteMax() const;

        /**
         * Get the value for which no image data will be less than
         *
         * @return the minimum theoretical image data value
         */
        float GetDataAbsoluteMin() const;

        /**
         * Gets a pointer to the user passed data associated with the image.
         * This function is considered unsafe. The pointer returned could be
         * invalidated if the buffer is released. The pointer may also be
         * invalidated if the Image object is passed to
         * Image::Release().
         *
         * TODO: no way to set private data for image yet.
         *
         * @return A pointer to the user passed data pointer.
         */
        void* GetPrivateData() const;

        /**
         * Gets the size of the buffer associated with the image in bytes.
         *
         * @return The size of the buffer, in bytes.
         */
        size_t GetBufferSize() const;

        /**
         * Performs a deep copy of the Image. After this operation, the image
         * contents and member variables will be the same. The Images will not
         * share a buffer. The Image's current buffer will not be released.
         *
         * @param pSrcImage The Image to copy the data from.
         */
        void DeepCopy(const ImagePtr pSrcImage);

        /**
         * Gets the width of the image in pixels.  This information is retrieved
         * from the Transport Layer image format headers.  It is retrieved on
         * a per image basis.
         *
         * @return The width in pixels.
         */
        size_t GetWidth() const;

        /**
         * Gets the height of the image in pixels. This information is retrieved
         * from the Transport Layer Image format headers.  It is retrieved on
         * a per image basis.
         *
         * @return The height in pixels.
         */
        size_t GetHeight() const;

        /**
         * Gets the stride of the image in bytes.  The stride
         * of an image is how many bytes are in each row.  This information is
         * retrieved  from the Transport Layer Image format headers.  It is
         * retrieved on a per image basis.
         *
         * @return The stride in bytes.
         */
        size_t GetStride() const;

        /**
         * Gets the number of bits used per pixel in the image.  This information is
         * retrieved from the Transport Layer Image format headers.  It is retrieved
         * on a per image basis.
         *
         * @return The number of bits used per pixel.
         */
        size_t GetBitsPerPixel() const;

        /**
         * Gets the number of channels (depth) used in the image.
         * Returns 0 if the number of channels for the given pixel format is unknown.
         *
         * @return The number of channels per pixel.
         */
        size_t GetNumChannels() const;

        /**
         * Gets the ROI x offset in pixels for this image.  This information is
         * retrieved from the Transport Layer Image format headers.  It is retrieved
         * on a per image basis.
         *
         * @return The x offset in pixels.
         */
        size_t GetXOffset() const;

        /**
         * Gets the ROI y offset in pixels for this image.  This information is
         * retrieved from the Transport Layer Image format headers.  It is retrieved
         * on a per image basis.
         *
         * @return The y offset in pixels.
         */
        size_t GetYOffset() const;

        /**
         * Gets the x padding in bytes for this image.  This is the number of bytes at
         * the end of each line to facilitate alignment in buffers. This information is
         * retrieved from the Transport Layer Image format headers.  It is retrieved
         * on a per image basis.
         *
         * @return The x padding in bytes.
         */
        size_t GetXPadding() const;

        /**
         * Gets the y padding in bytes for this image.  This is the number of bytes at
         * the end of each image to facilitate alignment in buffers. This information is
         * retrieved from the Transport Layer Image format headers.  It is retrieved
         * on a per image basis.
         *
         * @return The y padding in bytes.
         */
        size_t GetYPadding() const;

        /**
         * Gets the frame ID for this image.
         *
         * @return The frame ID.
         */
        uint64_t GetFrameID() const;

        /**
         * Gets the payload type that was transmitted.  This is a device types specific
         * value that identifies how the image was transmitted. This information is
         * retrieved from the Transport Layer Image format headers.  It is retrieved
         * on a per image basis.
         *
         * @return Device types specific payload type.
         */
        size_t GetPayloadType() const;

        /**
         * Gets the GenTL specific payload type that was transmitted.  This is a Transport Layer specific
         * value that identifies how the image was transmitted. This information is
         * retrieved from the Transport Layer Image format headers.  It is retrieved
         * on a per image basis.
         *
         * @return Transport Layer specific payload type.
         */
        PayloadTypeInfoIDs GetTLPayloadType() const;

        /**
         * Gets the pixel format of the image.  This is a Transport Layer specific
         * pixel format that identifies how the pixels in the image should be
         * interpreted. To understand how to interpret this value it is necessary to know
         * what the transport layer namespace is. This can be retrieved through
         * a call to GetTLPixelFormatNamespace().  This information is retrieved
         * from the Transport Layer Image format headers.  It is retrieved on a per
         * image basis.
         *
         * @see GetTLPixelFormatNamespace()
         *
         * @return Transport Layer specific pixel format.
         */
        uint64_t GetTLPixelFormat() const;

        /**
         * Returns an enum value that represents the namespace in which this
         * image's TL specific pixel format resides.  This information is
         * important to properly interpret the value returned by GetTLPixelFormat()
         *
         * @see GetTLPixelFormat()
         *
         * @return enum value representing the PixelFormatNamespace.
         */
        PixelFormatNamespaceID GetTLPixelFormatNamespace() const;

        /**
         * Returns a string value that represents this image's pixel format. The string
         * is a valid SFNC name that maps to the underlying TL specific pixel format.
         * This is the most generic way to identify the pixel format of the image.
         *
         * @return string value representing the PixelFormat.
         */
        GenICam::gcstring GetPixelFormatName() const;

        /**
         * Returns an enum value that represents the pixel format of this image.
         * The enum can be used with the easy access GenICam features available
         * through the Camera.h header file.  This easy access enum can also be
         * used in the Convert() function.
         *
         * @see Convert()
         *
         * @return enum value representing the PixelFormat.
         */
        Spinnaker::PixelFormatEnums GetPixelFormat() const;

        /**
         * Returns an enum value that represents the integer type used in the
         * pixel format of this image.
         *
         * @return enum value representing the integer type used.
         */
        Spinnaker::PixelFormatIntType GetPixelFormatIntType() const;

        /**
         * Returns a boolean value indicating if this image was incomplete. An
         * image is marked as incomplete if the transport layer received less data
         * then it requested.
         *
         * @return Returns true if image is incomplete, false otherwise.
         */
        bool IsIncomplete() const;

        /**
         * Returns the size of valid data in the image payload.  This is the actual amount
         * of data read from the device. A user created image has a payload size of zero.
         * GetBufferSize() returns the total size of bytes allocated for the image.
         *
         * @see GetBufferSize()
         *
         * @return size_t value representing valid payload.
         */
        size_t GetValidPayloadSize() const;

        /**
         * Returns the id of the chunk data layout.
         *
         * @return uint64_t value representing the id of the chunk data layout.
         */
        uint64_t GetChunkLayoutId() const;

        /**
         * Gets the time stamp for the image in nanoseconds.
         *
         * @return The time stamp of the image.
         */
        uint64_t GetTimeStamp() const;

        /**
         * Saves the image to the specified file name with the file format
         * specified.
         *
         * @param pFilename Filename to save image with.
         * @param format File format to save in.
         */
        void Save(const char* pFilename, ImageFileFormat format = FROM_FILE_EXT);

        /**
         * Saves the image to the specified file name with the options specified.
         *
         * @param pFilename Filename to save image with.
         * @param pOption Options to use while saving image.
         */
        void Save(const char* pFilename, PNGOption& pOption);

        /**
         * Saves the image to the specified file name with the options specified.
         *
         * @param pFilename Filename to save image with.
         * @param pOption Options to use while saving image.
         */
        void Save(const char* pFilename, PPMOption& pOption);

        /**
         * Saves the image to the specified file name with the options specified.
         *
         * @param pFilename Filename to save image with.
         * @param pOption Options to use while saving image.
         */
        void Save(const char* pFilename, PGMOption& pOption);

        /**
         * Saves the image to the specified file name with the options specified.
         *
         * @param pFilename Filename to save image with.
         * @param pOption Options to use while saving image.
         */
        void Save(const char* pFilename, TIFFOption& pOption);

        /**
         * Saves the image to the specified file name with the options specified.
         *
         * @param pFilename Filename to save image with.
         * @param pOption Options to use while saving image.
         */
        void Save(const char* pFilename, JPEGOption& pOption);

        /**
         * Saves the image to the specified file name with the options specified.
         *
         * @param pFilename Filename to save image with.
         * @param pOption Options to use while saving image.
         */
        void Save(const char* pFilename, JPG2Option& pOption);

        /**
         * Saves the image to the specified file name with the options specified.
         *
         * @param pFilename Filename to save image with.
         * @param pOption Options to use while saving image.
         */
        void Save(const char* pFilename, BMPOption& pOption);

        /**
         * Returns a pointer to a chunk data interface.  No ownership is transfered,
         * the chunk data interface reference is valid until Image::Release()
         * is called on this image.
         *
         * @return ChunkData interface that provides access to image chunks.
         */
        const ChunkData& GetChunkData() const;

        /**
         * Retrieves a number of pixel statistics for an image including
         * a histogram array of the range of pixel values.
         *
         * @param pStatistics The statistics of an image.
         */
        void CalculateStatistics(ImageStatistics& pStatistics);

        /**
         * Checks if the image contains ImageCRC checksum from chunk data
         *
         * @return Returns true if image contains ImageCRC checksum from chunk data and false otherwise.
         */
        bool HasCRC() const;

        /**
         * Checks if the computed checksum matches with chunk data's ImageCRC
         *
         * @return Returns true if computed checksum matches with the chunk data's CRC and false otherwise.
         */
        bool CheckCRC() const;

        /**
         * Returns the size of the image
         *
         * @return The image size in bytes.
         */
        size_t GetImageSize() const;

        /**
         * Returns true if the image is still in use by the stream
         *
         * @return Returns true if the image is in use and false otherwise.
         */
        bool IsInUse();

        /**
         * Returns data integrity status of the image returned from GetNextImage()
         *
         * @return Returns whether image has any data integrity issues.
         */
        ImageStatus GetImageStatus() const;

        /**
         * Returns a string describing the meaning of the status enum
         *
         * @return Returns the meaning of the status enum.
         */
        static const char* GetImageStatusDescription(ImageStatus status);

        /**
         * Returns a boolean value indicating whether this image is compressed.
         *
         * @return Returns true if image is compressed, false otherwise.
         */
        bool IsCompressed() const;

      protected:
        friend class IDataStream;
        friend class Stream;
        friend class ImageConverter;
        friend class ImageFiler;
        friend class ImageStatsCalculator;
        friend class ImageUtilityImpl;
        friend class ImageUtilityPolarizationImpl;

        ImageData* GetImageData() const;

        Image();
        Image(const ImagePtr image);
        Image(size_t width, size_t height, size_t offsetX, size_t offsetY, PixelFormatEnums pixelFormat, void* pData);

        ImagePtr CreateShared() const;
        void DeepCopy(const Image& pSrcImage);
        void Convert(PixelFormatEnums format, Image& pDestImage, ColorProcessingAlgorithm colorAlgorithm = DEFAULT)
            const;

      private:
        ImageData* m_pImageData;
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#ifdef _MSC_VER
#pragma warning(pop)
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#endif // FLIR_SPINNAKER_IMAGE_H