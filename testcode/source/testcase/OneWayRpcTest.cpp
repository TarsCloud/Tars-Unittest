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
#include "TarsTest/TestcaseServer/OneWayRpcTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"

using namespace std;
using namespace tars;
using namespace TarsTest;

bool g_OneWayRpcTestSuccess = false;

struct OneWayRpcTestS : public::testing::Test
{
public:
    OneWayRpcTestS()
    {
        _comm = new Communicator();
    }
protected:
    CommunicatorPtr _comm;
};

class OneWayRpcTestObjCallback: public OneWayRpcTestPrxCallback
{
public:
    virtual void callback_test(Int32 ret)
    {
        cerr << "std::exception: err callback" <<  std::endl;
    }
};
typedef tars::TC_AutoPtr<OneWayRpcTestObjCallback> OneWayRpcTestObjCallbackPtr;


TEST_F(OneWayRpcTestS, oneway_should_response_rpc_when_client_async_call_server_by_ip)
{
    g_OneWayRpcTestSuccess = false;
    
    OneWayRpcTestPrx prx = _comm->stringToProxy<OneWayRpcTestPrx> (ONEWAY_RPC_SERVANT_ENDPOIONT);

    prx -> async_test(NULL);

    TC_Common::sleep(1);

    EXPECT_TRUE(g_OneWayRpcTestSuccess);
}



