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

#ifndef FLIR_SPINNAKER_AVIRECORDER_H
#define FLIR_SPINNAKER_AVIRECORDER_H

#include "SpinnakerPlatform.h"
#include "SpinnakerDefs.h"

namespace Spinnaker
{
    class ImagePtr;

    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /*@{*/

    /**
     *  @defgroup AVIRecorder_h AVI Recorder Class
     */
    /*@{*/

    /**
     * @brief Provides the functionality for the user to record images to an AVI file.
     *
     * NOTE: This class is deprecated and replaced by SpinVideo. Refer to SpinVideo.h instead.
     */

    class DEPRECATED_CLASS("AVIRecorder is deprecated, use SpinVideo instead.") SPINNAKER_API AVIRecorder
    {
      public:
        /**
         * Default constructor.
         */
        AVIRecorder();

        /**
         * Default destructor.
         */
        virtual ~AVIRecorder();

        /**
         * Open an AVI file in preparation for writing Images to disk.
         * The size of AVI files is limited to 2GB. The filenames are
         * automatically generated using the filename specified.
         *
         * @param pFileName The filename of the AVI file.
         * @param pOption Options to apply to the AVI file.
         *
         * @see AVIClose()
         *
         */
        virtual void AVIOpen(const char* pFileName, AVIOption& pOption);

        /**
         * Open an MJPEG AVI file in preparation for writing Images to disk.
         * The size of AVI files is limited to 2GB. The filenames are
         * automatically generated using the filename specified.
         *
         * @param pFileName The filename of the AVI file.
         * @param pOption MJPEG options to apply to the AVI file.
         *
         * @see AVIClose()
         * @see MJPGOption
         *
         */
        virtual void AVIOpen(const char* pFileName, MJPGOption& pOption);

        /**
         * Open an H264 MP4 file in preparation for writing Images to disk.
         * The size of MP4 files is limited to 2GB. The filenames are
         * automatically generated using the filename specified.
         *
         * @param pFileName The filename of the MP4 file.
         * @param pOption H264 options to apply to the MP4 file.
         *
         * @see AVIClose()
         * @see H264Option
         *
         */
        virtual void AVIOpen(const char* pFileName, H264Option& pOption);

        /**
         * Append an image to the AVI/MP4 file.
         *
         * @param pImage The image to append.
         *
         */
        virtual void AVIAppend(ImagePtr pImage);

        /**
         * Close the AVI/MP4 file.
         *
         * @see AVIOpen()
         *
         */
        virtual void AVIClose();

        /**
         * Set the maximum file size (in megabytes) of a AVI/MP4 file. A new AVI/MP4 file
         * is created automatically when file size limit is reached. Setting
         * a maximum size of 0 indicates no limit on file size.
         *
         * @param size The maximum AVI file size in MB.
         *
         * @see AVIAppend( ImagePtr pImage)
         *
         */
        virtual void SetMaximumAVISize(unsigned int size);

      private:
        AVIRecorder(const AVIRecorder&);
        AVIRecorder& operator=(const AVIRecorder&);

        struct AVIRecorderData; // Forward declaration

        AVIRecorderData* m_pAVIRecorderData;
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_AVIRECORDER_H