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

#include "gtest/gtest.h"
#include<vector>
#include "servant/Application.h"
#include "TarsServantName.h"
#include "TarsTest/UnitTest/AServant.h"
USING_NS_STD
USING_NS_TARS
using namespace TarsTest;

/****************************************************
Tars典型测试
校验返回值
****************************************************/

struct SimpleRpcTest : public ::testing::Test
{
    SimpleRpcTest()
    {
        _comm = Application::getCommunicator();
    }
protected:
    CommunicatorPtr _comm;
};

class SimpleRpcObjCallback: public AServantPrxCallback
{
public:
  virtual void callback_queryTest(tars::Int32 ret,  const vector<TarsTest::RspInfo>& vRsp)
  	{
       int iSize=vRsp.size();
	   EXPECT_EQ(iSize, 1);
	}
};
typedef tars::TC_AutoPtr<SimpleRpcObjCallback> SimpleRpcObjCallbackPtr;

TEST_F(SimpleRpcTest, should_response_rpc_when_client_sync_call_server_by_ip)
{
    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();
	
    AServantPrx prx  = _comm->stringToProxy<AServantPrx> (ASERVANT_ENDPOINT);
	ReqInfo stReq;
	stReq.sServerName="AServer";
	stReq.sDate="20181106";
	stReq.sStartTime="0000";
	stReq.sEndTime="2360";
	stReq.uInterval=1;
    vector<RspInfo> vRsp;
    int iRet = prx->queryTest(stReq,vRsp);

    EXPECT_EQ(iRet, 0);
    TLOGDEBUG("Simple RPC test time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
}
TEST_F(SimpleRpcTest, should_response_rpc_when_client_async_call_server_by_ip)
{
    AServantPrx prx = _comm->stringToProxy<AServantPrx> (ASERVANT_ENDPOINT);
    ReqInfo stReq;
	stReq.sServerName="AServer";
	stReq.sDate="20181106";
	stReq.sStartTime="0000";
	stReq.sEndTime="2360";
	stReq.uInterval=1;
    SimpleRpcObjCallbackPtr cbp = new SimpleRpcObjCallback();
    prx -> async_queryTest(cbp,stReq);

    TC_Common::sleep(1);

}

