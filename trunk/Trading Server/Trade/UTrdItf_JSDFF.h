//---------------------------------------------------------------------------
#ifndef UTrdItf_JSDFFH
#define UTrdItf_JSDFFH
//---------------------------------------------------------------------------
//#include "UTrdStructFF.h"
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

enum jsdff_entrust_way {zzwtff = 1, rjwtff, dhwtff, kswtff, wswtff};

class TTrdItf_JSDFF : public TTrdItfBase
{
public:
    typedef struct
    {
      char   SvrIp[16];
      int    SvrPort;
      int    TimeOut;
      //
      jsdff_entrust_way entrust_way;      //����ί�з�ʽ
      char   branch_no[4];              //Ӫҵ������
      char   gw_ver;                    //V6����V5����
      char   jysID;                     //����������
      char   seatID[20];                //ϯλ��
      char   sysCenter[20];             //ϵͳ���ĺ�
      int    qry_type;
      char   JyCode[20];                    //���ױ���
    } TJSDSet;
private:	// User declarations
    TIdTCPClient *FidTcp;
    TIdIPWatch   *FidIPWatch;    
    TJSDSet       FJSDSet;

    AnsiString GetRequestHead(AnsiString FuncNo);
    AnsiString GetErrorText(int code, char *error);
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
    
    //int  QryMoneyFF();   //�ʽ��ѯ��ϸ

    int QryTrdState(char *Cid);    //ί��״̬��ѯ
    
    //////���׺���/////
    int  Buy();      //-
    int  Sell();     //-
    int  Undo(); //ί�г���-

    int  QryFutureCode(); //��ѯ����

    virtual bs_type ConvertType(char * type)
    {
      if(strlen(type)>0)
      {
        if (strcmp(type,"0")==0)
          return btBuy;
        else if (strcmp(type, "1")==0)
          return btSell;
        else
        {
          if(type[0]=='0') return btBuy;
          else if(type[0]=='1') return btSell;
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

  void DeStr(AnsiString Sour,TStringList* strList,AnsiString DivSign)
  {
    long n= Sour.Length();
    for ( int i=1; i<=n ;i++)
    {
      if( Sour[i] == DivSign[1] )
      {
        Sour[i] = '\r';
      }
    }

    strList->Text = Sour;

    /*
    AnsiString tmpStr;
    Sour  = Sour.Trim();

    for(;;) {
      if(Sour.AnsiPos(DivSign)==0) {break;}
      tmpStr = Sour.SubString(1,Sour.AnsiPos(DivSign)-1).Trim();
      if(tmpStr!="") { strList->Add(tmpStr);         }
      else           { strList->Add("byhd_null_str");}
      Sour = Sour.SubString(Sour.AnsiPos(DivSign)+DivSign.Length(),Sour.Length());
    }
    if(Sour.Trim()!="") {strList->Add(Sour.Trim());}
    */
  }

public:		// User declarations
    TTrdItf_JSDFF(TJSDSet *set);
    virtual  ~TTrdItf_JSDFF();
    void CloseLink(void)
    {
      FidTcp->Disconnect();
    }

};

#endif
