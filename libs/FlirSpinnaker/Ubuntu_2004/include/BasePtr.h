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

#ifndef FLIR_SPINNAKER_BASE_PTR_H
#define FLIR_SPINNAKER_BASE_PTR_H

#include "SpinnakerPlatform.h"

namespace Spinnaker
{
    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /*@{*/

    /**
     *  @defgroup BasePtr_h BasePtr Class
     */
    /*@{*/

    /**
     * @brief The base class of the SystemPtr, CameraPtr, InterfacePtr, ImagePtr and LoggingEventDataPtr objects.
     */
    template <class T, class B = T> class SPINNAKER_API BasePtr
    {
      public:
        //! Default constructor.
        BasePtr(void) throw();

        virtual ~BasePtr(void);

        //! Copy constructor
        BasePtr(const BasePtr& other) throw();

        //! Assign INode Pointer
        virtual BasePtr& operator=(const BasePtr& rhs);

        virtual BasePtr& operator=(const int nMustBeNull);

        virtual BasePtr& operator=(const long nMustBeNull);

        virtual BasePtr& operator=(const std::nullptr_t nullPtr);

        //! Dereferencing
        virtual operator T*(void)const;

        //! Dereferencing
        virtual T* operator->(void)const;

        //! True if the pointer is valid
        virtual bool IsValid() const throw();

        //! True if the pointer is valid
        virtual operator bool(void) const throw();

        //! Pointer equal
        virtual bool operator==(const BasePtr& rT) const;

        //! Pointer equal
        virtual bool operator==(std::nullptr_t) const;

        //! Pointer equal
        virtual bool operator==(int nMustBeNull) const;

        //! Pointer equal
        virtual bool operator==(long nMustBeNull) const;

        //! get()
        virtual T* get() const;

      protected:
        struct PointerData;
        //! Underlying raw pointer.
        PointerData* m_pT;
    };

    //! Pointer equal
    template <class T, class B> inline bool operator==(const std::nullptr_t, const BasePtr<T, B>& rhs)
    {
        return rhs == nullptr;
    }

    /** @}*/

    /** @}*/
} // namespace Spinnaker
#endif // FLIR_SPINNAKER_BASE_PTR_H