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

#ifndef FLIR_SPINNAKER_IMAGE_UTILITY_H
#define FLIR_SPINNAKER_IMAGE_UTILITY_H

#include "SpinnakerPlatform.h"
#include "CameraDefs.h"

namespace Spinnaker
{
    class ImagePtr;

    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /*@{*/

    /**
     *  @defgroup ImageUtility_h Image Utility Class
     */
    /*@{*/

    /**
     * @brief Static helper functions for the image object class.
     */

    class SPINNAKER_API ImageUtility
    {
      public:
        /**
         * Image scaling algorithms.
         */
        enum ImageScalingAlgorithm
        {
            /*
             * Uses copies of the nearest source pixels to compute a scaled image.
             * The scaling factor used with this algorithm will be rounded to the
             * nearest integer (upscaling) or inverse integer (downscaling).
             * eg. 1.3 will be rounded to 1 and 0.3 will be rounded to (1 / 3).
             */
            NEAREST_NEIGHBOR
        };

        /**
         * Image normalization source data options.
         * Options to normalize the source data based on the max and min values present in the specific
         * image (image data) or the theoretical abosolute max and min image data values for the image type (absolute
         * data). By default the abosolute max and min values for an image are the max and min values allowable for the
         * image's pixel format. An exception to this is for some computed image data formats such as AoLP, DoLP and
         * Stokes, where the absolute max and min are dependant on the algorithm used.
         *
         * For a given pixel, normalization is done by:
         * NormalizedValue = ((maxDest - minDest) * (PixelValue - minSrc) / (maxSrc - minSrc)) + minDest
         */
        enum SourceDataRange
        {
            /** Normalize based on the actual max and min values for the source image. */
            IMAGE_DATA_RANGE,
            /** Normalize based on the theoretical max and min values for the source image. */
            ABSOLUTE_DATA_RANGE,
            /** Normalize based on the actual min and theoretical max values for the source image. */
            IMAGE_MIN_ABSOLUTE_MAX,
            /** Normalize based on the theoretical min and actual max values for the source image. */
            ABSOLUTE_MIN_IMAGE_MAX
        };

        /**
         * Computes a scaled image using the specified parameters.
         * Does not support scaling of raw bayer images.
         *
         * @param srcImage The source image from which to create scaled image
         * @param scalingAlg The desired image scaling algorithm to use
         * @param scalingFactor The desired image scaling factor to use
         *
         * @return The scaled image
         */
        static ImagePtr CreateScaled(const ImagePtr& srcImage, ImageScalingAlgorithm scalingAlg, double scalingFactor);

        /**
         * Computes a scaled image using the specified parameters.
         * Does not support scaling of raw bayer images.
         * The destination image height and width must be sufficient to store the calculated data.
         * The destination image pixel format must be the same as the source image.
         *
         * @param srcImage The source image from which to create scaled image
         * @param destImage An image object in which to store the scaled data
         *
         * @param scalingAlg The desired image scaling algorithm to use
         * @param scalingFactor The desired image scaling factor to use
         */
        static void CreateScaled(
            const ImagePtr& srcImage,
            ImagePtr& destImage,
            ImageScalingAlgorithm scalingAlg,
            double scalingFactor);

        /**
         * Computes a normalized image.
         * The full range of the destination pixel format data type will be used as the min
         * and max range for normalization.
         * The destination pixel format must be of the same data type as the source image pixel format.
         *
         * @param srcImage The source image from which to create normalized image
         * @param destPixelFormat The desired pixel format for the normalized image
         * @param srcDataRange The desired option for the source data range to normalize from
         *
         * @return The normalized image
         */
        static ImagePtr CreateNormalized(
            const ImagePtr& srcImage,
            const PixelFormatEnums destPixelFormat,
            SourceDataRange srcDataRange = IMAGE_DATA_RANGE);

        /**
         * Computes a normalized image.
         * The min and max must be within range of the destination pixel format data type.
         * The normalized image pixel format will be the same as the source image.
         *
         * @param srcImage The source image from which to create normalized image
         * @param min The lower bound of the normalization range
         * @param max The upper bound of the normalization range
         * @param srcDataRange The desired option for the source data range to normalize from
         *
         * @return The normalized image
         */
        static ImagePtr CreateNormalized(
            const ImagePtr& srcImage,
            const double min,
            const double max,
            SourceDataRange srcDataRange = IMAGE_DATA_RANGE);

        /**
         * Computes a normalized image.
         * The min and max must be within range of the destination pixel format data type.
         * The destination pixel format must be of the same data type as the source image pixel format.
         *
         * @param srcImage The source image from which to create normalized image
         * @param min The lower bound of the normalization range
         * @param max The upper bound of the normalization range
         * @param destPixelFormat The desired pixel format for the normalized image
         * @param srcDataRange The desired option for the source data range to normalize from
         *
         * @return The normalized image
         */
        static ImagePtr CreateNormalized(
            const ImagePtr& srcImage,
            const double min,
            const double max,
            const PixelFormatEnums destPixelFormat,
            SourceDataRange srcDataRange = IMAGE_DATA_RANGE);

        /**
         * Computes a normalized image.
         * The full range of the destination pixel format data type will be used as the min
         * and max range for normalization.
         * The destination image must be initialized and have the same width and height as the source image.
         * The destination image pixel format must be of the same data type as the source image pixel format.
         *
         * @param srcImage The source image from which to create normalized image
         * @param destImage The destination image in which to store the normalized image
         * @param srcDataRange The desired option for the source data range to normalize from
         */
        static void CreateNormalized(
            const ImagePtr& srcImage,
            ImagePtr& destImage,
            SourceDataRange srcDataRange = IMAGE_DATA_RANGE);

        /**
         * Computes a normalized image.
         * The min and max must be within range of the destination pixel format data type.
         * The destination image must be initialized and have the same width and height as the source image.
         * The destination image pixel format must be of the same data type as the source image pixel format.
         *
         * @param srcImage The source image from which to create normalized image
         * @param destImage The destination image in which to store the normalized image
         * @param min The lower bound of the normalization range
         * @param max The upper bound of the normalization range
         * @param srcDataRange The desired option for the source data range to normalize from
         */
        static void CreateNormalized(
            const ImagePtr& srcImage,
            ImagePtr& destImage,
            const double min,
            const double max,
            SourceDataRange srcDataRange = IMAGE_DATA_RANGE);
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_IMAGE_UTILITY_H