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
 * MockProxyObjCallBack.cpp
 *
 *  Created on: 2018年8月22日
 *      Author: abelguo
 */
#include "servant/TarsLogger.h"
#include "servant/BaseF.h"
#include "stub/MockProxyObjCallback.h"

using namespace tars;

namespace mockProxy
{
    void MockProxyObjCallback::doResponse(shared_ptr<ResponsePacket> responsePacket)
    {
        responsePacket->iRequestId = iRequestId;

        TarsOutputStream<BufferWriter> os;

        responsePacket->writeTo(os);

        string response;

        Int32 iHeaderLen = htonl(sizeof(Int32) + os.getByteBuffer().size());

        response.reserve(sizeof(Int32) + os.getByteBuffer().size());

        response.append((const char*)&iHeaderLen, sizeof(Int32));

        response.append((const char*)&os.getByteBuffer()[0], os.getByteBuffer().size());
        TLOGDEBUG("[MockProxy]MockProxyObjCallback response[" << response.size() << "]: " << response <<endl);

        getCurrent()->sendResponse(response.c_str(), response.size());

        return;
    }
}


