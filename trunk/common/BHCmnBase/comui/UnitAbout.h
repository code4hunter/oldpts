//----------------------------------------------------------------------------
#ifndef UnitAboutH
#define UnitAboutH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <Controls.hpp>
#include <jpeg.hpp>
//----------------------------------------------------------------------------
class TAboutBox : public TForm
{
__published:
	TButton *OKButton;
  TLabel *Label2;
  TLabel *Label3;
  TLabel *Label5;
  TBevel *Bevel1;
  TLabel *Label4;
  TLabel *Label1;
	void __fastcall Label5MouseEnter(TObject *Sender);
  void __fastcall Label5MouseLeave(TObject *Sender);
  void __fastcall Label5Click(TObject *Sender);
private:
public:
	virtual __fastcall TAboutBox(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif    
