//---------------------------------------------------------------------------
#ifndef UTrdItf_Test2H
#define UTrdItf_Test2H
//---------------------------------------------------------------------------
#include "UTrdStruct.h"
#include "UTrdItfBase.h"

#include <system.hpp>
#include <stdlib.h>
#include <vector>
#include <systdate.h>


struct order
{
  long id;
  char code[20];
  double price;
  long num;
  long cancel;
  bool bcancel;
  long ord_num;
  TDateTime ord_time;
};

typedef std::vector<order> ORDERS;


//---------------------------------------------------------------------------
class TTrdItf_TEST2 : public TTrdItfBase
{
private:	// User declarations
    int  Init();  //��ʼ��
    int  SetAccount(); //�����ʺ�

    //////��ѯ����//////
    int  GetTrdInfo();   //ȡ���̿�����
    int  QryMoney();     //�ʽ��ѯ
    int  QryStock();     //�ɷݲ�ѯ
    int  QryCanBuy();    //ȡ��������
    int  QryDetail();    //�ɽ���ѯ
    int  QryHisDetail(); //��ʷ�ɽ���ѯ
    int  QryCsn();       //��ѯĳ��ί�к�ͬ
    int  QryCurCsn();    //����ί�в�ѯ
    int  QryHisCsn();    //��ʷί�в�ѯ
    int  QryCurTrd();    //���ճɽ���ѯ
    int  QryHisTrd();    //��ʷ�ɽ���ѯ
    int  QryBill();      //��ѯ�ʽ���ˮ�����ʵ���
    int  QryStocks();    //��ѯ�ʺ������еĹɷ�

    //////���׺���/////
    int  Buy();
    int  Sell();
    int  Undo(); //ί�г���

    static ORDERS FOrders;
    long FindID(char* id);
    static long FOrderID;

    virtual bs_type ConvertType(char *type)
    {
      return btNo;
    }

    virtual wt_state ConvertState(char *state)
    {
      return wsno;
    }

public:		// User declarations
    TTrdItf_TEST2();
    virtual  ~TTrdItf_TEST2();

    void CloseLink(void)
    {
      return;
    }

};

#endif
