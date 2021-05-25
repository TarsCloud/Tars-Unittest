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

struct CoroutineRpcTest : public ::testing::Test
{
    CoroutineRpcTest()
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
bool CoroutineRpcTest::isCallbackCalled = false;

class RPCTestObjCoroPrxCallback: public RPCTestCoroPrxCallback
{
public:
    virtual void callback_test(Int32 ret)
    {
        EXPECT_EQ(ret, 2);
        CoroutineRpcTest::isCallbackCalled = true;
    }
    virtual void callback_testStr(Int32 ret, const std::string& sOut)
    {
        EXPECT_STREQ(sOut.c_str(), "out");
        EXPECT_EQ(ret, 2);
        CoroutineRpcTest::isCallbackCalled = true;
    }
};
typedef tars::TC_AutoPtr<RPCTestObjCoroPrxCallback> RPCTestObjCoroPrxCallbackPtr;

//继承框架的协程类
class TestCoroutine : public Coroutine
{
public:
    TestCoroutine(const string &sObj):_sObj(sObj)
    {
        _comm.stringToProxy(_sObj, prx);
    }
    ~TestCoroutine() {}

    void handle()
    {
        CoroParallelBasePtr sharedPtr = new CoroParallelBase(2);

        RPCTestObjCoroPrxCallbackPtr cb1 = new RPCTestObjCoroPrxCallback();
        cb1->setCoroParallelBasePtr(sharedPtr);
        prx->coro_test(cb1);

        RPCTestObjCoroPrxCallbackPtr cb2 = new RPCTestObjCoroPrxCallback();
        cb2->setCoroParallelBasePtr(sharedPtr);
        prx->coro_testStr(cb2);

        coroWhenAll(sharedPtr);
    }
private:
    string _sObj;
    Communicator _comm;
    RPCTestPrx prx;
};


TEST_F(CoroutineRpcTest, should_response_rpc_when_client_Coroutine_call_server_by_ip)
{
    ServerConfig::OpenCoroutine = true;

    TestCoroutine testCoro(BASE_RPC_SERVANT_ENDPOINT);

    testCoro.setCoroInfo(1, 1, 128*1024);

    testCoro.start();

    testCoro.getThreadControl().join();

    TC_Common::sleep(1);

    EXPECT_TRUE(isCallbackCalled);
}

