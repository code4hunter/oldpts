//---------------------------------------------------------------------------
//���֤ȯ
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

int TTrdItf_JSD_GD::Init()  //��ʼ��                                 ..)
{
	try
	{
		//����
		if (_gateway==NULL) {
			_gateway = new JsdGateway(_setup.TimeOut);
		}
		ClientIp = _T("127.0.0.1");
		_gateway->SetOP_SITE  ((char*)ClientIp.c_str());           //����վ��
		_gateway->SetOP_BRANCH(_setup.branch_no.c_str());         //������֧


		if (_gateway->Connect(_setup.SvrIp.c_str(),_setup.SvrPort)!=true)
		{
			this->SetLastError(-1,'E',PLUGINNAME,"�������ؽ�ʿ��ʧ��,SvrIp = %s, Port = %d",
				_setup.SvrIp.c_str(),_setup.SvrPort);
			return -1;
		}
	}
	catch ( Exception &e)
	{
		this->SetLastError(-1,'E',PLUGINNAME,"�������ؽ�ʿ��ʧ��,SvrIp = %s, Port = %d, ErrMsg = %s",
			_setup.SvrIp.c_str(),_setup.SvrPort,AnsiString(e.Message).c_str());
		return -1;
	}

	return 0;
}

//--------------------------------------------------------------------------
// CMD:���ܺ�(2)|����Ӫҵ������|�г�����|��ʱ����|�ʺ�|����|ί�з�ʽ|
//

//--------------------------------------------------------------------------
int TTrdItf_JSD_GD::SetAccount() //�����ʺ�
{
	AnsiString cmd;

	ZeroMemory(&FAccInfo,sizeof(FAccInfo));

	try
	{
		//1.	�ɹ���־��Y  2.	����  3.	ԭ�����ʺŵ�ʵ���г�����  4.	ԭ����������ʺŴ���
		//5.	���Ҵ��루Ч����ʺŶ�Ӧ�Ļ��Ҵ��뷵�أ��ͻ��ŷ�������ң�����Ϊ1�� 6.	�ͻ���

		cmd.printf("1|%s|0||%s|%s|%s|",
			_setup.branch_no,
			FRequest.SetAccount.Account,
			_setup.entrust_way, "");

		int ret = _gateway->WaitAnswer(cmd.c_str(),7)  ;
		if (ret !=0)
		{
			this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"����ʧ��,%s",_gateway->GetRequestBuffer());
			return ret;
		}

		_setup.money_type = _gateway->GetFieldValue(0,5)[0];

		// 1. ���ܺ�(2)  2.����Ӫҵ������  3.�г�����  4.��ʱ����  5.�ʺ� 6.���� 7.ί�з�ʽ
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

		//  �װ���1.�ɹ���־  2.����     3.�ͻ���   4.�г�����
		//��̰���1.�г�����  2.�г����� 3.�ɶ����� 4.���ִ���  5.��������
		ret = _gateway->WaitAnswer(cmd.c_str(),5,0,4) ;
		if (ret !=0)
		{
			this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"����ʧ��,%s",_gateway->GetRequestBuffer());
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
			this->SetLastError(-1,'E',PLUGINNAME,"��Ӧ����,�޹ɶ��ʺš�");
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
		this->SetLastError(-1,'E',PLUGINNAME,"�쳣����,%s",AnsiString(e.Message));
		return -1;
	}

	return 0;
}

//��ѯ�ʽ����Ϳ����ʽ���9
int TTrdItf_JSD_GD::QryMoney()     //�ʽ��ѯ
{

	AnsiString cmd;
	cmd.sprintf("9|%s|%s||%s|",
		_setup.branch_no,                         // 2
		_setup.money_type,                        // 3
		FAccInfo.Capital);                         // 5

	try
	{
		// 1.�ɹ���־  2.�ʽ����  3.�����ʽ�  4.����δ���ս��  5.����δ���ս��
		// 6.ί��δ�ɽ�������    7.��������  8.�쳣�����ʽ�
		int ret = _gateway->WaitAnswer(cmd.c_str(),8);
		if (ret !=0)
		{
			this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"����ʧ��,%s",_gateway->GetRequestBuffer());
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
		this->SetLastError(-1,'E',PLUGINNAME,"�쳣����,%s",AnsiString(e.Message));
		return -1;
	}

	return 0;
}

int TTrdItf_JSD_GD::QryCurCsn()    //����ί�в�ѯ
{
	AnsiString cmd;

	//      -----1----|------2-------|----3---|----4---|--5---|---6----|
	//      ���ܺ�(14)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|��ʼ����|
	//      -----7----|---------------8--------------|------------------9---------------|
	//      ��ֹ����  |��ͬ��(Ϊ�ո�ʱ��ѯ��������)  |֤ȯ����(Ϊ�ո�ʱ��ѯ���й�Ʊ����)|
	//      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
	//      ��෵������|��������|������ͬ��|ί�з�ʽ|�����г�����|����ʽ(0-�г����롢1-ί��ʱ�䡢2-ί��ʱ�䵹��)|
	//
	//               1| 2| 3|| 5| 6| 7|8|9|10|11|12|13|14| |


	try
	{
		if (FRequest.QryCurCsn.OrderID[0] != 0) // �鵥��ί��
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
			//A|10.0.38.11|100|B881136426|��|510050|50ETF|100|2.200|64433|0|0.000|0|δ�ɽ�|13:36:02  |20090818| |W|1|1| |��| |0| |0.00|
			//A|10.0.38.11|100|B881136426|��|510050|50ETF|100|2.200|64433|0|0.000|0|���ڳ���|13:36:02|20090818| |2|1|1| |��| |0| |0.00|

			//�װ���
			//1.	�ɹ���־��Y  2.	��¼������������������
			//��������
			//1.	�ɶ��ʺ�    2.	����������ƣ�V6��3.	֤ȯ����4.	֤ȯ����5.	ί������6.	ί�м۸�
			//7.	��ͬ��  8.	�ɽ�����9.	�ɽ��۸�10.	ί��״̬11.	�ɽ�״̬12.	ί��ʱ��13.	����14.	������Ϣ
			//15.	�ɹ���־  16.	�г�����17.	��������־���¹�̨��18.	�ɽ�״̬��־���¹�̨��19.	����������ƣ��¹�̨��
			//20.	������루�¹�̨��21.	����������V7.00��22.	ί������(������������,���������ȵ�,�������)
			int ret = _gateway->WaitAnswer(cmd.c_str(),20,0);
			if (ret !=0)
			{
				this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"����ʧ��,%s",_gateway->GetRequestBuffer());
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
			//11 �������� 12 ������ͬ�� 14	�����г�����
			sprintf(ci->SeqNum ,"%s|%s|%s|%s|", _gateway->GetFieldValue(1,13).c_str() ,
				_gateway->GetFieldValue(1,7).c_str() ,
				_setup.entrust_way.c_str() ,
				_gateway->GetFieldValue(1,16).c_str());

			/*
			������7.0��ǰ�İ汾��ѯ�����ķ���
			//�ɽ���־
			//0�ѳɽ�    1���ֳɽ�  2���ڳ���  3���ֳ���   4���⳷��   5��Ʊ����  C��������  D�����ѷ�
			//Wδ�ɽ�    9 ����ʧ��   A ���ֳɽ�ʧ��    E �����ѷ����ֳɽ�

			char ts =  _gateway->GetFieldValue(1,15)[0];
			if(ts=='2' || ts=='4' || (ts=='3' && ((*FAnswer)[0].QryOrder.OrderInfo.MatchQty > 0)))
			{
			if(ts == '3' && ++reqry_num < 3 ) //����ǲ������ٲ�ֱ�� reqry_num >3
			{
			Sleep(100);
			goto HH;
			}

			int csnnum = toInt(_gateway->GetFieldValue(1,5).c_str(), 0);
			(*FAnswer)[0].QryOrder.OrderInfo.CancelQty = (*FAnswer)[0].QryOrder.OrderInfo.MatchQty - csnnum ;
			}
			*/
		}
		else if( FRequest.QryCurCsn.MaxRecord == 0 )  // ������
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
					// 1.�ɶ��ʺ� 2.�������  3.֤ȯ����  4.֤ȯ����  5.ί������  6.ί�м۸�
					// 7.��ͬ��   8.�ɽ�����  9.�ɽ��۸� 10.ί��״̬ 11.�ɽ�״̬ 12.�ɽ�ʱ��
					//13.����    14.������Ϣ 15.�ɹ���־ 16.�г�����
					int ret=	_gateway->WaitAnswer(cmd.c_str(),16,0)  ;
					if (ret !=0)
					{
						this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"����ʧ��,%s",_gateway->GetRequestBuffer());
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
						//11 �������� 12 ������ͬ�� 14	�����г�����
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
		else // ������ѯ
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
			// 1.�ɶ��ʺ� 2.�������  3.֤ȯ����  4.֤ȯ����  5.ί������  6.ί�м۸�
			// 7.��ͬ��   8.�ɽ�����  9.�ɽ��۸� 10.ί��״̬ 11.�ɽ�״̬ 12.�ɽ�ʱ��
			//13.����    14.������Ϣ 15.�ɹ���־ 16.�г�����

			int ret = _gateway->WaitAnswer(cmd.c_str(),16,0);
			if (ret !=0)
			{
				this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"����ʧ��,%s",_gateway->GetRequestBuffer());
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
				//11 �������� 12 ������ͬ�� 14	�����г�����
				sprintf(ci->SeqNum ,"%s|%s|%s|%s|", _gateway->GetFieldValue(i,13).c_str() ,
					_gateway->GetFieldValue(i,7).c_str() ,
					_setup.entrust_way.c_str() ,
					_gateway->GetFieldValue(i,16).c_str());
			}
		}
	}
	catch( Exception &e )
	{
		this->SetLastError(-1,'E',PLUGINNAME,"�쳣����,%s",AnsiString(e.Message));
		return -1;
	}
	return 0;
}


int TTrdItf_JSD_GD::QryCurTrd()    //���ճɽ���ѯ
{
	AnsiString cmd;

	//  1.���ܺ�(13)   2.����Ӫҵ������  3.�г�����     4.��ʱ����      5.�ͻ���
	//  6.��෵������ 7.����֤ȯ����    8.�����ɶ��ʺ� 9.�����ɽ���� 10.ί�з�ʽ
	// 11.�����г����루v5.83�����г�����=0��ѯ����ʱ�������룩
	//
	try
	{
		if (FRequest.QryCurTrd.OrderID[0] != 0) // �鵥��ί�еĳɽ�
		{
        	return -1;
		}
		else if(FRequest.QryCurTrd.MaxRecord == 0)    // ������
		{
			//7.	����֤ȯ����|8.	�����ɶ��ʺ�|9.	�����ɽ����| 10.	ί�з�ʽ|11.	�����г����루v5.83�����г�����=0��ѯ����ʱ�������룩 |

			AnsiString seq = "|||" + _setup.entrust_way + "||";
			TList *recList = new TList();
			//
			// 1.�ɶ��ʺ� 2.�������  3.֤ȯ����  4.֤ȯ����  5.�ɽ�����  6.�ɽ��۸�
			// 7.�ɽ�ʱ�� 8.�ɽ����  9.��ͬ���� 10.�г����루9-10Ϊv5.83ʵ�֣�
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
						this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"����ʧ��,%s",_gateway->GetRequestBuffer());
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
		else    // ������ѯ
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
				this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"����ʧ��,%s",_gateway->GetRequestBuffer());
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
		this->SetLastError(-1,'E',PLUGINNAME,"�쳣����,%s",AnsiString(e.Message));
		return -1;
	}
	return 0;
}

int TTrdItf_JSD_GD::QryStocks()    //��ѯ�ʺ������еĹɷ�
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
				//CMD ���ܺ�(10)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|��ѯ�г����루�ո��ʾ�����г���|
				//    --------------------------------7---------------------------------|
				//    ��ѯ֤ȯ���루Ϊ�ո�ʱ��ʾ��ѯ���й�Ʊ������ֻ��ѯĳһֻ��Ʊ�����|
				//    ---------------8----------------|-----9------|-----10-----|-----11-----|
				//    �ɶ����루�ո��ʾ���йɶ����룩|�����г�����|����֤ȯ����|�����ɶ��ʺ�|
				//    -----12-----|-----------13-----------|---14---|
				//    ��෵������|�������ܣ�1��ϸ��2���ܣ�|ί�з�ʽ|
				//    -----------------------------------------15------------------------------------------------|
				//    ���Ҵ��루v5.20.2ʵ�֣�����ѯ�г�����Ϊ�ն����Ҵ��벻Ϊ��ʱ�����ѯ�û��ҵ��г�{��A����A}��|
				//    -------------------16----------------------|-----------------17-------------------|
				//    �Ƿ񷵻غϼ�ֵ��1�����غϼ�ֵ�����������أ�|������ʼ���ڣ�Ϊ�գ������������Ϣ��|
				//
				//                 1| 2| 3|| 5| 6|7| 8| 9|10|11|12| |14||16||
				cmd.sprintf("10|%s|%s||%s|%s| |%s|%s|%s|%s|%d|1|%s||||",       //������ĵ�˵16�������
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

	

				//[3]A|10.0.38.11|100|2|0800044619|002282|�����|500|500|5750.000|0.000|11.500|11.500|500|5750.000|0.000| | |11.500|0.000|11.500|
				//  1.�г�����  2.�ɶ��ʺ�   3.֤ȯ����        4.֤ȯ����  5.���(���ϵ��ճɽ�)
				//  6.�������  7.��ֵ(����) 8.����ӯ��(����)  9.�ɱ��۸� 10.�������¼�
				// 11.���տ������          12.��Ʊ��ֵ(����) 13.����ӯ��(���տ��)
				// 14.��������              15.һ�仰������Ϣ 16.��ծ���� 17.ÿ��ԪӦ����Ϣ(���ǹ�ծΪ0)

				int ret = _gateway->WaitAnswer(cmd.c_str(),17,false);
				if (ret !=0)
				{
					this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"����ʧ��,%s",_gateway->GetRequestBuffer());
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
		this->SetLastError(-1,'E',PLUGINNAME,"�쳣����,%s",AnsiString(e.Message));
		return -1;
	}

	return 0;
}

//////���׺���/////
//---------------------------------------------------------------------------
// CMD: ���ܺ�(3)|����Ӫҵ������|�г�����|��ʱ����|�ɶ��ʺ�|֤ȯ����|��������(1���롢2����)
//      |ί������|ί�м۸�|ί�з�ʽ|���б�־|���д���|
//---------------------------------------------------------------------------
int TTrdItf_JSD_GD::Order()
{
	AnsiString cmd;
	AnsiString et = ConvertMarketType(FRequest.Order.Market);

/*
	if (FRequest.Entrust.Prop == 1)
	{
		// 1.���ܺ�(202)  2.Ӫҵ������  3.�г�����  4.��ʱ����  5.�ͻ���
		// 6.�ɶ�����     7.�깺/��ر�־��1���깺��2����أ�
		// 8.�������     9.�깺�ݶ�    10.ί�з�ʽ
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
	// CMD: ���ܺ�(3)|����Ӫҵ������|�г�����|��ʱ����|�ɶ��ʺ�|֤ȯ����|
	//
	//      ----------7-----------|----8---|----9---|---10---|---11---|---12---|
	//      ��������(1���롢2����)|ί������|ί�м۸�|ί�з�ʽ|���б�־|���д���|
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
		this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"����ʧ��,%s",_gateway->GetRequestBuffer());
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


int TTrdItf_JSD_GD::Undo() //ί�г���
{

	AnsiString cmd;
	//
	//     ----1----|-------2------|----3---|----4---|---5--|---6--|----7---|
	//CMD: ���ܺ�(4)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|��ͬ��|ί�з�ʽ|
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
		this->SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"����ʧ��,%s",_gateway->GetRequestBuffer());
		return ret;
	}

	if( _setup.debug_mode )
	{
		ODS('M', PLUGINNAME,"REQ->%s\r\nRECV->%s", _gateway->GetRequestBuffer(),_gateway->GetReturnData() );
	}

	return 0;
}


