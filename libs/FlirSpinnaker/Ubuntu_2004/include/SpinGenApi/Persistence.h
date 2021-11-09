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

#ifndef SPINNAKER_GENAPI_PERSISTENCE_H
#define SPINNAKER_GENAPI_PERSISTENCE_H

#include "Types.h"
#include "Pointer.h"
#include "ISelectorDigit.h"
#include "GCString.h"
#include "GCStringVector.h"
#include <list>
#include <iostream>

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         * @brief Basic interface to persist values to
         */
        interface SPINNAKER_API_ABSTRACT IPersistScript
        {
            /**
             * sets information about the node map
             */
            virtual void SetInfo(GenICam::gcstring & Info) = 0;

            /**
             * Stores a feature
             */
            virtual void PersistFeature(IValue & item) = 0;
        };

        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup Persistence_h Persistence Class
         */
        /*@{*/

        /**
         * @brief Bag holding streamable features of a nodetree
         */
        class SPINNAKER_API CFeatureBag : public IPersistScript
        {
          public:
            CFeatureBag();
            virtual ~CFeatureBag();

            /**
             * sets information about the node map
             */
            virtual void SetInfo(GenICam::gcstring& Info);

            /**
             * Stores a feature
             */
            virtual void PersistFeature(IValue& item);

            /**
             * Loads the features from the bag to the node tree
             * @param pNodeMap  The node map
             * @param Verify If true, all streamable features are read back
             * @param pErrorList If an error occurs during loading the error message is stored in the list and the
             * loading continues
             */
            /*! For Verify=true the list of names in the feature bag is replayed again.
                If a node is a selector it's value is set to the value from the feature bag
                If not the value is read from the camera and compared with the value from the feature bag.
            */
            bool LoadFromBag(INodeMap* pNodeMap, bool Verify = true, GenICam::gcstring_vector* pErrorList = NULL);

            /**
             * @brief Stores the streamable nodes to this feature bag
             *   @param pNodeMap The node map to persist
             *   @param MaxNumPersistSkriptEntries The max number of entries in the container; -1 means unlimited
             * @return number of entries in the bag
             */
            int64_t StoreToBag(INodeMap* pNodeMap, const int MaxNumPersistSkriptEntries = -1);

            /**
             * compares the content of two feature bags
             */
            bool operator==(const CFeatureBag& FeatureBag) const;

            void* GetFeatureBagHandle();

          private:
            void* m_featureBag;
        };

        /*@}*/

        /**
         * @brief Helper function ignoring lines starting with comment character '#'
         */
        // note: this method must be inlined because it uses istream in the parameter list
        SPINNAKER_API std::istream& EatComments(std::istream& is);

        /**
         * @brief Reads in persistent data from a stream
         */
        // note: this method must be inlined because it uses istream in the parameter list
        SPINNAKER_API std::istream& operator>>(std::istream& is, CFeatureBag& FeatureBag);

        /**
         * @brief writes out persistent data to a stream
         */
        // note: this method must be inlined because it uses ostream in the parameter list
        SPINNAKER_API std::ostream& operator<<(std::ostream& os, const CFeatureBag& FeatureBag);

        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // SPINNAKER_GENAPI_PERSISTENCE_H
