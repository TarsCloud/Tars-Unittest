#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"


#include "util/tc_autoptr.h"
#include "util/tc_functor.h"
#include "util/tc_thread_pool.h"
#include <vector>
#include <cassert>
#include <iostream>


using namespace std;
using namespace tars;
using namespace TarsTest;


/// begin test data
TC_Atomic a;

class TestPointer : public TC_HandleBase
{
public:
    void func(int &i)
    {
        int n = 10000;
        while(n)
        {
            i++;
            n--;
        }
    }
};

void testAdd()
{
    int i = 1000000;
    while(i--)
    {
        a.inc();
    }
}

void testDel()
{
    int i = 1000000;
    while(i--)
    {
        a.dec();
    }
}    
    
/// end test data

// 测试多线程并行读写 TC_Atomic 时的原子性与正确性
TEST(TarsUtilTestcase, UT_TC_Atomic)
{
    EXPECT_EQ(0, a.get());

    TC_ThreadPool tpoolA;
    tpoolA.init(10);
    tpoolA.start();

    TC_ThreadPool tpoolB;
    tpoolB.init(10);
    tpoolB.start();

    {
        TC_Functor<void> functor(testAdd);
        TC_Functor<void>::wrapper_type wt(functor);

        for(size_t i = 0; i < tpoolA.getThreadNum(); i++)
        {
            tpoolA.exec(wt);
        }
    }

    {
        TC_Functor<void> functor(testDel);
        TC_Functor<void>::wrapper_type wt(functor);

        for(size_t i = 0; i < tpoolB.getThreadNum(); i++)
        {
            tpoolB.exec(wt);
        }
    }

    tpoolA.waitForAllDone();
    tpoolB.waitForAllDone();

    EXPECT_EQ(0, a.get());


}


// 测试 TC_AutoPtr 的构造函数 TC_AutoPtr(T* p = 0) ？
TEST(TarsUtilTestcase, UT_TC_AutoPtr)
{
    int i = 0;

    typedef TC_AutoPtr<TestPointer> TestPointerPtr;
    vector<TestPointerPtr> vtp;
    for(size_t j = 0; j < 10; j++)
    {
        vtp.push_back(new TestPointer());
    }

    EXPECT_EQ(0, i);
    
    for(size_t j = 0; j < 10; j++)
    {
        vtp[j]->func(i);
    }
    EXPECT_EQ(10*10000, i);
    
    vector<TestPointerPtr> vtp1 = vtp;
    for(size_t j = 0; j < 10; j++)
    {
        vtp[j]->func(i);
    }

    EXPECT_EQ(20*10000, i);
}

