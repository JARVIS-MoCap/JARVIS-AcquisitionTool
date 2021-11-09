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

#ifndef FLIR_SPINNAKER_PLATFORM_H
#define FLIR_SPINNAKER_PLATFORM_H

/**
 *  @defgroup SpinnakerHeaders Spinnaker Headers
 */

/*@{*/

/**
 * @defgroup SpinnakerPlatform Spinnaker Platform
 *
 * Platform-specific header file for Spinnaker.
 * All the platform-specific code that is required by individual compilers
 * to produce the appropriate code for each platform.
 */

/*@{*/

#define SPINNAKER_API_ABSTRACT /*nothing*/
// Windows 32-bit and 64-bit
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)

#ifdef SPINNAKER_EXPORT
#define SPINNAKER_API __declspec(dllexport)
#elif defined(Spinnaker_STATIC)
#define SPINNAKER_API
#else
#define SPINNAKER_API __declspec(dllimport)
#endif

#if _MSC_VER > 1000
#pragma once
#endif

//#elif defined(MAC_OSX)

// Mac OSX

#else
// Linux and all others

// Using GCC 4 where hiding attributes is possible
#define SPINNAKER_API   __attribute__((visibility("default")))
#define SPINNAKER_LOCAL __attribute__((visibility("hidden")))

#endif

// Helper to deprecate functions and methods
// For C++14
#if __cplusplus >= 201402L
#if defined(__has_cpp_attribute)
#if __has_cpp_attribute(deprecated)
#define DEPRECATED_CLASS(msg)      [[deprecated(msg)]]
#define DEPRECATED_ENUM(msg)       enum [[deprecated(msg)]]
#define DEPRECATED_FUNC(msg, func) [[deprecated(msg)]] func
#endif
#endif
// For other C++ versions
#else
#ifdef __GNUC__
#define DEPRECATED_CLASS(msg)      __attribute__((deprecated(msg)))
#define DEPRECATED_ENUM(msg)       enum __attribute__((deprecated(msg)))
#define DEPRECATED_FUNC(msg, func) func __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
#define DEPRECATED_CLASS(msg)      __declspec(deprecated(msg))
#define DEPRECATED_ENUM(msg)       __declspec(deprecated(msg)) enum
#define DEPRECATED_FUNC(msg, func) __declspec(deprecated(msg)) func
#endif
#endif

#endif // FLIR_SPINNAKER_PLATFORM_H

/*@}*/

/*@}*/
