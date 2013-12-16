//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include <Clipbrd.hpp>
#include "uMain.h"
#include "uTestThread.h"

#include <string>
#include <map>

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmMain *frmMain;

TItfTrd itf("PTrdDll_RM2.dll");

std::map<std::string,TItfTrd*> _itfs;

struct ITFDATA
{
	double reserve; // 保留的钱
};
std::map<std::string, ITFDATA> _itfs_data;
void clearAllItf(void);

//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btLoginClick(TObject *Sender)
{
	Application->Title =  edAccount->Text;
	this->Caption = Application->Title;
	Memo1->Lines->Add(Now().TimeString());
  double t,te;
  if(itf.Init(AnsiString(edSvr->Text).c_str())==0)
	{
		account_type as = AnsiString(cbLoginType->Text)[1];

		String strAcc = edAccount->Text + " " +  edPassword->Text  ;
		if( cbHistoryAccount->Items->Text.Pos(strAcc) < 1 )
    {
				cbHistoryAccount->Items->Add(strAcc);
				cbHistoryAccount->Items->SaveToFile(Application->ExeName+".account.txt");
    }

		pitf = &itf;
		if(itf.Login(AnsiString(edAccount->Text).c_str(),as,AnsiString(edPassword->Text).c_str())==0)
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

	int ret =  itf.Undo(AnsiString(edOrderID->Text).c_str(),cbMarket->Text[1]);
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
	int num = StrToInt(edQryNum->Text);
	if(itf.QryOrder(AnsiString(edOrderID->Text).c_str(),"",&ordinfo,num)==0)
	{
		if( num == 1 )
		{
			AnsiString text;
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
	if(itf.QryOrder("",AnsiString(edQryOrderSeq->Text).c_str(),&ci,num)==0)
	{
		Memo1->Lines->Add("查询当前委托："+IntToStr(num));

		char buf[1024];

		sprintf(buf,"%25s,%20s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%15s,%50s",
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
				sprintf(buf,"%25s,%20s,%10c,%10d,%10d,%10c,%10c,%10d,%10.3f,%10d,%10.3f,%10d,%15s,%50s",
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
	int ret =  itf.QryTrade(AnsiString(edOrderID->Text).c_str(),
		AnsiString(edQryTrdSeq->Text).c_str(),&ti,num)  ;
	if(ret==0)
	{
		char buf[1024];
		if(!cbautoqry->Checked)
		{
			Memo1->Lines->Add("查询当日成交"+ IntToStr(num));
			sprintf(buf,"%25s,%20s,%20s,%10s,%10s,%10s,%10s,%10s,%10s,%50s",
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
			sprintf(buf,"%25s,%20s,%20s,%10d,%10d,%10c,%10d,%10.3f,%10c,%50s",
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
    pool = NULL;
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

		try
		{
			moccAccs->Lines->LoadFromFile(Application->ExeName+".qcacc.txt");
		}
		catch(...)
		{

		}

		try
		{
			Memo2->Lines->LoadFromFile(Application->ExeName+".ords.txt");
		}
		catch(...)
		{

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

		pcol = qcListview->Columns->Add();
		pcol->Caption =  "合同序号";
		pcol->Width = 60;
		pcol = qcListview->Columns->Add();
		pcol->Caption =  "证券代码";
		pcol->Width = 60;
		pcol = qcListview->Columns->Add();
		pcol->Caption =  "交易市场";
		pcol->Width = 60;
		pcol = qcListview->Columns->Add();
		pcol->Caption =  "委托时间";
		pcol->Width = 60;
		pcol = qcListview->Columns->Add();
		pcol->Caption =  "委托日期";
		pcol->Width = 60;
		pcol = qcListview->Columns->Add();
		pcol->Caption =  "委托类型";
		pcol->Width = 60;
		pcol = qcListview->Columns->Add();
		pcol->Caption =  "委托状态";
		pcol->Width = 60;
		pcol = qcListview->Columns->Add();
		pcol->Caption =  "委托数量";
		pcol->Width = 60;
		pcol = qcListview->Columns->Add();
		pcol->Caption =  "委托价格";
		pcol->Width = 70;
		pcol = qcListview->Columns->Add();
		pcol->Caption =  "成交数量";
		pcol->Width = 70;
		pcol = qcListview->Columns->Add();
		pcol->Caption =  "成交价格";
		pcol->Width = 60;
		pcol = qcListview->Columns->Add();
		pcol->Caption =  "撤单数量";
		pcol->Width = 60;
		pcol = qcListview->Columns->Add();
		pcol->Caption =  "股东代码";
		pcol->Width = 20;
		pcol = qcListview->Columns->Add();
		pcol->Caption =  "账户";
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
				strncpy(buf,AnsiString(cbHistoryAccount->Items->Strings[i]).c_str(),100);
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
			String(L",Code:")+IntToStr((int)errcode));
	}
	//PageControl1->ActivePageIndex = 0;
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
	if( itf.Order(AnsiString(edCode->Text).c_str(),
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

	moccAccs->Lines->SaveToFile(Application->ExeName+".qcacc.txt");

	Memo2->Lines->SaveToFile(Application->ExeName+".ords.txt");

    if( pool != NULL )
        delete pool;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btRfPositionClick(TObject *Sender)
{
	lvPos->Items->BeginUpdate();

	lvPos->Items->Clear();
	TStockInfo *si=NULL;
	int num=sizeof(TStockInfo);

	market_type mt = cbMarket->Text[1];
	if( cbAllStk->Checked )
		mt = 'N';

	double mktvalue=0;

	if(itf.QryStocks(mt,&si,num)==0)
	{
		for(int i=0;i<num;i++)
		{
			if( si[i].Available<=0 && si[i].PosNum <=0 ) continue;
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

            int  revvlm = 0;
            if(cbFilter->Checked)
            {
            for(int j=0;j< moExcept->Lines->Count;j++)
            {
                String l = moExcept->Lines->Strings[j];
                int sp = l.Pos(",");
                if (sp>0) {
                    String code = l.SubString(1,sp-1);
                    int v= l.SubString(sp+1,l.Length()-sp).ToIntDef(0);

                    if (String(si[i].SecuID) == code) {
                        revvlm = v;
                        break;
                    }
                }
            }
            }

			if (si[i].PosDir == 'L') {
				pItem->ImageIndex = 8;
				pItem->SubItems->Add(FormatFloat("0.000",si[i].PosNum * (si[i].CurPrice - si[i].CostPrice)));
				//mktvalue+= si[i].PosNum*si[i].CostPrice;
			}
			else if(si[i].PosDir == 'S')
			{
				pItem->ImageIndex = 10;
				pItem->SubItems->Add(FormatFloat("0.000",si[i].PosNum * (si[i].CostPrice-si[i].CurPrice)));
				//mktvalue-= si[i].PosNum*si[i].CostPrice;
			}
			else if(si[i].PosDir == 'N')
			{
				pItem->ImageIndex = 9;
				pItem->SubItems->Add(FormatFloat("0.000",si[i].PosNum * (si[i].CurPrice - si[i].CostPrice)));
				mktvalue+= (si[i].PosNum-revvlm)*si[i].CostPrice;
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

	lbMktValue->Caption = FormatFloat("0.000",mktvalue);
}
//---------------------------------------------------------------------------
void TfrmMain::addOrd(char *ordid)
{
	if( strlen(ordid)>0 )
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
				pItem->SubItems->Add(IntToStr((int)ordinfo[0].Time));
				pItem->SubItems->Add(IntToStr((int)ordinfo[0].Date));
				pItem->SubItems->Add((char)ordinfo[0].Type);
				pItem->SubItems->Add((char)ordinfo[0].State);
				pItem->SubItems->Add(IntToStr((int)ordinfo[0].CsnVol));
				pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].CsnPrice));
				pItem->SubItems->Add(IntToStr((int)ordinfo[0].TrdVol));
				pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].TrdPrice));
				pItem->SubItems->Add(IntToStr((int)ordinfo[0].CancelVol));
				pItem->SubItems->Add(ordinfo[0].Account);
				pItem->ImageIndex = 4;
			}

			if(ordinfo!=NULL)
				itf.FreeAnswer(ordinfo);
		}
	}
}

void __fastcall TfrmMain::btClearClick(TObject *Sender)
{
	if(MessageBox(this->Handle,"是否确定要清仓？","询问",MB_OKCANCEL)	 ==IDOK )
	{
		double vClose = edCloseAmt->Text.ToDouble();
		double vAmt = lbMktValue->Caption.ToDouble();

		double closeRate = 0;
		if( vAmt >0.1 && vClose < vAmt )
			closeRate = vClose / vAmt;
        else
            closeRate = 1;

		TStockInfo *si=NULL;
		int stknum=0;

    	//float fix = edFixPrc->Text.ToDouble();

		market_type mt = cbMarket->Text[1];
		if( cbAllStk->Checked )
			mt = 'N';

		AnsiString txt;
		if(itf.QryStocks(mt,&si,stknum)==0)
		{
			for(int i=0;i<stknum;i++)
			{
                if( (moExcept->Text.Pos(String(si[i].SecuID))>0)  && (!cbFilter->Checked))
                    continue;

                int  revvlm =0;
                for(int j=0; j< moExcept->Lines->Count;j++)
                {
                    String l = moExcept->Lines->Strings[j];
                    int sp = l.Pos(",");
                    if (sp>0) {
                        String code = l.SubString(1,sp-1);
                        int v= l.SubString(sp+1,l.Length()-sp).ToIntDef(0);

                        if (String(si[i].SecuID) == code) {
                            revvlm = v;
                            break;
                        }
                    }
                }
				char ordid[255] = {'\0'};
				bool bsucc = false;
				if( si[i].PosNum-revvlm > 0)
				{
					int num = ((int)((si[i].Available-revvlm)*closeRate)) /100*100;
					if (si[i].PosDir == pdLong ) {
                        double price = get_price( AnsiString(si[i].SecuID),
                            AnsiString((char)si[i].Market),AnsiString((char)otCloseSell),edFixPrc->Text);
						if( cbPrint->Checked )
						{
							txt.printf("-> %15s%10s%15f%10d%5c%5c",
										AnsiString(edAccount->Text).c_str(),
										si[i].SecuID,
										price,
										num,
										si[i].Market,
										otCloseSell);
							Memo1->Lines->Add(txt);
						}
						else{
                            if(num>0 && itf.Order( si[i].SecuID,
                                price,
                                num,
                                si[i].Market,
                                otCloseSell,
                                ordid,
                                254) == 0 )
                            {
                                addOrd(ordid);
                            }
                        }
					}
					else if(si[i].PosDir == pdShort) {
                        double price = get_price( AnsiString(si[i].SecuID),
                            AnsiString((char)si[i].Market),AnsiString((char)otCloseBuy),edFixPrc->Text);
						//char ordid[255];
						if( cbPrint->Checked )
						{
							txt.printf("-> %15s%10s%15f%10d%5c%5c",
										AnsiString(edAccount->Text).c_str(),
										si[i].SecuID,
										price,
										num,
										si[i].Market,
										otCloseBuy);
							Memo1->Lines->Add(txt);
						}
						else{
						if( num>0 && itf.Order( si[i].SecuID,
							price,
							si[i].PosNum,
							si[i].Market,
							otCloseBuy,
							ordid,
							254) == 0 )
						{
							addOrd(ordid);
						}
						}
					}
					else if(si[i].PosDir == pdNet) {
						if( si[i].Available>= num )
						{
							if( num>1000000 )
							{
								for(int j=0;j<num/1000000;j++)
								{
                                    double price = get_price( AnsiString(si[i].SecuID),
                                        AnsiString((char)si[i].Market),AnsiString((char)otSell),edFixPrc->Text);
									if( cbPrint->Checked )
									{
										txt.printf("-> %15s%10s%15f%10d%5c%5c",
													AnsiString(edAccount->Text).c_str(),
													si[i].SecuID,
												    price,
													1000000,
													si[i].Market,
													otSell);
										Memo1->Lines->Add(txt);
									}
									else{
										if( itf.Order( si[i].SecuID,
											price,
											1000000,
											si[i].Market,
											otSell,
											ordid,
											254) == 0 )
										{
											addOrd(ordid);
										}
									}
								}

								num = num %1000000 *100/100;
                                double price = get_price( AnsiString(si[i].SecuID),
                                        AnsiString((char)si[i].Market),AnsiString((char)otSell),edFixPrc->Text);
								if( cbPrint->Checked )
								{
									txt.printf("-> %15s%10s%15f%10d%5c%5c",
												AnsiString(edAccount->Text).c_str(),
												si[i].SecuID,
												price,
												num,
												si[i].Market,
												otSell);
									Memo1->Lines->Add(txt);
								}
								else{
                                    if( num>0 &&  itf.Order( si[i].SecuID,
                                        price,
                                        num,
                                        si[i].Market,
                                        otSell,
                                        ordid,
                                        254) == 0 )
                                    {
                                        addOrd(ordid);
                                    }
								}

							}
							else
							{
                                double price = get_price( AnsiString(si[i].SecuID),
                                        AnsiString((char)si[i].Market),AnsiString((char)otSell),edFixPrc->Text);
								//char ordid[255];
								if( cbPrint->Checked )
								{
									txt.printf("-> %15s%10s%15f%10d%5c%5c",
												AnsiString(edAccount->Text).c_str(),
												si[i].SecuID,
												price,
												num,
												si[i].Market,
												otSell);
									Memo1->Lines->Add(txt);
								}
								else{
                                    if( num>0 &&  itf.Order( si[i].SecuID,
                                        price,
                                        num,
                                        si[i].Market,
                                        otSell,
                                        ordid,
                                        254) == 0 )
                                    {
                                        addOrd(ordid);
                                    }
                                }
							}
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
	double amt=0;
	// load all working order
	lvWorking->Items->BeginUpdate();
	lvWorking->Items->Clear();
	TOrderInfo *ci=NULL;
	AnsiString seq = "";
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
				pItem->SubItems->Add(IntToStr((int)ci[i].Time));
				pItem->SubItems->Add(IntToStr((int)ci[i].Date));
				pItem->SubItems->Add((char)ci[i].Type);
				pItem->SubItems->Add((char)ci[i].State);
				pItem->SubItems->Add(IntToStr((int)ci[i].CsnVol));
				pItem->SubItems->Add(FormatFloat("0.000",ci[i].CsnPrice));
				pItem->SubItems->Add(IntToStr((int)ci[i].TrdVol));
				pItem->SubItems->Add(FormatFloat("0.000",ci[i].TrdPrice));
				pItem->SubItems->Add(IntToStr((int)ci[i].CancelVol));
				pItem->SubItems->Add(ci[i].Account);
				pItem->ImageIndex = 4;

				amt+= (ci[i].CsnVol-ci[i].TrdVol)*ci[i].CsnPrice;
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

	Label11->Caption = FormatFloat("0.000",amt);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btCancelAllClick(TObject *Sender)
{
	for (int i = 0; i < lvWorking->Items->Count; i++) {
		TListItem *pItem = lvWorking->Items->Item[i];

		if(itf.Undo(AnsiString(pItem->Caption).c_str(),
			(market_type)pItem->SubItems->Strings[1].ToInt())==0)
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
		if(itf.QryOrder(AnsiString(pItem->Caption).c_str(),"",&ordinfo,num)==0)
		{
			if( num == 1 )
			{
      			pItem->SubItems->Clear();
				pItem->SubItems->Add(ordinfo[0].SecuID);
				pItem->SubItems->Add(ordinfo[0].Market);
				pItem->SubItems->Add(IntToStr((int)ordinfo[0].Time));
				pItem->SubItems->Add(IntToStr((int)ordinfo[0].Date));
				pItem->SubItems->Add((char)ordinfo[0].Type);
				pItem->SubItems->Add((char)ordinfo[0].State);
				pItem->SubItems->Add(IntToStr((int)ordinfo[0].CsnVol));
				pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].CsnPrice));
				pItem->SubItems->Add(IntToStr((int)ordinfo[0].TrdVol));
				pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].TrdPrice));
				pItem->SubItems->Add(IntToStr((int)ordinfo[0].CancelVol));
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

void __fastcall TfrmMain::Timer2Timer(TObject *Sender)
{
	TTradeInfo *ti=NULL;
	int num=100;
	int ret =  itf.QryTrade("",FQryTradeSeq.c_str(),&ti,num)  ;
	if(ret==0)
	{
		char buf[1024];
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
			moTrade->Lines->Add(buf);
			if( ti[i].SeqNum[0] != 0 )
				FQryTradeSeq = ti[i].SeqNum ;
		}
		lbQryCount->Caption = IntToStr(lbQryCount->Caption.ToInt()+1);
		lbSeq->Caption = FQryTradeSeq;
	}
	else
	{
		moTrade->Lines->Add("查询成交失败:"+ IntToStr(ret));
		btGetLastErr->Click();
	}

	if(ti)
	{
		itf.FreeAnswer(ti);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btStartQryClick(TObject *Sender)
{
	FQryTradeSeq = "";
	moTrade->Lines->Clear();
	btStopQry->Enabled = true;
	btStartQry->Enabled = false;
	Timer2->Enabled = true;
	lbQryCount->Caption = L"0" ;
	lbSeq->Caption = L"";
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btStopQryClick(TObject *Sender)
{
	Timer2->Enabled = false;
	btStopQry->Enabled = false;
	btStartQry->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btAddAccToqcClick(TObject *Sender)
{
	moccAccs->Lines->Add(edSvr->Text + L" " + cbHistoryAccount->Text);
}
//---------------------------------------------------------------------------

void getAccount(UnicodeString line,AnsiString &svr,AnsiString &acc,AnsiString &pwd,double &reserve)
{
	char buf[255];
	char *pPass = NULL;
	char *pacc = NULL;
	char *preserve=NULL;
	strncpy(buf,AnsiString(line).c_str(),255);
	for( int i=0;i<255;i++)
	{
		if( buf[i] == ' ' )
		{
			buf[i] = 0;
			if( pacc != NULL )
				if( pPass != NULL )
					preserve=buf+i+1;
				else
					pPass = buf+i+1;
			else
				pacc = buf+i+1;
		}
	}

	svr = buf ;
	acc = pacc;
	pwd = pPass ;
	reserve = StrToFloatDef(UnicodeString(preserve),0);
}

void getOrder( AnsiString line,AnsiString &acc,AnsiString &code,
	AnsiString &mkt,AnsiString &num,AnsiString &price,AnsiString &ordtype,
	AnsiString &rev)
{
	char buf[255];
	int j=0;
	int field=0;
	for(int i=1;i<=line.Length();i++)
	{
		if( line[i] == ',' )
		{
			buf[j] =0;
			switch( field++ )
			{
			case 0:
				acc = buf;
			break;
			case 1:
				code = buf;
			break;
			case 2:
				mkt = buf;
			break;
			case 3:
				num =buf;
			break;
			case 4:
				price =buf;
			break;
			case 5:
				ordtype = buf;
			}
			j=0;
		}
		else
		{
			buf[j++] = line[i];
		}
	}

	if( field == 6)
	{
		buf[j]=0;
		rev = buf;
	}
}

void clearAllItf(void)
{
	std::map<std::string,TItfTrd*>::iterator itr1 ;;
	for( itr1=_itfs.begin() ;  itr1  !=  _itfs.end();  itr1++ )
	{
		TItfTrd* ptrd  = itr1->second ;
		if( ptrd != NULL )
		{
			ptrd->Close();
			delete ptrd;
		}
	}
	_itfs.clear();
}

void __fastcall TfrmMain::btLoadItfClick(TObject *Sender)
{
	int err=0;
	for( int i=0; i<moccAccs->Lines->Count; i++ )
	{
		UnicodeString line = moccAccs->Lines->Strings[i];
		AnsiString svr,acc,pwd;
		double rev;
		getAccount( line, svr,acc,pwd,rev );

		if( acc.Length() >0 )
		{
			_itfs_data[acc.c_str()].reserve = rev;
			TItfTrd* ptrd = _itfs[acc.c_str()];

			if( ptrd == NULL )
				_itfs[acc.c_str()] = new TItfTrd("PTrdDll_RM2.dll");

			ptrd = _itfs[acc.c_str()];

			if ( ptrd != NULL )
			{
				ptrd->Close();
				ptrd->Open();
				if( ptrd->Init(svr.c_str()) != 0)
				{
					err++;
					ShowLastErr(ptrd,acc.c_str());
				}
				else
				{
					if( ptrd->Login(acc.c_str(),'Z',pwd.c_str())!= 0 )
					{
						err++;
						ShowLastErr(ptrd,acc.c_str());
					}
				}
			}
		}
	}

	if( err>0 )
	{
		AnsiString eTxt;
		eTxt.printf("出现%d个错误",err);
		MessageBox(this->Handle,eTxt.c_str(),"载入错误",MB_OK);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	clearAllItf();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Button1Click(TObject *Sender)
{
	if(MessageBox(this->Handle,"是否确定要清仓？","询问",MB_OKCANCEL)	 ==IDOK )
	{
		AnsiString txt;
		TStockInfo *si=NULL;
		int stknum=0;

    	//float fix = edFixPrc->Text.ToDouble();

		std::map<std::string,TItfTrd*>::iterator itr1 ;;
		for( itr1=_itfs.begin() ;  itr1  !=  _itfs.end();  itr1++ )
		{
			TItfTrd* ptrd  = itr1->second ;
			if( ptrd != NULL )
			{
				if(ptrd->QryStocks('N',&si,stknum)==0)
				{
					for(int i=0;i<stknum;i++)
					{
						char ordid[255] = {'\0'};
						bool bsucc = false;
						if( si[i].PosNum > 0)
						{
							if (si[i].PosDir == pdLong ) {
                                double price = get_price( AnsiString(si[i].SecuID),
                                    AnsiString((char)si[i].Market),AnsiString((char)otCloseSell),edFixPrc->Text);
								if( cbonlylist->Checked )
								{
									txt.printf("-> %15s%10s%15f%10d%5c%5c",
										itr1->first.c_str(),
										si[i].SecuID,
										price,
										si[i].PosNum,
										si[i].Market,
										otCloseSell);
									Memo1->Lines->Add(txt);
								}
								else
								{
									if( ptrd->Order( si[i].SecuID,
										price,
										si[i].PosNum,
										si[i].Market,
										otCloseSell,
										ordid,
										254) == 0 )
									{
										bsucc = true;
									}
									else
									{
										Memo1->Lines->Add("委托失败");
										ShowLastErr(ptrd,itr1->first.c_str());
									}
								}
							}
							else if(si[i].PosDir == pdShort) {
                                double price = get_price( AnsiString(si[i].SecuID),
                                    AnsiString((char)si[i].Market),AnsiString((char)otCloseBuy),edFixPrc->Text);
								//char ordid[255];
								if( cbonlylist->Checked )
								{
									txt.printf("-> %15s%10s%15f%10d%5c%5c",
                                        itr1->first.c_str(),
										si[i].SecuID,
										price,
										si[i].PosNum,
										si[i].Market,
										otCloseBuy);
									Memo1->Lines->Add(txt);
								}
								else
								{
									if( ptrd->Order( si[i].SecuID,
										price,
										si[i].PosNum,
										si[i].Market,
										otCloseBuy,
										ordid,
										254) == 0 )
									{
										bsucc = true;
									}
									else
									{
										Memo1->Lines->Add("委托失败");
										ShowLastErr(ptrd,itr1->first.c_str());
									}
								}
							}
							else if(si[i].PosDir == pdNet) {
                                int num = si[i].Available;
                                if( num>0 )
                                {
                                    if( num>1000000 )
                                    {
                                        for(int j=0;j<num/1000000;j++)
                                        {
                                            double price = get_price( AnsiString(si[i].SecuID),
                                                AnsiString((char)si[i].Market),AnsiString((char)otSell),edFixPrc->Text);
                                            if( cbonlylist->Checked )
                                            {
                                                txt.printf("-> %15s%10s%15f%10d%5c%5c",
                                                            itr1->first.c_str(),
                                                            si[i].SecuID,
                                                            price,
                                                            1000000,
                                                            si[i].Market,
                                                            otSell);
                                                Memo1->Lines->Add(txt);
                                            }
                                            else{
                                                if( ptrd->Order( si[i].SecuID,
                                                    price,
                                                    1000000,
                                                    si[i].Market,
                                                    otSell,
                                                    ordid,
                                                    254) == 0 )
                                                {
                                                    bsucc = true;
                                                }
                                                else
                                                {
                                                    Memo1->Lines->Add("委托失败");
                                                    ShowLastErr(ptrd,itr1->first.c_str());
                                                }
                                            }
                                        }

                                        num = num %1000000;
                                        double price = get_price( AnsiString(si[i].SecuID),
                                                AnsiString((char)si[i].Market),AnsiString((char)otSell),edFixPrc->Text);
                                        if( cbonlylist->Checked )
                                        {
                                            txt.printf("-> %15s%10s%15f%10d%5c%5c",
                                                        itr1->first.c_str(),
                                                        si[i].SecuID,
                                                        price,
                                                        num,
                                                        si[i].Market,
                                                        otSell);
                                            Memo1->Lines->Add(txt);
                                        }
                                        else{
                                            if( num>0 &&  ptrd->Order( si[i].SecuID,
                                                price,
                                                num,
                                                si[i].Market,
                                                otSell,
                                                ordid,
                                                254) == 0 )
                                            {
                                                bsucc = true;
                                            }
                                            else
                                            {
                                                Memo1->Lines->Add("委托失败");
                                                ShowLastErr(ptrd,itr1->first.c_str());
                                            }
                                        }

                                    }
                                    else
                                    {
                                        double price = get_price( AnsiString(si[i].SecuID),
                                                AnsiString((char)si[i].Market),AnsiString((char)otSell),edFixPrc->Text);
                                        //char ordid[255];
                                        if( cbonlylist->Checked )
                                        {
                                            txt.printf("-> %15s%10s%15f%10d%5c%5c",
                                                        itr1->first.c_str(),
                                                        si[i].SecuID,
                                                        price,
                                                        num,
                                                        si[i].Market,
                                                        otSell);
                                            Memo1->Lines->Add(txt);
                                        }
                                        else{
                                            if( num>0 &&  ptrd->Order( si[i].SecuID,
                                                price,
                                                num,
                                                si[i].Market,
                                                otSell,
                                                ordid,
                                                254) == 0 )
                                            {
                                                bsucc = true;
                                            }
                                            else
                                            {
                                                Memo1->Lines->Add("委托失败");
                                                ShowLastErr(ptrd,itr1->first.c_str());
                                            }
                                        }
                                    }
                                }
							}

							if( bsucc == true && strlen(ordid)>0 )
							{
								TOrderInfo *ordinfo=NULL;
								int num = 1;
								if(ptrd->QryOrder(ordid,"",&ordinfo,num)==0)
								{
									//if( num == 1 )
									{
										TListItem *pItem = qcListview->Items->Add();
										pItem->Caption = ordinfo[0].ContractID;
										pItem->SubItems->Add(ordinfo[0].SecuID);
										pItem->SubItems->Add(ordinfo[0].Market);
										pItem->SubItems->Add(IntToStr((int)ordinfo[0].Time));
										pItem->SubItems->Add(IntToStr((int)ordinfo[0].Date));
										pItem->SubItems->Add((char)ordinfo[0].Type);
										pItem->SubItems->Add((char)ordinfo[0].State);
										pItem->SubItems->Add(IntToStr((int)ordinfo[0].CsnVol));
										pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].CsnPrice));
										pItem->SubItems->Add(IntToStr((int)ordinfo[0].TrdVol));
										pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].TrdPrice));
										pItem->SubItems->Add(IntToStr((int)ordinfo[0].CancelVol));
										pItem->SubItems->Add(ordinfo[0].Account);
										pItem->SubItems->Add(itr1->first.c_str());
										pItem->ImageIndex = 4;
									}

									if(ordinfo!=NULL)
										ptrd->FreeAnswer(ordinfo);
								}
							}
						}
					}
				}
				else
				{
					Memo1->Lines->Add("查询股份失败");
					ShowLastErr(ptrd,itr1->first.c_str());
				}

				if(si)
				{
					ptrd->FreeAnswer(si);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Button3Click(TObject *Sender)
{
	for (int i = 0; i < qcListview->Items->Count; i++) {
		TListItem *pItem = qcListview->Items->Item[i];

		TItfTrd* ptrd = _itfs[AnsiString(pItem->SubItems->Strings[12]).c_str()];

		if (ptrd!=NULL ) {
			if(ptrd->Undo(AnsiString(pItem->Caption).c_str(),mtNo)==0)
			{
				Memo1->Lines->Add(pItem->Caption + "撤单成功");
			}
		}
		else
			Memo1->Lines->Add( pItem->SubItems->Strings[12]+ "账户对应的接口不存在");
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Button2Click(TObject *Sender)
{
	qcListview->Items->BeginUpdate();
	try
	{
	for (int i = 0; i < qcListview->Items->Count; i++) {
		TListItem *pItem = qcListview->Items->Item[i];
		TOrderInfo *ordinfo=NULL;
		int num = 1;
		UnicodeString acc = pItem->SubItems->Strings[12];
		TItfTrd* ptrd = _itfs[AnsiString(acc).c_str()];
		if (ptrd!=NULL ) {
			if(ptrd->QryOrder(AnsiString(pItem->Caption).c_str(),"",&ordinfo,num)==0)
			{
				//if( num == 1 )
				{
					pItem->SubItems->Clear();
					pItem->SubItems->Add(ordinfo[0].SecuID);
					pItem->SubItems->Add(ordinfo[0].Market);
					pItem->SubItems->Add(IntToStr((int)ordinfo[0].Time));
					pItem->SubItems->Add(IntToStr((int)ordinfo[0].Date));
					pItem->SubItems->Add((char)ordinfo[0].Type);
					pItem->SubItems->Add((char)ordinfo[0].State);
					pItem->SubItems->Add(IntToStr((int)ordinfo[0].CsnVol));
					pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].CsnPrice));
					pItem->SubItems->Add(IntToStr((int)ordinfo[0].TrdVol));
					pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].TrdPrice));
					pItem->SubItems->Add(IntToStr((int)ordinfo[0].CancelVol));
					pItem->SubItems->Add(ordinfo[0].Account);
                    pItem->SubItems->Add(acc);

					if (ordinfo[0].State>=osbw && ordinfo[0].State<=osyf) {
						pItem->ImageIndex = 14;
				}
				else
					pItem->ImageIndex = 4;
				}

				if(ordinfo!=NULL)
					ptrd->FreeAnswer(ordinfo);
			}
		}
		else
			Memo1->Lines->Add( pItem->SubItems->Strings[12]+ "账户对应的接口不存在");
	}
	}
	__finally
	{
		qcListview->Items->EndUpdate();
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::Button4Click(TObject *Sender)
{
	// load all working order
	qcListview->Items->BeginUpdate();
	qcListview->Items->Clear();
	TOrderInfo *ci=NULL;

	std::map<std::string,TItfTrd*>::iterator itr1 ;;
	for( itr1=_itfs.begin() ;  itr1  !=  _itfs.end();  itr1++ )
	{
		TItfTrd* ptrd  = itr1->second ;
		if( ptrd != NULL )
		{
        	AnsiString seq = "";
			int num = 500;
			while (ptrd->QryOrder("",seq.c_str(),&ci,num)==0 && num > 0 )
			{
				for(int i=0;i<num;i++)
				{
					if( !(ci[i].State == osbw ||
							ci[i].State == osyc ||
							ci[i].State == oscj ||
							ci[i].State == osyf ) )
				{
						TListItem *pItem = qcListview->Items->Add();
						pItem->Caption = ci[i].ContractID;
						pItem->SubItems->Add(ci[i].SecuID);
						pItem->SubItems->Add(ci[i].Market);
						pItem->SubItems->Add(IntToStr((int)ci[i].Time));
						pItem->SubItems->Add(IntToStr((int)ci[i].Date));
						pItem->SubItems->Add((char)ci[i].Type);
						pItem->SubItems->Add((char)ci[i].State);
						pItem->SubItems->Add(IntToStr((int)ci[i].CsnVol));
						pItem->SubItems->Add(FormatFloat("0.000",ci[i].CsnPrice));
						pItem->SubItems->Add(IntToStr((int)ci[i].TrdVol));
						pItem->SubItems->Add(FormatFloat("0.000",ci[i].TrdPrice));
						pItem->SubItems->Add(IntToStr((int)ci[i].CancelVol));
						pItem->SubItems->Add(ci[i].Account);
						pItem->SubItems->Add(itr1->first.c_str());
						pItem->ImageIndex = 4;
					}
					seq = ci[i].SeqNum ;
				}

				if(ci)
				{
					ptrd->FreeAnswer(ci);
					ci = NULL;
				}
			}
		}
	}

	qcListview->Items->EndUpdate();
}
//---------------------------------------------------------------------------
void TfrmMain::ShowLastErr(TItfTrd*trd,const char *acc)
{
 	char text[256];
	char sender[100];
	long errcode = trd->GetLastError(text,255,sender,100) ;
	if( errcode != 0 )
	{
		Memo1->Lines->Add(String("Account:") + String(acc) + String(" Sender:") + sender + String(", Error:") + text +
			String(L",Code:")+IntToStr((int)errcode));
	}
}


void __fastcall TfrmMain::Button5Click(TObject *Sender)
{
	UnicodeString txt;

	for (int i = 0; i < lvWorking->Items->Count; i++) {
		TListItem *pItem = lvWorking->Items->Item[i];
		txt.cat_printf(L"%s",pItem->Caption.c_str());
		for(int j=0;j<pItem->SubItems->Count;j++)
		{
			txt.cat_printf(L",%s",pItem->SubItems->Strings[j].c_str());
		}
		txt.cat_printf(L"\n");
	}

	Clipboard()->SetTextBuf(txt.c_str());
}
//---------------------------------------------------------------------------

double TfrmMain::get_price(AnsiString code,AnsiString mkt,AnsiString ordtype,AnsiString price)
{
    double ret = StrToFloatDef(price,-1) ;

    if( ret == -1)
    {
        if( pool == NULL )
            pool = new TPool(NULL);

        int src = mkt[1];
        int index = pool->Find(WideString(code).c_bstr(),src);
        if( index>-1 )
        {
            IQuote2 *qt = pool->GetItem(index);
            if( qt!=NULL )
            {
                if( ordtype[1] == otBuy || ordtype[1] ==otOpenBuy ||
                    ordtype[1] == otCloseBuy ||ordtype[1] == otCloseTodayBuy)
                {
                    if( price.Pos("一档")==1 )
                    {
                        qt->get_AskPrice(TVariant((long)0),&ret);
                    }
                    else if( price.Pos("二档")==1 )
                    {
                        qt->get_AskPrice(TVariant((long)1),&ret);
                    }
                    else if( price.Pos("三档")==1 )
                    {
                        qt->get_AskPrice(TVariant((long)2),&ret);
                    }
                    else if( price.Pos("四档")==1 )
                    {
                        qt->get_AskPrice(TVariant((long)3),&ret);
                    }
                    else if( price.Pos("五档")==1 )
                    {
                        qt->get_AskPrice(TVariant((long)4),&ret);
                    }
                    else if( price.Pos("反向一档")==1 )
                    {
                        qt->get_BidPrice(TVariant((long)0),&ret);
                    }
                    else if( price.Pos("当前")==1 )
                    {
                        qt->get_LastPrice(&ret);
                    }
                }
                else if( ordtype[1] ==otSell || ordtype[1] ==otOpenSell||
                    ordtype[1] ==otCloseSell|| ordtype[1] == otCloseTodaySell)
                {
                    if( price.Pos("一档")==1 )
                    {
                        qt->get_BidPrice(TVariant((long)0),&ret);
                    }
                    else if( price.Pos("二档")==1 )
                    {
                        qt->get_BidPrice(TVariant((long)1),&ret);
                    }
                    else if( price.Pos("三档")==1 )
                    {
                        qt->get_BidPrice(TVariant((long)2),&ret);
                    }
                    else if( price.Pos("四档")==1 )
                    {
                        qt->get_BidPrice(TVariant((long)3),&ret);
                    }
                    else if( price.Pos("五档")==1 )
                    {
                        qt->get_BidPrice(TVariant((long)4),&ret);
                    }
                    else if( price.Pos("反向一档")==1 )
                    {
                        qt->get_AskPrice(TVariant((long)0),&ret);
                    }
					else if( price.Pos("当前")==1 )
                    {
                        qt->get_LastPrice(&ret);
                    }
                }
                qt->Release();
            }
        }

    }

    return ret;
}

void __fastcall TfrmMain::Button6Click(TObject *Sender)
{
//
	for(int i=0;i<Memo2->Lines->Count;i++)
	{
		AnsiString line = Memo2->Lines->Strings[i];
		if( line.Pos("-")==1 )
			continue;
		else
		{
			AnsiString acc,code,mkt,num,price,ordtype,rev;
			getOrder(AnsiString(line),acc,code,mkt,num,price,ordtype,rev);
			if( cbonlylist->Checked )
			{
                int c =  StrToInt(num)/1000000;
                for( int i=0;i<c ;i++)
                {
                    Memo1->Lines->Add(acc+","+code+","+mkt+",1000000,"+FloatToStr(get_price(code,mkt,ordtype,price))+","+ordtype);
                }
                int a = StrToInt(num)%1000000;
                if( a>0 )
                    Memo1->Lines->Add(acc+","+code+","+mkt+","+IntToStr(a)+","+FloatToStr(get_price(code,mkt,ordtype,price))+","+ordtype);
			}
			else
			{
				std::map<std::string,TItfTrd*>::iterator iter=_itfs.find(acc.c_str());
				if( iter!= _itfs.end() )
				{
                 	TItfTrd* ptrd  =  iter->second;
					if( ptrd != NULL )
					{
                        int c =  StrToInt(num)/1000000;
                        for( int i=0;i<c ;i++)
                        {
                            char ordid[255] = {'\0'};
                            if( ptrd->Order(code.c_str(),get_price(code,mkt,ordtype,price),1000000,
                                mkt[1],ordtype[1],ordid,255)==0)
                            {
                                if( strlen(ordid)>0 )
                                {
                                    TOrderInfo *ordinfo=NULL;
                                    int num = 1;
                                    if(ptrd->QryOrder(ordid,"",&ordinfo,num)==0)
                                    {
                                        //if( num == 1 )
                                        {
                                            TListItem *pItem = qcListview->Items->Add();
                                            pItem->Caption = ordinfo[0].ContractID;
                                            pItem->SubItems->Add(ordinfo[0].SecuID);
                                            pItem->SubItems->Add(ordinfo[0].Market);
                                            pItem->SubItems->Add(IntToStr((int)ordinfo[0].Time));
                                            pItem->SubItems->Add(IntToStr((int)ordinfo[0].Date));
                                            pItem->SubItems->Add((char)ordinfo[0].Type);
                                            pItem->SubItems->Add((char)ordinfo[0].State);
                                            pItem->SubItems->Add(IntToStr((int)ordinfo[0].CsnVol));
                                            pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].CsnPrice));
                                            pItem->SubItems->Add(IntToStr((int)ordinfo[0].TrdVol));
                                            pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].TrdPrice));
                                            pItem->SubItems->Add(IntToStr((int)ordinfo[0].CancelVol));
                                            pItem->SubItems->Add(ordinfo[0].Account);
                                            pItem->SubItems->Add(iter->first.c_str());
                                            pItem->ImageIndex = 4;
                                        }

                                        if(ordinfo!=NULL)
                                            ptrd->FreeAnswer(ordinfo);
                                    }
                                }
                            }
                            else
                            {
                                char text[256];
                                char sender[100];
                                long errcode = ptrd->GetLastError(text,255,sender,100) ;
                                if( errcode != 0 )
                                {
                                    Memo1->Lines->Add(String("Sender:") + sender + String(", Error:") + text +
                                    String(L",Code:")+IntToStr((int)errcode));
                                }
                            }
                        }
                        int a = StrToInt(num)%1000000;
                        if( a>0 )
                        {
                            char ordid[255] = {'\0'};
                            if( ptrd->Order(code.c_str(),get_price(code,mkt,ordtype,price),a,
                                mkt[1],ordtype[1],ordid,255)==0)
                            {
                                if( strlen(ordid)>0 )
                                {
                                    TOrderInfo *ordinfo=NULL;
                                    int num = 1;
                                    if(ptrd->QryOrder(ordid,"",&ordinfo,num)==0)
                                    {
                                        //if( num == 1 )
                                        {
                                            TListItem *pItem = qcListview->Items->Add();
                                            pItem->Caption = ordinfo[0].ContractID;
                                            pItem->SubItems->Add(ordinfo[0].SecuID);
                                            pItem->SubItems->Add(ordinfo[0].Market);
                                            pItem->SubItems->Add(IntToStr((int)ordinfo[0].Time));
                                            pItem->SubItems->Add(IntToStr((int)ordinfo[0].Date));
                                            pItem->SubItems->Add((char)ordinfo[0].Type);
                                            pItem->SubItems->Add((char)ordinfo[0].State);
                                            pItem->SubItems->Add(IntToStr((int)ordinfo[0].CsnVol));
                                            pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].CsnPrice));
                                            pItem->SubItems->Add(IntToStr((int)ordinfo[0].TrdVol));
                                            pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].TrdPrice));
                                            pItem->SubItems->Add(IntToStr((int)ordinfo[0].CancelVol));
                                            pItem->SubItems->Add(ordinfo[0].Account);
                                            pItem->SubItems->Add(iter->first.c_str());
                                            pItem->ImageIndex = 4;
                                        }

                                        if(ordinfo!=NULL)
                                            ptrd->FreeAnswer(ordinfo);
                                    }
                                }
                            }
                            else
                            {
                                char text[256];
                                char sender[100];
                                long errcode = ptrd->GetLastError(text,255,sender,100) ;
                                if( errcode != 0 )
                                {
                                    Memo1->Lines->Add(String("Sender:") + sender + String(", Error:") + text +
                                    String(L",Code:")+IntToStr((int)errcode));
                                }
                            }
                        }
					}
				}
            }
		}
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::Button7Click(TObject *Sender)
{
	std::map<std::string,TItfTrd*>::iterator itr1 ;;
    Memo1->Lines->Add("账户             币种   权益                  可用");
	for( itr1=_itfs.begin() ;  itr1  !=  _itfs.end();  itr1++ )
	{
		TItfTrd* ptrd  = itr1->second ;
		if( ptrd != NULL )
		{
            TMoneyInfo mi;
            int ret =ptrd->QryMoney(cbMoneyType->Text[1],mi) ;
            if(ret==0)
            {
                AnsiString txt;
                txt.sprintf("%10s%10s%15.2f%15.2f",itr1->first.c_str(),AnsiString(mi.MoneyType).c_str(),
                   mi.balance,mi.available );
                Memo1->Lines->Add(txt);
            }
            else
            {
                Memo1->Lines->Add("查询余额失败:"+IntToStr(ret));
            }
        }
	}
	Memo1->Perform(WM_VSCROLL,SB_BOTTOM,0);
	PageControl1->ActivePage = TabSheet1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Button8Click(TObject *Sender)
{
//加入委托池
    String txt;
    txt.sprintf(L"%s,%s,%c,%s,%s,%c",edAccount->Text.c_str(),edCode->Text.c_str(),
        cbMarket->Text[1],
        edOrdNum->Text.c_str(),
        edPrice->Text.c_str(),
        cbOrderType->Text[1]
        ) ;
    Memo2->Lines->Add(txt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Button9Click(TObject *Sender)
{
	Timer3->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Button10Click(TObject *Sender)
{
	Timer3->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Timer3Timer(TObject *Sender)
{
//
	static TDate dt = Date();
    static bool bFired = false;
	if( Date()>dt)
	{
		bFired = false;
		dt = Date();
	}
	unsigned short h,m,s,ms;
	DecodeTime(Now(),h,m,s,ms);
	int lnow = h*10000+m*100+s;

	if( lnow >= edExecTime->Text.ToIntDef(145500) && lnow<=150000 )
	{
		if(bFired==false)
		{
			btHuiGou->Click();
			bFired = true;
		}
	}
	else
	{
        btHuiGou->Caption = IntToStr(lnow);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btHuiGouClick(TObject *Sender)
{
	qcListview->Items->BeginUpdate();
	qcListview->Items->Clear();
	qcListview->Items->EndUpdate() ;

	for(int i=0;i<Memo2->Lines->Count;i++)
	{
		AnsiString line = Memo2->Lines->Strings[i];
		if( line.Pos("-")==1 )
			continue;
		else
		{
			AnsiString acc,code,mkt,num,price,ordtype,rev;
			getOrder(AnsiString(line),acc,code,mkt,num,price,ordtype,rev);
			if( cbonlylist->Checked )
			{
            	std::map<std::string,TItfTrd*>::iterator iter=_itfs.find(acc.c_str());
				if( iter!= _itfs.end() )
				{
					TItfTrd* ptrd  =  iter->second;
					if( ptrd != NULL )
					{
						TMoneyInfo mi;
						int ret = ptrd->QryMoney(motRMB,mi);
						if( ret == 0 )
						{
							double ava = mi.available - rev.ToIntDef(0);
							double prc = get_price(code,mkt,ordtype,price);
							int inum = ava/100;
							for(int  i =0 ;i<inum/100000; i++)
							{
								Memo1->Lines->Add(acc+","+code+","+mkt+",100000,"+FloatToStr(prc)+","+ordtype+ "," + FloatToStr(ava));
							}

							inum = inum % 100000;
							for(int  i =0 ;i<inum/10000; i++)
							{
								Memo1->Lines->Add(acc+","+code+","+mkt+",10000,"+FloatToStr(prc)+","+ordtype+ "," + FloatToStr(ava));
							}

							inum = inum % 10000;
							for(int  i =0 ;i<inum/1000; i++)
							{
								Memo1->Lines->Add(acc+","+code+","+mkt+",1000,"+FloatToStr(prc)+","+ordtype+ "," + FloatToStr(ava));
							}
						}
					}
				}
			}
			else
			{
				std::map<std::string,TItfTrd*>::iterator iter=_itfs.find(acc.c_str());
				if( iter!= _itfs.end() )
				{
                 	TItfTrd* ptrd  =  iter->second;
					if( ptrd != NULL )
					{
						TMoneyInfo mi;
						int ret = ptrd->QryMoney(motRMB,mi);
						if( ret == 0 )
						{
							double ava = mi.available - rev.ToIntDef(0);
							double prc = get_price(code,mkt,ordtype,price);
							int inum = ava/100;
							for(int  i =0 ;i<inum/100000; i++)
							{
								char ordid[255] = {'\0'};
								if( ptrd->Order(code.c_str(),prc,100000,
									mkt[1],ordtype[1],ordid,255)==0)
								{
									if( strlen(ordid)>0 )
									{
										TOrderInfo *ordinfo=NULL;
										int num = 1;
										if(ptrd->QryOrder(ordid,"",&ordinfo,num)==0)
										{
											//if( num == 1 )
											{
												TListItem *pItem = qcListview->Items->Add();
												pItem->Caption = ordinfo[0].ContractID;
												pItem->SubItems->Add(ordinfo[0].SecuID);
												pItem->SubItems->Add(ordinfo[0].Market);
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].Time));
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].Date));
												pItem->SubItems->Add((char)ordinfo[0].Type);
												pItem->SubItems->Add((char)ordinfo[0].State);
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].CsnVol));
												pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].CsnPrice));
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].TrdVol));
												pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].TrdPrice));
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].CancelVol));
												pItem->SubItems->Add(ordinfo[0].Account);
												pItem->SubItems->Add(iter->first.c_str());
												pItem->ImageIndex = 4;
											}

											if(ordinfo!=NULL)
												ptrd->FreeAnswer(ordinfo);
										}
									}
								}
								else
								{
									char text[256];
									char sender[100];
									long errcode = ptrd->GetLastError(text,255,sender,100) ;
									if( errcode != 0 )
									{
										Memo1->Lines->Add(String("Sender:") + sender + String(", Error:") + text +
										String(L",Code:")+IntToStr((int)errcode));
									}
								}
							}

							inum = inum % 100000;
							for(int  i =0 ;i<inum/10000; i++)
							{
								char ordid[255] = {'\0'};
								if( ptrd->Order(code.c_str(),prc,10000,
									mkt[1],ordtype[1],ordid,255)==0)
								{
									if( strlen(ordid)>0 )
									{
										TOrderInfo *ordinfo=NULL;
										int num = 1;
										if(ptrd->QryOrder(ordid,"",&ordinfo,num)==0)
										{
											//if( num == 1 )
											{
												TListItem *pItem = qcListview->Items->Add();
												pItem->Caption = ordinfo[0].ContractID;
												pItem->SubItems->Add(ordinfo[0].SecuID);
												pItem->SubItems->Add(ordinfo[0].Market);
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].Time));
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].Date));
												pItem->SubItems->Add((char)ordinfo[0].Type);
												pItem->SubItems->Add((char)ordinfo[0].State);
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].CsnVol));
												pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].CsnPrice));
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].TrdVol));
												pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].TrdPrice));
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].CancelVol));
												pItem->SubItems->Add(ordinfo[0].Account);
												pItem->SubItems->Add(iter->first.c_str());
												pItem->ImageIndex = 4;
											}

											if(ordinfo!=NULL)
												ptrd->FreeAnswer(ordinfo);
										}
									}
								}
								else
								{
									char text[256];
									char sender[100];
									long errcode = ptrd->GetLastError(text,255,sender,100) ;
									if( errcode != 0 )
									{
										Memo1->Lines->Add(String("Sender:") + sender + String(", Error:") + text +
										String(L",Code:")+IntToStr((int)errcode));
									}
								}
							}

							inum = inum % 10000;
							for(int  i =0 ;i<inum/1000; i++)
							{
								char ordid[255] = {'\0'};
								if( ptrd->Order(code.c_str(),prc,1000,
									mkt[1],ordtype[1],ordid,255)==0)
								{
									if( strlen(ordid)>0 )
									{
										TOrderInfo *ordinfo=NULL;
										int num = 1;
										if(ptrd->QryOrder(ordid,"",&ordinfo,num)==0)
										{
											//if( num == 1 )
											{
												TListItem *pItem = qcListview->Items->Add();
												pItem->Caption = ordinfo[0].ContractID;
												pItem->SubItems->Add(ordinfo[0].SecuID);
												pItem->SubItems->Add(ordinfo[0].Market);
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].Time));
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].Date));
												pItem->SubItems->Add((char)ordinfo[0].Type);
												pItem->SubItems->Add((char)ordinfo[0].State);
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].CsnVol));
												pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].CsnPrice));
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].TrdVol));
												pItem->SubItems->Add(FormatFloat("0.000",ordinfo[0].TrdPrice));
												pItem->SubItems->Add(IntToStr((int)ordinfo[0].CancelVol));
												pItem->SubItems->Add(ordinfo[0].Account);
												pItem->SubItems->Add(iter->first.c_str());
												pItem->ImageIndex = 4;
											}

											if(ordinfo!=NULL)
												ptrd->FreeAnswer(ordinfo);
										}
									}
								}
								else
								{
									char text[256];
									char sender[100];
									long errcode = ptrd->GetLastError(text,255,sender,100) ;
									if( errcode != 0 )
									{
										Memo1->Lines->Add(String("Sender:") + sender + String(", Error:") + text +
										String(L",Code:")+IntToStr((int)errcode));
									}
								}
							}
						}
					}
				}
            }
		}
	}
}
//---------------------------------------------------------------------------

