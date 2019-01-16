#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"


#include "util/tc_monitor.h"
#include "util/tc_common.h"
#include <iostream>

using namespace std;
using namespace tars;
using namespace TarsTest;

TC_ThreadLock mutex;

template<typename T>
class TestLock : public T
{
public:
    TestLock()
    {
        i = 0;
    }

    void out()
    {
        typename T::Lock lock(*this);
        ++i;
        cout << pthread_self() << ":" << i << endl;
        sleep(1);
        cout << pthread_self() << ":" << i << endl;
    }

    void testLock(int i)
    {
        long long n = TC_Common::now2us();
        while(i)
        {
            typename T::Lock lock(*this);
            --i;
        }
        cout << (TC_Common::now2us() - n)/1000. << endl;
    }
protected:
    int i;
};

//TestLock<TC_ThreadLock> tl;
TestLock<TC_ThreadRecLock> tl;

void ThreadEntry1(void *)
{
    int i=100;
    while(i-- > 0)
        tl.out();
}

void ThreadEntry2(void *)
{
    int i=100;
    while(i-- > 0)
        tl.out();
}

TEST(TarsUtilTestcase, UT_TC_ThreadLock)
{
    int i = 1000000;
    tl.testLock(i);

    pthread_t itid1;
    pthread_t itid2;

    pthread_create(&itid1, NULL, (void *(*)(void *))&ThreadEntry1, NULL);
    pthread_create(&itid2, NULL, (void *(*)(void *))&ThreadEntry2, NULL);

    pthread_join(itid1, NULL);
    pthread_join(itid2, NULL);

}


