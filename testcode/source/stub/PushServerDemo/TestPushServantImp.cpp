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

#include "stub/TestPushServantImp.h"
#include "servant/Application.h"

using namespace std;

class PushUser
{
public:
    static map<string, TarsCurrentPtr> pushUser;
    static TC_ThreadMutex mapMutex;
};
map<string, TarsCurrentPtr> PushUser::pushUser;
TC_ThreadMutex PushUser::mapMutex;

//////////////////////////////////////////////////////
void TestPushServantImp::initialize()
{
    //initialize servant here:
    //...
}

//////////////////////////////////////////////////////
void TestPushServantImp::destroy()
{
    //destroy servant here:
    //...
}

void TestPushServantImp::setPushInfo(const string &sInfo, string& pushInfo)
{
    unsigned int iBuffLength = htonl(sInfo.size()+8);
    unsigned char * pBuff = (unsigned char*)(&iBuffLength);

    pushInfo = "";
    for (int i = 0; i<4; ++i)
    {
        pushInfo += *pBuff++;
    }

    unsigned int iRequestId = htonl(0);
    unsigned char * pRequestId = (unsigned char*)(&iRequestId);

    for (int i = 0; i<4; ++i)
    {
        pushInfo += *pRequestId++;
    }

    pushInfo += sInfo;
}

void TestPushServantImp::push(const string& sInfo)
{
    string pushInfo;
    setPushInfo(sInfo, pushInfo);
    for(map<string, TarsCurrentPtr>::iterator it = (PushUser::pushUser).begin(); it != (PushUser::pushUser).end(); ++it)
    {
        (it->second)->sendResponse(pushInfo.c_str(), pushInfo.size());
        LOG->debug() << "sendResponse: " << pushInfo.size() <<endl;
    }
}

int TestPushServantImp::doRequest(tars::TarsCurrentPtr current, vector<char>& response)
{
    //保存客户端的信息，以便对客户端进行push消息

    /*map<string, TarsCurrentPtr>::iterator it = PushUser::pushUser.find(current->getIp());
    if(it == PushUser::pushUser.end())
    {
        (PushUser::mapMutex).lock();
        PushUser::pushUser.insert(map<string, TarsCurrentPtr>::value_type(current->getIp(), current));
        (PushUser::mapMutex).unlock();
        LOG->debug() << "connect ip: " << current->getIp() << endl;
    }
    push("Push  Hello!");*/
    string pushInfo;
    setPushInfo("Push   Hello!", pushInfo);
    current->sendResponse(pushInfo.c_str(), pushInfo.size());
    //返回给客户端它自己请求的数据包，即原包返回
    const vector<char>& request = current->getRequestBuffer();
    response = request;

    return 0;
}
//客户端关闭到服务端的连接，或者服务端发现客户端长时间未发送包过来，然后超过60s就关闭连接
//调用的方法
int TestPushServantImp::doClose(TarsCurrentPtr current)
{
    /*(PushUser::mapMutex).lock();
    map<string, TarsCurrentPtr>::iterator it = PushUser::pushUser.find(current->getIp());
    if(it != PushUser::pushUser.end())
    {
        PushUser::pushUser.erase(it);
        LOG->debug() << "close ip: " << current->getIp() << endl;
    }
    (PushUser::mapMutex).unlock();*/

    return 0;
}


