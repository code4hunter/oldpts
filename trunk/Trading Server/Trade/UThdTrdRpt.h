//---------------------------------------------------------------------------

#ifndef UThdTrdRptH
#define UThdTrdRptH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "..\..\CmnSpecial\URjlLib.h"
//---------------------------------------------------------------------------
class TThdTrdRpt : public TThread
{            
private:
  TItfTrd     *FItfTrd;
  TTradeInfo   FTrdInfo;
  TAccountInfo FAccInfo;

  HANDLE FMutex;

  TTradeInfo FTradeInfo[5000];

  void __fastcall TrdReport();

protected:
  void __fastcall Execute();

public:
  __fastcall TThdTrdRpt(bool CreateSuspended,TItfTrd *ItfTrd);
  void __fastcall ChangeAccount(TItfTrd *ItfTrd);
};
//---------------------------------------------------------------------------
#endif
