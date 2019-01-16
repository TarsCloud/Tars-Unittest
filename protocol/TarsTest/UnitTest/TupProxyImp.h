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

#ifndef _TupProxyImp_H_
#define _TupProxyImp_H_

#include "servant/Application.h"
#include "util/tc_http.h"
#include "TupCallback.h"
#include "AServant.h"

using namespace std;
using namespace tars;
using namespace TarsTest;

/**
 *
 *
 */
class TupProxyImp : public Servant
{
public:
    TupProxyImp();
    /**
     *
     */
    virtual ~TupProxyImp();

    /**
     *
     */
    virtual void initialize();

    /**
     *
     */
    virtual void destroy();

    /**
     * 处理客户端的主动请求
     * @param current
     * @param response
     * @return int
     */
    virtual int doRequest(TarsCurrentPtr current, vector<char>& response);

    /**
     * @param resp
     * @return int
     */
    virtual int doResponse(ReqMessagePtr resp);

protected:
    /**
     * 处理请求
     *
     * @param current
     */
    int doRequest(const tars::TarsCurrentPtr &current, const char *buffer, size_t length);

    /**
     * 解析出多个TUP包
     *
     * @param buffer
     * @param length
     * @param map<int32_t, UniPacket<> >
     * @return int
     */
    int parseTupRequest(const char *buffer, size_t length, map<int32_t, RequestPacket*> &mTupRequest);

    /**
     * 异步发送
     *
     * @param wup
     * @param proxy
     */
    void tupAsyncCall(RequestPacket *wup, const AServantPrx &proxy, const TupCallbackPtr &cb);

protected:
	int _iNum;
    int64_t _iTime;
	AServantPrx _pPrx;
	ProxyProtocol           _prot_tup; 
	TC_HttpRequest httpRequest;
};


/////////////////////////////////////////////////////
#endif
