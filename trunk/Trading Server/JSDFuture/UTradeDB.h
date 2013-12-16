//---------------------------------------------------------------------------
#ifndef UTradeDBH
#define UTradeDBH
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include "sqlite3.h"
#include "UTrdStruct.h"


class trade_db
{
private:
	sqlite3     *db;
	std::string      filename;
	HANDLE hMutex;

public:
	trade_db();
	~trade_db();
	void Lock();
	void Unlock();
public:
	// �������ݿ�
	void connect(void);

	// �Ͽ�
	void disconnect(void);

	// ���½������б�
	void reset_tables(void);

	// �Ƿ�������
	bool is_connected(void) const
	{
		return (db!=NULL);
	}

	std::string& get_db_filename(void)
	{
        return filename;
    }

	// ����һ��ί�м�¼
	void add_order(std::string ord);

	// ����һ�����׼�¼������������¼,trdnum <0 ��ʾ������¼
	void add_trade(std::string ordid,std::string trdid,std::string cid,
		std::string code,char market,long time,long date,int trdnum,double trdprice,
		char ordtype);

	// ��ѯί�м�¼
	long qry_orders(std::string account,std::string ordid,std::string seqnum,long maxrec,
		std::vector<TOrderInfo> &list);

	// ��ѯ���׼�¼
	long qry_trades(std::string account,std::string ordid,std::string seqnum,long maxrec,
		std::vector<TTradeInfo> &list );

	char qry_order_market(std::string account,std::string ordid);
};



#endif
