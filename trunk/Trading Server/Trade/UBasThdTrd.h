//---------------------------------------------------------------------------
#ifndef UBasThdTrdH
#define UBasThdTrdH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <queue>
#include "..\..\Project\TrdDll\UItfTrd.h"
//---------------------------------------------------------------------------
enum TTrdState{tsFinish=0,tsStop,tsRunning};

struct TQueItf                    //队列中的结构
{
  char          SecuID[8];              //股票代码
  char          PtfName[8];             //投资组合名称
  long          Vol;                    //成交量
  char          Scheme[20];             //方案名称
  long          PriceLimit;             //价格限制
  long          VolLimit;               //量的上限
  double        AvgPrice;               //当前均价
  long          CurVol;                 //当前完成的量
  bool          StartTrd;               //启动交易还是停止交易
  TAccountInfo  AccountInfo;            //账号信息
  TTrdState     State;                  //交易状态
};
//---------------------------------------------------------------------------
class TBasThdTrd : public TThread
{
private:
protected:
  struct TScheme                    //方案结构
  {
    String  Name;                   //方案名称
    int     ConsignPrice;           //价格方案，如：成交价=0，买一价=1，买二价=2，买三价=3
    double  FloatMny;               //价格微调
    double  VolPercent;             //数量方案
    int     VolScheme;
    int     Vol1;
    int     Vol2;
    int     TrdSec;                 //触发条件
    int     Sec1;
    int     Sec2;
    int     TrdCancelTime;          //撤单方案
    double  TrdCancelPrc;
  };

  struct TLocalDtl                  //从队列中读取交易信息存放在本地列表的结构
  {
    String   SecuID;                //股票代码
    String   PtfName;               //投资组合名称
    int      LastTime;              //上次下单时间
    double   TrdX;                  //下单随机数或行情最新价
    int      QryTime;               //上次查询时间，间隔10秒查询一次成交情况,成交完成后撤单
    long     LastVol;               //上一次撤单前的累计成交量
    long     CurVol;                //当前下单的累计成交量
    double   LastPrc;               //上一次撤单前的累计金额
    long     TotalVol;              //完成吸纳需要达到的下单总成交量
    TScheme  *Scheme;               //方案结构
    double   PriceLimit;            //价格限制，吸纳时是上限，派发时是下限
    double   VolLimit;              //量上限
    TList    *TrdInfo;              //下单列表
    long     Locate;                //指针在FInSuck或FInSend中的位置
    int      ItfTrdPos;             //对应的账号列表中的指针位置
  };

  struct TTrdInfo                   //下单列表结构
  {
    String  ContractID;             //下单合同号
    long    Num;                    //本次下单需要完成的量
    long    CurVol;                 //当前完成的量
    double  Prc;                    //下单价格
    long    DoTime;                 //下单时间
    bool    HasUndo;                //目前是否已经撤单
  };

  TList     *FItfTrdLst;            //交易接口列表，一个账号一个
  TList     *FLocalDtl;             //线程中的股票信息列表，存放着TLocalDtl结构

  double    FZXJ;                   //成交价
  double    FPrice[3];              //三个申价
  long      FVolum[3];              //三个申量

  String    FErrMsg;
  TDateTime FRepTime;               //成交回报中的参数
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

