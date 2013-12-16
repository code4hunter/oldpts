//---------------------------------------------------------------------------

#pragma hdrstop

#include "OrderKeeper.h"
#include <tchar.h>
#include <iostream>
#include <string>
//---------------------------------------------------------------------------

#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{

	TSetAccount_Req req;

	strncpy(req.Account,"acc1",6);
	strncpy(req.PW,"pass",6);
	order_keeper_manager::instance()->start_keeper(&req);
	order_keeper_manager::instance()->start_keeper(&req);

	strncpy(req.Account,"acc2",6);
	strncpy(req.PW,"pass2",6);
	order_keeper_manager::instance()->start_keeper(&req);
	order_keeper_manager::instance()->start_keeper(&req);



	std::string input;
	std::cin >> input;
	return 0;
}
//---------------------------------------------------------------------------
