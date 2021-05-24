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

struct PropertyTest : public ::testing::Test
{
    PropertyTest()
    {
        _comm = Application::getCommunicator();
    }
protected:
    CommunicatorPtr _comm;
};

TEST_F(PropertyTest, should_response_rpc_when_client_sync_call_server_by_ip)
{

    map<string, string> mapConfig;
    
    mapConfig["sync-invoke-timeout"] = "3000";
    mapConfig["async-invoke-timeout"] = "3000";
    mapConfig["refresh-endpoint-interval"] = "5000";
    mapConfig["report-interval"] = "30";
    mapConfig["sendthread"] = "2";
    mapConfig["recvthread"] = "2";
    mapConfig["asyncthread"] = "4";
    mapConfig["sample-rate"] = "1000001";
    mapConfig["max-sample-count"] = "15";
    mapConfig["enableset"] = "y";

    _comm->setProperty(mapConfig);
    
    RPCTestPrx prx  = _comm->stringToProxy<RPCTestPrx> (BASE_RPC_SERVANT_ENDPOINT);

    
    int syncTimeOut  = TC_Common::strto<int>(_comm->getProperty("sync-invoke-timeout"));
    int AyncTimeOut  = TC_Common::strto<int>(_comm->getProperty("async-invoke-timeout"));
    int RefreshEpInterval  = TC_Common::strto<int>(_comm->getProperty("refresh-endpoint-interval"));
    int reportInterval  = TC_Common::strto<int>(_comm->getProperty("report-interval"));
    int sendthread  = TC_Common::strto<int>(_comm->getProperty("sendthread"));
    int recvthread  = TC_Common::strto<int>(_comm->getProperty("recvthread"));
    int asyncthread  = TC_Common::strto<int>(_comm->getProperty("asyncthread"));
    int samplerate  = TC_Common::strto<int>(_comm->getProperty("sample-rate"));
    int maxsamplecount  = TC_Common::strto<int>(_comm->getProperty("max-sample-count"));

    EXPECT_EQ(syncTimeOut, 3000);
    EXPECT_EQ(AyncTimeOut, 3000);
    EXPECT_EQ(RefreshEpInterval, 5000);
    EXPECT_EQ(reportInterval, 30);
    EXPECT_EQ(sendthread, 2);
    EXPECT_EQ(recvthread, 2);
    EXPECT_EQ(asyncthread, 4);
    EXPECT_EQ(samplerate, 1000001);
    EXPECT_EQ(maxsamplecount, 15);

    mapConfig["sync-invoke-timeout"] = "2000";
    mapConfig["async-invoke-timeout"] = "2000";
    mapConfig["refresh-endpoint-interval"] = "6000";
    mapConfig["report-interval"] = "60";
    mapConfig["sendthread"] = "1";
    mapConfig["recvthread"] = "1";
    mapConfig["asyncthread"] = "2";
    mapConfig["sample-rate"] = "1000000";
    mapConfig["max-sample-count"] = "10";

    _comm->setProperty(mapConfig);
    
    prx  = _comm->stringToProxy<RPCTestPrx> (BASE_RPC_SERVANT_ENDPOINT);
}


