//---------------------------------------------------------------------------
#pragma hdrstop

#include <SysUtils.hpp>
#include <math.hpp>
#include <stdlib.h>
#include <inifiles.hpp>
#include <assert.h>
#include "uTrdItf_Test.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//static variable
vector<TOrderInfo> TTrdItfTest::m_orders;
vector<TTradeInfo> TTrdItfTest::m_deals;
LONG TTrdItfTest::m_Order_ID = 0;
LONG TTrdItfTest::m_trd_id = 0;
CRITICAL_SECTION TTrdItfTest::m_CS;
LONG TTrdItfTest::m_ref_count=0;

long convert_time_to_long( String stime)
{
	char *pstr = stime.c_str();
	char tmp[100];
	int j = 0;
	for(int i=0;i<stime.Length();i++)
	{
		if( pstr[i] !=':')
		{
			tmp[j++] = pstr[i];
		}
	}
	tmp[j]='\0';
  return atoi(tmp);
}

TTrdItfTest::TTrdItfTest(const char *psetupfile,ADDLOG plogfunc)
	:TTrdItfBase(psetupfile,plogfunc)
{
	m_rate_per_match = 0.3;  // 每次成交的比率占总委托量
	m_system_cancel_probability = 0.01; // 系统撤单的百分比
	m_cancel_fault_probability  = 0.05; // 撤单失败的百分比，即撤单后又成交了
	m_report_withdraw=true;
	m_use_hq = false;
	if (InterlockedIncrement(&m_ref_count)==1) {
		InitializeCriticalSection(&m_CS);
	}

	//m_ptsdb = new TdmPTSDB(NULL);
	try
	{
		FPool =new TPool(NULL);
		FPool->Connect();
	}
	catch(...)
	{
    	FPool = NULL;
    }
}


TTrdItfTest::~TTrdItfTest()
{
	if (InterlockedDecrement(&m_ref_count)==0) {
		DeleteCriticalSection(&m_CS);
	}
	this->CloseLink();
    /*
	if( m_ptsdb != NULL  )
		delete m_ptsdb;
    */
	if( FPool!= NULL )
	{
    	delete FPool ;
	}
}

void TTrdItfTest::lock_g(void)
{
	EnterCriticalSection(&m_CS);
}

void TTrdItfTest::unlock_g(void)
{
	LeaveCriticalSection(&m_CS);
}

int  TTrdItfTest::Init()
{
	this->lock_g();
	m_orderid.clear();
	this->unlock_g();
	this->CloseLink();
    /*
	if( m_report_withdraw == true )
	{
  	assert( m_ptsdb!= NULL );
		if( m_ptsdb->ConnectToDB(PTSConStr) == false )
		{
			this->SetLastError(-101,'E',PLUGINNAME,"连接PTSDB失败,connstr=%s",PTSConStr.c_str()) ;
			return -101;
		}
		else
		{
			ODS('M',PLUGINNAME, "Connected to PTSDB!");
		}
	}
    */
	return 0;
}

int  TTrdItfTest::SetAccount()
{
	if( FRequest.SetAccount.Account[0] == 0 )
    {
    	this->SetLastError(-1,'E',PLUGINNAME,"登陆的账户不能为空！") ;
    	return -1;
    }

	FAccInfo.lt = FRequest.SetAccount.LoginType;
	lstrcpyn(FAccInfo.PW, FRequest.SetAccount.PW, PWD_LEN);//帐号密码
	lstrcpyn(FAccInfo.Capital,FRequest.SetAccount.Account,ACC_LEN);
 	FAccount = FRequest.SetAccount.Account;
	NewAns(1);
	memcpy(&((*FAnswer)[0].SetAccount.AccountInfo),&FAccInfo,sizeof(TAccountInfo));

	return 0;
}

int  TTrdItfTest::QryMoney()
{
	NewAns(1);
	(*FAnswer)[0].QryMoney.MoneyInfo.MoneyType = FRequest.QryMoney.MoneyType ;
	(*FAnswer)[0].QryMoney.MoneyInfo.balance = 88000000;
	(*FAnswer)[0].QryMoney.MoneyInfo.available=88000000;
	return 0;
}

int  TTrdItfTest::QryCurCsn()
{
	// Query Order by order id
	if(FRequest.QryCurCsn.OrderID[0]!= 0)
	{
		// in this dll order id is the index of m_orders + 1
		int i = atoi(FRequest.QryCurCsn.OrderID);
		if (i>0 && i <= this->m_orders.size()) {
			TOrderInfo &ord = m_orders.at(i-1);
			NewAns(1);
			memcpy(&((*FAnswer)[0].QryCurCsn.OrderInfo),&ord,sizeof(TOrderInfo));
		}
		else
		{
			this->SetLastError(-2,'E',PLUGINNAME,"Can not find this order ID:%s",
				FRequest.QryCurCsn.OrderID) ;
			return -2;
		}
	}
	// Query orders from seqnum and return less than MaxRecord records
	else if( FRequest.QryCurCsn.MaxRecord>0 )
	{
		// in this dll order's SeqNum is login account + ':' + order id
		int reccount = 0;
		NewAns(FRequest.QryCurCsn.MaxRecord);

		bool bfinded_first = (FRequest.QryCurCsn.SeqNum[0]== 0);
		for (int i = 0; i < m_orders.size(); i++) {
			TOrderInfo &ord = m_orders.at(i);
			if( bfinded_first == false )
			{
				if( strcmp(ord.SeqNum,FRequest.QryCurCsn.SeqNum)== 0)
					bfinded_first=true;
			}
			else
			{
				if( strstr(ord.SeqNum,GetStockAccountByType(FAccInfo.lt)) -ord.SeqNum == 0 )
				{

					memcpy(&((*FAnswer)[reccount++].QryCurCsn.OrderInfo),&ord,sizeof(TOrderInfo));
					if( reccount>= FRequest.QryCurCsn.MaxRecord ) break;
				}
			}
		}
		this->SetAnsCount(reccount);
	}
	else
	{
		this->SetLastError(-1,'E',PLUGINNAME,"Input Parameter Error") ;
		return -1;
	}
	return 0;
}

int  TTrdItfTest::QryCurTrd()
{
	// Query Order by order id
	if(FRequest.QryCurTrd.OrderID[0]!= 0)
	{
		// in this dll order id is the index of m_orders + 1
		int i = atoi(FRequest.QryCurTrd.OrderID);
		if (i>0 && i <= this->m_orders.size()) {
			TOrderInfo &ord = m_orders.at(i-1);
			if( ord.State ==    osbw    ||
					ord.State ==    osyc    ||
					ord.State ==    oscj    ||
					ord.State ==    osyf    )
			{
				TTradeInfo trd;
				lstrcpy(trd.ContractID,ord.ContractID);
				lstrcpy(trd.SecuID,ord.SecuID);
				sprintf(trd.TrdID ,"%s",ord.ContractID);

				trd.Time = atoi(FormatDateTime("hhnnss",Time()).c_str());
				trd.Date = atoi(FormatDateTime("yyyymmdd",Date()).c_str());
				trd.Type = ord.Type;
				trd.Vol =  ord.TrdVol;
				trd.Price = ord.TrdPrice;

				trd.Market = ord.Market;
				sprintf(trd.SeqNum,"%s",ord.SeqNum);

				NewAns(1);
				memcpy(&((*FAnswer)[0].QryCurTrd.TrdInfo),&trd,sizeof(TTradeInfo));
			}
			else
			{
				this->SetLastError(-3,'E',PLUGINNAME,"This order (ID:%s) is being filled",
				FRequest.QryCurCsn.OrderID) ;
				return -3;
      }
		}
		else
		{
			this->SetLastError(-2,'E',PLUGINNAME,"Can not find this order ID:%s",
				FRequest.QryCurCsn.OrderID) ;
			return -2;
		}
	}
	// Query orders from seqnum and return less than MaxRecord records
	else if( FRequest.QryCurTrd.MaxRecord>0 )
	{
		// in this dll order's SeqNum is login account + ':' + order id
		int reccount = 0;
		NewAns(FRequest.QryCurTrd.MaxRecord);
		bool bfinded_first = (FRequest.QryCurTrd.SeqNum[0]==0);

		for (int i = 0; i < m_deals.size(); i++) {
			TTradeInfo &trd = m_deals.at(i);
			if( bfinded_first == false )
			{
				if( strcmp(trd.SeqNum,FRequest.QryCurTrd.SeqNum)== 0)
					bfinded_first=true;
			}
			else
			{
				if( strstr(trd.SeqNum,GetStockAccountByType(FAccInfo.lt)) -trd.SeqNum == 0 )
				{
					memcpy(&((*FAnswer)[reccount++].QryCurTrd.TrdInfo),&trd,sizeof(TOrderInfo));
					if( reccount>= FRequest.QryCurTrd.MaxRecord ) break;
				}
			}
		}
		this->SetAnsCount(reccount);
	}
	else
	{
		this->SetLastError(-1,'E',PLUGINNAME,"Input Parameter Error") ;
		return -1;
	}
	return 0;
}

int  TTrdItfTest::QryStocks()
{
	this->SetLastError(-1,'E',PLUGINNAME,"Not support QryStocks.") ;
	return -1;
}

int  TTrdItfTest::Order()
{
	TOrderInfo ord;
	ZeroMemory(&ord,sizeof(ord));
	lstrcpyn(ord.SecuID,FRequest.Order.SecuID,CODE_LEN);
	ord.Market = FRequest.Order.Market;
	ord.Time = atoi(FormatDateTime("hhnnss",Time()).c_str());
	ord.Date = atoi(FormatDateTime("yyyymmdd",Date()).c_str());
	ord.Type = FRequest.Order.Type;
	ord.State =oswb;
	ord.CsnVol = FRequest.Order.Num;
	ord.TrdVol = 0;
	ord.CancelVol = 0;
	ord.CsnPrice = FRequest.Order.Price;
	ord.TrdPrice = 0;
	ord.Account[0] = 0;

  lock_g();
	
	long id = InterlockedIncrement(&m_Order_ID);
	sprintf(ord.ContractID ,"%d",id);
	sprintf(ord.SeqNum,"%s:%d",GetStockAccountByType(FAccInfo.lt),id);

	NewAns(1);
	strcpy((*FAnswer)[0].Order.ContractID,ord.ContractID);

	m_orders.push_back(ord);
	m_orderid.push_back(id);
	unlock_g();

	return 0;
}

int  TTrdItfTest::Undo()
{
	int i = atoi(FRequest.Undo.ContractID);
	if (i>0 && i <= this->m_orders.size()) {
		TOrderInfo &ord = m_orders.at(i-1);
		switch (ord.State) {
			case oswb:
			case osyb:
			case osbc:
			{
				ord.State = osdc;
				return 0;
			}
		}
	}

	this->SetLastError(-1,'W',PLUGINNAME,"Already filled.") ;
	return -1;
}

bool TTrdItfTest::GetConfig(void)
{
	if( FSetupFile== NULL ) return false;

	TMemIniFile *ini = new TMemIniFile( FSetupFile );
	try
	{
		// 判断是否存在插件的设置，没有的话返回false以便系统能够生成默认的设置
		if( ini->SectionExists(PLUGINNAME) == false ) return false;
		m_rate_per_match = ini->ReadFloat(PLUGINNAME,"m_rate_per_match",m_rate_per_match);
		m_system_cancel_probability=ini->ReadFloat(PLUGINNAME,"m_system_cancel_probability",m_system_cancel_probability);
		m_cancel_fault_probability=ini->ReadFloat(PLUGINNAME,"m_cancel_fault_probability",m_cancel_fault_probability);
		//PTSConStr = ini->ReadString(PLUGINNAME,"PTSDB",PTSConStr) ;
		//m_report_withdraw = ini->ReadBool(PLUGINNAME,"ReportWithdraw",m_report_withdraw);
		m_use_hq =  ini->ReadBool(PLUGINNAME,"use_hq_pool",m_use_hq);
	}
	__finally
	{
		delete ini;
	}
	return true;
}

void TTrdItfTest::SetConfig(void)
{
	if( FSetupFile== NULL ) return ;

	TMemIniFile *ini = new TMemIniFile( FSetupFile );
	try
	{
		ini->WriteFloat(PLUGINNAME,"m_rate_per_match",m_rate_per_match);
		ini->WriteFloat(PLUGINNAME,"m_system_cancel_probability",m_system_cancel_probability);
		ini->WriteFloat(PLUGINNAME,"m_cancel_fault_probability",m_cancel_fault_probability);
		//ini->WriteString(PLUGINNAME,"PTSDB",PTSConStr) ;
		//ini->WriteBool(PLUGINNAME,"ReportWithdraw",m_report_withdraw);
		ini->WriteBool(PLUGINNAME,"use_hq_pool",m_use_hq);
		ini->UpdateFile();
	}
	__finally
	{
  	delete ini;
	}
}

void TTrdItfTest::CloseLink(void)
{
	return TTrdItfBase::CloseLink();
}

int  TTrdItfTest::KeepAlive(void)
{
	//list<TTradeInfo> list2;
	lock_g();
	try
	{
		TTime n = Now();
		unsigned short h,m,s,ms;
		n.DecodeTime(&h,&m,&s,&ms);
		if( h==23 )
		{
			m_orders.clear();
			m_deals.clear();
			m_Order_ID = 0;
			m_trd_id = 0;
		}
		/*
		if( m_orderid.size() > 100 )
		{
			// compress vector
			// clear zero item
			vector<long> tmp;
			for(int i=0;i<m_orderid.size();i++)
			{
				if(m_orderid[i]>0 )
					tmp.push_back(m_orderid[i]);
			}

			m_orderid.clear();

    	m_orderid.assign(tmp.begin(),tmp.end()); 
		}
		*/

		for(int i=0;i<m_orderid.size();i++)
		{
			long index = m_orderid.at(i);
			if( index <=0 ) continue;

			assert( (index -1) >=0 );
			assert( (index -1) < m_orders.size() );
			TOrderInfo &ord =m_orders.at(index-1);
			assert(atoi(ord.ContractID) == index);
			TTradeInfo trd;
			ZeroMemory(&trd,sizeof(trd));

			switch( ord.State)
			{
				case oswb:  //未报(等待申报中...)
				{
					int  prob = 1;
					if( m_system_cancel_probability>0 )
						prob = rand() % (int)(100 / (m_system_cancel_probability*100))  ;
					if ( prob == 0 ) {
						lstrcpy(trd.ContractID,ord.ContractID);
						lstrcpy(trd.SecuID,ord.SecuID);
						long id = InterlockedIncrement(&m_trd_id);
						sprintf(trd.TrdID ,"%d",id);
						trd.Time = atoi(FormatDateTime("hhnnss",Time()).c_str());
						trd.Date = atoi(FormatDateTime("yyyymmdd",Date()).c_str());
						trd.Type = ord.Type;
						trd.Vol =  - ord.CsnVol;
						trd.Price = 0;
						trd.Market = ord.Market;
						sprintf(trd.SeqNum,"%s:%d",GetStockAccountByType(FAccInfo.lt),id);

						//update order
						ord.CancelVol= -ord.CsnVol;
            			ord.State = osyf;

						m_deals.push_back(trd);
						//list2.push_back(trd);
						ODS("oswb : %d",trd.Vol);
					}
					else
						ord.State = osyb;
					break;
				}
				case osyb:  //已报(已经报了,但没有任何成交,等待成交中...)
				case osbc:  //部成(已经有成交了,正在成交中...
				{
					if( m_use_hq && FPool !=NULL)
					{
						// 获取盘口数据
						long lidx = FPool->Find(WideString(ord.SecuID).c_bstr(),ord.Market);
						TCOMIQuote2 qt(FPool->GetItem(lidx));
						long num = 0;
						double price = 0;
						bool btraded = false;
						tagVARIANT idx;
						idx.vt = VT_INT;
						idx.lVal = 0L;
						switch( ord.Type )
						{
							case otBuy:
							case otOpenBuy:
							case otCloseBuy:
							case otCloseTodayBuy:
							{
								qt->get_AskPrice(idx,&price);
								qt->get_AskQty(idx,&num);

                                num = num*m_rate_per_match;

								if (ord.CsnPrice >= price) {
									btraded = true;
									num = min(ord.CsnVol - ord.TrdVol , num);
								}
								break;
							}

							case otSell:
							case otOpenSell:
							case otCloseSell:
							case otCloseTodaySell:
							{
								qt->get_BidPrice(idx,&price);
								qt->get_BidQty(idx,&num);
                                num = num*m_rate_per_match;
								if (ord.CsnPrice <= price) {
									btraded = true;
									num = min(ord.CsnVol - ord.TrdVol ,num );
								}
								break;
							}
						}
						// 撮合
						if (btraded== true && num >0) {
							long t =convert_time_to_long(String(qt->LastTime));
							if (t>ord.Time) {
								lstrcpy(trd.ContractID,ord.ContractID);
								lstrcpy(trd.SecuID,ord.SecuID);
								long id = InterlockedIncrement(&m_trd_id);
								sprintf(trd.TrdID ,"%d",id);

								ord.Time =t;
								trd.Time = t;
								//trd.Time = atoi(FormatDateTime("hhnnss",Time()).c_str());
								trd.Date = atoi(FormatDateTime("yyyymmdd",Date()).c_str());
								trd.Type = ord.Type;
								trd.Vol = num;
								trd.Price = price;
								trd.Market = ord.Market;
								sprintf(trd.SeqNum,"%s:%d",GetStockAccountByType(FAccInfo.lt),id);

								//update order

								ord.TrdPrice =(ord.TrdPrice * ord.TrdVol + trd.Price * trd.Vol)/(trd.Vol+ord.TrdVol);
								ord.TrdVol += trd.Vol;

								if( ord.TrdVol == ord.CsnVol )
									ord.State = oscj;

								if( ord.TrdVol == (ord.CsnVol + ord.CancelVol) )
									ord.State = osbw;
								m_deals.push_back(trd);
							}
						}
					}
					else
					{
						lstrcpy(trd.ContractID,ord.ContractID);
						lstrcpy(trd.SecuID,ord.SecuID);
						long id = InterlockedIncrement(&m_trd_id);
						sprintf(trd.TrdID ,"%d",id);
						trd.Time = atoi(FormatDateTime("hhnnss",Time()).c_str());
						trd.Date = atoi(FormatDateTime("yyyymmdd",Date()).c_str());
						trd.Type = ord.Type;
						trd.Vol = Min((ord.CsnVol - ord.TrdVol), 1+ord.CsnVol * m_rate_per_match);
						trd.Price = ord.CsnPrice;
						trd.Market = ord.Market;
						sprintf(trd.SeqNum,"%s:%d",GetStockAccountByType(FAccInfo.lt),id);

						//update order

						ord.TrdPrice = ord.CsnPrice;
						ord.TrdVol += trd.Vol;

						if( ord.TrdVol == ord.CsnVol )
							ord.State = oscj;

						if( ord.TrdVol == (ord.CsnVol + ord.CancelVol) ) ord.State = osbw;
						m_deals.push_back(trd);
					}
					//ODS("osyb,osbc : %d",trd.Vol);
					break;
				}
				case osdc:  //待撤(撤单命令已下等待撤单)
				{
					int  prob = 1;
					if( m_cancel_fault_probability >0 )
						prob = rand() % (int)(100 / (m_cancel_fault_probability*100))  ;
					if ( prob == 0 )
					{
          				lstrcpy(trd.ContractID,ord.ContractID);
						lstrcpy(trd.SecuID,ord.SecuID);
						long id = InterlockedIncrement(&m_trd_id);
						sprintf(trd.TrdID ,"%d",id);
						trd.Time = atoi(FormatDateTime("hhnnss",Time()).c_str());
						trd.Date = atoi(FormatDateTime("yyyymmdd",Date()).c_str());
						trd.Type = ord.Type;
						trd.Vol =  ord.CsnVol - ord.TrdVol;
						trd.Price = ord.CsnPrice;
						trd.Market = ord.Market;
						sprintf(trd.SeqNum,"%s:%d",GetStockAccountByType(FAccInfo.lt),id);

						//update order

						ord.TrdPrice = ord.CsnPrice;
						ord.TrdVol += trd.Vol;

						if( ord.TrdVol == ord.CsnVol ) ord.State = oscj;
						if( ord.TrdVol == (ord.CsnVol + ord.CancelVol) ) ord.State = osbw;

						m_deals.push_back(trd);
						ODS("撤单时成交 %s:%d",trd.ContractID,trd.Vol);
					}
					else
					{
          				lstrcpy(trd.ContractID,ord.ContractID);
						lstrcpy(trd.SecuID,ord.SecuID);
						long id = InterlockedIncrement(&m_trd_id);
						sprintf(trd.TrdID ,"%d",id);
						trd.Time = atoi(FormatDateTime("hhnnss",Time()).c_str());
						trd.Date = atoi(FormatDateTime("yyyymmdd",Date()).c_str());
						trd.Type = ord.Type;
						trd.Vol =  ord.TrdVol-ord.CsnVol;
						trd.Price = 0;
						trd.Market = ord.Market;
						sprintf(trd.SeqNum,"%s:%d",GetStockAccountByType(FAccInfo.lt),id);

						//update order
						ord.CancelVol= ord.TrdVol - ord.CsnVol;
						if( ord.TrdVol > 0 )
							ord.State = osbw;
						else
							ord.State = osyc;
						
						m_deals.push_back(trd);
						//list2.push_back(trd);
						ODS("撤单 %s: %d",trd.ContractID,trd.Vol);
					}

					break;
				}
				case osbw:  //部撤(确定状态,部分撤销，部分成交)
				case osyc:  //已撤(确定状态,全部撤销了)
				case oscj:  //已成(确定状态,完全成交)
				case osyf:  //已废(确定状态,系统撤单)
				case osno:
					m_orderid[i]= 0;
        	//break;
      }
    } 	
	}
	__finally
	{
		unlock_g();
	}
	/*
	if( m_report_withdraw )
	{
  	assert( m_ptsdb!= NULL );
		list<TTradeInfo>::iterator  ite;
		for (ite = list2.begin(); ite != list2.end(); ite++)
		{
				m_ptsdb->AddOrderReport(FAccount,ite->ContractID,"",abs((int)ite->Vol),0,0.0f,ite->Date,
						ite->Time,"","PTrdTest.dll");
				ODS('U',PLUGINNAME,"%s,%s,%d",FAccount.c_str(),ite->ContractID,ite->Vol);
		}
	}
    */
	return 0;
}
