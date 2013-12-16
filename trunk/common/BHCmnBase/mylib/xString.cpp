//---------------------------------------------------------------------------
#pragma hdrstop

#include "xString.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
void SplitStr(const String Str,const String Delimiter,String & Str1,String & Str2)
{
  int iPos=Str.Pos(Delimiter);
  if(iPos>0)
  {
    Str1=Str.SubString(1,iPos-1);
    Str2=Str.SubString(iPos+Delimiter.Length(),Str.Length()-iPos+Delimiter.Length()-1);
  }
  else
  {
    Str1=Str;
    Str2="";
  }
}

String GetSubStr(const String Str,const String BegDelimiter,const String EndDelimiter)
{
  int Beg=Str.Pos(BegDelimiter)+BegDelimiter.Length();
  int End=Str.Pos(EndDelimiter);
  if(End>=Beg)
  {
    return Str.SubString(Beg,End-Beg);
  }
  return "";
}
