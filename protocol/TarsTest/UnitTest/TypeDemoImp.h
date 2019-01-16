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

#ifndef _TypeDemoImp_H_
#define _TypeDemoImp_H_

#include "servant/Application.h"
#include "TypeDemo.h"

/**
 *
 *
 */
class TypeDemoImp : public TarsTest::TypeDemo
{
public:
    /**
     *
     */
    virtual ~TypeDemoImp() {}

    /**
     *
     */
    virtual void initialize();

    /**
     *
     */
    virtual void destroy();

    /**
     *
     */
    virtual int test(tars::TarsCurrentPtr current) { return 0;};
	virtual tars::Int32 echoInt(tars::Int32 iInput,tars::Int32 &iEcho,tars::TarsCurrentPtr current);
	virtual tars::Int32 echoBool(tars::Bool bInput,tars::Bool &bEcho,tars::TarsCurrentPtr current);
	virtual tars::Int32 echoByte(tars::Char bInput,tars::Char &bEcho,tars::TarsCurrentPtr current);
	virtual tars::Int32 echoShort(tars::Short sInput,tars::Short &sEcho,tars::TarsCurrentPtr current);
	virtual tars::Int32 echoLong(tars::Int64 lInput,tars::Int64 &lEcho,tars::TarsCurrentPtr current) ;
	virtual tars::Int32 echoString(const std::string & strInput,std::string & strEcho,tars::TarsCurrentPtr current);
	virtual tars::Int32 echoVector(const vector<tars::Int32> & vInput,vector<tars::Int32> & vEcho,tars::TarsCurrentPtr current);
	virtual tars::Int32 echoMap(const map<tars::Int32, std::string> & mInput,map<tars::Int32, std::string> &mEcho,tars::TarsCurrentPtr current);
	virtual tars::Int32 echoMultiType(const vector<map<tars::Int32, std::string> > & mtInput,vector<map<tars::Int32, std::string> > &mtEcho,tars::TarsCurrentPtr current);
	//virtual tars::Int32 queryForTafPlus(const TarsTest::ReqInfo & req,vector<TarsTest::RspInfo> &vRsp,tars::TarsCurrentPtr current);
};
/////////////////////////////////////////////////////
#endif
