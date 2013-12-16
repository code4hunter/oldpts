#ifndef UTrdCot_JZH
#define UTrdCot_JZH
//------------------------------------------------------------------------------
#include "UTrdCot.h"
#include "UTrdItf_JZ.h"
//------------------------------------------------------------------------------
class TTrdCot_JZ : public TTrdCot
{
private:	// User declarations
  TTrdItfBase *FTrdItf;
  //String      FAppPath;

  int __fastcall Request(TRequest Request,TAnswer **Answer,int &AnsCount);
  int __fastcall DeleteAns(TAnswer **Answer)
  {
    return FTrdItf->FreeAnswer(*Answer);
  }
public:		// User declarations
  __fastcall TTrdCot_JZ(TTrdItf_JZ::TJZSet * js);
  __fastcall ~TTrdCot_JZ();
};
//---------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------

