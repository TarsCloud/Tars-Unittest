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

/*
 * UdpRpcTest.cpp
 *
 *  Created on: 2018年10月19日
 *      Author: abelguo
 */
#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"

USING_NS_STD
USING_NS_TARS
using namespace TarsTest;
USING_NS_TARSTEST

struct UdpRpcTest : public ::testing::Test
{
    UdpRpcTest()
    {
        _comm = Application::getCommunicator();
    }
protected:
    CommunicatorPtr _comm;
};

TEST_F(UdpRpcTest, should_response_udp_rpc_when_client_sync_call_server_by_ip)
{
    RPCTestPrx prx  = _comm->stringToProxy<RPCTestPrx> (UDP_RPC_SERVANT_ENDPOINT);

    int res = prx->test();

    EXPECT_EQ(res, 2);
}

