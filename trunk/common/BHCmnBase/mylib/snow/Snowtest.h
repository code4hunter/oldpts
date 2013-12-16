//---------------------------------------------------------------------------

#ifndef SnowtestH
#define SnowtestH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <sysdyn.h>
//---------------------------------------------------------------------------
// 定义雪花结构
struct TSnow
{
  TPoint sp;//雪花的坐标
  TColor scolor;//雪花的颜色
  unsigned int ssize;//雪花的大小
};

class PACKAGE TSnowtest : public TCustomPanel
{
private:
  int FSnowNumber;
  int FMaxSize;
  Graphics::TBitmap * FImage;
  TPicture * FBKPicture;
  TTimer * FTimer;
  bool FActive;
  TStringList * FStrList;
  DynamicArray<TSnow> FSnows;
  TEXTMETRIC ReturnResults;
  int FSpeed;
  bool FCenterFonts;
  int FFontX;

  void __fastcall SetSnowNumbers(int value);
  void __fastcall SetSnowMasSize(int value);
  void __fastcall SetActive(bool value);
  void __fastcall SetPicture(TPicture * value);
  void __fastcall SetText(TStringList * value);
  void __fastcall FTimerTimer(TObject * Sender);
  void __fastcall InitSnows();
  void __fastcall DrawSnows(TCanvas *DCanvas,TSnow &p);
  void __fastcall DrawText(TCanvas *DCanvas,int W,int x,int y);
  void __fastcall SetSpeed(int value);
protected:
public:
  virtual __fastcall TSnowtest(TComponent* Owner);
  __fastcall ~TSnowtest(void);

__published:
  __property int SnowNumbers  = { read=FSnowNumber, write=SetSnowNumbers ,default=200};
  __property int SnowMasSize  = { read=FMaxSize, write=SetSnowMasSize ,default=6 };
  __property bool Active  = { read=FActive, write=SetActive ,default=false };
  __property TPicture * Picture  = { read=FBKPicture, write=SetPicture };
  __property TStringList * Strs  = { read=FStrList, write=SetText };
  __property Font;
  __property int Speed  = { read=FSpeed, write=SetSpeed ,default=20};
  __property bool CenterFonts  = { read=FCenterFonts, write=FCenterFonts ,default=true };
  __property int FontX  = { read=FFontX, write=FFontX ,default=10};
  __property Visible ;
  __property OnEnter ;
	__property OnExit ;
  __property OnClick ;
  __property OnDblClick ;
};
//---------------------------------------------------------------------------
#endif
