#ifndef _AServantImp_H_
#define _AServantImp_H_

#include "servant/Application.h"
#include "AServant.h"

/**
 *
 *
 */
class AServantImp : public TarsTest::AServant
{
public:
    /**
     *
     */
    virtual ~AServantImp() {}

    /**
     *
     */
    virtual void initialize();

    /**
     *
     */
    virtual void destroy();
	virtual tars::Int32 test(tars::TarsCurrentPtr current);
	virtual tars::Int32 testInt(tars::Int32 iIn,tars::Int32 &iOut,tars::TarsCurrentPtr current);
	virtual tars::Int32 testHello(const std::string & sReq,std::string &sRsp,tars::TarsCurrentPtr current);
	virtual tars::Int32 saySomething(const std::string & something,std::string &strOut,tars::TarsCurrentPtr current);
	virtual tars::Int32 queryTest(const TarsTest::ReqInfo & req,vector<TarsTest::RspInfo> &vRsp,tars::TarsCurrentPtr current);
    /**
     *
     */
};
/////////////////////////////////////////////////////
#endif
