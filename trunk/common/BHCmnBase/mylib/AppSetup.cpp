//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AppSetup.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall TAppSetup::TAppSetup(const AnsiString PathName)
{
  FFileName=PathName;
  //ReadFromFile(FFileName);
}

//---------------------------------------------------------------------------
__fastcall TAppSetup::~TAppSetup(void)
{
}

//---------------------------------------------------------------------------
void __fastcall TAppSetup::ReadIni(void)
{
}

//---------------------------------------------------------------------------
void __fastcall TAppSetup::WriteIni(void)
{
}

//---------------------------------------------------------------------------
void __fastcall TAppSetup::ReadFromFile(const AnsiString PathName)
{
  AnsiString stemp=PathName;

  if (stemp=="")
    stemp=FFileName;

  FIniFile = new TIniFile(stemp);

  try
  {
    ReadIni();
  }
  __finally
  {
    delete FIniFile;
  }
}

//---------------------------------------------------------------------------
void __fastcall TAppSetup::SaveToFile(const AnsiString PathName)
{
  AnsiString stemp=PathName;

  if (stemp=="")
    stemp=FFileName;

  FIniFile = new TIniFile(stemp);

  //È¥³ýÖ»¶Á
	DWORD Attrs=GetFileAttributesA(stemp.c_str());
	if ((Attrs & FILE_ATTRIBUTE_READONLY))
	{
		SetFileAttributesA(stemp.c_str(), Attrs - FILE_ATTRIBUTE_READONLY);
	}

  try
  {
    WriteIni();
  }
  __finally
  {
    delete FIniFile;
  }
}

