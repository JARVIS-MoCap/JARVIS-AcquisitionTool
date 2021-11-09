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

#ifndef PGR_LOGGINGEVENTDATA_H
#define PGR_LOGGINGEVENTDATA_H

#include "Spinnaker.h"

namespace Spinnaker
{
    /**
     *  @defgroup SpinnakerEventClasses Spinnaker EventHandler Classes
     */

    /*@{*/

    /**
     *  @defgroup LoggingEventData_h Logging EventHandler Class
     */

    /*@{*/

    /**
     * @brief The LoggingEventData object.
     */

    class SPINNAKER_API LoggingEventData
    {
      public:
        /**
         * Default Destructor
         */
        ~LoggingEventData();

        /**
         * Gets the logging event category name.
         *
         * @return The category name
         */
        const char* GetCategoryName();

        /**
         * Gets the logging event message.
         *
         * @return The log message
         */
        const char* GetLogMessage();

        /**
         * Gets the logging event's Nested Diagnostic Context (NDC).
         *
         * @return The log event's NDC
         */
        const char* GetNDC();

        /**
         * Gets the logging event priority.
         *
         * @return The log priority
         */
        const int GetPriority();

        /**
         * Gets the logging event thread name.
         *
         * @return The thread name
         */
        const char* GetThreadName();

        /**
         * Gets the logging event time stamp.
         *
         * @return The time stamp of the log
         */
        const char* GetTimestamp();

        /**
         * Gets the logging event priority name.
         *
         * @return The priority name of the log
         */
        const char* GetPriorityName();

      protected:
        friend class SystemImpl;

        /**
         * Default Constructor
         */
        LoggingEventData(void* data);

      private:
        struct LoggingEventDataInternal; // Forward declaration

        LoggingEventDataInternal* m_pLoggingEventData;
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#endif // PGR_LoggingEventData_H