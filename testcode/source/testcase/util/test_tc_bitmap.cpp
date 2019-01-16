#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"

#include "util/tc_shm.h"
#include "util/tc_bitmap.h"
#include "util/tc_option.h"
#include "util/tc_common.h"

#include <iterator>
#include <iostream>
#include <string.h>

using namespace std;
using namespace tars;
using namespace TarsTest;

TC_Shm      g_shm;
TC_BitMap   g_bmap;

#define DUMP_FILE  "./bitmap.dump"

void initMap()
{
    unsigned iBit       = 3;
    size_t iMemSize     = TC_BitMap::calcMemSize(100, iBit);
    g_shm.init(iMemSize, 9999);

    if (g_shm.iscreate())
    {
        g_bmap.create(g_shm.getPointer(), g_shm.size(), iBit);
    }
    else
    {
        g_bmap.connect(g_shm.getPointer(), g_shm.size(), iBit);
    }

    cout << "init mem:" << iMemSize << endl;
}

void usage(char *argv[])
{
    cout << argv[0] << " --get=uin --bit" << endl;
    cout << argv[0] << " --set=uin --bit" << endl;
    cout << argv[0] << " --clear=uin --bit" << endl;
    cout << argv[0] << " --clear4all --bit" << endl;
    cout << argv[0] << " --dump=file" << endl;
    cout << argv[0] << " --load=file" << endl;
    cout << argv[0] << " --help" << endl;
}



TEST(TarsUtilTestcase, UT_TC_BitMap)
// int main(int argc, char *argv[])
{
    char * g_array_argv[6][3] = {
        { (char*)"test", (char*)"--get=0", (char*)"--bit=1",  },
        { (char*)"test", (char*)"--set=98", (char*)"--bit=1",   },
        { (char*)"test", (char*)"--clear=99", (char*)"--bit=1", },
        { (char*)"test", (char*)"--clear4all", (char*)"--bit=1", },
        { (char*)"test", (char*)"--dump=./bitmap.dump", (char*)" ",  },
        { (char*)"test", (char*)"--load=./bitmap.dump", (char*)" ",  },
    };    
    
    FILE *file;
    TC_Option *op;

    initMap();
    file = fopen(DUMP_FILE, "wb+");
    
    ASSERT_TRUE(NULL != file) << "can't open file: " << DUMP_FILE << endl ;
    
    //cout  << sizeof(g_array_argv) << endl;
    //cout  << sizeof(char*[3]) << endl;
    for(unsigned int i=0; i<(sizeof(g_array_argv)/sizeof(char*[3])); i++)
    {
        char **argv = g_array_argv[i];
        int argc = (sizeof(g_array_argv[i]) / sizeof(char *));
        
        //cout << (sizeof(g_array_argv[i]) / sizeof(char *)) << endl;
        //cout << i << "  " << argv[1] << endl;
        op = new TC_Option();
        op->decode(argc, argv);
        
        // cout << "argc: " << argc << ",  " << "argv: " << argv[1] << endl;
        
        if(op->hasParam("get"))
        {
            size_t uin = TC_Common::strto<size_t>(op->getValue("get"));
            unsigned bit = TC_Common::strto<unsigned>(op->getValue("bit"));
            cout << "uin=" << uin << ", " << "bit=" << bit << endl;
            cout << "get:" << uin << "=" << g_bmap.get(uin, bit) << endl;
            EXPECT_EQ(0, g_bmap.get(uin, bit));
        }
        else if(op->hasParam("set"))
        {
            size_t uin = TC_Common::strto<size_t>(op->getValue("set"));
            unsigned bit = TC_Common::strto<unsigned>(op->getValue("bit"));
            cout << "set:" << uin << "=" << g_bmap.set(uin, bit) << endl;
            EXPECT_EQ(1, g_bmap.get(uin, bit));
        }
        else if(op->hasParam("clear"))
        {
            size_t uin = TC_Common::strto<size_t>(op->getValue("clear"));
            unsigned bit = TC_Common::strto<unsigned>(op->getValue("bit"));
            cout << "clear:" << uin << "=" << g_bmap.clear(uin, bit) << endl;
            EXPECT_EQ(0, g_bmap.get(uin, bit));
        }
        else if(op->hasParam("clear4all"))
        {
            int bit = TC_Common::strto<int>(op->getValue("bit"));
            cout << "clear4all:" << bit << "=" << g_bmap.clear4all((unsigned)bit) << endl;
            EXPECT_EQ(0, g_bmap.get(98, bit));
        }
        else if(op->hasParam("dump"))
        { 
            string file = op->getValue("dump");
            cout << "file dump =" << file << endl;
            int ret = g_bmap.dump2file(file);
            EXPECT_EQ(0, ret);
            if(ret == 0)
                cout << "dump2file:" << file << " ok" << endl;
            else
                cout << "dump2file:" << file << " err:" << ret << endl;
        } 
        else if(op->hasParam("load"))
        {
            string file = op->getValue("load");
            int ret = g_bmap.load5file(file);
            EXPECT_EQ(0, ret);
            if(ret == 0)
                cout << "load5file:" << file << " ok" << endl;
            else
                cout << "load5file:" << file << " err:" << ret << endl;
        }
        else
        {
            usage(argv);
        }
    }

}


