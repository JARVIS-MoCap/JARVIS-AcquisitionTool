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

#ifndef SPINNAKER_GENAPI_GCSYNCH_H
#define SPINNAKER_GENAPI_GCSYNCH_H

#include "GCTypes.h"
#include "GCString.h"

#if defined(_WIN32)
#include <windows.h>
#include <winbase.h>
#elif defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__))
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <list>
#elif defined(VXWORKS)
#include <vxworks.h>
#include <taskLib.h>
#else
#error No/unknown platform thread support
#endif

namespace Spinnaker
{
    namespace GenICam
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup GCSynch_h GCSynch Class
         */
        /*@{*/

        //-----------------------------------------------------------------
        // CLock
        //-----------------------------------------------------------------

        /**
         * @brief A lock class
         */
        class SPINNAKER_API CLock
        {
          public:
            /**
             * Constructor
             */
            CLock();

            /**
             * Destructor
             */
            ~CLock();

            /**
             * tries to enter the critical section; returns true if successful
             */
            bool TryLock();

            /**
             * enters the critical section (may block)
             */
            void Lock();

            /**
             * leaves the critical section
             */
            void Unlock();

          private:
            /**
             * no copy constructor
             */
            CLock(const CLock&);

            /**
             * no assignment operator
             */
            CLock& operator=(const CLock&);

          protected:
#if defined(_WIN32)
            /**
             * The critical section object
             */
            CRITICAL_SECTION m_csObject;
#elif defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__))
            /**
             * the mutex object
             */
            pthread_mutex_t m_mtxObject;
#elif defined(VXWORKS)
            SEM_ID m_sem;
#else
#error No/unknown platform thread support
#endif
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup GCSynch_h GCSynch Class
         */
        /*@{*/

        /**
         * This class is for testing purposes only. It should not be used for
         * client code because it exists only for Windows but not for Linux
         * since it uses internal data structures of a Win32 object
         */
        class SPINNAKER_API CLockEx : public CLock
        {
          public:
#if defined(_WIN32)
            /**
             * Gives access to internal data member for test and purposes
             */
            int64_t GetLockCount();

            /**
             * Gives access to internal data member for test and purposes
             */
            int64_t GetRecursionCount();

#elif defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__) || defined(VXWORKS))
            // nothing implemented for Unix
#else
#error No/unknown platform support
#endif

          private:
            /**
             * no copy constructor
             */
            CLockEx(const CLockEx&);

            /**
             * no assignment operator
             */
            CLockEx& operator=(const CLockEx&);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup GCSynch_h GCSynch Class
         */
        /*@{*/

        //-----------------------------------------------------------------
        // AutoLock
        //-----------------------------------------------------------------
        class AutoLock
        {
            CLock& m_Lock;

          public:
            AutoLock(CLock& lock) : m_Lock(lock)
            {
                m_Lock.Lock();
            }

            ~AutoLock()
            {
                m_Lock.Unlock();
            }

          private:
            AutoLock& operator=(const AutoLock&);
            AutoLock(const AutoLock&);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup GCSynch_h GCSynch Class
         */
        /*@{*/

        //-----------------------------------------------------------------
        // template LockableObject<Object,ThreadingModel>
        //-----------------------------------------------------------------

        /**
         * @brief Instance-Lock for an object
         */
        template <class Object> class LockableObject
        {
          public:
            mutable CLock m_Lock;

            class Lock;
            friend class Lock;

            /** A scopelevel Lock class.
             * Automatically acquires the lock when created and releases
             * it when destroyed.
             */
            class Lock
            {
                /// Reference to outer object
                const LockableObject<Object>& m_Object;

              public:
                Lock(const LockableObject<Object>& obj) : m_Object(obj)
                {
                    m_Object.m_Lock.Lock();
                }

                ~Lock()
                {
                    m_Object.m_Lock.Unlock();
                }

              private:
                Lock& operator=(const Lock&);
            };

            /// Get a new lock
            Lock GetLock() const
            {
                return Lock(*this);
            }
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup GCSynch_h GCSynch Class
         */
        /*@{*/

        /**
         * @brief Named global lock which can be used over process boundaries
         */
        class SPINNAKER_API CGlobalLock
        {
          public:
            /**
             * Creates a global lock object name pszName.
             * In case an object with the same name already exists
             * a reference to the existing object will be created.
             * If pszName is NULL an unnamed object will be created.
             */
            explicit CGlobalLock(const char* pszName);
#if defined(_WIN32) && !defined(PHARLAP_WIN32)
            /**
             * Creates a global lock object name pszName.
             * In case an object with the same name already exists
             * a reference to the existing object will be created.
             * If pszName is NULL an unnamed object will be created.
             */
            explicit CGlobalLock(const wchar_t* pszName);
#endif
            /**
             * Creates a global lock object name strName.
             * In case an object with the same name already exists
             * a reference to the existing object will be created.
             * If strName is empty an unnamed object will be created.
             */
            explicit CGlobalLock(const gcstring& strName);

            ~CGlobalLock();

          public:
            /**
             * tests whether the lock is valid
             */
            bool IsValid(void) const;

            /**
             * enters the lock (may block)
             */
            bool Lock(unsigned int timeout_ms);

            /**
             * tries to enter the lock and returns immediately when not possible
             */
            bool TryLock(void);

            /**
             * leaves the lock
             */
            void Unlock(void);

#if defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__))
            // creates a hashed name instead of the real name
            void HashSemName(const gcstring& strName);
#endif

          protected:
#if defined(_WIN32)
            HANDLE m_handle;
#elif defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__))
            gcstring m_semName;
            sem_t* m_handle;
#elif VXWORKS
            // There are no named locks on VxWorks. While we could use a single global lock, we
            // will just rely on the caller to add their own locking in
#else
#error No/unknown platform thread support
#endif

            // This is for debugging/assertions only
            // the d'tor check whether this is 0 in debug builds
            // in release builds this is always 0
            mutable long m_DebugCount;

          private:
            // not copyable
            CGlobalLock(const CGlobalLock&);
            CGlobalLock& operator=(const CGlobalLock&);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup GCSynch_h GCSynch Class
         */
        /*@{*/

        /**
         * @brief Unlocks the global lock object on destruction
         *
         * This is for automatic UNLOCKING only.
         * We can't do automatic locking here since there is no returnvalue for contructors
         */
        //-----------------------------------------------------------------
        // unlocks the global lock object on destruction
        // this is for automatic UNLOCKING only.
        // we can't do automatic locking here since we don't get a returnvalue from the c'tor
        //-----------------------------------------------------------------
        class SPINNAKER_API CGlobalLockUnlocker
        {
          protected:
            CGlobalLock& m_Lock;
            bool m_enabled;

          public:
            CGlobalLockUnlocker(CGlobalLock& lock)
                : m_Lock(lock),
                  m_enabled(true) // this allows the auto unlock to be turned off for messy code structures
            {
                // explicitly don't lock the object here since we want to do this manually and handle the return value
                // properly
            }

            ~CGlobalLockUnlocker()
            {
                UnlockEarly();
            }

            /**
             * This function allows to unlock the object early before the object is destroyed
             */
            void UnlockEarly(void)
            {
                if (m_enabled)
                {
                    m_enabled = false;
                    m_Lock.Unlock();
                }
            }

          private:
            CGlobalLockUnlocker& operator=(const CGlobalLockUnlocker&);
            CGlobalLockUnlocker(const CGlobalLockUnlocker&);
        };

        /*@}*/
        /*@}*/
    } // namespace GenICam
} // namespace Spinnaker

#endif // SPINNAKER_GENAPI_GCSYNCH_H
