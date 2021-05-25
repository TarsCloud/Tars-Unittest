#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"


#include "util/tc_file.h"
#include <errno.h>
#include <iterator>
// #include <sys/time.h>

using namespace std;
using namespace tars;
using namespace TarsTest;

/*
int removeFile(const string &sFullFileName, bool bRecursive)
{
    cout << sFullFileName << endl;
    string path = TC_File::simplifyDirectory(sFullFileName);

    struct stat f_stat;

    if (lstat(path.c_str(), &f_stat) == -1)
    {
        return -1;
    }

    if(S_ISDIR(f_stat.st_mode))
    {
        if(bRecursive)
        {
            vector<string> files;
            TC_File::listDirectory(path, files, true, false);
            for(size_t i = 0; i < files.size(); i++)
            {
                removeFile(files[i], bRecursive);
            }

            if(path != "/")
            {
                if(::rmdir(path.c_str()) == -1)
                {
                    return -1;
                }
                return 0;
            }
        }
        else
        {
            if(::rmdir(path.c_str()) == -1)
            {
                return -1;
            }
        }
    }
    else
    {
        if(::remove(path.c_str()) == -1)
        {
            return -1;
        }
    }

    return 0;
}
*/

struct Out
{
    void operator()(const string &n)
    {
        cout << n << endl;
    }
};

// TEST(TarsUtilTestcase, UT_TC_File)
// {

// //    	cout << TC_File::getFileSize("./test_tc_file.cpp") << endl;
// //    	cout << TC_File::isFileExist("./test_tc_file.cpp", S_IFDIR) << endl;
//     EXPECT_TRUE(TC_File::makeDir("./test"));
//     EXPECT_TRUE(TC_File::isFileExist("./test", S_IFDIR));
//     EXPECT_EQ(0, TC_File::removeFile("./test", true));
//     EXPECT_FALSE(TC_File::isFileExist("./test", S_IFDIR));

//     EXPECT_TRUE(TC_File::makeDirRecursive("./test/test1/test2/"));
//     EXPECT_TRUE(TC_File::isFileExistEx("./test/test1/test2/", S_IFDIR));
//     EXPECT_EQ(0, TC_File::removeFile("./test", true));
//     EXPECT_FALSE(TC_File::isFileExist("./test", S_IFDIR));        
    
//     EXPECT_TRUE("not_exist/" == TC_File::extractUrlFilePath("http://127.0.0.1/not_exist/"));
//     EXPECT_TRUE("" == TC_File::extractUrlFilePath("http://127.0.0.1/"));
//     EXPECT_TRUE("test.html" == TC_File::extractUrlFilePath("HtTp://127.0.0.1/test.html"));
    
//     EXPECT_EQ("/", TC_File::simplifyDirectory("/."));
//     EXPECT_EQ("/ab/tt/t/t/../tt", TC_File::simplifyDirectory("/./ab/tt//t///t//../tt/"));
    
//     // TC_File::removeFile("./", true);
// //        int ret = removeFile("/home/jarodruan/taf/bin/tmp", true);
//     //vector<string> v;
//     //TC_File::listDirectory("/usr", v, true);
//     //for_each(v.begin(), v.end(), Out());

// //        TC_File::removeFile("/home/base.l", false);


// }


TEST(TarsUtilTestcase, UT_TC_File1)   //此时使用的是TEST_F宏
{
	string file = "./test.dat";
	string data = "helloword";
	data[3] = '\0';

	TC_File::save2file(file, data);
	int fileSize = TC_File::getFileSize(file);
	cout << "file size:" << fileSize  << endl;
	ASSERT_TRUE(fileSize == data.size());

	string load = TC_File::load2str(file);
	cout << "load file size:" << load.size() << endl;
	ASSERT_TRUE(load == data);

	bool fileExists = TC_File::isFileExist(file, S_IFREG);
    cout << "file exists:" << fileExists << endl;
    ASSERT_TRUE(fileExists);

    string dir = "test";
    TC_File::makeDir(dir);
	fileExists = TC_File::isFileExist(dir, S_IFDIR);
	cout << "dir exists:" << fileExists << endl;
	ASSERT_TRUE(fileExists);

	string newFile = dir + FILE_SEP + file;
	TC_File::save2file(newFile, data);
	fileExists = TC_File::isFileExist(newFile, S_IFREG);
	cout << "newFile exists:" << fileExists << endl;
	ASSERT_TRUE(fileExists);

	TC_File::makeDir(dir + FILE_SEP + "test1");
	TC_File::makeDir(dir + FILE_SEP + "test2");

	vector<string> v;
	TC_File::listDirectory(dir, v, true);
	cout << "listDirectory:" << endl;
	for(auto s : v)
	{
		cout << "    " << s << endl;
	}

	TC_File::removeFile(dir, true);
	fileExists = TC_File::isFileExist(file, S_IFDIR);
	cout << "dir exists:" << fileExists << endl;
	ASSERT_TRUE(!fileExists);
}

TEST(TarsUtilTestcase, UT_TC_File2)
{
#if TARGET_PLATFORM_WINDOWS
	cout << "simplifyDirectory:" << TC_File::simplifyDirectory("/./ab/tt//t///t//../tt/") << endl;
	ASSERT_TRUE(TC_File::simplifyDirectory("/./ab/tt//t///t//../tt/") == "ab\\tt\\t\\tt");
	cout << "simplifyDirectory:" << TC_File::simplifyDirectory("c:/ab/tt//t///t//../tt/") << endl;
	ASSERT_TRUE(TC_File::simplifyDirectory("c:/ab/tt//t///t//../tt/") == "c:\\ab\\tt\\t\\tt");
#else
	cout << "simplifyDirectory:" << TC_File::simplifyDirectory("/./ab/tt//t///t//../tt/") << endl;
	ASSERT_TRUE(TC_File::simplifyDirectory("/./ab/tt//t///t//../tt/") == "/ab/tt/t/tt");
	cout << "simplifyDirectory:" << TC_File::simplifyDirectory("/ab/tt//t///t//../tt/") << endl;
	ASSERT_TRUE(TC_File::simplifyDirectory("/ab/tt//t///t//../tt/") == "/ab/tt/t/tt");
#endif
}

TEST(TarsUtilTestcase, UT_TC_File3)
{

	ASSERT_TRUE(TC_File::extractFileExt("/usr/local/app/bin.exe") == "exe");
	ASSERT_TRUE(TC_File::extractFileExt("/usr/local/app/bin") == "");
	ASSERT_TRUE(TC_File::extractFileExt("/usr/local/app.dir/bin.exe") == "exe");
	ASSERT_TRUE(TC_File::extractFileExt("c:\\usr\\local\\app.dir\\bin.exe") == "exe");
	ASSERT_TRUE(TC_File::extractFileExt("c:\\usr\\local\\app.dir\\bin") == "");

	ASSERT_TRUE(TC_File::extractFileName("/usr/local/app/bin.exe") == "bin.exe");
	ASSERT_TRUE(TC_File::extractFileName("/usr/local/app/bin") == "bin");
	ASSERT_TRUE(TC_File::extractFileName("/usr/local/app.dir/bin.exe") == "bin.exe");
	ASSERT_TRUE(TC_File::extractFileName("c:\\usr\\local\\app.dir\\bin.exe") == "bin.exe");
	ASSERT_TRUE(TC_File::extractFileName("c:\\usr\\local\\app.dir\\bin") == "bin");
	ASSERT_TRUE(TC_File::extractFileName("bin.exe") == "bin.exe");

	ASSERT_TRUE(TC_File::extractFilePath("/usr/local/app/bin.exe") == "/usr/local/app/");
	ASSERT_TRUE(TC_File::extractFilePath("/usr/local/app/bin") == "/usr/local/app/");
	ASSERT_TRUE(TC_File::extractFilePath("/usr/local/app.dir/bin.exe") == "/usr/local/app.dir/");
	ASSERT_TRUE(TC_File::extractFilePath("c:\\usr\\local\\app.dir\\bin.exe") == "c:\\usr\\local\\app.dir\\");
	ASSERT_TRUE(TC_File::extractFilePath("c:\\usr\\local\\app.dir\\bin") == "c:\\usr\\local\\app.dir\\");
	ASSERT_TRUE(TC_File::extractFilePath("temp.gif") == string(".") + FILE_SEP);

	ASSERT_TRUE(TC_File::excludeFileExt("/usr/local/app/bin.exe") == "/usr/local/app/bin");

	ASSERT_TRUE(TC_File::excludeFileExt("/usr/local/app/bin") == "/usr/local/app/bin");
	ASSERT_TRUE(TC_File::excludeFileExt("/usr/local/app.dir/bin.exe") == "/usr/local/app.dir/bin");
	ASSERT_TRUE(TC_File::excludeFileExt("c:\\usr\\local\\app.dir\\bin.exe") == "c:\\usr\\local\\app.dir\\bin");
	ASSERT_TRUE(TC_File::excludeFileExt("c:\\usr\\local\\app.dir\\bin") == "c:\\usr\\local\\app.dir\\bin");
	ASSERT_TRUE(TC_File::excludeFileExt("temp.gif") == "temp");
}

