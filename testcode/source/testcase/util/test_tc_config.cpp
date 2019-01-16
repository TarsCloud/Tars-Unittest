#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"


#include "util/tc_config.h"
#include "util/tc_file.h"
#include <iterator>
#include <sys/time.h>
using namespace std;
using namespace tars;
using namespace TarsTest;


TEST(TarsUtilTestcase, UT_TC_Config)
{
    try  {
        TC_Config conf;
        conf.parseFile("./template.config.conf");

        cout << "parseFile************************************" << endl;
        cout << conf.tostr() << endl;

        vector<string> n = conf.getDomainVector("/");
        cout << TC_Common::tostr(n) << endl;

        // return 0;
        cout << "parseFile************************************" << endl;
        TC_Config conft = conf;
        cout << conft.tostr() << endl;

        cout << conf["/tars/application/client<locator>"] << endl;
        map<string, string> m1 = conf.getDomainMap("/tars/allow");
        cout << TC_Common::tostr(m1) << endl;  
        cout << conf["/tars/allow<A>"] << endl;

        cout << "parseString************************************" << endl;
        TC_File tf;
        conf.parseString(tf.load2str("./template.config.conf"));
        cout << conf.tostr() << endl;
        cout << conf["/tars/application/client<locator>"] << endl;

        cout << "insertDomain create false************************************" << endl;

        conf.insertDomain("/tars/insert", "insert", false);
        cout << conf.tostr() << endl;
        conf.parseString(conf.tostr());
        cout << conf.tostr() << endl;

        cout << "insertDomain create true************************************" << endl;

        conf.insertDomain("/tars/insert", "insert", true);
        cout << conf.tostr() << endl;
        conf.parseString(conf.tostr());
        cout << conf.tostr() << endl;

        cout << "insertDomainParam************************************" << endl;

        map<string, string> m;
        m["abc"] = "def";
        m["ttt"] = "yyy";
        conf.insertDomainParam("/tars/insert/insert1", m, false);
        cout << conf.tostr() << endl;
        conf.insertDomainParam("/tars/insert/insert1", m, true);
        cout << conf.tostr() << endl;

        cout << "joinConfig true************************************" << endl;
        TC_Config conf1;
        conf1.parseFile("./log.config.conf");

        conf1.joinConfig(conf, true);
        cout << conf1.tostr() << endl;

        cout << "joinConfig false************************************" << endl;
        TC_Config conf2;
        conf2.parseFile("./log.config.conf");
        conf2.joinConfig(conf, false);
        cout << conf2.tostr() << endl;

        TC_Config conf3 = conf2;
        cout << conf3.tostr() << endl;
    }
	catch(exception &ex)
	{
        EXPECT_FALSE(false) << ex.what() << endl;
	}    

}


