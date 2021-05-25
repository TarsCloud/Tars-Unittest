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
#include "util/tc_file.h"
#include "util/tc_option.h"
#include "servant/TarsLogger.h"
#include "servant/Application.h"
#include "gtest/gtest.h"
#include "TarsServantName.h"
#include "TarsTest/UnitTest/DyeingTest.h"
using namespace std;
using namespace tars;
using namespace TarsTest;
#define DYEFILEPATH "/usr/local/app/tars/app_log/tars_dyeing/"
extern string getTime();
/****************************************************
主动染色测试，染色开关作用域内日志额外打印到染色日志
校验染色文件是否存在
****************************************************/

TEST(ActiveDyeTest, should_response_when_call_active_dyeing)
{
    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();
    try
    {
		CommunicatorPtr comm = new Communicator();
		DyeingTestPrx dyeingPrx= comm->stringToProxy<DyeingTestPrx>(DYEING_SERVANT_ENDPOINT);
		LOG->debug() << __FILE__ << "|" << __LINE__ << "|CLIENT:noDyeing" << endl;
		DLOG << __FILE__ << "|" << __LINE__ << "|CLIENT:noDyeing" << endl;
		FDLOG("T_D") << __FILE__ << "|" << __LINE__ << "|CLIENT:noDyeing" << endl;
	    {

			TarsDyeingSwitch dye;
			dye.enableDyeing();
			LOG->debug() << __FILE__ << "|" << __LINE__ << "|CLIENT:Dyeing" << endl;
			DLOG << __FILE__ << "|" << __LINE__ << "|CLIENT:Dyeing" << endl;
			FDLOG("T_D") << __FILE__ << "|" << __LINE__ << "|CLIENT:Dyeing" << endl;
		    std::string s("123456");
			std::string ret ;
			int iRet = dyeingPrx->testDyeing(s, ret);
            EXPECT_EQ(iRet,0);
			LOG->debug() << __FILE__ << "|" << __LINE__ << "|CLIENT:Dyed"  << endl;
			DLOG << __FILE__ << "|" << __LINE__ << "|CLIENT:Dyed" << endl;
			FDLOG("T_D") << __FILE__ << "|" << __LINE__ << "|CLIENT:Dyed" << endl;
		}
		LOG->debug() << __FILE__ << "|" << __LINE__ << "|CLIENT:afterDye" << endl;
		DLOG << __FILE__ << "|" << __LINE__ << "|CLIENT:afterDye" << endl;
		FDLOG("T_D") << __FILE__ << "|" << __LINE__ << "|CLIENT:afterDye" << endl;
		string dyeFile=DYEFILEPATH;
		dyeFile.append("dyeing");
		dyeFile.append("_");
		dyeFile.append(getTime());
		dyeFile.append(".log");
        TC_Common::sleep(1);
		EXPECT_EQ(TC_File::isFileExist(dyeFile), true);
		// int iRet=access(dyeFile.c_str(), F_OK);
		// EXPECT_EQ(iRet,0);
		
	}
    catch (std::exception & e)
    {
        TLOGDEBUG("exception:" << e.what() << endl);
		
		
    }
	catch (...)
	{
		TLOGDEBUG("exception:..." << endl);	
	}

	TC_Common::sleep(1);	//等待异步写日志线程同步日志数据到tarlog
	
	TLOGDEBUG("Active dyeing time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
	
}
