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


#ifndef TARS_TAF_TEST_TESTCODE_INCLUDE_TARSSERVANTNAME_H_
#define TARS_TAF_TEST_TESTCODE_INCLUDE_TARSSERVANTNAME_H_
#include "TarsTest.h"

TARSTEST_NS_START

#define EXCEPT_BASE_RPC_SERVANT_ENDPOINT "TarsTest.UnitTest.RPCTestObj@tcp -h 127.0.0.1 -p 9000"

#define TEST_CASE_ADMIN_NAME_ENDPOINT  "AdminObj@tcp -h 127.0.0.1 -p 10100"
#define TEST_CASE_DYEING_ADMIN_NAME_ENDPOINT  "AdminObj@tcp -h 127.0.0.1 -p 10200"

#define HTTP_RPC_SERVANT_ENDPOINT            "TarsTest.TestcaseServer.HttpDemoObj@tcp -h 127.0.0.1 -p 10101"
#define MOCK_PROXY_SERVANT_ENDPOINT     "TarsTest.TestcaseServer.RPCTestObj@tcp -h 127.0.0.1 -p 10102"
#define BASE_RPC_SERVANT_ENDPOINT            "TarsTest.TestcaseServer.RPCTestObj@tcp -h 127.0.0.1 -p 10103"
#define UDP_RPC_SERVANT_ENDPOINT             "TarsTest.TestcaseServer.UdpRPCObj@udp -h 127.0.0.1 -p 10104"
#define PUSH_SERVANT_ENDPOINT                   "TarsTest.TestcaseServer.PushObj@tcp -h 127.0.0.1 -p 10105"
#define ONEWAY_RPC_SERVANT_ENDPOIONT  "TarsTest.TestcaseServer.OneWayRpcObj@tcp -h 127.0.0.1 -p 10110"

#define UNIT_TEST_ADMIN_NAME_ENDPOINT  "AdminObj@tcp -h 127.0.0.1 -p 10200"
#define UNIT_TEST_CONFIG_NAME_ENDPOINT "ConfigObj@tcp -h 127.0.0.1 -p 10200"


#define LOG_SERVER_ADMIN_NAME_ENDPOINT  "AdminObj@tcp -h 127.0.0.1 -p 10300"
#define STAT_SERVER_ADMIN_NAME_ENDPOINT  "AdminObj@tcp -h 127.0.0.1 -p 10400"


#define TYPT_TEST_ENDPOINT  "TarsTest.UnitTest.TypeDemoObj@tcp -h 127.0.0.1 -p 10000  -t 60000"
#define TUP_SERVANT_ENDPOINT    "TarsTest.UnitTest.TupDemoObj@tcp -h 127.0.0.1 -p 10001 -t 60000"
#define DYEING_SERVANT_ENDPOINT "TarsTest.UnitTest.DyeingTestObj@tcp -h 127.0.0.1 -p 10002 -t 60000"
#define PING_SERVANT_ENDPOINT "TarsTest.UnitTest.TarsPingTestObj@tcp -h 127.0.0.1 -p 10003 -t 60000"
#define ASERVANT_ENDPOINT "TarsTest.UnitTest.AServantObj@tcp -h 127.0.0.1 -p 10004 -t 60000"
#define TUP_PROXY_ENDPOINT "TarsTest.UnitTest.TupProxyObj@tcp -h 127.0.0.1 -p 10005 -t 60000"
#define AASERVANT_ENDPOINT "TarsTest.UnitTest.AAServantObj@tcp -h 127.0.0.1 -p 10006 -t 60000"
#define PROXY_ENDPOINT "TarsTest.UnitTest.ProxyObj@tcp -h 127.0.0.1 -p 10008"


#define BASE_RPC_SERVANT_NAME     "TarsTest.TestcaseServer.RPCTestObj"
#define BASE_RPC_SERVANT_NAME_INACTIVE     "TarsTest.TestcaseServer.RPCInactiveTestObj"

#define EPS_TEST_SERVANT_NAME     "TarsTest.TestcaseServer.EpsTestObj"

#define ONEWAY_RPC_SERVANT_NAME "TarsTest.TestcaseServer.OneWayRpcObj"
#define UDP_RPC_SERVANT_NAME "TarsTest.TestcaseServer.UdpRPCObj"

TARSTEST_NS_END

#endif /* TARS_TAF_TEST_TESTCODE_INCLUDE_TARSSERVANTNAME_H_ */
