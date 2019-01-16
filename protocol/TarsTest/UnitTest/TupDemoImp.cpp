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

#include "TupDemoImp.h"
#include "servant/Application.h"

using namespace std;

//////////////////////////////////////////////////////
void TupDemoImp::initialize()
{
    //initialize servant here:
    //...
}

//////////////////////////////////////////////////////
void TupDemoImp::destroy()
{
    //destroy servant here:
    //...
}
tars::Int32 TupDemoImp::helloWord(const std::string & strIn,std::string &strOut,tars::TarsCurrentPtr current)
{
    strOut=strIn;
	return 2;
}
tars::Int32 TupDemoImp::aAddb(const TarsTest::AddInt & addData,TarsTest::Result &aAddbResult,tars::TarsCurrentPtr current)
{
    int res=addData.adda+addData.addb;
	aAddbResult.addResult=res;
	aAddbResult.strResult=addData.addStr;
	return 0;
}








