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

#pragma once

//#include <GenApi/GenApiVersion.h>
//#include <GenApi/GenApiDll.h>
#include "GCString.h"
#include "GCStringVector.h"
#include <memory>

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        class CLock; // forward
        class CNodeDataMap;
        struct INodeMap;

        /**
         *  @defgroup NodeMapFactory_h NodeMapFactory Class
         */
        /*@{*/

        /**
         * @brief Lists the cache usage strategies. The cache stores preprocessed camera description xml files providing
         * faster access or smaller footprint. note The environment variable GENICAM_CACHE_VERSION, e.g.
         * GENICAM_CACHE_V3_0, must contain the path to cache directory for using the cache.
         */
        typedef enum
        {
            CacheUsage_Automatic,  ///< The use of cache files is determined automatically.
            CacheUsage_ForceWrite, ///< Forces the loading and preprocessing of the camera description xml file.
                                   ///< If a cache directory is available the result of preprocessing is written to the
                                   ///< cache.
            CacheUsage_ForceRead,  ///< Suppresses loading and preprocessing of the camera description xml file and
                                  ///< forces reading a cache file from cache directory. Fails if no matching cache file
                                  ///< is available.
            CacheUsage_Ignore ///< Forces the loading and preprocessing of the camera description xml file. No cache
                              ///< file is written.
        } ECacheUsage_t;

        /**
         * @brief Lists the processable file types.
         */
        typedef enum
        {
            // ContentType_Auto,
            ContentType_Xml,      ///< XML camera description file text
            ContentType_ZippedXml ///< Zipped XML camera description file text
        } EContentType_t;

        /*@}*/

        /**
         *  @addtogroup NodeMapFactory_h NodeMapFactory Class
         */
        /*@{*/

        //*************************************************************
        // CNodeMapFactory
        //*************************************************************

        /*!
        * @brief The node map factory is used for creating node maps from camera description files.

        \ingroup GenApi_PublicInterface
        \par Examples

        \code
        // Simple node map creation from buffer, downloaded from a device for instance.
        CNodeMapFactory cameraNodeMapFactory( ContentType_ZippedXml, buffer, bufferSize);

        // Create the node map. The node map can be destroyed using the IDestroy interface later.
        INodeMap* pNodeMap = cameraNodeMapFactory.CreateNodeMap();
        // The next step is attaching the device port (not shown).
        \endcode

        \code
        // Node map creation with injecting additional xml fragments.
        CNodeMapFactory cameraNodeMapFactory( ContentType_Xml, buffer, bufferSize);
        cameraParameters.AddInjectionData( CNodeMapFactory(ContentType_Xml, filename1));
        cameraParameters.AddInjectionData( CNodeMapFactory(ContentType_Xml, filename2));

        // Create the node map. The node map can be destroyed using the IDestroy interface later.
        INodeMap* pNodeMap = cameraNodeMapFactory.CreateNodeMap();
        // The next step is attaching the device port (not shown).
        \endcode

        \code
        // Node map creation and additional extraction of a category subtree.
        CNodeMapFactory cameraNodeMapFactory( ContentType_Xml, buffer, bufferSize);
        // Extract a subtree for later chunk parsing.
        CNodeMapFactory chunkDataNodeMapFactory = cameraParameters.ExtractSubtree("ChunkData");

        // Create the node map. The node map can be destroyed using the IDestroy interface later.
        INodeMap* pNodeMap = cameraParameters.CreateNodeMap();
        // The next step is attaching the device port (not shown).
        \endcode

        \code
        // Node map creation with injecting additional xml fragments and additional extraction of a category subtree.
        CNodeMapFactory cameraNodeMapFactory( ContentType_Xml, buffer, bufferSize);
        cameraParameters.AddInjectionData( CNodeMapFactory(ContentType_Xml, filename1));
        cameraParameters.AddInjectionData( CNodeMapFactory(ContentType_Xml, filename2));
        CNodeMapFactory chunkDataNodeMapFactory = cameraNodeMapFactory.ExtractSubtree("ChunkData");

        // Create the node map. The node map can be destroyed using the IDestroy interface later.
        INodeMap* pNodeMap = cameraNodeMapFactory.CreateNodeMap();
        // The next step is attaching the device port (not shown).

        // A node map factory can create multiple node maps from the provided camera description file(s).
        for(int i = 0; i < 20; ++i)
        {
            INodeMap* pNodeMapChunks = chunkDataNodeMapFactory.CreateNodeMap();
            //...
        }
        \endcode

        \attention The is CNodeMapFactory not thread-safe.

        \attention You need to take care when camera description file data can be actually be freed, see method
        documentation of the node map factory for more detail.
        */

        class SPINNAKER_API CNodeMapFactory
        {
          public:
            /**
             * Creates an empty node map factory for assigning a non-empty node map factory later.
             */
            CNodeMapFactory();

            /**
             * Destroys the node map factory data if all references to the data have been released.
             */
            virtual ~CNodeMapFactory();

            /**
             * @brief Creates another reference to the node map factory data. No data is copied.
             */
            CNodeMapFactory(const CNodeMapFactory&);

            /**
             * @brief Creates another reference to the assigned node map factory data. Destroys the "overwritten" node
             * map factory data if all references to the data have been released.
             */
            CNodeMapFactory& operator=(const CNodeMapFactory&);

            /**
             * Creates the node map factory and simply stores the full path to the provided camera description file
             * data.
             *
             * @param[in] FileType     Defines how the camera description file is stored, e.g. as zipped XML text.
             * @param[in] FileName     The full path of the camera description file to process.
             * @param[in] CacheUsage   Defines if and how to use the cache for preprocessed camera description files.
             * @param[in] SuppressStringsOnLoad Suppresses loading strings that are not needed for most use cases, e.g.
             * node tooltip or description, for reducing the memory footprint.
             *
             * Throws an invalid argument exception if FileName is empty. Throws if environment variables in FileName
             * cannot be resolved.
             *
             * @attention The given file must be readable until the camera description file data has been released. The
             * IsCameraDescriptionFileDataReleased() method can be used to check if releasing has been done.
             */
            CNodeMapFactory(
                EContentType_t FileType,
                const GenICam::gcstring& FileName,
                ECacheUsage_t CacheUsage = CacheUsage_Automatic,
                bool SuppressStringsOnLoad = false);

            /**
             * Creates the node map factory and simply stores the pointer and the size of the provided camera
             * description file data.
             *
             * @param[in] ContentType  Defines how the camera description file is stored, e.g. as zipped XML text.
             * @param[in] pData        The pointer to the camera description file data.
             * @param[in] DataSize     The size of the camera description file data.
             * @param[in] CacheUsage   Defines if and how to use the cache for preprocessed camera description files.
             * @param[in] SuppressStringsOnLoad Suppresses loading strings that are not needed for most use cases, e.g.
             * node tooltip or description, for reducing the memory footprint.
             *
             * Throws an invalid argument exception if pData is NULL or DataSize is 0.
             *
             * @attention The given buffer must not be freed or changed until the camera description file data has been
             * released. The IsCameraDescriptionFileDataReleased() method can be used to check if releasing has been
             * done.
             */
            CNodeMapFactory(
                EContentType_t ContentType,
                const void* pData,
                size_t DataSize,
                ECacheUsage_t CacheUsage = CacheUsage_Automatic,
                bool SuppressStringsOnLoad = false);

            /**
             * Creates the node map factory and copies the provided camera description file string.
             *
             * @param[in] XmlData      The camera description file data as XML text.
             *                       The provided text is copied. You can use the overloaded constructor accepting a
             * buffer to avoid that. \code gcstring cdfData;
             *                       //... fill cdfData ...
             *                       CNodeMapFactory factory(ContentType_Xml, cfdData.c_str(), cfdData.size());
             *                       // Create the node map. The node map can be destroyed using the IDestroy interface
             * later. INodeMap* pNodeMap = factory.CreateNodeMap();
             *                       // The next step is attaching the device port (not shown).
             *                       \endcode
             * @param[in] CacheUsage   Defines if and how to use the cache for preprocessed camera description files.
             * @param[in] SuppressStringsOnLoad Suppresses loading strings that are not needed for most use cases, e.g.
             * node tooltip or description, for reducing the memory footprint.
             *
             * Throws an invalid argument exception if XmlData is empty.
             */
            CNodeMapFactory(
                const GenICam::gcstring& XmlData,
                ECacheUsage_t CacheUsage = CacheUsage_Automatic,
                bool SuppressStringsOnLoad = false);

            /**
             * Returns true if nothing is loaded (IsLoaded()) and no source data is available, e.g. when the node map
             * factory has been created with the default constructor.
             */
            bool IsEmpty() const;

            /**
             * Adds a node map factory representing a camera description file to inject.
             *
             * @param[in] injectionData A node map factory representing a camera description file to inject.
             *
             * The injected files are injected in the order they are added.
             * InjectionData must not be preprocessed. The IsPreprocessed() method can be used to check if preprocessing
             * has been done before. The cache usage of injection data is ignored.
             */
            void AddInjectionData(CNodeMapFactory& injectionData);

            /**
             * Advanced: Loads, Parses, and Injects the camera description files recursively. The result is a memory
             * internal representation of the camera description file(s), the CNodeDataMap (not part of the public
             * interface).
             *
             * This step is usually done automatically. Prevents cache read if called manually.
             */
            void LoadAndInject();

            /**
             * Can be used to check whether the LoadAndInject() processing step has been performed. Returns true if
             * IsPreprocessed() returns true (Preprocessed Data has been loaded from cache).
             */
            bool IsLoaded() const;

            /**
             * The name of the node that represents the root of the subtree that shall be extracted.
             *
             * @param[in] SubTreeRootNodeName      The root of the branch to extract, e.g. "ChunkData".
             * @param[in] doRenameToRoot           Renames the extracted subtree root node SubTreeRootNodeName to
             * "Root", sets the IsFeature property. Preprocess() is automatically called if needed to create the memory
             * internal representation of the camera description file(s). The preprocessed result can be read from the
             * cache or written to the cache in this step. This depends on the availability of a cache and the used
             * CacheUsage setting.
             */
            CNodeMapFactory ExtractSubtree(const GenICam::gcstring& SubTreeRootNodeName, bool doRenameToRoot = false);

            /**
             * Advanced: Creates the preprocessed memory internal representation of the camera description file(s), the
             * CNodeDataMap (not part of the public interface).
             */
            /*!
            This step is usually done automatically.
            Preprocessed data can be read from the cache or written to the cache in this step. This depends on the
            availability of a cache and the used CacheUsage setting. By calling this method directly direct cache load
            is suppressed, see CreateNodeMap() for more information.
            */
            void Preprocess();

            /**
             * Can be used to check whether the Preprocess() processing step has been performed.
             */
            bool IsPreprocessed() const;

            /**
             * Advanced: Releases any in constructors provided camera description file data buffers or files.
             */
            /*!
            This step is usually done automatically.
            All references to added injection data are dropped in this step to free the data.
            After this step any in constructors provided buffers can be freed or any in constructors given files can be
            deleted.
            */
            void ReleaseCameraDescriptionFileData();

            /**
             * Can be used to check whether the ReleaseCameraDescriptionFileData() processing step has been performed.
             */
            bool IsCameraDescriptionFileDataReleased() const;

            /**
             * Creates a node map from the preprocessed memory internal representation of the camera description
             * file(s).
             */
            /*!
            Preprocess() is automatically called if needed. The preprocess step can be omitted by the factory depending
            on the cache mode setting when a cache file is available, then the cache file is read and converted directly
            into a node map. ReleaseCameraDescriptionFileData() is called if DoReleaseCameraDescriptionFileData is true.
            This method can be called multiple times to create multiple instances of a node map.
            */
            INodeMap* CreateNodeMap(
                const GenICam::gcstring& DeviceName = "Device",
                bool DoReleaseCameraDescriptionFileData = true);

            /**
             * Creates a node map from the preprocessed memory internal representation of the camera description
             * file(s).
             */
            /*!
            Preprocess() is automatically called if needed. The preprocess step can be omitted by the factory depending
            on the cache mode setting when a cache file is available, then the cache file is read and converted directly
            into a node map. ReleaseCameraDescriptionFileData() is called if DoReleaseCameraDescriptionFileData is true.
            This method can be called multiple times to create multiple instances of a node map.
            This method allows to provide an external lock to avoid using too many locks in an application.
            \attention The provided lock must not be destroyed before the created node map.
            */
            INodeMap* CreateNodeMap(
                CLock& UserProvidedLock,
                const GenICam::gcstring& DeviceName = "Device",
                bool DoReleaseCameraDescriptionFileData = true);

            /**
             * Creates an empty node map usable as placeholder, e.g. if certain features are not supported by a module.
             */
            static INodeMap* CreateEmptyNodeMap();

            /**
             * Deletes all preprocessed camera description files from the cache.
             */
            static bool ClearCache();

            /*! Each list entry is a string with the format "{Major}.{Minor}" were {Major} and {Minor} are integers
            Example: {"1.1", "1.2"} indicates that the schema v1.1 and v1.2 are supported.
            The SubMinor version number is not given since it is for fully compatible bug fixes only
            */
            void GetSupportedSchemaVersions(GenICam::gcstring_vector& SchemaVersions) const;

            /**
             * Outputs the pre-processed node map in string form (for debug purpose)
             */
            GenICam::gcstring ToString() const;

            /**
             * Outputs the pre-processed node map in XML form (mainly for debug purpose)
             */
            GenICam::gcstring ToXml() const;

            static CNodeDataMap* CreateNodeDataFromNodeMap(INodeMap* pNodeMap);

            typedef struct
            {
                uint32_t NumNodes;
                uint32_t NumProperties;
                uint32_t NumLinks;
                uint32_t NumStrings;
            } NodeStatistics_t;

            void GetNodeStatistics(NodeStatistics_t& NodeStatistics);

            /**
             * Applies a style sheet to the pre-processed node map.
             */
            const GenICam::gcstring ApplyStyleSheet(const GenICam::gcstring& StyleSheetFileName);

          private:
            class CNodeMapFactoryImpl;

            CNodeMapFactoryImpl* m_pImpl;
        };

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker
