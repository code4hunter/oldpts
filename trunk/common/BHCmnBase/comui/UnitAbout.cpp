//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitAbout.h"
#include "xSystem.h"
#include "versinfo.hpp"
//---------------------------------------------------------------------
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
    Label3->Caption=Format("Version %d.%d (Build %d.%d)",ARRAYOFCONST((
        vi->productMajorVersion(),
        vi->productMinorVersion(),
        vi->productBuild(),
        vi->productSubBuild())));
  }
  delete vi;

  Label1->Caption=Application->Title;
  Label2->Caption=Application->Title;
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


