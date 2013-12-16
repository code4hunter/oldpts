//---------------------------------------------------------------------------
#ifndef xStringH
#define xStringH

#include <windows.h>
#include <classes.hpp>
//---------------------------------------------------------------------------
void SplitStr(const String Str,const String Delimiter,String & Str1,String & Str2);
String GetSubStr(const String Str,const String BegDelimiter,const String EndDelimiter);
//---------------------------------------------------------------------------
#endif
