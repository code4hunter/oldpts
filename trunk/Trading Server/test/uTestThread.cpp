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
					if( pitf->Order(frmMain->edCode->Text.c_str(),
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
					if( pitf->Undo(ordList->Strings[i].c_str(),frmMain->cbMarket->Text[1]) != 0 )
					{
						pitf->GetLastError(errtext,1000,sender,100);
						strcpy(buf,errtext);
						this->Synchronize(UpdateCaption);
					}
				}
	}
	else
	{

		TItfTrd itf("PTrdDll_RM.dll");

		itf.Open();
		if(itf.Init(frmMain->edSvr->Text.c_str())==0)
		{
			if(
				itf.Login(frmMain->edAccount->Text.c_str(),frmMain->cbLoginType->Text[1],frmMain->edPassword->Text.c_str())==0
				)
			{
				DWORD  oldtick = 0;

				if( frmMain->edCode->Text.Length() >0 )
				{

				oldtick = GetTickCount();
				while (i-->0)
				{
					char ordid[255];
					if( itf.Order(frmMain->edCode->Text.c_str(),
						frmMain->edPrice->Text.ToDouble(),
						frmMain->edOrdNum->Text.ToInt(),
						frmMain->cbMarket->Text[1],
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

				DWORD nowtick = GetTickCount();
				sprintf(buf,"每秒钟下单笔数:%f,%d,%d",((double)ordList->Count*1000.0f)/(double)Max(nowtick-oldtick,1),ordList->Count,nowtick-oldtick);
				this->Synchronize(UpdateCaption);

				oldtick = GetTickCount();
				for( int i=0;i<ordList->Count;i++)
				{
					if( itf.Undo(ordList->Strings[i].c_str(),frmMain->cbMarket->Text[1]) != 0 )
					{
						if( !btestspeed )
						{
							itf.GetLastError(errtext,1000,sender,100);
							strcpy(buf,errtext);
							this->Synchronize(UpdateCaption);
						}
					}
				}
				sprintf(buf,"每秒钟撤单笔数:%f",(ordList->Count*1000.0f)/(double)Max((GetTickCount()-oldtick),1));
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
				sprintf(buf,"每秒钟查钱笔数:%f",(count*1000.0f)/(double)Max((GetTickCount()-oldtick),1));
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