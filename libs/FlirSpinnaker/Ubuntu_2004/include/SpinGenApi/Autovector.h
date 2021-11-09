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

#ifndef SPINNAKER_GENAPI_AUTOVECTOR_H
#define SPINNAKER_GENAPI_AUTOVECTOR_H

#include <vector>
#include "GCTypes.h"
#include "SpinnakerPlatform.h"

#if defined(WIN32)
typedef long ATOMIC_VARIABLE;
#elif defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__))
typedef uint32_t ATOMIC_VARIABLE;
#else
#error Unsupported platform
#endif

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup AutoVector_h AutoVector Class
         */
        /*@{*/

        /**
         * @brief Vector of integers with reference counting.
         */
        class SPINNAKER_API int64_autovector_t
        {
          public:
            int64_autovector_t();
            int64_autovector_t(const int64_autovector_t& obj);
            explicit int64_autovector_t(size_t n);
            virtual ~int64_autovector_t(void);

            int64_autovector_t& operator=(const int64_autovector_t& obj);

            void operator delete(void* pWhere);
            void* operator new(size_t uiSize);
            int64_t& operator[](size_t uiIndex);
            const int64_t& operator[](size_t uiIndex) const;
            size_t size() const;

          protected:
            std::vector<int64_t>* _pv;
            ATOMIC_VARIABLE* _pCount;
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup AutoVector_h AutoVector Class
         */
        /*@{*/

        /**
         * @brief Vector of doubles with reference counting.
         */
        class SPINNAKER_API double_autovector_t
        {
          public:
            double_autovector_t();
            double_autovector_t(const double_autovector_t& obj);
            explicit double_autovector_t(size_t n);
            virtual ~double_autovector_t(void);

            double_autovector_t& operator=(const double_autovector_t& obj);

            void operator delete(void* pWhere);
            void* operator new(size_t uiSize);
            double& operator[](size_t uiIndex);
            const double& operator[](size_t uiIndex) const;
            size_t size() const;

          protected:
            std::vector<double>* _pv;
            ATOMIC_VARIABLE* _pCount;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // SPINNAKER_GENAPI_AUTOVECTOR_H
