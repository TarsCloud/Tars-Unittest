#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"


#include "util/tc_mmap.h"
#include "util/tc_option.h"
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;
using namespace tars;
using namespace TarsTest;



void testCreate(size_t n)
{
    TC_Mmap mmap;
    cout << "create mmap" << endl;
    mmap.mmap("mmap.dat", n);
    mmap.munmap();
    cout << "create mmap OK" << endl;
}

void testWrite(const string &s)
{
    TC_Mmap mmap;
    cout << "write mmap" << endl;
    mmap.mmap("mmap.dat", 1000);
    memcpy(mmap.getPointer(), s.c_str(), s.length());

    TC_Common::sleep(10);

    mmap.munmap();
}

void testRead()
{
    TC_Mmap mmap;
    cout << "read mmap" << endl;
    mmap.mmap("mmap.dat", 1000);

    string s;
    s.assign((char*)mmap.getPointer(), mmap.getSize());
    mmap.munmap();

    cout << s << endl;
}

void main_test(int argc, char *argv[])
{

    TC_Option option;
    option.decode(argc, argv);

    // int pagesize = sysconf(_SC_PAGESIZE);

    // cout << "pagesize:" << pagesize << endl;

    if(option.getValue("test") == "create")
    {
        size_t n = 50;
        testCreate(n);
    }
    else if(option.getValue("test") == "write")
    {
        testWrite(option.getValue("c"));
    }
    else if(option.getValue("test") == "read")
    {
        testRead();
    }

}



TEST(TarsUtilTestcase, UT_TC_Mmap)
{
    testCreate(50);
    testWrite("just a test.");
    testRead();
    /*
    char * g_array_argv[6][3] = { 

    };    
     
    for(unsigned int i=0; i<(sizeof(g_array_argv)/sizeof(char*[3])); i++)
    {
        char **argv = g_array_argv[i];
        int argc = (sizeof(g_array_argv[i]) / sizeof(char *));
        main_test(argc, argv);
    }        
    */
}

