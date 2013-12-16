//---------------------------------------------------------------------------
//光大证券
//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTrdItf_JSD_GD.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
long convert_datetime_str_to_long(const char * str)
{
	// remove non alpha characters
	char buf[255];
	int j = 0;
	for (_SIZE_T i = 0; i < strlen(str); i++) {
		if( isdigit(str[i]) )
		{
			buf[j++] = str[i];
		}
	}
	buf[j] = 0;

	return atoi(buf);
}

TTrdItf_JSD_GD::TTrdItf_JSD_GD(const char *psetupfile,ADDLOG plogfunc):
TTrdItfBase(psetupfile,plogfunc)
{
	_setup.SvrIp = "127.0.0.1";
	_setup.SvrPort = 17990;
	_setup.TimeOut = 5000;
	_setup.debug_mode = false;
	_setup.branch_no = "999";
	_setup.entrust_way = 0;
}

TTrdItf_JSD_GD::~TTrdItf_JSD_GD()
{
	this->CloseLink();
	delete _gateway;
}

int TTrdItf_JSD_GD::Init()  //初始化                                 ..)
{
	try
	{
		//连接
		if (_gateway==NULL) {
			_gateway = new JsdGateway(_setup.TimeOut);
		}
		ClientIp = _T("127.0.0.1");
		_gateway->SetOP_SITE  ((char*)ClientIp.c_str());           //操作站点
		_gateway->SetOP_BRANCH(_setup.branch_no.c_str());         //操作分支


		if (_gateway->Connect(_setup.SvrIp.c_str(),_setup.SvrPort)!=true)
		{
			this->SetLastError(-1,'E',PLUGINNAME,"连接网关金士达失败,SvrIp = %s, Port = %d",
				_setup.SvrIp.c_str(),_setup.SvrPort);
			return -1;
		}
	}
	catch ( Exception &e)
	{
		this->SetLastError(-1,'E',PLUGINNAME,"连接网关金士达失败,SvrIp = %s, Port = %d, ErrMsg = %s",
			_setup.SvrIp.c_str(),_setup.SvrPort,AnsiString(e.Message).c_str());
		return -1;
	}

	return 0;
}

//--------------------------------------------------------------------------
// CMD:功能号(2)|发起营业部代码|市场代码|暂时不用|帐号|密码|委托方式|
//

//--------------------------------------------------------------------------
int TTrdItf_JSD_GD::SetAccount() //设置帐号
{
	AnsiString cmd;

	ZeroMemory(&FAccInfo,sizeof(FAccInfo));

	try
	{
		//1.	成功标志：Y  2.	姓名  3.	原输入帐号的实际市场代码  4.	原输入的完整帐号代码
		//5.	货币代码（效验的帐号对应的货币代码返回，客户号返回人民币，代码为1） 6.	客户号

		cmd.printf("1|%s|0||%s|%s|%s|",
			_setup.branch_no,
			FRequest.SetAccount.Account,
			_setup.entrust_way, "");

		int ret = _gateway->WaitAnswer(cmd.c_str(),7)  ;
		if (ret !=0)
		{
			this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"请求失败,%s",_gateway->GetRequestBuffer());
			return ret;
		}

		_setup.money_type = _gateway->GetFieldValue(0,5)[0];

		// 1. 功能号(2)  2.发起营业部代码  3.市场代码  4.暂时不用  5.帐号 6.密码 7.委托方式
		if(FRequest.SetAccount.LoginType == asCA)
		{
			cmd.sprintf("2|%s|0||%s|%s|%s|", _setup.branch_no, FRequest.SetAccount.Account,
				FRequest.SetAccount.PW, _setup.entrust_way);
		}
		else if(FRequest.SetAccount.LoginType==asSHA)
		{
			cmd.sprintf("2|%s|1||%s|%s|%s|", _setup.branch_no, FRequest.SetAccount.Account,
				FRequest.SetAccount.PW, _setup.entrust_way);
		}
		else if(FRequest.SetAccount.LoginType==asSZA)
		{
			cmd.sprintf("2|%s|2||%s|%s|%s|", _setup.branch_no, FRequest.SetAccount.Account,
				FRequest.SetAccount.PW, _setup.entrust_way);
		}
		else
			return -1;

		//  首包：1.成功标志  2.姓名     3.客户号   4.市场个数
		//后继包：1.市场代码  2.市场名称 3.股东代码 4.币种代码  5.币种名称
		ret = _gateway->WaitAnswer(cmd.c_str(),5,0,4) ;
		if (ret !=0)
		{
			this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"请求失败,%s",_gateway->GetRequestBuffer());
			return ret;
		}

		if( _setup.debug_mode )
		{
			ODS('M', PLUGINNAME,"REQ->%s\r\nRECV->%s", _gateway->GetRequestBuffer(),_gateway->GetReturnData() );
		}

		strncpy(FAccInfo.Capital, _gateway->GetFieldValue(0,3).c_str(), 13);

		for ( int i =1; i<_gateway->GetRecCount(); i++ )
		{
			if (_gateway->GetFieldValue(i,1)[0] == '1')
				strncpy(FAccInfo.SH, _gateway->GetFieldValue(i,3).c_str(), 13);
			else if (_gateway->GetFieldValue(i,1)[0] == '2')
				strncpy(FAccInfo.SZ, _gateway->GetFieldValue(i,3).c_str(), 13);
		}

		strncpy(FAccInfo.PW, FRequest.SetAccount.PW, 13);

		if(FRequest.SetAccount.LoginType==asSHA)
		{
			lstrcpyn(FAccInfo.SH,FRequest.SetAccount.Account,13);
		}
		else if(FRequest.SetAccount.LoginType==asSZA)
		{
			lstrcpyn(FAccInfo.SZ,FRequest.SetAccount.Account,13);
		}

		if(FAccInfo.SH[0]==0 && FAccInfo.SZ[0]==0) {
			this->SetLastError(-1,'E',PLUGINNAME,"响应错误,无股东帐号。");
			return -1;
		}

		if( _setup.debug_mode )
		{
			ODS('M', PLUGINNAME,"REQ->%s\r\nRECV->%s", _gateway->GetRequestBuffer(),_gateway->GetReturnData() );
		}

		NewAns(1);
		memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));
	}
	catch( Exception &e )
	{
		this->SetLastError(-1,'E',PLUGINNAME,"异常错误,%s",AnsiString(e.Message));
		return -1;
	}

	return 0;
}

//查询资金余额和可用资金余额－9
int TTrdItf_JSD_GD::QryMoney()     //资金查询
{

	AnsiString cmd;
	cmd.sprintf("9|%s|%s||%s|",
		_setup.branch_no,                         // 2
		_setup.money_type,                        // 3
		FAccInfo.Capital);                         // 5

	try
	{
		// 1.成功标志  2.资金余额  3.可用资金  4.买入未交收金额  5.卖出未交收金额
		// 6.委托未成交冻结金额    7.货币名称  8.异常冻结资金
		int ret = _gateway->WaitAnswer(cmd.c_str(),8);
		if (ret !=0)
		{
			this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"请求失败,%s",_gateway->GetRequestBuffer());
			return ret;
		}

		if( _setup.debug_mode )
		{
			ODS('M', PLUGINNAME,"REQ->%s\r\nRECV->%s", _gateway->GetRequestBuffer(),_gateway->GetReturnData() );
		}

		NewAns(1);
		(*FAnswer)[0].QryMoney.MoneyInfo.MoneyType = ConvertMoneyType( _gateway->GetFieldValue(0,7).c_str() );
		(*FAnswer)[0].QryMoney.MoneyInfo.balance = StrToFloat(_gateway->GetFieldValue(0,2).c_str());
		(*FAnswer)[0].QryMoney.MoneyInfo.available = StrToFloat(_gateway->GetFieldValue(0,3).c_str());

	}
	catch( Exception &e )
	{
		this->SetLastError(-1,'E',PLUGINNAME,"异常错误,%s",AnsiString(e.Message));
		return -1;
	}

	return 0;
}

int TTrdItf_JSD_GD::QryCurCsn()    //当日委托查询
{
	AnsiString cmd;

	//      -----1----|------2-------|----3---|----4---|--5---|---6----|
	//      功能号(14)|发起营业部代码|市场代码|暂时不用|客户号|起始日期|
	//      -----7----|---------------8--------------|------------------9---------------|
	//      终止日期  |合同号(为空格时查询所有数据)  |证券代码(为空格时查询所有股票数据)|
	//      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
	//      最多返回数量|索引日期|索引合同号|委托方式|索引市场代码|排序方式(0-市场代码、1-委托时间、2-委托时间倒序)|
	//
	//               1| 2| 3|| 5| 6| 7|8|9|10|11|12|13|14| |


	try
	{
		if (FRequest.QryCurCsn.OrderID[0] != 0) // 查单个委托
		{
			//               1| 2| 3|| 5| 6| 7| 8|9| |||13|| |
			cmd.sprintf("14|%s|%s||%s|%s|%s|%s| |1|||%s||0|",
				_setup.branch_no,                         // 2
				" ",                                        // 3
				FAccInfo.Capital,                          // 5
				FormatDateTime("yyyymmdd",Date()),    // 6
				FormatDateTime("yyyymmdd",Date()),    // 7
				FRequest.QryCurCsn.OrderID,             // 8
				_setup.entrust_way           // 13
				);
			//													     3           5                  9       11                        15
			//A|10.0.38.11|100|B881136426|买|510050|50ETF|100|2.200|64433|0|0.000|0|未成交|13:36:02  |20090818| |W|1|1| |买| |0| |0.00|
			//A|10.0.38.11|100|B881136426|买|510050|50ETF|100|2.200|64433|0|0.000|0|场内撤单|13:36:02|20090818| |2|1|1| |买| |0| |0.00|

			//首包：
			//1.	成功标志：Y  2.	记录个数（后续包个数）
			//后续包：
			//1.	股东帐号    2.	买卖类别名称（V6）3.	证券代码4.	证券名称5.	委托数量6.	委托价格
			//7.	合同号  8.	成交数量9.	成交价格10.	委托状态11.	成交状态12.	委托时间13.	日期14.	出错信息
			//15.	成功标志  16.	市场代码17.	买卖类别标志（新柜台）18.	成交状态标志（新柜台）19.	买卖类别名称（新柜台）
			//20.	错误代码（新柜台）21.	撤单数量（V7.00）22.	委托属性(比如融资买入,融资卖出等等,中文输出)
			int ret = _gateway->WaitAnswer(cmd.c_str(),20,0);
			if (ret !=0)
			{
				this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"请求失败,%s",_gateway->GetRequestBuffer());
				return ret;
			}

			if( _setup.debug_mode )
			{
				ODS('M', PLUGINNAME,"REQ->%s\r\nRECV->%s", _gateway->GetRequestBuffer(),_gateway->GetReturnData() );
			}

			int count = StrToInt(_gateway->GetFieldValue(0,2).c_str());
			if (count <= 0) return ERR_REMOTE_OTHER_FAILED;

			NewAns(1);
			TOrderInfo *ci =   &(*FAnswer)[0].QryCurCsn.OrderInfo;
			lstrcpyn(ci->ContractID , _gateway->GetFieldValue(1,7).c_str(),SEQ_LEN);
			lstrcpyn(ci->SecuID, _gateway->GetFieldValue(1,3).c_str(),CODE_LEN) ;
			ci->Market = ConvertMarketType(_gateway->GetFieldValue(1,16).c_str()) ;
			ci->Time = convert_datetime_str_to_long(_gateway->GetFieldValue(1,12).c_str());
			ci->Date = convert_datetime_str_to_long(_gateway->GetFieldValue(1,13).c_str());
			ci->Type = ConvertOrderType(_gateway->GetFieldValue(1,2).c_str());
			ci->State = ConvertOrderState(_gateway->GetFieldValue(1,11).c_str());
			ci->CsnVol= StrToInt(_gateway->GetFieldValue(1,5).c_str());
			ci->TrdVol = StrToInt(_gateway->GetFieldValue(1,8).c_str());
			ci->CancelVol = StrToInt(_gateway->GetFieldValue(1,21).c_str());;
			ci->CsnPrice = StrToFloat(_gateway->GetFieldValue(1,6).c_str());
			ci->TrdPrice = StrToFloat(_gateway->GetFieldValue(1,9).c_str());
			lstrcpyn(ci->Account ,_gateway->GetFieldValue(1,1).c_str(),ACC_LEN);
			//11 索引日期 12 索引合同号 14	索引市场代码
			sprintf(ci->SeqNum ,"%s|%s|%s|%s|", _gateway->GetFieldValue(1,13).c_str() ,
				_gateway->GetFieldValue(1,7).c_str() ,
				_setup.entrust_way.c_str() ,
				_gateway->GetFieldValue(1,16).c_str());

			/*
			以下是7.0以前的版本查询撤单的方法
			//成交标志
			//0已成交    1部分成交  2场内撤单  3部分撤单   4场外撤单   5股票不足  C撤单请求  D撤单已发
			//W未成交    9 撤单失败   A 部分成交失败    E 撤单已发部分成交

			char ts =  _gateway->GetFieldValue(1,15)[0];
			if(ts=='2' || ts=='4' || (ts=='3' && ((*FAnswer)[0].QryOrder.OrderInfo.MatchQty > 0)))
			{
			if(ts == '3' && ++reqry_num < 3 ) //如果是部撤则再查直到 reqry_num >3
			{
			Sleep(100);
			goto HH;
			}

			int csnnum = toInt(_gateway->GetFieldValue(1,5).c_str(), 0);
			(*FAnswer)[0].QryOrder.OrderInfo.CancelQty = (*FAnswer)[0].QryOrder.OrderInfo.MatchQty - csnnum ;
			}
			*/
		}
		else if( FRequest.QryCurCsn.MaxRecord == 0 )  // 查所有
		{
			AnsiString seq = "||"+ _setup.entrust_way+ "||";
			TList *recList = new TList();
			try
			{
				do
				{
					cmd.sprintf("14|%s|%c||%s|%s|%s| | |%d|%s1|",
						_setup.branch_no,                          // 2
						' ',                                        // 3
						FAccInfo.Capital,                           // 5
						FormatDateTime("yyyymmdd",Date()),                               // 6
						FormatDateTime("yyyymmdd",Date()),                               // 7
						50,                                       // 10
						//"",                            // 11
						//"",                      // 12
						//_setup.entrust_way,           // 13
						//""                         // 14
						seq
						);
					// 1.股东帐号 2.买卖类别  3.证券代码  4.证券名称  5.委托数量  6.委托价格
					// 7.合同号   8.成交数量  9.成交价格 10.委托状态 11.成交状态 12.成交时间
					//13.日期    14.出错信息 15.成功标志 16.市场代码
					int ret=	_gateway->WaitAnswer(cmd.c_str(),16,0)  ;
					if (ret !=0)
					{
						this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"请求失败,%s",_gateway->GetRequestBuffer());
						return ret;
					}
					if( _setup.debug_mode )
					{
						ODS('M', PLUGINNAME,"REQ->%s\r\nRECV->%s", _gateway->GetRequestBuffer(),_gateway->GetReturnData() );
					}

					int count = StrToInt(_gateway->GetFieldValue(0,2).c_str());
					if (count <= 0) break;

					for ( int i =1; i<_gateway->GetRecCount(); i++ )
					{
						TOrderInfo *ci =   new TOrderInfo;
						lstrcpyn(ci->ContractID , _gateway->GetFieldValue(i,7).c_str(),SEQ_LEN);
						lstrcpyn(ci->SecuID, _gateway->GetFieldValue(i,3).c_str(),CODE_LEN) ;
						ci->Market = ConvertMarketType(_gateway->GetFieldValue(i,16).c_str()) ;
						ci->Time = convert_datetime_str_to_long(_gateway->GetFieldValue(i,12).c_str());
						ci->Date = convert_datetime_str_to_long(_gateway->GetFieldValue(i,13).c_str());
						ci->Type = ConvertOrderType(_gateway->GetFieldValue(i,2).c_str());
						ci->State = ConvertOrderState(_gateway->GetFieldValue(i,11).c_str());
						ci->CsnVol= StrToInt(_gateway->GetFieldValue(i,5).c_str());
						ci->TrdVol = StrToInt(_gateway->GetFieldValue(i,8).c_str());
						ci->CancelVol = StrToInt(_gateway->GetFieldValue(i,21).c_str());;
						ci->CsnPrice = StrToFloat(_gateway->GetFieldValue(i,6).c_str());
						ci->TrdPrice = StrToFloat(_gateway->GetFieldValue(i,9).c_str());
						lstrcpyn(ci->Account , _gateway->GetFieldValue(i,1).c_str(),ACC_LEN);
						//11 索引日期 12 索引合同号 14	索引市场代码
						sprintf(ci->SeqNum ,"%s|%s|%s|%s|", _gateway->GetFieldValue(i,13).c_str() ,
							_gateway->GetFieldValue(i,7).c_str() ,
							_setup.entrust_way.c_str() ,
							_gateway->GetFieldValue(i,16).c_str());
						seq = ci->SeqNum;
						recList->Add(ci);
					}
				}
				while(1);

				if(recList->Count>0)
				{
					NewAns(recList->Count);
					for(int i=0; i<recList->Count; i++)
					{
						TOrderInfo *ci =   &(*FAnswer)[i].QryCurCsn.OrderInfo;
						memcpy(ci,recList->Items[i],sizeof(TOrderInfo));
						delete (TOrderInfo *)recList->Items[i];
					}
				}
			}
			__finally
			{
				delete recList;
			}
		}
		else // 增量查询
		{
			AnsiString seq = FRequest.QryCurCsn.SeqNum;
			if( seq.Length() == 0)
				seq = "||"+ _setup.entrust_way+ "||";
			cmd.sprintf("14|%s|%c||%s|%s|%s| | |%d|%s1|",
				_setup.branch_no,                          // 2
				' ',                                        // 3
				FAccInfo.Capital,                           // 5
				FormatDateTime("yyyymmdd",Date()),                               // 6
				FormatDateTime("yyyymmdd",Date()),                               // 7
				FRequest.QryCurCsn.MaxRecord,                                       // 10
				//"",                            // 11
				//"",                      // 12
				//_setup.entrust_way,           // 13
				//""                         // 14
				seq
				);
			// 1.股东帐号 2.买卖类别  3.证券代码  4.证券名称  5.委托数量  6.委托价格
			// 7.合同号   8.成交数量  9.成交价格 10.委托状态 11.成交状态 12.成交时间
			//13.日期    14.出错信息 15.成功标志 16.市场代码

			int ret = _gateway->WaitAnswer(cmd.c_str(),16,0);
			if (ret !=0)
			{
				this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"请求失败,%s",_gateway->GetRequestBuffer());
				return ret;
			}

			if( _setup.debug_mode )
			{
				ODS('M', PLUGINNAME,"REQ->%s\r\nRECV->%s", _gateway->GetRequestBuffer(),_gateway->GetReturnData() );
			}

			int count = StrToInt(_gateway->GetFieldValue(0,2).c_str());
			if (count < 0) return ERR_REMOTE_OTHER_FAILED;

			NewAns(_gateway->GetRecCount()-1);

			for ( int i =1; i<_gateway->GetRecCount(); i++ )
			{
				TOrderInfo *ci =   &(*FAnswer)[i-1].QryCurCsn.OrderInfo;
				lstrcpyn(ci->ContractID , _gateway->GetFieldValue(i,7).c_str(),SEQ_LEN);
				lstrcpyn(ci->SecuID, _gateway->GetFieldValue(i,3).c_str(),CODE_LEN) ;
				ci->Market = ConvertMarketType(_gateway->GetFieldValue(i,16).c_str()) ;
				ci->Time = convert_datetime_str_to_long(_gateway->GetFieldValue(i,12).c_str());
				ci->Date = convert_datetime_str_to_long(_gateway->GetFieldValue(i,13).c_str());
				ci->Type = ConvertOrderType(_gateway->GetFieldValue(i,2).c_str());
				ci->State = ConvertOrderState(_gateway->GetFieldValue(i,11).c_str());
				ci->CsnVol= StrToInt(_gateway->GetFieldValue(i,5).c_str());
				ci->TrdVol = StrToInt(_gateway->GetFieldValue(i,8).c_str());
				ci->CancelVol = StrToInt(_gateway->GetFieldValue(i,21).c_str());;
				ci->CsnPrice = StrToFloat(_gateway->GetFieldValue(i,6).c_str());
				ci->TrdPrice = StrToFloat(_gateway->GetFieldValue(i,9).c_str());
				lstrcpyn(ci->Account , _gateway->GetFieldValue(i,1).c_str(),ACC_LEN);
				//11 索引日期 12 索引合同号 14	索引市场代码
				sprintf(ci->SeqNum ,"%s|%s|%s|%s|", _gateway->GetFieldValue(i,13).c_str() ,
					_gateway->GetFieldValue(i,7).c_str() ,
					_setup.entrust_way.c_str() ,
					_gateway->GetFieldValue(i,16).c_str());
			}
		}
	}
	catch( Exception &e )
	{
		this->SetLastError(-1,'E',PLUGINNAME,"异常错误,%s",AnsiString(e.Message));
		return -1;
	}
	return 0;
}


int TTrdItf_JSD_GD::QryCurTrd()    //当日成交查询
{
	AnsiString cmd;

	//  1.功能号(13)   2.发起营业部代码  3.市场代码     4.暂时不用      5.客户号
	//  6.最多返回数量 7.索引证券代码    8.索引股东帐号 9.索引成交编号 10.委托方式
	// 11.索引市场代码（v5.83，当市场代码=0查询所有时必须添入）
	//
	try
	{
		if (FRequest.QryCurTrd.OrderID[0] != 0) // 查单个委托的成交
		{
        	return -1;
		}
		else if(FRequest.QryCurTrd.MaxRecord == 0)    // 查所有
		{
			//7.	索引证券代码|8.	索引股东帐号|9.	索引成交编号| 10.	委托方式|11.	索引市场代码（v5.83，当市场代码=0查询所有时必须添入） |

			AnsiString seq = "|||" + _setup.entrust_way + "||";
			TList *recList = new TList();
			//
			// 1.股东帐号 2.买卖类别  3.证券代码  4.证券名称  5.成交数量  6.成交价格
			// 7.成交时间 8.成交编号  9.合同号码 10.市场代码（9-10为v5.83实现）
			//
			try
			{
				do
				{
					//               1| 2| 3|| 5| 6| 7| 8| 9|10|11|12
					cmd.sprintf("13|%s|%c||%s|%d|%s%s|%s|A|",
						_setup.branch_no,                          // 2
						'0',                                        // 3
						FAccInfo.Capital,                           // 5
						100,                                       // 6
						seq
						);


					int ret = _gateway->WaitAnswer(cmd.c_str(),10,false);
					if (ret !=0)
					{
						this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"请求失败,%s",_gateway->GetRequestBuffer());
						return ret;
					}

					if( _setup.debug_mode )
					{
						ODS('M', PLUGINNAME,"REQ->%s\r\nRECV->%s", _gateway->GetRequestBuffer(),_gateway->GetReturnData() );
					}

					int count = StrToInt(_gateway->GetFieldValue(0,2).c_str());
					if (count <= 0) break;

					for (int i = 1; i < _gateway->GetRecCount(); i++)
					{
						TTradeInfo *ti = new TTradeInfo;
						memset(ti, 0, sizeof(TTradeInfo));

						lstrcpyn(ti->ContractID, _gateway->GetFieldValue(i,9).c_str(),SEQ_LEN);
						lstrcpyn(ti->SecuID,_gateway->GetFieldValue(i,3).c_str(),CODE_LEN);
						lstrcpyn(ti->TrdID, _gateway->GetFieldValue(i,8).c_str(),SEQ_LEN);
						ti->Time = convert_datetime_str_to_long(_gateway->GetFieldValue(i,7).c_str());
						ti->Date = Date().FormatString(L"yyyymmdd").ToInt();
						ti->Type = ConvertOrderType(_gateway->GetFieldValue(i,2).c_str());
						ti->Vol = StrToInt(_gateway->GetFieldValue(i,5).c_str());
						ti->Price = StrToFloat(_gateway->GetFieldValue(i,6).c_str());
						ti->Market = ConvertMarketType(_gateway->GetFieldValue(i,10).c_str()) ;
						lstrcpyn(ti->Account ,_gateway->GetFieldValue(i,1).c_str() ,ACC_LEN);
						sprintf(ti->SeqNum ,"%s|%s|%s|%s|%s|",ti->SecuID,ti->Account,ti->TrdID,
							_setup.entrust_way,_gateway->GetFieldValue(i,10).c_str());
						recList->Add(ti);

						seq= ti->SeqNum;
					}
				}
				while(1);
				if(recList->Count>0)
				{
					NewAns(recList->Count);
					for(int i=0; i<recList->Count; i++)
					{
						TTradeInfo *ci =   &(*FAnswer)[i].QryCurTrd.TrdInfo;
						memcpy(ci,recList->Items[i],sizeof(TTradeInfo));
						delete (TTradeInfo *)recList->Items[i];
					}
				}
			}
			__finally
			{
				delete recList;
			}
		}
		else    // 增量查询
		{
			AnsiString seq = FRequest.QryCurTrd.SeqNum;
			if( seq.Length() == 0)
			{
                seq = "|||" + _setup.entrust_way + "||";
			}

			cmd.sprintf("13|%s|%c||%s|%d|%s%s|%s|A|",
				_setup.branch_no,                          // 2
				'0',                                        // 3
				FAccInfo.Capital,                           // 5
				100,                                       // 6
				seq
				);


			int ret = _gateway->WaitAnswer(cmd.c_str(),10,false);
			if (ret !=0)
			{
				this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"请求失败,%s",_gateway->GetRequestBuffer());
				return ret;
			}

			if( _setup.debug_mode )
			{
				ODS('M', PLUGINNAME,"REQ->%s\r\nRECV->%s", _gateway->GetRequestBuffer(),_gateway->GetReturnData() );
			}

			int count = StrToInt(_gateway->GetFieldValue(0,2).c_str());
			if (count < 0) return ERR_REMOTE_OTHER_FAILED;

			NewAns(_gateway->GetRecCount()-1);

			for (int i = 1; i < _gateway->GetRecCount(); i++)
			{
				TTradeInfo *ti =&(*FAnswer)[i-1].QryCurTrd.TrdInfo;
				memset(ti, 0, sizeof(TTradeInfo));

				lstrcpyn(ti->ContractID, _gateway->GetFieldValue(i,9).c_str(),SEQ_LEN);
				lstrcpyn(ti->SecuID,_gateway->GetFieldValue(i,3).c_str(),CODE_LEN);
				lstrcpyn(ti->TrdID, _gateway->GetFieldValue(i,8).c_str(),SEQ_LEN);
				ti->Time = convert_datetime_str_to_long(_gateway->GetFieldValue(i,7).c_str());
				ti->Date = Date().FormatString(L"yyyymmdd").ToInt();
				ti->Type = ConvertOrderType(_gateway->GetFieldValue(i,2).c_str());
				ti->Vol = StrToInt(_gateway->GetFieldValue(i,5).c_str());
				ti->Price = StrToFloat(_gateway->GetFieldValue(i,6).c_str());
				ti->Market = ConvertMarketType(_gateway->GetFieldValue(i,10).c_str()) ;
				lstrcpyn(ti->Account ,_gateway->GetFieldValue(i,1).c_str() ,ACC_LEN);
				sprintf(ti->SeqNum ,"%s|%s|%s|%s|%s|",ti->SecuID,ti->Account,ti->TrdID,
					_setup.entrust_way,_gateway->GetFieldValue(i,10).c_str());

				seq= ti->SeqNum;
			}
		}
	}
	catch( Exception &e )
	{
		this->SetLastError(-1,'E',PLUGINNAME,"异常错误,%s",AnsiString(e.Message));
		return -1;
	}
	return 0;
}

int TTrdItf_JSD_GD::QryStocks()    //查询帐号中所有的股份
{
	AnsiString et = ConvertMarketType(FRequest.QryStocks.Market);

	AnsiString cmd;

	AnsiString idxStock = "";
	AnsiString idxAcc   = "";
	AnsiString idxMart  = "";

	TList *recList = new TList();

	try
	{
		try
		{
			do
			{
				//    ----1-----|-------2------|----3---|---4----|---5--|----------------6---------------|
				//CMD 功能号(10)|发起营业部代码|市场代码|暂时不用|客户号|查询市场代码（空格表示所有市场）|
				//    --------------------------------7---------------------------------|
				//    查询证券代码（为空格时表示查询所有股票，否则只查询某一只股票情况）|
				//    ---------------8----------------|-----9------|-----10-----|-----11-----|
				//    股东代码（空格表示所有股东代码）|索引市场代码|索引证券代码|索引股东帐号|
				//    -----12-----|-----------13-----------|---14---|
				//    最多返回数量|操作功能（1明细、2汇总）|委托方式|
				//    -----------------------------------------15------------------------------------------------|
				//    货币代码（v5.20.2实现：当查询市场代码为空而货币代码不为空时，则查询该货币的市场{沪A和深A}）|
				//    -------------------16----------------------|-----------------17-------------------|
				//    是否返回合计值（1：返回合计值，其他不返回）|点评起始日期（为空，则不输出点评信息）|
				//
				//                 1| 2| 3|| 5| 6|7| 8| 9|10|11|12| |14||16||
				cmd.sprintf("10|%s|%s||%s|%s| |%s|%s|%s|%s|%d|1|%s||||",       //光大新文档说16必须填空
					_setup.branch_no,                         // 2
					et,                                        // 3
					FAccInfo.Capital,                          // 5
					et,                                        // 6
					this->GetStockAccountByMarket(FRequest.QryStocks.Market),     // 8
					idxMart.c_str(),                           // 9
					idxStock.c_str(),                          // 10
					idxAcc.c_str(),                            // 11
					100,                                      // 12
					_setup.entrust_way);         // 14

	

				//[3]A|10.0.38.11|100|2|0800044619|002282|博深工具|500|500|5750.000|0.000|11.500|11.500|500|5750.000|0.000| | |11.500|0.000|11.500|
				//  1.市场代码  2.股东帐号   3.证券代码        4.证券名称  5.余额(加上当日成交)
				//  6.可用余额  7.市值(当日) 8.浮动盈亏(当日)  9.成本价格 10.行情最新价
				// 11.昨日库存数量          12.股票市值(昨日) 13.浮动盈亏(昨日库存)
				// 14.点评日期              15.一句话点评信息 16.国债净价 17.每百元应计利息(不是国债为0)

				int ret = _gateway->WaitAnswer(cmd.c_str(),17,false);
				if (ret !=0)
				{
					this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"请求失败,%s",_gateway->GetRequestBuffer());
					return ret;
				}

				if( _setup.debug_mode )
				{
					ODS('M', PLUGINNAME,"REQ->%s\r\nRECV->%s", _gateway->GetRequestBuffer(),_gateway->GetReturnData() );
				}

				int count = StrToInt(_gateway->GetFieldValue(0,2).c_str());
				if (count <=0 ) break;

				NewAns(_gateway->GetRecCount()-1);

				for (int i = 1; i < _gateway->GetRecCount(); i++)
				{
					TStockInfo *ti = &(*FAnswer)[i-1].QryStocks.StockInfo;
					memset(ti, 0, sizeof(TStockInfo));

					idxMart = _gateway->GetFieldValue(i,1).c_str();
					idxStock = _gateway->GetFieldValue(i,3).c_str();
					idxAcc =  _gateway->GetFieldValue(i,2).c_str();

					lstrcpyn(ti->SecuID, idxStock.c_str(), CODE_LEN);
					lstrcpyn(ti->Account, idxAcc.c_str(), ACC_LEN);
					ti->PosDir = ConvertPosDir("");
					ti->Market = ConvertMarketType(idxMart.c_str());
					ti->Balance = StrToInt(_gateway->GetFieldValue(i,5).c_str());
					ti->PosNum = StrToInt(_gateway->GetFieldValue(i,5).c_str());
					ti->Available = StrToInt(_gateway->GetFieldValue(i,6).c_str());
					ti->CostPrice =StrToFloat(_gateway->GetFieldValue(i,9).c_str());
					ti->CurPrice = StrToFloat(_gateway->GetFieldValue(i,10).c_str());
				}
			}
			while(1) ;
			if(recList->Count>0)
			{
				NewAns(recList->Count);
				for(int i=0; i<recList->Count; i++)
				{
					TTradeInfo *ci =   &(*FAnswer)[i].QryCurTrd.TrdInfo;
					memcpy(ci,recList->Items[i],sizeof(TTradeInfo));
					delete (TTradeInfo *)recList->Items[i];
				}
			}
		}
		__finally
		{
			delete recList;
		}
	}
	catch( Exception &e )
	{
		this->SetLastError(-1,'E',PLUGINNAME,"异常错误,%s",AnsiString(e.Message));
		return -1;
	}

	return 0;
}

//////交易函数/////
//---------------------------------------------------------------------------
// CMD: 功能号(3)|发起营业部代码|市场代码|暂时不用|股东帐号|证券代码|买卖类型(1买入、2卖出)
//      |委托数量|委托价格|委托方式|银行标志|银行代码|
//---------------------------------------------------------------------------
int TTrdItf_JSD_GD::Order()
{
	AnsiString cmd;
	AnsiString et = ConvertMarketType(FRequest.Order.Market);

/*
	if (FRequest.Entrust.Prop == 1)
	{
		// 1.功能号(202)  2.营业部代码  3.市场代码  4.暂时不用  5.客户号
		// 6.股东代码     7.申购/赎回标志（1：申购，2：赎回）
		// 8.基金代码     9.申购份额    10.委托方式
		//                1| 2| 3|| 5| 6|7| 8| 9|10|

		char ss;
		if(FRequest.Entrust.BorS=='B')  ss='1';
		else                            ss='2';


		cmd.sprintf("202|%s|%c||%s|%s|%c|%s|%d|%s|",
			_setup.branch_no,                          // 2
			et,                                         // 3
			FAccInfo.Capital,                           // 5
			et == '1' ? FAccInfo.SH : FAccInfo.SZ,      // 6
			ss,
			FRequest.Entrust.SecuID,                    // 8
			FRequest.Entrust.Num,                           // 9
			_setup.entrust_way);          // 10
	}
*/

	//      ----1----|------2-------|----3---|----4---|----5---|----6---|
	// CMD: 功能号(3)|发起营业部代码|市场代码|暂时不用|股东帐号|证券代码|
	//
	//      ----------7-----------|----8---|----9---|---10---|---11---|---12---|
	//      买卖类型(1买入、2卖出)|委托数量|委托价格|委托方式|银行标志|银行代码|
	//
	//              1| 2| 3|| 5| 6|7| 8|   9|10|||
	AnsiString ss = ConvertOrderType(FRequest.Order.Type);

	cmd.sprintf("3|%s|%s||%s|%s|%s|%d|%.3f|%s|||",
		_setup.branch_no,                         // 2
		et,                                        // 3
		this->GetStockAccountByMarket(FRequest.Order.Market),     // 5
		FRequest.Order.SecuID,                   // 6
		ss,
		FRequest.Order.Num,                          // 8
		FRequest.Order.Price,                        // 9
		_setup.entrust_way);         // 10

	int ret = _gateway->WaitAnswer(cmd.c_str(),2) ;
	if (ret !=0)
	{
		this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"请求失败,%s",_gateway->GetRequestBuffer());
		return ret;
	}

	if( _setup.debug_mode )
	{
		ODS('M', PLUGINNAME,"REQ->%s\r\nRECV->%s", _gateway->GetRequestBuffer(),_gateway->GetReturnData() );
	}

	NewAns(1);
	strncpy((*FAnswer)[0].Order.ContractID, _gateway->GetFieldValue(0,2).c_str(), 19);

	return 0;
}


int TTrdItf_JSD_GD::Undo() //委托撤单
{

	AnsiString cmd;
	//
	//     ----1----|-------2------|----3---|----4---|---5--|---6--|----7---|
	//CMD: 功能号(4)|发起营业部代码|市场代码|暂时不用|客户号|合同号|委托方式|
	//
	//              1| 2| 3|| 5| 6| 7|
	cmd.sprintf("4|%s|%s||%s|%s|%s|",
		_setup.branch_no,                          // 2
		ConvertMarketType(FRequest.Undo.Market),   // 3
		FAccInfo.Capital,                           // 5
		FRequest.Undo.ContractID,                   // 6
		_setup.entrust_way);          // 7

	int ret = _gateway->WaitAnswer(cmd.c_str(),2);
	if (ret !=0)
	{
		this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"请求失败,%s",_gateway->GetRequestBuffer());
		return ret;
	}

	if( _setup.debug_mode )
	{
		ODS('M', PLUGINNAME,"REQ->%s\r\nRECV->%s", _gateway->GetRequestBuffer(),_gateway->GetReturnData() );
	}

	return 0;
}


