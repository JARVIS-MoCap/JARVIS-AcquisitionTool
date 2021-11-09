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

#ifndef SPINNAKER_GENAPI_COMPATIBILITY_H
#define SPINNAKER_GENAPI_COMPATIBILITY_H

#if defined(_MSC_VER) && defined(_WIN32)

typedef struct _SPIN_GUID
{
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
} SPIN_GUID;

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

#elif defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__) || defined(VXWORKS))

#include <stdint.h>
/**
 * Watch out!
 * In order not to break existing code, we have to duplicate the
 * broken MS Windows GUID handling. Never mix with code using the
 * rfc4122-compliant uuid framework implemented by libuuid!
 */
typedef struct _SPIN_GUID
{
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t Data4[8];
} __attribute__((packed)) SPIN_GUID;

#else
#error Unsupported platform
#endif

#if defined(__x86_64) // GNUC && 64 Bit
#define FMT_I64 "l"
#else // all 32 bit and all Windows
#define FMT_I64 "ll"
#endif

#endif // ifndef SPINNAKER_GENAPI_COMPATIBILITY_H
