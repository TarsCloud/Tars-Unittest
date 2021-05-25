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
#include "servant/Application.h"
#include "TarsTest/UnitTest/Proxy.h"
#include "TarsServantName.h"
using namespace std;
using namespace TarsTest;
using namespace tars;
/****************************************************
Porxy测试，主调调用Proxy的接口，Proxy调用被调
主调与Proxy、Proxy与被调之间都是tars调用
校验返回值
****************************************************/

/**
* @brief 代理回调类
*/

class ProxyTestCallback: public ProxyPrxCallback
{
     virtual void callback_testProxy(tars::Int32 ret,  const std::string& sRsp)
     {
        EXPECT_EQ(ret,0);
		EXPECT_STREQ(sRsp.c_str(),"tars go");
	 }
};

struct ProxyTest : public ::testing::Test 
{
    ProxyTest()
    {
        _comm = Application::getCommunicator();
    }
protected:
    CommunicatorPtr _comm;
};
typedef tars::TC_AutoPtr<ProxyTestCallback> ProxyTestCallbackPtr;

//同步调用
TEST_F(ProxyTest, should_response_when_syn_call_proxy_call)
{   
    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();
	
    ProxyPrx prx;
    prx=_comm->stringToProxy<ProxyPrx>(PROXY_ENDPOINT);

    try
    {
		string sReq("tars go");
        string sRsp("");
		int iRet = prx->testProxy(sReq, sRsp);
		EXPECT_EQ(iRet,0);
		EXPECT_STREQ(sReq.c_str(),sRsp.c_str());

    }
    catch(exception &ex)
    {
        
		 TLOGERROR("ex:" << ex.what() << endl);
    }
    catch(...)
    {
         TLOGERROR("unknown exception." << endl);
    }
	
    TLOGDEBUG("Proxy test time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
}

//异步调用
TEST_F(ProxyTest, should_response_when_asyn_call_proxy_call)
{
    ProxyPrx prx;
    prx=_comm->stringToProxy<ProxyPrx>(PROXY_ENDPOINT);

    try
    {
		string sReq("tars go");
        ProxyTestCallbackPtr cbp= new ProxyTestCallback();
		prx->async_testProxy(cbp,sReq);
		TC_Common::sleep(1);
    }
    catch(exception &ex)
    {
        
		 TLOGERROR("ex:" << ex.what() << endl);
    }
    catch(...)
    {
         TLOGERROR("unknown exception." << endl);
    }

}

