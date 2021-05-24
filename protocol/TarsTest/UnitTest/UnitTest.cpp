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

#include "util/tc_http.h"
#include "util/tc_network_buffer.h"
#include "UnitTest.h"
#include "TypeDemoImp.h"
#include "TupDemoImp.h"
#include "DyeingTestImp.h"
#include "TarsPingTestImp.h"
#include "AServantImp.h"
#include "BServantImp.h"
#include "TupProxyImp.h"
#include "ProxyImp.h"
using namespace std;

UnitTest g_app;


// struct TupProtocol
// {
//     /**
//      * 解析http请求
//      * @param in
//      * @param out
//      *
//      * @return int
//      */
//     static int parseHttp(string &in, vector<char> &out)
//     {
//         try
//         {
//                         //判断请求是否是HTTP请求
//             bool b = TC_HttpRequest ::checkRequest(in.c_str(), in.length());
//                         //完整的HTTP请求
//             if(b)
//             {
//                 out = in;
//                 in  = "";
// 				//cout<<"out size: " << out.size() << endl;
// 				//TLOGDEBUG("out size: " << out.size() << endl);
//                 return TC_NetWorkBuffer::PACKET_FULL;
//             }
//             else
//             {
//                 return TC_NetWorkBuffer::PACKET_LESS;
//             }
//         }
//         catch(exception &ex)
//         {
//             return TC_NetWorkBuffer::PACKET_ERR;
//         }

//         return TC_NetWorkBuffer::PACKET_LESS;             //表示收到的包不完全
//     }

// };

// struct NTarsProtocol
// {
//     /**
//      * 解析no tars请求
//      * @param in
//      * @param out
//      *
//      * @return int
//      */
//     static int parse(string &in, string &out)
//     {
        
//             out = in;
//             in  = "";
//             return 0;

//     }

// };

/////////////////////////////////////////////////////////////////
void
UnitTest::initialize()
{
    //initialize application here:
    //...
    addServant<TypeDemoImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".TypeDemoObj");
    addServant<TupDemoImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".TupDemoObj");
    addServant<DyeingTestImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".DyeingTestObj");
	addServant<TarsPingTestImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".TarsPingTestObj");
	addServant<AServantImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".AServantObj");
	addServant<AServantImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".AAServantObj");
	addServant<BServantImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".BServantObj");
	addServantProtocol(ServerConfig::Application + "." + ServerConfig::ServerName + ".AAServantObj", &TC_NetWorkBuffer::parseEcho);
	addServant<TupProxyImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".TupProxyObj");
	addServantProtocol(ServerConfig::Application + "." + ServerConfig::ServerName + ".TupProxyObj", &TC_NetWorkBuffer::parseHttp);
	addServant<ProxyImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".ProxyObj");
} 
/////////////////////////////////////////////////////////////////
void
UnitTest::destroyApp()
{
    //destroy application here:
    //...
}
/////////////////////////////////////////////////////////////////
int
main(int argc, char* argv[])
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
    return -1;
}
/////////////////////////////////////////////////////////////////
