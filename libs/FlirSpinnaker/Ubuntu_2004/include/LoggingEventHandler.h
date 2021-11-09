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

#ifndef FLIR_SPINNAKER_LOGGING_EVENT_HANDLER_H
#define FLIR_SPINNAKER_LOGGING_EVENT_HANDLER_H

#include "Interface/ILoggingEventHandler.h"
#include "LoggingEventDataPtr.h"

namespace Spinnaker
{
    class LoggingEventDataPtr;

    /**
     *  @defgroup SpinnakerEventClasses Spinnaker EventHandler Classes
     */
    /*@{*/

    /**
     *  @defgroup LoggingEventHandler_h LoggingEventHandler Class
     */
    /*@{*/

    /**
     * @brief An event handler for capturing the device logging event.
     */

    class SPINNAKER_API LoggingEventHandler : public ILoggingEventHandler
    {
      public:
        /**
         * Default constructor.
         */
        LoggingEventHandler();

        /**
         * Virtual destructor.
         */
        ~LoggingEventHandler();

        /**
         * The callback for the log event.
         *
         * @param eventPtr The logging event pointer
         *
         */
        virtual void OnLogEvent(LoggingEventDataPtr eventPtr) = 0;

      protected:
        /**
         * Assignment operator.
         */
        LoggingEventHandler& operator=(const LoggingEventHandler&);
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_LOGGING_EVENT_HANDLER_H