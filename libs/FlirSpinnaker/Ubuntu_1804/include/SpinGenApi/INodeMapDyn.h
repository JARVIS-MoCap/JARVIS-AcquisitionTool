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

#ifndef SPINNAKER_GENAPI_INODEMAPDYN_H
#define SPINNAKER_GENAPI_INODEMAPDYN_H

#include "GCString.h"
#include "INodeMap.h"
#include "GCStringVector.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4251) // XXX needs to have dll-interface to be used by clients of class YYY
#endif

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiInterfaces Spinnaker GenApi Interfaces
         */
        /*@{*/

        /**
         *  @defgroup INodeMapDyn_h INodeMapDyn Interface
         */
        /*@{*/

        //*************************************************************
        // INodeMap interface
        //*************************************************************

        /**
         * @brief Interface to access the node map
         */
        interface SPINNAKER_API_ABSTRACT INodeMapDyn : virtual public INodeMap
        {
            /**
             * Deletes all Nodes from the map
             */
            virtual void ClearAllNodes() = 0;

            /**
             * Loads an XML from a file
             */
            virtual void LoadXMLFromFile(const GenICam::gcstring& FileName) = 0;

            /**
             * Loads an XML from a file with injection
             */
            virtual void LoadXMLFromFileInject(
                const GenICam::gcstring& TargetFileName, const GenICam::gcstring& InjectFileName) = 0;

            /**
             * Loads an XML from a string
             */
            virtual void LoadXMLFromString(const GenICam::gcstring& XMLData) = 0;

            /**
             * Loads an XML from a string with injection
             */
            virtual void LoadXMLFromStringInject(
                const GenICam::gcstring& TargetXMLData, const GenICam::gcstring& InjectXMLData) = 0;

            /**
             * Loads an XML, checks it for correctness, pre-processes it, caches it, and optionally applies a style
             * sheet, and optionally writes it to a file
             */
            virtual void PreprocessXMLFromFile(
                const GenICam::gcstring& XMLFileName,        /*!> The name of the XML file to process*/
                const GenICam::gcstring& StyleSheetFileName, /*!> Optional name of a style sheet which is applied after
                                                                the pre-processor (can be empty string)*/
                /*!> This has no effect if the OutputFileName is an empty string*/
                const GenICam::gcstring& OutputFileName, /*!> Optional name of an output file into which the processed
                                                            data is written (can be empty string)*/
                const uint32_t XMLValidation = xvDefault /*!> Optional bit mask formed from EXMLValidation enumeration
                                                            indicating which tests should be performed on the XML file*/
                ) = 0;

            /**
             * Injects an XML file into a target file
             */
            virtual void MergeXMLFiles(
                const GenICam::gcstring& TargetFileName,   /*!> Name of the target XML file to process*/
                const GenICam::gcstring& InjectedFileName, /*!> Name of the Injected XML file to process*/
                const GenICam::gcstring& OutputFileName    /*!> Name of the oputput file*/
                ) = 0;

            /**
             * Extract independent subtree
             */
            virtual void ExtractIndependentSubtree(
                const GenICam::gcstring& XMLData,       /*!> The XML data the subtree is extracted from.*/
                const GenICam::gcstring& InjectXMLData, /*!> Optional XML data that is injected before extracting the
                                                           subtree. No effect if an empty string is passed.*/
                const GenICam::gcstring& SubTreeRootNodeName, /*!> The name of the node that represents the root of the
                                                                 subtree that shall be extracted.*/
                GenICam::gcstring& ExtractedSubtree           /*!> The returned extracted subtree as string.*/
                ) = 0;

            /**
             * Gets a list of supported schema versions
             */
            /*! Each list entry is a string with the format "<Major>.<Minor>" were <Major> and <Minor> are integers
                Example: {"1.1", "1.2"} indicates that the schema v1.1 and v1.2 are supported.
                The SubMinor version number is not given since it is for fully compatible bug fixes only
            */
            virtual void GetSupportedSchemaVersions(GenICam::gcstring_vector & SchemaVersions) = 0;

            /**
             * Loads an XML from a ZIP file
             */
            virtual void LoadXMLFromZIPFile(const GenICam::gcstring& ZipFileName) = 0;

            /**
             * Loads an XML from a ZIP data buffer
             */
            virtual void LoadXMLFromZIPData(const void* zipData, size_t zipSize) = 0;

            /**
             * Loads a Zipped XML, checks it for correctness, pre-processes it, caches it, and optionally applies a
             * style sheet, and optionally writes it to a file
             */
            virtual void PreprocessXMLFromZIPFile(
                const GenICam::gcstring& XMLFileName,        /*!> The name of the XML file to process*/
                const GenICam::gcstring& StyleSheetFileName, /*!> Optional name of a style sheet which is applied after
                                                                the pre-processor (can be empty string)*/
                /*!> This has no effect if the OutputFileName is an empty string*/
                const GenICam::gcstring& OutputFileName, /*!> Optional name of an output file into which the processed
                                                            data is written (can be empty string)*/
                const uint32_t XMLValidation = xvDefault /*!> Optional bit mask formed from EXMLValidation enumeration
                                                            indicating which tests should be performed on the XML file*/
                ) = 0;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // ifndef SPINNAKER_GENAPI_INODEMAPDYN_H
