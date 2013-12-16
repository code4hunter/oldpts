//---------------------------------------------------------------------------
#ifndef UThdSendH
#define UThdSendH

#include "UBasThdTrd.h"
//---------------------------------------------------------------------------
typedef std::queue<TQueItf*>TQueSend;
//---------------------------------------------------------------------------
class TThdSend :public TBasThdTrd
{
private:
  TQueSend *FQueSend;
  TList    *FInSend;                //������ȡ�õ�ָ��ת�Ƶ����TList�б���

  int  __fastcall GetScheme(TScheme *Scheme,String SchemeName);
  int  __fastcall GetInfo(String SecuID);
  int  __fastcall GetFromQue();
protected:
  void __fastcall Execute();

public:
  __fastcall TThdSend(bool CreateSuspended);
  __fastcall ~TThdSend();

  void __fastcall NewTask(TQueItf *QueItf);
};
//---------------------------------------------------------------------------
#endif
