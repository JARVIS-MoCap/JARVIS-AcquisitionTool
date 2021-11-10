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

#ifndef PGR_SPINNAKER_EXCEPTION_H
#define PGR_SPINNAKER_EXCEPTION_H

#include "SpinnakerPlatform.h"
#include "SpinnakerDefs.h"
#include <stdio.h>
#include <exception>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4275) // non dll-interface structXXX used as base
#endif

namespace Spinnaker
{
    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */

    /*@{*/

    /**
     *  @defgroup Exception_h Exception Class
     */

    /*@{*/

    /**
     * @brief The Exception object represents an error that is returned from the library.
     *        Overloaded operators allow comparisons against other Exception objects.
     */

    class SPINNAKER_API Exception : public virtual std::exception
    {

      public:
        /**
         * Default constructor.
         */
        Exception();

        /**
         * Message constructor.
         *
         * @param line Line number where the exception is thrown
         * @param fileName Name of the file called
         * @param funcName Name of the function called
         * @param errMsg A pointer to the exception message string
         * @param err Error code
         */
        Exception(
            int line,
            const char* fileName,
            const char* funcName,
            const char* errMsg,
            Error err);

        /**
         * Message constructor.
         *
         * @param line Line number where the exception is thrown
         * @param fileName Name of the file called
         * @param funcName Name of the function called
         * @param buildDate Build date
         * @param buildTime Build time
         * @param errMsg A pointer to the exception message string
         * @param err Error code
         */
        Exception(
            int line,
            const char* fileName,
            const char* funcName,
            const char* buildDate,
            const char* buildTime,
            const char* errMsg,
            Error err);

        /**
         * Copy constructor.
         */
        Exception(const Exception& except);

        /**
         * Default destructor.
         */
        virtual ~Exception() throw();

        /**
         * Assignment operator.
         */
        Exception& operator=(const Exception& except);

        /**
         * Equality operator.
         */
        bool operator==(const Error err) const;

        /**
         * Inequality operator.
         */
        bool operator!=(const Error err) const;

        /**
         * virtual override for what().
         * Gets the error code and error message.
         */
        virtual const char* what() const throw(); // add throw() to avoid looser throw specifier error

        /**
         * Gets the error code and full error message including the line, file, function, build date, and time.
         */
        const char* GetFullErrorMessage() const;

        /**
         * Accessor Functions.
         */
        const char* GetErrorMessage() const;
        const char* GetFileName() const;
        const char* GetFunctionName() const;
        const char* GetBuildDate() const;
        const char* GetBuildTime() const;
        int GetLineNumber() const;
        Error GetError() const;

      protected:
      private:
        struct ExceptionData;
        ExceptionData* m_pImpl;
    };

    /*@}*/

    /*@}*/
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // PGR_SPINNAKER_EXCEPTION_H