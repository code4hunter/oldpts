#ifndef UTrdCot_JSDH
#define UTrdCot_JSDH
//------------------------------------------------------------------------------
#include "UTrdStruct.h"
#include "UTrdCot.h"
#include "UTrdItf_JSD.h"
//------------------------------------------------------------------------------
class TTrdCot_JSD : public TTrdCot
{
private:	// User declarations
  TTrdItfBase *FTrdItf;

  int __fastcall Request(TRequest Request,TAnswer **Answer,int &AnsCount);
  int __fastcall DeleteAns(TAnswer **Answer)
  {
    return FTrdItf->FreeAnswer(*Answer);
  }
public:		// User declarations
  __fastcall TTrdCot_JSD(TTrdItf_JSD::TJSDSet *js);
  __fastcall ~TTrdCot_JSD();
};
//---------------------------------------------------------------------------
//extern PACKAGE TFClsBase *FClsBase;
//---------------------------------------------------------------------------


//------------------------------------------------------------------------------

#endif


