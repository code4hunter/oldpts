//---------------------------------------------------------------------------
#pragma hdrstop
#include <system.hpp>
#include "uItfTrdTrdSvr.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

TTrdItf_TrdSvr::TTrdItf_TrdSvr(const char *psetupfile,ADDLOG plogfunc)
		:TTrdItfBase(psetupfile,plogfunc)
{
	FUDLFile = "";
	FPTrdDllVersion = 0;
	FDllName = "PTrdDll_RM.dll";
	FServerInfo = "127.0.0.1:2005";
	FItfTrd = NULL;
	FItfTrd1 = NULL;
	DataModule1 = NULL;
	FAccount="";
}

TTrdItf_TrdSvr::~TTrdItf_TrdSvr()
{
	this->CloseLink();
}

int  TTrdItf_TrdSvr::Init()         //初始化
{
	int ret = 0;

	if( DataModule1 == NULL )
	{
		DataModule1 = new TDataModule1(NULL);
		if( DataModule1->ConnectToDB(FUDLFile) != true )
			return -1;
	}

	if( FPTrdDllVersion == 1 )
	{
		// new version 1 PTRDdll.dll
		if( FItfTrd1 != NULL )
		{
			this->CloseLink();
		}

		FItfTrd1 = new PTRDDLL1::TItfTrd1(false,NULL, FDllName.c_str() );
		FItfTrd1->Open();

		int p = FServerInfo.Pos(":");
		ret = FItfTrd1->Init(LeftStr(FServerInfo,p-1).c_str(),
			RightStr(FServerInfo,FServerInfo.Length()-p).c_str());
	}
	else if(  FPTrdDllVersion == 3 )
	{
		if( FItfTrd != NULL )
		{
			this->CloseLink();
		}

		FItfTrd = new TItfTrd( FDllName.c_str() );
		FItfTrd->Open();
		ret = FItfTrd->Init(FServerInfo.c_str());
	}
	else
	{
		this->SetLastError(-1,'E',PLUGINNAME,"Do not support the version interface (%d)",FPTrdDllVersion) ;
		ret = -2;
	}

	return ret;
}

int  TTrdItf_TrdSvr::SetAccount()   //登录柜台中间件
{
	FAccount = FRequest.SetAccount.Account;
	int ret = -1;
	switch( FPTrdDllVersion )
	{
		case 1:
		{
			PTRDDLL1::TAccountSort as;
			if( FItfTrd1 == NULL )
			{
				this->SetLastError(-1,'E',PLUGINNAME,"FItfTrd1 == NULL") ;
				return -1;
			}

			switch (FRequest.SetAccount.LoginType) {
				case asSHA : as = PTRDDLL1::asSH; break;
				case asSZA : as = PTRDDLL1::asSZ; break;
				case asJJS : as = PTRDDLL1::asJJS;break;
				case asCA  : as = PTRDDLL1::asCA;break;
			default:
				as = PTRDDLL1::asCA;
			}
			ret= FItfTrd1->SetAccount( FRequest.SetAccount.Account,as,
																	 FRequest.SetAccount.PW);
			if( ret == 0 )
			{
				FQryOrder.set_param(FItfTrd1,DataModule1,FAccount) ;
				SetAccountByType(FRequest.SetAccount.LoginType,FRequest.SetAccount.Account,
					FRequest.SetAccount.PW);
			}
			break;
		}
		case 3:
			if( FItfTrd == NULL )
			{
				this->SetLastError(-1,'E',PLUGINNAME,"FItfTrd3 == NULL") ;
				return -1;
			}
			ret =  FItfTrd->Login( FRequest.SetAccount.Account,
															FRequest.SetAccount.LoginType,
															FRequest.SetAccount.PW);

			if( ret == 0 )
			{
				SetAccountByType(FRequest.SetAccount.LoginType,FRequest.SetAccount.Account,
					FRequest.SetAccount.PW);
			}
			break;
		default:
			return -1;
	}

	return ret ;
}
//////查询函数//////
int  TTrdItf_TrdSvr::QryMoney()     //资金查询
{
	int ret = -100;
	if( FPTrdDllVersion == 1)
	{
		if( this->FItfTrd1 == NULL ) return -1;
		TMoneyInfo mi;
		double b,a;
		mi.MoneyType = motRMB;
		ret = FItfTrd1->QryMoney(b,a);
		if( ret == 0)
		{
			NewAns(1);
			mi.balance = b;
			mi.available =a;
			memcpy(&((*FAnswer)[0].QryMoney.MoneyInfo),&mi,sizeof(TMoneyInfo));
		}
	}
	else if( FPTrdDllVersion == 3)
	{
		if( FItfTrd == NULL )
		{
			this->SetLastError(-1,'E',PLUGINNAME,"FItfTrd3 == NULL") ;
			return -1;
		}

		TMoneyInfo mi;
		ret = FItfTrd->QryMoney( FRequest.QryMoney.MoneyType,mi);
		if( ret == 0)
		{
			NewAns(1);
			memcpy(&((*FAnswer)[0].QryMoney.MoneyInfo),&mi,sizeof(TMoneyInfo));
		}
	}
	return ret;
}

int  TTrdItf_TrdSvr::QryCurCsn()		//当日委托查询
{
	int ret = -100;
	TOrderInfo *poi =NULL;
	int num = FRequest.QryCurCsn.MaxRecord;;
	if( FPTrdDllVersion == 1 || FPTrdDllVersion == 0 )  // manual ,1.0
	{
		// query from database
		if( DataModule1 == NULL )
		{
			this->SetLastError(-1,'E',PLUGINNAME,"Database not available.") ;
			return -1;
		}
		ret = DataModule1->GetOrders(FAccount,FRequest.QryCurCsn.OrderID,
			FRequest.QryCurCsn.SeqNum,&poi,num);
		if( ret==0 )
		{
			if( num > 0 )
			{
				NewAns(num);
				for(int i=0;i<num;i++)
				{
					memcpy(&((*FAnswer)[i].QryCurCsn.OrderInfo),&poi[i],sizeof(TOrderInfo));
				}
			}
			if( poi!= NULL )
				delete [] poi;
		}
	}
	else if (FPTrdDllVersion == 3)
	{
		if( FItfTrd == NULL )
		{
			this->SetLastError(-1,'E',PLUGINNAME,"FItfTrd3 == NULL") ;
			return -1;
		}
		ret = FItfTrd->QryOrder( FRequest.QryCurCsn.OrderID,
				FRequest.QryCurCsn.SeqNum,&poi,num);
		if( ret==0 )
		{
			if( num > 0 )
			{
				NewAns(num);
				for(int i=0;i<num;i++)
				{
					memcpy(&((*FAnswer)[i].QryCurCsn.OrderInfo),&poi[i],sizeof(TOrderInfo));
				}
			}
			if( poi!= NULL )
				FItfTrd->FreeAnswer(poi);
		}
	}
	return ret;
}
	
int  TTrdItf_TrdSvr::QryCurTrd()    //当日成交查询
{
	int ret = -100;
	TTradeInfo * pti =NULL;
	int num=FRequest.QryCurTrd.MaxRecord;
		
	if( FPTrdDllVersion == 1 || FPTrdDllVersion == 0 )  // manual ,1.0
	{
		if( DataModule1 == NULL )
		{
			this->SetLastError(-1,'E',PLUGINNAME,"Database not available.") ;
			return -1;
		}

		// query from database
		ret = DataModule1->GetOrderReports(FAccount,FRequest.QryCurTrd.OrderID,
			FRequest.QryCurTrd.SeqNum,&pti,num);

		if( ret==0 )
		{
			if( num > 0 )
			{
				NewAns(num);
				for( int i =0 ;i<num;i++)
					memcpy(&((*FAnswer)[i].QryCurTrd.TrdInfo),&pti[i],sizeof(TTradeInfo));
			}
			if( pti!= NULL )
				delete [] pti;
		}
	}
	else if (FPTrdDllVersion == 3)
	{
		if( FItfTrd == NULL )
		{
			this->SetLastError(-1,'E',PLUGINNAME,"FItfTrd3 == NULL") ;
			return -1;
		}
		ret = FItfTrd->QryTrade(FRequest.QryCurTrd.OrderID,
			FRequest.QryCurTrd.SeqNum,&pti,num);
		if( ret == 0)
		{
			if( num > 0 )
			{
				NewAns(num);
				for( int i =0 ;i<num;i++)
					memcpy(&((*FAnswer)[i].QryCurTrd.TrdInfo),&pti[i],sizeof(TTradeInfo));
			}
			if( pti!= NULL )
				FItfTrd->FreeAnswer(pti);
		}
	}
	return ret;
}

int  TTrdItf_TrdSvr::QryStocks()    //查询帐号中所有的股份
{
	int ret  = -100;
	if( FPTrdDllVersion ==1 )
	{
		if( FItfTrd1 == NULL ) return -1;if( FItfTrd1 == NULL )
		{
			this->SetLastError(-1,'E',PLUGINNAME,"FItfTrd1 == NULL") ;
			return -1;
		}

		PTRDDLL1::TStockInfo * pSi = NULL;
		int num =0;

		PTRDDLL1::TBourse bs;
		switch(FRequest.QryStocks.Market)
		{
			case mtSHA : bs = PTRDDLL1::bsSH; break;
			case mtSZA : bs = PTRDDLL1::bsSZ; break;
			case mtJJS : bs = PTRDDLL1::bsJJS;break;
			default:
			{
				this->SetLastError(-1,'E',PLUGINNAME,"Not support %c marker type.",FRequest.Undo.Market) ;
				return -1;
			}
		}
		ret = FItfTrd1->QryStocks(&pSi,num,bs);
		if( ret == 0 && num >0  )
		{
			NewAns( num );
			TStockInfo si;
			for (int i = 0; i < num; i++)
			{
				lstrcpyn(si.SecuID ,pSi[i].SecuID, CODE_LEN);
				lstrcpyn(si.Account,FAccount.c_str(),ACC_LEN);
				si.PosDir = pdNo;
				si.Market = mtNo;
				si.Balance = pSi[i].Balance;
				si.PosNum = 0;
				si.Available = pSi[i].Available;
				si.CostPrice = pSi[i].CostPrice;
				si.CurPrice = pSi[i].CurPrice;
				memcpy(&(*FAnswer)[i].QryStocks.StockInfo, &si, sizeof(TStockInfo));
			}
			FItfTrd1->FreeAnswer(pSi);
		}
	}
	else if( FPTrdDllVersion == 3)
	{
		if( FItfTrd == NULL )
		{
			this->SetLastError(-1,'E',PLUGINNAME,"FItfTrd3 == NULL") ;
			return -1;
		}
		TStockInfo * pSi = NULL;
		int num = 0;
		ret= FItfTrd->QryStocks(FRequest.QryStocks.Market,&pSi,num);
		if( ret == 0)
		{
			if( num > 0 )
			{
				NewAns( num );
				for (int i = 0; i < num; i++)
				{
						memcpy(&(*FAnswer)[i].QryStocks.StockInfo, &pSi[i], sizeof(TStockInfo));
				}
				FItfTrd->FreeAnswer(pSi);
			}
		}
	}
	return ret;
}
	
int  TTrdItf_TrdSvr::GetLastError()	 //获取最后错误
{
	int ret  = 0;
	char errtxt[1024];
	char sender[256];
	if( FPTrdDllVersion == 1)
	{
		if( FItfTrd1 == NULL )
		{
			this->SetLastError(-1,'E',PLUGINNAME,"FItfTrd1 == NULL") ;
			return 0;
		}

		ret = FItfTrd1->GetLastError(errtxt,sender);
		if( ret != 0 )
		{
			this->SetLastError(-2,'E',PLUGINNAME,"ItfTrd1 Error,sender=%s,msg=%s",sender,
				errtxt) ;
		}
	}
	else if( FPTrdDllVersion == 3 )
	{
		if( FItfTrd == NULL ) return -1;
		ret = FItfTrd->GetLastError(errtxt,1023,sender,99);
		if( ret != 0 )
		{
			this->SetLastError(-2,'E',PLUGINNAME,"ItfTrd3 Error,sender=%s,msg=%s",sender,
				errtxt) ;
		}
	}

	if(FLastError.ErrorCode != 0 )
	{
		NewAns(1);
		memcpy( &( *FAnswer )[0].GetLastError.Error,&FLastError,sizeof(FLastError));
	}
	return 0;
}
	
//////交易函数/////
int  TTrdItf_TrdSvr::Order()        //委托
{
	int ret= -100;
	char ordid[SEQ_LEN+1];
	if( FPTrdDllVersion == 0 )  // manual
	{
		// add the order to db
		if( DataModule1 == NULL ) return -2;
		__int64 oid = DataModule1->AddOrder( FAccount,
			FRequest.Order.SecuID,
			FRequest.Order.Price,
			FRequest.Order.Num,"0",
			String(FRequest.Order.Type),
			String( FRequest.Order.Market),
			oswb);
		if( oid >0 )
		{
			NewAns(1);
			lstrcpyn((*FAnswer)[0].Order.ContractID, IntToStr(oid).c_str(),SEQ_LEN);
			return 0;
		}
		else
		{
			this->SetLastError(-1,'E',PLUGINNAME,"DataModule1->AddOrder Order Failed.") ;
			return -1;
		}
	}
	else if (FPTrdDllVersion == 1)
	{
		if( DataModule1 == NULL ) return -2;
		if( FItfTrd1 == NULL )
		{
			this->SetLastError(-1,'E',PLUGINNAME,"FItfTrd1 == NULL") ;
			return -1;
		}
		char bs =  ' ';
		int type = 0;
		switch( FRequest.Order.Type )
		{
			case otBuy      : bs = 'B'; type = 0; break;
			case otSell     : bs = 'S'; type = 0; break;
			case otETFSub   : bs = 'B'; type = 1; break;
			case otETFRed   : bs = 'S'; type = 1; break;
			case otOpenBuy  : bs = 'B'; type = 0; break;
			case otOpenSell : bs = 'S'; type = 0; break;
			case otCloseBuy : bs = 'B'; type = 1; break;
			case otCloseSell: bs = 'S'; type = 1; break;
			default:
			{
				this->SetLastError(-1,'E',PLUGINNAME,"Do not support this order type %c.",FRequest.Order.Type) ;
				return -1;
			}
		}

		/*
		type 的用法

		type = 1  表示申购赎回命令

		set 开平标志 as a
		0  开仓
		1  平仓
		2  平今

		set 投保标志 as b
		0  投机
		1  保值

		type = a + b<<4 表示开平和投保的组合

		*/
		if( bs == 'B' )
			ret = FItfTrd1->Buy(FRequest.Order.SecuID,FRequest.Order.Price,FRequest.Order.Num,
				ordid,type);
		else if (bs == 'S') {
			ret = FItfTrd1->Sell(FRequest.Order.SecuID,FRequest.Order.Price,FRequest.Order.Num,
				ordid,type);
		}
		if( ret ==0 )
		{

			__int64 oid = DataModule1->AddOrder( FAccount,
				FRequest.Order.SecuID,
				FRequest.Order.Price,
				FRequest.Order.Num,ordid,
				String( (char)FRequest.Order.Type),
				String( (char)FRequest.Order.Market),
				oswb);
			if( oid >0 )
			{
				TOrderInfo oi;
				ZeroMemory(&oi,sizeof(TOrderInfo));
				lstrcpyn(oi.ContractID,ordid,SEQ_LEN);
				lstrcpyn(oi.SecuID,FRequest.Order.SecuID,CODE_LEN);
				oi.Market = FRequest.Order.Market;
				oi.Time = StrToInt(Time().FormatString("hhnnss"));
				oi.Date = StrToInt(Date().FormatString("yyyymmdd"));
				oi.Type = FRequest.Order.Type;
				oi.State = osyb;
				oi.CsnVol =  FRequest.Order.Num;
				oi.TrdVol = 0;
				oi.CancelVol = 0;
				oi.CsnPrice =FRequest.Order.Price;
				oi.TrdPrice = 0;
				//oi.Account=FAccount;
				//oi.SeqNum;
				FQryOrder.add_order(oi,oid);
				NewAns(1);
				lstrcpyn((*FAnswer)[0].Order.ContractID, IntToStr(oid).c_str(),SEQ_LEN);
				return 0;
			}
			else
			{
				this->SetLastError(-1,'E',PLUGINNAME,"DataModule1->AddOrder Order Failed,ordid = %s",ordid) ;
				return -1;
			}
		}

	}
	else if( FPTrdDllVersion == 3)
	{
		if( FItfTrd == NULL )
		{
			this->SetLastError(-1,'E',PLUGINNAME,"FItfTrd3 == NULL") ;
			return -1;
		}
		ret= FItfTrd->Order( FRequest.Order.SecuID,
													 FRequest.Order.Price,
													 FRequest.Order.Num,
													 FRequest.Order.Market,
													 FRequest.Order.Type,
													 ordid,SEQ_LEN);
		if( ret ==0 )
		{
			NewAns(1);
			lstrcpyn((*FAnswer)[0].Order.ContractID, ordid,SEQ_LEN);
			return 0;
		}
	}

	return ret;
}

int  TTrdItf_TrdSvr::Undo()        //委托撤单
{
	if( FPTrdDllVersion == 0 )  // manual
	{
		// add the order to db
		if( DataModule1 == NULL ) return -2;
		if( DataModule1->CancelOrder( StrToInt64(FRequest.Undo.ContractID) ) )
		{
			return 0;
		}
		else
		{
			this->SetLastError(-1,'E',PLUGINNAME,"DataModule1->CancelOrder %d failed.",FRequest.Undo.ContractID) ;
			return -1;
		}
	}
	else if (FPTrdDllVersion == 1)
	{
		if( FItfTrd1 == NULL )
		{
			this->SetLastError(-1,'E',PLUGINNAME,"FItfTrd1 == NULL") ;
			return -1;
		}

		PTRDDLL1::TBourse bs;
		switch(FRequest.Undo.Market)
		{
			case mtSHA : bs = PTRDDLL1::bsSH; break;
			case mtSZA : bs = PTRDDLL1::bsSZ; break;
			case mtJJS : bs = PTRDDLL1::bsJJS;break;
			default:
			{
				this->SetLastError(-1,'E',PLUGINNAME,"Not support %c marker type.",FRequest.Undo.Market) ;
				return -1;
			}
		}
		return FItfTrd1->Undo(FRequest.Undo.ContractID,bs);
	}
	else if (FPTrdDllVersion == 3)
	{
		if( FItfTrd == NULL )
		{
			this->SetLastError(-1,'E',PLUGINNAME,"FItfTrd3 == NULL") ;
			return -1;
		}
		return FItfTrd->Undo( FRequest.Undo.ContractID, FRequest.Undo.Market);
	}

	return -100;
}

//将配置信息读出来,如果没有获取完整的配置信息返回false
bool TTrdItf_TrdSvr::GetConfig(void)
{
	if( FSetupFile== NULL ) return false;

	TMemIniFile *ini = new TMemIniFile( FSetupFile );
	try
	{
		// 判断是否存在插件的设置，没有的话返回false以便系统能够生成默认的设置
		if( ini->SectionExists(PLUGINNAME) == false ) return false;
		FServerInfo = ini->ReadString(PLUGINNAME,"ServerInfo",FServerInfo);
		FUDLFile = ini->ReadString(PLUGINNAME,"DBUDLFile",FUDLFile);
		FDllName = ini->ReadString(PLUGINNAME,"PTrdDllName",FDllName);
		FPTrdDllVersion =ini->ReadInteger(PLUGINNAME,"PTrdDllVersion",FPTrdDllVersion);
	}
	__finally
	{
		delete ini;
	}
	return true;
}
//将配置信息回写到配置文件
void TTrdItf_TrdSvr::SetConfig(void)
{
	if( FSetupFile== NULL ) return ;

	TMemIniFile *ini = new TMemIniFile( FSetupFile );
	try
	{
		ini->WriteString(PLUGINNAME,"ServerInfo",FServerInfo);
		ini->WriteString(PLUGINNAME,"DBUDLFile",FUDLFile);
		ini->WriteString(PLUGINNAME,"PTrdDllName",FDllName);
		ini->WriteInteger(PLUGINNAME,"PTrdDllVersion",FPTrdDllVersion);

		ini->UpdateFile();
	}
	__finally
	{
		delete ini;
	}
}
//关闭中间件链接
void TTrdItf_TrdSvr::CloseLink(void)
{
	if( FItfTrd != NULL )
	{
		FItfTrd->Close();
		delete FItfTrd;
		FItfTrd = NULL;
	}

	if( FItfTrd1 != NULL )
	{
		FItfTrd1->Close();
		delete FItfTrd1;
		FItfTrd1 = NULL;
	}

	if( DataModule1 != NULL )
	{
		delete DataModule1;
		DataModule1=NULL;
	}
}

int  TTrdItf_TrdSvr::KeepAlive(void)
{
	if( FPTrdDllVersion == 1 )
	{
		this->FQryOrder.do_query();
	}
	return 0;
}
