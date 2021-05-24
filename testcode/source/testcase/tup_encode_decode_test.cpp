#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "gtest/gtest.h"
#include "TarsTest/UnitTest/UserInfo.h"
#include "tup/tup.h"

using namespace std;
using namespace tars;
using namespace tup;
using namespace Test;

// static string str2hex(const string& sBuffer)
// {
//     string str = "";
//     for (size_t i = 0; i < sBuffer.length(); ++i) {
//         char sb[4] = {0};
//         snprintf(sb, 4, "%02x", (unsigned char)sBuffer[i]);
//         if (i%10==0)str.append("\n");
//         str.append("(byte)0x");
//         str.append(sb);
//         str.append(",");
//     }
//     return str;
// }

/*static char __data[] = {
    0x1c,0x2c,0x3c,0x40,0x03,0x56,0x00,0x66,0x09,0x6e,0x4c,0x6f,0x67,0x69,0x6e,0x6e,0x65,0x77,0x7d,0x00,0x00,0x39,0x08,0x00,0x02,0x06,0x03,0x70,0x77,0x64,0x18,0x00,0x01,0x06,0x06,0x73,0x74,0x72,0x69,0x6e,0x67,0x1d,0x00,0x00,0x0a,0x06,0x08,0x33,0x67,0x71,0x71,0x74,0x65,0x73,0x74,0x06,0x03,0x75,0x69,0x6e,0x18,0x00,0x01,0x06,0x05,0x69,0x6e,0x74,0x33,0x32,0x1d,0x00,0x00,0x05,0x02,0x3f,0xe2,0x78,0xac,0x8c,0x98,0x0c,0xa8,0x0c,};
*/
TEST(TupUniPacketTest, encode_and_decode_using_UniPacket)
{
    try
    {

        ////////////////////////////////////////
        /*
        string data(__data, sizeof(__data));
        UniRequest<> request;
        request.decode(data.c_str(), data.length());
        return 0;
        cout << "type:" << Class<Int32>::name() << endl;
        cout << "type:" << Class<vector<Char> >::name() << endl;
        cout << "type:" << Class<map<Short, vector<string> > >::name() << endl;
        cout << "type:" << Class<map<Double, map<Float, vector<Bool> > > >::name() << endl;
        cout << "type:" << Class<map<Int64, vector<UserInfo> > >::name() << endl;
        cout << "type:" << Class<map<Short, FriendInfo> >::name() << endl;
        */

        string buff = "";
        ////////////////////////////////////////
        UniPacket<> client;

        client.setRequestId(10000);
        client.setServantName("do");
        client.setFuncName("test");

        client.put<Int32>("qq", 11688188);
        client.put<string>("nick", "zhangsan");

        //struct
        FriendInfo fi;
        fi.nick = "zhangsan";
        fi.uin = 172917;
        fi.birthday.push_back('5');
        fi.birthday.push_back('3');
        client.put<FriendInfo>("friendInfo", fi);

         //vector
        vector<UserInfo> vui;
        UserInfo ui;
        ui.qq = 123456;
        ui.nick = "wawa";
        ui.birthday.push_back('2');
        ui.birthday.push_back('0');
        vui.push_back(ui);
        ui.qq = 122400997;
        ui.nick = "wawahaha";
        ui.birthday.push_back('1');
        ui.birthday.push_back('9');
        ui.city = "bj";
        vui.push_back(ui);
        client.put<vector<UserInfo> >("userInfo", vui);

        //map
        map<short, FriendInfo> mfi;
        FriendInfo ffi;
        ffi.uin = 10001;
        ffi.nick = "friend1";
        ffi.birthday.push_back('9');
        ffi.birthday.push_back('8');
        mfi[10001] = ffi;
        ffi.uin = 10002;
        ffi.nick = "friend2";
        ffi.birthday.clear();
        ffi.birthday.push_back('9');
        ffi.birthday.push_back('7');
        mfi[10002] = ffi;
        client.put<map<short, FriendInfo> >("friendInfo", mfi);

        //crypt-attr
        UniAttribute<> attr;
        attr.put<Int32>("attr-qq", 172917);
        attr.put<string>("attr-nick", "sanzhang");
        vector<FriendInfo> vfi;

        attr.put<vector<FriendInfo> >("attr-friends", vfi);

        vector<char> crpyBuffer;
        attr.encode(crpyBuffer);
        //do encrypt...
        client.put("crypt-attr", crpyBuffer);

        vector<char> vc;
        vc.push_back('a');
        vc.push_back('b');
        vc.push_back('c');
        vc.push_back('d');
        vc.push_back('e');
        client.put<vector<char> >("vc", vc);

        //客户端编码
        client.encode(buff);

        ////////////////////////////////////////
        //网络传输...
        /*
        cout << str2hex(buff) << endl; 
        output.close();
        return 0;
        */
        ////////////////////////////////////////

        cout << "---------------------------------" << endl;

        //服务端解码
        UniPacket<> server;
        server.decode(buff.c_str(), buff.length());

        cout << "[requestId]:" << server.getRequestId() << endl;
	    EXPECT_EQ(server.getRequestId(),10000);
        cout << "[servantName]:" << server.getServantName() << endl;
	    EXPECT_STREQ(server.getServantName().c_str(), "do");
        cout << "[funcName]:" << server.getFuncName() << endl;
	    EXPECT_STREQ(server.getFuncName().c_str(), "test");
        cout << "[qq]:" << server.get<int>("qq") << endl;
	    EXPECT_EQ(server.get<int>("qq"), 11688188);
        cout << "[nick]:" << server.get<string>("nick") << endl;
	    EXPECT_STREQ(server.get<string>("nick").c_str(), "zhangsan");

        //vector
        vector<UserInfo> vinfo;
        server.get("userInfo", vinfo);
	    ASSERT_EQ(vinfo.size(), 2);

        for (size_t j = 0; j < vinfo.size(); ++j)
        {
            UserInfo info = vinfo[j];
            cout << "[userInfo]:" << j << endl; 
            cout << "<qq>:" << info.qq << endl;
            cout << "<nick>:" << info.nick << endl;
            if(0 == j)
            {
                EXPECT_EQ(info.qq, 123456);
                EXPECT_STREQ(info.nick.c_str(), "wawa");
                ASSERT_EQ(info.birthday.size(), 2);
                EXPECT_STREQ(info.city.c_str(), "gd");
            }
            else if(1 == j)
            {
                EXPECT_EQ(info.qq, 122400997);
                EXPECT_STREQ(info.nick.c_str(), "wawahaha");
                ASSERT_EQ(info.birthday.size(), 4);
                EXPECT_STREQ(info.city.c_str(), "bj");
            }
             
	        char *szBirthday = new char[info.birthday.size() + 1];  
            cout << "<birthday>:";
            for (int i = 0; i < info.birthday.size(); ++i)
            {
                cout << info.birthday[i] << ",";
                snprintf(szBirthday + i, sizeof(szBirthday) - i, "%d", info.birthday[i] - '0');
            }
            if(0 == j)
            {
                EXPECT_STREQ(szBirthday, "20");
            }
            else if(1 == j)
            {
                EXPECT_STREQ(szBirthday, "2019");
            }

            delete []szBirthday;

            cout << endl;
            cout << "<city>:" << info.city << endl;

        }

        cout << "---------------------------------" << endl;
        //map
        map<short, FriendInfo> minfo;
        server.get("friendInfo", minfo);

        ASSERT_EQ(minfo.size(), 2);

	int index = 0;
        for (map<short, FriendInfo>::iterator it = minfo.begin(); it != minfo.end(); ++it, ++index)
        {
            cout << "[friendInfo]:" << it->first << endl;
            cout << "<uin>:" << it->second.uin << endl;
            cout << "<nick>:" << it->second.nick << endl;
            cout << "<birthday>:";

            char *szBirthday = new char[it->second.birthday.size() + 1];  

            // char szBirthday[it->second.birthday.size() + 1] = {0};
            for (size_t i = 0; i < it->second.birthday.size(); ++i)
            {
                cout << it->second.birthday[i] << ",";
                snprintf(szBirthday + i, sizeof(szBirthday) - i, "%c", it->second.birthday[i]);
            }
            cout << endl;

            if(0 == index)
            {
                EXPECT_EQ(it->first, 10001);
                EXPECT_EQ(it->second.uin, 10001);
                EXPECT_STREQ(it->second.nick.c_str(), "friend1");
                EXPECT_STREQ(szBirthday, "98");
            }
            else if(1 == index)
            {
                EXPECT_EQ(it->first, 10002);
                EXPECT_EQ(it->second.uin, 10002);
                EXPECT_STREQ(it->second.nick.c_str(), "friend2");
                EXPECT_STREQ(szBirthday, "97");
            }

            delete[] szBirthday;
        }

        cout << "---------------------------------" << endl;
        //crypt-attr
        UniAttribute<> cryptAttr;
        vector<char> cryptAttrBuffer;
        server.get("crypt-attr", cryptAttrBuffer);

        //do decrypt...
        cryptAttr.decode(cryptAttrBuffer);
        cout << "[attr-qq]:" << cryptAttr.get<int>("attr-qq") << endl;
        EXPECT_EQ(cryptAttr.get<int>("attr-qq"), 172917);
        cout << "[attr-nick]:" << cryptAttr.get<string>("attr-nick") << endl;
        EXPECT_STREQ(cryptAttr.get<string>("attr-nick").c_str(), "sanzhang");
        vector<FriendInfo> sfi;
        cryptAttr.get("attr-friends", sfi);
        cout << "[attr-friends]:" << sfi.size() << endl;
        EXPECT_EQ(sfi.size(), 0);
        for (size_t i = 0; i < sfi.size(); ++i)
        {
            cout << "<uin>:" << sfi[i].uin << endl;
            cout << "<nick>:" << sfi[i].nick << endl;
        }
        cout << "---------------------------------" << endl;
        ////////////////////////////////////////
        cout << "{default}:" << server.getByDefault<string>("default", "kaka") << endl;
    }
    catch (exception& e)
    {
        cout << "excep:" << e.what() << endl;
    }
    catch (...)
    {
        cout << "excep." << endl;
    }
}

