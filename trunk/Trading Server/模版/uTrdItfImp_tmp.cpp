//---------------------------------------------------------------------------


#pragma hdrstop

#include "uTrdItfImp.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TTrdItfImp::TTrdItfImp(const char *psetupfile,ADDLOG plogfunc)
{

}

TTrdItfImp::~TTrdItfImp()
{

}

//��ʼ��
int TTrdItfImp::Init()
{

}

//�����ʺ�
int TTrdItfImp::SetAccount()
{

}

//�ʽ��ѯ
int TTrdItfImp::QryMoney()
{

}

//����ί�в�ѯ
int TTrdItfImp::QryCurCsn()
{

}

//���ճɽ���ѯ
int TTrdItfImp::QryCurTrd()
{

}

//��ѯ�ʺ������еĹɷ�
int TTrdItfImp::QryStocks()
{

}

//ί�г���
int TTrdItfImp::Order()
{

}

int TTrdItfImp::Undo()
{

}

market_type  TTrdItfImp::ConvertMarketType(const char *t)
{

}

order_type   TTrdItfImp::ConvertOrderType(const char *t)
{

}

order_state  TTrdItfImp::ConvertOrderState(const char *t)
{

}

pos_direction TTrdItfImp::ConvertPosDir(const char *t)
{

}

money_type   TTrdItfImp::ConvertMoneyType(const char *t)
{

}

char *  TTrdItfImp::ConvertMarketType(market_type t)
{

}

char *  TTrdItfImp::ConvertOrderType(order_type t)
{

}

char *  TTrdItfImp::ConvertOrderState(order_state t)
{

}

char *  TTrdItfImp::ConvertPosDir(pos_direction t)
{

}

char *  TTrdItfImp::ConvertMoneyType(money_type t)
{

}

//��������Ϣ������,���û�л�ȡ������������Ϣ����false
bool TTrdItfImp::GetConfig(void)
{

}

//��������Ϣ��д�������ļ�
void TTrdItfImp::SetConfig(void)
{

}

//�ر��м������
void TTrdItfImp::CloseLink(void)
{

}

int TTrdItfImp::KeepAlive(void)
{

}
