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

#ifndef FLIR_SPINNAKER_INTERFACELIST_H
#define FLIR_SPINNAKER_INTERFACELIST_H

#include "Interface/IInterfaceList.h"

namespace Spinnaker
{
    /**
     * @defgroup SpinnakerClasses Spinnaker Classes
     */

    /*@{*/

    /**
     * @defgroup InterfaceList_h InterfaceList Class
     */

    /*@{*/

    /**
     * @brief A list of the available interfaces on the system.
     */

    class SPINNAKER_API InterfaceList : public IInterfaceList
    {
      public:
        /*
         * Default Constructor
         */
        InterfaceList(void);

        /*
         * Virtual Destructor
         */
        virtual ~InterfaceList(void);

        /*
         * Copy Constructor
         */
        InterfaceList(const InterfaceList& iface);

        /**
         * Assignment operator.
         */
        InterfaceList& operator=(const InterfaceList& iface);

        /**
         * Array subscription operators
         */
        InterfacePtr operator[](unsigned int index);

        /**
         * Returns the size of the interface list.  The size is the number
         * of Interface objects stored in the list.
         *
         * @return An integer that represents the list size.
         */
        unsigned int GetSize() const;

        /**
         * Returns a pointer to an Interface object at the "index".
         *
         * @param index The index at which to retrieve the Interface object
         *
         * @return A pointer to an Interface object.
         */
        InterfacePtr GetByIndex(unsigned int index) const;

        /**
         * Clears the list of interfaces and destroys their corresponding objects.
         * It is important to first make sure there are no referenced cameras still
         * in use before calling Clear().  If a camera on any of the interfaces is still
         * in use this function will throw an exception.
         *
         */
        void Clear();

      protected:
        friend class SystemImpl;
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_INTERFACELIST_H