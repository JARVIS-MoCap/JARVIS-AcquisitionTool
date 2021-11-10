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

#ifndef FLIR_SPINNAKER_CHUNK_DATA_INFERENCE_H
#define FLIR_SPINNAKER_CHUNK_DATA_INFERENCE_H

#include "SpinGenApi/GCTypes.h"
#include "SpinnakerPlatform.h"
#include "CameraDefs.h"

namespace Spinnaker
{
    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /*@{*/

    /**
     * Inference Bounding Box Type
     */
    enum InferenceBoxType
    {
        INFERENCE_BOX_TYPE_RECTANGLE = 0,
        INFERENCE_BOX_TYPE_CIRCLE = 1,
        INFERENCE_BOX_TYPE_ROTATED_RECTANGLE = 2
    };

    /**
     * Inference Bounding Box Type Data Structures
     */
    typedef struct
    {
        int16_t topLeftXCoord;
        int16_t topLeftYCoord;
        int16_t bottomRightXCoord;
        int16_t bottomRightYCoord;
    } InferenceBoxRect;

    typedef struct
    {
        int16_t centerXCoord;
        int16_t centerYCoord;
        int16_t radius;
    } InferenceBoxCircle;

    typedef struct
    {
        int16_t topLeftXCoord;
        int16_t topLeftYCoord;
        int16_t bottomRightXCoord;
        int16_t bottomRightYCoord;
        short rotationAngle;
    } InferenceBoxRotatedRect;

    /**
     * Inference Bounding Boxes data structure
     */
    typedef struct InferenceBoundingBox
    {
        InferenceBoxType boxType;
        int16_t classId;
        float32_t confidence;

        InferenceBoxRect rect;
        InferenceBoxCircle circle;
        InferenceBoxRotatedRect rotatedRect;
    } InferenceBoundingBox;

    /**
     *  @defgroup ChunkDataInference_h Chunk Data Inference Class
     */
    /*@{*/

    /**
     * @brief An inference bounding boxes object which holds information about the detected bounding boxes.
     */
    class SPINNAKER_API InferenceBoundingBoxResult
    {
      public:
        /**
         * Default Constructor
         */
        InferenceBoundingBoxResult();

        /**
         * Destructor
         */
        ~InferenceBoundingBoxResult();

        /**
         * Default Constructor with arguments
         *
         * @param data The bounding box binary data from chunk data.
         * @param lengthInBytes The length of bounding box binary data in bytes.
         */
        InferenceBoundingBoxResult(const uint8_t* data, const int64_t lengthInBytes);

        /**
         * Copy Constructor
         */
        InferenceBoundingBoxResult(const InferenceBoundingBoxResult& other);

        /**
         * Assignment Operator
         */
        InferenceBoundingBoxResult& operator=(const InferenceBoundingBoxResult& rhs);

        /**
         * Returns the bounding box format version number.
         */
        int8_t GetVersion() const;

        /**
         * Returns the number of bounding boxes.
         */
        int16_t GetBoxCount() const;

        /**
         * Returns the number of bytes allocated for one bounding box.
         */
        int8_t GetBoxSize() const;

        /**
         * Returns the bounding box at specified index.
         *
         * @param index Index of the bounding box to return.
         */
        InferenceBoundingBox GetBoxAt(const uint16_t index) const;

      private:
        struct InferenceBoundingBoxResultData;
        InferenceBoundingBoxResultData* m_pData;
    };
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_CHUNK_DATA_UTILITY_INFERENCE_H