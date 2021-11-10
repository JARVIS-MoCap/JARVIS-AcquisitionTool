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

#ifndef SPINNAKER_GENICAM_GCUTILITIES_H_
#define SPINNAKER_GENICAM_GCUTILITIES_H_

#include "SpinnakerPlatform.h"
#include "GCTypes.h"
#include "GCString.h"
#include "GCStringVector.h"

#if defined(_WIN32)
#include <windows.h>
#endif

#if defined(UNDER_RTSS)
#define USE_TEMP_CACHE_FILE 0
#else
#define USE_TEMP_CACHE_FILE 1
#endif // defined(UNDER_RTSS)

#if defined(UNDER_RTSS)
#define USE_TEMP_CACHE_FILE 0
#else
#define USE_TEMP_CACHE_FILE 1
#endif // defined(UNDER_RTSS)

#if defined(_MSC_VER)
#if defined(_WIN64)
#define PLATFORM_NAME "Win64_x64"
#else
#define PLATFORM_NAME "Win32_i86"
#endif
#elif defined(__GNUC__)
#define GENICAM_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#if defined(__LP64__)
#if defined(__linux__)
#define PLATFORM_NAME "Linux64_x64"
#elif defined(__APPLE__)
#define PLATFORM_NAME "Maci64_x64"
#else
#error Unknown Platform
#endif
#else
#if defined(__linux__)
#define PLATFORM_NAME "Linux32_i86"
#elif defined(__APPLE__)
#define PLATFORM_NAME "Maci64_x64"
#elif defined(VXWORKS)
#define PLATFORM_NAME "VxWorks_PPC"
#else
#error Unknown Platform
#endif
#endif
#else
#error Unknown Platform
#endif

#ifndef GC_COUNTOF
#define GC_COUNTOF(arr) (sizeof(arr) / sizeof(arr)[0])
#endif

namespace Spinnaker
{
    namespace GenICam
    {
        /**
         *  @defgroup SpinnakerGenApiUtilities Spinnaker GenApi Utilities
         */
        /*@{*/

        /**
         *  @defgroup GCUtilities_h GCUtilities Utility
         */
        /*@{*/

        /**
         * This verifies at runtime if there was no loss of data if an type Ts (e.g. int64t) was downcast
         * to type Td (e.g. int32_t)
         */
        template <typename Td, typename Ts> inline Td INTEGRAL_CAST2(Ts s);

        /**
         * This verifies at runtime if there was no loss of data if an int64_t was downcast
         * to type T (e.g. int32_t)
         */
        template <typename T> inline T INTEGRAL_CAST(int64_t ll);

        /**
         * Returns true if an environment variable exists
         */
        SPINNAKER_API bool DoesEnvironmentVariableExist(const Spinnaker::GenICam::gcstring& VariableName);

        /**
         * Retrieve the value of an environment variable
         * \throw runtime_exception if not found
         */
        SPINNAKER_API gcstring GetValueOfEnvironmentVariable(const gcstring& VariableName);

        /**
         * Retrieve the value of an environment variable
         * @return true if environment variable was found, otherwise false
         */
        SPINNAKER_API bool GetValueOfEnvironmentVariable(const gcstring& VariableName, gcstring& VariableContent);

#if defined(UNDER_RTSS)
        /**
         * Returns true if a file exists
         */
        SPINNAKER_API bool DoesFileExist(const gcstring& FilePath);
#endif // defined(UNDER_RTSS)

        /**
         * Converts \ to / and replaces all unsave characters by their %xx equivalent
         * \ingroup Base_PublicUtilities
         */
        SPINNAKER_API gcstring UrlEncode(const gcstring& Input);

        /**
         * Replaces %xx escapes by their char equivalent
         * \ingroup Base_PublicUtilities
         */
        SPINNAKER_API gcstring UrlDecode(const gcstring& Input);

        /**
         * Replaces $(ENVIRONMENT_VARIABLES) in a string and replace ' ' with %20
         * \ingroup Base_PublicUtilities
         */
        SPINNAKER_API void ReplaceEnvironmentVariables(gcstring& Buffer, bool ReplaceBlankBy20 = false);

        /**
         * Retrieve the path of the GenICam cache folder
         * The path to the cache folder can be stored by calling SetGenICamCacheFolder().
         *   If GetGenICamCacheFolder() is called before SetGenICamCacheFolder(), it will return
         *   the value of environment variable GENICAM_CACHE_Vx_y.  If this environment variable does
         *   not exist, an exception will be thrown.
         */
        SPINNAKER_API gcstring GetGenICamCacheFolder(void);

        /**
         * Retrieve the path of the GenICam logging properties file
         *
         * The path to the logging properties file can be stored by calling SetGenICamLogConfig().
         *   If GetGenICamLogConfig() is called before SetGenICamLogConfig(), it will return
         *   the value of environment variable GENICAM_LOG_CONFIG_Vx_y.  If this environment variable does
         *   not exist, an exception will be thrown.
         */
        SPINNAKER_API gcstring GetGenICamLogConfig(void);

        /**
         * Retrieve the path of the CLProtocol folder
         * The path to the CLProtocol folder can be stored by calling SetGenICamCLProtocolFolder().
         *   If GetGenICamCLProtocolFolder() is called before SetGenICamCLProtocolFolder(), it will return
         *   the value of environment variable GENICAM_CLPROTOCOL.  If this environment variable does
         *   not exist, an exception will be thrown.
         */
        SPINNAKER_API gcstring GetGenICamCLProtocolFolder(void);

        /**
         * Stores the path of the GenICam cache folder
         */
        SPINNAKER_API void SetGenICamCacheFolder(const gcstring& path);

        /**
         * Stores the path of the GenICam logging properties file
         */
        SPINNAKER_API void SetGenICamLogConfig(const gcstring& path);

        /**
         * Stores the path of the CLProtocol folder
         */
        SPINNAKER_API void SetGenICamCLProtocolFolder(const gcstring& path);

        /**
         * splits str input string into a list of tokens using the delimiter
         */
        SPINNAKER_API void Tokenize(
            const gcstring& str,             /*!< string to be split*/
            gcstring_vector& tokens,         /*!< result of the splitting operation*/
            const gcstring& delimiters = " " /*!< delimiters for the splitting*/
        );

        /**
         * Gets a list of files or directories matching a given FileTemplate
         */
        SPINNAKER_API void GetFiles(
            const gcstring& FileTemplate, /*!> The file template. Can contain environment variables.*/
            gcstring_vector& FileNames,   /*!> A list of files matching the file template*/
            const bool DirectoriesOnly =
                false); /*!> true = only subdirectories (ex . and ..) are retrieved; false = only files are retrieved*/

        /**
         * Gets the full path to the module (DLL/SO) containing the given \a pFunction; empty string if not found.
         */
        SPINNAKER_API gcstring GetModulePathFromFunction(void* pFunction);

        /*@}*/
        /*@}*/
    } // namespace GenICam
} // namespace Spinnaker

#define GENICAM_UNUSED(unused_var) ((void)(unused_var))

#if !defined(GENICAM_DEPRECATED)
#if defined(__GNUC__) && (__GNUC__ >= 3) && defined(__GNUC_MINOR__) &&                                                 \
    (__GNUC_MINOR__ >= 1) // is at least GCC 3.1 compiler?
#define GENICAM_DEPRECATED(FUNCTION) FUNCTION __attribute__((deprecated))
#elif defined(_MSC_VER) && (_MSC_VER >= 1300) // is at least VC 2003 compiler?
#define GENICAM_DEPRECATED(FUNCTION) __declspec(deprecated) FUNCTION
#else
#define GENICAM_DEPRECATED(FUNCTION) FUNCTION
#endif // compiler check
#endif // #if !defined(GENICAM_DEPRECATED)

///////////////////////////////////////////////////////////////////////////////
//
//    Useful to create pragma message output reconized by VisualStudio
//
//    Usage:
//       #pragma message ( __ERR__ "Invalid DLL ABI" )
//
///////////////////////////////////////////////////////////////////////////////
// Message formater
#define _TO_STRING(__stN) #__stN
#ifndef EXPAND_TO_STRINGISE
#define EXPAND_TO_STRINGISE(__stN) _TO_STRING(__stN)
#endif
#define __LINE_STR__               EXPAND_TO_STRINGISE(__LINE__)
#define __LOCATION__               __FILE__ "(" __LINE_STR__ ")"
#define __OUTPUT_FORMATER__(_type) __LOCATION__ " : " _type " : "

// Message types
#define __WARN__ __OUTPUT_FORMATER__("WARNING")
#define __ERR__  __OUTPUT_FORMATER__("ERROR")
#define __TODO__ __OUTPUT_FORMATER__("TBD")

#endif // SPINNAKER_GENICAM_GCUTILITIES_H_
