/**
 * Tencent is pleased to support the open source community by making Tars available.
 *
 * Copyright (C) 2016THL A29 Limited, a Tencent company. All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use this file except 
 * in compliance with the License. You may obtain a copy of the License at
 *
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software distributed 
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the 
 * specific language governing permissions and limitations under the License.
 */

#ifndef _MockProxyObjImp_H_
#define _MockProxyObjImp_H_
// #include "util/tc_atomic.h"
#include "servant/Application.h"
#include "servant/Servant.h"
#include "MockServerObjProxy.h"

using namespace tars;
using namespace std;

namespace mockProxy
{
    /**
     *
     *
     */
    class MockProxyObjImp : public Servant
    {
    public:
        /**
         *
         */
        virtual ~MockProxyObjImp() {}

        /**
         *
         */
        virtual void initialize();

        /**
         *
         */
        virtual void destroy();

        /**
         * 应用接收消息处理入口
         * @param current
         * @param response
         *
         * @return int
         */
        virtual int doRequest(tars::TarsCurrentPtr current, vector<char>& response);

        /**
         * 应用回应消息处理入口
         * @param resp
         * @return int
         */
        virtual int doResponse(ReqMessagePtr resp);

    private:
        void setPushInfo(const string &sInfo);

        void push(const string& pushInfo);

        void parseOriginalRequest(const TarsCurrentPtr current, RequestPacket &requestPacket);

        void replaceRequestId(const RequestPacket &oldRequest, RequestPacket &newRequest);

        void callMockServer(const RequestPacket &requestPacket,  const ServantProxyCallbackPtr& callback);

        static std::atomic<int> requestId;

        string _sMockServerObjName ;
    };

}
/////////////////////////////////////////////////////
#endif
