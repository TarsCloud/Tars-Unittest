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
#include "TarsTest/UnitTest/DyeingTest.h"
using namespace std;
using namespace tars;
using namespace TarsTest; 
#define DYEFILEPATH "/usr/local/app/tars/app_log/tars_dyeing/"
extern string getTime();
/****************************************************
被动染色测试，对接口调用进行染色。被动染色分为两步：
1.通过管理接口设置染色字段的key值
2.通过key值调用接口
校验染色文件是否存在
****************************************************/

struct DyeingTestCase : public ::testing::Test
{
	DyeingTestCase()
	{
		_comm = Application::getCommunicator();
	}
protected:
	CommunicatorPtr _comm;
};


//未打开染色开关的场景
TEST_F(DyeingTestCase, should_response_when_call_no_dyeing_cmd)
{ 
    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();
	
	DyeingTestPrx dyeingPrx= _comm->stringToProxy<DyeingTestPrx>(DYEING_SERVANT_ENDPOINT);
    string strIn="123456";
	string strOut;
	int ret=dyeingPrx->testDyeing(strIn,strOut);
	EXPECT_EQ(ret,0);

	TLOGDEBUG("no dyeing request time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
}
//打开染色开关，但未使用染色key调用的场景
TEST_F(DyeingTestCase, should_response_when_call_nodykey_cmd)
{
    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();
    
	AdminFPrx adminFPrx = _comm->stringToProxy<AdminFPrx>(UNIT_TEST_ADMIN_NAME_ENDPOINT);
	string setdyeing = adminFPrx->notify("tars.setdyeing 123456 TarsTest.UnitTest.DyeingTestObj testDyeing");
	EXPECT_TRUE(setdyeing.find("DyeingKey=123456") != string::npos);
	DyeingTestPrx dyeingPrx= _comm->stringToProxy<DyeingTestPrx>(DYEING_SERVANT_ENDPOINT);
    string strIn="abc";
	string strOut;
	int ret=dyeingPrx->testDyeing(strIn,strOut);
	TC_Common::sleep(1);
	EXPECT_EQ(ret,0);

	TLOGDEBUG("dyeing without key request time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
	
}
//打开染色开关，使用染色key调用的场景
TEST_F(DyeingTestCase, should_response_when_call_dyeing_cmd)
{
    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();
  
	AdminFPrx adminFPrx = _comm->stringToProxy<AdminFPrx>(UNIT_TEST_ADMIN_NAME_ENDPOINT);
	string setdyeing = adminFPrx->notify("tars.setdyeing 123456 TarsTest.UnitTest.DyeingTestObj testDyeing");
	EXPECT_TRUE(setdyeing.find("DyeingKey=123456") != string::npos);
	DyeingTestPrx dyeingPrx= _comm->stringToProxy<DyeingTestPrx>(DYEING_SERVANT_ENDPOINT);
    string strIn="123456";
	string strOut;
	int ret=dyeingPrx->testDyeing(strIn,strOut);
	TC_Common::sleep(1);
	EXPECT_EQ(ret,0);
	string dyeFile=DYEFILEPATH;
	dyeFile.append("dyeing");
	dyeFile.append("_");
	dyeFile.append(getTime());
	dyeFile.append(".log");
	EXPECT_EQ(TC_File::isFileExist(dyeFile), true);
	// int iRet=access(dyeFile.c_str(), F_OK);
	// EXPECT_EQ(iRet,0);
	
	TLOGDEBUG("dyeing with key request time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
	
}



