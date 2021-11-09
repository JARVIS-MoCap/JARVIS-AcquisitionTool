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

#ifndef FLIR_SPINNAKER_IIMAGESTATISTICS_H
#define FLIR_SPINNAKER_IIMAGESTATISTICS_H

#include "Image.h"

namespace Spinnaker
{
    /**
     * @defgroup SpinnakerClasses Spinnaker Classes
     */

    /*@{*/

    /**
     * @defgroup IImageStatistics_h IImageStatistics Class
     */

    /*@{*/

    /**
     * @brief The interface file for image statistics.
     */

    class SPINNAKER_API IImageStatistics
    {
      public:
        virtual ~IImageStatistics(){};

        virtual void EnableAll() = 0;
        virtual void DisableAll() = 0;
        virtual void EnableGreyOnly() = 0;
        virtual void EnableRGBOnly() = 0;
        virtual void EnableHSLOnly() = 0;
        virtual void GetChannelStatus(StatisticsChannel channel, bool* pEnabled) const = 0;
        virtual void SetChannelStatus(StatisticsChannel channel, bool enabled) = 0;
        virtual void GetRange(StatisticsChannel channel, unsigned int* pMin, unsigned int* pMax) const = 0;
        virtual void GetPixelValueRange(
            StatisticsChannel channel,
            unsigned int* pPixelValueMin,
            unsigned int* pPixelValueMax) const = 0;
        virtual void GetNumPixelValues(StatisticsChannel channel, unsigned int* pNumPixelValues) const = 0;
        virtual void GetMean(StatisticsChannel channel, float* pPixelValueMean) const = 0;
        virtual void GetHistogram(StatisticsChannel channel, int** ppHistogram) const = 0;
        virtual void GetStatistics(
            StatisticsChannel channel,
            unsigned int* pRangeMin = NULL,
            unsigned int* pRangeMax = NULL,
            unsigned int* pPixelValueMin = NULL,
            unsigned int* pPixelValueMax = NULL,
            unsigned int* pNumPixelValues = NULL,
            float* pPixelValueMean = NULL,
            int** ppHistogram = NULL) const = 0;

      protected:
        IImageStatistics(){};
        IImageStatistics(const IImageStatistics&){};
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_IIMAGESTATISTICS_H
