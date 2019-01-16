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

#ifndef _TestcaseServer_H_
#define _TestcaseServer_H_

#include <iostream>
#include "servant/Application.h"
#include "util/tc_autoptr.h"
#include "util/tc_thread.h"

using namespace tars;

/**
 *
 **/
class TestcaseServer : public Application
{
public:
    /**
     *
     **/
    virtual ~TestcaseServer() {};

    /**
     *
     **/
    virtual void initialize();

    /**
     *
     **/
    virtual void destroyApp();

	
    bool cmdAdd(const string& command, const string& params, string& result);

	
    bool delTarsViewVersion(const string& command, const string& params, string& result);
};

extern TestcaseServer g_app;

class RunTestThread : public TC_Thread, public TC_HandleBase
{
	public:
	virtual void run();
	void init(int argc, char* argv[]);
private:
	int argc;
	char** argv;
};
typedef TC_AutoPtr<RunTestThread> RunTestThreadPtr;

extern "C" void RunTestCaseServer(int argc, char* argv[])
{
	RunTestThreadPtr thread = new RunTestThread();
	thread->init(argc, argv);
	thread->start();
}

////////////////////////////////////////////
#endif
