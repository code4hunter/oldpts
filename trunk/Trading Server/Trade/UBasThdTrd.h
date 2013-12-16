//---------------------------------------------------------------------------
#ifndef UBasThdTrdH
#define UBasThdTrdH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <queue>
#include "..\..\Project\TrdDll\UItfTrd.h"
//---------------------------------------------------------------------------
enum TTrdState{tsFinish=0,tsStop,tsRunning};

struct TQueItf                    //�����еĽṹ
{
  char          SecuID[8];              //��Ʊ����
  char          PtfName[8];             //Ͷ���������
  long          Vol;                    //�ɽ���
  char          Scheme[20];             //��������
  long          PriceLimit;             //�۸�����
  long          VolLimit;               //��������
  double        AvgPrice;               //��ǰ����
  long          CurVol;                 //��ǰ��ɵ���
  bool          StartTrd;               //�������׻���ֹͣ����
  TAccountInfo  AccountInfo;            //�˺���Ϣ
  TTrdState     State;                  //����״̬
};
//---------------------------------------------------------------------------
class TBasThdTrd : public TThread
{
private:
protected:
  struct TScheme                    //�����ṹ
  {
    String  Name;                   //��������
    int     ConsignPrice;           //�۸񷽰����磺�ɽ���=0����һ��=1�������=2��������=3
    double  FloatMny;               //�۸�΢��
    double  VolPercent;             //��������
    int     VolScheme;
    int     Vol1;
    int     Vol2;
    int     TrdSec;                 //��������
    int     Sec1;
    int     Sec2;
    int     TrdCancelTime;          //��������
    double  TrdCancelPrc;
  };

  struct TLocalDtl                  //�Ӷ����ж�ȡ������Ϣ����ڱ����б�Ľṹ
  {
    String   SecuID;                //��Ʊ����
    String   PtfName;               //Ͷ���������
    int      LastTime;              //�ϴ��µ�ʱ��
    double   TrdX;                  //�µ���������������¼�
    int      QryTime;               //�ϴβ�ѯʱ�䣬���10���ѯһ�γɽ����,�ɽ���ɺ󳷵�
    long     LastVol;               //��һ�γ���ǰ���ۼƳɽ���
    long     CurVol;                //��ǰ�µ����ۼƳɽ���
    double   LastPrc;               //��һ�γ���ǰ���ۼƽ��
    long     TotalVol;              //���������Ҫ�ﵽ���µ��ܳɽ���
    TScheme  *Scheme;               //�����ṹ
    double   PriceLimit;            //�۸����ƣ�����ʱ�����ޣ��ɷ�ʱ������
    double   VolLimit;              //������
    TList    *TrdInfo;              //�µ��б�
    long     Locate;                //ָ����FInSuck��FInSend�е�λ��
    int      ItfTrdPos;             //��Ӧ���˺��б��е�ָ��λ��
  };

  struct TTrdInfo                   //�µ��б�ṹ
  {
    String  ContractID;             //�µ���ͬ��
    long    Num;                    //�����µ���Ҫ��ɵ���
    long    CurVol;                 //��ǰ��ɵ���
    double  Prc;                    //�µ��۸�
    long    DoTime;                 //�µ�ʱ��
    bool    HasUndo;                //Ŀǰ�Ƿ��Ѿ�����
  };

  TList     *FItfTrdLst;            //���׽ӿ��б�һ���˺�һ��
  TList     *FLocalDtl;             //�߳��еĹ�Ʊ��Ϣ�б������TLocalDtl�ṹ

  double    FZXJ;                   //�ɽ���
  double    FPrice[3];              //�������
  long      FVolum[3];              //��������

  String    FErrMsg;
  TDateTime FRepTime;               //�ɽ��ر��еĲ���
  bool      FRepBuy;
  String    FRepSecuID;
  long      FRepVol;
  double    FRepPrice;

  void __fastcall AddTrd(TLocalDtl *l,String ContractID,long Num,double Prc);
  void __fastcall ClearTrd();
  void __fastcall DeleteTrd(int i);
  void __fastcall ShowErr();
  void __fastcall TrdRep();

  int __fastcall FindInLocal(String SecuID,String PtfName,TAccountInfo  AccountInfo);
  int __fastcall FindInLocal(TList *In,TQueItf *QueItf);
  int __fastcall FindItfTrd(TAccountInfo  AccountInfo);
  int __fastcall UndoAllTrd(TLocalDtl *l);

  virtual int  __fastcall GetFromQue()=0;
  virtual int  __fastcall GetScheme(TScheme *Scheme,String SchemeName)=0;
  virtual int  __fastcall GetInfo(String SecuID)=0;

  void __fastcall Execute();
public:
  __fastcall TBasThdTrd(bool CreateSuspended);
  __fastcall ~TBasThdTrd();

  virtual void __fastcall NewTask(TQueItf *QueItf)=0;
};
//---------------------------------------------------------------------------
inline void __fastcall TBasThdTrd::AddTrd(TLocalDtl *l,String ContractID,long Num,double Prc)
{
  TTrdInfo   *t = new TTrdInfo();
  t->ContractID = ContractID;
  t->Num        = Num;
  t->CurVol     = 0;
  t->Prc        = Prc;
  t->DoTime     = time(NULL);
  t->HasUndo    = false;

  l->LastTime   = time(NULL);
  l->TrdInfo->Add(t);
}
//---------------------------------------------------------------------------
inline void __fastcall TBasThdTrd::DeleteTrd(int i)
{
  TLocalDtl *l  = (TLocalDtl*)(FLocalDtl->Items[i]);

  delete l->Scheme;   l->Scheme = NULL;
  for(int j=0;j<(l->TrdInfo)->Count;j++)
    delete (TTrdInfo *)((l->TrdInfo)->Items[j]);
  delete l->TrdInfo;    l->TrdInfo = NULL;
  delete l;             l = NULL;
  FLocalDtl->Delete(i);
}
//---------------------------------------------------------------------------
inline void __fastcall TBasThdTrd::ClearTrd()
{
  for(int i=0;i<FLocalDtl->Count;i++) DeleteTrd(i);
  FLocalDtl->Clear();
}
//---------------------------------------------------------------------------
#endif

