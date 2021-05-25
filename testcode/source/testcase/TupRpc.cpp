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

#include <iostream>
#include <cstdlib>
// #include <unistd.h>
#include "gtest/gtest.h"
#include "util/tc_common.h"
#include "util/tc_clientsocket.h"
#include "servant/Application.h"
#include "tup/tup.h"
#include "TarsTest/UnitTest/TupDemo.h"
#include "TarsServantName.h"

using namespace std;
using namespace tars;
using namespace TarsTest;

/****************************************************
PRC请求方式测试TUP协议
****************************************************/

class TupTestCallback:public TupDemoPrxCallback
{
     virtual void callback_aAddb(tars::Int32 ret,  const TarsTest::Result& aAddbResult)
     { 
         EXPECT_EQ(ret, 0);
		 EXPECT_EQ(aAddbResult.addResult,3);
     }
};
	

struct TupTest : public ::testing::Test 
{
    TupTest()
    {
        _comm = Application::getCommunicator();
    }
    protected:
    CommunicatorPtr _comm;
};
typedef tars::TC_AutoPtr<TupTestCallback> TupTestCallbackPtr;

/**
* @brief 同步调用，校验返回值
*/

TEST_F(TupTest, test_tup_rpc_when_client_sync_call_server_by_ip)
{

  
    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();
	
	TarsUniPacket<> req;
	TarsUniPacket<>rsp;
	
	int iRequestId=1;
	req.setRequestId(iRequestId);
	req.setServantName("TarsTest.UnitTest.TupDemoObj");
    req.setFuncName("aAddb");
    
    struct AddInt addData;
    addData.adda = 1;
    addData.addb = 2;
    addData.addStr = "1 + 2 = 3";
    req.put<const AddInt>("addData",addData);
    
    string sendBuff;
    req.encode(sendBuff);   
    
    int iRet = -1; 

	TupDemoPrx prx;
	prx = _comm->stringToProxy<TupDemoPrx> (TUP_SERVANT_ENDPOINT);
    tars::ProxyProtocol proxy_codec;
	proxy_codec.responseFunc = tars::ProxyProtocol::tupResponse;
	prx->tars_set_protocol(proxy_codec);
	tars::ResponsePacket response;
	prx->rpc_call(iRequestId, "aAddb", sendBuff.c_str(), sendBuff.size(), response);
	iRet=response.iRet;
	EXPECT_EQ(iRet, 0);
	rsp.decode(&response.sBuffer[0],response.sBuffer.size());
	struct Result aAddbResult; 
	rsp.get<Result>("aAddbResult",aAddbResult);
	EXPECT_EQ(aAddbResult.addResult,3);

	TLOGDEBUG("tup test time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
}

/**
* @brief 异步调用，校验返回值
*/

TEST_F(TupTest, test_tup_rpc_when_client_async_call_server_by_ip)
{

  
   
	TarsUniPacket<> req;
	TarsUniPacket<>rsp;
	
	int iRequestId=1;
	req.setRequestId(iRequestId);
	req.setServantName("TarsTest.UnitTest.TupDemoObj");
    req.setFuncName("aAddb");
    
    struct AddInt addData;
    addData.adda = 1;
    addData.addb = 2;
    addData.addStr = "1 + 2 = 3";
    req.put<const AddInt>("addData",addData);
    
    string sendBuff;
    req.encode(sendBuff);   
    
    
	TupDemoPrx prx;
	prx = _comm->stringToProxy<TupDemoPrx> (TUP_SERVANT_ENDPOINT);
    tars::ProxyProtocol proxy_codec;
	proxy_codec.responseFunc = tars::ProxyProtocol::tupResponse;
	prx->tars_set_protocol(proxy_codec);
	
	TupTestCallbackPtr cbp=new TupTestCallback();
	prx->rpc_call_async(iRequestId, "aAddb", sendBuff.c_str(), sendBuff.size(),cbp);
    TC_Common::sleep(1);
}



