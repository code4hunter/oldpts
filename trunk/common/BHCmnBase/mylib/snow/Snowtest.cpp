//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Snowtest.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TSnowtest *)
{
  new TSnowtest(NULL);
}
//---------------------------------------------------------------------------
__fastcall TSnowtest::TSnowtest(TComponent* Owner)
  : TCustomPanel(Owner)
{
  FImage=new Graphics::TBitmap();
  FBKPicture=new TPicture();
  FTimer=new TTimer(this);
  FStrList=new TStringList();
  FTimer->Enabled=false;
  FTimer->Interval=10;
  FSpeed=20;
  FTimer->OnTimer=FTimerTimer;
  FSnowNumber=200;
  FMaxSize=6;
  FCenterFonts=true;
  FFontX=10;
  this->Caption="COPYRIGHT CODEHUNTER 1998-2001";
  this->BevelOuter=bvNone;
}
//---------------------------------------------------------------------------
namespace Snowtest
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TSnowtest)};
     RegisterComponents("Samples", classes, 0);
  }
}
//---------------------------------------------------------------------------

void __fastcall TSnowtest::SetSnowNumbers(int value)
{
  if(FSnowNumber != value)
  {
    if(FActive)
    {
      SetActive(false);
      FSnowNumber = value;
      SetActive(true);
    }
    else
      FSnowNumber = value;
  }
}

void __fastcall TSnowtest::SetSnowMasSize(int value)
{
  if(FMaxSize != value)
  {
    if(FActive)
    {
      SetActive(false);
      FMaxSize = value;
      SetActive(true);
    }
    else
      FMaxSize = value;
  }
}

void __fastcall TSnowtest::SetActive(bool value)
{
  if(FActive != value)
  {
    if(Width>0&&Height>0)
    {
      FActive = value;
      if(FActive)
      {
        InitSnows();
      }
      FTimer->Enabled=FActive;
    }
  }
}

void __fastcall TSnowtest::SetPicture(TPicture * value)
{
  if(FBKPicture != value)
  {
    FBKPicture->Assign(value);
    if(FBKPicture->Width>0)
      this->Width=FBKPicture->Width;
    if(FBKPicture->Height>0)
      this->Height=FBKPicture->Height;
  }
}

void __fastcall TSnowtest::SetText(TStringList * value)
{
  if(FStrList != value)
  {
    FStrList->Assign(value);
  }
}

//---------------------------------------------------------------------------

void __fastcall TSnowtest::FTimerTimer(TObject * Sender)
{
  static int y=this->Height;
  this->Canvas->Draw(0,0,FImage);//将画好的帧画到窗口上
  FImage->Canvas->Draw(0,0,FBKPicture->Graphic);//用背景重画帧
  if(y<-ReturnResults.tmHeight*FStrList->Count) y=this->Height;//字幕行数决定750这个值
  y--;
  DrawText(FImage->Canvas,FImage->Width,FFontX,y);//将文本画在新的帧上
  randomize();
  int temp;
  FImage->Canvas->Pen->Style=psClear;
  for(int i=0;i<FSnowNumber;i++)
  {
    if(FSnows[i].sp.y>this->Height)
    {
      FSnows[i].sp.y=0;
      FSnows[i].sp.x=rand()%this->Width;
    }
    FSnows[i].sp.y+=4;
    temp=rand()%100;
    if(temp<50)
      FSnows[i].sp.x++;
    else
      FSnows[i].sp.x--;
    DrawSnows(FImage->Canvas,FSnows[i]);
  }
}

__fastcall TSnowtest::~TSnowtest(void)
{
  delete FImage;
  delete FBKPicture;
  delete FTimer;
  delete FStrList;
}

void __fastcall TSnowtest::InitSnows()
{
  randomize();
  int temp;
  FSnows.Length=FSnowNumber;
  for(int i=0;i<FSnowNumber;i++)
  {
    FSnows[i].sp.x=rand()%this->Width;
    FSnows[i].sp.y=-rand()%this->Height;
    FSnows[i].ssize=rand()%FMaxSize;
    temp=rand()%255;
    if(temp<230) temp=255;
    FSnows[i].scolor=(TColor)RGB(temp,temp,temp);
  }
  FImage->Width=FBKPicture->Width;
  FImage->Height=FBKPicture->Height;
  if(FBKPicture->Width>0)
    this->Width=FBKPicture->Width;
  if(FBKPicture->Height>0)
    this->Height=FBKPicture->Height;
  FImage->Canvas->Font=this->Font;
  GetTextMetrics(FImage->Canvas->Handle,&ReturnResults);
}

//画雪花的函数
void __fastcall TSnowtest::DrawSnows(TCanvas *DCanvas,TSnow &p)
{
  DCanvas->Brush->Color=p.scolor;
  DCanvas->Ellipse(p.sp.x,p.sp.y,p.sp.x+p.ssize,p.sp.y+p.ssize);
}

//显示字幕的函数
void __fastcall TSnowtest::DrawText(TCanvas *DCanvas,int W,int x,int y)
{
  int dx;
  W/=2;
  DCanvas->Brush->Style =bsClear;
  DCanvas->Pen->Style=psSolid;
  for(int i=0;i< FStrList->Count;i++)
  {
    y+=ReturnResults.tmHeight;
    if(y>-10&&y<this->Height)
    {
      if(FCenterFonts)
        dx=W-(ReturnResults.tmAveCharWidth*FStrList->Strings[i].Length())/2;
      else
        dx=x;
      DCanvas->TextOutA(dx,y,FStrList->Strings[i]);
    }
  }
}

void __fastcall TSnowtest::SetSpeed(int value)
{
  if(FSpeed != value)
  {
    FSpeed = value;
    FTimer->Interval=FSpeed;
  }
}
