//---------------------------------------------------------------------------

#ifndef uSafeStringH
#define uSafeStringH

#include <SyncObjs.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TSafeStrings : public TStringList
{
private:

protected:
  TCriticalSection * FCS;
public:
  void Lock(void)
  {
    FCS->Enter();
  }

  void Unlock(void)
  {
    FCS->Leave();
  }

  __fastcall TSafeStrings(void) : TStringList()
  {
    FCS = new  TCriticalSection();
  }

  __fastcall virtual ~TSafeStrings(void)
  {
    delete FCS;
  }
};


#endif
 