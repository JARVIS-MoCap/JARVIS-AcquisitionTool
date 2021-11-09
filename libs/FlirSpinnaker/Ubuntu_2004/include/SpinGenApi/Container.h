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

#ifndef SPINNAKER_GENAPI_NODEVECTOR_H
#define SPINNAKER_GENAPI_NODEVECTOR_H

#include "SpinnakerPlatform.h"
#include <stdint.h>
#include <iterator>
#include <memory>

#include <vector>

/**
 *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
 */

/*@{*/

/**
 *  @defgroup Container_h Container Class
 */

/*@{*/

#ifndef _WIN32
#include <stdint.h>
#endif

#if defined(__GNUC__) && !defined(VXWORKS) && !defined(__APPLE__) &&                                                   \
    !defined(SWIG) // ignore if SWIG is parsing this file
using namespace __gnu_cxx;
#endif

#if defined(__GNUC__) && defined(__linux__)
#include <cstddef>
#endif

#if defined(_WIN32) || (defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__) || defined(VXWORKS)))

#ifdef _WIN32
// conversion from 'uintptr_t' to 'void *' of greater size
// This is a portability warning
#pragma warning(disable : 4312)
#endif // _WIN32

// MacOS doesn't like us redefining standard namespace
#if !defined(__APPLE__)
namespace std
{
    /**
     *  @defgroup STDClasses std Classes
     */

    /*@{*/

    template <class T> class allocator;
    template <class T, class Allocator> class vector;

    /*@}*/
} // namespace std
#endif

namespace Spinnaker
{
    namespace GenApi
    {
        struct INode;
        struct IValue;

        //*************************************************************
        // N O D E _ V E C T O R
        //*************************************************************

        /**
         *  @addtogroup Container_h Container Class
         */
        /*@{*/

        /**
         * @brief A vector of INode pointers
         */
        class SPINNAKER_API node_vector
        {
          public:
            typedef INode* T;

            // Nested types
            // ---------------------------------------------------------------------------
            class SPINNAKER_API const_iterator
            {
                // iterator traits
                // ------------------------------------------------------------------------
              public:
                typedef std::random_access_iterator_tag iterator_category;
                typedef T value_type;
                typedef ptrdiff_t difference_type;
                typedef T* pointer;
                typedef T& reference;
                // Ctor / Dtor
                // -------------------------------------------------------------------------
              public:
                const_iterator(T* pPtr = 0);

                // Operators
                // -------------------------------------------------------------------------
              public:
                const T& operator*(void)const;
                const_iterator& operator++(void);
                const_iterator operator++(int);
                const_iterator& operator--(void);
                const_iterator operator--(int);
                const_iterator& operator+=(intptr_t iInc);
                const_iterator operator+=(intptr_t iInc) const;
                const_iterator operator+(intptr_t iInc) const;
                const_iterator& operator-=(intptr_t iDec);
                const_iterator operator-=(intptr_t iDec) const;
                intptr_t operator-(const const_iterator& iter) const;
                const_iterator operator-(intptr_t iDec) const;
                const T& operator[](intptr_t iIndex) const;
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
                T* _ps;
            };

            class SPINNAKER_API iterator : public const_iterator
            {
              public:
                // iterator traits
                // -------------------------------------------------------------------------
                typedef std::random_access_iterator_tag iterator_category;
                typedef T value_type;
                typedef const_iterator::difference_type difference_type;
                typedef const_iterator::pointer pointer;
                typedef const_iterator::reference reference;
                // Ctor / Dtor
                // -------------------------------------------------------------------------
              public:
                iterator(T* pPtr = 0);

                // Operators
                // -------------------------------------------------------------------------
              public:
                T& operator*(void)const;
                iterator& operator++(void);
                iterator operator++(int);
                iterator& operator--(void);
                iterator operator--(int);
                iterator& operator+=(intptr_t iInc);
                iterator operator+=(intptr_t iInc) const;
                iterator operator+(intptr_t iInc) const;
                iterator& operator-=(intptr_t iDec);
                iterator operator-=(intptr_t iDec) const;
                intptr_t operator-(const iterator& iter) const;
                iterator operator-(intptr_t iDec) const;
                T& operator[](intptr_t iIndex) const;
                SPINNAKER_API
                friend iterator operator+(intptr_t iInc, const iterator& iter);
            };

            // Ctor / Dtor
            // ---------------------------------------------------------------------------
          public:
            node_vector(void);
            explicit node_vector(size_t uiSize);
            node_vector(const node_vector& obj);
            virtual ~node_vector(void);

            // Element access
            // ---------------------------------------------------------------------------
          public:
            virtual void assign(size_t n, const T& val);
            virtual void clear(void);
            virtual iterator erase(iterator pos);
            virtual T& at(size_t uiIndex);
            virtual const T& at(size_t uiIndex) const;
            virtual T& back(void);
            virtual const T& back(void) const;
            virtual iterator begin(void);
            virtual const_iterator begin(void) const;
            virtual size_t capacity(void) const;
            virtual iterator end(void);
            virtual const_iterator end(void) const;
            virtual T& front(void);
            virtual const T& front(void) const;
            virtual size_t max_size(void) const;
            virtual size_t size(void) const;
            virtual iterator insert(iterator pos, const T& val);
            virtual bool empty(void) const;
            virtual void pop_back(void);
            virtual void push_back(const T& val);
            virtual void resize(size_t uiSize);
            virtual void reserve(size_t uiSize);

            // Do not use - only left in for backwards compatibility!
            virtual void erase(size_t uiIndex);
            virtual void insert(size_t uiIndex, const T& val);

            // Operators
            // ---------------------------------------------------------------------------
          public:
            node_vector& operator=(const node_vector& obj);
            T& operator[](size_t uiIndex);
            const T& operator[](size_t uiIndex) const;
            void operator delete(void* pWhere);
            void* operator new(size_t uiSize);

            // Member
            // ---------------------------------------------------------------------------
          private:
            typedef std::vector<T, std::allocator<T>> vector_t;
            vector_t* _pv;
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup Container_h Container Class
         */
        /*@{*/

        //*************************************************************
        // V A L U E _ V E C T O R
        //*************************************************************

        /**
         * @brief A vector of IValue pointers
         */
        class SPINNAKER_API value_vector
        {
          public:
            typedef IValue* T;
            // Nested types
            // ---------------------------------------------------------------------------
          public:
            class SPINNAKER_API const_iterator
            {
                // iterator traits
                // ------------------------------------------------------------------------
              public:
                typedef std::random_access_iterator_tag iterator_category;
                typedef T value_type;
                typedef ptrdiff_t difference_type;
                typedef T* pointer;
                typedef T& reference;

                // Ctor / Dtor
                // -------------------------------------------------------------------------
              public:
                const_iterator(T* pPtr = 0);

                // Operators
                // -------------------------------------------------------------------------
              public:
                const T& operator*(void)const;
                const_iterator& operator++(void);
                const_iterator operator++(int);
                const_iterator& operator--(void);
                const_iterator operator--(int);
                const_iterator& operator+=(intptr_t iInc);
                const_iterator operator+=(intptr_t iInc) const;
                const_iterator operator+(intptr_t iInc) const;
                const_iterator& operator-=(intptr_t iDec);
                const_iterator operator-=(intptr_t iDec) const;
                intptr_t operator-(const const_iterator& iter) const;
                const_iterator operator-(intptr_t iDec) const;
                const T& operator[](intptr_t iIndex) const;
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
                T* _ps;
            };

            class SPINNAKER_API iterator : public const_iterator
            {
              public:
                // iterator traits
                // -------------------------------------------------------------------------
                typedef std::random_access_iterator_tag iterator_category;
                typedef T value_type;
                typedef const_iterator::difference_type difference_type;
                typedef const_iterator::pointer pointer;
                typedef const_iterator::reference reference;
                // Ctor / Dtor
                // -------------------------------------------------------------------------
              public:
                iterator(T* pPtr = 0);

                // Operators
                // -------------------------------------------------------------------------
              public:
                T& operator*(void)const;
                iterator& operator++(void);
                iterator operator++(int);
                iterator& operator--(void);
                iterator operator--(int);
                iterator& operator+=(intptr_t iInc);
                iterator operator+=(intptr_t iInc) const;
                iterator operator+(intptr_t iInc) const;
                iterator& operator-=(intptr_t iDec);
                iterator operator-=(intptr_t iDec) const;
                intptr_t operator-(const iterator& iter) const;
                iterator operator-(intptr_t iDec) const;
                T& operator[](intptr_t iIndex) const;
                SPINNAKER_API
                friend iterator operator+(intptr_t iInc, const iterator& iter);
            };

            // Ctor / Dtor
            // ---------------------------------------------------------------------------
          public:
            value_vector(void);
            explicit value_vector(size_t uiSize);
            value_vector(const value_vector& obj);
            virtual ~value_vector(void);

            // Element access
            // ---------------------------------------------------------------------------
          public:
            virtual void assign(size_t n, const T& obj);
            virtual void clear(void);
            virtual iterator erase(iterator pos);
            virtual T& at(size_t uiIndex);
            virtual const T& at(size_t uiIndex) const;
            virtual T& back(void);
            virtual const T& back(void) const;
            virtual iterator begin(void);
            virtual const_iterator begin(void) const;
            virtual size_t capacity(void) const;
            virtual iterator end(void);
            virtual const_iterator end(void) const;
            virtual T& front(void);
            virtual const T& front(void) const;
            virtual size_t max_size(void) const;
            virtual size_t size(void) const;
            virtual iterator insert(iterator pos, const T& val);
            virtual bool empty(void) const;
            virtual void pop_back(void);
            virtual void push_back(const T& val);
            virtual void resize(size_t uiSize, const T& val);
            virtual void reserve(size_t uiSize);

            // Do not use - only left in for backwards compatibility!
            virtual void erase(size_t uiIndex);
            virtual void insert(size_t uiIndex, const T& val);

            // Operators
            // ---------------------------------------------------------------------------
          public:
            value_vector& operator=(const value_vector& obj);
            T& operator[](size_t uiIndex);
            const T& operator[](size_t uiIndex) const;
            void operator delete(void* pWhere);
            void* operator new(size_t uiSize);

            // Member
            // ---------------------------------------------------------------------------
          private:
            typedef std::vector<T, std::allocator<T>> vector_t;
            vector_t* _pv;
        };

        /**
         * a list of feature references
         */
        typedef value_vector FeatureList_t;

        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

/*@}*/
/*@}*/

#else
#error Unknown platform
#endif

#endif // SPINNAKER_GENAPI_NODEVECTOR_H
