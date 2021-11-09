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

#ifndef SPINNAKER_GENICAM_GCSTRING_H
#define SPINNAKER_GENICAM_GCSTRING_H

#include "SpinnakerPlatform.h"
#include <iostream>
#include <sstream>
#pragma pack(push, 8)

#define GCSTRING_NPOS size_t(-1)

namespace Spinnaker
{
    namespace GenICam
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup GCString_h GCString Class
         */
        /*@{*/

        class SPINNAKER_API gcstring
        {
#if defined(_MSC_VER) && !defined(PHARLAP_WIN32)
          public:
            /**
             * Helper class for storing shared-ownership wchar_t *
             */
            class SPINNAKER_API gcwchar
            {
              public:
                /**
                 * Creates a buffer of \a n wchar_ts
                 */
                explicit gcwchar(size_t n);

                // copy constructor
                gcwchar(const gcwchar& rhs);

                // assignment operator
                gcwchar& operator=(const gcwchar& rhs);

                /**
                 * Gets the c-string.
                 */
                const wchar_t* c_str() const;

                /**
                 * Gets the length of the buffer.
                 */
                size_t length() const;

                /**
                 * destructor
                 */
                ~gcwchar();

              private:
                class impl;
                impl* m_pimpl;
            };

#endif

            // Ctor / Dtor
            // -------------------------------------------------------------------------
          public:
            gcstring();
            gcstring(const char* pc);
            gcstring(const char* pc, size_t n);
            gcstring(size_t count, char ch);
            gcstring(const gcstring& str);
#if defined(_MSC_VER) && !defined(PHARLAP_WIN32)
            explicit gcstring(const wchar_t* pBufferUTF16);
            gcstring(const wchar_t* pBufferUTF16, size_t n);
#endif
            virtual ~gcstring(void);

            // Data access
            // -------------------------------------------------------------------------
          public:
            virtual gcstring& append(const gcstring& str);
            virtual gcstring& append(size_t count, char ch);
            virtual gcstring& assign(const gcstring& str);
            virtual gcstring& assign(size_t count, char ch);
            virtual gcstring& assign(const char* pc);
            virtual gcstring& assign(const char* pc, size_t n);
#if defined(_MSC_VER) && !defined(PHARLAP_WIN32)
            virtual gcstring& assign(const wchar_t* pStringUTF16);
            virtual gcstring& assign(const wchar_t* pStringUTF16, int n);
#endif
            virtual int compare(const gcstring& str) const;
#if defined(_MSC_VER) && !defined(PHARLAP_WIN32)
            virtual gcwchar w_str(void) const;
#endif
            virtual const char* c_str(void) const;
            virtual bool empty(void) const;
            virtual size_t find(char ch, size_t offset = 0) const;
            virtual size_t find(const gcstring& str, size_t offset = 0) const;
            virtual size_t find(const gcstring& str, size_t offset, size_t count) const;
            virtual size_t find(const char* pc, size_t offset = 0) const;
            virtual size_t find(const char* pc, size_t offset, size_t count) const;
            virtual size_t length(void) const;
            virtual size_t size(void) const;
            virtual void resize(size_t n);
            virtual size_t max_size() const;
            virtual gcstring substr(size_t offset = 0, size_t count = GCSTRING_NPOS) const;
            virtual size_t find_first_of(const gcstring& str, size_t offset = 0) const;
            virtual size_t find_first_not_of(const gcstring& str, size_t offset = 0) const;
            static size_t _npos(void);
            virtual void swap(gcstring& Right);

            // Operators
            // -------------------------------------------------------------------------
          public:
            bool operator!=(const gcstring& str) const;
            bool operator!=(const char* pc) const;
            gcstring& operator+=(const gcstring& str);
            gcstring operator+=(const gcstring& str) const;
            gcstring& operator+=(const char* pc);

            gcstring& operator+=(char ch);
            gcstring operator+=(char ch) const;
            gcstring& operator=(const gcstring& str);
#if defined(_MSC_VER) && !defined(PHARLAP_WIN32)
            gcstring& operator=(const wchar_t* pStringUTF16);
#endif
            bool operator==(const gcstring& str) const;
            bool operator==(const char* pc) const;
            bool operator<(const gcstring& str) const;
            bool operator>(const gcstring& str) const;
            operator const char*(void)const;
            void operator delete(void* pWhere);
            void operator delete(void* pWhere, void* pNewWhere);
            void* operator new(size_t uiSize);
            void* operator new(size_t uiSize, void* pWhere);
            SPINNAKER_API
            friend gcstring operator+(const gcstring& left, const gcstring& right);
            SPINNAKER_API
            friend gcstring operator+(const gcstring& left, const char* right);
            SPINNAKER_API
            friend gcstring operator+(const char* left, const gcstring& right);

          public:
            static const size_t npos;

          private:
            // redundant pointer to make the possible to see the contents of the string in the debugger
            const char* m_psz;
            // actual std::string object
            uint8_t m_strData[64];
        };

        /*@}*/
        /*@}*/
    } // namespace GenICam
} // namespace Spinnaker

namespace Spinnaker
{
    namespace GenICam
    {
        // this is necessary due to the circular dependency between string/exception
        SPINNAKER_API void ThrowBadAlloc();

        /**
         * STL getline
         */
        inline std::istream& getline(std::istream& is, Spinnaker::GenICam::gcstring& str)
        {
            try
            {
                std::string tmp;
                std::getline(is, tmp);
                str.assign(tmp.c_str(), tmp.size());
            }
            catch (std::bad_alloc&)
            {
                ThrowBadAlloc();
            }
            return is;
        }

        /**
         * STL getline
         */
        inline std::istream& getline(std::istream& is, Spinnaker::GenICam::gcstring& str, char delim)
        {
            try
            {
                std::string tmp;
                std::getline(is, tmp, delim);
                str.assign(tmp.c_str(), tmp.size());
            }
            catch (std::bad_alloc&)
            {
                ThrowBadAlloc();
            }
            return is;
        }
    } // namespace GenICam
} // namespace Spinnaker

/**
 * STL operator out
 */
inline std::ostream& operator<<(std::ostream& ostr, const Spinnaker::GenICam::gcstring& str)
{
    try
    {
        // use formatted output operator of std::string
        ostr << str.c_str();
    }
    catch (std::bad_alloc&)
    {
        Spinnaker::GenICam::ThrowBadAlloc();
    }
    return ostr;
}

/**
 * STL operator in
 */
inline std::istream& operator>>(std::istream& istr, Spinnaker::GenICam::gcstring& str)
{
    try
    {
        std::string tmp;
        istr >> tmp;
        str.assign(tmp.c_str(), tmp.size());
    }
    catch (std::bad_alloc&)
    {
        Spinnaker::GenICam::ThrowBadAlloc();
    }
    return istr;
}

#pragma pack(pop)

#endif // SPINNAKER_GENICAM_GCSTRING_H
