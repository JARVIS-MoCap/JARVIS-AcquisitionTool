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

#ifndef FLIR_SPINNAKER_IMAGE_UTILITY_HEATMAP_H
#define FLIR_SPINNAKER_IMAGE_UTILITY_HEATMAP_H

#include "SpinnakerPlatform.h"

namespace Spinnaker
{
    class ImagePtr;

    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /*@{*/

    /**
     *  @defgroup ImageUtilityHeatmap_h Image Utility Heatmap Class
     */
    /*@{*/

    /**
     * @brief Static functions to create heatmap images from image objects of pixel format Mono8 and Mono16.
     */

    class SPINNAKER_API ImageUtilityHeatmap
    {
      public:
        /**
         * Color specifiers for the heatmap color gradient.
         */
        enum HeatmapColor
        {
            HEATMAP_BLACK = 1,
            HEATMAP_BLUE = 2,
            HEATMAP_CYAN = 3,
            HEATMAP_GREEN = 4,
            HEATMAP_YELLOW = 5,
            HEATMAP_RED = 6,
            HEATMAP_WHITE = 7
        };

        /**
         * Computes a heatmap image.
         * A heatmap image reinterprets monochrome data by mapping the luminosity of each pixel
         * to a color value defined in the heatmap color gradient. The created image can be
         * modified by changing the color gradient and heatmap range from the accompanying functions.
         * The source image is required to be Mono8 or Mono16 pixel format.
         *
         * @param srcImage The source image from which to create the heatmap
         *
         * @see SetHeatmapRange()
         * @see SetHeatmapColorGradient()
         *
         * @return The heatmap image
         */
        static ImagePtr CreateHeatmap(const ImagePtr& srcImage);

        /**
         * Computes a heatmap image.
         * A heatmap image reinterprets monochrome data by mapping the luminosity of each pixel
         * to a color value defined in the heatmap color gradient. The created image can be
         * modified by changing the color gradient and heatmap range from the accompanying functions.
         * The source image is required to be Mono8 or Mono16 pixel format.
         * The destination is required to be initialized, RGB8 or RGB16 pixel format, and have the
         * same width, height, x offset, and y offset as the source image.
         *
         * @param srcImage The source image from which to create the heatmap
         * @param destImage The destination image in which to store the created heatmap
         *
         * @see SetHeatmapRange()
         * @see SetHeatmapColorGradient()
         */
        static void CreateHeatmap(const ImagePtr& srcImage, ImagePtr& destImage);

        /**
         * Sets the heatmap gradient color vector to the new desired range between HEATMAP_BLACK
         * and HEATMAP_WHITE.
         *
         * @param newLowColor New color at which to begin the gradient.
         * @param newHighColor New color at which to end the gradient.
         */
        static void SetHeatmapColorGradient(const HeatmapColor newLowColor, const HeatmapColor newHighColor);

        /**
         * Returns the current heatmap gradient color range.
         *
         * @param currentLowColor Current color at which the gradient begins.
         * @param currentHighColor Current color at which the gradient ends.
         *
         * @see SetHeatmapColorGradient()
         */
        static void GetHeatmapColorGradient(HeatmapColor& currentLowColor, HeatmapColor& currentHighColor);

        /**
         * Sets the high and low values used to determine which grayscale values are converted
         * to a color 'heatmap' representation. Acceptable values range from 0 to 100.
         *
         * @param newLowValue New value at which to begin color representation.
         * @param newHighValue New value at which to end color representation.
         */
        static void SetHeatmapRange(const unsigned int newLowValue, const unsigned int newHighValue);

        /**
         * Returns the current high and low values used in heatmap representations.
         *
         * @param currentLowValue Current value at which color representation begins.
         * @param currentHighValue Current value at which color representation ends.
         *
         * @see SetHeatmapRange()
         */
        static void GetHeatmapRange(unsigned int& currentLowValue, unsigned int& currentHighValue);
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_IMAGE_UTILITY_HEATMAP_H