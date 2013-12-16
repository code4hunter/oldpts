//---------------------------------------------------------------------------
#include "UTrdItf_JZ.h"

/*
typedef bool  _stdcall(*KDAPI_IS)(long _TimeOut) ;
typedef int   _stdcall(*KDAPI_C)(tagNETWORKADD serverAddress[3],char *GYDM,char *GYMM);
typedef int   _stdcall(*KDAPI_R)(tagREQUEST &request);
typedef int   _stdcall(*KDAPI_RF)(tagREQUEST &request,char *yfzdm,char *mdfzdm);
typedef int   _stdcall(*KDAPI_A)(tagRESULT &result);
typedef void  _stdcall(*KDAPI_STM)(char *s,Money *x1);
typedef void  _stdcall(*KDAPI_STSM)(char *s,SmallMoney *x1);
typedef char* _stdcall(*KDAPI_MTS)( Money m);
typedef char* _stdcall(*KDAPI_SMTS)( SmallMoney m);
typedef int   _stdcall(*KDAPI_DISC)(void);
*/

typedef bool  _stdcall(*KDAPI_IS)(long _TimeOut, int nConnections) ;
typedef int   _stdcall(*KDAPI_C)(tagNETWORKADD serverAddress[3],char *GYDM,char *GYMM, int nConnectionNo);
typedef int   _stdcall(*KDAPI_R)(tagREQUEST &request, int nConnectionNo, unsigned int *sClientSocket=NULL);
typedef int   _stdcall(*KDAPI_RF)(tagREQUEST &request,char *yfzdm,char *mdfzdm, int nConnectionNo, unsigned int *sClientSocket=NULL);
typedef int   _stdcall(*KDAPI_A)(tagRESULT &result, int nConnectionNo);
typedef void  _stdcall(*KDAPI_STM)(char *s,Money *x1);
typedef void  _stdcall(*KDAPI_STSM)(char *s,SmallMoney *x1);
typedef char* _stdcall(*KDAPI_MTS)( Money m);
typedef char* _stdcall(*KDAPI_SMTS)( SmallMoney m);
typedef int   _stdcall(*KDAPI_DISC)(int nConnectionNo);

static LONG link_count_jz=0;
static HINSTANCE  hinstlib=NULL ;  //动态链接库句柄
static KDAPI_IS   KDAPI_is=NULL ;
static KDAPI_C    KDAPI_c=NULL ;
static KDAPI_R    KDAPI_r=NULL ;
static KDAPI_RF   KDAPI_rf=NULL ;
static KDAPI_A    KDAPI_a=NULL ;
static KDAPI_STM  KDAPI_stm=NULL;
static KDAPI_MTS  KDAPI_mts=NULL;
static KDAPI_STSM KDAPI_stsm=NULL;
static KDAPI_SMTS KDAPI_smts=NULL;
static KDAPI_DISC KDAPI_d=NULL;

static const int MAX_CONNECTIONS=150;              //最大连接数

//---------------------------------------------------------------------------
TTrdItf_JZ::TTrdItf_JZ(TJZSet *JZSet) : TTrdItfBase()
{
  memcpy(&FJZSet ,JZSet,sizeof(TJZSet));
  FCurConnectNO=-1;
}
//---------------------------------------------------------------------------
TTrdItf_JZ::~TTrdItf_JZ()
{
  CloseLink();
  if(link_count_jz<=0)
  {
    if(hinstlib)
    {
      FreeLibrary(hinstlib);
      hinstlib=NULL;
    }
  }
}
//---------------------------------------------------------------------------

int  TTrdItf_JZ::Connect(void)
{
  tagNETWORKADD sa[3];

  memset(sa,0,3*sizeof(tagNETWORKADD));

  lstrcpyn( sa[1].Address ,FJZSet.MiddAddress,13) ;//网卡号
  lstrcpyn( sa[1].Node,FJZSet.MiddNode,9) ;       //网段号
  sa[1].Socket = FJZSet.MiddSocket;                   //Socket

  lstrcpyn( sa[2].Address ,FJZSet.MiddAddress,13) ;//网卡号
  lstrcpyn( sa[2].Node,FJZSet.MiddNode,9) ;       //网段号
  sa[2].Socket = FJZSet.MiddSocket;                   //Socket

  lstrcpyn( sa[0].Address ,FJZSet.MiddAddress,13) ;//网卡号
  lstrcpyn( sa[0].Node,FJZSet.MiddNode,9) ;       //网段号
  sa[0].Socket = FJZSet.MiddSocket;                   //Socket

  int i =( (KDAPI_c)(sa,FJZSet.CounterID,FJZSet.CounterPW,FCurConnectNO));

  if (i != 0) { return -1 ; }
  else return 0;
}


int  TTrdItf_JZ::Init()
{
  FCurConnectNO=-1;

  if(link_count_jz==0)
  {
    hinstlib = LoadLibrary("API_BH"); //"API_BH");

    if(hinstlib==NULL) return -1;

    KDAPI_is = (KDAPI_IS)GetProcAddress(hinstlib,"KDAPI_InitSystem_MT") ;
    KDAPI_c  = (KDAPI_C)GetProcAddress(hinstlib,"KDAPI_Connect_MT") ;
    KDAPI_r  = (KDAPI_R)GetProcAddress(hinstlib,"KDAPI_Request_MT") ;
    KDAPI_rf = (KDAPI_RF)GetProcAddress(hinstlib,"KDAPI_Request_fzdm_MT") ;
    KDAPI_a  = (KDAPI_A)GetProcAddress(hinstlib,"KDAPI_Answer_MT") ;

    KDAPI_stm  = (KDAPI_STM)GetProcAddress(hinstlib,"KDAPI_StrToMoney") ;
    KDAPI_stsm = (KDAPI_STSM)GetProcAddress(hinstlib,"KDAPI_StrToSmallMoney") ;
    KDAPI_mts  = (KDAPI_MTS)GetProcAddress(hinstlib,"KDAPI_MoneyToStr") ;
    KDAPI_smts = (KDAPI_SMTS)GetProcAddress(hinstlib,"KDAPI_SmallMoneyToStr") ;
    KDAPI_d    = (KDAPI_DISC)GetProcAddress(hinstlib,"KDAPI_Disconnect_MT") ;

    if(!( KDAPI_is && KDAPI_c && KDAPI_r && KDAPI_rf  && KDAPI_a  && KDAPI_stm  &&
        KDAPI_stsm &&  KDAPI_mts &&  KDAPI_smts && KDAPI_d) )
    {
        return -1;
    }

    if (! (KDAPI_is)(10,MAX_CONNECTIONS) )  { return -1 ; } /*本来为1000*/
  }

  if(link_count_jz>=MAX_CONNECTIONS) return -2; //超出最大连接数

  FCurConnectNO = link_count_jz;
  InterlockedIncrement(&link_count_jz);

  return Connect();
}
//---------------------------------------------------------------------------
double  TTrdItf_JZ::SMToD(SmallMoney m)
{
  return double(m)/1000;
}
//---------------------------------------------------------------------------
double  TTrdItf_JZ::MToD(Money m)
{
  return double(m.lo_value+m.hi_value*4294967296)/10000;
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::Request(tagREQUEST &request,tagRESULT **Results,int &ResNum)
{
  int  retVal = 0;
  char jzbuffer[10*sizeof(tagRESULT)];  //防止内存溢出

RESEND:

  *Results=NULL;
  if((ResNum = (KDAPI_r)(request,FCurConnectNO))>0 )
  {
    *Results = new tagRESULT[ResNum];
    memset(*Results,0,(ResNum)*sizeof(tagRESULT));

    for(int i=0;i<ResNum;i++)
    {
      retVal = (KDAPI_a)(((*Results)[i]),FCurConnectNO);

      if(retVal<=0)
      {
        //delete [](*Results); *Results = NULL;
        //retVal = -2;
        break;
      }
    }
  }
  else if(ResNum==-4)
  { //请求失败
    tagRESULT result[1];
    (KDAPI_a)(result[0],FCurConnectNO);
    ODS("柜台请求失败： %s" ,result[0].ErrMsg.ErrMsg);
    return 0;
  }
  else
  { //其它异常
    switch(ResNum)
    {
      case -1: { ODS("柜台错误：没有调用InitSystem");  break; }

      case -2: {
        ODS("柜台错误：中间件连接错误 (未调用Connect) ,自动重连...");
        if(Connect()==0)
        {
          goto RESEND;
        }
        else ODS("重连中间件失败！");

        break;
      }

      case -3: { ODS("柜台错误：OEM未授权");  break; }
      case -5: { ODS("柜台错误：中间件连接错误(所有连接已断)");  break; }
      case -6: { ODS("柜台错误：发送数据错误");  break; }
    };
  }

  return ResNum;
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::SetAccount()
{
  tagREQUEST r;      //请求
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  r.head.length   = sizeof(tagKHJY_Request); //长度  (整个数据包长度)
  r.head.crc      = 0;                       //CRC校验码 //从serio 开始计算 保留
  r.head.serio    = 501;                     //序列号(按请求划分,1开始)
  r.head.function = 5;                       //功能号
  r.head.czfs     = FJZSet.EntrustWay;       //操作方式
  r.head.status   = 0;                       //状态 0正确 其他错误(应答有效)

  r.khjy.GDMS   = 2;                         //'2'同资金帐号关联

  switch(FRequest.SetAccount.Sort) {
    case asSH: { r.khjy.KHBSLX = FJZSet.SHBourse;  break; }
    case asSZ: { r.khjy.KHBSLX = FJZSet.SZBourse;  break; }
    default: r.khjy.KHBSLX = FRequest.SetAccount.Sort;  break;
  };

  strcpy(r.khjy.KHBS,FRequest.SetAccount.Account); //KHBS  股东代码或资金帐号或磁卡号
  strcpy(r.khjy.JYMM,FRequest.SetAccount.PW);

  if((retVal=Request(r,&a,num))>0) {
    memset(&FAccInfo,0,sizeof(TAccountInfo));
    strcpy(FAccInfo.PW,FRequest.SetAccount.PW);

    for(int i=0;i<num;i++)
    {
      memcpy(FAccInfo.Capital,a[i].khjy.ZJZH,ZJZH_WIDTH);

      if(a[i].khjy.JYSDM==FJZSet.SZBourse) { memcpy(FAccInfo.SZ,a[i].khjy.GDDM,GDXM_WIDTH); }
      else if(a[i].khjy.JYSDM==FJZSet.SHBourse) { memcpy(FAccInfo.SH,a[i].khjy.GDDM,GDXM_WIDTH); }
    }

    if(FRequest.SetAccount.Sort==asSH)
    {
      lstrcpyn(FAccInfo.SH,FRequest.SetAccount.Account,13);
    }
    else if(FRequest.SetAccount.Sort==asSZ)
    {
      lstrcpyn(FAccInfo.SZ,FRequest.SetAccount.Account,13);
    }

    if(FAccInfo.SH[0]==0 && FAccInfo.SZ[0]==0) { retVal = -1; }
  }

  if(a) { delete []a; }
  if(retVal>0){
    NewAns(1);
    memcpy(&((*FAnswer)[0].SetAccount.AccountInfo),&FAccInfo,sizeof(TAccountInfo));
    return 0;
  }
  else if(retVal==0) { return -1; }
  else { return retVal; }
}

//---------------------------------------------------------------------------
int  TTrdItf_JZ::GetTrdInfo()
{
  tagREQUEST r;      //请求
  tagRESULT  *a = NULL;
  int        num,retVal = 0;
  String     secuID = FRequest.GetTrdInfo.SecuID;

  r.dmjy.HEAD.length   = sizeof(tagDMJY_Request); //长度  (整个数据包长度)
  r.dmjy.HEAD.crc      = 0;                       //CRC校验码 //从serio 开始计算 保留
  r.dmjy.HEAD.serio    = 1;                       //序列号(按请求划分,1开始)
  r.dmjy.HEAD.function = 7;                       //功能号
  r.dmjy.HEAD.czfs     = FJZSet.EntrustWay;                       //操作方式
  r.dmjy.HEAD.status   = 0;                       //状态 0正确 其他错误(应答有效)

  if (secuID[1]=='S') {  // '0'-'9'交易所代码(参看柜台设置)
    r.dmjy.JYSDM = FJZSet.SZBourse;
    memcpy(r.dmjy.GDDM,FAccInfo.SZ,GDDM_WIDTH);   // 股东代码或资金帐号
  }
  else {
    r.dmjy.JYSDM = FJZSet.SHBourse;
    memcpy(r.dmjy.GDDM,FAccInfo.SH,GDDM_WIDTH);   // 股东代码或资金帐号
  }

  secuID = secuID.SubString(2,secuID.Length());
  strcpy(r.dmjy.ZQDM,secuID.c_str());       

  if((retVal=Request(r,&a,num))>0) {
    NewAns(1);

    (*FAnswer)[0].GetTrdInfo.BuyInfo.ZXJ    = SMToD(a[0].dmjy.ZJCJ);
    (*FAnswer)[0].GetTrdInfo.BuyInfo.CJSL   = a[0].dmjy.CJSL ;

    (*FAnswer)[0].GetTrdInfo.BuyInfo.Price1 = SMToD(a[0].dmjy.MRJG1);
    (*FAnswer)[0].GetTrdInfo.BuyInfo.Volum1 = a[0].dmjy.MCSL1 ;

    (*FAnswer)[0].GetTrdInfo.BuyInfo.Price2 = SMToD(a[0].dmjy.MRJG2);
    (*FAnswer)[0].GetTrdInfo.BuyInfo.Volum2 = a[0].dmjy.MCSL2 ;

    (*FAnswer)[0].GetTrdInfo.BuyInfo.Price3 = SMToD(a[0].dmjy.MRJG3);
    (*FAnswer)[0].GetTrdInfo.BuyInfo.Volum3 = a[0].dmjy.MCSL3 ;

    (*FAnswer)[0].GetTrdInfo.SellInfo.ZXJ  = SMToD(a[0].dmjy.ZJCJ);
    (*FAnswer)[0].GetTrdInfo.SellInfo.CJSL = a[0].dmjy.CJSL ;

    (*FAnswer)[0].GetTrdInfo.SellInfo.Price1 = SMToD(a[0].dmjy.MCJG1);
    (*FAnswer)[0].GetTrdInfo.SellInfo.Volum1 = a[0].dmjy.MRSL1 ;

    (*FAnswer)[0].GetTrdInfo.SellInfo.Price2 = SMToD(a[0].dmjy.MCJG2);
    (*FAnswer)[0].GetTrdInfo.SellInfo.Volum2 = a[0].dmjy.MRSL2 ;

    (*FAnswer)[0].GetTrdInfo.SellInfo.Price3 = SMToD(a[0].dmjy.MCJG3);
    (*FAnswer)[0].GetTrdInfo.SellInfo.Volum3 = a[0].dmjy.MRSL3 ;
  }

  if(a) { delete []a; }
  if(retVal>0) { return 0; }
  else if(retVal==0) { return -1; }
  else { return retVal; }
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::QryMoney()
{
  tagREQUEST r;      //请求
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  r.zjcx.HEAD.length   = sizeof(tagZJCX_Request); //长度  (整个数据包长度)
  r.zjcx.HEAD.crc      = 0;                       //CRC校验码 //从serio 开始计算 保留
  r.zjcx.HEAD.serio    = 1201;                    //序列号(按请求划分,1开始)
  r.zjcx.HEAD.function = 12;                      //功能号
  r.zjcx.HEAD.czfs     = FJZSet.EntrustWay;                       //操作方式
  r.zjcx.HEAD.status   = 0;                       //状态 0正确 其他错误(应答有效)


  memcpy(r.zjcx.KHBS,FAccInfo.Capital,KHBS_WIDTH); //KHBS  股东代码或资金帐号
  r.zjcx.KHBSLX = 'Z';                            // '0'-'9'交易所代码(参看柜台设置)

  if((retVal=Request(r,&a,num))>0) {
    NewAns(1);

    (*FAnswer)[0].QryMoney.Balance   = MToD(a[0].zjcx.YE);  //余额
    (*FAnswer)[0].QryMoney.Available = MToD(a[0].zjcx.KYS); //可用额
  }

  if(a) { delete []a; }
  if(retVal>0) { return 0; }
  else if(retVal==0) { return -1; }
  else { return retVal; }
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::QryStock()
{
  tagREQUEST r;      //请求
  tagRESULT  *a         = NULL;
  int        num,retVal = 0;
  String     secuID     = FRequest.QryStock.SecuID;

  r.gfcx.HEAD.length   = sizeof(tagGFCX_Request); //长度  (整个数据包长度)
  r.gfcx.HEAD.crc      = 0;                       //CRC校验码 //从serio 开始计算 保留
  r.gfcx.HEAD.serio    = 1301;                    //序列号(按请求划分,1开始)
  r.gfcx.HEAD.function = 13;                      //功能号
  r.gfcx.HEAD.czfs     = FJZSet.EntrustWay;                          //操作方式
  r.gfcx.HEAD.status   = 0;                        //状态 0正确 其他错误(应答有效)

  r.gfcx.GDMS = '0' ;
  r.gfcx.CXMS = '0' ;

  if (secuID[1]=='S') {
    r.gfcx.ZQBSLX = FJZSet.SZBourse;
    memcpy(r.gfcx.KHBS,FAccInfo.SZ,KHBS_WIDTH); //KHBS  股东代码或资金帐号
    r.gfcx.KHBSLX = FJZSet.SZBourse;
  }
  else {
    r.gfcx.ZQBSLX = FJZSet.SHBourse;
    memcpy(r.gfcx.KHBS,FAccInfo.SH,KHBS_WIDTH);       //KHBS  股东代码或资金帐号
    r.gfcx.KHBSLX = FJZSet.SHBourse;
  }

  secuID = secuID.SubString(2,secuID.Length());
  strcpy(r.gfcx.ZQBS,secuID.c_str());

  if((retVal=Request(r,&a,num))>0) {
    NewAns(1);

    (*FAnswer)[0].QryStock.Balance    = MToD(a[0].gfcx.YE);
    (*FAnswer)[0].QryStock.Available  = MToD(a[0].gfcx.KYS);
    (*FAnswer)[0].QryStock.BuyFreeze  = MToD(a[0].gfcx.MRDJS);
    (*FAnswer)[0].QryStock.SellFreeze = MToD(a[0].gfcx.MCDJS);
  }

  if(a) { delete []a; }
  if(retVal>0) { return 0; }
  else if(retVal==0) { return -1; }
  else { return retVal; }
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::QryCanBuy()
{
  tagREQUEST r;      //请求
  tagRESULT  *a         = NULL;
  int        num,retVal = 0;
  String     secuID     = FRequest.QryCanBuy.SecuID;

  r.kmsl.HEAD.length   = sizeof(tagKMSL_Request); //长度  (整个数据包长度)
  r.kmsl.HEAD.crc      = 0;                       //CRC校验码 //从serio 开始计算 保留
  r.kmsl.HEAD.serio    = 801;                     //序列号(按请求划分,1开始)
  r.kmsl.HEAD.function = 8;                       //功能号
  r.kmsl.HEAD.czfs     = FJZSet.EntrustWay;                       //操作方式
  r.kmsl.HEAD.status   = 0;                       //状态 0正确 其他错误(应答有效)

  if (secuID[1]=='S') {
    r.kmsl.JYSDM = FJZSet.SZBourse;
    memcpy(r.kmsl.GDDM,FAccInfo.SZ,GDDM_WIDTH);  //KHBS  股东代码或资金帐号
  }
  else {
    r.kmsl.JYSDM = FJZSet.SHBourse;
    memcpy(r.kmsl.GDDM,FAccInfo.SH,GDDM_WIDTH);  //KHBS  股东代码或资金帐号
  }

  secuID = secuID.SubString(2,secuID.Length());
  strcpy(r.kmsl.ZQDM,secuID.c_str());
  strcpy(r.kmsl.WTJG,FloatToStr(FRequest.QryCanBuy.Price).c_str());

  if((retVal=Request(r,&a,num))>0) {
    NewAns(1);
    
    (*FAnswer)[0].QryCanBuy.Num = a[0].kmsl.KMSL ;
  }

  if(a) { delete []a; }
  if(retVal>0) { return 0; }
  else if(retVal==0) { return -1; }
  else { return retVal; }
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::Deal(String SecuID,double Price,int Num,char Sort,short type,String &HTXH)
{
  tagREQUEST r;      //请求
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  if(type==1) //etf create or redeem
  {
    r.etfsgsh.HEAD.length   = sizeof(tagWTQR_Request); //长度  (整个数据包长度)
    r.etfsgsh.HEAD.crc      = 0;                       //CRC校验码 //从serio 开始计算 保留
    r.etfsgsh.HEAD.serio    = 902;                     //序列号(按请求划分,1开始)
    r.etfsgsh.HEAD.function = funcETFSGSH;                       //功能号
    r.etfsgsh.HEAD.czfs     = FJZSet.EntrustWay;                       //操作方式
    r.etfsgsh.HEAD.status   = 0;                       //状态 0正确 其他错误(应答有效)

    if (SecuID[1]=='S')
    {
        r.etfsgsh.JYSDM = FJZSet.SZBourse;
        memcpy(r.etfsgsh.GDDM,FAccInfo.SZ,GDDM_WIDTH); //KHBS  股东代码或资金帐号
    }
    else
    {
        r.etfsgsh.JYSDM = FJZSet.SHBourse;
        memcpy(r.etfsgsh.GDDM,FAccInfo.SH,GDDM_WIDTH); //KHBS  股东代码或资金帐号
    }

    SecuID = SecuID.SubString(2,SecuID.Length());

    r.etfsgsh.MMLB = Sort;

    strcpy(r.etfsgsh.ETFDM,SecuID.c_str());
    strcpy(r.etfsgsh.WTSL,IntToStr(Num).c_str());

    if((retVal=Request(r,&a,num))>0) { HTXH = a[0].etfsgsh.HTXH; }
  }
  else
  {
      r.wtqr.HEAD.length   = sizeof(tagWTQR_Request); //长度  (整个数据包长度)
      r.wtqr.HEAD.crc      = 0;                       //CRC校验码 //从serio 开始计算 保留
      r.wtqr.HEAD.serio    = 901;                     //序列号(按请求划分,1开始)
      r.wtqr.HEAD.function = funcWTQR;                       //功能号
      r.wtqr.HEAD.czfs     = FJZSet.EntrustWay;                       //操作方式
      //r.wtqr.HEAD.czfs     = '1';
      r.wtqr.HEAD.status   = 0;                       //状态 0正确 其他错误(应答有效)

      if (SecuID[1]=='S') {
        r.wtqr.JYSDM = FJZSet.SZBourse;
        memcpy(r.wtqr.GDDM,FAccInfo.SZ,GDDM_WIDTH); //KHBS  股东代码或资金帐号
      }
      else {
        r.wtqr.JYSDM = FJZSet.SHBourse;
        memcpy(r.wtqr.GDDM,FAccInfo.SH,GDDM_WIDTH); //KHBS  股东代码或资金帐号
      }

      SecuID = SecuID.SubString(2,SecuID.Length());

      r.wtqr.MMLB = Sort;

      strcpy(r.wtqr.ZQDM,SecuID.c_str());
      strcpy(r.wtqr.WTJG,FormatFloat("0.000",Price).c_str());
      strcpy(r.wtqr.WTSL,IntToStr(Num).c_str());
      strcpy(r.wtqr.ReqSrcInfo,"");

      if((retVal=Request(r,&a,num))>0) { HTXH = a[0].wtqr.HTXH; }
  }

  if(a) { delete []a; }
  if(retVal>0) { return 0; }
  else if(retVal==0) { return -1; }
  else { return retVal; }
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::Buy()
{
  String htxh = "";
  int    retVal;

    if((retVal=Deal(FRequest.Buy.SecuID,FRequest.Buy.Price,
                    FRequest.Buy.Num, 'B',FRequest.Buy.Type,htxh))==0)
    {
        NewAns(1);

        lstrcpyn((*FAnswer)[0].Buy.ContractID,htxh.c_str(),20);
    }

  return retVal;
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::Sell()
{
  String htxh = "";
  int    retVal;

  if((retVal=Deal(FRequest.Sell.SecuID,FRequest.Sell.Price,
                    FRequest.Sell.Num,'S',FRequest.Sell.Type,htxh))==0) {
    NewAns(1);

    lstrcpyn((*FAnswer)[0].Sell.ContractID,htxh.c_str(),20);
  }

  return retVal;
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::Undo()
{
  tagREQUEST r;      //请求
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  r.wtcd.HEAD.length   = sizeof(tagWTCD_Request); //长度  (整个数据包长度)
  r.wtcd.HEAD.crc      = 0;                       //CRC校验码 //从serio 开始计算 保留
  r.wtcd.HEAD.serio    = 1001;                    //序列号(按请求划分,1开始)
  r.wtcd.HEAD.function = 10;                      //功能号
  r.wtcd.HEAD.czfs     = FJZSet.EntrustWay;                       //操作方式
  r.wtcd.HEAD.status   = 0;                       //状态 0正确 其他错误(应答有效)

  r.wtcd.GDMS  = '0';

  r.wtcd.JYSDM = FRequest.Undo.Bourse==bsSZ?FJZSet.SZBourse:FJZSet.SHBourse;
  if(FRequest.Undo.Bourse==bsSZ) { memcpy(r.wtcd.GDDM,FAccInfo.SZ,GDDM_WIDTH); }
  else { memcpy(r.wtcd.GDDM,FAccInfo.SH,GDDM_WIDTH); }

  strcpy(r.wtcd.HTXH,FRequest.Undo.ContractID);
  strcpy(r.wtcd.ReqSrcInfo,"");

  retVal = Request(r,&a,num);

  if(a) { delete []a; }
  if(retVal>=0) { return 0; }
  else { return retVal; }
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::QryDetail()
{
/*
  tagREQUEST r;      //请求
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  r.cjcx.HEAD.length   = sizeof(tagDRCJCX_Request); //长度  (整个数据包长度)
  r.cjcx.HEAD.crc      = 0;                         //CRC校验码 //从serio 开始计算 保留
  r.cjcx.HEAD.serio    = 1601;                      //序列号(按请求划分,1开始)
  r.cjcx.HEAD.function = 16 ;                       //功能号
  r.cjcx.HEAD.czfs     = 0;                         //操作方式
  r.cjcx.HEAD.status   = 0;                         //状态 0正确 其他错误(应答有效)

  r.cjcx.GDMS = '0' ;
  r.cjcx.CXFS = '1' ;

  r.cjcx.KHBSLX = FRequest.QryDetail.Bourse==bsSZ?FJZSet.SZBourse:FJZSet.SHBourse;
  if(FRequest.QryDetail.Bourse==bsSZ) { memcpy(r.cjcx.KHBS,FAccInfo.SZ,KHBS_WIDTH); }
  else { memcpy(r.cjcx.KHBS,FAccInfo.SH,KHBS_WIDTH); }

  r.cjcx.ZQBSLX = FRequest.QryDetail.Bourse==bsSZ?FJZSet.SZBourse:FJZSet.SHBourse;
  strcpy(r.cjcx.ZQBS," ");
  strcpy(r.cjcx.HTXH,FRequest.QryDetail.ContractID);

  if((retVal=Request(r,&a,num))>0) {
    NewAns(1);

    for(int i=0;i<num;i++) {
      if(a[i].cjcx.CJSL<0) { (*FAnswer)[0].QryDetail.UndoNum = a[i].cjcx.CJSL; }
      else {
        (*FAnswer)[0].QryDetail.Num   = a[i].cjcx.CJSL ;
        (*FAnswer)[0].QryDetail.Price = SMToD(a[i].cjcx.CJJG);
      }
    }
  }

  if(a) { delete []a; }
  if(retVal>=0) { return 0; }
  //else if(retVal==0) { return -1; }
  else { return retVal; }
*/
  if(FRequest.QryDetail.ContractID[0]==0) return -1;
  
  tagREQUEST r;
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  memset(&r,0,sizeof(tagREQUEST));

  r.head.length   = sizeof(tagDRCJCX_Request); //长度  (整个数据包长度)
  r.head.serio    = 15;                      //序列号(按请求划分,1开始)
  r.head.function = 14;                       //功能号
  r.head.status   = 0 ;
  r.head.crc      = 0 ;
  r.head.czfs     = FJZSet.EntrustWay; 

  r.wtcx.GDMS   = '0';
  r.wtcx.CXMS   = '0';

  if(FRequest.QryDetail.Bourse==bsSH)
  {
    r.wtcx.KHBSLX   = FJZSet.SHBourse;
    memcpy(r.wtcx.KHBS,FAccInfo.SH,KHBS_WIDTH);
  }
  else if(FRequest.QryDetail.Bourse==bsSZ)
  {
    r.wtcx.KHBSLX   = FJZSet.SZBourse;
    memcpy(r.wtcx.KHBS,FAccInfo.SZ,KHBS_WIDTH);
  }
  else
  {
    r.wtcx.KHBSLX   = 'Z';
    memcpy(r.wtcx.KHBS,FAccInfo.Capital,KHBS_WIDTH);
  }

  r.wtcx.ZQBSLX = 'N';
  r.wtcx.ZQBS[0]='\0';

  strcpy(r.wtcx.HTXH,FRequest.QryDetail.ContractID);

  if((retVal=Request(r,&a,num))>0)
  {
    if(num>0) {
      NewAns(1);

      for(int i=0;i<1;i++)
      {
        (*FAnswer)[i].QryDetail.Num   = a[i].wtcx.CJSL ;
        (*FAnswer)[i].QryDetail.Price = SMToD(a[i].wtcx.CJJG);
        (*FAnswer)[i].QryDetail.UndoNum =-abs(a[i].wtcx.CDSL);
      }
    }
  }

  if(a) { delete []a; }
  if(retVal>0) { return 0; }
  else if(retVal==0) { return -1; }
  else { return retVal; }   
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::QryHisDetail()
{
  tagREQUEST r;
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  memset(&r,0,sizeof(tagREQUEST));

  r.head.length   = sizeof(tagLSCJCX_Request); //长度  (整个数据包长度)
  r.head.serio    = 1801;                      //序列号(按请求划分,1开始)
  r.head.function = 18 ;                       //功能号
  r.head.czfs     =FJZSet.EntrustWay;
  r.lscjcx.GDMS   = '2';
  r.lscjcx.KHBSLX = 'Z';
  memcpy(r.lscjcx.KHBS,FAccInfo.Capital,KHBS_WIDTH);
  r.lscjcx.ZQBSLX = FRequest.QryHisDetail.Bourse==bsSZ?FJZSet.SZBourse:FJZSet.SHBourse;
  strcpy(r.lscjcx.ZQBS," ");
  strcpy(r.lscjcx.QSRQ,FRequest.QryHisDetail.DateStr);
  strcpy(r.lscjcx.ZZRQ,FRequest.QryHisDetail.DateStr);
  r.lscjcx.CXFS   = '0';  //查明细

  if((retVal=Request(r,&a,num))>0) {
    NewAns(1);

    for(int i=0;i<num;i++) {
      if(strcmp(a[i].lscjcx.HTXH,FRequest.QryHisDetail.ContractID)==0) {
        if(a[i].lscjcx.CJSL<0) { (*FAnswer)[0].QryHisDetail.UndoNum += a[i].lscjcx.CJSL; }
        else {
          if(((*FAnswer)[0].QryHisDetail.Num+a[i].lscjcx.CJSL)!=0) {
            (*FAnswer)[0].QryHisDetail.Price = ((*FAnswer)[0].QryHisDetail.Price*
              (*FAnswer)[0].QryHisDetail.Num+SMToD(a[i].lscjcx.CJJG)*a[i].lscjcx.CJSL)/
              ((*FAnswer)[0].QryHisDetail.Num+a[i].lscjcx.CJSL);
            (*FAnswer)[0].QryHisDetail.Num  += a[i].lscjcx.CJSL;
          }
          else {
            (*FAnswer)[0].QryHisDetail.Price = 0;
            (*FAnswer)[0].QryHisDetail.Num   = 0;
          }
        }

        retVal = 0;
      }
    }
  }

  if(a) { delete []a; }
  if(retVal>0) { return -1; }
  else { return retVal; }
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::QryCsn()
{
  tagREQUEST r;
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  memset(&r,0,sizeof(tagREQUEST));

  r.head.length   = sizeof(tagDRCJCX_Request); //长度  (整个数据包长度)
  r.head.serio    = 1401;                      //序列号(按请求划分,1开始)
  r.head.function = 14 ;                       //功能号
  r.head.czfs     =FJZSet.EntrustWay;
  r.wtcx.GDMS   = '2';
  r.wtcx.CXMS   = '0';
  r.wtcx.KHBSLX = 'Z';
  memcpy(r.wtcx.KHBS,FAccInfo.Capital,KHBS_WIDTH);
  r.wtcx.ZQBSLX = FRequest.QryCsn.Bourse==bsSZ?FJZSet.SZBourse:FJZSet.SHBourse;
  strcpy(r.wtcx.ZQBS," ");
  strcpy(r.wtcx.HTXH,FRequest.QryCsn.ContractID);
  
  if((retVal=Request(r,&a,num))>0) {
    if(num>0) {
      NewAns(1);

      memcpy((*FAnswer)[0].QryCsn.CsgInfo.ContractID,a[0].wtcx.HTXH,HTXH_WIDTH);           //合同序号
      memcpy((*FAnswer)[0].QryCsn.CsgInfo.SecuID,a[0].wtcx.ZQDM,ZQDM_WIDTH);               //证券代码
      memcpy((*FAnswer)[0].QryCsn.CsgInfo.SecuDesc,a[0].wtcx.ZQMC,ZQMC_WIDTH);             //证券名称
      memcpy((*FAnswer)[0].QryCsn.CsgInfo.Time,a[0].wtcx.WTSJ,DATETIME_WIDTH);             //委托时间
      (*FAnswer)[0].QryCsn.CsgInfo.Type      = ConvertType(a[0].wtcx.MMLB);                             //买卖类别
      (*FAnswer)[0].QryCsn.CsgInfo.State     = ConvertState(a[0].wtcx.CDBZ);                             //撤单状态
      (*FAnswer)[0].QryCsn.CsgInfo.CsnVol    = a[0].wtcx.WTSL;                             //委托数量
      (*FAnswer)[0].QryCsn.CsgInfo.TrdVol    = a[0].wtcx.CJSL;                             //成交数量
      (*FAnswer)[0].QryCsn.CsgInfo.CancelVol = a[0].wtcx.CDSL;                             //撤单数量
      (*FAnswer)[0].QryCsn.CsgInfo.Bourse    = a[0].wtcx.JYSDM==FJZSet.SZBourse?bsSZ:bsSH; //交易所类型

      (*FAnswer)[0].QryCsn.CsgInfo.CsnPrice  = SMToD(a[0].wtcx.WTJG); //委托价格
      (*FAnswer)[0].QryCsn.CsgInfo.TrdPrice  = SMToD(a[0].wtcx.CJJG); //成交价格
    }
  }

  if(a) { delete []a; }
  if(retVal>0) { return 0; }
  else if(retVal==0) { return -1; }
  else { return retVal; }
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::QryCurCsn()
{
  tagREQUEST r;
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  memset(&r,0,sizeof(tagREQUEST));

  r.head.length   = sizeof(tagDRCJCX_Request); //长度  (整个数据包长度)
  r.head.serio    = 1401;                      //序列号(按请求划分,1开始)
  r.head.function = 14 ;                       //功能号
  r.head.czfs     =FJZSet.EntrustWay;
  r.wtcx.GDMS   = '2';
  r.wtcx.CXMS   = '0';
  r.wtcx.KHBSLX = 'Z';
  memcpy(r.wtcx.KHBS,FAccInfo.Capital,KHBS_WIDTH);
  r.wtcx.ZQBSLX = ' ';
  strcpy(r.wtcx.ZQBS," ");
  strcpy(r.wtcx.HTXH," ");
  
  if((retVal=Request(r,&a,num))>0) {
    if(num>0) {
      NewAns(num);

      for(int i=0;i<num;i++) {
         memcpy((*FAnswer)[i].QryCurCsn.CsgInfo.ContractID,a[i].wtcx.HTXH,HTXH_WIDTH);           //合同序号
         memcpy((*FAnswer)[i].QryCurCsn.CsgInfo.SecuID,a[i].wtcx.ZQDM,ZQDM_WIDTH);               //证券代码
         memcpy((*FAnswer)[i].QryCurCsn.CsgInfo.SecuDesc,a[i].wtcx.ZQMC,ZQMC_WIDTH);             //证券名称
         memcpy((*FAnswer)[i].QryCurCsn.CsgInfo.Time,a[i].wtcx.WTSJ,DATETIME_WIDTH);             //委托时间
         (*FAnswer)[i].QryCurCsn.CsgInfo.Type      = ConvertType(a[i].wtcx.MMLB);                             //买卖类别
         (*FAnswer)[i].QryCurCsn.CsgInfo.State     = ConvertState(a[i].wtcx.CDBZ);                             //撤单状态
         (*FAnswer)[i].QryCurCsn.CsgInfo.CsnVol    = a[i].wtcx.WTSL;                             //委托数量
         (*FAnswer)[i].QryCurCsn.CsgInfo.TrdVol    = a[i].wtcx.CJSL;                             //成交数量
         (*FAnswer)[i].QryCurCsn.CsgInfo.CancelVol = a[i].wtcx.CDSL;                             //撤单数量
         (*FAnswer)[i].QryCurCsn.CsgInfo.Bourse    = a[i].wtcx.JYSDM==FJZSet.SZBourse?bsSZ:bsSH; //交易所类型

         (*FAnswer)[i].QryCurCsn.CsgInfo.CsnPrice  = SMToD(a[i].wtcx.WTJG); //委托价格
         (*FAnswer)[i].QryCurCsn.CsgInfo.TrdPrice  = SMToD(a[i].wtcx.CJJG); //成交价格
      }
    }
  }

  if(a) { delete []a; }
  if(retVal>0) { return 0; }
  else if(retVal==0) { return -1; }
  else { return retVal; }
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::QryHisCsn()
{
  tagREQUEST r;
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  memset(&r,0,sizeof(tagREQUEST));

  r.head.length   = sizeof(tagLSWTCX_Request); //长度  (整个数据包长度)
  r.head.serio    = 1501;                      //序列号(按请求划分,1开始)
  r.head.function = 15 ;                       //功能号
  r.head.czfs     =FJZSet.EntrustWay;
  r.lswtcx.GDMS   = '2';
  r.lswtcx.KHBSLX = 'Z';
  memcpy(r.lswtcx.KHBS,FAccInfo.Capital,KHBS_WIDTH);
  r.lswtcx.ZQBSLX = ' ';
  strcpy(r.lswtcx.ZQBS," ");
  strcpy(r.lswtcx.QSRQ,FRequest.QryHisCsn.StartDay);
  strcpy(r.lswtcx.ZZRQ,FRequest.QryHisCsn.EndDay);

  if((retVal=Request(r,&a,num))>0) {
    if(num>0) {
      NewAns(num);

      for(int i=0;i<num;i++) {
         memcpy((*FAnswer)[i].QryHisCsn.CsgInfo.ContractID,a[i].lswtcx.HTXH,HTXH_WIDTH);   //合同序号
         memcpy((*FAnswer)[i].QryHisCsn.CsgInfo.SecuID,a[i].lswtcx.ZQDM,ZQDM_WIDTH);       //证券代码
         memcpy((*FAnswer)[i].QryHisCsn.CsgInfo.SecuDesc,a[i].lswtcx.ZQMC,ZQMC_WIDTH);     //证券名称
         memcpy((*FAnswer)[i].QryHisCsn.CsgInfo.Date,a[i].lswtcx.WTRQ,DATETIME_WIDTH);     //委托时间
         (*FAnswer)[i].QryHisCsn.CsgInfo.Type      = ConvertType(a[i].lswtcx.MMLB);                     //买卖类别
         (*FAnswer)[i].QryHisCsn.CsgInfo.CsnVol    = a[i].lswtcx.WTSL;                     //委托数量
         (*FAnswer)[i].QryHisCsn.CsgInfo.TrdVol    = a[i].lswtcx.CJSL;                     //成交数量
         (*FAnswer)[i].QryHisCsn.CsgInfo.CancelVol = a[i].lswtcx.CDSL;                     //撤单数量
         (*FAnswer)[i].QryHisCsn.CsgInfo.CsnPrice  = SMToD(a[i].lswtcx.WTJG); //委托价格
         (*FAnswer)[i].QryHisCsn.CsgInfo.TrdPrice  = SMToD(a[i].lswtcx.CJJG); //成交价格
      }
    }
  }

  if(a) { delete []a; }
  if(retVal>0) { return 0; }
  else if(retVal==0) { return -1; }
  else { return retVal; }
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::QryCurTrd()
{
  tagREQUEST r;
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  memset(&r,0,sizeof(tagREQUEST));

  r.head.length   = sizeof(tagDRCJCX_Request); //长度  (整个数据包长度)
  r.head.serio    = 1601;                      //序列号(按请求划分,1开始)
  r.head.function = 16 ;                       //功能号
  r.head.czfs     =FJZSet.EntrustWay;
  r.cjcx.GDMS   = '2';
  r.cjcx.KHBSLX = 'Z';
  memcpy(r.cjcx.KHBS,FAccInfo.Capital,KHBS_WIDTH);
  r.cjcx.CXFS = '1';
  r.cjcx.ZQBSLX = ' ';                 
  strcpy(r.cjcx.ZQBS," ");
  strcpy(r.cjcx.HTXH," ");

  if((retVal=Request(r,&a,num))>0) {
    if(num>0) {
      NewAns(num);

      for(int i=0;i<num;i++) {
        memcpy((*FAnswer)[i].QryCurTrd.TrdInfo.SecuID,a[i].cjcx.ZQDM,ZQDM_WIDTH);
        memcpy((*FAnswer)[i].QryCurTrd.TrdInfo.SecuDesc,a[i].cjcx.ZQMC,ZQMC_WIDTH);
        memcpy((*FAnswer)[i].QryCurTrd.TrdInfo.Time,a[i].cjcx.WTSJ,DATETIME_WIDTH);
        (*FAnswer)[i].QryCurTrd.TrdInfo.Type  = ConvertType(a[i].cjcx.MMLB);
        (*FAnswer)[i].QryCurTrd.TrdInfo.Vol   = a[i].cjcx.CJSL;
        (*FAnswer)[i].QryCurTrd.TrdInfo.Price = SMToD(a[i].cjcx.CJJG);
      }
    }
  }

  if(a) { delete []a; }
  if(retVal>0) { return 0; }
  else if(retVal==0) { return -1; }
  else { return retVal; }
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::QryHisTrd()
{
  tagREQUEST r;
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  memset(&r,0,sizeof(tagREQUEST));

  r.head.length   = sizeof(tagLSCJCX_Request); //长度  (整个数据包长度)
  r.head.serio    = 1801;                      //序列号(按请求划分,1开始)
  r.head.function = 18 ;                       //功能号
  r.head.czfs     =FJZSet.EntrustWay;
  r.lscjcx.GDMS   = '2';
  r.lscjcx.KHBSLX = 'Z';
  memcpy(r.lscjcx.KHBS,FAccInfo.Capital,KHBS_WIDTH);
  r.lscjcx.ZQBSLX = ' ';
  strcpy(r.lscjcx.ZQBS," ");
  strcpy(r.lscjcx.QSRQ,FRequest.QryHisTrd.StartDay);
  strcpy(r.lscjcx.ZZRQ,FRequest.QryHisTrd.EndDay);
  r.lscjcx.CXFS   = '0';

  if((retVal=Request(r,&a,num))>0) {
    if(num>0) {
      NewAns(num);

      for(int i=0;i<num;i++) {
        memcpy((*FAnswer)[i].QryHisTrd.TrdInfo.SecuID,a[i].lscjcx.ZQDM,ZQDM_WIDTH);
        memcpy((*FAnswer)[i].QryHisTrd.TrdInfo.SecuDesc,a[i].lscjcx.ZQMC,ZQMC_WIDTH);
        memcpy((*FAnswer)[i].QryHisTrd.TrdInfo.Date,a[i].lscjcx.FSRQ,DATETIME_WIDTH);
        (*FAnswer)[i].QryHisTrd.TrdInfo.Type  = ConvertType(a[i].lscjcx.MMLB);
        (*FAnswer)[i].QryHisTrd.TrdInfo.Vol   = a[i].lscjcx.CJSL;
        (*FAnswer)[i].QryHisTrd.TrdInfo.Price = SMToD(a[i].lscjcx.CJJG);
      }
    }
  }

  if(a) { delete []a; }
  if(retVal>0) { return 0; }
  else if(retVal==0) { return -1; }
  else { return retVal; }
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::QryBill()
{
  tagREQUEST r;
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  memset(&r,0,sizeof(tagREQUEST));

  r.head.length   = sizeof(tagZJLS_Request); //长度  (整个数据包长度)
  r.head.serio    = 1901;                      //序列号(按请求划分,1开始)
  r.head.function = 19 ;                       //功能号
  r.head.czfs     =FJZSet.EntrustWay;
  r.zjls.KHBSLX   = 'Z';
  memcpy(r.zjls.KHBS,FAccInfo.Capital,KHBS_WIDTH);
  strcpy(r.zjls.QSRQ,FRequest.QryBill.StartDay);
  strcpy(r.zjls.ZZRQ,FRequest.QryBill.EndDay);
  
  if((retVal=Request(r,&a,num))>0) {
    if(num>0) {
      NewAns(num);

      for(int i=0;i<num;i++) {
        memcpy((*FAnswer)[i].QryBill.FundInfo.Date,a[i].zjls.FSRQ,DATETIME_WIDTH);
        memcpy((*FAnswer)[i].QryBill.FundInfo.SecuID,a[i].zjls.ZQDM,ZQDM_WIDTH);
        memcpy((*FAnswer)[i].QryBill.FundInfo.SecuDesc,a[i].zjls.ZQMC,ZQMC_WIDTH);
        memcpy((*FAnswer)[i].QryBill.FundInfo.Type,a[i].zjls.ZYDMSM,ZYDM_WIDTH);
        (*FAnswer)[i].QryBill.FundInfo.Vol     = a[i].zjls.CJSL;
        (*FAnswer)[i].QryBill.FundInfo.Price   = SMToD(a[i].zjls.CJJG);
        (*FAnswer)[i].QryBill.FundInfo.TrdMny  = MToD(a[i].zjls.CJJE);
        (*FAnswer)[i].QryBill.FundInfo.Balance = MToD(a[i].zjls.ZJBCYE);
      }
    }
  }

  if(a) { delete []a; }
  if(retVal>0) { return 0; }
  else if(retVal==0) { return -1; }
  else { return retVal; }
}
//---------------------------------------------------------------------------
int  TTrdItf_JZ::QryStocks()
{
  tagREQUEST r;
  tagRESULT  *a = NULL;
  int        num,retVal = 0;

  memset(&r,0,sizeof(tagREQUEST));

  r.head.length   = sizeof(tagZJLS_Request); //长度  (整个数据包长度)
  r.head.serio    = 1301;                      //序列号(按请求划分,1开始)
  r.head.function = 13 ;                       //功能号
  r.head.czfs     =FJZSet.EntrustWay;
  r.gfcx.GDMS     = '0';
  r.gfcx.CXMS     = '0';
  //r.gfcx.KHBSLX   = 'Z';  //查整个资金账号
  if(FRequest.QryStocks.Bourse==bsSH)
  {
    r.gfcx.KHBSLX   = FJZSet.SHBourse;
    memcpy(r.gfcx.KHBS,FAccInfo.SH,KHBS_WIDTH);
  }
  else if(FRequest.QryStocks.Bourse==bsSZ)
  {
    r.gfcx.KHBSLX   = FJZSet.SZBourse;
    memcpy(r.gfcx.KHBS,FAccInfo.SZ,KHBS_WIDTH);
  }
  else
  {
    r.gfcx.KHBSLX   = 'Z';
    memcpy(r.gfcx.KHBS,FAccInfo.Capital,KHBS_WIDTH);
  }
  r.gfcx.ZQBSLX   = ' ';         //'0'-'9'交易所代码(参看柜台设置)
  strcpy(r.gfcx.ZQBS," ");       //证券标识

  if((retVal=Request(r,&a,num))>0) {
    if(num>0) {
      NewAns(num);

      for(int i=0;i<num;i++)
      {
        if(a[i].gfcx.JYSDM == FJZSet.SHBourse)
          (*FAnswer)[i].QryStocks.StockInfo.SecuID[0]='H';
        else if( a[i].gfcx.JYSDM == FJZSet.SZBourse)
          (*FAnswer)[i].QryStocks.StockInfo.SecuID[0]='S';
        else
          (*FAnswer)[i].QryStocks.StockInfo.SecuID[0]='N';
          
        memcpy((*FAnswer)[i].QryStocks.StockInfo.SecuID+1,a[i].gfcx.ZQDM,ZQDM_WIDTH);
        memcpy((*FAnswer)[i].QryStocks.StockInfo.SecuDesc,a[i].gfcx.GDDM,GDDM_WIDTH);
        (*FAnswer)[i].QryStocks.StockInfo.Balance       = MToD(a[i].gfcx.YE);
        (*FAnswer)[i].QryStocks.StockInfo.Available     = MToD(a[i].gfcx.KYS);
        (*FAnswer)[i].QryStocks.StockInfo.BuyFreeze     = MToD(a[i].gfcx.MRDJS);
        (*FAnswer)[i].QryStocks.StockInfo.SellFreeze    = MToD(a[i].gfcx.MCDJS);
        (*FAnswer)[i].QryStocks.StockInfo.AbnorFreeze   = MToD(a[i].gfcx.YCDJS);  //异常冻结
        (*FAnswer)[i].QryStocks.StockInfo.Cost          = MToD(a[i].gfcx.CKCB);   //参考成本
        (*FAnswer)[i].QryStocks.StockInfo.CostPrice     = SMToD(a[i].gfcx.CKCBJG/100.0f); //参考成本价
        (*FAnswer)[i].QryStocks.StockInfo.CurVal        = MToD(a[i].gfcx.CKSZ);   //参考市值
        (*FAnswer)[i].QryStocks.StockInfo.CurPrice      = SMToD(a[i].gfcx.CKSZJG); //参考市价
        (*FAnswer)[i].QryStocks.StockInfo.ProfitAndLoss = MToD(a[i].gfcx.CKYK);   //参考盈亏


      }
    }
  }

  if(a) { delete []a; }
  if(retVal>0) { return 0; }
  else if(retVal==0) { return -1; }
  else { return retVal; }
}
//---------------------------------------------------------------------------

//关闭中间件链接
void TTrdItf_JZ::CloseLink(void)
{
  if(KDAPI_d && FCurConnectNO>-1)
  {
    KDAPI_d(FCurConnectNO);
    FCurConnectNO=-1;
    InterlockedDecrement(&link_count_jz);
  }
}
