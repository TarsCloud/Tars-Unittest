#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"


#include "util/tc_thread.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace tars;
using namespace TarsTest;

class MyThread : public TC_Thread, public TC_ThreadLock
{
public:
    MyThread()
    {
        bTerminate = false;
    }
    /**
     * 结束线程
     */
    void terminate()
    {
        bTerminate = true;

        {
            TC_ThreadLock::Lock sync(*this);
            notifyAll();
        }
    }

    void doSomething()
    {
        cout << "doSomething" << endl;
    }
    /**
     * 运行
     */
protected:
    virtual void run() 
    {
        while(!bTerminate)
        {
             //TODO: your business
            doSomething();

            {
                TC_ThreadLock::Lock sync(*this);
                timedWait(1000);
            }
        }
    }

protected:
    bool bTerminate;
};

TEST(TarsUtilTestcase, UT_TC_Thread)
{
    MyThread mt;
    mt.start();

    sleep(5);

    mt.terminate();
    mt.getThreadControl().join();

}


