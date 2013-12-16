/*
 *  DESC: �����м����̬�⺯����װ
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
  //ȡ���ݻ�������һ����¼
  typedef char * WINAPI(* FQAGetRow)( char *pData,int nIndex,char *pBuff,int nMaxSize );
  //ȡ��¼�е�һ����
  typedef char * WINAPI(* FQAGetString)( char *pData,int nIndex,char *pBuff,int nMaxSize );
  //��ʼ��,���û�������
  typedef BOOL WINAPI(* FApex3rdInit)( const char *pUser,const char *pWtfs,const char *pYyb,const char *pRight );
  //����Զ��Ӫҵ��
  typedef BOOL WINAPI(* FApexSetDestYYB)( int nYYB );
  //�����˳�
  typedef void WINAPI(* FApex3rdExit)();
  //������
  typedef void * WINAPI(* FApexOpenLink)( const char *pDest,char *pRemote );
  //�ر�����
  typedef void WINAPI(* FApexCloseLink)( void *pACI );
  //ȡ�ϴβ���������Ϣ
  typedef int WINAPI(* FGetLastErrMsg)( void *pACI,char *buffer);
  //�ʽ��ȷ��
  typedef int WINAPI(* Fcheck_zjzh)( char *pZjzh, char *pPwd, void *pACI );
  //ȡ�ʽ���Ϣ
  typedef int WINAPI(* Fread_zjxx)( char *pZjzh,char *pBz,char **pOut,void *pACI);
  //����ί��
  typedef int WINAPI(* Ftrade_buy)( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
  //����ί��
  typedef int WINAPI(* Ftrade_sale)( char *pZjzh,char *pJys,char *pGdzh, char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
  //ί�г���
  typedef int WINAPI(* Ftrade_abort)( char *pZjzh,char *pJys,char *pGdzh,char *pPwd,char *pHth,void *pACI);
  //��������
  typedef int WINAPI(* Ftrade_abort_batch)( char *pZjzh,char *pJys,char *pGdzh,char *pPwd,char *pZqdm,void *pACI);
  //��������
  typedef int WINAPI(* Ftrade_buy_batch)( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm, float nWtjg, long nWtzl,long nWtsl, char *pPwd, void *pACI);
  //��������
  typedef int WINAPI(* Ftrade_sale_batch)( char *pZjzh,char *pJys,char *pGdzh, char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
  //����ί�в�ѯ
  typedef int WINAPI(* Fread_wt_zjzh)( char *pZjzh,char *pJys,char **pOut,void *pACI );
  //��ʷί�в�ѯ
  typedef int WINAPI(* Fread_lswt_zjzh)( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
  //���ʽ�Ų�ѯ��Ʊ���
  typedef int WINAPI(* Fread_gp_zjzh)( char *pZjzh,char *pJys,char **pOut,void *pACI );
  //��֤ȯ�����ѯ��Ʊ���(�����������)
  typedef int WINAPI(* Fread_gp_zqdm)( char *pGdzh,char *pJys,char *pZqdm,char **pOut,void *pACI );
  //�����������
  typedef int WINAPI(* Fread_kmrsl)( char *pZjzh,char *pJys,char *pZqdm,double nWtjg,void *pACI,char *pGdh);
  //���ճɽ���ѯ
  typedef int WINAPI(* Fread_drcj_zjzh)( char *pZjzh,char *pJys,char **pOut,void *pACI );
  //���ճɽ���ϸ��ѯ
  typedef int WINAPI(* Fread_drcj_hth)( char *pGdzh,char *pJys,char *pHth,char **pOut,void *pACI );
  //��ʷ�ɽ���ѯ
  typedef int WINAPI(* Fread_lscj_zjzh)( char *pZjzh,char *pJys,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
  //��ʷ�ɽ���ѯ(�㷢) 2001.05.18
  typedef int WINAPI(* Fread_gfcj_zjzh)( char *pZjzh,char *pKsrq,char *pJsrq,char *pBZ,char **pOut,void *pACI );
  //��ѯ�ʽ���ˮ(�ʽ���ϸ)
  typedef int WINAPI(* Fread_zjls)( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
  //����������
  typedef int WINAPI(* Fcheckaccpass)( char *pKhdm,char *pStyle,char *pJys,char *pZhmm,int nType,void *pACI );
  //����ί�в�ѯ��zjzh,gdzh,hth���
  typedef int WINAPI(* Frequestentrust)( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char **pOut,void *pACI );
  //���ճɽ���ѯ��zjzh,gdzh,hth���
  typedef int WINAPI(* Fentrustresult)( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char **pOut,void *pACI );
  //��ʷ�ɽ���ѯ��zjzh,gdzh,wth���
  typedef int WINAPI(* Frequestbusiness)( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
  //��ѯ��Ʊ,��zjzh,gdzh,zqdm���
  typedef int WINAPI(* Frequeststock)( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm,char **pOut,void *pACI );
  //���ò���
  typedef int WINAPI(* FApex3rdSetPara)( char *pUser,char *pWtfs,char *pYyb,char *pNode );
  //��ʷί�в�ѯ��zjzh,gdzh,hth���
  typedef int WINAPI(* Frequesthistentrust)( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
  //��ѯ�ʽ��ʻ��ͻ���Ϣ
  typedef int WINAPI(* Frequestaccinfo)( char *pZjzh,void *pACI );
  //�ɶ���ȷ��
  typedef int WINAPI(* Fcheck_gdzh)(char *pGdzh, char *pJys, char *pPwd, void *pACI );
  //��ѯ�ɶ���
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
