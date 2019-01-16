#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"


#include "util/tc_tea.h"
#include "util/tc_common.h"

using namespace std;
using namespace tars;
using namespace TarsTest;

#define KEY  "dRa93"

TEST(TarsUtilTestcase, UT_TC_Tea)
{
    string n = "abde";
    {
        string s = n;
        cout << "encrypt:" << s << endl;
        vector<char> v = tars::TC_Tea::encrypt(KEY, s.c_str(), s.length());
        cout << "encrypt:" << TC_Common::bin2str(&v[0], v.size()) << endl;
        vector<char> s1 = tars::TC_Tea::decrypt(KEY, &v[0], v.size());
        cout << "decrypt:" << &s1[0] << endl;
    }

    {
        string s = n;
        cout << "encrypt:" << s << endl;
        vector<char> v = tars::TC_Tea::encrypt2(KEY, s.c_str(), s.length());
        cout << "encrypt:" << TC_Common::bin2str(&v[0], v.size()) << endl;
        vector<char> s1 = tars::TC_Tea::decrypt2(KEY, &v[0], v.size());
        cout << "decrypt:" << &s1[0] << endl;
    }

}


