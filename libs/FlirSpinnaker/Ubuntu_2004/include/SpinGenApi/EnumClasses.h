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

#ifndef SPINNAKER_GENAPI_ENUMCLASSES_H
#define SPINNAKER_GENAPI_ENUMCLASSES_H

#include "GCString.h"
#include "Types.h"

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup EnumClasses_h EnumClasses Class
         */
        /*@{*/

        //*************************************************************
        // Build in enumeration classes
        //*************************************************************

        /**
         * @brief Holds conversion methods for the sign enumeration
         */
        class SPINNAKER_API ESignClass
        {
          public:
            /**
             * Converts a string to enum value
             */
            static bool FromString(const GenICam::gcstring& ValueStr, ESign* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static void ToString(GenICam::gcstring& ValueStr, ESign* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static GenICam::gcstring ToString(ESign Value);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup EnumClasses_h EnumClasses Class
         */
        /*@{*/

        /**
         * @brief Holds conversion methods for the endianess enumeration
         */
        class SPINNAKER_API EEndianessClass
        {
          public:
            /**
             * Converts a string to enum value
             */
            static bool FromString(const GenICam::gcstring& ValueStr, EEndianess* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static void ToString(GenICam::gcstring& ValueStr, EEndianess* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static GenICam::gcstring ToString(EEndianess Value);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup EnumClasses_h EnumClasses Class
         */
        /*@{*/

        /**
         * @brief Holds conversion methods for the representation enumeration
         */
        class SPINNAKER_API ERepresentationClass
        {
          public:
            /**
             * Converts a string to enum value
             */
            static bool FromString(const GenICam::gcstring& ValueStr, ERepresentation* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static void ToString(GenICam::gcstring& ValueStr, ERepresentation* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static GenICam::gcstring ToString(ERepresentation Value);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup EnumClasses_h EnumClasses Class
         */
        /*@{*/

        /**
         * @brief Holds conversion methods for the visibility enumeration
         */
        class SPINNAKER_API EVisibilityClass
        {
          public:
            /**
             * Converts a string to enum value
             */
            static bool FromString(const GenICam::gcstring& ValueStr, EVisibility* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static void ToString(GenICam::gcstring& ValueStr, EVisibility* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static GenICam::gcstring ToString(EVisibility Value);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup EnumClasses_h EnumClasses Class
         */
        /*@{*/

        /**
         * @brief Holds conversion methods for the access mode enumeration
         */
        class SPINNAKER_API EAccessModeClass
        {
          public:
            /**
             * Converts a string to enum value
             */
            static bool FromString(const GenICam::gcstring& ValueStr, EAccessMode* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static void ToString(GenICam::gcstring& ValueStr, EAccessMode* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static GenICam::gcstring ToString(EAccessMode Value);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup EnumClasses_h EnumClasses Class
         */
        /*@{*/

        /**
         * @brief Holds conversion methods for the caching mode enumeration
         */
        class SPINNAKER_API ECachingModeClass
        {
          public:
            /**
             * Converts a string to enum value
             */
            static bool FromString(const GenICam::gcstring& ValueStr, ECachingMode* pValue);

            static void ToString(GenICam::gcstring& ValueStr, ECachingMode* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static GenICam::gcstring ToString(ECachingMode Value);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup EnumClasses_h EnumClasses Class
         */
        /*@{*/

        /**
         * @brief Holds conversion methods for the namespace enumeration
         */
        class SPINNAKER_API ENameSpaceClass
        {
          public:
            /**
             * Converts a string to enum value
             */
            static bool FromString(const GenICam::gcstring& ValueStr, ENameSpace* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static void ToString(GenICam::gcstring& ValueStr, ENameSpace* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static GenICam::gcstring ToString(ENameSpace Value);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup EnumClasses_h EnumClasses Class
         */
        /*@{*/

        /**
         * @brief Holds conversion methods for the standard namespace enumeration
         */
        class SPINNAKER_API EYesNoClass
        {
          public:
            /**
             * Converts a string to enum value
             */
            static bool FromString(const GenICam::gcstring& ValueStr, EYesNo* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static void ToString(GenICam::gcstring& ValueStr, EYesNo* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static GenICam::gcstring ToString(EYesNo Value);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup EnumClasses_h EnumClasses Class
         */
        /*@{*/

        /**
         * @brief Holds conversion methods for the standard namespace enumeration
         */
        class SPINNAKER_API EStandardNameSpaceClass
        {
          public:
            /**
             * Converts a string to enum value
             */
            static bool FromString(const GenICam::gcstring& ValueStr, EStandardNameSpace* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static void ToString(GenICam::gcstring& ValueStr, EStandardNameSpace* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static GenICam::gcstring ToString(EStandardNameSpace Value);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup EnumClasses_h EnumClasses Class
         */
        /*@{*/

        /**
         * @brief Holds conversion methods for the converter formulas
         */
        class SPINNAKER_API ESlopeClass
        {
          public:
            /**
             * Converts a string to enum value
             */
            static bool FromString(const GenICam::gcstring& ValueStr, ESlope* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static void ToString(GenICam::gcstring& ValueStr, ESlope* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static GenICam::gcstring ToString(ESlope Value);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup EnumClasses_h EnumClasses Class
         */
        /*@{*/

        /**
         * @brief Holds conversion methods for the notation type of floats
         */
        class SPINNAKER_API EDisplayNotationClass
        {
          public:
            /**
             * Converts a string to enum value
             */
            static bool FromString(const GenICam::gcstring& ValueStr, EDisplayNotation* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static void ToString(GenICam::gcstring& ValueStr, EDisplayNotation* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static GenICam::gcstring ToString(EDisplayNotation Value);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup EnumClasses_h EnumClasses Class
         */
        /*@{*/

        /**
         * @brief Holds conversion methods for the notation type of floats
         */
        class SPINNAKER_API EInputDirectionClass
        {
          public:
            /**
             * Converts a string to enum value
             */
            static bool FromString(const GenICam::gcstring& ValueStr, EInputDirection* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static void ToString(GenICam::gcstring& ValueStr, EInputDirection* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static GenICam::gcstring ToString(EInputDirection Value);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup EnumClasses_h EnumClasses Class
         */
        /*@{*/

        /**
         * @brief helper class converting EGenApiSchemaVersion from and to string
         */
        class SPINNAKER_API EGenApiSchemaVersionClass
        {
          public:
            /**
             * Converts a string to enum value
             */
            static bool FromString(const GenICam::gcstring& ValueStr, EGenApiSchemaVersion* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static void ToString(GenICam::gcstring& ValueStr, EGenApiSchemaVersion* pValue);

            /**
             * Converts a string to an int32_t property
             */
            static GenICam::gcstring ToString(EGenApiSchemaVersion Value);
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // ifndef SPINNAKER_GENAPI_ENUMCLASSES_H
