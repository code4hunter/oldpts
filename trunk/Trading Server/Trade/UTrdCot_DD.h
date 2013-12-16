//---------------------------------------------------------------------------
#ifndef UTrdCot_DDH
#define UTrdCot_DDH

#include "UTrdCot.h"
#include "UTrdItf_DD.h"
//---------------------------------------------------------------------------
class TTrdCot_DD : public TTrdCot
{
private:	// User declarations
  TTrdItfBase *FTrdItf;

  int __fastcall Request(TRequest Request,TAnswer **Answer,int &AnsCount);
  int __fastcall DeleteAns(TAnswer **Answer)
  {
    return FTrdItf->FreeAnswer(*Answer);
  }
public:		// User declarations
  __fastcall TTrdCot_DD(TTrdItf_DD::TDDSet * ds);
  __fastcall ~TTrdCot_DD();
};
#endif
