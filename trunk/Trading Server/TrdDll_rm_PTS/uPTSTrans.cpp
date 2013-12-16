//---------------------------------------------------------------------------
#pragma hdrstop
#include <comdef.h>
#include <stdio.h>
#include <vector>

#include "xSystem.h"
#include "uPTSTrans.h"

using namespace std;

#pragma package(smart_init)

const WideString DEFAULT_MEMO = L"PTrdDLL";
template <class T> T* NewAns(int n)
{
	 return new T[n];
};

void __stdcall _com_issue_error(HRESULT hr) throw(_com_error)
{
	IErrorInfo *pErr;
	GetErrorInfo( 0, &pErr );
	_com_error err(hr,pErr);

	String msg;
	if( pErr != NULL )
		msg.printf("COM´íÎó:(%s),ÃèÊö:(%s)",err.ErrorMessage(),
			String((wchar_t*)err.Description()).c_str());
	else
		msg.printf("COM´íÎó:(%s),ÃèÊö:(ÎÞ)",err.ErrorMessage());
	throw(EOleException(msg,err.Error(),
		String((wchar_t*)err.Source()),"",0));
}

inline void TESTHR(HRESULT x) { if FAILED(x) _com_issue_error(x); };

//---------------------------------------------------------------------------

TPTSItf::TPTSItf()
{
	FSession = new TPTSSession(NULL);
	FTCS = new TTradeCoreSvc(NULL);
	FTCS->GetDefaultInterface()->QueryInterface<ITradeCoreSvc2>(&FTCS2);
	FAccount  = NULL;
	ZeroMemory(&FAccInfo,sizeof(TAccountInfo));

	FError.ErrorCode = 0;
	lstrcpy(FError.Sender, "BHPTS");
	FError.Text[0] = 0;
}

TPTSItf::~TPTSItf()
{
	if(FAccount!=NULL )
	{
		FAccount->Release();
		FAccount=NULL;
	}

	delete FTCS;
}

void TPTSItf::init(WideString domain,WideString server,WideString trader)
{
	FServerName = server;
	FDomain     = domain;
	FTrader     = trader;
}

int TPTSItf::login(WideString account,WideString password,TAccountSort as)
{
	int ret = 0;
	FAccSort = as;
	ICustomer * pCus = NULL;
	IAccounts * pAccs= NULL;

	if(FAccount!=NULL )
	{
		FAccount->Release();
		FAccount=NULL;
	}

	try
	{
		if( ! FSession->IsLogin )
		{
			TESTHR(FSession->GetDefaultInterface()->Login( tcLoginTypePTS,FTrader,FDomain,password,
				FServerName,2,3));

			FTCS->SetSession(FSession->GetDefaultInterface());
		}
		//²éÕÒÕÊ»§

		long accid;
		if( account.Length() > 0 )
			accid = _wtoi(account.c_bstr());
		else
			return -1;
			
		for(long i=0;i<FTCS->Customers->Count;i++)
		{
			FTCS->Customers->get_Item( Variant(i), &pCus);
			if( (ICustomer*)pCus == NULL )
			{
				continue;
			}
			else
			{
				pCus->GetAccounts(&pAccs);
				pCus->Release();
				pCus = NULL;
				if( (IAccounts*)pAccs!=NULL )
				{
					pAccs->Find(accid,&FAccount);
					pAccs->Release();
					pAccs = NULL;
					if(  (IAccount*)FAccount != NULL  )
						break;
				}
			}
		}
		if( (IAccount*)FAccount == NULL )
			ret = -2;
		else
			sprintf( FAccInfo.Capital, "%d",FAccount->AccountID);
	}
	catch( Exception &e )
	{
#ifdef _DEBUG
		xErrBox("µÇÂ¼Ê§°Ü£¬´íÎóÐÅÏ¢:" + e.Message);
#endif
		SetLastError( e.Message.c_str(),-1);
		ret = -1;
	}

	if( pCus!=NULL)
	{
		pCus->Release();
		pCus = NULL;
	}

	if( pAccs!=NULL )
	{
		pAccs->Release();
		pAccs = NULL;
	}

	return ret;
}

int TPTSItf::QryMoney(double &Balance,double &Available)
{
	if( (IAccount*)FAccount == NULL ) return -1;
	IAccountDetail* pAccd=NULL;
	HRESULT hr = FAccount->GetDetail(tcCurrencyTypeRMB,&pAccd);
	if(SUCCEEDED(hr) &&  pAccd != NULL )
	{
		pAccd->get_Yesterday(&Balance);
		pAccd->get_Available(&Available);
		pAccd->Release();
		pAccd=NULL;
		return 0;
	}
	return -2;
}

int TPTSItf::QryDetail(char * ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum)
{
	if( FTCS2 == NULL ) return -1;
	IOrder *pord = NULL;
	FTCS2->GetOrder(WideString(ContractID).c_bstr(),&pord);
	if( pord != NULL )
	{
		Price = pord->ExecAvgPrice ;
		Num   = pord->ExecQty;

		switch (pord->OrderStatus)
		{
			case tcOrderStatusFilled :
			case tcOrderStatusRejected :
				UndoNum = -(pord->Quantity-pord->ExecQty);
				break;
			default:
				UndoNum = 0;
		}

		pord->Release();
		return 0;
	}
	else return -2;
}

int TPTSItf::QryCurCsn(TConsignInfo **CsgInfo,int &Num)
{
	if( (IAccount*)FAccount == NULL ) return -1;
	long index = 0;
	IOrders *pords = NULL;
	IOrder  *pord  = NULL;

	vector< TConsignInfo > tis;
	TConsignInfo ti;
	do
	{
		FAccount->GetWorkingOrders(&index,100, &pords);
		if( ((IOrders*)pords != NULL) && (pords->Count>0) )
		{
			for(long i=0;i<pords->Count;i++)
			{
				pords->get_Item(Variant(i),&pord);
				if((IOrder*)pord != NULL )
				{
					ZeroMemory(&ti,sizeof(ti));
					lstrcpyn(ti.SecuID,String(pord->InstrumentID).c_str(), 8);
					lstrcpyn(ti.Time,String(pord->OrderTime).c_str(),9);
					ti.SecuDesc[0]=0;
					lstrcpyn(ti.Date,String(pord->OrderDate).c_str(),9);
					ti.CsnVol = pord->Quantity;
					ti.CsnPrice = pord->Price;
					ti.TrdVol = pord->ExecQty;
					ti.TrdPrice = pord->ExecAvgPrice;

					switch (pord->Side)
					{
						case tcOrderSideUnknown:
							ti.Type  = 'N';
						break;
						case tcOrderSideBuy:
							ti.Type  = 'B';
						break;
						case tcOrderSideSell:
							ti.Type  = 'S';
						break;
					}

					switch (pord->InstIDSource)
					{
						case 101:
							ti.Bourse =  0;
						break;
						case 102:
							ti.Bourse =  1;
						break;
						case 106:
							ti.Bourse =  2;
						break;
					}

					switch (pord->OrderStatus)
					{
						case tcOrderStatusFilled :
						case tcOrderStatusRejected :
							ti.CancelVol = -(pord->Quantity-pord->ExecQty);
							break;
						default:
							ti.CancelVol = 0;
					}

					switch (tcOrderStatusFilled) {
						case tcOrderStatusNew:
							ti.State = wswb;
						break;
						case tcOrderStatusPartFilled:
							ti.State = wsbc;
						break;
						case tcOrderStatusFilled:
							ti.State = wscj;
						break;
						case tcOrderStatusRejected:
							ti.State = wsyf;
						break;
						case tcOrderStatusPendingNew:
							ti.State = wswb;
						break;
						case tcOrderStatusAccepted:
							ti.State = wsyb;
						break;
						case tcOrderStatusUnknown:
							ti.State = wsno;
						break;
          default:
						ti.State = wsno;
					}

					lstrcpyn(ti.ContractID,String(pord->OrderID).c_str(),8);

					tis.push_back(ti);

					pord->Release();
					pord = NULL;
				}
			}
		}
		else
		{
			if( pords != NULL )
			{
				pords->Release();
				pords = NULL;
			}
			break;
		}

		if( pords != NULL )
		{
			pords->Release();
			pords = NULL;
		}
	}
	while( 1 );

	Num = tis.size();
	if( Num>0 )
	{
		*CsgInfo = NewAns<TConsignInfo>(Num);
		for( size_t i=0;i<tis.size();i++)
		{
			memcpy(&(*CsgInfo)[i],&tis[i],sizeof(TConsignInfo));
		}
	}
	else
		*CsgInfo = NULL;

	return 0;
}

int TPTSItf::QryCurTrd(TTradeInfo **TrdInfo,int &Num)
{
	if( (IAccount*)FAccount == NULL ) return -1;
	WideString date = FormatDateTime("yyyymmdd",Date());
	WideString st   = "00:00:00";
	WideString en   = "23:59:59";
	long index = 0;
	IOrders* pords = NULL;
	IOrder*  pord=NULL;

	vector< TTradeInfo > tis;
	TTradeInfo ti;
	do
	{
		FAccount->GetFilledOrders(date.c_bstr(),st.c_bstr(),en.c_bstr(),&index,100, &pords);
		if( (pords != NULL) && (pords->Count>0) )
		{
			for(long i=0;i<pords->Count;i++)
			{
				pords->get_Item(Variant(i),&pord);
				if(pord != NULL )
				{
					ZeroMemory(&ti,sizeof(ti));
					lstrcpyn(ti.SecuID,String(pord->InstrumentID).c_str(), 8);
					lstrcpyn(ti.Time,String(pord->OrderTime).c_str(),9);
					ti.SecuDesc[0]=0;
					lstrcpyn(ti.Date,String(pord->OrderDate).c_str(),9);
					ti.Vol = pord->ExecQty;
					ti.Price=pord->ExecAvgPrice;

					switch (pord->Side)
					{
						case tcOrderSideUnknown:
							ti.Type  = 'N';
						break;
						case tcOrderSideBuy:
							ti.Type  = 'B';
						break;
						case tcOrderSideSell:
							ti.Type  = 'S';
						break;
					}
					tis.push_back(ti);

					pord->Release();
					pord = NULL;
				}
			}
		}
		else
		{
			if( pords != NULL )
			{
				pords->Release();
				pords = NULL;
			}
			break;
		}

		if( pords != NULL )
		{
			pords->Release();
			pords = NULL;
		}

	}
	while( 1 );

	Num = tis.size();
	if( Num>0 )
	{
		*TrdInfo = NewAns<TTradeInfo>(Num);
		for( size_t i=0;i<tis.size();i++)
		{
			memcpy(&(*TrdInfo)[i],&tis[i],sizeof(TTradeInfo));
		}
	}
	else
		*TrdInfo = NULL;

	return 0;
}

int TPTSItf::QryStocks(TStockInfo **StockInfo,int &Num,TBourse Bourse)
{
	if( (IAccount*)FAccount == NULL ) return -1;

	int src = 0;
	switch (Bourse)
	{
		case bsSH:
			src = 101;
		break;
		case bsSZ:
			src = 102;
		break;
		case bsJJS:
			src = 106;
		break;
	}
	
	long index = 0;
	IPositions* pposs = NULL;
	IPosition*  ppos;

	vector< TStockInfo > tis;
	TStockInfo ti;
	do
	{
		FAccount->GetPositions(&index,100,&pposs);
		if( (pposs != NULL) && (pposs->Count>0) )
		{
			for(long i=0;i<pposs->Count;i++)
			{
				pposs->get_Item(Variant(i),&ppos);
				if(ppos != NULL )
				{
					ZeroMemory(&ti,sizeof(ti));
					if( ppos->InstIDSource == src )
					{
						lstrcpyn(ti.SecuID+1,String(ppos->InstID).c_str(), 8);
						ti.SecuDesc[0]=0;
						ti.BuyFreeze=0;
						ti.SellFreeze=0;
						ti.AbnorFreeze=0;
						ti.ProfitAndLoss=0;

						if( src == 106 )
						{
							ti.SecuID[0]='J';
							switch (ppos->Direction)
							{
							case tcPositionDirectionLong:
							{
								ti.Balance = ppos->ForClose;
								ti.Available=0;
								ti.Cost=0;
								ti.CostPrice=ppos->BuyAvgPrice;
								ti.CurVal=0;
								ti.CurPrice=0;
								tis.push_back(ti);
							}
							break;
							case tcPositionDirectionShort:
							{
								ti.Balance=0;
								ti.Available = ppos->ForClose;
								ti.Cost=0;
								ti.CostPrice=0;
								ti.CurVal=0;
								ti.CurPrice = ppos->BuyAvgPrice;
								tis.push_back(ti);
							}
							break;
							}
						}
						else
						{
							if( src == 101 )
								ti.SecuID[0]='H';
							else if( src == 102 )
								ti.SecuID[0]='S';
							else
                            	ti.SecuID[0]='N';
							ti.Balance  =ppos->Position;
							ti.Available=ppos->ForSale;
							ti.Cost     =ppos->PositionCost;
							ti.CostPrice=ppos->BuyAvgPrice;
							ti.CurVal   =0;
							ti.CurPrice =0;
							tis.push_back(ti);
						}
					}
					ppos->Release();
					ppos = NULL;
				}
			}
		}
		else
		{
			if( pposs!= NULL )
			{
				pposs->Release();
				pposs = NULL;
			}
			break;
		}

		if( pposs!= NULL )
		{
			pposs->Release();
			pposs = NULL;
		}
	}
	while( 1 );

	Num = tis.size();
	if( Num>0 )
	{
		*StockInfo = NewAns<TStockInfo>(Num);
		for( size_t i=0;i<tis.size();i++)
		{
			memcpy(&(*StockInfo)[i],&tis[i],sizeof(TStockInfo));
		}
	}
	else
		*StockInfo = NULL;

	return 0;
}

int TPTSItf::BuyOrSell(WideString SecuID,double Price,int Num,
											 WideString &ContractID,short type,TcOrderSide side)
{
	if( (IAccount*)FAccount == NULL ) return -1;

	if( SecuID.Length()  < 2) return -1;

	int src = 0;

	switch (SecuID[1]) {
		case L'H':
			src = 101;
		break;
		case L'S':
			src = 102;
		break;
		case L'J':
			src = 106;
		default:
			src = 106;
	}

	SecuID.Delete(1,1);

	int ret  = 0;
	IOrders *pords = NULL;
	FAccount->NewOrders(&pords);

	if( pords!= NULL )
	{
		IOrder *pord = NULL;
		pords->Add(&pord);
		if( pord!= NULL )
		{
			if( src == 101 || src ==102 )
			{
				switch(type)
				{
					case 0: //buy s
					{
						pord->OrderType   = tcOrderTypeLimit;
						pord->InstrumentID= SecuID;
						pord->InstIDSource= src;
						pord->Side        = side;
						pord->Quantity    = Num;
						pord->Price       = Price;
						pord->Text        = DEFAULT_MEMO;
						pord->CreditTrading=tcCreditTradingNo;
					}
					break;
					case 1: //Éê¹º Êê»Ø
					{
						pord->OrderType   = tcOrderTypeNonTrading;
						pord->InstrumentID= SecuID;
						pord->InstIDSource= src;
						pord->Side        = side;
						pord->Quantity    = Num;
						pord->Price       = Price;
						pord->Text        = DEFAULT_MEMO;
						if( side == tcOrderSideSell )
							pord->NonTradingType= tcNonTradingOrderER;
						else if( side == tcOrderSideBuy )
							pord->NonTradingType= tcNonTradingOrderEC;
						else
							pord->NonTradingType= tcNonTradingOrderUnknown;
					}
					break;
				}
			}
			else if( src == 106 )
			{
				switch(type & 0x000F )
				{
					case 0:  //open
						pord->PositionEffect= tcPositionEffectOpen;
					break;
					case 1:  //close
						pord->PositionEffect= tcPositionEffectClose;
					break;
					case 2:  //close today
						pord->PositionEffect= tcPositionEffectCloseToday;
					break;
				}
				pord->Side=side;
				pord->OrderType=tcOrderTypeLimit;
				pord->InstrumentID= SecuID;
				pord->InstIDSource= src;
				pord->Quantity=Num;
				pord->Price=Price;
				pord->Text= DEFAULT_MEMO;
			}
			else
				ret = -4;
		}
		else
			ret = -3;

		if( ret == 0)
		{
			long errindex = -1;
			pords->Commit(tcCommitModeAbort,&errindex);
			if( errindex >=0 )
			{
				ret = -5;
#ifdef _DEBUG
				xErrBox(pord->RejectReason);
#endif
				SetLastError( String(pord->RejectReason).c_str(),-5);
			}
			else
			{
				ContractID = pord->OrderID;
			}
		}
		if( pord ) pord->Release();
		pords->Release();
	}
	else return -2;
	return ret;
}

int TPTSItf::Undo(WideString ContractID,TBourse Bourse)
{
	if( FTCS2 == NULL ) return -1;
	IOrder *pord = NULL;

	FTCS2->GetOrder(WideString(ContractID).c_bstr(),&pord);
	if( pord != NULL )
	{
		if(! SUCCEEDED(pord->Cancel()) )
		{
			pord->Release();
			SetLastError( "³·µ¥Ê§°Ü",-3);
			return -3;
		}
		pord->Release();
		return 0;
	}
	else
	{
		SetLastError( "Î´ÕÒµ½¸ÃÎ¯ÍÐ",-2);
		return -2;
	}

}

int TPTSItf::GetCapitalAcc(WideString &Acc)
{
	if( (IAccount*)FAccount == NULL ) return -1;
	Acc = IntToStr(FAccount->AccountID);
	return 0;
}

int TPTSItf::SetAccInfo(TAccountInfo *AccInfo)
{
	memcpy(&FAccInfo,AccInfo,sizeof(TAccountInfo));
	return 0;
}

int TPTSItf::GetAccInfo(TAccountInfo *AccInfo)
{
	memcpy(AccInfo,&FAccInfo,sizeof(TAccountInfo));
	return 0;
}

void TPTSItf::FreeAnswer(void *mem)
{
	if( mem!= NULL )
		delete[] mem;
}

int TPTSItf::GetLastError(char *ErrorText,char *Sender)
{
	lstrcpy(Sender, FError.Sender);
	lstrcpyn(ErrorText , FError.Text,MAX_TEXT);
	return FError.ErrorCode;
}

void TPTSItf::SetLastError(char* ErrorText,long errcode)
{
	FError.ErrorCode = errcode;
	lstrcpyn(FError.Text,ErrorText,MAX_TEXT);
}

