#include "gtest/gtest.h"
#include "servant/Application.h"
#include "TarsTest/TestcaseServer/RPCTest.h"
#include "servant/AdminF.h"
#include "TarsServantName.h"


#include "util/tc_file.h"
#include <errno.h>
#include <iterator>
#include <sys/time.h>

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

TEST(TarsUtilTestcase, UT_TC_File)
{

//    	cout << TC_File::getFileSize("./test_tc_file.cpp") << endl;
//    	cout << TC_File::isFileExist("./test_tc_file.cpp", S_IFDIR) << endl;
    EXPECT_TRUE(TC_File::makeDir("./test", S_IRWXU | S_IRWXG | S_IRWXO));
    EXPECT_TRUE(TC_File::isFileExist("./test", S_IFDIR));
    EXPECT_EQ(0, TC_File::removeFile("./test", true));
    EXPECT_FALSE(TC_File::isFileExist("./test", S_IFDIR));

    EXPECT_TRUE(TC_File::makeDirRecursive("./test/test1/test2/", S_IRWXU | S_IRWXG | S_IRWXO));
    EXPECT_TRUE(TC_File::isFileExistEx("./test/test1/test2/", S_IFDIR));
    EXPECT_EQ(0, TC_File::removeFile("./test", true));
    EXPECT_FALSE(TC_File::isFileExist("./test", S_IFDIR));        
    
    EXPECT_TRUE("not_exist/" == TC_File::extractUrlFilePath("http://127.0.0.1/not_exist/"));
    EXPECT_TRUE("" == TC_File::extractUrlFilePath("http://127.0.0.1/"));
    EXPECT_TRUE("test.html" == TC_File::extractUrlFilePath("HtTp://127.0.0.1/test.html"));
    
    EXPECT_EQ("/", TC_File::simplifyDirectory("/."));
    EXPECT_EQ("/ab/tt/t/t/../tt", TC_File::simplifyDirectory("/./ab/tt//t///t//../tt/"));
    
    // TC_File::removeFile("./", true);
//        int ret = removeFile("/home/jarodruan/taf/bin/tmp", true);
    //vector<string> v;
    //TC_File::listDirectory("/usr", v, true);
    //for_each(v.begin(), v.end(), Out());

//        TC_File::removeFile("/home/base.l", false);


}


