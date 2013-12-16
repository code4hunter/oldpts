//---------------------------------------------------------------------------
#pragma hdrstop

#include "UThdSuck.h"
#include "..\..\..\..\Common\CmnBase\URjlXML.h"
#include "..\URjlSysVar.h"
#include "..\URjlFuncX.h"
//---------------------------------------------------------------------------
__fastcall TThdSuck::TThdSuck(bool CreateSuspended) : TBasThdTrd(CreateSuspended)
{
  FQueSuck = new TQueSuck();
  FInSuck  = new TList();
  
  FInSuck->Clear();
}
//---------------------------------------------------------------------------
__fastcall TThdSuck::~TThdSuck()
{
  delete FInSuck;
  delete FQueSuck;
}
//---------------------------------------------------------------------------
void __fastcall TThdSuck::Execute()
{
  double  p=0;
  int     n=0,un=0;
  bool    undoall = false;
  TBourse bourse;
  HANDLE  hMutex=OpenSemaphore(SEMAPHORE_ALL_ACCESS	,true,TRjlFunc::ThrSuckMutex.c_str());
  TQueItf *q = NULL;

  while(true) {
    Sleep(500);
    WaitForSingleObject(hMutex,INFINITE);
    GetFromQue();                                           //读取队列

    for(int i=0;i<FLocalDtl->Count;i++){                    //扫描本地列表
      double   curp = 0;
      TLocalDtl *l  = ((TLocalDtl*)FLocalDtl->Items[i]);
      TItfTrd   *it = (TItfTrd *)(FItfTrdLst->Items[l->ItfTrdPos]);
      if(l->SecuID.SubString(1,1).UpperCase() == "S") bourse = bsSZ;
      else bourse = bsSH;

      //10秒查询一次成交情况
      //////////////////////
      undoall = false;
      if((time(NULL) - l->QryTime)>10 || Terminated){
        l->QryTime = time(NULL);

        for(int j=0;j<l->TrdInfo->Count;j++){
          TTrdInfo  *t          = (TTrdInfo *)(l->TrdInfo->Items[j]);
          String    ContractID  = t->ContractID;
          n = 0;

          if(it->QryDetail(ContractID,bourse,p,n,un)<=-1) {continue;}//成交查询 ,出错提示不需要,该单子未成交也会返回-1
          curp = n*p;
          if(t->HasUndo){                                  //如果是已经执行撤单的单子
            if(un!=0 || n>=t->Num){                        //如果撤单成功，或者单子已经全部成交
              l->LastPrc  = curp + l->LastPrc;
              l->LastVol += n;
              if(n - t->CurVol>0){
                FRepTime = Time();
                FRepBuy  = true;
                FRepSecuID = l->SecuID;
                FRepVol    = n - t->CurVol;
                FRepPrice  = p;
//                Synchronize(TrdRep);
              }
              l->CurVol  -= t->CurVol;
              delete t;
              l->TrdInfo->Delete(j);
              j--;
            }
            else{                                          //还未完成撤单
            }
          }
          else if(n - t->CurVol > 0){                                     //加到成交回报
            FRepTime = Time();
            FRepBuy  = true;
            FRepSecuID = l->SecuID;
            FRepVol    = n - t->CurVol;
            FRepPrice  = p;
//            Synchronize(TrdRep);
            l->CurVol += n - t->CurVol;                               //累计该股票所有单子的成交量
            t->CurVol  = n;                                           //保存一张单子的成交量
          }

          if(l->CurVol + l->LastVol>=l->TotalVol) undoall = true;                 //表示该股票可以全部撤单
        }

        q = ((TQueItf*)FInSuck->Items[l->Locate]);
        if(q != NULL){
          q->CurVol = l->CurVol + l->LastVol;   //向指针中置当前总成交量
          if(l->CurVol + l->LastVol>0)
            q->AvgPrice = (curp + l->LastPrc)/(l->CurVol + l->LastVol);//向指针中置当前总成交金额
        }
      }
      if(undoall){                                                     //对该股票执行全部撤单
        UndoAllTrd(l);
        if(q!=NULL) q->State = tsFinish;
        FErrMsg = l->SecuID+" 吸纳完成,吸纳总量为："+IntToStr(l->CurVol + l->LastVol);  //吸纳完成提示
        Synchronize(ShowErr);

        DeleteTrd(i);                                                  //从本地列表中删除
        i--;
        if(!Terminated) continue;
      }

      //撤单
      ////////////////////////
//      if((time(NULL) - l->UndoTime) > l->Scheme->TrdCancel*60){
//      l->UndoTime = time(NULL);
//      l->LastTime = time(NULL);

      for(int j=0;j<l->TrdInfo->Count;j++){
        TTrdInfo  *t         = (TTrdInfo *)(l->TrdInfo->Items[j]);
        String    ContractID = t->ContractID;
        bool       canCancel = false;
        if(l->Scheme->TrdCancelTime != 0){
          if((time(NULL) - t->DoTime) > l->Scheme->TrdCancelTime) canCancel=true;        //按时间撤单
        }
        if(l->Scheme->TrdCancelPrc != 0){
          double zxj = StrToFloat(TRjlSysVar()()->DatDyn->GetField(TRjlSysVar()()->DatDyn->GetLoc(l->SecuID),dtCp))/1000;
          if(t->Prc + t->Prc*l->Scheme->TrdCancelPrc/100<zxj) canCancel=true;           //价偏离撤单
        }
        if(!canCancel) continue;
        
        if(it->Undo(ContractID,bourse)<-1) {
          FErrMsg = "异常错误，按时撤单未成功,合同号：" + ContractID;        //撤单未成功
          Synchronize(ShowErr);
        }
        else{
          t->HasUndo = true;
        }
      }
//      l->CurVol  = 0;

//      if(!Terminated) continue;
//      }
      if(!Terminated){
        //按时下单
        //////////////////////
        if(l->Scheme->TrdSec<0){
          if(l->TrdX==TRjlFunc::StrToDouble(TRjlSysVar()()->DatDyn->GetField(TRjlSysVar()()->DatDyn->GetLoc(l->SecuID),dtCp)))  continue;
          l->TrdX=TRjlFunc::StrToDouble(TRjlSysVar()()->DatDyn->GetField(TRjlSysVar()()->DatDyn->GetLoc(l->SecuID),dtCp));
        }
        else if(l->Scheme->TrdSec>0){                //按指定时间下单
          if((time(NULL) - l->LastTime)<l->Scheme->TrdSec)  continue;
          l->LastTime = time(NULL);
        }
        else{
          if((time(NULL) - l->LastTime)<l->TrdX) continue; //取随机时间下单
          l->TrdX = random(l->Scheme->Sec2-l->Scheme->Sec1)+l->Scheme->Sec1;
        }
        
        double  prc=0;
        long    vol=0,dv=0;
        String  ContractID="";

        if(GetInfo(l->SecuID) <= -1){
          FErrMsg = "未获得"+ l->SecuID +"的盘口数据";
          Synchronize(ShowErr);
          continue;
        }

        if(l->Scheme->ConsignPrice==0)
          prc = FZXJ + l->Scheme->FloatMny;
        else{
          prc = FPrice[l->Scheme->ConsignPrice-1] + l->Scheme->FloatMny;
        }

        if(l->Scheme->VolPercent==0){
          vol = random(l->Scheme->Vol2 - l->Scheme->Vol1) + l->Scheme->Vol1;
        }
        else{
          for(int i=0;i<l->Scheme->VolScheme;i++) vol += FVolum[i];
          vol = vol*l->Scheme->VolPercent/100;
        }
        vol = vol/100<=0?100:vol/100*100;
        
        for(int j=0;j<l->TrdInfo->Count;j++) dv += ((TTrdInfo*)(l->TrdInfo->Items[j]))->Num;
        if(dv+l->LastVol>=l->TotalVol) continue;                 //如果下单的总量已经达到吸纳的总量，就不用再下单了
        if(vol+dv+l->LastVol>l->TotalVol) vol = l->TotalVol - dv - l->LastVol;

        int done = -1;
        int validnum;

        if(it->QryStock(l->SecuID,prc,validnum)<=-1){
          FErrMsg = " 资金查询失败，"+l->SecuID + "价格"+FloatToStr(prc) + " 吸纳下单未成功";
          Synchronize(ShowErr);
          continue;
        }
        else{
          if(vol>validnum){
            vol = validnum;
            FErrMsg = " 账户资金不足,吸纳停止";
            Synchronize(ShowErr);
            ((TQueItf*)FInSuck->Items[l->Locate])->State = tsFinish;
            DeleteTrd(i);                                                  //从本地列表中删除
            i--;
            continue;
          }
        }

        if((l->PriceLimit==0 && l->VolLimit == 0) || (prc<l->PriceLimit && vol<l->VolLimit))
          done = it->Buy(l->SecuID,prc,vol,ContractID);

        if(done <= -1) {
          FErrMsg = "股票"+l->SecuID + "价格"+FloatToStr(prc) + " 吸纳下单未成功";
          Synchronize(ShowErr);
          continue;
        }
        else AddTrd(l,ContractID,vol,prc);
      }

    } //end for FLocalTrd

    if(FLocalDtl->Count>0) ReleaseSemaphore(hMutex,1,NULL);
    
    if(Terminated){                                           //线程中断全撤单
      for(int i=0;i<FLocalDtl->Count;i++){
        TLocalDtl *l = ((TLocalDtl*)FLocalDtl->Items[i]);
        UndoAllTrd(l);
      }
      break;
    }
  }

  CloseHandle(hMutex);
}
//---------------------------------------------------------------------------
int __fastcall TThdSuck::GetScheme(TScheme *Scheme,String SchemeName)
{
  String      NodeName  = "自动吸纳";
  String      FileName  = String(TRjlSysVar()()->TradePath) + "\\TradeScheme.xml";
  TStringList *attr     = new TStringList();
  TStringList *cond     = new TStringList();

  if(SchemeName==""){
    TStrings *Header    = new TStringList();

    Header->Clear();
    TRjlXML::GetHead(FileName,Header);
    SchemeName = Header->Values["DftSuck"];  //方案名为空的话取默认方案

    delete Header;
  }

  cond->Add("Name="+SchemeName);
  if(TRjlXML::GetNode(FileName,NodeName,cond,attr)<=0) {delete cond;delete attr;return -1;}
  if(attr->Count>0){
    Scheme->Name          = SchemeName;
    Scheme->ConsignPrice  = StrToInt(attr->Values["ConsignPrice"]);
    Scheme->FloatMny      = TRjlFunc::StrToDouble(attr->Values["FloatMny"]);
    Scheme->VolPercent    = TRjlFunc::StrToDouble(attr->Values["VolPercent"]);
    Scheme->VolScheme     = StrToInt(attr->Values["VolScheme"]);
    Scheme->Vol1          = StrToInt(attr->Values["Vol1"]);
    Scheme->Vol2          = StrToInt(attr->Values["Vol2"]);
    Scheme->TrdSec        = StrToInt(attr->Values["TrdSec"]);
    Scheme->Sec1          = StrToInt(attr->Values["Sec1"]);
    Scheme->Sec2          = StrToInt(attr->Values["Sec2"]);
    Scheme->TrdCancelTime = StrToInt(attr->Values["TrdCancelTime"]);
    Scheme->TrdCancelPrc  = TRjlFunc::StrToDouble(attr->Values["TrdCancelPrc"]);
  }

  delete cond;
  delete attr;
  return 0;
}
//---------------------------------------------------------------------------
int __fastcall TThdSuck::GetInfo(String SecuID)
{
  int loc = TRjlSysVar()()->DatDyn->GetLoc(SecuID);

  FZXJ      = StrToFloat(TRjlSysVar()()->DatDyn->GetField(loc,dtCp))/1000;
  FPrice[0] = StrToFloat(TRjlSysVar()()->DatDyn->GetField(loc,dtCsp))/1000;//Info.Price1;
  FPrice[1] = StrToFloat(TRjlSysVar()()->DatDyn->GetField(loc,dtSp2))/1000;//Info.Price2;
  FPrice[2] = StrToFloat(TRjlSysVar()()->DatDyn->GetField(loc,dtSp3))/1000;//Info.Price3;
  FVolum[0] = StrToInt(TRjlSysVar()()->DatDyn->GetField(loc,dtSv1));//Info.Volum1;
  FVolum[1] = StrToInt(TRjlSysVar()()->DatDyn->GetField(loc,dtSv2));//Info.Volum2;
  FVolum[2] = StrToInt(TRjlSysVar()()->DatDyn->GetField(loc,dtSv3));//Info.Volum3;

  return 0;
}
//---------------------------------------------------------------------------
int __fastcall TThdSuck::GetFromQue()
{
  TBourse bourse;
  while(!FQueSuck->empty()){
    if(!FQueSuck->front()->StartTrd){                        //收到停止交易信号
//      int pos = FindInLocal(FQueSuck->front()->SecuID,FQueSuck->front()->PtfName,FQueSuck->front()->AccountInfo);
      int pos = FindInLocal(FInSuck,FQueSuck->front());
      if(pos>=0){
        TLocalDtl *l  = ((TLocalDtl*)FLocalDtl->Items[pos]);
        TItfTrd   *it = (TItfTrd *)(FItfTrdLst->Items[l->ItfTrdPos]);
        if(l->SecuID.SubString(1,1).UpperCase() == "S") bourse = bsSZ;
        else bourse = bsSH;

        for(int j=0;j<l->TrdInfo->Count;j++){                         //全部撤单
          TTrdInfo  *t         = (TTrdInfo *)(l->TrdInfo->Items[j]);
          String    ContractID = t->ContractID;

          if(it->Undo(ContractID,bourse)<-1) {
            FErrMsg = "成交完成后撤单未成功,合同号：" + ContractID;
            Synchronize(ShowErr);
          }
        }
        ((TQueItf*)FInSuck->Items[l->Locate])->State = tsStop;        //设置停止状态

        FErrMsg = "对股票" + l->SecuID + " 吸纳已经停止,成交量为" + IntToStr(l->CurVol+l->LastVol) + "股，剩余量为"+IntToStr(l->TotalVol-l->CurVol-l->LastVol)+ "股";
        Synchronize(ShowErr);
        DeleteTrd(pos);                                               //从本地列表中删除
      }

      FQueSuck->pop();
      continue;
    }

    TScheme *s = new TScheme();
    CoInitialize(NULL);
    if(GetScheme(s,FQueSuck->front()->Scheme)==-1) {
      FErrMsg = String(FQueSuck->front()->Scheme)+"方案信息读取错误";
      Synchronize(ShowErr);
      delete s;
      FQueSuck->front()->State = tsStop;
      FQueSuck->pop();  continue;
    }
    CoUninitialize();

    TLocalDtl *dtl  = new TLocalDtl();
    dtl->SecuID     = FQueSuck->front()->SecuID;
    dtl->PtfName    = FQueSuck->front()->PtfName;
    dtl->LastTime   = time(NULL);

    if(s->TrdSec < 0){                     //按行情刷新保存最新价
      dtl->TrdX = TRjlFunc::StrToDouble(TRjlSysVar()()->DatDyn->GetField(TRjlSysVar()()->DatDyn->GetLoc(dtl->SecuID),dtCp));
    }
    else if(s->TrdSec == 0) dtl->TrdX = random(s->Sec2-s->Sec1)+s->Sec1;     //随机时间下单保存随机时间

    dtl->QryTime    = time(NULL);
    dtl->LastVol    = FQueSuck->front()->CurVol;
    dtl->CurVol     = 0;
    dtl->LastPrc    = FQueSuck->front()->CurVol * FQueSuck->front()->AvgPrice;
    dtl->TotalVol   = FQueSuck->front()->Vol;
    dtl->Scheme     = s;
    dtl->PriceLimit = FQueSuck->front()->PriceLimit;
    dtl->VolLimit   = FQueSuck->front()->VolLimit;
    dtl->TrdInfo    = new TList();
    dtl->TrdInfo->Clear();

    FQueSuck->front()->State = tsRunning;                  //置状态
    FInSuck->Add(FQueSuck->front());                       //将队列中的结构指针转移到FInSuck中保存
    dtl->Locate = FInSuck->Count-1;                        //位置从0开始

    int ItfTrdPos = FindItfTrd(FQueSuck->front()->AccountInfo); //查找该账号的交易接口指针是否已经存在
    if(ItfTrdPos == -1){                                //若不存在，新增该交易接口指针，加到交易接口列表中
      CoInitialize(NULL);
      TItfTrd *it = new TItfTrd();
      it->Init("","");
      CoUninitialize();
      if(it->SetAccInfo(&(FQueSuck->front()->AccountInfo))<0){
        FQueSuck->pop() ;
        delete it; delete dtl->Scheme; delete dtl->TrdInfo;delete dtl;
        return 0;
      }
      ItfTrdPos   = FItfTrdLst->Add(it);
    }
    dtl->ItfTrdPos = ItfTrdPos;                            //在本地列表中记录该接口指针在接口列表中的位置，以便切换
    
    FLocalDtl->Add(dtl);                                   //加到本地列表中
    
    FQueSuck->pop() ;
  }
  
  return 0;
}
//---------------------------------------------------------------------------
void __fastcall TThdSuck::NewTask(TQueItf *QueItf)
{
  FQueSuck->push(QueItf);
  
  HANDLE  mx=OpenSemaphore(SEMAPHORE_ALL_ACCESS,true,TRjlFunc::ThrSuckMutex.c_str());
  ReleaseSemaphore(mx,1,NULL);
  CloseHandle(mx);  
}
//---------------------------------------------------------------------------

