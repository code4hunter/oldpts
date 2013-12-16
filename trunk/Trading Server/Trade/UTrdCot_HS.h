//---------------------------------------------------------------------------
#ifndef UTrdCot_HSH
#define UTrdCot_HSH

#include "UTrdCot.h"
#include "UTrdItf_HS.h"
//---------------------------------------------------------------------------
class TTrdCot_HS : public TTrdCot
{
private:	// User declarations
  TTrdItfBase *FTrdItf;

  int __fastcall Request(TRequest Request,TAnswer **Answer,int &AnsCount);
  int __fastcall DeleteAns(TAnswer **Answer)
  {
    return FTrdItf->FreeAnswer(*Answer);
  }
public:		// User declarations
  __fastcall TTrdCot_HS(TTrdItf_HS::THSSet * hs);
  __fastcall ~TTrdCot_HS();
};
#endif
