//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <SysUtils.hpp>
#pragma hdrstop

#include "UFrmMain.h"
#include "UnitAbout.h"
#include "xSystem.h"
#include "HsCommX_OCX.h"
#include "DebugStr.h"
#include "UPlugInWrapper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmMain *FrmMain;
TStp *g_stp;
//---------------------------------------------------------------------------
void addlog(char *log)
{
  FrmMain->LogIt(String(log),ltODS);
}

__fastcall TFrmMain::TFrmMain(TComponent* Owner)
  : TForm(Owner)
{
  FServer=NULL;
  FLog=NULL;
  FKeepAliveTh = NULL;
  
  CS=new TCriticalSection();
  this->Caption=Application->Title;
  g_stp=new TStp(ChangeFileExt(Application->ExeName,".ini"));
  FServer=new server_socket(g_stp->ServerIP.c_str(),g_stp->ServerPort,g_stp->WorkThread,
                g_stp->MaxClient);
  FLog=new TStringList();
  FLogCur=0;
  set_addlog_callback((ADDLOG)addlog);

  // ����DataĿ¼

  if( g_stp->SaveOrderFile )
  {
    try
    {
      if (g_stp->OrderFilePath.Length() == 0 )
      {
        g_stp->OrderFilePath = IncludeTrailingBackslash(
          ExtractFilePath(Application->ExeName)) + "Data\\";
        g_stp->SaveToFile();
      }

      ForceDirectories(g_stp->OrderFilePath);
      g_order_list = new TSafeStrings();

    }
    catch(...)
    {
      xErrBox("����Ŀ¼ʧ��:" + g_stp->OrderFilePath);
      g_order_list= NULL;
    }
  }
  else
  {
    g_order_list = NULL;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFrmMain::aboutExecute(TObject *Sender)
{
  AboutBox=new TAboutBox(this);
  AboutBox->ShowModal();
  delete AboutBox;
}
//---------------------------------------------------------------------------

void __fastcall TFrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  if(!start->Enabled)
  {
    if(MessageBox(Handle,"���������������Ƿ������Ҫ�رշ�������","ѯ��",
            MB_ICONQUESTION|MB_YESNO)== IDYES)
    {
      stopExecute(stop);
      CanClose=true;
    }
    else
      CanClose=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFrmMain::setupExecute(TObject *Sender)
{
  String aszPath=ChangeFileExt(Application->ExeName,".ini");
  if(FileExists(aszPath))
    xInvokeExe(aszPath);
  else
    xErrBox("\"" + aszPath + "\" �����ļ������ڣ�");
}
//---------------------------------------------------------------------------

void __fastcall TFrmMain::stopExecute(TObject *Sender)
{
  if( FKeepAliveTh != NULL )
  {
    FKeepAliveTh->Terminate();
    FKeepAliveTh->WaitFor();
    delete FKeepAliveTh;
    LogIt("���������߳�",ltMsg);
  }

  if(FServer->IsActive())
  {
    FServer->stop();
    if(!FServer->IsActive())
    {
      Caption=Application->Title+"-�ѹر�";
      LogIt("�������Ѿ��ر�",ltMsg);
      start->Enabled=true;
      stop->Enabled=!start->Enabled;
      setup->Enabled=start->Enabled;
      hsSetup->Enabled=start->Enabled;
      TrayIcon->Hint=Caption;
    }
    else
    {
      LogIt("�������ر�ʧ��",ltErr);
    }
  }

	sb->Panels->Items[2]->Text = "";
  //Timer1->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFrmMain::startExecute(TObject *Sender)
{
	g_req_num=0;
	g_stp->ReadFromFile();
	
	plugin_wrapper pw;
	if( pw.load_plugin(g_stp->PlugInName.c_str())== true )
	{
  if (false==FServer->IsActive())
  {
    FServer->SetSvrParam(g_stp->ServerIP.c_str(),g_stp->ServerPort,
      g_stp->WorkThread,g_stp->MaxClient);
    int err=FServer->start();
    if(FServer->IsActive())
    {
      Caption=Application->Title+"-������-" + IntToStr(g_stp->ServerPort);
      LogIt(String("�������Ѿ����� Listening at ") + FServer->get_local_ip() + ":" +
            IntToStr(g_stp->ServerPort) ,ltMsg);
      start->Enabled=false;
      stop->Enabled=!start->Enabled;
      setup->Enabled=start->Enabled;
      hsSetup->Enabled=start->Enabled;
      TrayIcon->Hint=Caption;

			char itfname[255],version[255];
			pw.get_version(itfname,254,version,254);
			String tmp;
			tmp.sprintf("%s(%s) Version:%s",itfname,g_stp->PlugInName.c_str(),version);
      sb->Panels->Items[2]->Text=tmp;
			if(g_stp->KeepAliveTime>0)
      {
        FKeepAliveTh =new keep_alive_th(false,FServer,g_stp->KeepAliveTime);
        LogIt("���������߳�,�������(����)"+IntToStr(g_stp->KeepAliveTime),ltMsg);
      }
    }
    else
    {
			LogIt("����������ʧ�� ErrCode=" + IntToStr(err),ltErr);
    }
  }
	//Timer1->Enabled=true;
	}
	else
	{
		LogIt("����������ʧ��,������'" + g_stp->PlugInName + "'����,���ǺϷ��Ĳ����",ltErr);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFrmMain::FormDestroy(TObject *Sender)
{
	Timer1->Enabled=false;

  if(!FileExists(g_stp->FileName))
    g_stp->SaveToFile();

  delete FServer;

  AddToLog();
  xSaveStringToFile(ChangeFileExt(Application->ExeName,".log"),
        log->Lines->Text);

  if( g_order_list )
  {
    AddOrder();
    delete g_order_list;
  }

  delete FLog;
  delete g_stp;
  delete CS;
}
//---------------------------------------------------------------------------

void TFrmMain::LogIt(String Text,TLogType lt)
{
  String str;
  
  switch(lt)
  {
    case ltMsg: str="M[��Ϣ "; break;
    case ltWarn:str="W[���� "; break;
    case ltErr: str="E[���� "; break;
    case ltODS: str="P[��� "; break;
    default:    str="O[���� ";
  }

  __try
  {
    CS->Enter();
    FLog->Add(str + DateTimeToStr(Now()) + "] " + Text);
  }
  __finally
  {
    CS->Leave();
  }
}

void __fastcall TFrmMain::FormActivate(TObject *Sender)
{
  startExecute(start);
}
//---------------------------------------------------------------------------

void __fastcall TFrmMain::UpdateStatus()
{
  sb->Panels->Items[0]->Text="�ͻ���: " + IntToStr(FServer->m_client_num);
  sb->Panels->Items[1]->Text="������: " + IntToStr(g_req_num);
}

void __fastcall TFrmMain::Timer1Timer(TObject *Sender)
{
  if(FServer) UpdateStatus();
  if(FLog) AddToLog();

  static DWORD oldcount = GetTickCount();
  if( GetTickCount() - oldcount >= 1000 )
  {
    AddOrder();
    oldcount = GetTickCount();
  }
}

//---------------------------------------------------------------------------
void __fastcall TFrmMain::ClientDisconnected(TMessage &Message)
{
  unsigned short errcode=WSAGETSELECTERROR(Message.LParam);
  if(errcode==WSAECONNRESET	|| errcode==WSAECONNABORTED || errcode==WSAENETDOWN)
  {
    completion_key *ck=FServer->get_key_by_sock(Message.WParam);
    if(ck)
    {
      ck->PostFree(IO_DISCONNECTED);
    }
  }
}

void __fastcall TFrmMain::AddToLog(void)
{
  int n=FLog->Count;
  if( FLogCur < n)
  {
    for(int i=FLogCur;i<n;i++)
      log->Lines->Add(FLog->Strings[i]);
    FLogCur=n;

    if(log->Lines->Count>1000)
    {
      xSaveStringToFile(ChangeFileExt(Application->ExeName,".log"),
        log->Lines->Text);
      log->Lines->Clear();
      for(int i=(FLogCur-1);i>=0;i--)
        FLog->Delete(i);
      FLogCur=0;
    }
  }
}

void __fastcall TFrmMain::E1Click(TObject *Sender)
{
  this->Close();
}
//---------------------------------------------------------------------------

void TFrmMain::AddOrder(void)
{
  // ��ί�������Ϣд���ļ�
  if( g_order_list!=NULL && g_order_list->Count > 0)
  {
    String filename = g_stp->OrderFilePath;
    int n =  filename.Length() ;
    if( n < 1) return;

    if( '\\' != filename[n] ) filename = filename + "\\" ;

    filename += (Date().FormatString("yyyymmdd")) + ".dat";

    FILE *out;
    if ((out = fopen(filename.c_str(), "a+")) != NULL)
    {
      g_order_list->Lock();
      fprintf(out,"%s",g_order_list->Text.c_str());
      g_order_list->Clear();
      g_order_list->Unlock();
      fclose( out );
    }
    else
    {
      LogIt("���ļ�����:" +  filename ,ltErr);
    }
  }
}

void __fastcall TFrmMain::TrayIconDblClick(TObject *Sender)
{
	Application->Restore();
	this->Show();

}
//---------------------------------------------------------------------------

void __fastcall TFrmMain::ApplicationEvents1Minimize(TObject *Sender)
{
	Application->ShowMainForm = false;
	this->Hide();
}
//---------------------------------------------------------------------------



