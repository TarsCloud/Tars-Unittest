#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"



#include "util/tc_mem_queue.h"
#include "util/tc_sem_mutex.h"
#include "util/tc_shm.h"
#include "util/tc_thread_pool.h"
#include "util/tc_common.h"
#include "util/tc_functor.h"
#include <sstream>
#include <iostream>

using namespace std;
using namespace tars;
using namespace TarsTest;

TC_Shm shm;
TC_SemMutex  semLock;
TC_MemQueue  memQueue;

/**
 * 线程调用过程
 * @param s
 * @param i
 */
void writeQueue()
{
    int i = 10000;
    while(i)
    {
        TC_LockT<TC_SemMutex> l(semLock);
        if(memQueue.push_back(TC_Common::tostr(i)))
        {
            cout << pthread_self() << " | writeQueue OK " << i << ":" << memQueue.elementCount() << endl;
            i--;
        }
        else
        {
            cout << pthread_self() << " | writeQueue FULL " << i << endl;
            return;
        }
    }
}

void readQueue()
{
    while(true)
    {
        string s;
        TC_LockT<TC_SemMutex> l(semLock);
        if(memQueue.pop_front(s))
        {
            cout << pthread_self() << " | readQueue OK " << s << endl;
        }
        else
        {
            cout << pthread_self() << " | readQueue EMPTY" << endl;
            // sleep(1);
            return;
        }
    }
}

TEST(TarsUtilTestcase, UT_TC_MemQueue)
{

    size_t l = 1024000;
    shm.init(l, 8000);
    semLock.init(8000);

    if(shm.iscreate())
    {
        memQueue.create(shm.getPointer(), l);
    }
    else
    {
        memQueue.connect(shm.getPointer(), l);
    }

    
    {
        TC_ThreadPool twpool;
        twpool.init(4);
        twpool.start();

        TC_Functor<void> w(writeQueue);
        TC_Functor<void>::wrapper_type iwt(w);
        for(size_t i = 0; i < twpool.getThreadNum(); i++)
        {
            twpool.exec(iwt);
        }

        twpool.waitForAllDone();
    }

    {
        TC_ThreadPool trpool;
        trpool.init(4);
        trpool.start();

        TC_Functor<void> r(readQueue);
        TC_Functor<void>::wrapper_type irt(r);

        for(size_t i = 0; i < trpool.getThreadNum(); i++)
        {
            trpool.exec(irt);
        }

        trpool.waitForAllDone();
    }

}


