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
#include "TarsTest.h"
#include "util/tc_thread.h"
#include "utils/ServerAdmin.h"
#include "servant/Application.h"

#include "TarsServantName.h"
#include "servant/AdminF.h"

USING_NS_TARS
USING_NS_TARSTEST

extern "C" void RunTestCaseServer(int argc, char* argv[]);

/////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    RunTestCaseServer(argc, argv);
    TC_Common::sleep(2);
    testing::GTEST_FLAG(output)="xml:./../../../taf_result.xml";
    testing::GTEST_FLAG(filter)="**";

    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    TC_Common::sleep(2);
    ServerAdmin().shutdown(STAT_SERVER_ADMIN_NAME_ENDPOINT);
    ServerAdmin().shutdown(LOG_SERVER_ADMIN_NAME_ENDPOINT);
    ServerAdmin().shutdown(UNIT_TEST_ADMIN_NAME_ENDPOINT)
                 .shutdown(TEST_CASE_ADMIN_NAME_ENDPOINT);
                 
    TC_Common::sleep(2);

    return 0;
}



