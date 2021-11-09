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

#ifndef SPINNAKER_GENICAM_GCSTRINGLIST_H
#define SPINNAKER_GENICAM_GCSTRINGLIST_H

#include "SpinnakerPlatform.h"
#include "GCString.h"

#if defined(_WIN32) || (defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__) || defined(VXWORKS)))

namespace Spinnaker
{
    namespace GenICam
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup GCStringVector_h GCStringVector Class
         */
        /*@{*/

        /**
         * @brief A vector of gcstrings which is a clone of std::vector<std::string>
         */
        class SPINNAKER_API gcstring_vector
        {
            // Nested types
            // ---------------------------------------------------------------------------
          public:
            class SPINNAKER_API const_iterator
            {
                // Ctor / Dtor
                // -------------------------------------------------------------------------
              public:
                const_iterator(gcstring* pStr = 0);

                // Operators
                // -------------------------------------------------------------------------
              public:
                const gcstring& operator*(void)const;
                const gcstring* operator->(void)const;
                const_iterator& operator++(void);
                const_iterator operator++(int);
                const_iterator& operator--(void);
                const_iterator operator--(int);
                const_iterator& operator+=(intptr_t iInc);
                const_iterator operator+(intptr_t iInc) const;
                const_iterator& operator-=(intptr_t iDec);
                intptr_t operator-(const const_iterator& iter) const;
                const_iterator operator-(intptr_t iDec) const;
                const gcstring& operator[](intptr_t iIndex) const;
                bool operator==(const const_iterator& iter) const;
                bool operator!=(const const_iterator& iter) const;
                bool operator<(const const_iterator& iter) const;
                bool operator>(const const_iterator& iter) const;
                bool operator<=(const const_iterator& iter) const;
                bool operator>=(const const_iterator& iter) const;
                SPINNAKER_API
                friend const_iterator operator+(intptr_t iInc, const const_iterator& iter);

                // Member
                // -------------------------------------------------------------------------
              protected:
                gcstring* _ps;
            };

            class SPINNAKER_API iterator : public const_iterator
            {
                // Ctor / Dtor
                // -------------------------------------------------------------------------
              public:
                iterator(gcstring* pStr = 0);

                // Operators
                // -------------------------------------------------------------------------
              public:
                gcstring& operator*(void)const;
                gcstring* operator->(void)const;
                iterator& operator++(void);
                iterator operator++(int);
                iterator& operator--(void);
                iterator operator--(int);
                iterator& operator+=(intptr_t iInc);
                iterator operator+(intptr_t iInc) const;
                iterator& operator-=(intptr_t iDec);
                intptr_t operator-(const iterator& iter) const;
                iterator operator-(intptr_t iDec) const;
                gcstring& operator[](intptr_t iIndex) const;
                SPINNAKER_API
                friend iterator operator+(intptr_t iInc, const iterator& iter);
            };

            // Ctor / Dtor
            // ---------------------------------------------------------------------------
          public:
            gcstring_vector(void);
            explicit gcstring_vector(size_t uiSize, const gcstring& str = gcstring());
            gcstring_vector(const gcstring_vector& obj);
            virtual ~gcstring_vector(void);

            // Element access
            // ---------------------------------------------------------------------------
          public:
            virtual void assign(size_t n, const gcstring& val);
            virtual void clear(void);
            virtual iterator erase(iterator pos);
            virtual gcstring& at(size_t uiIndex);
            virtual const gcstring& at(size_t uiIndex) const;
            virtual gcstring& back(void);
            virtual const gcstring& back(void) const;
            virtual iterator begin(void);
            virtual const_iterator begin(void) const;
            virtual size_t capacity(void) const;
            virtual iterator end(void);
            virtual const_iterator end(void) const;
            virtual gcstring& front(void);
            virtual const gcstring& front(void) const;
            virtual size_t max_size(void) const;
            virtual size_t size(void) const;
            virtual iterator insert(iterator pos, const gcstring& str);
            virtual bool empty(void) const;
            virtual void pop_back(void);
            virtual void push_back(const gcstring& str);
            virtual void resize(size_t uiSize, const gcstring& str = gcstring());
            virtual void reserve(size_t uiSize);

            // Do not use the methods below - they only exist for
            // backwards compatibility
            virtual gcstring_vector& assign(const gcstring_vector& obj);
            virtual void erase(size_t uiIndex);
            virtual void insert(size_t uiIndex, const gcstring& str);

            // Operators
            // ---------------------------------------------------------------------------
          public:
            gcstring_vector& operator=(const gcstring_vector& obj);
            gcstring& operator[](size_t uiIndex);
            const gcstring& operator[](size_t uiIndex) const;
            void operator delete(void* pWhere);
            void* operator new(size_t uiSize);

            // Member
            // ---------------------------------------------------------------------------
          private:
            void* _pv;
        };

        /*@}*/
        /*@}*/
    } // namespace GenICam
} // namespace Spinnaker

#else
#error No known support for shared libraries
#endif

#endif // SPINNAKER_GENICAM_GCSTRINGLIST_H
