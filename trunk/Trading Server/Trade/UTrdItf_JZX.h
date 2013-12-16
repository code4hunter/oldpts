//---------------------------------------------------------------------------
#ifndef UTrdItf_JZXH
#define UTrdItf_JZXH
//---------------------------------------------------------------------------

#include "UTrdItfBase.h"
#include "UTrdStruct.h"
#include <windows.h>
#include "kcbpcli.h"

#define JZX_MAX_REC_NUM     "20"//��ѯÿ����෵�ؼ�¼��
#define JZX_MAX_REC_NUM_INT  20//��ֵ������GTJA_MAX_REC_NUMֵ����ͬ��
#define QL_MARKET_SH         "1"
#define QL_MARKET_SZ         "0"

//---------------------------------------------------------------------------
class TTrdItf_JZX : public TTrdItfBase
{
public:
    typedef struct
    {
      char ServerName[KCBP_SERVERNAME_MAX+1];/*�û��Զ����KCBP����������*/
      //int nProtocal; /*Э�����ͣ�0 ��ʾʹ��TCP*/
      char ServerAddr[KCBP_DESCRIPTION_MAX+1]; /*�����IP*/
      unsigned int ServerPort;/*����˶˿ں�*/

      char DptCode[20];//Ӫҵ������
      unsigned int Timeout;//���ӳ�ʱ20

      char UserName[20];
      char Password[20];
      char Operway;//������ʽ
      char SendQName[20];///*���Ͷ������ƣ��ɷ����ָ��*/
      char ReceiveQName[20];///*���ն������ƣ��ɷ����ָ��*/
    } TJZXSet;
private:
  TJZXSet FGTJASet;
  KCBPCLIHANDLE FHandle;

  int SetSytemParams(char *Funid, bool IsLogin);
  int CheckSqlExecute(void);
  int CheckRsOpen(void);

  int InitRequest(char *Funid, bool IsLogin=false);
  int ExecuteRequest(char *Funid);//return:0--success,100--have more results,

  String FOrderDate;
  int Order(char *BsType, char *SecuID, int Num, double Price, int &OrderNo);

  String FAccountType;
  TStrings *FSrcList, *FDstList;
  int QueryMoreResults(TStrings *pSrcList, TStrings *pDstList);

  char FEnPassword[50];
  int Encrypt(char *pSrc, char *pDst);

  char FCustid[50];
  int GetStkAccount(char *LogType, char *Logid, char *ZJ, char *SH, char *SZ);

  char FBankCode[100];

  char FKey[50];

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

    virtual bs_type ConvertType(char *type)
    {
      if(lstrcmpi(type, "B") == 0)
        return btBuy;
      else if(lstrcmpi(type, "S") == 0)
        return btSell;
      //else if(lstrcmpi(type, "1") == 0)//�깺��
      //  return btBuy;
      //else if(lstrcmpi(type, "2") == 0)//��أ�
      //  return btSell;
      
      return btNo;
    }

    virtual wt_state ConvertState(char *state)
    {
      //'0','δ��' ��lbm��ί�гɹ�д��δ����־
      //'1','����' ����ط�ʽ��,����ɨ��δ��ί��,����ί����Ϊ����״̬
      // '2','�ѱ�' ���̳ɹ���,���̻���д���ͱ�־Ϊ�ѱ�
      //'3','�ѱ�����' �ѱ�ί�г���
      //'4','���ɴ���' ���ֳɽ���ί�г���
      //'5','����' ���ֳɽ��󳷵��ɽ�
      //'6','�ѳ�' ȫ�������ɽ�
      //'7','����' �ѱ�ί�в��ֳɽ�
      //'8','�ѳ�' ί�л򳷵�ȫ���ɽ�
      //'9','�ϵ�' ί��ȷ��Ϊ�ѵ� 'A','����' 'B','����' ��̩ģʽ�У��ѱ����ӿڿ���δ�����ؿ�Ľ׶Σ���׼ģʽ���á�
      if(strlen(state)==0) return wsno;
      switch(state[0])
      {
        case '0':
        case '1':
        case 'A':
        case 'B':
          return wswb;
        case '2':
          return wsyb;
        case '3':
        case '4':
          return wsdc;
        case '5':
          return wsbw;
        case '6':
          return wsyc;
        case '7':
          return wsbc;
        case '8':
          return wscj;
        case '9':
          return wsyf;
        default:
          return wsno;
      }
    }
public:		// User declarations
    TTrdItf_JZX(TJZXSet *pSet);
    virtual  ~TTrdItf_JZX();
    void CloseLink(void);
};

#endif
