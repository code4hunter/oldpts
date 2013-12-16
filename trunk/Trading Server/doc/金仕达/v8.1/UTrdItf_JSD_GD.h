//---------------------------------------------------------------------------
#ifndef UTrdItf_JSD_GDH
#define UTrdItf_JSD_GDH
//---------------------------------------------------------------------------
#include "UTrdItfBase.h"
#include "JsdGateway.h"
//#include <Classes.hpp>
//---------------------------------------------------------------------------


//const char * DETAIL_STATE = {"�ѳɽ�", "���ֳɽ�", "���ڳ���", "���ֳ���", "���⳷��", "��Ʊ����", "δ�ɽ�", "���걨", "��������", "�����ѷ�"};



class TTrdItf_JSD_GD : public TTrdItfBase
{
public:
    //enum jsd_entrust_way {zzwt = 1, rjwt, dhwt, kswt, wswt,wzwt,bpwt};

    //;ί�з�ʽ0--������1--��������2--�绰��3--����ί�С�4--����ί�� 5-- ETFί�з�ʽ  6--bpwt
    typedef struct
    {
      char   SvrIp[16];
      int    SvrPort;
      int    TimeOut;
      //
      int    entrust_way;      //����ί�з�ʽ
      char   branch_no[4];              //Ӫҵ����
      char   money_type;

    } TJSDSet;
private:	// User declarations

  	JsdGateway *_gateway;

    string ClientIp;

    TJSDSet FJSDSet;

    int  Init();  //��ʼ��
    int  SetAccount(); //�����ʺ�

    //////��ѯ����//////
    int  QryQtn();   //ȡ���̿�����
    int  QryMoney();     //�ʽ��ѯ -
//    int  QryStock();     //�ɷݲ�ѯ
    int  QryDetail();    //�ɽ���ѯ -
    int  QryCurCsn();    //����ί�в�ѯ
    int  QryHisCsn();    //��ʷί�в�ѯ
    int  QryCurTrd();    //���ճɽ���ѯ
    int  QryHisTrd();    //��ʷ�ɽ���ѯ
    int  QryBill();      //��ѯ�ʽ���ˮ�����ʵ���
    int  QryStocks();    //��ѯ�ʺ������еĹɷ�-
    int  QryETFs();    //��ѯETF������Ϣ

    //////���׺���/////
    int  Entrust();      //-
    int  Undo(); //ί�г���-

    char ConvertBorS(char * type)
    {
      if(strlen(type)>0)
      {
        if (strcmp(type,"��")==0)
          return 'B';
        else if (strcmp(type, "��")==0)
          return 'S';
        else
        {
          if(type[0]=='1') return 'B';
          else if(type[0]=='2') return 'S';
        }
      }

      return 'N';
    }

    wt_status ConvertState(char *state)
    {
      if(lstrcmp(state,"�ѳɽ�")==0)
        return wscj;
      else if(lstrcmp(state,"���ڳ���")==0)
        return wsyc;
      else if(lstrcmp(state,"���ֳ���")==0)
        return wsbw;
      else if(lstrcmp(state,"���⳷��")==0)
        return wsyc;
      else if(lstrcmp(state,"��Ʊ����")==0)
        return wsyf;
      else if(lstrcmp(state,"δ�ɽ�")==0)
        return wsyb;
      else if(lstrcmp(state,"���걨")==0)
        return wsyb;
      else if(lstrcmp(state,"��������")==0)
        return wsdc;
      else if(lstrcmp(state,"�����ѷ�")==0)
        return wsdc;
      else
        return wsno;
    }

/*�г�����
  0--�ͻ��ţ�*--����Ż�ſ��ţ�#--���д���
  1--�Ϻ�A�ɣ�2--����A�ɣ�3--�Ϻ�B�ɣ�4--����B�ɣ�
*/

  TBourse ConvertBourse(const char *market)
  {
    if(strlen(market)<1) return bsXXX;
    switch(market[0]) {
      case '1': return bsSHS;
      case '2': return bsSZS;
      default:  return bsXXX;
    }
  }  
    
public:		// User declarations
    TTrdItf_JSD_GD(TJSDSet *set);
    virtual  ~TTrdItf_JSD_GD();
    void CloseLink(void)
    {
      _gateway->Disconnect();
    }

};

#endif
