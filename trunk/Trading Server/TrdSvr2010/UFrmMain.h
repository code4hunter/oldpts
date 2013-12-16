//---------------------------------------------------------------------------
#ifndef UFrmMainH
#define UFrmMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <SyncObjs.hpp>
#include "trayicon.h"
////////////////////////////////////////////////////////////////////////////
#include "server_socket.h"
#include "USetup.h"
#include "UKeepAliveTh.h"
#include <AppEvnts.hpp>
#include "uSafeString.h"

//---------------------------------------------------------------------------
enum TLogType { ltMsg, ltWarn, ltErr,ltODS };
class TFrmMain : public TForm
{

__published:	// IDE-managed Components
  TBevel *Bevel1;
  TSpeedButton *sbStart;
  TSpeedButton *sbStop;
  TSpeedButton *sbSetup;
  TSpeedButton *sbAbout;
  TStatusBar *sb;
  TMemo *log;
  TActionList *ActionList;
  TAction *start;
  TAction *stop;
  TAction *setup;
  TAction *about;
  TAction *restory;
  TPopupMenu *PopupMenu1;
  TMenuItem *N1;
  TMenuItem *N2;
  TMenuItem *N3;
  TMenuItem *N6;
  TMenuItem *N7;
  TMenuItem *N5;
  TTrayIcon *TrayIcon;
  TImageList *ImageList1;
  TTimer *Timer1;
  TAction *hsSetup;
  TMenuItem *N8;
  TMenuItem *E1;
	TApplicationEvents *ApplicationEvents1;
  void __fastcall aboutExecute(TObject *Sender);
  void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
  void __fastcall setupExecute(TObject *Sender);
  void __fastcall stopExecute(TObject *Sender);
  void __fastcall startExecute(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormActivate(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
  void __fastcall E1Click(TObject *Sender);
	void __fastcall TrayIconDblClick(TObject *Sender);
	void __fastcall ApplicationEvents1Minimize(TObject *Sender);
private:	// User declarations
  server_socket *FServer;
  void __fastcall UpdateStatus();
  TStrings *FLog;
  keep_alive_th *FKeepAliveTh;
  void __fastcall AddToLog(void);
  int FLogCur;
  void AddOrder(void);

public:		// User declarations
  __fastcall TFrmMain(TComponent* Owner);
  void LogIt(AnsiString Text,TLogType lt);
  TCriticalSection *CS;
protected:
  void __fastcall ClientDisconnected(TMessage &Message);

BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(MY_DISCONNECTED, TMessage, ClientDisconnected)
END_MESSAGE_MAP(TForm)

};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
extern PACKAGE TFrmMain *FrmMain;
extern PACKAGE TStp *g_stp;
//---------------------------------------------------------------------------
#endif
