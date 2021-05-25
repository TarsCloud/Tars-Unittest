/**
 * Tencent is pleased to support the open source community by making Tars available.
 *
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.
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
#include "AdminReg.h"
#include "servant/Application.h"
#include "servant/Communicator.h"
#include <iostream>

using namespace std;
using namespace tars;


class Test1
{
public:
    Test1(const string &sStr);
    ~Test1();
    void  th_dohandle(int excut_num);
private:
    CommunicatorPtr _comm;
    AdminRegPrx  _prx;
};

Test1::Test1(const string &sStr)
{
    _comm = Application::getCommunicator();
    _prx = _comm->stringToProxy<AdminRegPrx>("tars.tarsAdminRegistry.AdminRegObj@tcp -h 10.208.139.242 -p 12000 -t 60000");
}

Test1::~Test1()
{
    
}

void Test1::th_dohandle(int excut_num)
{
    for(int i=0; i<excut_num; i++) 
    {
        try
        {
            string application("tars");
            string serverName("tarsconfig");
            string nodeName("10.208.139.242");

            ServerStateDesc state;
            string result;

            int iRet = _prx->tars_set_timeout(15000)->getServerState(application, serverName, nodeName, state, result);
            EXPECT_TRUE(iRet == 0) << "tars get tarsconfig ServerState fail" << endl;
        }
        catch(TC_Exception &e)
        {
            EXPECT_TRUE(false) << "pthread id: " << std::this_thread::get_id() << "id: " << i << "exception: " << e.what() << endl;
        }
        catch(...)
        {
            EXPECT_TRUE(false) << "pthread id: " << std::this_thread::get_id() << "id: " << i << "unknown exception." << endl;
        }
    }
}

TEST(TarsFramework, AdminRegistry)
{
    string s = "sObj";
    Test1 test1(s);    
    try
    {

        tars::Int32 times = TC_Common::strto<tars::Int32>(s);

        test1.th_dohandle(times);

    }
    catch(exception &e)
    {
        EXPECT_TRUE(false)<<e.what()<<endl;
    }
    catch(...)
    {
        
    }

}

