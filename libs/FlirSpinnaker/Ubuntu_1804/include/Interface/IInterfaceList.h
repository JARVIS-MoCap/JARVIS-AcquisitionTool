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

#ifndef FLIR_SPINNAKER_IINTERFACELIST_H
#define FLIR_SPINNAKER_IINTERFACELIST_H

#include "InterfacePtr.h"

namespace Spinnaker
{
    /**
     * @defgroup SpinnakerClasses Spinnaker Classes
     */

    /*@{*/

    /**
     * @defgroup IInterfaceList_h IInterfaceList Class
     */

    /*@{*/

    /**
     * @brief The interface file for InterfaceList class.
     */

    class SPINNAKER_API IInterfaceList
    {
      public:
        virtual ~IInterfaceList(void){};
        virtual InterfacePtr operator[](unsigned int index) = 0;
        virtual unsigned int GetSize() const = 0;
        virtual InterfacePtr GetByIndex(unsigned int index) const = 0;
        virtual void Clear() = 0;

      protected:
        struct InterfaceListData; // Forward declaration
        InterfaceListData* m_pInterfaceListData;

        IInterfaceList(void){};
        IInterfaceList(const IInterfaceList&){};
        IInterfaceList& operator=(const IInterfaceList&);
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_IINTERFACELIST_H