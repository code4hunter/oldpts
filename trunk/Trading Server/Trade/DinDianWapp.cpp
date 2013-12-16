/*
 *  DESC: 顶点中间件动态库函数包装
 *  FILE: DinDianWapp
 *  BY:   CodeHunter
 */

//---------------------------------------------------------------------------
#include "DinDianWapp.h"
#include "..\..\common\BHCmnBase\DebugStr.h"
//---------------------------------------------------------------------------
CAPEX3RD::CAPEX3RD()
{
  m_QAGetRow            =NULL ;
  m_QAGetString         =NULL ;
  m_Apex3rdInit         =NULL ;
  m_ApexSetDestYYB      =NULL ;
  m_Apex3rdExit         =NULL ;
  m_ApexOpenLink        =NULL ;
  m_ApexCloseLink       =NULL ;
  m_GetLastErrMsg       =NULL ;
  m_check_zjzh          =NULL ;
  m_read_zjxx           =NULL ;
  m_trade_buy           =NULL ;
  m_trade_sale          =NULL ; 
  m_trade_abort         =NULL ;
  m_trade_abort_batch   =NULL ;
  m_trade_buy_batch     =NULL ; 
  m_trade_sale_batch    =NULL ;
  m_read_wt_zjzh        =NULL ;
  m_read_lswt_zjzh      =NULL ; 
  m_read_gp_zjzh        =NULL ;
  m_read_gp_zqdm        =NULL ; 
  m_read_kmrsl          =NULL ;
  m_read_drcj_zjzh      =NULL ;
  m_read_drcj_hth       =NULL ; 
  m_read_lscj_zjzh      =NULL ;
  m_read_gfcj_zjzh      =NULL ; 
  m_read_zjls           =NULL ;
  m_checkaccpass        =NULL ; 
  m_requestentrust      =NULL ;
  m_entrustresult       =NULL ; 
  m_requestbusiness     =NULL ;
  m_requeststock        =NULL ;
  m_Apex3rdSetPara      =NULL ;
  m_requesthistentrust  =NULL ;
  m_requestaccinfo      =NULL ;
  m_check_gdzh          =NULL ;
  m_read_gdzh           =NULL ;
  m_etf_sgsh            =NULL ;

  FDllHandle = LoadLibrary("APEX3RD.dll");

  if(!FDllHandle)
  {
    MessageBox(NULL,"导入动态链接库\"APEX3RD.dll\"失败！将退出应用程序。","ERROR!",MB_ICONERROR);
    return;
  }
  else
  {
    m_QAGetRow           = (FQAGetRow          )GetProcAddress( FDllHandle,"QAGetRow");
    m_QAGetString        = (FQAGetString       )GetProcAddress( FDllHandle,"QAGetString");
    m_Apex3rdInit        = (FApex3rdInit       )GetProcAddress( FDllHandle,"Apex3rdInit");
    m_ApexSetDestYYB     = (FApexSetDestYYB    )GetProcAddress( FDllHandle,"ApexSetDestYYB");
    m_Apex3rdExit        = (FApex3rdExit       )GetProcAddress( FDllHandle,"Apex3rdExit");
    m_ApexOpenLink       = (FApexOpenLink      )GetProcAddress( FDllHandle,"ApexOpenLink");
    m_ApexCloseLink      = (FApexCloseLink     )GetProcAddress( FDllHandle,"ApexCloseLink");
    m_GetLastErrMsg      = (FGetLastErrMsg     )GetProcAddress( FDllHandle,"GetLastErrMsg");
    m_check_zjzh         = (Fcheck_zjzh        )GetProcAddress( FDllHandle,"check_zjzh");
    m_read_zjxx          = (Fread_zjxx         )GetProcAddress( FDllHandle,"read_zjxx");
    m_trade_buy          = (Ftrade_buy         )GetProcAddress( FDllHandle,"trade_buy");
    m_trade_sale         = (Ftrade_sale        )GetProcAddress( FDllHandle,"trade_sale");
    m_trade_abort        = (Ftrade_abort       )GetProcAddress( FDllHandle,"trade_abort");
    m_trade_abort_batch  = (Ftrade_abort_batch )GetProcAddress( FDllHandle,"trade_abort_batch");
    m_trade_buy_batch    = (Ftrade_buy_batch   )GetProcAddress( FDllHandle,"trade_buy_batch");
    m_trade_sale_batch   = (Ftrade_sale_batch  )GetProcAddress( FDllHandle,"trade_sale_batch");
    m_read_wt_zjzh       = (Fread_wt_zjzh      )GetProcAddress( FDllHandle,"read_wt_zjzh");
    m_read_lswt_zjzh     = (Fread_lswt_zjzh    )GetProcAddress( FDllHandle,"read_lswt_zjzh");
    m_read_gp_zjzh       = (Fread_gp_zjzh      )GetProcAddress( FDllHandle,"read_gp_zjzh");
    m_read_gp_zqdm       = (Fread_gp_zqdm      )GetProcAddress( FDllHandle,"read_gp_zqdm");
    m_read_kmrsl         = (Fread_kmrsl        )GetProcAddress( FDllHandle,"read_kmrsl");
    m_read_drcj_zjzh     = (Fread_drcj_zjzh    )GetProcAddress( FDllHandle,"read_drcj_zjzh");
    m_read_drcj_hth      = (Fread_drcj_hth     )GetProcAddress( FDllHandle,"read_drcj_hth");
    m_read_lscj_zjzh     = (Fread_lscj_zjzh    )GetProcAddress( FDllHandle,"read_lscj_zjzh");
    m_read_gfcj_zjzh     = (Fread_gfcj_zjzh    )GetProcAddress( FDllHandle,"read_gfcj_zjzh");
    m_read_zjls          = (Fread_zjls         )GetProcAddress( FDllHandle,"read_zjls");
    m_checkaccpass       = (Fcheckaccpass      )GetProcAddress( FDllHandle,"checkaccpass");
    m_requestentrust     = (Frequestentrust    )GetProcAddress( FDllHandle,"requestentrust");
    m_entrustresult      = (Fentrustresult     )GetProcAddress( FDllHandle,"entrustresult");
    m_requestbusiness    = (Frequestbusiness   )GetProcAddress( FDllHandle,"requestbusiness");
    m_requeststock       = (Frequeststock      )GetProcAddress( FDllHandle,"requeststock");
    m_Apex3rdSetPara     = (FApex3rdSetPara    )GetProcAddress( FDllHandle,"Apex3rdSetPara");
    m_requesthistentrust = (Frequesthistentrust)GetProcAddress( FDllHandle,"requesthistentrust");
    m_requestaccinfo     = (Frequestaccinfo    )GetProcAddress( FDllHandle,"requestaccinfo");
    m_check_gdzh         = (Fcheck_gdzh        )GetProcAddress( FDllHandle,"check_gdzh");
    m_read_gdzh          = (Fread_gdzh         )GetProcAddress( FDllHandle,"read_gdzh");
    m_etf_sgsh           = (Fetf_sgsh          )GetProcAddress( FDllHandle,"etf_sgsh");

    if( !(m_QAGetRow          ||
          m_QAGetString       ||
          m_Apex3rdInit       ||
          m_ApexSetDestYYB    ||
          m_Apex3rdExit       ||
          m_ApexOpenLink      ||
          m_ApexCloseLink     ||
          m_GetLastErrMsg     ||
          m_check_zjzh        ||
          m_read_zjxx         ||
          m_trade_buy         ||
          m_trade_sale        ||
          m_trade_abort       ||
          m_trade_abort_batch ||
          m_trade_buy_batch   ||
          m_trade_sale_batch  ||
          m_read_wt_zjzh      ||
          m_read_lswt_zjzh    ||
          m_read_gp_zjzh      ||
          m_read_gp_zqdm      ||
          m_read_kmrsl        ||
          m_read_drcj_zjzh    ||
          m_read_drcj_hth     ||
          m_read_lscj_zjzh    ||
          m_read_gfcj_zjzh    ||
          m_read_zjls         ||
          m_checkaccpass      ||
          m_requestentrust    ||
          m_entrustresult     ||
          m_requestbusiness   ||
          m_requeststock      ||
          m_Apex3rdSetPara    ||
          m_requesthistentrust||
          m_requestaccinfo    ||
          m_check_gdzh        ||
          m_read_gdzh         ||
          m_etf_sgsh
          ))
    {
      bLoaded=false;
      MessageBox(NULL,"动态链接库中某些函数不存在！","ERROR!",MB_ICONERROR);
    }
    else bLoaded=true;
  }
}

CAPEX3RD::~CAPEX3RD()
{
  if(FDllHandle)
    FreeLibrary(FDllHandle);
}

char * CAPEX3RD::QAGetRow( char *pData,int nIndex,char *pBuff,int nMaxSize )
{
  if(m_QAGetRow)
    return m_QAGetRow(pData,nIndex,pBuff,nMaxSize);
  else
    return "";
}

char * CAPEX3RD::QAGetString( char *pData,int nIndex,char *pBuff,int nMaxSize )
{
  if(m_QAGetString)
    return m_QAGetString( pData,nIndex,pBuff,nMaxSize );
  else
    return "";
}

BOOL CAPEX3RD::Apex3rdInit( const char *pUser,const char *pWtfs,const char *pYyb,const char *pRight )
{
  if(m_Apex3rdInit)
    return m_Apex3rdInit( pUser,pWtfs,pYyb,pRight ) ;
  else
    return FALSE;
}

BOOL CAPEX3RD::ApexSetDestYYB( int nYYB )
{
  if(m_ApexSetDestYYB)
    return  m_ApexSetDestYYB(nYYB);
  else
    return FALSE;
}

void CAPEX3RD::Apex3rdExit()
{
  if(m_Apex3rdExit) m_Apex3rdExit();
}

void * CAPEX3RD::ApexOpenLink( const char *pDest,char *pRemote )
{
  if(m_ApexOpenLink)
    return m_ApexOpenLink( pDest,pRemote );
  else
    return NULL;
}

void CAPEX3RD::ApexCloseLink( void *pACI )
{
  if(m_ApexCloseLink)
    m_ApexCloseLink(pACI);
}

int CAPEX3RD::GetLastErrMsg( void *pACI,char *buffer)
{
  if(m_GetLastErrMsg)
    return m_GetLastErrMsg( pACI,buffer);
  else
    return NOTIMP;
}

int CAPEX3RD::check_zjzh( char *pZjzh, char *pPwd, void *pACI )
{
  if(m_check_zjzh)
#ifdef _DEBUG
  {
    int ret=m_check_zjzh( pZjzh, pPwd, pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_check_zjzh( pZjzh, pPwd, pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::read_zjxx( char *pZjzh,char *pBz,char **pOut,void *pACI)
{
  if(m_read_zjxx)
#ifdef _DEBUG
  {
    int ret=m_read_zjxx( pZjzh,pBz,pOut,pACI);
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_read_zjxx( pZjzh,pBz,pOut,pACI);
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::trade_buy( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI)
{
  if(m_trade_buy)
#ifdef _DEBUG
  {
    int ret=m_trade_buy( pZjzh,pJys,pGdzh,pZqdm, nWtjg, nWtsl, pPwd, pACI);
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_trade_buy( pZjzh,pJys,pGdzh,pZqdm, nWtjg, nWtsl, pPwd, pACI);
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::trade_sale( char *pZjzh,char *pJys,char *pGdzh, char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI)
{
  if(m_trade_sale)
#ifdef _DEBUG
  {
    int ret=m_trade_sale( pZjzh,pJys,pGdzh, pZqdm,  nWtjg,nWtsl, pPwd, pACI);
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_trade_sale( pZjzh,pJys,pGdzh, pZqdm,  nWtjg,nWtsl, pPwd, pACI);
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::trade_abort( char *pZjzh,char *pJys,char *pGdzh,char *pPwd,char *pHth,void *pACI)
{
  if(m_trade_abort)
#ifdef _DEBUG
  {
    int ret=m_trade_abort( pZjzh,pJys,pGdzh,pPwd,pHth,pACI);
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_trade_abort( pZjzh,pJys,pGdzh,pPwd,pHth,pACI);
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::trade_abort_batch( char *pZjzh,char *pJys,char *pGdzh,char *pPwd,char *pZqdm,void *pACI)
{
  if(m_trade_abort_batch)
#ifdef _DEBUG
  {
    int ret=m_trade_abort_batch( pZjzh,pJys,pGdzh,pPwd,pZqdm,pACI);
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_trade_abort_batch( pZjzh,pJys,pGdzh,pPwd,pZqdm,pACI);
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::trade_buy_batch( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm, float nWtjg, long nWtzl,long nWtsl, char *pPwd, void *pACI)
{
  if(m_trade_buy_batch)
#ifdef _DEBUG
  {
    int ret=m_trade_buy_batch( pZjzh,pJys,pGdzh,pZqdm,nWtjg, nWtzl,nWtsl, pPwd, pACI);
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_trade_buy_batch( pZjzh,pJys,pGdzh,pZqdm,nWtjg, nWtzl,nWtsl, pPwd, pACI);
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::trade_sale_batch( char *pZjzh,char *pJys,char *pGdzh, char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI)
{
  if(m_trade_sale_batch)
#ifdef _DEBUG
  {
    int ret=m_trade_sale_batch( pZjzh,pJys,pGdzh, pZqdm, nWtjg, nWtsl, pPwd, pACI);
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_trade_sale_batch( pZjzh,pJys,pGdzh, pZqdm, nWtjg, nWtsl, pPwd, pACI);
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::read_wt_zjzh( char *pZjzh,char *pJys,char **pOut,void *pACI )
{
  if(m_read_wt_zjzh)
#ifdef _DEBUG
  {
    int ret=m_read_wt_zjzh( pZjzh,pJys,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_read_wt_zjzh( pZjzh,pJys,pOut,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::read_lswt_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI )
{
  if(m_read_lswt_zjzh)
#ifdef _DEBUG
  {
    int ret=m_read_lswt_zjzh( pZjzh,pKsrq,pJsrq,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_read_lswt_zjzh( pZjzh,pKsrq,pJsrq,pOut,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::read_gp_zjzh( char *pZjzh,char *pJys,char **pOut,void *pACI )
{
  if(m_read_gp_zjzh)
#ifdef _DEBUG
  {
    int ret=m_read_gp_zjzh( pZjzh,pJys,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_read_gp_zjzh( pZjzh,pJys,pOut,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::read_gp_zqdm( char *pGdzh,char *pJys,char *pZqdm,char **pOut,void *pACI )
{
  if(m_read_gp_zqdm)
#ifdef _DEBUG
  {
    int ret=m_read_gp_zqdm( pGdzh,pJys,pZqdm,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_read_gp_zqdm( pGdzh,pJys,pZqdm,pOut,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::read_kmrsl( char *pZjzh,char *pJys,char *pZqdm,double nWtjg,void *pACI,char *pGdh)
{
  if(m_read_kmrsl)
#ifdef _DEBUG
  {
    int ret=m_read_kmrsl( pZjzh,pJys,pZqdm,nWtjg,pACI,pGdh);
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_read_kmrsl( pZjzh,pJys,pZqdm,nWtjg,pACI,pGdh);
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::read_drcj_zjzh( char *pZjzh,char *pJys,char **pOut,void *pACI )
{
  if(m_read_drcj_zjzh)
#ifdef _DEBUG
  {
    int ret=m_read_drcj_zjzh( pZjzh,pJys,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_read_drcj_zjzh( pZjzh,pJys,pOut,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::read_drcj_hth( char *pGdzh,char *pJys,char *pHth,char **pOut,void *pACI )
{ 
  if(m_read_drcj_hth)
#ifdef _DEBUG
  {
    int ret=m_read_drcj_hth( pGdzh,pJys,pHth,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_read_drcj_hth( pGdzh,pJys,pHth,pOut,pACI );
#endif
  else
    return NOTIMP;
}
  
int CAPEX3RD::read_lscj_zjzh( char *pZjzh,char *pJys,char *pKsrq,char *pJsrq,char **pOut,void *pACI )
{
  if(m_read_lscj_zjzh)
#ifdef _DEBUG
  {
    int ret=m_read_lscj_zjzh( pZjzh,pJys,pKsrq,pJsrq,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_read_lscj_zjzh( pZjzh,pJys,pKsrq,pJsrq,pOut,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::read_gfcj_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char *pBZ,char **pOut,void *pACI )
{
  if(m_read_gfcj_zjzh)
#ifdef _DEBUG
  {
    int ret=m_read_gfcj_zjzh( pZjzh,pKsrq,pJsrq,pBZ,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_read_gfcj_zjzh( pZjzh,pKsrq,pJsrq,pBZ,pOut,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::read_zjls( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI )
{
  if(m_read_zjls)
#ifdef _DEBUG
  {
    int ret=m_read_zjls( pZjzh,pKsrq,pJsrq,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_read_zjls( pZjzh,pKsrq,pJsrq,pOut,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::checkaccpass( char *pKhdm,char *pStyle,char *pJys,char *pZhmm,int nType,void *pACI )
{
  if(m_checkaccpass)
#ifdef _DEBUG
  {
    int ret=m_checkaccpass( pKhdm,pStyle,pJys,pZhmm,nType,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_checkaccpass( pKhdm,pStyle,pJys,pZhmm,nType,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::requestentrust( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char **pOut,void *pACI )
{
  if(m_requestentrust)
#ifdef _DEBUG
  {
    int ret=m_requestentrust( pZjzh,pJys,pGdzh,pHth,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_requestentrust( pZjzh,pJys,pGdzh,pHth,pOut,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::entrustresult( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char **pOut,void *pACI )
{
  if(m_entrustresult)
#ifdef _DEBUG
  {
    int ret=m_entrustresult( pZjzh,pJys,pGdzh,pHth,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_entrustresult( pZjzh,pJys,pGdzh,pHth,pOut,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::requestbusiness( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char *pKsrq,char *pJsrq,char **pOut,void *pACI )
{
  if(m_requestbusiness)
#ifdef _DEBUG
  {
    int ret=m_requestbusiness( pZjzh,pJys,pGdzh,pHth,pKsrq,pJsrq,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_requestbusiness( pZjzh,pJys,pGdzh,pHth,pKsrq,pJsrq,pOut,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::requeststock( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm,char **pOut,void *pACI )
{
  if(m_requeststock)
#ifdef _DEBUG
  {
    int ret=m_requeststock(pZjzh,pJys,pGdzh,pZqdm,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_requeststock(pZjzh,pJys,pGdzh,pZqdm,pOut,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::Apex3rdSetPara( char *pUser,char *pWtfs,char *pYyb,char *pNode )
{
  if(m_Apex3rdSetPara)
    return m_Apex3rdSetPara( pUser,pWtfs,pYyb,pNode );
  else
    return NOTIMP;
}

int CAPEX3RD::requesthistentrust( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char *pKsrq,char *pJsrq,char **pOut,void *pACI )
{
  if(m_requesthistentrust)
#ifdef _DEBUG
  {
    int ret=m_requesthistentrust( pZjzh,pJys,pGdzh,pHth,pKsrq,pJsrq,pOut,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_requesthistentrust( pZjzh,pJys,pGdzh,pHth,pKsrq,pJsrq,pOut,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::requestaccinfo( char *pZjzh,void *pACI )
{
  if(m_requestaccinfo)
#ifdef _DEBUG
  {
    int ret=m_requestaccinfo( pZjzh,pACI );
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_requestaccinfo( pZjzh,pACI );
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::check_gdzh(char *pGdzh, char *pJys, char *pPwd, void *pACI )
{
  if(m_check_gdzh)
#ifdef _DEBUG
  {
    int ret=m_check_gdzh(pGdzh,pJys,pPwd,pACI);
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_check_gdzh(pGdzh,pJys,pPwd,pACI);
#endif
  else
    return NOTIMP;
}

int CAPEX3RD::read_gdzh(char *pZjzh,char *pJys,char **pOut,void *pACI )
{
  if(m_read_gdzh)
#ifdef _DEBUG
  {
    int ret=m_read_gdzh(pZjzh,pJys,pOut,pACI);
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_read_gdzh(pZjzh,pJys,pOut,pACI);
#endif
  else
    return NOTIMP;
}

//nWTSL >0 代表申购，小于0 代表赎回
int CAPEX3RD::etf_sgsh(char *pJYS,char *pGDH,char *pZQDM,long nWTSL,
                       double dWTJG,char *pZJZH,char *pPwd, void *pACI)
{
  if(m_etf_sgsh)
#ifdef _DEBUG
  {
    int ret=m_etf_sgsh(pJYS,pGDH,pZQDM, nWTSL,dWTJG,pZJZH,pPwd, pACI);
    if(ret<0)
    {
        char msg[255];
        GetLastErrMsg(pACI,msg);
        ODS(msg);
    }

    return ret;
  }
#else
    return m_etf_sgsh(pJYS,pGDH,pZQDM, nWTSL,dWTJG,pZJZH,pPwd, pACI);
#endif
  else
    return NOTIMP;
}
