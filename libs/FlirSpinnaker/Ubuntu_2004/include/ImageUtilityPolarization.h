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

#ifndef FLIR_SPINNAKER_IMAGE_UTILITY_POLARIZATION_H
#define FLIR_SPINNAKER_IMAGE_UTILITY_POLARIZATION_H

#include "SpinnakerDefs.h"

namespace Spinnaker
{
    class ImagePtr;

    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /*@{*/

    /**
     *  @defgroup ImageUtilityPolarization_h Image Utility Polarization Class
     */
    /*@{*/

    /**
     * @brief Static functions to create polarization images from image objects of pixel format Polarized8 and
     * BayerRGPolarized8.
     */

    class SPINNAKER_API ImageUtilityPolarization
    {
      public:
        /**
         * Polarization quadrant specifiers describing the four orientations of linear polarizing
         * filters on polarized cameras
         */
        enum PolarizationQuadrant
        {
            /** The 0 degree of polarization. */
            QUADRANT_I0,
            /** The 45 degree of polarization. */
            QUADRANT_I45,
            /** The 90 degree of polarization. */
            QUADRANT_I90,
            /** The 135 degree of polarization. */
            QUADRANT_I135
        };

        /**
         * Extracts all pixels of a specified degree of linear polarization into a new image object.
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format will be Mono8 or BayerRG8 respectively.
         * The destination image height and width will be half of the source image.
         *
         * @param srcImage The source image from which to extract polarization data
         * @param desiredQuadrant The polarization quadrant to extract
         *
         * @return The specified polarization quadrant image
         */
        static ImagePtr ExtractPolarQuadrant(const ImagePtr& srcImage, const PolarizationQuadrant desiredQuadrant);

        /**
         * Extracts all pixels of a specified degree of linear polarization into the provided image object.
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format must be Mono8 or BayerRG8 respectively.
         * The destination image height and width must be half of the source image.
         *
         * @param srcImage The source image from which to extract polarization data
         * @param destQuadImage The destination image in which to store the extracted polarization quadrant
         * @param desiredQuadrant The polarization quadrant to extract
         */
        static void ExtractPolarQuadrant(
            const ImagePtr& srcImage,
            ImagePtr& destQuadImage,
            const PolarizationQuadrant desiredQuadrant);

        /**
         * Create a glare reduced image from the source image by choosing the
         * darkest pixel from each polarization quadrant
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format will be Mono8 or BayerRG8 respectively.
         * The destination image height and width must be half of the source image.
         *
         * @param srcImage The source image from which to extract polarization data
         *
         * @return The reduced glare image
         */
        static ImagePtr CreateGlareReduced(const ImagePtr& srcImage);

        /**
         * Create a glare reduced image from the source image by choosing the
         * darkest pixel from each polarization quadrant
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format will be Mono8 or BayerRG8 respectively.
         * The destination image height and width must be half of the source image.
         *
         * @param srcImage The source image from which to apply glare reduction
         * @param destGlareReducedImage The destination image in which to store the image with reduced glare
         */
        static void CreateGlareReduced(const ImagePtr& srcImage, ImagePtr& destGlareReducedImage);

        /**
         * Computes an image representing the overall intensity of light from a polarized image.
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format will be Mono16s or RGB16s respectively.
         * The destination image height and width will be half of the source image.
         *
         * @param srcImage The source image from which to extract polarization data
         * @param colorProcessingAlg The color processing algorithm to use for color images
         *
         * @return The Stokes' S0 image
         */
        static ImagePtr CreateStokesS0(
            const ImagePtr& srcImage,
            const ColorProcessingAlgorithm colorProcessingAlg = DEFAULT);

        /**
         * Computes an image representing the overall intensity of light from a polarized image.
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format must be Mono16s or RGB16s respectively.
         * The destination image height and width must be half of the source image.
         *
         * @param srcImage The source image from which to extract polarization data
         * @param destStokesS0Image The destination image in which to store the Stokes' S0 image
         * @param colorProcessingAlg The color processing algorithm to use for color images
         */
        static void CreateStokesS0(
            const ImagePtr& srcImage,
            ImagePtr& destStokesS0Image,
            const ColorProcessingAlgorithm colorProcessingAlg = DEFAULT);

        /**
         * Computes an image representing the difference in intensity accepted through the polarizers
         * at 0 and 90 to the horizontal.
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format will be Mono16s or RGB16s respectively.
         * The destination image height and width will be half of the source image.
         *
         * @param srcImage The source image from which to extract polarization data
         * @param colorProcessingAlg The color processing algorithm to use for color images
         *
         * @return The Stokes' S1 image
         */
        static ImagePtr CreateStokesS1(
            const ImagePtr& srcImage,
            const ColorProcessingAlgorithm colorProcessingAlg = DEFAULT);

        /**
         * Computes an image representing the difference in intensity accepted through the polarizers
         * at 0 and 90 to the horizontal.
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format must be Mono16s or RGB16s respectively.
         * The destination image height and width must be half of the source image.
         *
         * @param srcImage The source image from which to extract polarization data
         * @param destStokesS1Image The destination image in which to store the Stokes' S1 image
         * @param colorProcessingAlg The color processing algorithm to use for color images
         */
        static void CreateStokesS1(
            const ImagePtr& srcImage,
            ImagePtr& destStokesS1Image,
            const ColorProcessingAlgorithm colorProcessingAlg = DEFAULT);

        /**
         * Computes an image representing the difference in intensity accepted through the polarizers
         * at 45 and -45 to the horizontal.
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format will be Mono16s or RGB16s respectively.
         * The destination image height and width will be half of the source image.
         *
         * @param srcImage The source image from which to extract polarization data
         * @param colorProcessingAlg The color processing algorithm to use for color images
         *
         * @return The Stokes' S2 image
         */
        static ImagePtr CreateStokesS2(
            const ImagePtr& srcImage,
            const ColorProcessingAlgorithm colorProcessingAlg = DEFAULT);

        /**
         * Computes an image representing the difference in intensity accepted through the polarizers.
         * at 45 and -45 to the horizontal.
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format must be Mono16s or RGB16s respectively.
         * The destination image height and width must be half of the source image.
         *
         * @param srcImage The source image from which to extract polarization data
         * @param destStokesS2Image The destination image in which to store the Stokes' S2 image
         * @param colorProcessingAlg The color processing algorithm to use for color images
         */
        static void CreateStokesS2(
            const ImagePtr& srcImage,
            ImagePtr& destStokesS2Image,
            const ColorProcessingAlgorithm colorProcessingAlg = DEFAULT);

        /**
         * Computes an image representing the fraction of incident light intensity in the linear
         * polarization states.
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format will be Mono32f or RGB32f respectively.
         * The destination image height and width will be half of the source image.
         *
         * @param srcImage The source image from which to extract polarization data
         * @param colorProcessingAlg The color processing algorithm to use for color images
         *
         * @return The degree of linear polarization (dolp) image
         */
        static ImagePtr CreateDolp(
            const ImagePtr& srcImage,
            const ColorProcessingAlgorithm colorProcessingAlg = DEFAULT);

        /**
         * Computes an image representing the fraction of incident light intensity in the linear
         * polarization states.
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format must be Mono32f or RGB32f respectively.
         * The destination image height and width must be half of the source image.
         *
         * @param srcImage The source image from which to extract polarization data
         * @param destDolpImage The destination image in which to store the degree of linear
         *                      polarization (dolp) image
         * @param colorProcessingAlg The color processing algorithm to use for color images
         */
        static void CreateDolp(
            const ImagePtr& srcImage,
            ImagePtr& destDolpImage,
            const ColorProcessingAlgorithm colorProcessingAlg = DEFAULT);

        /**
         * Computes an image representing the angle at which linearly polarized light oscillates with respect
         * to a reference axis.
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format will be Mono32f or RGB32f respectively.
         * The destination image height and width will be half of the source image.
         *
         * @param srcImage The source image from which to extract polarization data
         * @param colorProcessingAlg The color processing algorithm to use for color images
         *
         * @return The angle of linear polarization (aolp) image
         */
        static ImagePtr CreateAolp(
            const ImagePtr& srcImage,
            const ColorProcessingAlgorithm colorProcessingAlg = DEFAULT);

        /**
         * Computes an image representing the angle at which linearly polarized light oscillates with respect
         * to a reference axis.
         * The source image pixel format must be Polarized8 or BayerRGPolarized8.
         * The destination image pixel format must be Mono32f or RGB32f respectively.
         * The destination image height and width must be half of the source image.
         *
         * @param srcImage The source image from which to extract polarization data
         * @param destAolpImg The destination image in which to store the angle of linear polarization
         *                    (aolp) image
         * @param colorProcessingAlg The color processing algorithm to use for color images
         */
        static void CreateAolp(
            const ImagePtr& srcImage,
            ImagePtr& destAolpImg,
            const ColorProcessingAlgorithm colorProcessingAlg = DEFAULT);
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_IMAGE_UTILITY_POLARIZATION_H