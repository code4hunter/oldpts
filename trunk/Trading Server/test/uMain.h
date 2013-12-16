//---------------------------------------------------------------------------

#ifndef uMainH
#define uMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include "IdCompressorZLibEx.hpp"
#include "IdZLibCompressorBase.hpp"
#include <IdBaseComponent.hpp>

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
  TMemo *Memo1;
  TGroupBox *GroupBox2;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TLabel *Label4;
	TButton *btLogin;
	TButton *btWithdraw;
	TEdit *edCode;
	TEdit *edPrice;
	TEdit *edOrderID;
	TButton *btQryMoney;
	TButton *btQryOrderByID;
	TEdit *edOrdNum;
	TButton *btQryStocks;
	TButton *btQryOrder;
	TButton *btQryTrade;
	TLabeledEdit *edAccount;
	TLabeledEdit *edPassword;
	TPanel *Panel1;
	TComboBox *cbOrderType;
  TLabel *Label5;
  TBevel *Bevel1;
  TBevel *Bevel2;
  TSplitter *Splitter1;
	TButton *btGetAccount;
	TComboBox *cbHistoryAccount;
	TButton *btGetLastErr;
	TButton *btLogout;
	TComboBox *cbMarket;
	TLabel *Label6;
	TComboBox *cbLoginType;
	TButton *btOrder;
	TComboBox *cbMoneyType;
	TLabel *Label7;
	TEdit *edQryTrdSeq;
	TEdit *edSvr;
	TEdit *edQryOrderSeq;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *edQryNum;
	TButton *btMultThTest;
	TEdit *edThreadNum;
	TEdit *edOrderNum;
	TCheckBox *cbTestSpeed;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TListView *lvWorking;
	TListView *lvPos;
	TPanel *Panel2;
	TPanel *Panel3;
	TButton *btrefOrders;
	TButton *btCancelAll;
	TButton *btRfPosition;
	TButton *btClear;
	TButton *btLoadAll;
	TImageList *ImageList1;
	TTimer *Timer1;
	TCheckBox *cbautoqry;
	TEdit *edFixPrc;
  void __fastcall btLoginClick(TObject *Sender);
  void __fastcall btQryMoneyClick(TObject *Sender);
  void __fastcall btWithdrawClick(TObject *Sender);
  void __fastcall btQryOrderByIDClick(TObject *Sender);
  void __fastcall btQryStocksClick(TObject *Sender);
  void __fastcall btQryOrderClick(TObject *Sender);
	void __fastcall btQryTradeClick(TObject *Sender);
  void __fastcall btGetAccountClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall cbHistoryAccountChange(TObject *Sender);
	void __fastcall btGetLastErrClick(TObject *Sender);
	void __fastcall btLogoutClick(TObject *Sender);
	void __fastcall btOrderClick(TObject *Sender);
	void __fastcall btMultThTestClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btRfPositionClick(TObject *Sender);
	void __fastcall btClearClick(TObject *Sender);
	void __fastcall btLoadAllClick(TObject *Sender);
	void __fastcall btCancelAllClick(TObject *Sender);
	void __fastcall btrefOrdersClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall cbautoqryClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
