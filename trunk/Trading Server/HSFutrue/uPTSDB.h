//---------------------------------------------------------------------------

#ifndef uPTSDBH
#define uPTSDBH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TdmPTSDB : public TDataModule
{
__published:	// IDE-managed Components
	TADOConnection *cn;
	void __fastcall DataModuleDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TdmPTSDB(TComponent* Owner);
	bool ConnectToDB(WideString UDLFileName);
	void DisConnect(void);
	bool AddOrderReport( String account,
											 String ordid,
											 String execid,
											 long cxlqty,
											 long exeqty,
											 double exepx,
											 long exedate,
											 long exetime,
											 String seqno,
											 String remark);
};
//---------------------------------------------------------------------------
#endif
