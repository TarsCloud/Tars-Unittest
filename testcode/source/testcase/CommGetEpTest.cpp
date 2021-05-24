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
#include "stub/DbHandle.h"


USING_NS_STD
USING_NS_TARS
using namespace TarsTest;

struct CommGetEpTest : public ::testing::Test
{
    CommGetEpTest()
    {
        _comm = Application::getCommunicator();
    }
protected:
    CommunicatorPtr _comm;
};


TEST_F(CommGetEpTest, should_return_endpoint)
{
    string setName = "ab.cd.ef";
    
    CDbHandle::addInactiveEndPoint(BASE_RPC_SERVANT_NAME, 10121, TC_Endpoint::TCP);
    
    CDbHandle::addActiveEndPoint(BASE_RPC_SERVANT_NAME, 10103, TC_Endpoint::TCP);

    RPCTestPrx prx  = _comm->stringToProxy<RPCTestPrx> (BASE_RPC_SERVANT_ENDPOINT);

    vector<EndpointInfo> activeEndPoint, inactiveEndPoint;
    prx->tars_endpoints(activeEndPoint, inactiveEndPoint);

    EXPECT_EQ(activeEndPoint.size(), 1);
    EXPECT_EQ(inactiveEndPoint.size(), 1);
}


TEST_F(CommGetEpTest, should_return_endpoint_all)
{
    CDbHandle::addInactiveEndPoint(BASE_RPC_SERVANT_NAME, 10121, TC_Endpoint::TCP);

    RPCTestPrx prx  = _comm->stringToProxy<RPCTestPrx> (BASE_RPC_SERVANT_ENDPOINT);

    vector<EndpointInfo> activeEndPoint, inactiveEndPoint;
    prx->tars_endpointsAll(activeEndPoint, inactiveEndPoint);

    EXPECT_EQ(activeEndPoint.size(), 1);
    EXPECT_EQ(inactiveEndPoint.size(), 1);
}

TEST_F(CommGetEpTest, should_return_endpoint_by_set)
{
    string setName = "ab.cd.ef";
    
    CDbHandle::addEndPointbySet(BASE_RPC_SERVANT_NAME, 10103, TC_Endpoint::TCP, "ab", "cd", "ef");
   
    RPCTestPrx prx  = _comm->stringToProxy<RPCTestPrx> (BASE_RPC_SERVANT_ENDPOINT);

    vector<EndpointInfo> activeEndPoint, inactiveEndPoint;
    prx->tars_endpointsBySet(setName, activeEndPoint, inactiveEndPoint);

    EXPECT_EQ(activeEndPoint.size(), 1);
    EXPECT_EQ(inactiveEndPoint.size(), 1);
}

TEST_F(CommGetEpTest, should_response_all_endpoints)
{
    
    CDbHandle::addActiveEndPoint(BASE_RPC_SERVANT_NAME, 10103, TC_Endpoint::TCP);

    vector<TC_Endpoint> vEndpoint = _comm->getEndpoint("TarsTest.TestcaseServer.RPCTestObj");

    RPCTestPrx prx;
    string sEndpoint("");
    sEndpoint += "TarsTest.TestcaseServer.RPCTestObj";
    sEndpoint += "@";
    sEndpoint += vEndpoint[0].toString();

    prx  = _comm->stringToProxy<RPCTestPrx> (sEndpoint);

    int res = prx->test();
    EXPECT_EQ(res, 2);

    vector<TC_Endpoint> vEndpointAll = _comm->getEndpoint4All(BASE_RPC_SERVANT_NAME);

    RPCTestPrx prxall;
    for(size_t i = 0; i < vEndpointAll.size(); ++i)
    {
        string sEndpointall("");
        sEndpointall += BASE_RPC_SERVANT_NAME;
        sEndpointall += "@";
        sEndpointall += vEndpointAll[i].toString();

        cout << sEndpointall << endl;

        prxall  = _comm->stringToProxy<RPCTestPrx> (sEndpointall);
    }
    
    int resall = prxall->test();
    EXPECT_EQ(resall, 2);
}


