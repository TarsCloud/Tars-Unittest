#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"


#include "util/tc_option.h"
#include "util/tc_common.h"
#include <iterator>
#include <iostream>
#include <sys/time.h>

using namespace std;
using namespace tars;
using namespace TarsTest;



TEST(TarsUtilTestcase, UT_TC_Option)
{
    char * g_array_argv[6][3] = {
        { (char*)"test", (char*)"--get=0", (char*)"--bit=1",  },
        { (char*)"test", (char*)"--set=98", (char*)"--bit=1",   },
        { (char*)"test", (char*)"--clear=99", (char*)"--bit=1", },
        { (char*)"test", (char*)"--clear4all", (char*)"--bit=1", },
        { (char*)"test", (char*)"--dump=./bitmap.dump", (char*)" ",  },
        { (char*)"test", (char*)"--load=./bitmap.dump", (char*)" ",  },
    };    
    
    TC_Option *op;
    
    for(unsigned int i=0; i<(sizeof(g_array_argv)/sizeof(char*[3])); i++)
    {
        char **argv = g_array_argv[i];
        int argc = (sizeof(g_array_argv[i]) / sizeof(char *));
        
        //cout << (sizeof(g_array_argv[i]) / sizeof(char *)) << endl;
        //cout << i << "  " << argv[1] << endl;
        op = new TC_Option();
        op->decode(argc, argv);

        map<string, string> mp = op->getMulti();

        cout << "map:" << endl;
        cout << TC_Common::tostr(mp) << endl;

        vector<string> d = op->getSingle();
        cout << "vector:" << endl;
        cout << TC_Common::tostr(d) << endl;

		cout << op->getValue("abc") << endl;
	}

}


