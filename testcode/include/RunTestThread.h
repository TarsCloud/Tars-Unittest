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

#ifndef TARS_TAF_TEST_TESTCODE_INCLUDE_STUB_RUNTESTTHREAD_H_
#define TARS_TAF_TEST_TESTCODE_INCLUDE_STUB_RUNTESTTHREAD_H_
#include "gtest/gtest.h"
#include <iostream>
#include "TarsTest.h"
#include "util/tc_autoptr.h"
#include "util/tc_thread.h"
#include "utils/ServerAdmin.h"
#include "TarsServantName.h"
#include ""
TARSTEST_NS_START
USING_NS_TARS

extern TestcaseServer g_app;
class RunTestThread : public TC_Thread, public TC_HandleBase
{
    public:
     virtual void run()
     {
        try
        {
            g_app.main(argc, argv);
            g_app.waitForShutdown();
        }
        catch (std::exception& e)
        {
            cerr << "std::exception:" << e.what() << std::endl;
        }
        catch (...)
        {
            cerr << "unknown exception." << std::endl;
        }
     }
     void init(int argc, char* argv[])
    {
         this->argc = argc;
         this->argv = argv;

    }
private:
         int argc;
         char* argv[];

 
};
typedef TC_AutoPtr<RunTestThread> RunTestThreadPtr;


TARSTEST_NS_END

#endif /* TARS_TAF_TEST_TESTCODE_INCLUDE_STUB_RUNTESTTHREAD_H_ */
