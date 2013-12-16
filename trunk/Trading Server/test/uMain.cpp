//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "UTrdStruct_Rm.h"
#include "uMain.h"
#include "UItfTrd.h"
#include "uTestThread.h"
#include <idzlib.hpp>

//---------------------------------------------------------------------------
#pragma link "IdCompressorZLibEx"
#pragma link "IdZLibCompressorBase"
#pragma resource "*.dfm"
TfrmMain *frmMain;

TItfTrd itf("PTrdDll_RM.dll");
//---------------------------------------------------------------------------

// return out buffer ,you need free the buffer,result is sizeof(out buffer)
int zlib_compress( const void * in,const int size ,void **out)
{
	*out= NULL;
	TStream *streamOut = new TMemoryStream();

	TStream *streamCompress= new TCompressionStream(Idzlib::clDefault,streamOut);
	try
	{
		streamCompress->WriteBuffer(in,size);
	}
	__finally
	{
		delete streamCompress;
	}

	__int64 outlen = streamOut->Size ;
	if( outlen>0 )
	{
		*out = new char[outlen +  sizeof(int) ];
		memcpy(*out,&size,sizeof(int));
		streamOut->Read((char*)(*out)+sizeof(int),outlen);
	}
	delete streamOut;

	return outlen+sizeof(int);
}

int zlib_decompress( const void *in,const int size,void **out)
{
	*out= NULL;
	TStream *streamIn = new TMemoryStream();
	streamIn->Write((char*)in+sizeof(int),size-sizeof(int));

	int outlen =0;
	memcpy(&outlen,in,sizeof(int));

	TStream *streamDecompress= new TDecompressionStream(streamIn);
	try
	{
		if( outlen>0 )
		{
			*out = new char[outlen];
			streamDecompress->Read(*out,outlen);
		}
	}
	__finally
	{
		delete streamDecompress;
		delete streamIn;
	}
	return outlen;
}

__fastcall TfrmMain::TfrmMain(TComponent* Owner)
  : TForm(Owner)
{
	int a= sizeof(TRequest);
	int b= sizeof(TAnswer);

	TRequest r;
	r.Head.Version = 1111;
	r.Order.Price = 99.9;

	void *out=NULL;
	int ret = zlib_compress( &r,sizeof(r),&out );
	Caption = IntToStr(a) + ":" + IntToStr(ret);

	TRequest *r2=NULL;
	void *out2 = NULL;
	int restory = zlib_decompress(out,ret,&out2 );

	r2 =  (TRequest *)out2;

	assert( r2->Head.Version == r.Head.Version );
	assert( r2->Order.Price == r.Order.Price );

	delete[] out;
	delete[] out2;


}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btLoginClick(TObject *Sender)
{
	Memo1->Lines->Add(Now().TimeString());
  double t,te;
  if(itf.Init(edSvr->Text.c_str())==0)
	{
		account_type as = cbLoginType->Text[1];

		String strAcc = edAccount->Text + " " +  edPassword->Text  ;
		if( cbHistoryAccount->Items->Text.Pos(strAcc) < 1 )
    {
				cbHistoryAccount->Items->Add(strAcc);
				cbHistoryAccount->Items->SaveToFile(Application->ExeName+".account.txt");
    }

		pitf = &itf;
		if(itf.Login(edAccount->Text.c_str(),as,edPassword->Text.c_str())==0)
    {
			btQryMoney->Click();
    }
    else
    {
			Memo1->Lines->Add("登录失败");
			btGetLastErr->Click();
    }
  }
	else
	{
		Memo1->Lines->Add("初始化柜台失败");
		btGetLastErr->Click();
	}
	PageControl1->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btQryMoneyClick(TObject *Sender)
{
	Memo1->Lines->Add(Now().TimeString());
	TMoneyInfo mi;
  int ret =itf.QryMoney(cbMoneyType->Text[1],mi) ;
	if(ret==0)
	{
  	Memo1->Lines->Add("币种：" + String(mi.MoneyType));
		Memo1->Lines->Add("余额：" + FloatToStr(mi.balance));
		Memo1->Lines->Add("可用：" + FloatToStr(mi.available));
  }
	else
	{
		Memo1->Lines->Add("查询余额失败:"+IntToStr(ret));
		btGetLastErr->Click();
	}
	PageControl1->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btWithdrawClick(TObject *Sender)
{
	Memo1->Lines->Add(Now().TimeString());
	//market_type b;
	if(edOrderID->Text.Length()==0) return;

	int ret =  itf.Undo(edOrderID->Text.c_str(),cbMarket->Text[1]);
	if(ret==0)
	{
		Memo1->Lines->Add(edOrderID->Text + "撤单成功");
  }
	else
	{
		Memo1->Lines->Add("撤单失败:" + IntToStr(ret));
		btGetLastErr->Click();
	}
	PageControl1->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btQryOrderByIDClick(TObject *Sender)
{
	market_type b;
  Memo1->Lines->Add(Now().TimeString());
	if(edOrderID->Text.Length()==0) return;

	TOrderInfo *ordinfo=NULL;
	int num = 1;
	if(itf.QryOrder(edOrderID->Text.c_str(),"",&ordinfo,num)==0)
	{
		if( num == 1 )
		{
			String text;
			text.printf(
			"ContractID = %s\r\n"
			"SecuID     = %s\r\n" 
			"Market     = %c\r\n" 
			"Time       = %d\r\n" 
			"Date       = %d\r\n" 
			"Type       = %c\r\n" 
			"State      = %c\r\n" 
			"CsnVol     = %d\r\n" 
			"CsnPrice   = %f\r\n" 
			"TrdVol     = %d\r\n" 
			"TrdPrice   = %f\r\n" 
			"CancelVol  = %d\r\n"
			"Account    = %s\r\n"
			"SeqNum     = %s\r\n",
											ordinfo[0].ContractID,
											ordinfo[0].SecuID,
											ordinfo[0].Market,
											ordinfo[0].Time,
											ordinfo[0].Date,
											ordinfo[0].Type,
											ordinfo[0].State,
											ordinfo[0].CsnVol,
											ordinfo[0].CsnPrice,
											ordinfo[0].TrdVol,
											ordinfo[0].TrdPrice,
											ordinfo[0].CancelVol,
											ordinfo[0].Account,
											ordinfo[0].SeqNum
			);
			Memo1->Lines->Add(text);
		}
		else
			Memo1->Lines->Add("返回数据条数不正确"+IntToStr(num));
		if(ordinfo!=NULL)
			itf.FreeAnswer(ordinfo);
	}
	else
	{
		Memo1->Lines->Add("Error");
		btGetLastErr->Click();
	}
	PageControl1->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btQryStocksClick(TObject *Sender)
{
	Memo1->Lines->Add(Now().TimeString());
	TStockInfo *si=NULL;
	int num=sizeof(TStockInfo);
	char buf[1255];

	if(itf.QryStocks(cbMarket->Text[1],&si,num)==0)
	{
		Memo1->Lines->Add(cbMarket->Text + "股份："+IntToStr(num));
		sprintf(buf,"%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s",
				"代码",
				"股东帐号",
				"余额",
				"可用",
				"拥有股数",
				"成本价",
				"当前价",
				"部位类型",
				"市场");

		Memo1->Lines->Add(buf);
		for(int i=0;i<num;i++)
		{
				sprintf(buf,"%10s,%10s,%10d,%10d,%10d,%10.3f,%10.3f,%10c,%10c",
				si[i].SecuID,
				si[i].Account,
				si[i].Balance,
				si[i].Available,
				si[i].PosNum,
				si[i].CostPrice,
				si[i].CurPrice,
				si[i].PosDir,
				si[i].Market);

				Memo1->Lines->Add(buf);
		}
	}
	else
	{
		Memo1->Lines->Add("查询股份失败");
		btGetLastErr->Click();
	}

	if(si)
	{
		itf.FreeAnswer(si);
	}
	PageControl1->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btQryOrderClick(TObject *Sender)
{
	Memo1->Lines->Add(Now().TimeString());
	TOrderInfo *ci=NULL;
	int num=edQryNum->Text.ToIntDef(10);
	if(itf.QryOrder("",edQryOrderSeq->Text.c_str(),&ci,num)==0)
	{
		Memo1->Lines->Add("查询当前委托："+IntToStr(num));

		char buf[1024];

		sprintf(buf,"%10s,%20s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%15s,%50s",
						"合同序号",
						"证券代码",
						"交易市场",
						"委托时间",
						"委托日期",
						"委托类型",
						"委托状态",
						"委托数量",
						"委托价格",
						"成交数量",
						"成交价格",
						"撤单数量",
						"股东代码",
						"定位串");
				Memo1->Lines->Add(buf);

		for(int i=0;i<num;i++)
		{
				sprintf(buf,"%10s,%20s,%10c,%10d,%10d,%10c,%10c,%10d,%10.3f,%10d,%10.3f,%10d,%15s,%50s",
											ci[i].ContractID,
											ci[i].SecuID,
											ci[i].Market,
											ci[i].Time,
											ci[i].Date,
											ci[i].Type,
											ci[i].State,
											ci[i].CsnVol,
											ci[i].CsnPrice,
											ci[i].TrdVol,
											ci[i].TrdPrice,
											ci[i].CancelVol,
											ci[i].Account,
											ci[i].SeqNum);
				Memo1->Lines->Add(buf);

				edQryOrderSeq->Text = ci[i].SeqNum ;
		}

	}
	else
	{
		Memo1->Lines->Add("查询委托失败");
		btGetLastErr->Click();
	}

	if(ci)
	{
		itf.FreeAnswer(ci);
	}
	PageControl1->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btQryTradeClick(TObject *Sender)
{
	TTradeInfo *ti=NULL;
	int num=edQryNum->Text.ToIntDef(10);
	int ret =  itf.QryTrade(edOrderID->Text.c_str(),edQryTrdSeq->Text.c_str(),&ti,num)  ;
	if(ret==0)
	{
		char buf[1024];
		if(!cbautoqry->Checked)
		{
			Memo1->Lines->Add("查询当日成交"+ IntToStr(num));
			sprintf(buf,"%10s,%20s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%50s",
					"合同序号",
					"证券代码",
					"成交编号",
					"成交时间",
					"成交日期",
					"买卖类别",
					"成交数量",
					"成交价格",
					"市场",
					"定位串"
					 );
			Memo1->Lines->Add(buf);
		}
		for(int i=0;i<num;i++)
		{
			sprintf(buf,"%10s,%20s,%10s,%10d,%10d,%10c,%10d,%10.3f,%10c,%50s",
					ti[i].ContractID,
					ti[i].SecuID,
					ti[i].TrdID,
					ti[i].Time,
					ti[i].Date,
					ti[i].Type,
					ti[i].Vol,
					ti[i].Price,
					ti[i].Market,
					ti[i].SeqNum );
			Memo1->Lines->Add(buf);
			if( ti[i].SeqNum[0] != 0 )
				edQryTrdSeq->Text = ti[i].SeqNum ;
		}
	}
	else
	{
		Memo1->Lines->Add("查询成交失败:"+ IntToStr(ret));
		btGetLastErr->Click();
	}

	if(ti)
	{
		itf.FreeAnswer(ti);
	}
	PageControl1->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btGetAccountClick(TObject *Sender)
{
	TAccountInfo ai;
	char txt[255];

	if( 0 == itf.GetAccInfo( ai ) )
  {
    sprintf( txt, "资金帐号:%s,密码:%s,上证股东:%s,深证股东:%s,金交所:%s",
									ai.Capital,ai.PW,ai.SH,ai.SZ,ai.FJJS);

    Memo1->Lines->Add( txt );
  }
  else
		Memo1->Lines->Add("调用GetAccInfo失败！");

	PageControl1->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
		String s = Application->ExeName+".account.txt";
		if( FileExists( s ) )
				cbHistoryAccount->Items->LoadFromFile(s);

		s = Application->ExeName+".cfg.txt";
		if( FileExists(s) )
		{
			TStrings * cfg = new TStringList();
			cfg->LoadFromFile(s);
			if( cfg->Count>=4 )
			{
				edCode->Text = cfg->Strings[0];
				edPrice->Text=cfg->Strings[1];
				edOrdNum->Text=cfg->Strings[2];
				edSvr->Text=   cfg->Strings[3];
			}
			delete cfg;
		}

		TListColumn *pcol = lvWorking->Columns->Add();
		pcol->Caption =  "合同序号";
		pcol->Width = 60;
		pcol = lvWorking->Columns->Add();
		pcol->Caption =  "证券代码";
		pcol->Width = 60;
		pcol = lvWorking->Columns->Add();
		pcol->Caption =  "交易市场";
		pcol->Width = 60;
		pcol = lvWorking->Columns->Add();
		pcol->Caption =  "委托时间";
		pcol->Width = 60;
		pcol = lvWorking->Columns->Add();
		pcol->Caption =  "委托日期";
		pcol->Width = 60;
		pcol = lvWorking->Columns->Add();
		pcol->Caption =  "委托类型";
		pcol->Width = 60;
		pcol = lvWorking->Columns->Add();
		pcol->Caption =  "委托状态";
		pcol->Width = 60;
		pcol = lvWorking->Columns->Add();
		pcol->Caption =  "委托数量";
		pcol->Width = 60;
		pcol = lvWorking->Columns->Add();
		pcol->Caption =  "委托价格";
		pcol->Width = 70;
		pcol = lvWorking->Columns->Add();
		pcol->Caption =  "成交数量";
		pcol->Width = 70;
		pcol = lvWorking->Columns->Add();
		pcol->Caption =  "成交价格";
		pcol->Width = 60;
		pcol = lvWorking->Columns->Add();
		pcol->Caption =  "撤单数量";
		pcol->Width = 60;
		pcol = lvWorking->Columns->Add();
		pcol->Caption =  "股东代码";
		pcol->Width = 60;

		this->Width = 900;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cbHistoryAccountChange(TObject *Sender)
{
		int i = cbHistoryAccount->ItemIndex ;
    if( i>-1 )
    {
        char buf[100];
        char *pPass = NULL;
				strncpy(buf,cbHistoryAccount->Items->Strings[i].c_str(),100);
        for( int i=0;i<100;i++)
        {
            if( buf[i] == ' ' )
            {
                buf[i] = 0;
                pPass = buf+i+1;
                break;
            }
        }
				edAccount->Text = buf ;
				edPassword->Text = pPass ;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btGetLastErrClick(TObject *Sender)
{
	char text[256];
	char sender[100];
	long errcode = itf.GetLastError(text,255,sender,100) ;
	if( errcode != 0 )
	{
		Memo1->Lines->Add(String("Sender:") + sender + String(", Error:") + text +
			String(",Code:")+IntToStr(errcode));
	}
	PageControl1->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btLogoutClick(TObject *Sender)
{
	Memo1->Lines->Add(Now().TimeString());
	Memo1->Lines->Add("登出");
	itf.Close();
	PageControl1->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btOrderClick(TObject *Sender)
{
	char ordid[255];
	if( itf.Order(edCode->Text.c_str(),
		edPrice->Text.ToDouble(),
		edOrdNum->Text.ToInt(),
		cbMarket->Text[1],
		cbOrderType->Text[1],
		ordid,
		254) == 0 )
	{
   	Memo1->Lines->Add("委托号为:" + String(ordid));
	}
	else
	{
		Memo1->Lines->Add("委托失败");
		btGetLastErr->Click();
	}
	PageControl1->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btMultThTestClick(TObject *Sender)
{
	if( MessageBox(this->Handle,"是否启动多个线程测试？","询问",MB_OKCANCEL  ) == ID_OK)
	{
		for( int i=0;i<edThreadNum->Text.ToIntDef(10) ;i++)
		{
			TestThread * pth  =  new TestThread(false);
		}
  }	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
	TStrings * cfg = new TStringList();
	cfg->Add(edCode->Text);
	cfg->Add(edPrice->Text);
	cfg->Add(edOrdNum->Text);
	cfg->Add(edSvr->Text);
	cfg->SaveToFile(Application->ExeName+".cfg.txt") ;
	delete cfg;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btRfPositionClick(TObject *Sender)
{
	lvPos->Items->Clear();
	TStockInfo *si=NULL;
	int num=sizeof(TStockInfo);

	lvPos->Items->BeginUpdate();
	if(itf.QryStocks(cbMarket->Text[1],&si,num)==0)
	{
		for(int i=0;i<num;i++)
		{
			TListItem *pItem = lvPos->Items->Add();
			pItem->Caption = si[i].SecuID;
			pItem->SubItems->Add(si[i].Account);
			pItem->SubItems->Add(IntToStr(si[i].Balance));
			pItem->SubItems->Add(IntToStr(si[i].Available));
			pItem->SubItems->Add(IntToStr(si[i].PosNum));
			pItem->SubItems->Add(FormatFloat("0.000",si[i].CostPrice));
			pItem->SubItems->Add(FormatFloat("0.000",si[i].CurPrice));
			pItem->SubItems->Add((char)si[i].PosDir);
			pItem->SubItems->Add(si[i].Market);

			if (si[i].PosDir == 'L') {
				pItem->ImageIndex = 8;
				pItem->SubItems->Add(FormatFloat("0.000",si[i].PosNum * (si[i].CurPrice - si[i].CostPrice)));
			}
			else if(si[i].PosDir == 'S')
			{
				pItem->ImageIndex = 10;
				pItem->SubItems->Add(FormatFloat("0.000",si[i].PosNum * (si[i].CostPrice-si[i].CurPrice)));
			}
			else if(si[i].PosDir == 'N')
			{
				pItem->ImageIndex = 9;
				pItem->SubItems->Add(FormatFloat("0.000",si[i].PosNum * (si[i].CurPrice - si[i].CostPrice)));
			}
			else
			{
				pItem->ImageIndex = 17;
				pItem->SubItems->Add("NA");
			}
		}
	}
	else
	{
		Memo1->Lines->Add("查询股份失败");
		btGetLastErr->Click();
	}

	if(si)
	{
		itf.FreeAnswer(si);
	}
	lvPos->Items->EndUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btClearClick(TObject *Sender)
{
	if(MessageBox(this->Handle,"是否确定要清仓？","询问",MB_OKCANCEL)	 ==IDOK )
	{
		TStockInfo *si=NULL;
		int num=sizeof(TStockInfo);

    float fix = edFixPrc->Text.ToDouble();

		if(itf.QryStocks(cbMarket->Text[1],&si,num)==0)
		{
			for(int i=0;i<num;i++)
			{
				char ordid[255] = {'\0'};
				bool bsucc = false;
				if( si[i].PosNum > 0)
				{
					if (si[i].PosDir == pdLong ) {
						if( itf.Order( si[i].SecuID,
							si[i].CurPrice-fix,
							si[i].PosNum,
							si[i].Market,
							otCloseSell,
							ordid,
							254) == 0 )
						{
							bsucc = true;
						}
					}
					else if(si[i].PosDir == pdShort) {
						char ordid[255];
						if( itf.Order( si[i].SecuID,
							si[i].CurPrice+fix,
							si[i].PosNum,
							si[i].Market,
							otCloseBuy,
							ordid,
							254) == 0 )
						{
							bsucc = true;
						}
					}
					else if(si[i].PosDir == pdNet) {
          	if( si[i].Available> 0 )
            {
              char ordid[255];
              if( itf.Order( si[i].SecuID,
                si[i].CurPrice-fix,
                si[i].Available,
                si[i].Market,
                otSell,
                ordid,
                254) == 0 )
              {
                bsucc = true;
              }
            }
					}

					if( bsucc == true && strlen(ordid)>0 )
					{
						TOrderInfo *ordinfo=NULL;
						int num = 1;
						if(itf.QryOrder(ordid,"",&ordinfo,num)==0)
						{
							if( num == 1 )
							{
								TListItem *pItem = lvWorking->Items->Add();
								pItem->Caption = ordinfo[0].ContractID;
								pItem->SubItems->Add(ordinfo[0].SecuID);
								pItem->SubItems->Add(ordinfo[0].Market);
               	pItem->SubItems->Add(IntToStr(ordinfo[0].Time));
								pItem->SubItems->Add(IntToStr(ordinfo[0].Date));
								pItem->SubItems->Add((char)ordinfo[0].Type);
								pItem->SubItems->Add((char)ordinfo[0].State);
								pItem->SubItems->Add(IntToStr(ordinfo[0].CsnVol));
								pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].CsnPrice));
								pItem->SubItems->Add(IntToStr(ordinfo[0].TrdVol));
								pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].TrdPrice));
								pItem->SubItems->Add(IntToStr(ordinfo[0].CancelVol));
								pItem->SubItems->Add(ordinfo[0].Account);
								pItem->ImageIndex = 4;
							}

							if(ordinfo!=NULL)
								itf.FreeAnswer(ordinfo);
						}
					}
				}
			}
		}
		else
		{
			Memo1->Lines->Add("查询股份失败");
			btGetLastErr->Click();
		}

		if(si)
		{
			itf.FreeAnswer(si);
		}
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btLoadAllClick(TObject *Sender)
{
	// load all working order
	lvWorking->Items->BeginUpdate();
	lvWorking->Items->Clear();
	TOrderInfo *ci=NULL;
	String seq = "";
	int num = 500;
	while (itf.QryOrder("",seq.c_str(),&ci,num)==0 && num > 0 )
	{
		for(int i=0;i<num;i++)
		{
			if( !(ci[i].State == osbw ||
					ci[i].State == osyc ||
					ci[i].State == oscj ||
					ci[i].State == osyf ) )
    	{
				TListItem *pItem = lvWorking->Items->Add();
				pItem->Caption = ci[i].ContractID;
				pItem->SubItems->Add(ci[i].SecuID);
				pItem->SubItems->Add(ci[i].Market);
				pItem->SubItems->Add(IntToStr(ci[i].Time));
				pItem->SubItems->Add(IntToStr(ci[i].Date));
				pItem->SubItems->Add((char)ci[i].Type);
				pItem->SubItems->Add((char)ci[i].State);
				pItem->SubItems->Add(IntToStr(ci[i].CsnVol));
				pItem->SubItems->Add(FormatFloat("0.000",ci[i].CsnPrice));
				pItem->SubItems->Add(IntToStr(ci[i].TrdVol));
				pItem->SubItems->Add(FormatFloat("0.000",ci[i].TrdPrice));
				pItem->SubItems->Add(IntToStr(ci[i].CancelVol));
				pItem->SubItems->Add(ci[i].Account);
				pItem->ImageIndex = 4;
			}
			seq = ci[i].SeqNum ;
		}
		
		if(ci)
		{
			itf.FreeAnswer(ci);
			ci = NULL;
		}
	}
	lvWorking->Items->EndUpdate();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btCancelAllClick(TObject *Sender)
{
	for (int i = 0; i < lvWorking->Items->Count; i++) {
		TListItem *pItem = lvWorking->Items->Item[i];
		if(itf.Undo(pItem->Caption.c_str(),mtNo)==0)
		{
			Memo1->Lines->Add(pItem->Caption + "撤单成功");
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btrefOrdersClick(TObject *Sender)
{
	for (int i = 0; i < lvWorking->Items->Count; i++) {
		TListItem *pItem = lvWorking->Items->Item[i];
		TOrderInfo *ordinfo=NULL;
		int num = 1;
		if(itf.QryOrder(pItem->Caption.c_str(),"",&ordinfo,num)==0)
		{
			if( num == 1 )
			{
      	pItem->SubItems->Clear();
				pItem->SubItems->Add(ordinfo[0].SecuID);
				pItem->SubItems->Add(ordinfo[0].Market);
				pItem->SubItems->Add(IntToStr(ordinfo[0].Time));
				pItem->SubItems->Add(IntToStr(ordinfo[0].Date));
				pItem->SubItems->Add((char)ordinfo[0].Type);
				pItem->SubItems->Add((char)ordinfo[0].State);
				pItem->SubItems->Add(IntToStr(ordinfo[0].CsnVol));
				pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].CsnPrice));
				pItem->SubItems->Add(IntToStr(ordinfo[0].TrdVol));
				pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].TrdPrice));
				pItem->SubItems->Add(IntToStr(ordinfo[0].CancelVol));
				pItem->SubItems->Add(ordinfo[0].Account);

				if (ordinfo[0].State>=osbw && ordinfo[0].State<=osyf) {
					pItem->ImageIndex = 14;
				}
				else
        	pItem->ImageIndex = 4;

			}

			if(ordinfo!=NULL)
				itf.FreeAnswer(ordinfo);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Timer1Timer(TObject *Sender)
{
	btQryTrade->Click();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cbautoqryClick(TObject *Sender)
{
	Timer1->Enabled = cbautoqry->Checked;
	Memo1->Lines->Add("自动查询当日成交");
	char buf[1024];
		sprintf(buf,"%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%50s",
				"合同序号",
				"证券代码",
				"成交编号",
				"成交时间",
				"成交日期",
				"买卖类别",
				"成交数量",
				"成交价格",
				"市场",
				"定位串"
				 );
	Memo1->Lines->Add(buf);
}
//---------------------------------------------------------------------------

