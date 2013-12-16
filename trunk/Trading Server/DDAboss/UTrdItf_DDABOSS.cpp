/*
 *  DESC: 顶点中间件内部接口
 *  FILE: UTrdItf_DD
 *  BY:   CodeHunter
 */
 
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <IniFiles.hpp>

#include "UTrdItf_DDABOSS.h"
//---------------------------------------------------------------------------
#define jtsh  "SH"
#define jtsz  "SZ"
#define mtrmb "RMB"
#define mtusd "USD"
#define mthkd "HKD"
#define ERR_OTHERS               -103
#define ERR_UNIMPLEMENTED        -200  //未处理

int  TTrdItf_DDABOSS::GetGDZH(void* pFix, char *pKHH, TAccountInfo *ai)
{
    if (pFix == NULL) return -1;

    char buffer[512];
    char jys[8],bz[8],gdzh[16];
    int  nResult;

    FDll.FixCreate(pFix, FUNC_JY_GDHCX);
    FDll.FixSet(pFix, FID_KHH, pKHH);
    FDll.FixSet(pFix, FID_SQLB, 0);

    if (FDll.FixWrite(pFix) < 0) return -2;
    
    while ( 1 )
    {
        nResult = FDll.FixReadEx(pFix, 1000);
        FDll.FixGetBuffer(pFix, buffer, sizeof(buffer)-1);
        if (nResult <= 0) break;
        if (FDll.FixGetRecNo(pFix) < 0) break;

        lstrcpyn(jys , FDll.FixGet(pFix, FID_JYS, buffer, 0), sizeof(jys));
        lstrcpyn(gdzh, FDll.FixGet(pFix, FID_GDH, buffer, 0), sizeof(gdzh));

        if (strcmpi(jys, jtsh) == 0)
        {
            lstrcpyn(ai->SH, gdzh, sizeof(ai->SH));
        }
        else if (strcmpi(jys, jtsz) == 0)
        {
            lstrcpyn(ai->SZ, gdzh, sizeof(ai->SZ));
        }
    }

    return 0;
}

int  TTrdItf_DDABOSS::GetZJZH(void* pFix, char *pKHH, TAccountInfo *ai)
{
    if (pFix == NULL) return -1;

    char buffer[512];
    int nResult;

    FDll.FixCreate(pFix, FUNC_JY_ZJCX_KHH);
    FDll.FixSet(pFix, FID_KHH, pKHH);
    FDll.FixSet(pFix, FID_BZ,  "RMB");

    if (FDll.FixWrite(pFix) < 0) return -2;
    
    while ( 1 )
    {
        nResult = FDll.FixReadEx(pFix, 1000);
        FDll.FixGetBuffer(pFix, buffer, sizeof(buffer)-1);
        if (nResult <= 0) break;
        if (FDll.FixGetRecNo(pFix) < 0) break;

        lstrcpyn(ai->Capital , FDll.FixGet(pFix, FID_ZJZH, buffer, 0), sizeof(ai->Capital));
    }

    return 0;
}


TTrdItf_DDABOSS::TTrdItf_DDABOSS(const char *psetupfile,ADDLOG plogfunc)
	:TTrdItfBase(psetupfile,plogfunc)
{
		FFix = NULL;
  	ZeroMemory(&FSet ,sizeof(FSet));
}

TTrdItf_DDABOSS::~TTrdItf_DDABOSS()
{
		if(FFix!=NULL) {FDll.FixClose(FFix);  FFix = NULL;};
}

int  TTrdItf_DDABOSS::Init()
{
		FFix = FDll.FixConnect(FSet.pDest, FSet.pRemote);

    if (FFix)
        return 0;
		else
		{
			strcpy(FLastError.Sender,"DDABOSS");
			FLastError.ErrorCode = -100;
			lstrcpyn( FLastError.Text,"FixConnect连接柜台失败",MAX_TEXT );
			ODS('M',PLUGINNAME,"%s,Dest:%s",FLastError.Text,FSet.pDest);
			//this->SetError();
			return -2;
		}
}

int  TTrdItf_DDABOSS::SetAccount()
{
    char buffer[512],*pOut;
    int nIndex,nResult;
    char jys[8],bz[8],gdzh[16];

    //ZERO FAccInfo
    ZeroMemory(&FAccInfo,sizeof(FAccInfo));
		lstrcpyn(FAccInfo.PW, FRequest.SetAccount.PW, sizeof(FAccInfo.PW));

		if (FRequest.SetAccount.LoginType == asCA)
    {
        lstrcpyn(FAccInfo.Capital,FRequest.SetAccount.Account,13);

        FDll.FixCreate(FFix, FUNC_JY_JYMMJY);
        FDll.FixSet(FFix, FID_ZJZH, FRequest.SetAccount.Account);
        FDll.FixSet(FFix, FID_JYMM, FRequest.SetAccount.PW);
        FDll.FixSet(FFix, FID_JMLX, 0);
        if (FDll.FixWrite(FFix) > 0 && FDll.FixReadEx(FFix, 1000) > 0)
        {
            FDll.FixGetBuffer(FFix, buffer, sizeof(buffer) - 1);
            if (FDll.FixGetInt(FFix, FID_CODE) == 1)
            {
                memset(FKHH, 0, sizeof(FKHH));
								strcpy(FKHH, FDll.FixGet(FFix, FID_KHH, buffer, 0));

								GetGDZH(FFix, FKHH, &FAccInfo);
            }
            else
						{
								SetError();
								return FDll.FixGetInt(FFix, FID_CODE);
            }
				}
				else
				{
					SetError();
					return -1;
        }
		}
		else if (FRequest.SetAccount.LoginType == asSHA)
    {
				FDll.FixCreate(FFix, FUNC_JY_JYMMJY);
        FDll.FixSet(FFix, FID_GDH, FRequest.SetAccount.Account);
        FDll.FixSet(FFix, FID_JYS, jtsh);
        FDll.FixSet(FFix, FID_JYMM, FRequest.SetAccount.PW);
        FDll.FixSet(FFix, FID_JMLX, 0);
        if (FDll.FixWrite(FFix) > 0 && FDll.FixReadEx(FFix, 1000) > 0)
        {
            FDll.FixGetBuffer(FFix, buffer, sizeof(buffer) - 1);
            if (FDll.FixGetInt(FFix, FID_CODE) == 1)
            {
                memset(FKHH, 0, sizeof(FKHH));
                lstrcpyn(FKHH, FDll.FixGet(FFix, FID_KHH, buffer, 0), sizeof(FKHH));
                GetGDZH(FFix, FKHH, &FAccInfo);
                GetZJZH(FFix, FKHH, &FAccInfo);
								lstrcpyn(FAccInfo.SH,FRequest.SetAccount.Account,sizeof(FAccInfo.SH));
            }
            else
            {
								SetError();
                return FDll.FixGetInt(FFix, FID_CODE);
            }
				}
				else
				{
        	SetError();
					return -1;
        }
    }
		else if (FRequest.SetAccount.LoginType == asSZA)
    {
        FDll.FixCreate(FFix, FUNC_JY_JYMMJY);
        FDll.FixSet(FFix, FID_GDH, FRequest.SetAccount.Account);
        FDll.FixSet(FFix, FID_JYS, jtsz);
        FDll.FixSet(FFix, FID_JYMM, FRequest.SetAccount.PW);
        FDll.FixSet(FFix, FID_JMLX, 0);
        if (FDll.FixWrite(FFix) > 0 && FDll.FixReadEx(FFix, 1000) > 0)
        {
            FDll.FixGetBuffer(FFix, buffer, sizeof(buffer) - 1);
            if (FDll.FixGetInt(FFix, FID_CODE) == 1)
            {
                memset(FKHH, 0, sizeof(FKHH));
                lstrcpyn(FKHH, FDll.FixGet(FFix, FID_KHH, buffer, 0), sizeof(FKHH));
                GetGDZH(FFix, FKHH, &FAccInfo);
                GetZJZH(FFix, FKHH, &FAccInfo);
								lstrcpyn(FAccInfo.SZ,FRequest.SetAccount.Account,sizeof(FAccInfo.SZ));
            }
            else
            {
                SetError();
                return FDll.FixGetInt(FFix, FID_CODE);
            }
				}
				else
				{
          SetError();
					return -1;
        }
    }

    NewAns(1);
    memcpy(&((*FAnswer)[0].SetAccount.AccountInfo),&FAccInfo,sizeof(TAccountInfo));
    return 0;
}

//////查询函数//////

int  TTrdItf_DDABOSS::QryMoney()
{
    if (FFix == NULL) return -1;

    char buffer[512];
    int  nResult;

		FDll.FixCreate(FFix, FUNC_JY_ZJCX_KHH);
		FDll.FixSet(FFix, FID_KHH, FKHH);
    FDll.FixSet(FFix, FID_BZ,  ConvertMoneyType(FRequest.QryMoney.MoneyType));
		FDll.FixSet(FFix, FID_LOGICAL, "1");

		if (FDll.FixWrite(FFix) < 0)
		{
			SetError();
			return -2;
		}
    while ( 1 )
    {
				nResult = FDll.FixReadEx(FFix, 1000);
				FDll.FixGetBuffer(FFix, buffer, sizeof(buffer)-1);
        if (nResult <= 0) break;
        if (FDll.FixGetRecNo(FFix) < 0) break;

        NewAns(1);
				(*FAnswer)[0].QryMoney.MoneyInfo.balance   = FDll.FixGetDouble(FFix, FID_ZHYE);
				(*FAnswer)[0].QryMoney.MoneyInfo.available = FDll.FixGetDouble(FFix, FID_KYZJ);
				(*FAnswer)[0].QryMoney.MoneyInfo.MoneyType =
					ConvertMoneyType(FDll.FixGet(FFix, FID_BZ,buffer,0));
        return 0;
		}

    return -3;
}
/*
int  TTrdItf_DDABOSS::QryDetail()
{
    if(FRequest.QryDetail.ContractID[0]==0) return -1;
    if (FFix == NULL) return -1;

    char buffer[512];
    FDll.FixCreate(FFix, 14100);
		FDll.FixSet(FFix, FID_WTH,  FRequest.QryDetail.ContractID);
    int nResult = FDll.FixWrite(FFix);
    if (nResult >= 0)
    {
				nResult = FDll.FixReadEx(FFix, 1000);
        FDll.FixGetBuffer(FFix, buffer, sizeof(buffer)-1);
        if (nResult > 0)
        {
            NewAns(1);
            (*FAnswer)[0].QryDetail.Num   = FDll.FixGetInt(FFix, FID_CJSL);
            (*FAnswer)[0].QryDetail.Price = FDll.FixGetDouble(FFix, FID_CJJG);
            (*FAnswer)[0].QryDetail.UndoNum = -FDll.FixGetInt(FFix, FID_CDSL);
        }
        else
        {
            return -3;
        }
    }
    else
    {
        return -2;
    }

    return 0;
}
*/
int  TTrdItf_DDABOSS::QryCurCsn()
{
    if (FFix == NULL) return -1;

    char buffer[512];
    int  nResult;

    FDll.FixCreate(FFix, FUNC_JY_DRWTCX);
		FDll.FixSet(FFix, FID_KHH,  FKHH);
		if( FRequest.QryCurCsn.OrderID[0] != 0 )
		{
			FDll.FixSet(FFix, FID_WTH,  FRequest.QryCurCsn.OrderID);
		}
		if (FDll.FixWrite(FFix) < 0)
		{
			SetError();
			return -2;
		}

    TList * lstAns = new TList();
    try
    {
        while (1)
        {
            nResult = FDll.FixReadEx(FFix, 1000);
            FDll.FixGetBuffer(FFix, buffer, sizeof(buffer)-1);
            if (nResult <= 0) break;
            if (FDll.FixGetRecNo(FFix) < 0) break;

						TOrderInfo *ci = new TOrderInfo;
						memset(ci, 0, sizeof(TOrderInfo));

						lstrcpyn(ci->ContractID,
							FDll.FixGet(FFix, FID_WTH,  buffer, 0), sizeof(ci->ContractID));
						lstrcpyn(ci->SecuID,
							FDll.FixGet(FFix, FID_ZQDM, buffer, 0), sizeof(ci->SecuID));
						ci->Market = ConvertMarketType( FDll.FixGet(FFix,FID_JYS,buffer,0));
						ci->Time = ConvertTimeToInt( FDll.FixGet(FFix, FID_WTSJ,   buffer, 0));
						ci->Date = ConvertDateToInt( FDll.FixGet(FFix, FID_RQ,   buffer, 0));
						ci->Type = ConvertOrderType( FDll.FixGet(FFix, FID_WTLB,   buffer, 0));
						//ci->State= ConvertOrderState(FDll.FixGet(FFix, FID_SBJG, buffer,0));
						ci->State= ConvertOrderState(FDll.FixGet(FFix, FID_SBJGSM, buffer,0));
						ci->CsnVol    = FDll.FixGetInt(FFix, FID_WTSL);
            ci->TrdVol    = FDll.FixGetInt(FFix, FID_CJSL);
            ci->CancelVol = FDll.FixGetInt(FFix, FID_CDSL);
            ci->CsnPrice  = FDll.FixGetDouble(FFix, FID_WTJG);
            ci->TrdPrice  = FDll.FixGetDouble(FFix, FID_CJJG);
						lstrcpyn(ci->Account,
							FDll.FixGet(FFix, FID_GDH, buffer, 0), sizeof(ci->Account));
            lstAns->Add(ci);
        }

        if (lstAns->Count > 0)
        {
            NewAns(lstAns->Count);
            for (int i = 0; i < lstAns->Count; i++)
            {
								TOrderInfo *ci = (TOrderInfo *)lstAns->Items[i];
                memcpy(&(*FAnswer)[i].QryCurCsn.OrderInfo, ci, sizeof(TOrderInfo));
            }
        }

        for (int i = 0; i < lstAns->Count; i++)
        {
						TOrderInfo *ci = (TOrderInfo *)lstAns->Items[i];
            delete ci;
        }
        lstAns->Clear();
    }
    __finally
    {
        delete lstAns;
    }

    return 0;
}

int  TTrdItf_DDABOSS::QryCurTrd()
{
    if (FFix == NULL) return -1;

    char buffer[512];
    char temp[20];
    int  nResult;

		FDll.FixCreate(FFix, FUNC_JY_FBCJCX);
		FDll.FixSet(FFix, FID_KHH,  FKHH);
		if( FRequest.QryCurTrd.OrderID[0] != 0 )
		{
			FDll.FixSet(FFix, FID_WTH,  FRequest.QryCurTrd.OrderID);
    }
		if (FDll.FixWrite(FFix) < 0){SetError(); return -2;}

		TList * lstAns = new TList();
    try
    {
        while (1)
        {
            nResult = FDll.FixReadEx(FFix, 1000);
            FDll.FixGetBuffer(FFix, buffer, sizeof(buffer)-1);
            if (nResult <= 0) break;
            if (FDll.FixGetRecNo(FFix) < 0) break;

            TTradeInfo *ti = new TTradeInfo;
            memset(ti, 0, sizeof(TTradeInfo));

						strncpy(ti->SecuID,   FDll.FixGet(FFix, FID_ZQDM, buffer, 0), CODE_LEN);
						strncpy(ti->ContractID ,FDll.FixGet(FFix,FID_WTH,buffer,0),SEQ_LEN);
						strncpy(ti->TrdID, FDll.FixGet(FFix, FID_CJBH, buffer, 0), SEQ_LEN);
						ti->Time = ConvertTimeToInt(FDll.FixGet(FFix, FID_CJSJ,   buffer, 0));
						ti->Date = ConvertDateToInt(FDll.FixGet(FFix, FID_RQ,   buffer, 0));
						ti->Type = ConvertOrderType(FDll.FixGet(FFix, FID_WTLB, buffer, 0));
						ti->Market = ConvertMarketType(FDll.FixGet(FFix, FID_JYS, buffer, 0));

						ti->Vol   = FDll.FixGetInt(FFix, FID_CJSL);
						FDll.FixGet(FFix,FID_CXBZ,buffer,0);
						if( buffer[0] == 'W' ) ti->Vol = -abs(ti->Vol);
						ti->Price = FDll.FixGetDouble(FFix, FID_CJJG);
						strncpy(ti->Account ,
							FDll.FixGet(FFix,FID_GDH,buffer,0),sizeof(ti->Account));

            lstAns->Add(ti);
        }

        if (lstAns->Count > 0)
        {
            NewAns(lstAns->Count);
            for (int i = 0; i < lstAns->Count; i++)
            {
                TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
                memcpy(&(*FAnswer)[i].QryCurTrd.TrdInfo, ti, sizeof(TTradeInfo));
            }
        }

        for (int i = 0; i < lstAns->Count; i++)
        {
            TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
            delete ti;
        }
        lstAns->Clear();
    }
    __finally
    {
        delete lstAns;
    }

    return 0;

}

int  TTrdItf_DDABOSS::QryStocks()
{
    if (FFix == NULL) return -1;

    char buffer[512];
    char temp[20];
    int  nResult;

    FDll.FixCreate(FFix, FUNC_JY_CCCX);
		FDll.FixSet(FFix, FID_KHH, FKHH);
		if(  FRequest.QryStocks.Market !=  mtNo)
		{
			FDll.FixSet(FFix, FID_JYS, ConvertMarketType( FRequest.QryStocks.Market ));
			FDll.FixSet(FFix, FID_GDH,
				GetStockAccountByMarket(FRequest.QryStocks.Market));
		}

		if (FDll.FixWrite(FFix) < 0) {SetError();return -2; }

		TList * lstAns = new TList();
    try
		{
        while (1)
        {
            nResult = FDll.FixReadEx(FFix, 1000);
            FDll.FixGetBuffer(FFix, buffer, sizeof(buffer)-1);
            if (nResult <= 0) break;
            if (FDll.FixGetRecNo(FFix) < 0) break;

            TStockInfo *si = new TStockInfo;
						memset(si, 0, sizeof(TStockInfo));

						strncpy(si->SecuID ,
							FDll.FixGet(FFix, FID_ZQDM, buffer, 0), sizeof(si->SecuID));
						strncpy(si->Account,
							FDll.FixGet(FFix, FID_GDH, buffer, 0), sizeof(si->Account));
						si->PosDir = ConvertPosDir("");
						si->Market =   ConvertMarketType(FDll.FixGet(FFix,FID_JYS,buffer,0));
						si->Balance=  FDll.FixGetInt(FFix, FID_ZQSL);
						si->Available     = FDll.FixGetInt(FFix, FID_KMCSL);
						si->CostPrice     = FDll.FixGetDouble(FFix, FID_MRJJ);
						si->CurPrice      = FDll.FixGetDouble(FFix, FID_ZXJ);
						si->PosNum        = si->Balance +
							+FDll.FixGetInt(FFix, FID_FLTSL)         //表示当天赎回的数量（股票）或当天申购的数量（ETF）
							+FDll.FixGetInt(FFix, FID_DRMRCJSL)      //当日买入成交数量
							-FDll.FixGetInt(FFix, FID_DRMCCJSL)      //当日卖出成交数量
							+FDll.FixGetInt(FFix, FID_PGSL)          //配股未上市数量
							;
						lstAns->Add(si);
        }

        if (lstAns->Count > 0)
        {
            NewAns(lstAns->Count);
            for (int i = 0; i < lstAns->Count; i++)
            {
                TStockInfo *si = (TStockInfo *)lstAns->Items[i];
                memcpy(&(*FAnswer)[i].QryStocks.StockInfo, si, sizeof(TStockInfo));
            }
        }

        for (int i = 0; i < lstAns->Count; i++)
        {
            TStockInfo *si = (TStockInfo *)lstAns->Items[i];
            delete si;
        }
        lstAns->Clear();
    }
    __finally
    {
        delete lstAns;
    }

    return 0;

}

//////交易函数/////
int  TTrdItf_DDABOSS::Order()
{
    if (FFix == NULL) return -1;

    char buffer[512];
    char temp[20];
		int  nResult;


		if (FRequest.Order.Type == otETFSub ||
				FRequest.Order.Type == otETFRed )
    {
        FDll.FixCreate(FFix, FUNC_JY_ETFSGSH);
        FDll.FixSet(FFix, FID_KHH , FKHH);
				FDll.FixSet(FFix, FID_JYS , ConvertMarketType(FRequest.Order.Market));
				FDll.FixSet(FFix, FID_GDH , GetStockAccountByMarket(FRequest.Order.Market));
				FDll.FixSet(FFix, FID_JYLB, ConvertOrderType(FRequest.Order.Type)/*"29"*/);
				FDll.FixSet(FFix, FID_ZQDM, FRequest.Order.SecuID);
				FDll.FixSet(FFix, FID_WTFS, FSet.pWtfs);
				FDll.FixSetInt(FFix, FID_WTSL, FRequest.Order.Num);
		}
    else
		{
        FDll.FixCreate(FFix, FUNC_JY_MMWT);
        FDll.FixSet(FFix, FID_KHH , FKHH);
				FDll.FixSet(FFix, FID_JYS , ConvertMarketType(FRequest.Order.Market));
				FDll.FixSet(FFix, FID_GDH , GetStockAccountByMarket(FRequest.Order.Market));
				FDll.FixSet(FFix, FID_JYLB, ConvertOrderType(FRequest.Order.Type)/*"1"*/);
				FDll.FixSet(FFix, FID_ZQDM, FRequest.Order.SecuID);
				FDll.FixSet(FFix, FID_JYMM, FAccInfo.PW);
        FDll.FixSet(FFix, FID_WTFS, FSet.pWtfs);
        FDll.FixSet(FFix, FID_JMLX, "0");
				FDll.FixSetDouble(FFix, FID_WTJG, FRequest.Order.Price);
        FDll.FixSetInt(FFix, FID_WTSL, FRequest.Order.Num);
    }

		if (FDll.FixWrite(FFix) < 0){SetError(); return -2;}
    if (FDll.FixReadEx(FFix, 1000) <= 0) return -3;

    FDll.FixGetBuffer(FFix, buffer, sizeof(buffer) - 1);
    if (FDll.FixGetInt(FFix, FID_CODE) > 0)
    {
        NewAns(1);
				lstrcpyn((*FAnswer)[0].Order.ContractID, FDll.FixGet(FFix, FID_WTH, buffer, 0),
						sizeof((*FAnswer)[0].Order.ContractID));
        return 0;
    }
    else
    {
				SetError();
				return FDll.FixGetInt(FFix, FID_CODE);
    }
}

int  TTrdItf_DDABOSS::Undo()
{
    if (FFix == NULL) return -1;

    char buffer[512];
    int  nResult;

    FDll.FixCreate(FFix, FUNC_JY_MMCD);
    FDll.FixSet(FFix, FID_KHH , FKHH);
		FDll.FixSet(FFix, FID_JYS , ConvertMarketType(FRequest.Undo.Market));
		FDll.FixSet(FFix, FID_GDH , GetStockAccountByMarket(FRequest.Undo.Market));
    FDll.FixSet(FFix, FID_WTH,  FRequest.Undo.ContractID);
    FDll.FixSet(FFix, FID_JYMM, FAccInfo.PW);
    FDll.FixSet(FFix, FID_WTFS, FSet.pWtfs);
    FDll.FixSet(FFix, FID_JMLX, "0");
    
		if (FDll.FixWrite(FFix) < 0) {SetError();return -2; }
    if (FDll.FixReadEx(FFix, 1000) <= 0) return -3;

    FDll.FixGetBuffer(FFix, buffer, sizeof(buffer) - 1);
    if (FDll.FixGetInt(FFix, FID_CODE) > 0)
    {
        return 0;
    }
    else
    {
				SetError();
        return FDll.FixGetInt(FFix, FID_CODE);
    }

}

void TTrdItf_DDABOSS::SetError(void)
{
   char buffer[512];
   strcpy(FLastError.Sender,"DDABOSS");
	 FLastError.ErrorCode = FDll.FixGetInt(FFix, FID_CODE);
	 lstrcpyn( FLastError.Text,FDll.FixGet(FFix, FID_MESSAGE, buffer, 0),MAX_TEXT );
	 ODS('M',PLUGINNAME,"ErrCode=%d,%s",FLastError.ErrorCode,FLastError.Text);
}

void TTrdItf_DDABOSS::CloseLink(void)
{
	if(FFix!=NULL) {FDll.FixClose(FFix);  FFix = NULL;};
	TTrdItfBase::CloseLink();
}

market_type  TTrdItf_DDABOSS::ConvertMarketType(const char *t)
{
	if(t==NULL || strlen(t)<2 ) return mtNo;
	if( t[1] == 'H' ) return mtSHA;
	if( t[1] == 'Z' ) return mtSZA;
	ODS('M',PLUGINNAME,"MarketType = %s",t);
	return mtNo;
}

order_type   TTrdItf_DDABOSS::ConvertOrderType(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return otNo;
	if( strcmp(t,"1") == 0 ) return otBuy;
	if( strcmp(t,"2") == 0 ) return otSell;
	if( strcmp(t,"29") == 0 ) return otETFSub;
	if( strcmp(t,"30") == 0 ) return otETFRed;
	ODS('M',PLUGINNAME,"OrderType = %s",t);
	return otNo;
}

order_state  TTrdItf_DDABOSS::ConvertOrderState(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return osno;
	/*
	int state = atoi(t);
	switch (state) {
		case 0:return oswb;
		case 1:return osyb;
		case 2:return osbc;
		case -1:return osbw;
		case -2:return osyc;
	default:
		if( state<-1) return osyf;
		else
		{
			ODS('M',PLUGINNAME,"OrderState = %s",t);
			return osno;
		}
	}
	*/
	//未 申 报,申 报 中,已 申 报,撤消成功,全部成交,部份成交,无效委托
	if( strcmp(t,"未申报") == 0) return oswb;
	if( strcmp(t,"申报中") == 0) return oswb;
	if( strcmp(t,"已申报") == 0) return osyb;
	if( strcmp(t,"部分撤单") == 0) return osbw;
	if( strcmp(t,"全部撤单") == 0) return osyc;
	if( strcmp(t,"全部成交") == 0) return oscj;
	if( strcmp(t,"部份成交") == 0) return osbc;
	if( strcmp(t,"无效委托") == 0) return osyf;
	//无法撤单
	ODS('M',PLUGINNAME,"OrderState = %s",t);
	return osno;
}

pos_direction TTrdItf_DDABOSS::ConvertPosDir(const char *t)
{
	return pdNet;
}

money_type   TTrdItf_DDABOSS::ConvertMoneyType(const char *t)
{
	if(t==NULL || strlen(t)<3 ) return motNo;
	switch (t[0]) {
		case 'R': return motRMB;
		case 'U': return motUSD;
		case 'H': return motHKD;
	default:
		return motNo;
	}
}

char *  TTrdItf_DDABOSS::ConvertMarketType(market_type t)
{
	switch (t) {
		case mtSHA: return "SH" ;
		case mtSZA: return "SZ" ;
	default:
		return "";
	}
}

char *  TTrdItf_DDABOSS::ConvertOrderType(order_type t)
{
	switch (t) {
		case otBuy: return "1";
		case otSell: return "2";
		case otETFSub: return "29";
		case otETFRed: return "30";
	default:
		return "";
	}
}

char *  TTrdItf_DDABOSS::ConvertOrderState(order_state t)
{
	return "";
}

char *  TTrdItf_DDABOSS::ConvertPosDir(pos_direction t)
{
	return "";
}

char *  TTrdItf_DDABOSS::ConvertMoneyType(money_type t)
{
	switch (t) {
		case motRMB: return "RMB";
		case motUSD: return "USD";
		case motHKD: return "HKD";
	default:
		return "";
	}
}

bool TTrdItf_DDABOSS::GetConfig(void)
{
	if( FSetupFile== NULL ) return false;

	TMemIniFile *ini = new TMemIniFile( FSetupFile );
	try
	{
		// 判断是否存在插件的设置，没有的话返回false以便系统能够生成默认的设置
		if( ini->SectionExists(PLUGINNAME) == false ) return false;
		lstrcpyn(FSet.pUser,ini->ReadString(PLUGINNAME,"pUser",FSet.pUser).c_str(),9);
		lstrcpyn(FSet.pWtfs,ini->ReadString(PLUGINNAME,"pWtfs",FSet.pWtfs).c_str(),2);
		lstrcpyn(FSet.pYyb,ini->ReadString(PLUGINNAME,"pYyb",FSet.pYyb).c_str(),9);
		lstrcpyn(FSet.pRight,ini->ReadString(PLUGINNAME,"pRight",FSet.pRight).c_str(),99);
		lstrcpyn(FSet.pDest,ini->ReadString(PLUGINNAME,"pDest",FSet.pDest).c_str(),49);
		lstrcpyn(FSet.pRemote,ini->ReadString(PLUGINNAME,"pRemote",FSet.pRemote).c_str(),99);
	}
	__finally
	{
		delete ini;
	}
	return true;
}

void TTrdItf_DDABOSS::SetConfig(void)
{
	if( FSetupFile== NULL ) return ;

	TMemIniFile *ini = new TMemIniFile( FSetupFile );
	try
	{
		ini->WriteString(PLUGINNAME,"pUser",FSet.pUser);
		ini->WriteString(PLUGINNAME,"pWtfs",FSet.pWtfs);
		ini->WriteString(PLUGINNAME,"pYyb",FSet.pYyb);
		ini->WriteString(PLUGINNAME,"pRight",FSet.pRight);
		ini->WriteString(PLUGINNAME,"pDest",FSet.pDest);
		ini->WriteString(PLUGINNAME,"pemote",FSet.pRemote);
		ini->UpdateFile();
	}
	__finally
	{
  	delete ini;
	}
}
