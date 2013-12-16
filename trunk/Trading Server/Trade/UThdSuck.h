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
  TQueSuck *FQueSuck;               //����ָ����У�ͨ��newtask����������ָ����������
  TList    *FInSuck;                //������ȡ�õ�ָ��ת�Ƶ����TList�б���

  int  __fastcall GetScheme(TScheme *Scheme,String SchemeName);
  int  __fastcall GetInfo(String SecuID);
  int  __fastcall GetFromQue();     //��ȡָ������е�ָ�����ǿ�ʼ�µ����ɣ���������Ϣת��FLocalDtl���
                                    //�����нṹָ��ת�Ƶ�FInSuck�б���
                                    //�����ֹͣһ�����ɣ���ִ��ֹͣ����

protected:
  void __fastcall Execute();

public:
  __fastcall TThdSuck(bool CreateSuspended);
  __fastcall ~TThdSuck();

  void __fastcall NewTask(TQueItf *QueItf);
};
//---------------------------------------------------------------------------
#endif
