/*
 * ServerAdmin.cpp
 *
 *  Created on: 2018年10月16日
 *      Author: abelguo
 */
#include "utils/ServerAdmin.h"
#include "servant/AdminF.h"
#include "servant/Application.h"

TARSTEST_NS_START

ServerAdmin::ServerAdmin()
{
	_comm = new Communicator();
}
ServerAdmin& ServerAdmin::shutdown(const string& serverName)
{
	AdminFPrx adminPrx = _comm->stringToProxy<AdminFPrx> (serverName);

	adminPrx->shutdown();

	return *this;
}

TARSTEST_NS_END

