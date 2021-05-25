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
 * PushTest.cpp
 *
 *  Created on: 2018年10月23日
 *      Author: abelguo
 */
#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsServantName.h"

USING_NS_STD
USING_NS_TARS

/*
 响应包解码函数，根据特定格式解码从服务端收到的数据，解析为ResponsePacket
*/
    // static vector<char> http1Request(tars::RequestPacket& request, Transceiver *);
// static TC_NetWorkBuffer::PACKET_TYPE pushResponse(TC_NetWorkBuffer &in, ResponsePacket& done)
// {
// static size_t pushResponse(const char* recvBuffer, size_t length, list<ResponsePacket>& done)
// {
//     // size_t pos = 0;
//     // while (pos < length)
//     // {
//         unsigned int len = length - pos;
//         if(len < sizeof(unsigned int))
//         {
//             break;
//         }
//         unsigned int iHeaderLen = ntohl(*(unsigned int*)(recvBuffer + pos));
//         //做一下保护,长度大于M
//         if (iHeaderLen > 100000 || iHeaderLen < sizeof(unsigned int))
//         {
//             throw TarsDecodeException("packet length too long or too short,len:" + TC_Common::tostr(iHeaderLen));
//         }
//         //包没有接收全
//         if (len < iHeaderLen)
//         {
//             break;
//         }
//         else
//         {
//             ResponsePacket rsp;
//             rsp.iRequestId = ntohl(*((unsigned int *)(recvBuffer + pos + sizeof(unsigned int))));
//             rsp.sBuffer.resize(iHeaderLen - 2*sizeof(unsigned int));
//             ::memcpy(&rsp.sBuffer[0], recvBuffer + pos + 2*sizeof(unsigned int), iHeaderLen - 2*sizeof(unsigned int));
//             pos += iHeaderLen;
//             done.push_back(rsp);
//         }
//     // }
//     return pos;
// }

/*
 响应包解码函数，根据特定格式解码从服务端收到的数据，解析为ResponsePacket
*/
static TC_NetWorkBuffer::PACKET_TYPE pushResponse(TC_NetWorkBuffer &in, ResponsePacket& rsp)
{
	size_t len = sizeof(tars::Int32);

	if (in.getBufferLength() < len)
	{
		return TC_NetWorkBuffer::PACKET_LESS;
	}

	string header;
	in.getHeader(len, header);

	assert(header.size() == len);

	tars::Int32 iHeaderLen = 0;

	::memcpy(&iHeaderLen, header.c_str(), sizeof(tars::Int32));

	iHeaderLen = ntohl(iHeaderLen);

	//做一下保护,长度大于M
	if (iHeaderLen > 100000 || iHeaderLen < (int)sizeof(unsigned int))
	{
		throw TarsDecodeException("packet length too long or too short,len:" + TC_Common::tostr(iHeaderLen));
	}

	//包没有接收全
	if (in.getBufferLength() < (uint32_t)iHeaderLen)
	{
		return TC_NetWorkBuffer::PACKET_LESS;
	}

	in.moveHeader(sizeof(iHeaderLen));

	tars::Int32 iRequestId = 0;
	string sRequestId;
	in.getHeader(sizeof(iRequestId), sRequestId);
	in.moveHeader(sizeof(iRequestId));

	rsp.iRequestId = ntohl(*((unsigned int *)(sRequestId.c_str())));
	len =  iHeaderLen - sizeof(iHeaderLen) - sizeof(iRequestId);
	in.getHeader(len, rsp.sBuffer);
	in.moveHeader(len);

    return TC_NetWorkBuffer::PACKET_FULL;
}
/*
   请求包编码函数，本函数的打包格式为
   整个包长度（字节）+iRequestId（字节）+包内容
*/
// static void pushRequest(const RequestPacket& request, string& buff)
// {
//     unsigned int net_bufflength = htonl(request.sBuffer.size()+8);
//     unsigned char * bufflengthptr = (unsigned char*)(&net_bufflength);

//     buff = "";
//     for (int i = 0; i<4; ++i)
//     {
//         buff += *bufflengthptr++;
//     }

//     unsigned int netrequestId = htonl(request.iRequestId);
//     unsigned char * netrequestIdptr = (unsigned char*)(&netrequestId);

//     for (int i = 0; i<4; ++i)
//     {
//         buff += *netrequestIdptr++;
//     }

//     string tmp;
//     tmp.assign((const char*)(&request.sBuffer[0]), request.sBuffer.size());
//     buff+=tmp;
// }
static vector<char> pushRequest(RequestPacket& request, Transceiver *)
{
    unsigned int net_bufflength = htonl(request.sBuffer.size()+8);
    unsigned char * bufflengthptr = (unsigned char*)(&net_bufflength);

	vector<char> buffer;
	buffer.resize(request.sBuffer.size()+8);

	memcpy(buffer.data(), bufflengthptr, sizeof(unsigned int));

    unsigned int netrequestId = htonl(request.iRequestId);
    unsigned char * netrequestIdptr = (unsigned char*)(&netrequestId);

	memcpy(buffer.data() + sizeof(unsigned int), netrequestIdptr, sizeof(unsigned int));
	memcpy(buffer.data() + sizeof(unsigned int) * 2, request.sBuffer.data(), request.sBuffer.size());

	return buffer;
	// sbuff->addBuffer(buffer);
}

struct PushTest : public ::testing::Test
{
    PushTest()
    {
        _comm = Application::getCommunicator();
    }
    void initPrx(const string& servantName)
    {
        prx = _comm->stringToProxy<ServantPrx>(servantName);

        ProxyProtocol prot;
        prot.requestFunc = pushRequest;
        prot.responseFunc = pushResponse;

        prx->tars_set_protocol(prot);
    }
    static bool isPushCallbackCalled;
protected:
    CommunicatorPtr _comm;
    ServantPrx  prx;
};
bool PushTest::isPushCallbackCalled = false;

class TestPushCallBack : public ServantProxyCallback
{
public:
    virtual int onDispatch(ReqMessagePtr msg)
    {
        if(msg->request.sFuncName == "printResult")
        {
            string sRet;
            sRet.assign(&(msg->response->sBuffer[0]), msg->response->sBuffer.size());

            // EXPECT_STREQ(sRet.c_str(), "heartbeat");
            return 0;
        }
        else if(msg->response->iRequestId == 0)
        {
            string sRet;
            sRet.assign(&(msg->response->sBuffer[0]), msg->response->sBuffer.size());
            EXPECT_STREQ(sRet.c_str(), "Push   Hello!");
            PushTest::isPushCallbackCalled = true;
            return 0;
        }
        EXPECT_TRUE(false);
        return -3;
    }
};
typedef tars::TC_AutoPtr<TestPushCallBack> TestPushCallBackPtr;

TEST_F(PushTest, given_push_call_back_when_connected_then_client_will_recieve_push_msg)
{
    initPrx(PUSH_SERVANT_ENDPOINT);

    TestPushCallBackPtr cbPush = new TestPushCallBack();
    prx->tars_set_push_callback(cbPush);

    string buf("heartbeat");
    TestPushCallBackPtr cb = new TestPushCallBack();
    prx->rpc_call_async(prx->tars_gen_requestid(), "printResult", buf.c_str(), buf.length(), cb);

    TC_Common::sleep(1);

    EXPECT_TRUE(isPushCallbackCalled);
}
