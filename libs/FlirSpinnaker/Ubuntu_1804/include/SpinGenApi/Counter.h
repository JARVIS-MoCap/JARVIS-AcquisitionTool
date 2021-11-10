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

#ifndef SPINNAKER_GENAPI_COUNTER_H
#define SPINNAKER_GENAPI_COUNTER_H

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup Counter_h Counter Class
         */
        /*@{*/

        /**
         * @brief Definition of a simple Counter class
         */

        class Counter
        {
          public:
            Counter() : m_value(0)
            {
            }

            unsigned int GetValue() const
            {
                return m_value;
            }

            unsigned int operator++() // prefix
            {
                return ++m_value;
            }

            unsigned int operator++(int) // postfix
            {
                return m_value++;
            }

            unsigned int operator--(int) // postfix
            {
                assert(m_value > 0);
                return m_value--;
            }

            unsigned int operator--() // prefix
            {
                assert(m_value > 0);
                return --m_value;
            }

            operator unsigned int()
            {
                return m_value;
            }

            bool IsZero()
            {
                return m_value == 0;
            }

          private:
            unsigned int m_value;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // SPINNAKER_GENAPI_COUNTER_H
