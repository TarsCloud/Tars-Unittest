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
#include "TarsTest/TestcaseServer/RPCTest.h"
// #include "TarsTest/TestcaseServer/EpsTest.h"
#include "TarsTest/TestcaseServer/OneWayRpcTest.h"
#include "TarsServantName.h"
#include "stub/DbHandle.h"

USING_NS_STD
USING_NS_TARS
using namespace TarsTest;

struct EndPointTest : public ::testing::Test
{
    EndPointTest()
    {
        _comm = Application::getCommunicator();
    }
    void TearDown()
    {
        CDbHandle::cleanEndPoint();
    }
protected:
    CommunicatorPtr _comm;
};

TEST_F(EndPointTest, consistant_hash_endpoint_normal)
{
    CDbHandle::addActiveEndPoint(EPS_TEST_SERVANT_NAME, 10120, TC_Endpoint::TCP);
    
    CDbHandle::addInactiveEndPoint(EPS_TEST_SERVANT_NAME, 10411, TC_Endpoint::TCP);
    
    CDbHandle::addInactiveEndPoint(EPS_TEST_SERVANT_NAME, 10412, TC_Endpoint::TCP);
    
    RPCTestPrx prx  = _comm->stringToProxy<RPCTestPrx> (EPS_TEST_SERVANT_NAME);

    int res = prx->tars_consistent_hash(2)->test();

    EXPECT_EQ(res, 2);
}


TEST_F(EndPointTest, given_servant_endpoint_added_to_registry_when_call_rpc_by_servant_name_then_rpc_response)
{
    CDbHandle::addActiveEndPoint(EPS_TEST_SERVANT_NAME, 10120, TC_Endpoint::TCP);
    
    CDbHandle::addInactiveEndPoint(EPS_TEST_SERVANT_NAME, 10123, TC_Endpoint::TCP);
    
    CDbHandle::addInactiveEndPoint(EPS_TEST_SERVANT_NAME, 10124, TC_Endpoint::TCP);
                
    RPCTestPrx prx  = _comm->stringToProxy<RPCTestPrx> (EPS_TEST_SERVANT_NAME);

    int res = prx->test();

    EXPECT_EQ(res, 2);
}



TEST_F(EndPointTest, hash_endpoint_normal)
{
    CDbHandle::addActiveEndPoint(EPS_TEST_SERVANT_NAME, 10120, TC_Endpoint::TCP);
    
    CDbHandle::addInactiveEndPoint(EPS_TEST_SERVANT_NAME, 10123, TC_Endpoint::TCP);
    
    CDbHandle::addInactiveEndPoint(EPS_TEST_SERVANT_NAME, 10124, TC_Endpoint::TCP);
    
    RPCTestPrx prx  = _comm->stringToProxy<RPCTestPrx> (EPS_TEST_SERVANT_NAME);

    int res = prx->tars_hash(1)->test();

    EXPECT_EQ(res, 2);
}

TEST_F(EndPointTest, hash_endpoint_expect)
{
    CDbHandle::addActiveEndPoint(EPS_TEST_SERVANT_NAME, 10120, TC_Endpoint::TCP);
    
    CDbHandle::addInactiveEndPoint(EPS_TEST_SERVANT_NAME, 10123, TC_Endpoint::TCP);
    
    CDbHandle::addInactiveEndPoint(EPS_TEST_SERVANT_NAME, 10124, TC_Endpoint::TCP);
    
    RPCTestPrx prx  = _comm->stringToProxy<RPCTestPrx> (EPS_TEST_SERVANT_NAME);

    
    int res = prx->tars_hash(2)->test();

    EXPECT_EQ(res, 2);
}


TEST_F(EndPointTest, endpoint_cons_hash2)
{
    CDbHandle::addActiveEndPoint(EPS_TEST_SERVANT_NAME, 10120, TC_Endpoint::TCP);
    
    CDbHandle::addInactiveEndPoint(EPS_TEST_SERVANT_NAME, 10123, TC_Endpoint::TCP);
    
    CDbHandle::addInactiveEndPoint(EPS_TEST_SERVANT_NAME, 10124, TC_Endpoint::TCP);
    
    RPCTestPrx prx  = _comm->stringToProxy<RPCTestPrx> (EPS_TEST_SERVANT_NAME);

    int res = prx->tars_consistent_hash(2)->test();

    EXPECT_EQ(res, 2);
}
TEST_F(EndPointTest, consistant_hash1_endpoint_staticweight)
{
    CDbHandle::addActiveWeight1EndPoint(ONEWAY_RPC_SERVANT_NAME, 10110, TC_Endpoint::TCP);
        
    CDbHandle::addInActiveWeight1EndPoint(ONEWAY_RPC_SERVANT_NAME, 10131, TC_Endpoint::TCP);
    
    OneWayRpcTestPrx prx  = _comm->stringToProxy<OneWayRpcTestPrx> (ONEWAY_RPC_SERVANT_NAME);

    int res = prx->tars_consistent_hash(1)->test();

    EXPECT_EQ(res, 2);
}

TEST_F(EndPointTest, static_weight_endpoint)
{
    CDbHandle::addActiveWeight1EndPoint(ONEWAY_RPC_SERVANT_NAME, 10110, TC_Endpoint::TCP);
    
    CDbHandle::addInActiveWeight1EndPoint(ONEWAY_RPC_SERVANT_NAME, 10131, TC_Endpoint::TCP);
        
    OneWayRpcTestPrx prx  = _comm->stringToProxy<OneWayRpcTestPrx> (ONEWAY_RPC_SERVANT_NAME);

    int res = prx->test();

    EXPECT_EQ(res, 2);
}


TEST_F(EndPointTest, hash_endpoint_staticweight1)
{
    CDbHandle::addActiveWeight1EndPoint(ONEWAY_RPC_SERVANT_NAME, 10110, TC_Endpoint::TCP);
    
    CDbHandle::addInActiveWeight1EndPoint(ONEWAY_RPC_SERVANT_NAME, 10131, TC_Endpoint::TCP);
    
    OneWayRpcTestPrx prx  = _comm->stringToProxy<OneWayRpcTestPrx> (ONEWAY_RPC_SERVANT_NAME);

    int res = prx->tars_hash(2)->test();

    EXPECT_EQ(res, 2);
}


TEST_F(EndPointTest, given_regitery_disable_when_call_rpc_by_servant_name_then_rpc_exception)
{
    try
    {
        Communicator comm;
        RPCTestPrx prx = comm.stringToProxy<RPCTestPrx> (BASE_RPC_SERVANT_NAME);

        ASSERT_TRUE(false);
    }
    catch (std::exception& e)
    {
        cout << "std::exception:" << e.what() << std::endl;
        EXPECT_STREQ(e.what(), "locator is not valid,_locator:");
    }
}

TEST_F(EndPointTest, given_servant_not_exist_when_call_rpc_by_servant_name_then_rpc_exception)
{
    try
    {
        RPCTestPrx prx = _comm->stringToProxy<RPCTestPrx> ("TarsTest.TestcaseServer.NotExistObj");

        prx->test();

        ASSERT_TRUE(false);
    }
    catch (std::exception& e)
    {
        cout << "std::exception:" << e.what() << std::endl;
        EXPECT_TRUE(string(e.what()).find("server unknown exception: ret:-7") != string::npos);
    }
}


TEST_F(EndPointTest, consistanthash_endpoint_inactive)
{

    CDbHandle::addActiveWeight1EndPoint(BASE_RPC_SERVANT_NAME, 10103, TC_Endpoint::TCP);

    CDbHandle::addInActiveWeight1EndPoint(BASE_RPC_SERVANT_NAME, 10124, TC_Endpoint::TCP);

    RPCTestPrx prx  = _comm->stringToProxy<RPCTestPrx> (BASE_RPC_SERVANT_NAME);

    int res = prx->tars_consistent_hash(1)->test();

    EXPECT_EQ(res, 2);

    int res1 = prx->tars_consistent_hash(2)->test();

    EXPECT_EQ(res1, 2);
}

