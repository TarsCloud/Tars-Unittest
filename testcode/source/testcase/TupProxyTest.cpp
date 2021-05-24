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
#include "servant/Application.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tars;

/**
* @brief 构造Tup请求包		
* @param id
* @return string
*/

string parsebuffer(int id)
{
    string buff;
    UniPacket<> req;

    req.setRequestId(id);
    req.setServantName("AServer");
    req.setFuncName("testInt");
    req.put<int>("iIn", 2);

    req.encode(buff);

    return buff;
}

// /**
// * @brief 请求方法
// * @param stHttp
// * @param tcpClient
// * @param stHttpRsp
// * @param iTimeout
// * @return int(返回码，0是成功，-3为超时)
// */
// int doTupRequest(TC_HttpRequest& stHttp,TC_TCPClient&tcpClient, TC_HttpResponse &stHttpRsp, int iTimeout)
// {
//     string sSendBuffer = stHttp.encode();
//     int iRet = tcpClient.send(sSendBuffer.c_str(), sSendBuffer.length());
//     if(iRet != TC_ClientSocket::EM_SUCCESS)
//     {
//         return iRet;
//     }

//     stHttpRsp.reset();

//     string sBuffer;

//     char *sTmpBuffer = new char[10240];
	
//     size_t iRecvLen  = 10240;

//     while(true)
//     {
//         iRecvLen = 10240;

//         iRet = tcpClient.recv(sTmpBuffer, iRecvLen);


//         if(iRet == TC_ClientSocket::EM_SUCCESS)
//             sBuffer.append(sTmpBuffer, iRecvLen);

//         switch(iRet)
//         {
//         case TC_ClientSocket::EM_SUCCESS:
//             if(stHttpRsp.incrementDecode(sBuffer))
//             {
				
//                 delete []sTmpBuffer;
//                 return TC_ClientSocket::EM_SUCCESS;
//             }
// 			else
// 			{
				
// 			}
//             continue;
//         case TC_ClientSocket::EM_CLOSE:
//             delete []sTmpBuffer;
//             stHttpRsp.incrementDecode(sBuffer);
//             return TC_ClientSocket::EM_SUCCESS;
			
//         default:
//             delete []sTmpBuffer;
//             return iRet;
//         }
//     }

//     return 0;
// }
/**
* @brief 执行请求方法
* @return int(返回码，0是成功，-3为超时)
*/

int tup_dohandle()
{
	
	//int64_t _iTime=TC_TimeProvider::getInstance()->getNowMs();
   
	int id = 0;
	TC_TCPClient tcpClient1;
	tcpClient1.init("127.0.0.1", 10005,3000);
    TC_HttpRequest stHttpReq;
    stHttpReq.setCacheControl("no-cache");
	string sServer1("http://127.0.0.1:10005");
	
    int iRet = -1;
        try
		{
            TC_HttpResponse stHttpRep;
			
			stHttpReq.setPostRequest(sServer1, parsebuffer(id++));

			iRet = stHttpReq.doRequest(tcpClient1,stHttpRep);  

			
		}
		catch(TC_Exception &e)
		{
			cout << "exception: " << e.what() << endl;
		}
		catch(...)
		{
			cout << " unknown exception." << endl;
		}
		return iRet;
}
TEST(TupProxyTest, should_response_tup_proxy_test_when_call_by_http)
{
    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();
	
	int iRet=tup_dohandle();
   
	EXPECT_EQ(iRet, 0);
	
	TLOGDEBUG("tupproxy  test time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
}

