//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitAbout.h"
#include "xSystem.h"
#include "versinfo.hpp"
//---------------------------------------------------------------------
#pragma link "Snowtest"
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
  Caption=Application->Title;
  VersionInfo *vi=new VersionInfo(AnsiString(Application->ExeName).c_str());
  if(vi->hasInfo())
  {
	Label3->Caption=Format(L"Version %d.%d (Build %d.%d)",ARRAYOFCONST((
		vi->productMajorVersion(),
		vi->productMinorVersion(),
		vi->productBuild(),
		vi->productSubBuild())));
  }
  delete vi;


  String s=ChangeFileExt(Application->ExeName,".bmp");
  if(FileExists(s))
  {
    logo->Picture->LoadFromFile(s);
    Label4->Caption="Copyright 2003-2004 ¹è¹È¿Æ¼¼ Corporation";
    Label5->Caption="";
  }
  Label1->Caption=Application->Title;
  Label2->Caption=Application->Title;
  logo->Active=true;
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::Label5MouseEnter(TObject *Sender)
{
  Label5->Font->Color=clBlue;
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::Label5MouseLeave(TObject *Sender)
{
  Label5->Font->Color=clBlack;
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::Label5Click(TObject *Sender)
{
  xInvokeExe(Label5->Caption,"");
}
//---------------------------------------------------------------------------


