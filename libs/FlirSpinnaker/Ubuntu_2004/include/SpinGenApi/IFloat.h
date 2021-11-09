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

#ifndef SPINNAKER_GENAPI_IFLOAT_H
#define SPINNAKER_GENAPI_IFLOAT_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "IValue.h"
#include "GCString.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4251) // XXX needs to have dll-interface to be used by clients of class YYY
#endif

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiInterfaces Spinnaker GenApi Interfaces
         */
        /*@{*/

        /**
         *  @defgroup IFloat_h IFloat Interface
         */
        /*@{*/

        //*************************************************************
        // IFloat interface
        //*************************************************************

        /**
         * @brief Interface for float properties
         */
        interface SPINNAKER_API_ABSTRACT IFloat : virtual public IValue
        {
            /**
             * Set node value
             *
             * @param Value The value to set
             * @param Verify Enables AccessMode and Range verification (default = true)
             */
            virtual void SetValue(double Value, bool Verify = true) = 0;

            /**
             * Set node value
             */
            virtual IFloat& operator=(double Value) = 0;

            /**
             * Get node value
             *
             * @param Verify Enables Range verification (default = false). The AccessMode is always checked
             * @param IgnoreCache If true the value is read ignoring any caches (default = false)
             * @return The value read
             */
            virtual double GetValue(bool Verify = false, bool IgnoreCache = false) = 0;

            /**
             * Get node value
             */
            virtual double operator()() = 0;

            /**
             * Get node value
             */
            virtual double operator*() = 0;

            /**
             * Get minimum value allowed
             */
            virtual double GetMin() = 0;

            /**
             * Get maximum value allowed
             */
            virtual double GetMax() = 0;

            /**
             * True if the float has a constant increment
             */
            virtual bool HasInc() = 0;

            /**
             * Get increment mode
             */
            virtual EIncMode GetIncMode() = 0;

            /**
             * Get the constant increment if there is any
             */
            virtual double GetInc() = 0;

            /**
             * Get list of valid value
             */
            virtual double_autovector_t GetListOfValidValues(bool bounded = true) = 0;

            /**
             * Get recommended representation
             */
            virtual ERepresentation GetRepresentation() = 0;

            /**
             * Get the physical unit name
             */
            virtual GenICam::gcstring GetUnit() const = 0;

            /**
             * Get the way the float should be converted to a string
             */
            virtual EDisplayNotation GetDisplayNotation() const = 0;

            /**
             * Get the precision to be used when converting the float to a string
             */
            virtual int64_t GetDisplayPrecision() const = 0;

            /**
             * Restrict minimum value
             */
            virtual void ImposeMin(double Value) = 0;

            /**
             * Restrict maximum value
             */
            virtual void ImposeMax(double Value) = 0;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // ifndef SPINNAKER_GENAPI_IFLOAT_H
