/**
 * Tencent is pleased to support the open source community by making Tars available.
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

USING_NS_STD
USING_NS_TARS
/****************************************************
管理接口测试，校验返回字符串
****************************************************/
TEST(AdminTest, should_response_when_call_admin_cmd)
{
    CommunicatorPtr c = Application::getCommunicator();

    AdminFPrx adminFPrx = c->stringToProxy<AdminFPrx>(TEST_CASE_ADMIN_NAME_ENDPOINT);

    string loadconfig = adminFPrx->notify("tars.loadconfig TarsTest.TestcaseServer.config.conf");
    EXPECT_TRUE(loadconfig.find("[succ] get remote config:") != string::npos);
    loadconfig = adminFPrx->notify("tars.loadconfig TarsTest.TestcaseServer.notExist.conf");
    EXPECT_TRUE(loadconfig.find("[fail] get remote config ") != string::npos);

    string setloglevel = adminFPrx->notify("tars.setloglevel DEBUG");
    EXPECT_TRUE(setloglevel.find("set log level [DEBUG] ok") != string::npos);

    string viewstatus = adminFPrx->notify("tars.viewstatus");
    EXPECT_TRUE(viewstatus.find("notify prefix object num:1") != string::npos);

    // string viewversion = adminFPrx->notify("tars.viewversion");
    // EXPECT_TRUE(viewversion.find("$1.1.0$") != string::npos);

    string connection = adminFPrx->notify("tars.connection");
    EXPECT_TRUE(connection.find("[adater:AdminAdapter] [connections:1]") != string::npos);
  
    string loadproperty = adminFPrx->notify("tars.loadproperty");
    EXPECT_TRUE(loadproperty.find("loaded config items:") != string::npos);
     
    string help = adminFPrx->notify("tars.help");
    EXPECT_TRUE(help.find("tars.closecore") != string::npos);

    string closecout = adminFPrx->notify("tars.closecout NO");
    cout << closecout << endl;

    string enabledaylog = adminFPrx->notify("tars.enabledaylog local|daylog|true");
    EXPECT_TRUE(enabledaylog.find("set local daylog true ok") != string::npos);
    enabledaylog = adminFPrx->notify("tars.enabledaylog remote|false");
    EXPECT_TRUE(enabledaylog.find("set remote false ok") != string::npos);

    string reloadlocator = adminFPrx->notify("tars.reloadlocator reload");
    EXPECT_TRUE(reloadlocator.find("[notify prefix object num:1]") != string::npos);

    // string closecore = adminFPrx->notify("tars.closecore no");
    // EXPECT_TRUE(closecore.find("after set cur:18446744073709551615;max: 18446744073709551615") != string::npos);
    // closecore = adminFPrx->notify("tars.closecore yes");
    // EXPECT_TRUE(closecore.find("after set cur:0;max: 18446744073709551615") != string::npos);

    string errorcmd = adminFPrx->notify("tars.errorcmd");
    EXPECT_STREQ(errorcmd.c_str(), "");

    string normalcmd = adminFPrx->notify("AdminCmdNormalTest returnMark");
    EXPECT_STREQ(normalcmd.c_str(), "[notify servant object num:1]\n[1]:returnMark AdminCmdNormalTest success!\n");

    string normaldeletecmd = adminFPrx->notify("DeletePrefixCmd");
    EXPECT_STREQ(normaldeletecmd.c_str(), "[notify servant object num:1]\n[1]:Delete success!\n");

    // viewversion = adminFPrx->notify("tars.viewversion");
    // EXPECT_STREQ(viewversion.c_str(), "");
}
