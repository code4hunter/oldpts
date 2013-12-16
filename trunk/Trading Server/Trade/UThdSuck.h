//---------------------------------------------------------------------------
#ifndef UThdSuckH
#define UThdSuckH

#include "UBasThdTrd.h"
//---------------------------------------------------------------------------
typedef std::queue<TQueItf*>TQueSuck;
//---------------------------------------------------------------------------
class TThdSuck :public TBasThdTrd
{
private:
  TQueSuck *FQueSuck;               //吸纳指令队列，通过newtask方法将吸纳指令加入队列中
  TList    *FInSuck;                //队列中取得的指针转移到这个TList中保存

  int  __fastcall GetScheme(TScheme *Scheme,String SchemeName);
  int  __fastcall GetInfo(String SecuID);
  int  __fastcall GetFromQue();     //读取指令队列中的指令，如果是开始新的吸纳，则吸纳信息转入FLocalDtl存放
                                    //队列中结构指针转移到FInSuck中保存
                                    //如果是停止一个吸纳，则执行停止代码

protected:
  void __fastcall Execute();

public:
  __fastcall TThdSuck(bool CreateSuspended);
  __fastcall ~TThdSuck();

  void __fastcall NewTask(TQueItf *QueItf);
};
//---------------------------------------------------------------------------
#endif
