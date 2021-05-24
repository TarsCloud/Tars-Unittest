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

#include "servant/Application.h"
#include "stub/MockProxyObjImp.h"

#include "stub/MockProxyObjCallback.h"

using namespace tars;
using namespace std;

namespace mockProxy
{

    vector<char> mockRequestFunc(RequestPacket& request, Transceiver *);
    TC_NetWorkBuffer::PACKET_TYPE mockResponseFunc(TC_NetWorkBuffer &in, ResponsePacket& done);

    // void mockRequestFunc(const RequestPacket& request, string& buff);
    // size_t mockResponseFunc(const char* recvBuffer, size_t length, list<ResponsePacket>& done);

    //////////////////////////////////////////////////////
    std::atomic<int> MockProxyObjImp::requestId = {0};

    static string outfill(const string& s, char c = ' ', int n = 29)
    {
        return (s + string(abs(n - (int)s.length()), c));
    }
    void MockProxyObjImp::initialize()
    {
        //initialize servant here:
        _sMockServerObjName =TC_Common::strto<string>(this->getApplication()->getConfig().get("/tars/mockproxy<mock-server-obj>", "MockProxy.MockServer.MockObj"));
        cout << outfill("mock-server-obj") << _sMockServerObjName << endl;
    }

    //////////////////////////////////////////////////////
    void MockProxyObjImp::destroy()
    {
        //destroy servant here:
        //...
    }

    int MockProxyObjImp::doResponse(ReqMessagePtr resp)
    {
        cout << "response" << endl;
        if (resp->callback->getType() == MOCK_PROXY_CALLBACK_TYPE)
        {
            MockProxyObjCallback* cb = dynamic_cast<MockProxyObjCallback*>(resp->callback.get());

            shared_ptr<ResponsePacket> response = resp->response;

            cb->doResponse(response);
        }

        return 0;
    }

    int MockProxyObjImp::doRequest(TarsCurrentPtr current, vector<char>& response)
    {
        try
        {
            current->setResponse(false);

            RequestPacket originalRequest;

            parseOriginalRequest(current, originalRequest);

            RequestPacket newRequest;

            replaceRequestId(originalRequest, newRequest);

            MockProxyObjCallbackPtr cb = new MockProxyObjCallback(this, current);

            cb->setRequestId(originalRequest.iRequestId);

            callMockServer(newRequest, cb);

        }
        catch (std::exception& e)
        {
            cerr << "MockProxyObjImp:: doRequest exception:" << e.what() << std::endl;
        }
        catch (...)
        {
            cerr << "MockProxyObjImp:: doRequest unknown exception." << std::endl;
        }

        return 0;
    }

    void MockProxyObjImp::parseOriginalRequest(const TarsCurrentPtr current, RequestPacket &requestPacket)
    {
        const vector<char>& request = current->getRequestBuffer();

        TarsInputStream<BufferReader> is;

        is.setBuffer(request.data(), request.size());

        requestPacket.readFrom(is);

        stringstream ss;
        requestPacket.displaySimple(ss);
        TLOGDEBUG("[MockProxy]Receive buffer size: "<< request.size() << ", request: " << ss.str() <<endl);
    }

    /**
     * 将原消息包的RequestId替换成新生产的RequestId，其他内容不变。
     */
    void MockProxyObjImp::replaceRequestId(const RequestPacket &oldRequest, RequestPacket &newRequest)
    {
        int newRequestId = ++requestId;

        TLOGINFO("[MockProxy]Create new request Id: "<< newRequestId <<endl);

        newRequest = oldRequest;

        newRequest.iRequestId = newRequestId;

        TarsOutputStream<BufferWriter> os;

        newRequest.writeTo(os);

        newRequest.sBuffer = os.getByteBuffer();
    }

    void MockProxyObjImp::callMockServer(const RequestPacket &requestPacket,  const ServantProxyCallbackPtr& cb)
    {
        MockServerObjPrx  mockServerPrx;

        mockServerPrx = Application::getCommunicator()->stringToProxy<MockServerObjPrx>(_sMockServerObjName);

        ProxyProtocol         mockProxyProtocol;
        mockProxyProtocol.requestFunc   = mockRequestFunc;
        mockProxyProtocol.responseFunc = mockResponseFunc;

        mockServerPrx->tars_set_protocol(mockProxyProtocol);

        string str(requestPacket.sBuffer.begin(), requestPacket.sBuffer.end());
        TLOGDEBUG("[MockProxy]callMockServer request buffer[" << requestPacket.sBuffer.size() << "]: "<< str <<endl);

        mockServerPrx ->rpc_call_async(requestPacket.iRequestId, requestPacket.sFuncName,
                                (const char*)(&requestPacket.sBuffer[0]), requestPacket.sBuffer.size(),    cb);
    }


    vector<char> mockRequestFunc(RequestPacket& request, Transceiver *)
    {
        vector<char> buff;

        Int32 iHeaderLen = htonl(sizeof(tars::Int32) + request.sBuffer.size());

        // buff.clear();

        buff.resize(sizeof(tars::Int32) + request.sBuffer.size());

        memcpy(buff.data(), (const char *)&iHeaderLen, sizeof(tars::Int32));

        memcpy(buff.data() + sizeof(tars::Int32) ,(const char*)&request.sBuffer[0], request.sBuffer.size());

        // buff.append((const char *)&iHeaderLen, sizeof(tars::Int32));

        // buff.append((const char*)&request.sBuffer[0], request.sBuffer.size());

        // TLOGINFO("[MockProxy]mockRequestFunc buff[" << buff.size() << "]: " << buff <<endl);

        return buff;
    }

    TC_NetWorkBuffer::PACKET_TYPE mockResponseFunc(TC_NetWorkBuffer &in, ResponsePacket& done)
    {
        return ProxyProtocol::tarsResponse(in, done);

    }

    // void mockRequestFunc(const RequestPacket& request, string& buff)
    // {
    //     Int32 iHeaderLen = htonl(sizeof(tars::Int32) + request.sBuffer.size());

    //     buff.clear();

    //     buff.reserve(sizeof(tars::Int32) + request.sBuffer.size());

    //     buff.append((const char*)&iHeaderLen, sizeof(tars::Int32));

    //     buff.append((const char*)&request.sBuffer[0], request.sBuffer.size());

    //     TLOGINFO("[MockProxy]mockRequestFunc buff[" << buff.size() << "]: " << buff <<endl);
    // }

    // size_t mockResponseFunc(const char* recvBuffer, size_t length, list<ResponsePacket>& done)
    // {
    //     return ProxyProtocol::tarsResponse(recvBuffer, length, done);
    // }
}
