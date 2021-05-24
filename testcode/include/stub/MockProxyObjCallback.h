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
 /*
 * MockProxyObjCallback.h
 *
 *  Created on: 2018年8月22日
 *      Author: abelguo
 */

#ifndef MOCK_PROXY_MOCKPROXYOBJCALLBACK_H_
#define MOCK_PROXY_MOCKPROXYOBJCALLBACK_H_
#include <string>
#include <vector>
#include "servant/Servant.h"

using namespace tars;
using namespace std;

namespace mockProxy
{
    const static string MOCK_PROXY_CALLBACK_TYPE = "MockProxyCallback";

    /* callback of async proxy for client */
    class MockProxyObjCallback: public ServantCallback
    {
    public:
        MockProxyObjCallback(const ServantPtr& servant, const TarsCurrentPtr& current)
            :ServantCallback(MOCK_PROXY_CALLBACK_TYPE, servant, current),iRequestId(0)
        {
        }

        virtual ~MockProxyObjCallback(){}

        /**
         * 异步回调处理函数
         * @param responsePacket
         */
        virtual void doResponse(shared_ptr<ResponsePacket>  responsePacket);

        /**
         * 设置RequestId，在回应消息时，需要使用
         * @param id
         */
        void setRequestId(Int32 id)  { iRequestId = id; }

    protected:

        Int32 iRequestId;
    };
    typedef TC_AutoPtr<MockProxyObjCallback> MockProxyObjCallbackPtr;

}


#endif /* MOCK_PROXY_MOCKPROXYOBJCALLBACK_H_ */
