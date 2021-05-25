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
#include <iostream>
#include <cstdlib>
// #include <unistd.h>
#include "gtest/gtest.h"
#include "util/tc_common.h"
#include "util/tc_clientsocket.h"
#include "servant/Application.h"
#include "tup/tup.h"
#include "TarsTest/UnitTest/TupDemo.h"
using namespace std;
using namespace tars;
using namespace TarsTest;

/****************************************************
TCP请求方式测试TUP协议
TUP协议是构建在Tars编解基础之上的传输协议
TUP协议通过put和get方法打包和解包
****************************************************/

TEST(TupHttpTest, test_tup_http_when_client_sync_call_server_by_ip)
{

    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();

	TC_TCPClient tcpClient;
    tcpClient.init("127.0.0.1", 10001, 3000);
	
	TarsUniPacket<> req;
	TarsUniPacket<>rsp;
	int iRequestId=1;
	req.setRequestId(iRequestId);
	req.setServantName("TarsTest.UnitTest.TupDemoObj");
    req.setFuncName("aAddb");
	
	struct AddInt addData;
	addData.adda = 2;
	addData.addb = 1;
	addData.addStr = "2 + 1 = 3";
    req.put<const AddInt>("addData",addData);
	
	string sendBuff;
	req.encode(sendBuff);	
	
    int iRet = -1; 
    try
    {
        

        int iSuc = tcpClient.send(sendBuff.c_str(),sendBuff.size()); 
		char recvBuff[1024]={0};
		size_t recvLen = sizeof(recvBuff);
		iSuc = tcpClient.recv(recvBuff,recvLen);
		rsp.decode(recvBuff,recvLen);

		
		TLOGDEBUG("[requestId]:" << rsp.getRequestId() << endl);
	    TLOGDEBUG("[servantName]:" << rsp.getServantName() << endl);
	    TLOGDEBUG("[funcName]:" << rsp.getFuncName() << endl);
		TLOGDEBUG("getTarsVersion|"<<rsp.getTarsVersion()<<endl);

		iRet = rsp.get<int>("");


    }
    catch(TC_Exception &e)
    {
         cout << " exception: " << e.what() << endl;
    }
    catch(...)
    {
         cout << " unknown exception." << endl;
    }
	
	
    struct Result aAddbResult; 
	rsp.get<Result>("aAddbResult",aAddbResult);
	EXPECT_EQ(iRet,0);
	EXPECT_EQ(aAddbResult.addResult,3);

	TLOGDEBUG("tup http test time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
}

