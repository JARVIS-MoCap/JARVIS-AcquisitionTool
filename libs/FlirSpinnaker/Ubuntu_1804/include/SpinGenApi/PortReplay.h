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

#ifndef SPINNAKER_GENAPI_PORTREPLAY_H
#define SPINNAKER_GENAPI_PORTREPLAY_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "IPortRecorder.h"
#include "PortNode.h"
#include "PortWriteList.h"

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup PortReplay_h PortReplay Class
         */
        /*@{*/

        /**
         * @brief Interface for replaying write commands on a port
         */
        class SPINNAKER_API PortReplay : virtual public IPortReplay, virtual public PortNode
        {
          public:
            PortReplay();

            virtual ~PortReplay();

            /**
             * sends the commands to the camera.
             */
            /*! the default implementation just walks the list and issues each command
                using the WriteRegister method. Depending on the capabilities of
                the transport layer the implementation can however use a special command
                which sends all register write commands as one package.
            */
            virtual void Replay(IPortWriteList* pPortRecorder, bool Invalidate = true);

            /**
             * overload SetReference for Value
             */
            virtual void SetReference(IPort* pBase);

            void* GetPortReplayHandle();

            virtual EAccessMode GetAccessMode() const
            {
                return PortNode::GetAccessMode();
            }

            virtual void Read(void* pBuffer, int64_t Address, int64_t Length)
            {
                return PortNode::Read(pBuffer, Address, Length);
            }

            virtual void Write(const void* pBuffer, int64_t Address, int64_t Length)
            {
                return PortNode::Write(pBuffer, Address, Length);
            }

          private:
            void* m_pPortReplay;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // ifndef SPINNAKER_GENAPI_PORTREPLAY_H
