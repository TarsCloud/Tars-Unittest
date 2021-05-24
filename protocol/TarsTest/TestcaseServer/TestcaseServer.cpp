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

#include "util/tc_network_buffer.h"
#include "TestcaseServer.h"
#include "HttpDemoImp.h"
#include "RPCTestImp.h"
#include "stub/MockProxyObjImp.h"
#include "stub/TestPushServantImp.h"
#include "stub/ConfigImp.h"
#include "stub/QueryImp.h"
#include "OneWayRpcTestImp.h"
#include "servant/NotifyObserver.h"
//#include "DyeingTestImp.h"
#include "EpsTestImp.h"


using namespace std;
using namespace mockProxy;

TestcaseServer g_app;
// struct PushProtocol
// {
// 	static int parse(string &in, string &out)
// 	{
// 		if(in.length() < sizeof(unsigned int))
// 		{
// 			return TC_NetWorkBuffer::PACKET_LESS;
// 		}

// 		unsigned int iHeaderLen;

// 		memcpy(&iHeaderLen, in.c_str(), sizeof(unsigned int));

// 		iHeaderLen = ntohl(iHeaderLen);

// 		if(iHeaderLen < (unsigned int)(sizeof(unsigned int))|| iHeaderLen > 1000000)
// 		{
// 			return TC_NetWorkBuffer::PACKET_ERR;
// 		}

// 		if((unsigned int)in.length() < iHeaderLen)
// 		{
// 			return TC_NetWorkBuffer::PACKET_LESS;
// 		}

// 		out = in.substr(0, iHeaderLen);

// 		in  = in.substr(iHeaderLen);

// 		return TC_NetWorkBuffer::PACKET_FULL;
// 	}
// };

// struct HttpProtocol
// {
//     /**
//      * 解析http请求
//      * @param in
//      * @param out
//      *
//      * @return int
//      */
//     static int parseHttp(string &in, string &out)
//     {
//         try
//         {
//             //判断请求是否是HTTP请求
//             bool b = TC_HttpRequest ::checkRequest(in.c_str(), in.length());
//             //完整的HTTP请求
//             if(b)
//             {
//                 out = in;
//                 in  = "";
//                 //TLOGDEBUG("out size: " << out.size() << endl);
//                 return TC_EpollServer::PACKET_FULL;
//             }
//             else
//             {
//                 return TC_EpollServer::PACKET_LESS;
//             }
//         }
//         catch(exception &ex)
//         {
//             return TC_EpollServer::PACKET_ERR;
//         }

//         return TC_EpollServer::PACKET_LESS;             //表示收到的包不完全
//     }

// };

// struct MockProtocol
// {
// 	static int parse(string &in, string &out)
// 	{
// 	    return AppProtocol::parse(in,out);
// 	}
// };


/////////////////////////////////////////////////////////////////
void
TestcaseServer::initialize()
{
    //initialize application here:
    //...
//    addServant<QueryImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".QueryObj");

    addServant<HttpDemoImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".HttpDemoObj");
	addServantProtocol(ServerConfig::Application + "." + ServerConfig::ServerName + ".HttpDemoObj", &TC_NetWorkBuffer::parseHttp);

	addServant<MockProxyObjImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".MockProxyObj");
	addServantProtocol(ServerConfig::Application + "." + ServerConfig::ServerName + ".MockProxyObj", &AppProtocol::parse);

	addServant<RPCTestImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".RPCTestObj");
	addServant<RPCTestImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".UdpRPCObj");

	addServant<TestPushServantImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".PushObj");
    addServantProtocol(ServerConfig::Application + "." + ServerConfig::ServerName + ".PushObj", &AppProtocol::parse);

    addServant<ConfigImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".ConfigObj");
    addServant<QueryImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".QueryObj");
     
	
    addServant<OneWayRpcTestImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".OneWayRpcObj");

	addServant<EpsTestImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".EpsTestObj");

	//addServant<DyeingTestImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".DyeingTestObj");

    TARS_ADD_ADMIN_CMD_NORMAL("AdminCmdNormalTest", TestcaseServer::cmdAdd);

    TARS_ADD_ADMIN_CMD_NORMAL("CmdToDelete", TestcaseServer::cmdAdd);

    getNotifyObserver()->unregisterNotify("CmdToDelete", this);

    TARS_ADD_ADMIN_CMD_NORMAL("DeletePrefixCmd", TestcaseServer::delTarsViewVersion);
	
}
/////////////////////////////////////////////////////////////////

bool TestcaseServer::cmdAdd(const string& command, const string& params, string& result)
{
	result = params + " AdminCmdNormalTest success!";
	return true;
}

bool TestcaseServer::delTarsViewVersion(const string& command, const string& params, string& result)
{
	getNotifyObserver()->unregisterPrefix("tars.viewversion", this);
	
	result = "Delete success!";
	return true;
}


void
TestcaseServer::destroyApp()
{
    //destroy application here:
    //...
}

void RunTestThread::run()
{
	try
	{
		g_app.main(argc, argv);
		g_app.waitForShutdown();
	}
	catch (std::exception& e)
	{
		cerr << "std::exception:" << e.what() << std::endl;
	}
	catch (...)
	{
		cerr << "unknown exception." << std::endl;
	}

}

void RunTestThread::init(int argc, char* argv[])
{
	this->argc = argc;
	this->argv = argv;

}

typedef TC_AutoPtr<RunTestThread> RunTestThreadPtr;

/////////////////////////////////////////////////////////////////
