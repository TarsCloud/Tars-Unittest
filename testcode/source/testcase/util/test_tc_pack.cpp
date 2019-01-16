#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"


#include "util/tc_pack.h"
#include <iostream>
#include <cassert>

using namespace std;
using namespace tars;
using namespace TarsTest;

TEST(TarsUtilTestcase, UT_TC_Pack)
{
    bool b = true;
    char c = 'a';
    short si = 3;
    int   ii = 4;
    char cn[] = "abc";
    string sn = "def";

    TC_PackIn pi;
    pi << b << c << si << ii << cn << sn;

    string s = pi.topacket();

    TC_PackOut po(s.c_str(), s.length());
    po >> b;
    assert(b == true);
    cout << "bool OK" << endl;

    po >> c;
    assert(c == 'a');
    cout << "char OK" << endl;

    po >> si;
    assert(si == 3);
    cout << "short OK" << endl;

    po >> ii;
    assert(ii == 4);
    cout << "int OK" << endl;

    po >> cn;
    assert(cn == string("abc"));
    cout << "char[] OK" << endl;

    po >> sn;
    assert(sn == "def");
    cout << "string OK" << endl;

    {
        pi.clear();

        pi << b << c;
        pi.insert(1) << cn;

        s = pi.topacket();
        po.init(s.c_str(), s.length());
        po >> b;
        assert(b == true);
        cout << "bool OK" << endl;

        po >> cn;
        assert(cn == string("abc"));
        cout << "char[] OK" << endl;

        po >> c;
        assert(c == 'a');
        cout << "char OK" << endl;
    }

    {
        pi.clear();
        pi << b << c;
        pi.replace(1) << 'b';

        s = pi.topacket();
        po.init(s.c_str(), s.length());
        po >> b;
        assert(b == true);
        cout << "bool OK" << endl;

        po >> c;
        assert(c == 'b');
        cout << "char OK" << endl;
    }

}


