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
#include "servant/Application.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"
#include "TarsTest/UnitTest/TarsPingTest.h"
using namespace std;
using namespace tars;
using namespace TarsTest; 

/****************************************************
Ping测试，测试主调和被调之间连接是否通
****************************************************/

struct PingTest : public ::testing::Test
{
	PingTest()
	{
		_comm = Application::getCommunicator();
	}
protected:
	CommunicatorPtr _comm;
};

TEST_F(PingTest, should_response_when_syncall_ping_cmd)
{
    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();  
    
	TarsPingTestPrx pPrx;
	int iRet=-1;
	try
	{
		
        pPrx=_comm->stringToProxy<TarsPingTestPrx>(PING_SERVANT_ENDPOINT);
        pPrx->tars_ping();
        iRet = 0;
    } 
    catch(exception &e)
    {
        cout<<e.what()<<endl;
    }
    catch(...)
    {
    }
	EXPECT_EQ(iRet,0);
	TLOGDEBUG("ping time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
}



