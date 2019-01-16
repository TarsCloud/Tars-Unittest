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

#ifndef _TupCallback_H_
#define _TupCallback_H_

#include "servant/Application.h"
#include "util/tc_http.h"

using namespace std;
using namespace tars;

struct StatInfo
{
    string  sIp;
    int64_t iTime;
    string sHttpHeaderValue;
};

/**
 * 异步回调对象
 */
class TupCallback : public ServantCallback
{
public:
    TupCallback(const string& type, 
                const ServantPtr& servant, 
                const TarsCurrentPtr& current) 
        :ServantCallback(type, servant, current), _iResponse(0), _isHttpProt(true)
    {
    }

    /**
     * 析构
     */
    virtual ~TupCallback();

    /**
     * 响应
     * 
     * @param buffer 
     */
    void doResponse_jce(const vector<char> &buffer);
    void doResponse_tup(const vector<char> &buffer);

    /**
     * 添加一个原始的tup
     * 
     * @param tup 
     */
    void addtup(int32_t iRequestId, RequestPacket *tup);

    /**
     * 删除
     * @param iRequestId
     */
    void deltup(int32_t iRequestId);

	//virtual int onDispatch(ReqMessagePtr msg);


protected:
    void doResponse();

protected:

    /**
     * 请求的tup包
     */
    map<int32_t, RequestPacket*>  _tupRequest;
    
    /**
    * 相应包个数
    */
    size_t                      _iResponse;

    /**
     * 所有的回应包
     */
    //vector<char>                _allBuffer;
	string						_allBuffer;

    string                      _nowServantName;   //现在正在回包的servantname

    bool                        _isHttpProt;
};

typedef TC_AutoPtr<TupCallback> TupCallbackPtr;


/////////////////////////////////////////////////////
#endif
