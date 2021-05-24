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
// #include "util/tc_bind.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "TarsServantName.h"


USING_NS_STD
USING_NS_TARS
using namespace TarsTest;

struct PropertyReportTest : public ::testing::Test
{
    PropertyReportTest()
    {
        _comm = Application::getCommunicator();
    }
protected:
    CommunicatorPtr _comm;
};

TEST_F(PropertyReportTest, should_report_property)
{
    _comm->setProperty("property", "TarsTest.TestcaseServer.PropertyObj@ tcp -h 127.0.0.1 -p 4444");
    //初始化分布数据范围
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(50);
    v.push_back(80);
    v.push_back(100);

    PropertyReportPtr srp = _comm->getStatReport()->createPropertyReport("PropertyReportTest", 
    PropertyReport::sum(), //求和 
    PropertyReport::avg(), 
    PropertyReport::count(),
    PropertyReport::max(), 
    PropertyReport::min(),
    PropertyReport::distr(v));

    for ( int is = 0; is < 10; is++ )
    {
        srp->report(rand() % 10);
    }

    vector<pair<string, string> > vs = srp->get();

    EXPECT_TRUE(vs.size() != 0);
    
}

