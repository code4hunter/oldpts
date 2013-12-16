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
    GetFromQue();                                           //��ȡ����

    for(int i=0;i<FLocalDtl->Count;i++){                    //ɨ�豾���б�
      double   curp = 0;
      TLocalDtl *l  = ((TLocalDtl*)FLocalDtl->Items[i]);
      TItfTrd   *it = (TItfTrd *)(FItfTrdLst->Items[l->ItfTrdPos]);
      if(l->SecuID.SubString(1,1).UpperCase() == "S") bourse = bsSZ;
      else bourse = bsSH;

      //10���ѯһ�γɽ����
      //////////////////////
      undoall = false;
      if((time(NULL) - l->QryTime)>10 || Terminated){
        l->QryTime = time(NULL);

        for(int j=0;j<l->TrdInfo->Count;j++){
          TTrdInfo  *t          = (TTrdInfo *)(l->TrdInfo->Items[j]);
          String    ContractID  = t->ContractID;
          n = 0;

          if(it->QryDetail(ContractID,bourse,p,n,un)<=-1) {continue;}//�ɽ���ѯ ,������ʾ����Ҫ,�õ���δ�ɽ�Ҳ�᷵��-1
          curp = n*p;
          if(t->HasUndo){                                  //������Ѿ�ִ�г����ĵ���
            if(un!=0 || n>=t->Num){                        //��������ɹ������ߵ����Ѿ�ȫ���ɽ�
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
            else{                                          //��δ��ɳ���
            }
          }
          else if(n - t->CurVol > 0){                                     //�ӵ��ɽ��ر�
            FRepTime = Time();
            FRepBuy  = true;
            FRepSecuID = l->SecuID;
            FRepVol    = n - t->CurVol;
            FRepPrice  = p;
//            Synchronize(TrdRep);
            l->CurVol += n - t->CurVol;                               //�ۼƸù�Ʊ���е��ӵĳɽ���
            t->CurVol  = n;                                           //����һ�ŵ��ӵĳɽ���
          }

          if(l->CurVol + l->LastVol>=l->TotalVol) undoall = true;                 //��ʾ�ù�Ʊ����ȫ������
        }

        q = ((TQueItf*)FInSuck->Items[l->Locate]);
        if(q != NULL){
          q->CurVol = l->CurVol + l->LastVol;   //��ָ�����õ�ǰ�ܳɽ���
          if(l->CurVol + l->LastVol>0)
            q->AvgPrice = (curp + l->LastPrc)/(l->CurVol + l->LastVol);//��ָ�����õ�ǰ�ܳɽ����
        }
      }
      if(undoall){                                                     //�Ըù�Ʊִ��ȫ������
        UndoAllTrd(l);
        if(q!=NULL) q->State = tsFinish;
        FErrMsg = l->SecuID+" �������,��������Ϊ��"+IntToStr(l->CurVol + l->LastVol);  //���������ʾ
        Synchronize(ShowErr);

        DeleteTrd(i);                                                  //�ӱ����б���ɾ��
        i--;
        if(!Terminated) continue;
      }

      //����
      ////////////////////////
//      if((time(NULL) - l->UndoTime) > l->Scheme->TrdCancel*60){
//      l->UndoTime = time(NULL);
//      l->LastTime = time(NULL);

      for(int j=0;j<l->TrdInfo->Count;j++){
        TTrdInfo  *t         = (TTrdInfo *)(l->TrdInfo->Items[j]);
        String    ContractID = t->ContractID;
        bool       canCancel = false;
        if(l->Scheme->TrdCancelTime != 0){
          if((time(NULL) - t->DoTime) > l->Scheme->TrdCancelTime) canCancel=true;        //��ʱ�䳷��
        }
        if(l->Scheme->TrdCancelPrc != 0){
          double zxj = StrToFloat(TRjlSysVar()()->DatDyn->GetField(TRjlSysVar()()->DatDyn->GetLoc(l->SecuID),dtCp))/1000;
          if(t->Prc + t->Prc*l->Scheme->TrdCancelPrc/100<zxj) canCancel=true;           //��ƫ�볷��
        }
        if(!canCancel) continue;
        
        if(it->Undo(ContractID,bourse)<-1) {
          FErrMsg = "�쳣���󣬰�ʱ����δ�ɹ�,��ͬ�ţ�" + ContractID;        //����δ�ɹ�
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
        //��ʱ�µ�
        //////////////////////
        if(l->Scheme->TrdSec<0){
          if(l->TrdX==TRjlFunc::StrToDouble(TRjlSysVar()()->DatDyn->GetField(TRjlSysVar()()->DatDyn->GetLoc(l->SecuID),dtCp)))  continue;
          l->TrdX=TRjlFunc::StrToDouble(TRjlSysVar()()->DatDyn->GetField(TRjlSysVar()()->DatDyn->GetLoc(l->SecuID),dtCp));
        }
        else if(l->Scheme->TrdSec>0){                //��ָ��ʱ���µ�
          if((time(NULL) - l->LastTime)<l->Scheme->TrdSec)  continue;
          l->LastTime = time(NULL);
        }
        else{
          if((time(NULL) - l->LastTime)<l->TrdX) continue; //ȡ���ʱ���µ�
          l->TrdX = random(l->Scheme->Sec2-l->Scheme->Sec1)+l->Scheme->Sec1;
        }
        
        double  prc=0;
        long    vol=0,dv=0;
        String  ContractID="";

        if(GetInfo(l->SecuID) <= -1){
          FErrMsg = "δ���"+ l->SecuID +"���̿�����";
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
        if(dv+l->LastVol>=l->TotalVol) continue;                 //����µ��������Ѿ��ﵽ���ɵ��������Ͳ������µ���
        if(vol+dv+l->LastVol>l->TotalVol) vol = l->TotalVol - dv - l->LastVol;

        int done = -1;
        int validnum;

        if(it->QryStock(l->SecuID,prc,validnum)<=-1){
          FErrMsg = " �ʽ��ѯʧ�ܣ�"+l->SecuID + "�۸�"+FloatToStr(prc) + " �����µ�δ�ɹ�";
          Synchronize(ShowErr);
          continue;
        }
        else{
          if(vol>validnum){
            vol = validnum;
            FErrMsg = " �˻��ʽ���,����ֹͣ";
            Synchronize(ShowErr);
            ((TQueItf*)FInSuck->Items[l->Locate])->State = tsFinish;
            DeleteTrd(i);                                                  //�ӱ����б���ɾ��
            i--;
            continue;
          }
        }

        if((l->PriceLimit==0 && l->VolLimit == 0) || (prc<l->PriceLimit && vol<l->VolLimit))
          done = it->Buy(l->SecuID,prc,vol,ContractID);

        if(done <= -1) {
          FErrMsg = "��Ʊ"+l->SecuID + "�۸�"+FloatToStr(prc) + " �����µ�δ�ɹ�";
          Synchronize(ShowErr);
          continue;
        }
        else AddTrd(l,ContractID,vol,prc);
      }

    } //end for FLocalTrd

    if(FLocalDtl->Count>0) ReleaseSemaphore(hMutex,1,NULL);
    
    if(Terminated){                                           //�߳��ж�ȫ����
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
  String      NodeName  = "�Զ�����";
  String      FileName  = String(TRjlSysVar()()->TradePath) + "\\TradeScheme.xml";
  TStringList *attr     = new TStringList();
  TStringList *cond     = new TStringList();

  if(SchemeName==""){
    TStrings *Header    = new TStringList();

    Header->Clear();
    TRjlXML::GetHead(FileName,Header);
    SchemeName = Header->Values["DftSuck"];  //������Ϊ�յĻ�ȡĬ�Ϸ���

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
    if(!FQueSuck->front()->StartTrd){                        //�յ�ֹͣ�����ź�
//      int pos = FindInLocal(FQueSuck->front()->SecuID,FQueSuck->front()->PtfName,FQueSuck->front()->AccountInfo);
      int pos = FindInLocal(FInSuck,FQueSuck->front());
      if(pos>=0){
        TLocalDtl *l  = ((TLocalDtl*)FLocalDtl->Items[pos]);
        TItfTrd   *it = (TItfTrd *)(FItfTrdLst->Items[l->ItfTrdPos]);
        if(l->SecuID.SubString(1,1).UpperCase() == "S") bourse = bsSZ;
        else bourse = bsSH;

        for(int j=0;j<l->TrdInfo->Count;j++){                         //ȫ������
          TTrdInfo  *t         = (TTrdInfo *)(l->TrdInfo->Items[j]);
          String    ContractID = t->ContractID;

          if(it->Undo(ContractID,bourse)<-1) {
            FErrMsg = "�ɽ���ɺ󳷵�δ�ɹ�,��ͬ�ţ�" + ContractID;
            Synchronize(ShowErr);
          }
        }
        ((TQueItf*)FInSuck->Items[l->Locate])->State = tsStop;        //����ֹͣ״̬

        FErrMsg = "�Թ�Ʊ" + l->SecuID + " �����Ѿ�ֹͣ,�ɽ���Ϊ" + IntToStr(l->CurVol+l->LastVol) + "�ɣ�ʣ����Ϊ"+IntToStr(l->TotalVol-l->CurVol-l->LastVol)+ "��";
        Synchronize(ShowErr);
        DeleteTrd(pos);                                               //�ӱ����б���ɾ��
      }

      FQueSuck->pop();
      continue;
    }

    TScheme *s = new TScheme();
    CoInitialize(NULL);
    if(GetScheme(s,FQueSuck->front()->Scheme)==-1) {
      FErrMsg = String(FQueSuck->front()->Scheme)+"������Ϣ��ȡ����";
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

    if(s->TrdSec < 0){                     //������ˢ�±������¼�
      dtl->TrdX = TRjlFunc::StrToDouble(TRjlSysVar()()->DatDyn->GetField(TRjlSysVar()()->DatDyn->GetLoc(dtl->SecuID),dtCp));
    }
    else if(s->TrdSec == 0) dtl->TrdX = random(s->Sec2-s->Sec1)+s->Sec1;     //���ʱ���µ��������ʱ��

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

    FQueSuck->front()->State = tsRunning;                  //��״̬
    FInSuck->Add(FQueSuck->front());                       //�������еĽṹָ��ת�Ƶ�FInSuck�б���
    dtl->Locate = FInSuck->Count-1;                        //λ�ô�0��ʼ

    int ItfTrdPos = FindItfTrd(FQueSuck->front()->AccountInfo); //���Ҹ��˺ŵĽ��׽ӿ�ָ���Ƿ��Ѿ�����
    if(ItfTrdPos == -1){                                //�������ڣ������ý��׽ӿ�ָ�룬�ӵ����׽ӿ��б���
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
    dtl->ItfTrdPos = ItfTrdPos;                            //�ڱ����б��м�¼�ýӿ�ָ���ڽӿ��б��е�λ�ã��Ա��л�
    
    FLocalDtl->Add(dtl);                                   //�ӵ������б���
    
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

