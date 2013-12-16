//---------------------------------------------------------------------------

#ifndef uTestThreadH
#define uTestThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------

#include "UItfTrd2.h"

class TestThread : public TThread
{            
private:
  char buf[255];
  int count;
protected:
  void __fastcall Execute();
public:
  __fastcall TestThread(bool CreateSuspended);
  void __fastcall UpdateCaption();
};

extern TItfTrd *pitf;
//---------------------------------------------------------------------------
#endif
 