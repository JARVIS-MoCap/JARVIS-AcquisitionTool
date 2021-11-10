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

#ifndef SPINNAKER_GENAPI_PORTRECORDER_H
#define SPINNAKER_GENAPI_PORTRECORDER_H

#include "SpinnakerPlatform.h"
#include "Types.h"
#include "IPortRecorder.h"
#include "PortNode.h"
#include "PortReplay.h"
#include "PortWriteList.h"

#pragma warning(push)
#pragma warning(disable : 4251) // XXX needs to have dll-interface to be used by clients of class YYY

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup PortRecorder_h PortRecorder  Class
         */
        /*@{*/

        /**
         * @brief Interface for recording write commands on a port
         */
        class SPINNAKER_API PortRecorder : virtual public IPortRecorder, virtual public PortReplay
        {
          public:
            PortRecorder();

            virtual ~PortRecorder();

            /**
             * starts logging all WriteRegister commands to a list
             */
            virtual void StartRecording(IPortWriteList* pPortRecorder);

            /**
             * stops recording
             */
            virtual void StopRecording();

            /**
             * Get the access mode of the node
             */
            virtual EAccessMode GetAccessMode() const;

            /**
             * overload SetReference for Value
             */
            virtual void SetReference(IPort* pBase);

            virtual void Replay(IPortWriteList* pPortRecorder, bool Invalidate = true)
            {
                return PortReplay::Replay(pPortRecorder, Invalidate);
            }

            virtual void Read(void* pBuffer, int64_t Address, int64_t Length)
            {
                return PortReplay::Read(pBuffer, Address, Length);
            }

            virtual void Write(const void* pBuffer, int64_t Address, int64_t Length)
            {
                return PortReplay::Write(pBuffer, Address, Length);
            }

          private:
            void* m_pPortRecorder;
        };

        /**
         * Reference to an IPortRecorder pointer
         */
        typedef PortRecorder CPortRecorderRef;

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#pragma warning(pop)

#endif // ifndef SPINNAKER_GENAPI_IPORTRECORDER_H
