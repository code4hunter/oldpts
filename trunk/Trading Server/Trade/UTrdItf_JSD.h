//---------------------------------------------------------------------------
#ifndef UTrdItf_JSDH
#define UTrdItf_JSDH
//---------------------------------------------------------------------------
#include "UTrdStruct.h"
#include "UTrdItfBase.h"
#include <IdTCPClient.hpp>
#include <IdIPWatch.hpp>
//---------------------------------------------------------------------------
#define DEF_HEAD_LEN            3
#define INDEX(n) n + DEF_HEAD_LEN - 1

#define DEF_ACK_OK              0
#define DEF_ACK_ERROR           -1
#define DEF_TIMEOUT             -100
#define DEF_INVALID_STOCKCODE   -101

#define DEF_OTHER_ERROR         -504

//const char * DETAIL_STATE = {"�ѳɽ�", "���ֳɽ�", "���ڳ���", "���ֳ���", "���⳷��", "��Ʊ����", "δ�ɽ�", "���걨", "��������", "�����ѷ�"};

enum jsd_entrust_way {zzwt = 1, rjwt, dhwt, kswt, wswt};


class TTrdItf_JSD : public TTrdItfBase
{
public:
    typedef struct
    {
      char   SvrIp[16];
      int    SvrPort;
      int    TimeOut;
      //
      jsd_entrust_way entrust_way;      //����ί�з�ʽ
      char   branch_no[4];              //Ӫҵ����
      char   money_type;

    } TJSDSet;
private:	// User declarations
    TIdTCPClient *FidTcp;
    TIdIPWatch   *FidIPWatch;    
    TJSDSet FJSDSet;

    AnsiString GetErrorText(int code, char *error);
    //AnsiString ReadFirstData();
    AnsiString ReadNextData();
    AnsiString ReadFirstData(AnsiString cmd);
    int  SplitData(AnsiString SD, TStringList *lstDD, int count);

    int  Init();  //��ʼ��
    int  SetAccount(); //�����ʺ�

    //////��ѯ����//////
    int  GetTrdInfo();   //ȡ���̿�����
    int  QryMoney();     //�ʽ��ѯ -
    int  QryStock();     //�ɷݲ�ѯ
    int  QryCanBuy();    //ȡ��������
    int  QryDetail();    //�ɽ���ѯ -
    int  QryHisDetail(); //��ʷ�ɽ���ѯ
    int  QryCsn();       //��ѯĳ��ί�к�ͬ
    int  QryCurCsn();    //����ί�в�ѯ
    int  QryHisCsn();    //��ʷί�в�ѯ
    int  QryCurTrd();    //���ճɽ���ѯ
    int  QryHisTrd();    //��ʷ�ɽ���ѯ
    int  QryBill();      //��ѯ�ʽ���ˮ�����ʵ���
    int  QryStocks();    //��ѯ�ʺ������еĹɷ�-

    //////���׺���/////
    int  Buy();      //-
    int  Sell();     //-
    int  Undo(); //ί�г���-

    virtual bs_type ConvertType(char * type)
    {
      if(strlen(type)>0)
      {
        if (strcmp(type,"��")==0)
          return btBuy;
        else if (strcmp(type, "��")==0)
          return btSell;
        else
        {
          if(type[0]=='1') return btBuy;
          else if(type[0]=='2') return btSell;
        }
      }

      return btNo;
    }

    virtual wt_state ConvertState(char *state)
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
public:		// User declarations
    TTrdItf_JSD(TJSDSet *set);
    virtual  ~TTrdItf_JSD();
    void CloseLink(void)
    {
      FidTcp->Disconnect();
    }

};

#endif
