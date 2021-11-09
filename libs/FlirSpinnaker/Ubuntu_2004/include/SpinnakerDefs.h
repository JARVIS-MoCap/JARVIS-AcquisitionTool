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

#ifndef FLIR_SPINNAKER_DEFS_H
#define FLIR_SPINNAKER_DEFS_H

#include <memory.h>
#include <stdint.h>
#include "SpinnakerPlatform.h"

namespace Spinnaker
{
    /**
     *  @defgroup SpinnakerHeaders Spinnaker Headers
     */

    /*@{*/

    /**
     * @defgroup SpinnakerDefs Spinnaker Definitions
     *
     * Definitions file for Spinnaker.
     */

    /**
     * Timeout values for getting next image, device, or interface event
     */
    const uint64_t EVENT_TIMEOUT_NONE = 0;                      // Do not wait.  GetNextImage will return immediately.
    const uint64_t EVENT_TIMEOUT_INFINITE = 0xFFFFFFFFFFFFFFFF; // Never timeout.  GetNextImage will wait indefinitely.

    /*@{*/

    /**
     * @brief Spinnaker enum definitions.
     */

    /**
     * The error codes used in Spinnaker.  These codes are returned as part of
     * Spinnaker::Exception.  The error codes in the range of -1000 to -1999
     * are reserved for exceptions that map directly to GenTL values.
     * The error codes in the range of -2000 to -2999 are reserved
     * for GenICam related errors.  The error codes in the range of -3000 to -3999
     * are reserved for image processing related errors.
     */
    enum Error
    {
        SPINNAKER_ERR_SUCCESS = 0,
        SPINNAKER_ERR_ERROR = -1001,
        SPINNAKER_ERR_NOT_INITIALIZED = -1002,
        SPINNAKER_ERR_NOT_IMPLEMENTED = -1003,
        SPINNAKER_ERR_RESOURCE_IN_USE = -1004,
        SPINNAKER_ERR_ACCESS_DENIED = -1005,
        SPINNAKER_ERR_INVALID_HANDLE = -1006,
        SPINNAKER_ERR_INVALID_ID = -1007,
        SPINNAKER_ERR_NO_DATA = -1008,
        SPINNAKER_ERR_INVALID_PARAMETER = -1009,
        SPINNAKER_ERR_IO = -1010,
        SPINNAKER_ERR_TIMEOUT = -1011,
        SPINNAKER_ERR_ABORT = -1012,
        SPINNAKER_ERR_INVALID_BUFFER = -1013,
        SPINNAKER_ERR_NOT_AVAILABLE = -1014,
        SPINNAKER_ERR_INVALID_ADDRESS = -1015,
        SPINNAKER_ERR_BUFFER_TOO_SMALL = -1016,
        SPINNAKER_ERR_INVALID_INDEX = -1017,
        SPINNAKER_ERR_PARSING_CHUNK_DATA = -1018,
        SPINNAKER_ERR_INVALID_VALUE = -1019,
        SPINNAKER_ERR_RESOURCE_EXHAUSTED = -1020,
        SPINNAKER_ERR_OUT_OF_MEMORY = -1021,
        SPINNAKER_ERR_BUSY = -1022,

        GENICAM_ERR_INVALID_ARGUMENT = -2001,
        GENICAM_ERR_OUT_OF_RANGE = -2002,
        GENICAM_ERR_PROPERTY = -2003,
        GENICAM_ERR_RUN_TIME = -2004,
        GENICAM_ERR_LOGICAL = -2005,
        GENICAM_ERR_ACCESS = -2006,
        GENICAM_ERR_TIMEOUT = -2007,
        GENICAM_ERR_DYNAMIC_CAST = -2008,
        GENICAM_ERR_GENERIC = -2009,
        GENICAM_ERR_BAD_ALLOCATION = -2010,

        SPINNAKER_ERR_IM_CONVERT = -3001,
        SPINNAKER_ERR_IM_COPY = -3002,
        SPINNAKER_ERR_IM_MALLOC = -3003,
        SPINNAKER_ERR_IM_NOT_SUPPORTED = -3004,
        SPINNAKER_ERR_IM_HISTOGRAM_RANGE = -3005,
        SPINNAKER_ERR_IM_HISTOGRAM_MEAN = -3006,
        SPINNAKER_ERR_IM_MIN_MAX = -3007,
        SPINNAKER_ERR_IM_COLOR_CONVERSION = -3008,
        SPINNAKER_ERR_IM_DECOMPRESSION = -3009,

        SPINNAKER_ERR_CUSTOM_ID = -10000
    };

    /**
     * Event types in Spinnaker.
     *
     * @see EventHandler::GetEventType()
     */
    enum EventType
    {
        SPINNAKER_EVENT_ARRIVAL_REMOVAL, /* Specifically, the device arrival/removal event */
        SPINNAKER_EVENT_DEVICE,
        SPINNAKER_EVENT_DEVICE_SPECIFIC,
        SPINNAKER_EVENT_NEW_BUFFER,
        SPINNAKER_EVENT_LOGGING_EVENT,
        SPINNAKER_EVENT_UNKNOWN,
        SPINNAKER_EVENT_INTERFACE_ARRIVAL_REMOVAL
    };

    /**
     * This enum represents the namespace in which the TL specific pixel format
     * resides.  This enum is returned from a captured image when calling
     * Image::GetTLPixelFormatNamespace().  It can be used to interpret the raw
     * pixel format returned from Image::GetTLPixelFormat().
     *
     * @see Image::GetTLPixelFormat()
     *
     * @see Image::GetTLPixelFormatNamespace()
     */
    enum PixelFormatNamespaceID
    {
        SPINNAKER_PIXELFORMAT_NAMESPACE_UNKNOWN = 0,    /* GenTL v1.2 */
        SPINNAKER_PIXELFORMAT_NAMESPACE_GEV = 1,        /* GenTL v1.2 */
        SPINNAKER_PIXELFORMAT_NAMESPACE_IIDC = 2,       /* GenTL v1.2 */
        SPINNAKER_PIXELFORMAT_NAMESPACE_PFNC_16BIT = 3, /* GenTL v1.4 */
        SPINNAKER_PIXELFORMAT_NAMESPACE_PFNC_32BIT = 4, /* GenTL v1.4 */

        SPINNAKER_PIXELFORMAT_NAMESPACE_CUSTOM_ID = 1000
    };

    /**
     * Color processing algorithms. Please refer to our knowledge base at
     * article at
     * https://www.flir.com/support-center/iis/machine-vision/knowledge-base/different-color-processing-algorithms-in-flycapture2
     * for complete details for each algorithm.
     */
    enum ColorProcessingAlgorithm
    {
        /** Default method. */
        DEFAULT,
        /** No color processing. */
        NO_COLOR_PROCESSING,
        /**
         * Fastest but lowest quality. Equivalent to
         * FLYCAPTURE_NEAREST_NEIGHBOR_FAST in FlyCapture.
         */
        NEAREST_NEIGHBOR,
        /**
         * Nearest Neighbor with averaged green pixels. Higher quality but slower
         * compared to nearest neighbor without averaging.
         */
        NEAREST_NEIGHBOR_AVG,
        /** Weighted average of surrounding 4 pixels in a 2x2 neighborhood. */
        BILINEAR,
        /** Weights surrounding pixels based on localized edge orientation. */
        EDGE_SENSING,
        /** Well-balanced speed and quality. */
        HQ_LINEAR,
        /** Multi-threaded with similar results to edge sensing. */
        IPP,
        /** Best quality but much faster than rigorous. */
        DIRECTIONAL_FILTER,
        /** Slowest but produces good results. */
        RIGOROUS,
        /** Weighted pixel average from different directions. */
        WEIGHTED_DIRECTIONAL_FILTER
    };

    /** File formats to be used for saving images to disk. */
    enum ImageFileFormat
    {
        FROM_FILE_EXT = -1, /**< Determine file format from file extension. */
        PGM,                /**< Portable gray map. */
        PPM,                /**< Portable pixmap. */
        BMP,                /**< Bitmap. */
        JPEG,               /**< JPEG. */
        JPEG2000,           /**< JPEG 2000. */
        TIFF,               /**< Tagged image file format. */
        PNG,                /**< Portable network graphics. */
        RAW,                /**< Raw data. */
        JPEG12_C,           /**< 12 bit compressed JPEG data. */
        IMAGE_FILE_FORMAT_FORCE_32BITS = 0x7FFFFFFF
    };

    /** Status of images returned from GetNextImage() call. */
    enum ImageStatus
    {
        IMAGE_UNKNOWN_ERROR = -1,   /**< Image has an unknown error. */
        IMAGE_NO_ERROR = 0,         /**< Image is returned from GetNextImage() call without any errors. */
        IMAGE_CRC_CHECK_FAILED = 1, /**< Image failed CRC check. */
        IMAGE_DATA_OVERFLOW = 2,    /**< Received more data than the size of the image. */
        IMAGE_MISSING_PACKETS = 3,  /**< Image has missing packets. Potential fixes include enabling 
                                    jumbo packets and adjusting packet size/delay. For more information see 
                                    https://www.flir.com/support-center/iis/machine-vision/application-note/troubleshooting-image-consistency-errors/ */
        IMAGE_LEADER_BUFFER_SIZE_INCONSISTENT = 4,  /**< Image leader is incomplete. Could be caused by missing packet(s). See link above.*/
        IMAGE_TRAILER_BUFFER_SIZE_INCONSISTENT = 5, /**< Image trailer is incomplete. Could be caused by missing packet(s). See link above.*/
        IMAGE_PACKETID_INCONSISTENT = 6,            /**< Image has an inconsistent packet id. Could be caused by missing packet(s). See link above.*/
        IMAGE_MISSING_LEADER = 7,                   /**< Image leader is missing. Could be caused by missing packet(s). See link above.*/
        IMAGE_MISSING_TRAILER = 8,                  /**< Image trailer is missing. Could be caused by missing packet(s). See link above.*/
        IMAGE_DATA_INCOMPLETE = 9,                  /**< Image data is incomplete. Could be caused by missing packet(s). See link above.*/
        IMAGE_INFO_INCONSISTENT = 10,               /**< Image info is corrupted. Could be caused by missing packet(s). See link above.*/
        IMAGE_CHUNK_DATA_INVALID = 11,              /**< Image chunk data is invalid */
        IMAGE_NO_SYSTEM_RESOURCES = 12              /**< Image cannot be processed due to lack of system
                                                    resources. */
    };

    /** Options for saving PNG images. */
    struct PNGOption
    {
        /** Whether to save the PNG as interlaced. */
        bool interlaced;
        /** Compression level (0-9). 0 is no compression, 9 is best compression. */
        unsigned int compressionLevel;
        /** Reserved for future use. */
        unsigned int reserved[16];

        PNGOption()
        {
            interlaced = false;
            compressionLevel = 6;
            memset(reserved, 0, sizeof(reserved));
        }
    };

    /** Options for saving PPM images. */
    struct PPMOption
    {
        /** Whether to save the PPM as a binary file. */
        bool binaryFile;
        /** Reserved for future use. */
        unsigned int reserved[16];

        PPMOption()
        {
            binaryFile = true;
            memset(reserved, 0, sizeof(reserved));
        }
    };

    /** Options for saving PGM images. */
    struct PGMOption
    {
        /** Whether to save the PPM as a binary file. */
        bool binaryFile;
        /** Reserved for future use. */
        unsigned int reserved[16];

        PGMOption()
        {
            binaryFile = true;
            memset(reserved, 0, sizeof(reserved));
        }
    };

    /** Options for saving TIFF images. */
    struct TIFFOption
    {
        enum CompressionMethod
        {
            NONE = 1,      /**< Save without any compression. */
            PACKBITS,      /**< Save using PACKBITS compression. */
            DEFLATE,       /**< Save using DEFLATE compression (ZLIB compression). */
            ADOBE_DEFLATE, /**< Save using ADOBE DEFLATE compression */
            /**
             * Save using CCITT Group 3 fax encoding. This is only valid for
             * 1-bit images only. Default to LZW for other bit depths.
             */
            CCITTFAX3,
            /**
             * Save using CCITT Group 4 fax encoding. This is only valid for
             * 1-bit images only. Default to LZW for other bit depths.
             */
            CCITTFAX4,
            LZW, /**< Save using LZW compression. */
            /**
             * Save using JPEG compression. This is only valid for 8-bit
             * greyscale and 24-bit only. Default to LZW for other bit depths.
             */
            JPEG
        };

        /** Compression method to use for encoding TIFF images. */
        CompressionMethod compression;
        /** Reserved for future use. */
        unsigned int reserved[16];

        TIFFOption()
        {
            compression = LZW;
            memset(reserved, 0, sizeof(reserved));
        }
    };

    /** Options for saving JPEG image. */
    struct JPEGOption
    {
        /** Whether to save as a progressive JPEG file. */
        bool progressive;
        /**
         * JPEG image quality in range (0-100).
         * - 100 - Superb quality.
         * - 75  - Good quality.
         * - 50  - Normal quality.
         * - 10  - Poor quality.
         */
        unsigned int quality;
        /** Reserved for future use. */
        unsigned int reserved[16];

        JPEGOption()
        {
            progressive = false;
            quality = 75;
            memset(reserved, 0, sizeof(reserved));
        }
    };

    /** Options for saving JPEG2000 image. */
    struct JPG2Option
    {
        /** JPEG saving quality in range (1-512). */
        unsigned int quality;
        /** Reserved for future use. */
        unsigned int reserved[16];

        JPG2Option()
        {
            quality = 16;
            memset(reserved, 0, sizeof(reserved));
        }
    };

    /** Options for saving Bitmap image. */
    struct BMPOption
    {
        bool indexedColor_8bit;
        /** Reserved for future use. */
        unsigned int reserved[16];

        BMPOption()
        {
            indexedColor_8bit = false;
            memset(reserved, 0, sizeof(reserved));
        }
    };

    /** Provides easier access to the current version of Spinnaker. **/
    struct LibraryVersion
    {
        /** Major version of the library **/
        unsigned int major;

        /** Minor version of the library **/
        unsigned int minor;

        /** Version type of the library **/
        unsigned int type;

        /** Build number of the library **/
        unsigned int build;
    };

    /**
     * Channels that allow statistics to be calculated.
     */
    enum StatisticsChannel
    {
        GREY,
        RED,
        GREEN,
        BLUE,
        HUE,
        SATURATION,
        LIGHTNESS,
        NUM_STATISTICS_CHANNELS
    };

    /** log levels */
    enum SpinnakerLogLevel
    {
        LOG_LEVEL_OFF = -1,     // Logging is off.
        LOG_LEVEL_FATAL = 0,    // Not used by Spinnaker.
        LOG_LEVEL_ALERT = 100,  // Not used by Spinnaker.
        LOG_LEVEL_CRIT = 200,   // Not used by Spinnaker.
        LOG_LEVEL_ERROR = 300,  // Failures that are non-recoverable without user intervention.
        LOG_LEVEL_WARN = 400,   // Failures that are recoverable without user intervention.
        LOG_LEVEL_NOTICE = 500, // Events such as camera arrival and removal, initialization and deinitialization,
                                // starting and stopping image acquisition, and feature modification.
        LOG_LEVEL_INFO = 600,  // Information about recurring events that are generated regularly such as information on
                               // individual images.
        LOG_LEVEL_DEBUG = 700, // Information that can be used to troubleshoot the system.
        LOG_LEVEL_NOTSET = 800 // Logs everything.
    };

    /* Enumeration of TLType dependent payload types. Introduced in GenTL v1.2 */
    enum PayloadTypeInfoIDs
    {
        PAYLOAD_TYPE_UNKNOWN = 0,         /* GenTL v1.2 */
        PAYLOAD_TYPE_IMAGE = 1,           /* GenTL v1.2 */
        PAYLOAD_TYPE_RAW_DATA = 2,        /* GenTL v1.2 */
        PAYLOAD_TYPE_FILE = 3,            /* GenTL v1.2 */
        PAYLOAD_TYPE_CHUNK_DATA = 4,      /* GenTL v1.2, Deprecated in GenTL 1.5*/
        PAYLOAD_TYPE_JPEG = 5,            /* GenTL v1.4 */
        PAYLOAD_TYPE_JPEG2000 = 6,        /* GenTL v1.4 */
        PAYLOAD_TYPE_H264 = 7,            /* GenTL v1.4 */
        PAYLOAD_TYPE_CHUNK_ONLY = 8,      /* GenTL v1.4 */
        PAYLOAD_TYPE_DEVICE_SPECIFIC = 9, /* GenTL v1.4 */
        PAYLOAD_TYPE_MULTI_PART = 10,     /* GenTL v1.5 */

        PAYLOAD_TYPE_CUSTOM_ID = 1000, /* Starting value for GenTL Producer custom IDs. */
        PAYLOAD_TYPE_EXTENDED_CHUNK = 1001
    };

    /** Possible Status Codes Returned from Action Command. */
    enum ActionCommandStatus
    {
        ACTION_COMMAND_STATUS_OK = 0, /* The device acknowledged the command.*/
        ACTION_COMMAND_STATUS_NO_REF_TIME =
            0x8013, /* The device is not synchronized to a master clock to be used as time reference. Typically used
                       when scheduled action commands cannot be scheduled for a future time since the reference time
                       coming from IEEE 1588 is not locked. */
        ACTION_COMMAND_STATUS_OVERFLOW = 0x8015, /* Returned when the scheduled action commands queue is full and the
                                                    device cannot accept the additional request. */
        ACTION_COMMAND_STATUS_ACTION_LATE =
            0x8016, /* The requested scheduled action command was requested at a point in time that is in the past. */
        ACTION_COMMAND_STATUS_ERROR =
            0x8FFF /* Generic Error. Try enabling the Extended Status Code 2.0 bit on gvcp configuration register in
                      order to receive more meaningful/detailed acknowledge messages from the device. */
    };

    /** Action Command Result */
    struct ActionCommandResult
    {
        unsigned int DeviceAddress; /* IP Address of device that responded to Action Command. */
        ActionCommandStatus Status; /* Action Command status return from device. */
    };

    /** Possible integer types and packing used in a pixel format. */
    enum PixelFormatIntType
    {
        IntType_UINT8,   /* Unsigned 8-bit integer. */
        IntType_INT8,    /* Signed 8-bit integer. */
        IntType_UINT10,  /* Unsigned 10-bit integer. */
        IntType_UINT10p, /* LSB packed unsigned 10-bit integer. */
        IntType_UINT10P, /* MSB packed unsigned 10-bit integer. */
        IntType_UINT12,  /* Unsigned 12-bit integer (unpacked). */
        IntType_UINT12p, /* LSB packed unsigned 12-bit integer. */
        IntType_UINT12P, /* MSB packed unsigned 12-bit integer. */
        IntType_UINT14,  /* Unsigned 14-bit integer (unpacked). */
        IntType_UINT16,  /* Unsigned 16-bit integer (unpacked). */
        IntType_INT16,   /* Signed 16-bit integer (unpacked). */
        IntType_FLOAT32, /* 32-bit float. */
        IntType_UNKNOWN
    };

    enum BufferOwnership
    {
        BUFFER_OWNERSHIP_SYSTEM, /* Buffers are owned and managed by the library */
        BUFFER_OWNERSHIP_USER    /* Buffers are owned and managed by the user */
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_DEFS_H
