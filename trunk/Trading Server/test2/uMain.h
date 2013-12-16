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

#include "UItfTrd.h"
#include "HQPoolSvrLib_OCX.h"

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
	TTabSheet *TabSheet4;
	TButton *btStartQry;
	TButton *btStopQry;
	TMemo *moTrade;
	TTimer *Timer2;
	TLabel *lbQryCount;
	TLabel *lbSeq;
	TCheckBox *cbAllStk;
	TTabSheet *TabSheet5;
	TMemo *moccAccs;
	TButton *btAddAccToqc;
	TListView *qcListview;
	TPanel *Panel4;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TSplitter *Splitter2;
	TButton *Button1;
	TButton *btLoadItf;
	TCheckBox *cbonlylist;
	TButton *Button5;
	TEdit *edCloseAmt;
	TLabel *lbMktValue;
	TCheckBox *cbPrint;
	TLabel *Label11;
	TMemo *Memo2;
	TButton *Button6;
    TButton *Button7;
    TButton *Button8;
    TMemo *moExcept;
    TCheckBox *cbFilter;
	TTimer *Timer3;
	TPanel *Panel5;
	TEdit *edExecTime;
	TButton *Button9;
	TButton *Button10;
	TButton *btHuiGou;
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
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall btStartQryClick(TObject *Sender);
	void __fastcall btStopQryClick(TObject *Sender);
	void __fastcall btAddAccToqcClick(TObject *Sender);
	void __fastcall btLoadItfClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
    void __fastcall Button7Click(TObject *Sender);
    void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Timer3Timer(TObject *Sender);
	void __fastcall btHuiGouClick(TObject *Sender);
private:	// User declarations
	AnsiString FQryTradeSeq;
	void addOrd(char *ordid);
    TPool *pool;
    double get_price(AnsiString code,AnsiString mkt,AnsiString ordtype,AnsiString price);

public:		// User declarations
  __fastcall TfrmMain(TComponent* Owner);

	void ShowLastErr(TItfTrd*trd,const char *acc);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
