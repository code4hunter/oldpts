//---------------------------------------------------------------------------
#ifndef uDmPTSRFH
#define uDmPTSRFH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "UTrdStruct.h"

struct _ord_
{
	TOrderInfo oi;
	__int64 ordrepid;
};

//---------------------------------------------------------------------------
class TDataModule1 : public TDataModule
{
__published:	// IDE-managed Components
	TADOConnection *cn;
	void __fastcall DataModuleDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDataModule1(TComponent* Owner);

	bool ConnectToDB(WideString UDLFileName);
	__int64 AddOrder( String acc,
											 String instid,
											 double ordprice,
											 long ordqty,
											 String orgordid,
											 String ordtype,
											 String market,
											 char ordstate
											 );

	bool CancelOrder( __int64 ordid );

	bool AddOrderReport( __int64 ordid,
											 String instid,
											 String execid,
											 long execqty,
											 double execprice);

	int GetOrders( AnsiString acc,
								 AnsiString OrdId,
								 AnsiString PosStr,
								 TOrderInfo **OrdInfo,
								 int &Num);

	int GetOrderReports(AnsiString acc,
											AnsiString OrdId,
											AnsiString PosStr,
											TTradeInfo **TrdInfo,
											int &Num);

	int GetUnfilledOrders(AnsiString acc,_ord_**OrdInfo,int &Num);
};
//---------------------------------------------------------------------------
#endif
