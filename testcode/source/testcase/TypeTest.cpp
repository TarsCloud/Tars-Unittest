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

#include <iostream>
#include <cstdlib>
// #include <unistd.h>
#include <vector>
#include <map>
#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/UnitTest/TypeDemo.h"
#include "TarsServantName.h"

#include "servant/AdminF.h"

using namespace std;
using namespace tars;
using namespace TarsTest;

/****************************************************
数据类型测试，主要针对tars的编解码进行测试
包括简单类型、复杂类型和复合类型
****************************************************/

class TypeDemoObjCallback: public TypeDemoPrxCallback
{
public:
    virtual ~TypeDemoObjCallback(){}
    virtual void callback_echoBool(tars :: Int32 ret, tars :: Bool bEcho)
    {
        TLOGDEBUG("async echoBool success!ret="<<ret);
        EXPECT_EQ(ret, 0);
    }
    
    virtual void callback_echoBool_exception(tars::Int32 ret)
    { 
        TLOGDEBUG("async echoBool exception!"<< endl);
    }
    virtual void callback_echoInt(tars::Int32 ret, tars::Int32 iEcho)
    {
        TLOGDEBUG("async echoInt success!ret="<<ret);
        EXPECT_EQ(ret, 0);
    }
    
    virtual void callback_echoInt_exception(tars::Int32 ret)
    { 
        TLOGDEBUG("async echoInt exception!"<< endl);
    }
    virtual void callback_test(Int32 ret)
    {
        TLOGDEBUG("async test success!ret="<<ret);
        EXPECT_EQ(ret, 0);
    }
    virtual void callback_test_exception(Int32 ret)
    {
        TLOGDEBUG("async test exception!"<< endl);
    }
};
typedef tars::TC_AutoPtr<TypeDemoObjCallback> TypeDemoObjCallbackPtr;

struct TypeTest : public ::testing::Test 
{
    TypeTest()
    {
        _comm = Application::getCommunicator();
    }
protected:
    CommunicatorPtr _comm;
};

TEST_F(TypeTest, test_type_when_client_sync_call_server_by_ip)
{

    int64_t tBegin = TC_TimeProvider::getInstance()->getNowMs();
	
    TypeDemoPrx prx;
	prx = _comm->stringToProxy<TypeDemoPrx> (TYPT_TEST_ENDPOINT);

    int iRsp;
    int res = prx->echoInt(1,iRsp);
    EXPECT_EQ(res, 0);
    EXPECT_EQ(iRsp, 1);
    
    bool bReq=true;
    bool bRsp=false;
    res = prx->echoBool(bReq,bRsp);
    EXPECT_EQ(res, 0);
    EXPECT_TRUE(bRsp);
    
    char btReq=1;
    char btRsp;
    res = prx->echoByte(btReq,btRsp);
    EXPECT_EQ(res, 0);

    short stReq=1;
    short stRsp;
    res = prx->echoShort(stReq,stRsp);
    EXPECT_EQ(res, 0);

    tars::Int64  lReq=1;
    tars::Int64  lRsp;
    res = prx->echoLong(lReq,lRsp);
    EXPECT_EQ(res, 0);

    string strReq="tarstest";
    string strRsp;
    res = prx->echoString(strReq,strRsp);
    EXPECT_EQ(res, 0);
    EXPECT_STREQ(strRsp.c_str(), "tarstest");

    vector<int> vReq;
    vector<int> vRsp;
    vReq.push_back(1);
	vReq.push_back(2);
	vReq.push_back(3);
	res=prx->echoVector(vReq,vRsp);
    EXPECT_EQ(res, 0);

    map<int,string> mReq;
    map<int,string> mRsp;
    mReq[0]="tarstest0";
	mReq[1]="tarstest1";
	mReq[2]="tarstest2";
    res=prx->echoMap(mReq,mReq);
    EXPECT_EQ(res, 0);


    vector<map<int,string>> mtReq;
    vector<map<int,string>> mtRsp;
    map<int,string> aReq;
	map<int,string> bbReq;
	mtReq.push_back(mReq);
	mtReq.push_back(aReq);
	mtReq.push_back(bbReq);
	mReq[0]="tarstest";
    res=prx->echoMultiType(mtReq,mtReq);
    EXPECT_EQ(res, 0);

	TLOGDEBUG("type test time cost: "<< " | " << TC_TimeProvider::getInstance()->getNowMs() - tBegin << "(ms)" << endl);
}



