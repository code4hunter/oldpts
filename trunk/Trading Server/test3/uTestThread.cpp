//---------------------------------------------------------------------------

#include <objbase.h>
#include <vcl.h>

#pragma hdrstop

#include "uTestThread.h"
#include "uMain.h"
#include "UItfTrd.h"
#include <stdio.h>
#include <math.hpp>
#pragma package(smart_init)

TItfTrd *pitf=NULL;

__fastcall TestThread::TestThread(bool CreateSuspended)
: TThread(CreateSuspended)
{
	this->FreeOnTerminate=true;   
}
//---------------------------------------------------------------------------
void __fastcall TestThread::Execute()
{
	char errtext[1001];
	char sender[1010];
	int count =  frmMain->edOrderNum->Text.ToIntDef(100);
	int i= count;
	bool btestspeed= frmMain->cbTestSpeed->Checked ;
	strcpy(buf,"线程启动");
	TStrings *ordList= new TStringList();
	this->Synchronize(UpdateCaption);

	if( pitf != NULL )
	{
		while (i-->0)
		{
			char ordid[255];
			if( pitf->Order(AnsiString(frmMain->edCode->Text).c_str(),
				frmMain->edPrice->Text.ToDouble(),
				frmMain->edOrdNum->Text.ToInt(),
				frmMain->cbMarket->Text[1],
				frmMain->cbOrderType->Text[1],
				ordid,
				254) == 0 )
			{
				ordList->Add(ordid);
				pitf->Undo(ordid,frmMain->cbMarket->Text[1]);
				//strcpy(buf,ordid);
				//this->Synchronize(UpdateCaption);
			}
			else
			{
				pitf->GetLastError(errtext,1000,sender,100);
				strcpy(buf,errtext);
				this->Synchronize(UpdateCaption);
			}
		}

		for( int i=0;i<ordList->Count;i++)
		{
			if( pitf->Undo(AnsiString(ordList->Strings[i]).c_str(),frmMain->cbMarket->Text[1]) != 0 )
			{
				pitf->GetLastError(errtext,1000,sender,100);
				strcpy(buf,errtext);
				this->Synchronize(UpdateCaption);
			}
		}
	}
	else
	{

		TItfTrd itf("PTrdDll_RM2.dll");

		itf.Open();
		if(itf.Init(AnsiString(frmMain->edSvr->Text).c_str())==0)
		{
			if(
				itf.Login(AnsiString(frmMain->edAccount->Text).c_str(),AnsiString(frmMain->cbLoginType->Text)[1],
				AnsiString(frmMain->edPassword->Text).c_str())==0
				)
			{
				DWORD  oldtick = 0;

				if( frmMain->edCode->Text.Length() >0 )
				{

					oldtick = GetTickCount();
					while (i-->0)
					{
						char ordid[255];
						if( itf.Order(AnsiString(frmMain->edCode->Text).c_str(),
							frmMain->edPrice->Text.ToDouble(),
							frmMain->edOrdNum->Text.ToInt(),
							AnsiString(frmMain->cbMarket->Text)[1],
							frmMain->cbOrderType->Text[1],
							ordid,
							254) == 0 )
						{
							ordList->Add(ordid);
							//itf.Undo(ordid,frmMain->cbMarket->Text[1]);
							//strcpy(buf,ordid);
							//this->Synchronize(UpdateCaption);
						}
						else
						{
							if( !btestspeed )
							{
								itf.GetLastError(errtext,1000,sender,100);
								strcpy(buf,errtext);
								this->Synchronize(UpdateCaption);
							}
						}
					}
					sprintf(buf,"每秒钟下单笔数:%f",(count*1000.f)/Max((GetTickCount()-oldtick),1));
					this->Synchronize(UpdateCaption);

					oldtick = GetTickCount();
					for( int i=0;i<ordList->Count;i++)
					{
						if( itf.Undo(AnsiString(ordList->Strings[i]).c_str(),
							AnsiString(frmMain->cbMarket->Text)[1]) != 0 )
						{
							if( !btestspeed )
							{
								itf.GetLastError(errtext,1000,sender,100);
								strcpy(buf,errtext);
								this->Synchronize(UpdateCaption);
							}
						}
					}
					sprintf(buf,"每秒钟撤单笔数:%f",(ordList->Count*1000.f)/Max((GetTickCount()-oldtick),1));
					this->Synchronize(UpdateCaption);
				}

				oldtick = GetTickCount();
				if(  btestspeed )
				{
					// 测试查钱速度
					for( int i=0;i< count ;i++)
					{
						TMoneyInfo mi;
						itf.QryMoney(motRMB,mi);
					}
				}
				sprintf(buf,"每秒钟查钱笔数:%f",(count*1000.f)/Max((GetTickCount()-oldtick),1));
				this->Synchronize(UpdateCaption);

				itf.Close();
			}
			else
			{
				itf.GetLastError(errtext,1000,sender,100);
				strcpy(buf,errtext);
				this->Synchronize(UpdateCaption);
			}
		}
		else
		{
			itf.GetLastError(errtext,1000,sender,100);
			strcpy(buf,errtext);
			this->Synchronize(UpdateCaption);
		}
	}
	strcpy(buf,"线程关闭");
	this->Synchronize(UpdateCaption);
	frmMain->Memo1->Lines->AddStrings(ordList);
	delete ordList;
}
//---------------------------------------------------------------------------
void __fastcall TestThread::UpdateCaption()
{
	frmMain->Memo1->Lines->Add(buf);
}
