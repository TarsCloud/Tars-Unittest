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
#include <string>
#include <map>
#include <iostream>
#include "util/tc_http.h"
#include "util/tc_common.h"
#include "util/tc_clientsocket.h"
#include "servant/Application.h"
#include "TarsServantName.h"



USING_NS_STD
USING_NS_TARS
USING_NS_TARSTEST

/****************************************************
http测试，测试原生接口的POST和GET两种方式
1.POST方式下，客户端的请求为Json串
2.GET方式下， 客户端的请求为参数字符串
校验返回码和内容
****************************************************/

// /**
// * @brief 请求执行方法
// * @param sSendBuffer
// * @param tcpClient
// * @param stHttpRsp
// * @param iTimeout
// * @return int(返回码，0是成功，-3为超时)
// */
// int doRequest(const string& sSendBuffer,TC_TCPClient&tcpClient, TC_HttpResponse &stHttpRsp, int iTimeout)
// {
//     int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();

// 	int iRet = tcpClient.send(sSendBuffer.c_str(), sSendBuffer.length());
// 	if(iRet != TC_ClientSocket::EM_SUCCESS)
// 	{
// 		return iRet;
// 	}

// 	stHttpRsp.reset();

// 	string sBuffer;

// 	char *sTmpBuffer = new char[10240];
// 	size_t iRecvLen  = 10240;

// 	while(true)
// 	{
// 		iRecvLen = 10240;

// 		iRet = tcpClient.recv(sTmpBuffer, iRecvLen);

// 		if(iRet == TC_ClientSocket::EM_SUCCESS)
// 		sBuffer.append(sTmpBuffer, iRecvLen);

// 		switch(iRet)
// 		{
// 		case TC_ClientSocket::EM_SUCCESS:
// 			if(stHttpRsp.incrementDecode(sBuffer))
// 			{
// 				delete []sTmpBuffer;
// 				return TC_ClientSocket::EM_SUCCESS;
// 			}
// 			continue;
// 		case TC_ClientSocket::EM_CLOSE:
// 			delete []sTmpBuffer;
// 			stHttpRsp.incrementDecode(sBuffer);
// 			return TC_ClientSocket::EM_SUCCESS;
// 		default:
// 			delete []sTmpBuffer;
// 			return iRet;
// 		}
// 	}

//     TLOGDEBUG("Http request time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
// 	return 0;
// }

/**
* @brief Get方法
* @param strOut
* @return int(返回码，0是成功，-3为超时)
*/

int th_doGet(string& strOut)
{
    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();  

    string sServer1("http://127.0.0.1:10101/query?a=b&c=d");

    TC_TCPClient tcpClient1;
    tcpClient1.init("127.0.0.1", 10101, 3000);
     
    TC_HttpRequest stHttpReq;
	stHttpReq.setCacheControl("no-cache");
	stHttpReq.setHeader("x-tx-host", "");
	stHttpReq.setHeader("Connection", "Keep-Alive"); 
	stHttpReq.setGetRequest(sServer1);
    // string sSendBuffer = stHttpReq.encode();
	
	TC_HttpResponse stHttpRsp;
	
	int iRet = -1;
	try
	  {
            
		iRet = stHttpReq.doRequest(tcpClient1, stHttpRsp); 	 
		if (iRet ==0)
		{
            strOut=stHttpRsp.getContent();
			TLOGDEBUG("Http rsp: "<<stHttpRsp.getContent()<<endl);
		    
        }
      } 
   
    catch(TC_Exception &e)
    {
         cout << " exception: " << e.what() << endl;
    }
    catch(...)
    {
         cout << " unknown exception." << endl;
    }
	
	TLOGDEBUG("get request time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
    return iRet;
}

/**
* @brief Post方法
* @param strOut
* @return int(返回码，0是成功，-3为超时)
*/

int th_doPost(string& strOut)
{
   

    string sServer1("http://127.0.0.1:10101/");

    TC_TCPClient tcpClient1;
    tcpClient1.init("127.0.0.1", 10101, 3000);
     
    TC_HttpRequest stHttpReq;
	stHttpReq.setCacheControl("no-cache");
	stHttpReq.setHeader("x-tx-host", "");
	stHttpReq.setHeader("Connection", "Keep-Alive"); 
    stHttpReq.setContentType("application/json");

	int iRet = -1;
	
    string sBuff("");
    sBuff="{\"key1\":\"value1\" \"key2\":\"value2\"}";
	
    stHttpReq.setPostRequest(sServer1, sBuff);
    // string sSendBuffer = stHttpReq.encode();
	TC_HttpResponse stHttpRsp;
	
	try
	  {
            
		iRet = stHttpReq.doRequest(tcpClient1, stHttpRsp); 	 
		if (iRet ==0)
		{
            strOut=stHttpRsp.getContent();
			TLOGDEBUG("Http rsp: "<<stHttpRsp.getContent()<<endl);
		    
        }
      } 
    
    catch(TC_Exception &e)
    {
         cout << " exception: " << e.what() << endl;
    }
    catch(...)
    {
         cout << " unknown exception." << endl;
    }
	
    return iRet;
}

//Get测试
TEST(HttpTest, should_http_response_when_client_get_call)
{
    string str;
    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs(); 
	int iRet=th_doGet(str);
	TLOGDEBUG("post request time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
    EXPECT_TRUE(str.find("Hello Tars") != string::npos);
	EXPECT_EQ(iRet, 0);
}

//Post测试
TEST(HttpTest, should_http_response_when_client_post_call)
{
	string str;
	 int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs(); 
	int iRet=th_doPost(str);
	TLOGDEBUG("post request time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
    EXPECT_TRUE(str.find("Hello Tars") != string::npos);
	EXPECT_EQ(iRet, 0);
}

