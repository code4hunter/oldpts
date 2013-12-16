//---------------------------------------------------------------------------


#pragma hdrstop

#include "OrderKeeper.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

order_keeper_manager::KEEPERMANAGERPTR order_keeper_manager::_instance(new order_keeper_manager());
boost::mutex order_keeper_manager::_map_mutex;
