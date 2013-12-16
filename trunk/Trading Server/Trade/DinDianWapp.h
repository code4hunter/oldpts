/*
 *  DESC: 顶点中间件动态库函数包装
 *  FILE: DinDianWapp
 *  BY:   CodeHunter
 */

//---------------------------------------------------------------------------
#ifndef DinDianWappH
#define DinDianWappH
//---------------------------------------------------------------------------
#include <windows.h>

#define NOTIMP -1000

class CAPEX3RD
{
private:
  //取数据缓冲区的一条记录
  typedef char * WINAPI(* FQAGetRow)( char *pData,int nIndex,char *pBuff,int nMaxSize );
  //取记录中的一个域
  typedef char * WINAPI(* FQAGetString)( char *pData,int nIndex,char *pBuff,int nMaxSize );
  //初始化,设置基本参数
  typedef BOOL WINAPI(* FApex3rdInit)( const char *pUser,const char *pWtfs,const char *pYyb,const char *pRight );
  //设置远程营业部
  typedef BOOL WINAPI(* FApexSetDestYYB)( int nYYB );
  //程序退出
  typedef void WINAPI(* FApex3rdExit)();
  //打开连接
  typedef void * WINAPI(* FApexOpenLink)( const char *pDest,char *pRemote );
  //关闭连接
  typedef void WINAPI(* FApexCloseLink)( void *pACI );
  //取上次操作返回信息
  typedef int WINAPI(* FGetLastErrMsg)( void *pACI,char *buffer);
  //资金号确认
  typedef int WINAPI(* Fcheck_zjzh)( char *pZjzh, char *pPwd, void *pACI );
  //取资金信息
  typedef int WINAPI(* Fread_zjxx)( char *pZjzh,char *pBz,char **pOut,void *pACI);
  //买入委托
  typedef int WINAPI(* Ftrade_buy)( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
  //卖出委托
  typedef int WINAPI(* Ftrade_sale)( char *pZjzh,char *pJys,char *pGdzh, char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
  //委托撤单
  typedef int WINAPI(* Ftrade_abort)( char *pZjzh,char *pJys,char *pGdzh,char *pPwd,char *pHth,void *pACI);
  //批量撒单
  typedef int WINAPI(* Ftrade_abort_batch)( char *pZjzh,char *pJys,char *pGdzh,char *pPwd,char *pZqdm,void *pACI);
  //批量买入
  typedef int WINAPI(* Ftrade_buy_batch)( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm, float nWtjg, long nWtzl,long nWtsl, char *pPwd, void *pACI);
  //批量卖出
  typedef int WINAPI(* Ftrade_sale_batch)( char *pZjzh,char *pJys,char *pGdzh, char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
  //当日委托查询
  typedef int WINAPI(* Fread_wt_zjzh)( char *pZjzh,char *pJys,char **pOut,void *pACI );
  //历史委托查询
  typedef int WINAPI(* Fread_lswt_zjzh)( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
  //按资金号查询股票余额
  typedef int WINAPI(* Fread_gp_zjzh)( char *pZjzh,char *pJys,char **pOut,void *pACI );
  //按证券代码查询股票余额(计算可卖数量)
  typedef int WINAPI(* Fread_gp_zqdm)( char *pGdzh,char *pJys,char *pZqdm,char **pOut,void *pACI );
  //计算可买数量
  typedef int WINAPI(* Fread_kmrsl)( char *pZjzh,char *pJys,char *pZqdm,double nWtjg,void *pACI,char *pGdh);
  //当日成交查询
  typedef int WINAPI(* Fread_drcj_zjzh)( char *pZjzh,char *pJys,char **pOut,void *pACI );
  //当日成交明细查询
  typedef int WINAPI(* Fread_drcj_hth)( char *pGdzh,char *pJys,char *pHth,char **pOut,void *pACI );
  //历史成交查询
  typedef int WINAPI(* Fread_lscj_zjzh)( char *pZjzh,char *pJys,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
  //历史成交查询(广发) 2001.05.18
  typedef int WINAPI(* Fread_gfcj_zjzh)( char *pZjzh,char *pKsrq,char *pJsrq,char *pBZ,char **pOut,void *pACI );
  //查询资金流水(资金明细)
  typedef int WINAPI(* Fread_zjls)( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
  //检查股民密码
  typedef int WINAPI(* Fcheckaccpass)( char *pKhdm,char *pStyle,char *pJys,char *pZhmm,int nType,void *pACI );
  //当日委托查询按zjzh,gdzh,hth组合
  typedef int WINAPI(* Frequestentrust)( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char **pOut,void *pACI );
  //当日成交查询按zjzh,gdzh,hth组合
  typedef int WINAPI(* Fentrustresult)( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char **pOut,void *pACI );
  //历史成交查询按zjzh,gdzh,wth组合
  typedef int WINAPI(* Frequestbusiness)( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
  //查询股票,按zjzh,gdzh,zqdm组合
  typedef int WINAPI(* Frequeststock)( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm,char **pOut,void *pACI );
  //设置参数
  typedef int WINAPI(* FApex3rdSetPara)( char *pUser,char *pWtfs,char *pYyb,char *pNode );
  //历史委托查询按zjzh,gdzh,hth组合
  typedef int WINAPI(* Frequesthistentrust)( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
  //查询资金帐户客户信息
  typedef int WINAPI(* Frequestaccinfo)( char *pZjzh,void *pACI );
  //股东号确认
  typedef int WINAPI(* Fcheck_gdzh)(char *pGdzh, char *pJys, char *pPwd, void *pACI );
  //查询股东号
  typedef int WINAPI(* Fread_gdzh)(char *pZjzh,char *pJys,char **pOut,void *pACI );
  typedef int WINAPI(* Fetf_sgsh)(char *pJYS,char *pGDH,char *pZQDM,long nWTSL,double dWTJG,char *pZJZH,char *pPwd, void *pACI);

  FQAGetRow               m_QAGetRow              ;       
  FQAGetString            m_QAGetString           ;
  FApex3rdInit            m_Apex3rdInit           ;
  FApexSetDestYYB         m_ApexSetDestYYB        ;
  FApex3rdExit            m_Apex3rdExit           ;
  FApexOpenLink           m_ApexOpenLink          ;
  FApexCloseLink          m_ApexCloseLink         ;
  FGetLastErrMsg          m_GetLastErrMsg         ;
  Fcheck_zjzh             m_check_zjzh            ;
  Fread_zjxx              m_read_zjxx             ;
  Ftrade_buy              m_trade_buy             ;
  Ftrade_sale             m_trade_sale            ;
  Ftrade_abort            m_trade_abort           ;
  Ftrade_abort_batch      m_trade_abort_batch     ;
  Ftrade_buy_batch        m_trade_buy_batch       ;
  Ftrade_sale_batch       m_trade_sale_batch      ;
  Fread_wt_zjzh           m_read_wt_zjzh          ;
  Fread_lswt_zjzh         m_read_lswt_zjzh        ;
  Fread_gp_zjzh           m_read_gp_zjzh          ;
  Fread_gp_zqdm           m_read_gp_zqdm          ;
  Fread_kmrsl             m_read_kmrsl            ;
  Fread_drcj_zjzh         m_read_drcj_zjzh        ;
  Fread_drcj_hth          m_read_drcj_hth         ;
  Fread_lscj_zjzh         m_read_lscj_zjzh        ;
  Fread_gfcj_zjzh         m_read_gfcj_zjzh        ;
  Fread_zjls              m_read_zjls             ;
  Fcheckaccpass           m_checkaccpass          ;
  Frequestentrust         m_requestentrust        ;
  Fentrustresult          m_entrustresult         ;
  Frequestbusiness        m_requestbusiness       ;
  Frequeststock           m_requeststock          ;
  FApex3rdSetPara         m_Apex3rdSetPara        ;
  Frequesthistentrust     m_requesthistentrust    ;
  Frequestaccinfo         m_requestaccinfo        ;
  Fcheck_gdzh             m_check_gdzh            ;
  Fread_gdzh              m_read_gdzh             ;
  Fetf_sgsh               m_etf_sgsh              ;
  HINSTANCE  FDllHandle;

  bool bLoaded;
public:
  CAPEX3RD();
  ~CAPEX3RD();

  char * QAGetRow( char *pData,int nIndex,char *pBuff,int nMaxSize ) ;
  char * QAGetString( char *pData,int nIndex,char *pBuff,int nMaxSize ) ;
  BOOL Apex3rdInit( const char *pUser,const char *pWtfs,const char *pYyb,const char *pRight ) ;
  BOOL ApexSetDestYYB( int nYYB );
  void Apex3rdExit();
  void * ApexOpenLink( const char *pDest,char *pRemote );
  void ApexCloseLink( void *pACI );
  int GetLastErrMsg( void *pACI,char *buffer);
  int check_zjzh( char *pZjzh, char *pPwd, void *pACI );
  int read_zjxx( char *pZjzh,char *pBz,char **pOut,void *pACI);
  int trade_buy( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
  int trade_sale( char *pZjzh,char *pJys,char *pGdzh, char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
  int trade_abort( char *pZjzh,char *pJys,char *pGdzh,char *pPwd,char *pHth,void *pACI);
  int trade_abort_batch( char *pZjzh,char *pJys,char *pGdzh,char *pPwd,char *pZqdm,void *pACI);
  int trade_buy_batch( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm, float nWtjg, long nWtzl,long nWtsl, char *pPwd, void *pACI) ;
  int trade_sale_batch( char *pZjzh,char *pJys,char *pGdzh, char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
  int read_wt_zjzh( char *pZjzh,char *pJys,char **pOut,void *pACI ) ;
  int read_lswt_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI ) ;
  int read_gp_zjzh( char *pZjzh,char *pJys,char **pOut,void *pACI ) ;
  int read_gp_zqdm( char *pGdzh,char *pJys,char *pZqdm,char **pOut,void *pACI ) ;
  int read_kmrsl( char *pZjzh,char *pJys,char *pZqdm,double nWtjg,void *pACI,char *pGdh) ;
  int read_drcj_zjzh( char *pZjzh,char *pJys,char **pOut,void *pACI );
  int read_drcj_hth( char *pGdzh,char *pJys,char *pHth,char **pOut,void *pACI );
  int read_lscj_zjzh( char *pZjzh,char *pJys,char *pKsrq,char *pJsrq,char **pOut,void *pACI ) ;
  int read_gfcj_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char *pBZ,char **pOut,void *pACI ) ;
  int read_zjls( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI ) ;
  int checkaccpass( char *pKhdm,char *pStyle,char *pJys,char *pZhmm,int nType,void *pACI );
  int requestentrust( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char **pOut,void *pACI ) ;
  int entrustresult( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char **pOut,void *pACI );
  int requestbusiness( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char *pKsrq,char *pJsrq,char **pOut,void *pACI ) ;
  int requeststock( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm,char **pOut,void *pACI )  ;
  int Apex3rdSetPara( char *pUser,char *pWtfs,char *pYyb,char *pNode );
  int requesthistentrust( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
  int requestaccinfo( char *pZjzh,void *pACI )  ;
  int check_gdzh(char *pGdzh, char *pJys, char *pPwd, void *pACI );
  int read_gdzh(char *pZjzh,char *pJys,char **pOut,void *pACI );
  int etf_sgsh(char *pJYS,char *pGDH,char *pZQDM,long nWTSL,double dWTJG,char *pZJZH,char *pPwd, void *pACI);
};

#endif
