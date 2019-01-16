#include "AServantImp.h"
#include "servant/Application.h"

using namespace std;

//////////////////////////////////////////////////////
void AServantImp::initialize()
{
    //initialize servant here:
    //...
}

//////////////////////////////////////////////////////
void AServantImp::destroy()
{
    //destroy servant here:
    //...
}

tars::Int32 AServantImp::test(tars::TarsCurrentPtr current)
{
  
	return 0;
}
tars::Int32 AServantImp::testInt(tars::Int32 iIn,tars::Int32 &iOut,tars::TarsCurrentPtr current)
{
    iOut=iIn;
    return 0;
}
tars::Int32 AServantImp::testHello(const std::string & sReq,std::string &sRsp,tars::TarsCurrentPtr current)
{
    TLOGDEBUG("HelloImp::testHellosReq:"<<sReq<<endl);
    sRsp = sReq;
    return 0;
}

tars::Int32 AServantImp::saySomething(const std::string & something,std::string &strOut,tars::TarsCurrentPtr current)
{
	strOut="Tars go";
    return 0;
}

tars::Int32 AServantImp::queryTest(const TarsTest::ReqInfo & req,vector<TarsTest::RspInfo> &vRsp,tars::TarsCurrentPtr current)
{
    TarsTest::RspInfo stRsp;
	stRsp.sSlaveName="tars";
	stRsp.sMasterIp="127.0.0.1";
	stRsp.sStartTime="0000";
	stRsp.sEndTime="2360";
	vRsp.push_back(stRsp);
	return 0;
}








