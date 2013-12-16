//---------------------------------------------------------------------------
#include <vcl.h>
#include "UTrdCot_JZ.h"

//---------------------------------------------------------------------------
__fastcall TTrdCot_JZ::TTrdCot_JZ(TTrdItf_JZ::TJZSet * js) : TTrdCot()
{
/*
  FAppPath  = Application->ExeName;

  for(int i=FAppPath.Length();i>0;i--) {
    if(FAppPath[i]!='\\') { FAppPath.Delete(i,1); }
    else { break; }
  }

  //载入设置
  _di_IXMLDocument xmlDoc;

  if(TRjlXML::OpenFile(FAppPath+"\\SysCfg.xml",xmlDoc)==0) {
    TStringList *resLst = new TStringList();

    resLst->Clear();
    TRjlXML::GetNode(xmlDoc,"MiddNode",resLst);
    jzSet.MiddNode = resLst->Values["value"];

    resLst->Clear();
    TRjlXML::GetNode(xmlDoc,"MiddAddress",resLst);
    jzSet.MiddAddress = resLst->Values["value"];

    resLst->Clear();
    TRjlXML::GetNode(xmlDoc,"MiddSocket",resLst);
    jzSet.MiddSocket = StrToInt(resLst->Values["value"]);

    resLst->Clear();
    TRjlXML::GetNode(xmlDoc,"CounterID",resLst);
    jzSet.CounterID = resLst->Values["value"];

    resLst->Clear();
    TRjlXML::GetNode(xmlDoc,"CounterPW",resLst);
    jzSet.CounterPW = resLst->Values["value"];

    resLst->Clear();
    TRjlXML::GetNode(xmlDoc,"SHBourse",resLst);
    jzSet.SHBourse = resLst->Values["value"][1];

    resLst->Clear();
    TRjlXML::GetNode(xmlDoc,"SZBourse",resLst);
    jzSet.SZBourse = resLst->Values["value"][1];

    TRjlXML::CloseFile(FAppPath+"\\SysCfg.xml",xmlDoc);
    delete resLst;
  }
  else { ShowMessage("配置文件\"SysCfg.xml\"打开失败！"); }

  TStp stp(ChangeFileExt(Application->ExeName,".ini"));
  jzSet.MiddNode=stp.MiddNode;
  jzSet.MiddAddress=stp.MiddAddress;
  jzSet.MiddSocket=stp.MiddSocket;
  jzSet.CounterID=stp.CounterID;
  jzSet.CounterPW=stp.CounterPW;
  jzSet.SHBourse=stp.SHBourse;
  jzSet.SZBourse=stp.SZBourse;
*/
  FTrdItf = new TTrdItf_JZ(js);
}
//---------------------------------------------------------------------------
__fastcall TTrdCot_JZ::~TTrdCot_JZ()
{
  delete FTrdItf;
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot_JZ::Request(TRequest Request,TAnswer **Answer,int &AnsCount)
{
  return FTrdItf->Request(Request,Answer,AnsCount);
}
//---------------------------------------------------------------------------

