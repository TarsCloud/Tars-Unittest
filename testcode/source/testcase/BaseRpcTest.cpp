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
// #include "util/tc_bind.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "TarsServantName.h"

USING_NS_STD
USING_NS_TARS
using namespace TarsTest;

struct BaseRpcTest : public ::testing::Test
{
    BaseRpcTest()
    {
        _comm = Application::getCommunicator();
    }
    void SetUp()
    {
        isCallbackCalled = false;
    }
    static bool isCallbackCalled;
protected:
    CommunicatorPtr _comm;
};
bool BaseRpcTest::isCallbackCalled = false;

class RPCTestObjCallback: public RPCTestPrxCallback
{
public:
    virtual void callback_test(Int32 ret)
    {
        EXPECT_EQ(ret, 2);
        BaseRpcTest::isCallbackCalled = true;
    }
};
typedef tars::TC_AutoPtr<RPCTestObjCallback> RPCTestObjCallbackPtr;

TEST_F(BaseRpcTest, should_response_rpc_when_client_sync_call_server_by_ip)
{
    RPCTestPrx prx  = _comm->stringToProxy<RPCTestPrx> (BASE_RPC_SERVANT_ENDPOINT);

    int res = prx->test();

    EXPECT_EQ(res, 2);

}
TEST_F(BaseRpcTest, should_rpc_exception_when_client_sync_call_not_exist_server)
{
    try
    {
        RPCTestPrx prx = _comm->stringToProxy<RPCTestPrx> (EXCEPT_BASE_RPC_SERVANT_ENDPOINT);

        prx->test();

        ASSERT_TRUE(false);
    }
    catch (std::exception& e)
    {
        EXPECT_TRUE(string(e.what()).find("server unknown exception: ret:-7") != string::npos);
    }
}


TEST_F(BaseRpcTest, should_response_rpc_when_client_async_call_server_by_ip)
{
    RPCTestPrx prx = _comm->stringToProxy<RPCTestPrx> (BASE_RPC_SERVANT_ENDPOINT);

    RPCTestObjCallbackPtr cbp = new RPCTestObjCallback();

    prx -> async_test(cbp);

    TC_Common::sleep(1);

    EXPECT_TRUE(isCallbackCalled);
}

// extern "C" void handleResult(const promise::Future<  RPCTestPrxCallbackPromise::PromisetestPtr >& f)
// {
//     do
//     {
//         RPCTestPrxCallbackPromise::PromisetestPtr ptr = f.get();
//         EXPECT_EQ(ptr->_ret, 2);
//         BaseRpcTest::isCallbackCalled = true;
//     } while (0);
// }
// TEST_F(BaseRpcTest, should_response_rpc_when_client_promise_async_call_server_by_ip)
// {
//     RPCTestPrx prx;
//     map<string, string> context;
//     prx = _comm->stringToProxy<RPCTestPrx> (BASE_RPC_SERVANT_ENDPOINT);

//     promise::Future< RPCTestPrxCallbackPromise::PromisetestPtr > f = prx -> promise_async_test(context);

//     f.then(tars::TC_Bind(&handleResult));

//     sleep(1);

//     EXPECT_TRUE(isCallbackCalled);
// }

