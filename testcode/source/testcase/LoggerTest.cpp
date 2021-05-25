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
#include <time.h>
#include "servant/Application.h"
#include "servant/TarsLogger.h"
#include <iostream>
using namespace tars;
#define FILEPATH "/usr/local/app/tars/app_log/TarsTest/TestcaseServer/TarsTest.TestcaseServer"


/****************************************************
Logger测试，包括测试日志等级和独立日志打印
1.改变本地日志等级，打印不同日志等级的日志
2.打印日志到不同的文件
3.校验日志文件是否存在
****************************************************/

/**
* @brief 获取当前日期
* @return int(返回码，0是成功，-3为超时)
*/

string getTime()
{
	time_t timep;
    time (&timep);     
	char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y%m%d",localtime(&timep) );
    return tmp;
}

/**
* @brief 打印日志
*/

int logger()
{
    int i = 10;
	int64_t t = TC_Common::now2ms();
	while(i)
	{

        LOG->info() << i << ":" << t << endl;
		LOG->debug() << i << ":" << t << endl;
		LOG->error() << i << ":" << t << endl;

  		FDLOG("abc1") << i << ":" << t << endl;
  		FDLOG("abc2") << i << ":" << t << endl;
  		FDLOG("abc3") << i << ":" << t << endl;
        i--;
	}
	string strTime=getTime();
	return i;
	
}

//日志打印测试
TEST(LoggerTest, should_response_when_call_logger)
{
    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();
	
    try
    {
        string strTime=getTime();
		string logFile=FILEPATH;
		logFile.append("_");
		logFile.append("abc1");
		logFile.append("_");
		logFile.append(strTime);
		logFile.append(".log");
		int iRet=logger();
		EXPECT_EQ(iRet, 0);

	    TC_Common::sleep(1);	
		EXPECT_EQ(TC_File::isFileExist(logFile), true);
                // int iRes=access(logFile.c_str(), F_OK);
		
		// EXPECT_EQ(iRes, 0);
		
	}
	catch(exception &ex)
	{
       TLOGDEBUG(ex.what() << endl);
	}

    TLOGDEBUG("LoggerTest time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
}


