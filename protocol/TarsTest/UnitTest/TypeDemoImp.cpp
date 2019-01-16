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

#include "TypeDemoImp.h"
#include "servant/Application.h"

using namespace std;

//////////////////////////////////////////////////////
void TypeDemoImp::initialize()
{
    //initialize servant here:
    //...
}

//////////////////////////////////////////////////////
void TypeDemoImp::destroy()
{
    //destroy servant here:
    //...
}
tars::Int32 TypeDemoImp::echoInt(tars::Int32 iInput,tars::Int32 &iEcho,tars::TarsCurrentPtr current)
{
   iEcho=iInput;
   return 0;
};
tars::Int32 TypeDemoImp::echoBool(tars::Bool bInput,tars::Bool &bEcho,tars::TarsCurrentPtr current)
{
   bEcho=bInput;
   return 0;
}
tars::Int32 TypeDemoImp::echoByte(tars::Char bInput,tars::Char &bEcho,tars::TarsCurrentPtr current)
{
   bEcho=bInput;
   return 0;
}
tars::Int32 TypeDemoImp::echoShort(tars::Short sInput,tars::Short &sEcho,tars::TarsCurrentPtr current)
{
	sEcho=sInput;
	return 0;

}
tars::Int32 TypeDemoImp::echoLong(tars::Int64 lInput,tars::Int64 &lEcho,tars::TarsCurrentPtr current)
{	
    lEcho=lInput;
	return 0;

}
tars::Int32 TypeDemoImp::echoString(const std::string & strInput, std::string & strEcho,tars::TarsCurrentPtr current)
{
	string tmp=strInput;
	strEcho=tmp;
	return 0;

}
tars::Int32 TypeDemoImp::echoVector(const vector<tars::Int32> & vInput,vector<tars::Int32> & vEcho,tars::TarsCurrentPtr current)
{
    vEcho.assign(vInput.begin(),vInput.end());
    return 0;
}
tars::Int32 TypeDemoImp::echoMap(const map<tars::Int32, std::string> & mInput,map<tars::Int32, std::string> &mEcho,tars::TarsCurrentPtr current)
{
    mEcho=mInput;
	return 0;
}
tars::Int32 TypeDemoImp::echoMultiType(const vector<map<tars::Int32, std::string> > & mtInput,vector<map<tars::Int32, std::string> > &mtEcho,tars::TarsCurrentPtr current)
{
    mtEcho=mtInput;
	return 0;
}

//tars::Int32 TypeDemoImp::queryForTafPlus(const TarsTest::ReqInfo & req,vector<TarsTest::RspInfo> &vRsp,tars::TarsCurrentPtr current)
//{
//    return 0;
//}





