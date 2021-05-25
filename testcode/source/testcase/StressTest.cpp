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
#include "TarsTest/UnitTest/AServant.h"
#include "TarsServantName.h"
#include "servant/Application.h"
#include "servant/Communicator.h"
#include "util/tc_thread_pool.h"
#include <iostream>

using namespace std;
using namespace TarsTest;
using namespace tars;

/****************************************************
压力测试用例
利用TC_ThreadPool启用多个线程进行压力测试
****************************************************/

/**
* @brief 请求执行方法
* @param pprx
* @param excut_num
* @param size
*/
void dohandle(AServantPrx pprx,int excut_num,int size)
{
    string s(size,'a');
    for(int i=0; i<excut_num; i++) 
    {
        try
        {

           string ret="";
           pprx->tars_set_timeout(15000)->saySomething(s,ret);
        }
        catch(TC_Exception &e)
        {
            cout << "pthread id: " << std::this_thread::get_id() << "id: " << i << "exception: " << e.what() << endl;
        }
        catch(...)
        {
            cout << "pthread id: " << std::this_thread::get_id()<< "id: " << i << "unknown exception." << endl;
        }
    }
}

TEST(StressTest,stress_test_when_call_multi_times)
{
    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();
	
	CommunicatorPtr _comm=Application::getCommunicator();
	AServantPrx prx=_comm->stringToProxy<AServantPrx> (ASERVANT_ENDPOINT);
    try
    {
        tars::Int32  threads = 10;
        TC_ThreadPool tp;
        tp.init(threads);
        tp.start();    

        TLOGDEBUG("init tp succ" << endl);
		int times=10;
		int size=100;
        for(int i = 0; i<threads; i++) 
        {
            auto fw = std::bind(&dohandle, prx,times, size);
            tp.exec(fw);
            TLOGDEBUG("********************" <<endl);
        }

        tp.waitForAllDone(); 
    }
    catch(exception &e)
    {
        cout<<e.what()<<endl;
    }
    catch(...)
    {
        
    }

	TLOGDEBUG("StressTest time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
}

