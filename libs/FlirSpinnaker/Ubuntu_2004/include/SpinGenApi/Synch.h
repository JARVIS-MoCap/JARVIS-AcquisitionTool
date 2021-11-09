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

#ifndef SPINNAKER_GENAPI_SYNCH_H
#define SPINNAKER_GENAPI_SYNCH_H

#include "SpinnakerPlatform.h"

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup Synch_h Synch Class
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
             * Constructor
             */
            CLock(void* pLock);

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
            friend class NodeMap;
            void* m_lock;
            bool m_bOwnLock;
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup Synch_h Synch Class
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

#elif defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__))
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

          protected:
            void* m_lockEx;
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup Synch_h Synch Class
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
    } // namespace GenApi
} // namespace Spinnaker

#endif // SPINNAKER_GENAPI_SYNCH_H
