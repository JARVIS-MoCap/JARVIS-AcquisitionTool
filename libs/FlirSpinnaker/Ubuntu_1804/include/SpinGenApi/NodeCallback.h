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

#ifndef SPINNAKER_GENAPI_NODECALLBACK_H
#define SPINNAKER_GENAPI_NODECALLBACK_H
#include "INode.h"

namespace Spinnaker
{
    namespace GenApi
    {
        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup NodeCallback_h NodeCallback Class
         */
        /*@{*/

        /**
         * the type of callback
         */
        typedef enum _ECallbackType
        {
            cbPostInsideLock = 1, /*!> callback is fired on leaving the tree inside the lock-guarded area*/
            cbPostOutsideLock = 2 /*!> callback is fired on leaving the tree inside the lock-guarded area*/
        } ECallbackType;

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup NodeCallback_h NodeCallback Class
         */
        /*@{*/

        /**
         * @brief callback body instance for INode pointers
         */
        class CNodeCallback
        {
          public:
            CNodeCallback(INode* pNode, ECallbackType CallbackType) : m_pNode(pNode), m_CallbackType(CallbackType)
            {
            }

            /**
             * virtual destructor
             */
            virtual ~CNodeCallback(){};

            /**
             * fires the callback if th type is right
             */
            virtual void operator()(ECallbackType CallbackType) const = 0;

            /**
             * destroys the object
             */
            virtual void Destroy() = 0;

            /**
             * returns the node the callback is registered to
             */
            INode* GetNode()
            {
                return m_pNode;
            }

            ECallbackType GetCallbackType()
            {
                return m_CallbackType;
            }

          protected:
            /**
             * the node were the callback is installed
             */
            INode* m_pNode;

            /**
             * the type of the callback
             */
            ECallbackType m_CallbackType;
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup NodeCallback_h NodeCallback Class
         */
        /*@{*/

        /***************************************************************************/
        // C Functions as callbacks
        /***************************************************************************/

        /**
         * @brief Container for a function pointer
         */
        template <class Function> class Function_NodeCallback : public CNodeCallback
        {
          public:
            /**
             * Constructor
             */
            Function_NodeCallback(INode* pNode, const Function& function, ECallbackType CallbackType)
                : CNodeCallback(pNode, CallbackType), m_pFunction(function)
            {
            }

            /**
             * execute operation: call the function
             */
            virtual void operator()(ECallbackType CallbackType) const
            {
                if (m_pFunction && m_CallbackType == CallbackType)
                    m_pFunction(m_pNode);
            }

            /**
             * destroys teh object
             */
            virtual void Destroy()
            {
                delete this;
            }

          private:
            /**
             * the callback function
             */
            const Function m_pFunction;

            /**
             * no assignment operator
             */
            Function_NodeCallback& operator=(Function_NodeCallback&);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup NodeCallback_h NodeCallback Class
         */
        /*@{*/

        /**
         * @brief make a new callback object for C functions
         */
        template <class Function>
        CNodeCallback* make_NodeCallback(INode* pNode, Function function, ECallbackType CallbackType)
        {
            return static_cast<CNodeCallback*>(new Function_NodeCallback<Function>(pNode, function, CallbackType));
        }

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup NodeCallback_h NodeCallback Class
         */
        /*@{*/

        /**
         * @brief Register a C-function as a callback
         */
        template <class Function>
        intptr_t Register(INode* pNode, Function f, ECallbackType CallbackType = cbPostInsideLock)
        {
            CNodeCallback* pCallback(make_NodeCallback(pNode, f, CallbackType));
            return pNode->RegisterCallback(pCallback);
        }

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup NodeCallback_h NodeCallback Class
         */
        /*@{*/

        /***************************************************************************/
        // C++ Member functions as callbacks
        /***************************************************************************/

        /**
         * @brief Container for a member function pointer
         */
        template <class Client, class Member> class Member_NodeCallback : public CNodeCallback
        {
          public:
            /**
             * Member function type
             */
            typedef void (Client::*PMEMBERFUNC)(INode*);

            /**
             * Constructor
             */
            Member_NodeCallback(INode* pNode, Client& client, Member member, ECallbackType CallbackType)
                : CNodeCallback(pNode, CallbackType), m_Client(client), m_pMemberFunc(member)
            {
            }

            /**
             * execute operation
             */
            virtual void operator()(ECallbackType CallbackType) const
            {
                if (m_pMemberFunc && m_CallbackType == CallbackType)
                    (m_Client.*m_pMemberFunc)(m_pNode);
            }

            /**
             * destroys the object
             */
            virtual void Destroy()
            {
                delete this;
            }

          private:
            /**
             * The object the method function belongs to
             */
            Client& m_Client;

            /**
             * The method to call
             */
            PMEMBERFUNC m_pMemberFunc;

            /**
             * no assignment operator
             */
            Member_NodeCallback& operator=(Member_NodeCallback&);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup NodeCallback_h NodeCallback Class
         */
        /*@{*/

        /**
         * @brief make a new callback object for member functions
         */
        template <class Client, class Member>
        CNodeCallback* make_NodeCallback(INode* pNode, Client& client, Member member, ECallbackType CallbackType)
        {
            return static_cast<CNodeCallback*>(
                new Member_NodeCallback<Client, Member>(pNode, client, member, CallbackType));
        }

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup NodeCallback_h NodeCallback Class
         */
        /*@{*/

        /**
         * @brief Register a C++-member function a callback
         */
        template <class Client, class Member>
        intptr_t Register(INode* pNode, Client& c, Member m, ECallbackType CallbackType = cbPostInsideLock)
        {
            CNodeCallback* pCallback(make_NodeCallback(pNode, c, m, CallbackType));
            return pNode->RegisterCallback(pCallback);
        }

        /**
         * Unregistering callback by handle
         */
        // definition in Node.cpp
        SPINNAKER_API void Deregister(GenApi::CallbackHandleType pCallbackInfo);

        /*@}*/
        /*@}*/
    } // namespace GenApi
} // namespace Spinnaker

#endif // SPINNAKER_GENAPI_NODECALLBACK_H
