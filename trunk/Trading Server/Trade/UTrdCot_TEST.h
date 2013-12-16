#ifndef UTrdCot_TESTH
#define UTrdCot_TESTH
//------------------------------------------------------------------------------
#include "UTrdStruct.h"
#include "UTrdCot.h"
#include "UTrdItf_TEST.h"
//------------------------------------------------------------------------------
class TTrdCot_TEST : public TTrdCot
{
private:	// User declarations
  TTrdItfBase *FTrdItf;

  int __fastcall Request(TRequest Request,TAnswer **Answer,int &AnsCount);
  int __fastcall DeleteAns(TAnswer **Answer)
  {
    return FTrdItf->FreeAnswer(*Answer);
  }
public:		// User declarations
  __fastcall TTrdCot_TEST();
  __fastcall ~TTrdCot_TEST();
};
//---------------------------------------------------------------------------
//extern PACKAGE TFClsBase *FClsBase;
//---------------------------------------------------------------------------


//------------------------------------------------------------------------------

#endif


