#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"


#include "util/tc_mem_chunk.h"
#include "util/tc_sem_mutex.h"
#include "util/tc_shm.h"
#include "util/tc_mmap.h"
#include "util/tc_file.h"
#include "util/tc_option.h"
#include "util/tc_common.h"
#include <sstream>
#include <iostream>
using namespace std;
using namespace tars;
using namespace TarsTest;

TC_Mmap m;
TC_MemMultiChunkAllocator alloc;


void testAllocate()
{
    vector<size_t> b = alloc.getBlockSize();
    cout << TC_Common::tostr(b) << endl;
    cout << alloc.allBlockChunkCount() << endl;

    vector<void*> v;
    size_t n = 77;
    do
    {
        size_t iAllocSize;
        void *p = alloc.allocate(n, iAllocSize);
        cout << p << endl;
        if(!p)
        {
            break;
        }
        v.push_back(p);
        n += 2;
    } while(0);

    cout << v.size() << endl;

    for(size_t i = 0; i < v.size(); i++)
    {
        alloc.deallocate(v[i]);
    }
}


TEST(TarsUtilTestcase, UT_TC_MemMultiChunkAllocator)
{
    return;
    
    if(TC_File::isFileExist("mc.hmap"))
    {
        m.mmap("mc.hmap", TC_File::getFileSize("mc.hmap"));
    }
    else
    {
        m.mmap("mc.hmap", 1204);
    }

    if(m.iscreate())
    {
        alloc.create(m.getPointer(), m.getSize(), 30, 100, 1.2);
    }
    else
    {
        alloc.connect(m.getPointer());
    }

    //if(option.hasParam("append"))
    {
        size_t i = m.getSize() * 3;

        m.munmap();
        m.mmap("mc.hmap", i);
        alloc.append(m.getPointer(), i);

        m.munmap();
        m.mmap("mc.hmap", i*3);
        alloc.append(m.getPointer(), i*3);

        m.munmap();
        m.mmap("mc.hmap", i*5);
        alloc.append(m.getPointer(), i*5);
    }
    //else if(option.hasParam("alloc"))
    {
        testAllocate();
    }

}


