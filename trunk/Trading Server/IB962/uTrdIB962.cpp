//---------------------------------------------------------------------------

#pragma hdrstop

#include "uTrdIB962.h"
#include "Contract.h"
#include "Order.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

static long CLIENT_ID = 0;

int getNewClientID(void)
{
	return InterlockedIncrement(&CLIENT_ID);
}

TTrdItf_IB962::TTrdItf_IB962(const char *psetupfile,ADDLOG plogfunc)  :
	TTrdItfBase(psetupfile,plogfunc)
{
	_clientId = getNewClientID();
	_worker = NULL;
}

TTrdItf_IB962::~TTrdItf_IB962()
{
	this->CloseLink();
}

int TTrdItf_IB962::Init()  //初始化
{
	if( _worker == NULL )
	{
		_worker = new RecvEventsTh(this->_setup.host.c_str(),
					_setup.port,_clientId,&_client);
	}

	int i=200;
	while( (!_client.isConnected()) && (i-- > 0) )
	{
		Sleep(100);
	}
	if( i<=0 ) return -1;
	return 0;
}

void TTrdItf_IB962::CloseLink(void)
{
	if( _worker!= NULL )
	{
		_worker->Stop();
		delete _worker;
		_worker = NULL;
    }
}

int  TTrdItf_IB962::SetAccount()
{
	FAccInfo.lt = asCA;
	lstrcpyn( FAccInfo.Capital ,FRequest.SetAccount.Account ,ACC_LEN);
	NewAns(1);
	memcpy(&((*FAnswer)[0].SetAccount.AccountInfo),&FAccInfo,sizeof(TAccountInfo));
	return 0;
}

int  TTrdItf_IB962::QryMoney()
{
	ACCOUNTS acc = _client.getAccounts(FAccInfo.Capital);

	NewAns(1);
	(*FAnswer)[0].QryMoney.MoneyInfo.MoneyType = FRequest.QryMoney.MoneyType;
	(*FAnswer)[0].QryMoney.MoneyInfo.balance = 0;
	(*FAnswer)[0].QryMoney.MoneyInfo.available = 0;

	for( int i = 0; i< acc.size(); i++ )
	{
		if( acc[i].currency == ConvertMoneyType(FRequest.QryMoney.MoneyType) )
		{
			if ( acc[i].key == "CashBalance" )
			{
				(*FAnswer)[0].QryMoney.MoneyInfo.balance = atof(acc[i].val.c_str());
			}
			else if(acc[i].key == "NetLiquidationByCurrency" )
			{
				(*FAnswer)[0].QryMoney.MoneyInfo.available = atof(acc[i].val.c_str());
			}
		}
	}

	return 0;
}

int  TTrdItf_IB962::QryCurCsn()
{
	//if( _client.isConnected() == false )
	//	return 0;//ERR_REMOTE_OTHER_FAILED;   //已经断开，需要重连

	std::vector<TOrderInfo> ords;
	trade_db _db;
	try
	{
    	_db.connect();
		_db.qry_orders(FRequest.QryCurCsn.OrderID,
			FRequest.QryCurCsn.SeqNum,FRequest.QryCurCsn.MaxRecord,ords);
	}
	catch(std::string &err)
	{
		ODS("qry_orders失败，%s",err.c_str());
		return -1;
    }

	if (ords.size() > 0)
    {
        NewAns(ords.size());
		for (int i = 0; i < ords.size(); i++)
        {
			TOrderInfo *ti = (TOrderInfo *)&ords[i];
			memcpy(&(*FAnswer)[i].QryCurCsn.OrderInfo, ti, sizeof(TOrderInfo));
        }
	}

	return 0;
}

int  TTrdItf_IB962::QryCurTrd()
{
	//if( _client.isConnected() == false )
	//	return 0;//ERR_REMOTE_OTHER_FAILED;   //已经断开，需要重连

	std::vector<TTradeInfo>  list;
	trade_db _db;
    try
	{
		_db.connect();
		_db.qry_trades(FRequest.QryCurTrd.OrderID,FRequest.QryCurTrd.SeqNum,
			FRequest.QryCurTrd.MaxRecord,list);
    }
	catch(std::string &err)
    {
		ODS("qry_trades，%s",err.c_str());
		return -1;
    }

	if (list.size() > 0)
    {
        NewAns(list.size());
        for (int i = 0; i < list.size(); i++)
        {
            TTradeInfo *ti = (TTradeInfo *)&list[i];
            memcpy(&(*FAnswer)[i].QryCurTrd.TrdInfo, ti, sizeof(TTradeInfo));
        }
    }
	return 0;
}

int  TTrdItf_IB962::QryStocks()
{
	POSITIONS poss = _client.getPositions(this->FAccInfo.Capital);
	position *p = NULL;
	NewAns(poss.size());
	for (int i = 0; i < poss.size(); i++)
	{
		p = &poss[i];
		TStockInfo *ci = &(*FAnswer)[i].QryStocks.StockInfo;
		sprintf( ci->SecuID,"%s.%s.%s.%s",p->contract.symbol.c_str(),
			p->contract.secType.c_str(),p->contract.primaryExchange.c_str(),p->contract.currency.c_str());
		strncpy( ci->Account, p->accountName.c_str(), ACC_LEN);
		if( p->position > 0 )
			ci->PosDir = pdLong;
		else if( p->position < 0 )
			ci->PosDir = pdShort;
		else
			ci->PosDir = pdNo;

		ci->Market = mtNo;
		ci->PosNum = abs(p->position);
		ci->Balance= abs(p->position);
		ci->Available=abs(p->position);
		ci->CostPrice=p->averageCost;
		ci->CurPrice=p->marketPrice;
	}

	return 0;
}

//////交易函数/////
int  TTrdItf_IB962::Order()
{
	if( !_client.isConnected() )  return -1;

	/*
	int i=200;
	while( (!_client.isOrderReady()) && (i-- > 0) )
	{
		Sleep(100);
	}

	if( i<=0 )
	{
		ODS("委托序号未获得！");
		return -1;
	}
	*/

	Contract contract;
	struct Order order;

	order.clientId = this->_clientId;
	char *p = FRequest.Order.SecuID;
	char *code = FRequest.Order.SecuID;
	// code format:
	// symbol.secType.exchange.currency.expiry
	//
	int nfield = 0;
	bool exit = false;
	for( int i=0;i<CODE_LEN;i++)
	{
		if( code[i] == '.' ||  code[i] == '\0')
		{
			if( code[i] == '\0' ) exit = true;
			code[i]  =  0;

			switch( nfield++ )
			{
				case 0:
					contract.symbol = p;
					break;
				case 1:
					contract.secType = p;
					break;
				case 2:
					contract.exchange = p;
					break;
				case 3:
					contract.currency = p;
					break;
				case 4:
					contract.expiry = p;
					break;
			}
			if( exit )
				break;
			p = FRequest.Order.SecuID+i+1;
		}
	}

	if( nfield == 2)
	{
		contract.exchange = "SMART";
		contract.currency = "USD";
	}
	else if( nfield == 3 )
	{
    	contract.currency = "USD";
	}
	
	contract.primaryExchange = "";

	switch (FRequest.Order.Type) {
		case otBuy:
		case otOpenBuy:
		case otCloseBuy:
		case otCloseTodayBuy:
			order.action = "BUY";
			break;
		case otSell:
		case otOpenSell:
		case otCloseSell:
		case otCloseTodaySell:
			order.action = "SELL";
			break;
	default:
		return -1;
	}

	order.totalQuantity = FRequest.Order.Num ;
	order.lmtPrice =  FRequest.Order.Price;
	if( order.lmtPrice<=0.0001 )
		order.orderType = "MKT";
	else
		order.orderType = "LMT";
	int oid = _client.sendOrder(contract, order);
	if( oid <=0 ) return -1;
	NewAns(1);
	snprintf( (*FAnswer)[0].Order.ContractID,SEQ_LEN,"%d",oid );

	return 0;
}

int  TTrdItf_IB962::Undo()
{
	int ordid =atoi(FRequest.Undo.ContractID);
	trade_db _db;
	std::vector<TOrderInfo> ords;
	try
	{
		_db.connect();
		if( 1 == _db.qry_orders(FRequest.Undo.ContractID,"",0,ords) )
		{
			if ( ords[0].State > osdc && 	ords[0].State<=osyf )
			{
				ODS("该委托无法撤单:%d，状态:%d",ordid,ords[0].State);
				return ERR_UNDO_CANNOT_CANCLE;
			}
			else
			{
				_client.cancelOrder(ordid) ;
			}
		}
		else
		{
			ODS("委托号不存在:%d",ordid);
			return -1;
		}
	}
	catch(std::string &err)
	{
		ODS("qry_orders:%s",err.c_str());
		return -1;
	}

	return 0;
}
