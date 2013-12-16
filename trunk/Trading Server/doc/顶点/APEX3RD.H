
// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the APEX3RD_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// APEX3RD_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

// This class is exported from the Apex3rd.dll
#ifdef APEX3RD_EXPORTS
#define APEX3RD_API __declspec(dllexport)
#else
#define APEX3RD_API __declspec(dllimport)
#endif

#define	ERROR_CONNECT	-301
//ȡ���ݻ�������һ����¼
APEX3RD_API char * WINAPI QAGetRow( char *pData,int nIndex,char *pBuff,int nMaxSize );
//ȡ��¼�е�һ����
APEX3RD_API char * WINAPI QAGetString( char *pData,int nIndex,char *pBuff,int nMaxSize );
//��ʼ��,���û�������
APEX3RD_API BOOL WINAPI Apex3rdInit(const char *pUser,const char *pWtfs,const char *pYyb,const char *pRight );
//����Զ��Ӫҵ��
APEX3RD_API BOOL WINAPI ApexSetDestYYB( int nYYB,void *pACI );
//�����˳�
APEX3RD_API void WINAPI Apex3rdExit();
//������
APEX3RD_API void * WINAPI ApexOpenLink( const char *pDest,char *pRemote );
//�ر�����
APEX3RD_API void WINAPI ApexCloseLink( void *pACI );
//ȡ�ϴβ���������Ϣ
APEX3RD_API int WINAPI GetLastErrMsg( void *pACI,char *buffer);
//�ʽ��ȷ��
APEX3RD_API int WINAPI check_zjzh(char *pZjzh, char *pPwd, void *pACI );
//�ɶ���ȷ��
APEX3RD_API int WINAPI check_gdzh(char *pGdzh, char *pJys, char *pPwd, void *pACI );

//������ȷ��
APEX3RD_API int WINAPI check_jjr(char *pJjr, char *pPwd, void *pACI );

//��ѯ�����˿ͻ�
APEX3RD_API int WINAPI read_jjrkh(char *pJjr, char **pOut ,void *pACI );

//��ѯ�ɶ���
APEX3RD_API int WINAPI read_gdzh(char *pZjzh,char *pJys,char **pOut,void *pACI );
//ȡ����
APEX3RD_API int WINAPI read_hqinfo( char *pZqdm, char *pJys,char **pOut,void *pACI );
//ȡ�ʽ���Ϣ
APEX3RD_API int WINAPI read_zjxx(char *pZjzh,char *pBz,char **pOut,void *pACI);
//����ί��
APEX3RD_API int WINAPI trade_buy(char *pZjzh,char *pJys,char *pGdzh,char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
//����ί��
APEX3RD_API int WINAPI trade_sale(char *pZjzh,char *pJys,char *pGdzh, char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
//ί�г���
APEX3RD_API int WINAPI trade_abort(char *pZjzh,char *pJys,char *pGdzh,char *pPwd,char *pHth,void *pACI);
//��������
APEX3RD_API int WINAPI trade_abort_batch(char *pZjzh,char *pJys,char *pGdzh,char *pPwd,char *pZqdm,void *pACI);
//��������
APEX3RD_API int WINAPI trade_buy_batch(char *pZjzh,char *pJys,char *pGdzh,char *pZqdm, float nWtjg, long nWtzl,long nWtsl, char *pPwd, void *pACI);
//��������
APEX3RD_API int WINAPI trade_sale_batch(char *pZjzh,char *pJys,char *pGdzh, char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
//����ת�й�
APEX3RD_API int WINAPI trade_szztg(char *pZjzh,
										 char *pGdzh,char *pPwd,
										 char *pZqdm,long nWtsl ,const char *pQSDM, float dSFJE, int nSFFS ,void *pACI);
//nSFFS 0:Ϊ�ֽ��շ�,1:ת���շ�


//����ί�в�ѯ
APEX3RD_API int WINAPI read_wt_zjzh( char *pZjzh,char *pJys,char **pOut,void *pACI );
//��ʷί�в�ѯ
APEX3RD_API int WINAPI read_lswt_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//���ʽ�Ų�ѯ��Ʊ���
APEX3RD_API int WINAPI read_gp_zjzh( char *pZjzh,char *pJys,char **pOut,void *pACI );
//��֤ȯ�����ѯ��Ʊ���(�����������)
APEX3RD_API int WINAPI read_gp_zqdm( char *pGdzh,char *pJys,char *pZqdm,char **pOut,void *pACI );
//��ѯ�¹����
APEX3RD_API int WINAPI read_xgph_zjzh( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//�����������
APEX3RD_API int WINAPI read_kmrsl( char *pZjzh,char *pJys,char *pZqdm,double nWtjg,void *pACI,char *pGdh);
//���ճɽ���ѯ
APEX3RD_API int WINAPI read_drcj_zjzh( char *pZjzh,char *pJys,char **pOut,void *pACI );
//���ճɽ���ϸ��ѯ
APEX3RD_API int WINAPI read_drcj_hth( char *pGdzh,char *pJys,char *pHth,char **pOut,void *pACI );
//��ʷ�ɽ���ѯ
APEX3RD_API int WINAPI read_lscj_zjzh( char *pZjzh,char *pJys,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//�ع������ѯ
APEX3RD_API int WINAPI read_hgjg_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//��ʷ�ɽ���ѯ(�㷢) 2001.05.18
APEX3RD_API int WINAPI read_gfcj_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char *pBZ,char **pOut,void *pACI );
APEX3RD_API int WINAPI read_jgrq(char *pZjzh,void *pACI);
//֤ȯ��ϸ��ѯ
APEX3RD_API int WINAPI read_zqmx_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char *pJys,char *pGdh,char **pOut,void *pACI );

//�޸��ʻ�����(��������)
APEX3RD_API int WINAPI change_password(char *pZjzh,char *pOldPwd,char *pNewPwd,void *pACI);
//�޸��ʽ�����
APEX3RD_API int WINAPI change_zjmm(char *pZjzh,char *pOldPwd,char *pNewPwd,void *pACI);
//����ת��(����ת��֤ȯ)
APEX3RD_API int WINAPI yhzz_yhtozq( char *pZjzh,char *pZjmm,char *pYhdm,char *pYhzh,char *pYhmm,double nZzje,char *pBZ, int nHBLB,void *pACI );
//����ת��(֤ȯת������)
APEX3RD_API int WINAPI yhzz_zqtoyh( char *pZjzh,char *pZjmm,char *pYhdm,char *pYhzh,char *pYhmm,double nZzje,char *pBZ, int nHBLB,void *pACI );
//��������ѯ����
APEX3RD_API int WINAPI yhzz_cx_yhye( char *pZjzh,char *pZjmm,char *pYhdm,char *pYhzh,char *pYhmm,char *pBZ, int nHBLB,void *pACI );
//��ѯ���п���
APEX3RD_API int WINAPI read_yhzh( char *pZjzh,char *pZhmm,char *pYhdm,char **pOut,void *pACI );
APEX3RD_API int WINAPI read_yhzh_bz( char *pZjzh,char *pZhmm,char *pYhdm,char * pBZ,char **pOut,void *pACI );
//����ת����ˮ��ѯ
APEX3RD_API int WINAPI read_yhzz_zjzh( char *pZjzh,char *pZhmm,char **pOut,void *pACI );
//����ת�ʺ�ͬ�Ų�ѯ
APEX3RD_API int WINAPI read_yhzz_hth( char *pZjzh,char *pZhmm,char *pHth,char **pOut,void *pACI );
//��ѯ�ʽ���ˮ(�ʽ���ϸ)
APEX3RD_API int WINAPI read_zjls( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//����������
APEX3RD_API int WINAPI checkaccpass( char *pKhdm,char *pStyle,char *pJys,char *pZhmm,int nType,void *pACI );
//����ί�в�ѯ��zjzh,gdzh,hth���
APEX3RD_API int WINAPI requestentrust( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char **pOut,void *pACI );
//���ճɽ���ѯ��zjzh,gdzh,hth���
APEX3RD_API int WINAPI entrustresult( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char **pOut,void *pACI );
//��ʷ�ɽ���ѯ��zjzh,gdzh,wth���
APEX3RD_API int WINAPI requestbusiness( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//��ѯ��Ʊ,��zjzh,gdzh,zqdm���
APEX3RD_API int WINAPI requeststock( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm,char **pOut,void *pACI );
//���ò���
APEX3RD_API int WINAPI Apex3rdSetPara( char *pUser,char *pWtfs,char *pYyb,char *pNode );
//��ʷί�в�ѯ��zjzh,gdzh,hth���
APEX3RD_API int WINAPI requesthistentrust( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//��ʷί�в�ѯ
APEX3RD_API int WINAPI read_lswt_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//��ѯ�ʽ��ʻ��ͻ���Ϣ
APEX3RD_API int WINAPI requestaccinfo( char *pZjzh,void *pACI );
APEX3RD_API int WINAPI requestaccinfoex( const  char *pZjzh,const char *pMode , const char * sLB,void *pACI );
//����ת��ҵ��
APEX3RD_API int WINAPI transferbusiness( int nStyle,char *pZjzh,char *pZjmm,char *pYhdm,char *pYhzh,char *pYhmm,double nZzje,char *pBz,void *pACI );


//�ʽ��ȡ
APEX3RD_API int WINAPI zjcq(const  char *pZjzh,const char *pZjmm,double dbje,const char * bz,
							const char *ywkm,const char *sqly,const char *sqfs,const char *zy,bool bMMBZ,void *pACI );
//�ʽ����
APEX3RD_API int WINAPI zjcz(const  char *pZjzh,const char *pZjmm,long nPzh,
							const char *sqly,const char *sqfs,const char *zy,void *pACI );

//����
APEX3RD_API int WINAPI zjzh_found( const char *pZjzh,const char *pZhxm,const char * yyb,const char *zhqz,const char *wtfs,
									const char *fwxm,const char* sfzh,const char * dz,const char* dh,const char *jymm,const char * zhmm,
									const char *yhdm,const char *yhzh,const char* bz,	char *pNewZjzh,void *pACI );
//���ֿ���
APEX3RD_API int WINAPI zjzh_found_bz( const char *pZjzh,const char *pZhmm,const char *bz ,void *pACI );
//�ʽ��ʻ��޸�
APEX3RD_API int WINAPI zjzh_modify( const char *pZjzh ,const char *pKHLB,const char *pJYS, const char *pZjmm,const char *pXgxm ,const char  *pOldValue , const char *pNewValue ,bool bModifyType, void *pACI );

//���ʽ�����
APEX3RD_API int WINAPI zjzh_destroy(const  char *pZjzh,const char *pZhmm,void *pACI );
APEX3RD_API int WINAPI zjzh_destroy_request(const  char *pZjzh,const char *pZhmm,	void *pACI );
//�ɶ�����
APEX3RD_API int WINAPI gdh_found( const char *pZjzh,const char *pZhmm,const char * gdzh,const char *gdxm,const char *jys,
								 const char* sfzh,const char * dz,const char* dh,const char *mmlb,long gdzd,void *pACI );
//���ɶ���
APEX3RD_API int WINAPI gdh_destory(const  char *pZjzh,const char *pZhmm,const char * gdzh,const char *jys,void *pACI );

//��ʧ�ɶ��ʺ�
APEX3RD_API int WINAPI gdh_suspend(const char *pZjzh,const char *pZhmm,const char * gdzh,const char *jys,void *pACI);
//��ѯ���йɶ���<����ʧ�ʻ�>
APEX3RD_API int WINAPI read_allgdzh(const char *pZjzh,const char *pZhmm,const char *pJys,char **pOut,void *pACI );
//��ѯ���������ʻ�<��������״̬>
APEX3RD_API int WINAPI read_allyhzh(const char *pZjzh,const char *pZhmm,const char *pYhdm,char **pOut,void *pACI );
//��ѯ�ɶ��ʻ���Ϣ
APEX3RD_API int WINAPI requestgdhinfo(const char *pGdzh ,const char *sJys,void *pACI );
//�޸Ĺɶ��ʻ���Ϣ
APEX3RD_API int WINAPI gdh_modify( const char *pZjzh , const char *pZhmm, const char *pGdzh ,const char *sJys, const char *pXgxm , const char *pOldValue, const char *pNewValue, void *pACI );

//��ҹɶ��ʺ�
APEX3RD_API int WINAPI gdh_resume(const char *pZjzh,const char *pZhmm,const char * gdzh,const char *jys,void *pACI);

//�����ʻ��Ǽ�
APEX3RD_API int WINAPI yhzh_found( const char *pZjzh,const char *pZhmm,const char * pYhdm,const char *pYhzh,double dYwsf, const char *pBz ,void *pACI );
//�����ʻ�ע��
APEX3RD_API int WINAPI yhzh_destory(const char *pZjzh,const char *pZhmm,const char * pYhdm,const char *pYhzh,void *pACI );

//��Աע��
APEX3RD_API int WINAPI user_login(const char *pUser,const char *pPwd,void *pACI);

//���չ�Աҵ���ѯ
APEX3RD_API int WINAPI read_drgyye(const char * pUserName ,const char *pPwd,const char *pBZ ,char **pOut,void *pACI);

//[���۳���] �ʽ��ʻ��µ������۵������Ϣ��ѯ
APEX3RD_API int WINAPI read_czye( const char *pZjzh , const char * pZhmm , void *pACI );
//[���۳���] ��������п����
APEX3RD_API int WINAPI request_czye( const char *pZjzh , const char *pYhzh , const char *pYhdm , const char * pYhmm , const char *pBZ , void *pACI );

//[���۳���] �����ۺŲ�ѯ
APEX3RD_API int WINAPI set_zczh(const char *pZjzh, const char *pZhmm, const char *pYhzh , const char * pYhdm ,void *pACI );

//[���۳���] ��ѯ�ͻ���Ϣ [���������ۿ���] <רΪ���۳���>
APEX3RD_API int WINAPI read_khxx_zczh( const char *pYhzh ,const char *pZhmm, const char * pYhdm , void *pACI );
   //����:�ʽ��ʻ�|Ӫҵ��|Ⱥ��|�ʻ�״̬|ί�з�ʽ|������Ŀ|������Ϣ

//[���۳���] �����������ʻ�
APEX3RD_API int WINAPI set_zczh(const char *pZjzh, const char *pZhmm, const char *pYhzh , const char * pYhdm ,void *pACI );
   //����:   >0�ɹ� ; <0 ʧ��
//ί���շ�
APEX3RD_API int WINAPI send_wtsf(char *pZjzh,char *pJys,char *pZqlb,void *pACI);

//��㱦����
APEX3RD_API int WINAPI whb_cx_ytoz_jypj(const char *pZjzh,const char *pZjmm,const char *pYhdm ,const char *pYhzh,const char *pYhmm,const char *pMcbz,const char *pChbs,const double fMcje,const char *pMrbz,void *pACI );
APEX3RD_API int WINAPI whb_cx_ztoy_jypj(const char *pZjzh,const char *pZjmm,const char *pYhdm ,const char *pYhzh,const char *pYhmm,const char *pMcbz,const char *pChbs,const double fMcje,const char *pMrbz,void *pACI );
APEX3RD_API int WINAPI whb_cx_ztoz_jypj(const char *pZjzh,const char *pZjmm,const char *pYhdm ,const char *pZjzh2,const char *pYhmm,const char *pMcbz,const char *pChbs,const double fMcje,const char *pMrbz,void *pACI );
APEX3RD_API int WINAPI whb_ytoz_jy     (const char *pZjzh,const char *pZjmm,const char *pYhdm ,const char *pYhzh,const char *pYhmm,const char *pMcbz,const char *pChbs,const double fMcje,const char *pMrbz,double fJypj,char * pFlg,void *pACI );
APEX3RD_API int WINAPI whb_ztoy_jy     (const char *pZjzh,const char *pZjmm,const char *pYhdm ,const char *pYhzh,const char *pYhmm,const char *pMcbz,const char *pChbs,const double fMcje,const char *pMrbz,double fJypj,char * pFlg,void *pACI );
APEX3RD_API int WINAPI whb_ztoz_jy     (const char *pZjzh,const char *pZjmm,const char *pYhdm ,const char *pZjzh2,const char *pYhmm,const char *pMcbz,const char *pChbs,const double fMcje,const char *pMrbz,double fJypj,char * pFlg,void *pACI );
APEX3RD_API int WINAPI whb_zjzh_jyls   (const char *pZjzh,const char *pZhmm,const char *pYhdm ,char **pOut,void *pACI );
APEX3RD_API int WINAPI whb_wth_jyls    (const char *pZjzh,const char *pZhmm,const char *pWTH  ,char **pOut,void *pACI );

///����ʽ�������� 
APEX3RD_API int WINAPI fund_trade_buy(char *pZjzh,char *pJymm,char *pTadm,char *pJjzh, long nWtlb,
									  char *pJjdm, double fWtje,char *pSfffs,void *pACI);

APEX3RD_API int WINAPI fund_trade_redeem(char *pZjzh,char *pJymm,char *pTadm,char *pJjzh, long nWtlb,
									  char *pJjdm, double fWtfe,long nJeshcl,char* pYyrq, char *pSfffs,void *pACI);
APEX3RD_API int WINAPI fund_trade_abort(char *pZjzh,char *pJymm,char *pTadm,char *pJjzh, long nWtlb,
									  char *pJjdm, char* pSqbh, void *pACI);
APEX3RD_API int WINAPI fund_trade_abort_wth(char *pZjzh,char *pJymm,long nWth, void *pACI);
APEX3RD_API int WINAPI fund_read_jjdm(char *pTadm,char *pJjdm,char **pOut,void *pACI );
APEX3RD_API int WINAPI fund_read_jjzh(char *pZjzh,char *pTadm,char **pOut,void *pACI );
APEX3RD_API int WINAPI fund_read_drwt(char *pZjzh,char *pTadm,char *pJjzh,char **pOut,void *pACI );
APEX3RD_API int WINAPI fund_read_gfxx(char *pZjzh,char *pTadm,char *pJjzh,char *pJjdm,char **pOut,void *pACI );
APEX3RD_API int WINAPI fund_read_cjxx(char *pZjzh,char *pTadm,char *pJjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
APEX3RD_API int WINAPI fund_trade_jjzh(char *pZjzh,char *pJymm,char *pTadm,char *pJjzh, 
									  char *pJjdm, double fWtje,char *pDfjjdm,void *pACI);
APEX3RD_API int WINAPI fund_trade_ztzsz(char *pZjzh,char *pJymm,char *pTadm,char *pJjzh, 
									  char *pJjdm, long nFhfs,char *pSfffs,void *pACI);

//*****���¾�Ҫ���ڲ�ʹ��***************
//���ӹ�Ա
APEX3RD_API int WINAPI UserOper_adduser(char *pUID,char *pUName,char *pPass,char *pGroup, char *pQZ, char *pYYB, char *pGYID, void *pACI);
//Ȩ�޸���
APEX3RD_API int WINAPI UserOper_CopyRight(char *pUID,char *pOPER,char *pUID2, char *pGYID,char *pGYMM, char *pOut,void *pACI);
//����ɾ��Ȩ��
APEX3RD_API int WINAPI UserOper_AddCanRight(char *pUID,char *pOPER,char *pRight, char *pGYID,char *pGYMM, char *pOut,void *pACI);
//���¹�Ա��Ϣ
APEX3RD_API int WINAPI UserOper_updateuser(char *pUID,char *pUName,char *pStatus, char *pQZXZ, char *pYYB,char *pYYBXZ, char *pGYID,char *pGYMM, void *pACI);
//ɾ����Ա
APEX3RD_API int WINAPI UserOper_deluser(char *pUID,char *pGYID,char *pGYMM, void *pACI);
//��ԱȨ�޲�ѯ
APEX3RD_API int WINAPI read_rights(const char *pUser,const char *pPwd,char **pOut,void *pACI);
//ϵͳ�ʻ�Ⱥ���ѯ
APEX3RD_API int WINAPI read_zhqz(char **pOut,void *pACI);
//ί�з�ʽ��ѯ
APEX3RD_API int WINAPI read_wtfs(char **pOut,void *pACI);
//ϵͳ�����ѯ
APEX3RD_API int WINAPI read_xtdm(const char *pXTXM,char **pOut,void *pACI);
APEX3RD_API int WINAPI zjzh_djjd( const char *pZjzh,const char *pZhmm,const char* bz,double dFsje,int nCZType, const char *pZY , int nMMJY ,void *pACI );
//*****���¾�Ҫ���ڲ�ʹ��***************

APEX3RD_API int WINAPI read_fjsx(char *pZjzh,char * pSXLB,char **pOut,void *pACI);
APEX3RD_API int WINAPI read_zqjydw(void *pACI );
//�޸ĸ�������
APEX3RD_API int WINAPI Modify_fjsx(char *pZjzh,char * pSXLB,char * pNewValue,void *pACI);
//��ѯ���ڹɶ��й�����ɶ���(AI_AU_CHECKSZGDTG) (ֻ�ʼ��н��װ�)
APEX3RD_API int WINAPI read_szgftg( char *pGdzh,char * pJys,char *pYyb,char **pOut,void *pACI);
//��ѯ�����ʽ�䶯
APEX3RD_API int WINAPI read_zj_drbd( char *pZjzh,char *pBz, char **pOut,void *pACI );
//  ԤԼ��ȡ
APEX3RD_API int WINAPI zjzh_yycq( const char *pZjzh,const char *pYyrq,const char* bz,double dFsje,int nCZType, const char *pZY ,const char * pYhdm , int nLsh ,void *pACI );
//  ԤԼ��ȡ��ѯ
APEX3RD_API int WINAPI read_yycq_zjzh( char *pZjzh,char *pBz,char *pKsrq,char *pJsrq,char **pOut,void *pACI );

APEX3RD_API int WINAPI etf_sgsh(char *pJYS,char *pGDH,char *pZQDM,long nWTSL,double dWTJG,char *pZJZH,char *pPwd, void *pACI);

APEX3RD_API int WINAPI etf_read_wxrg(char *pKSRQ,char *pJSRQ,char *pJYS,char *pRGDM,char *pGDH,char *pZJZH,long nSQBH,char *pRGLB,char **pOut,void *pACI );

APEX3RD_API int WINAPI etf_wxcd(long nSQBH,char *pJYS,char *pGDH,char *pPwd,char * pRGDM,void *pACI);

APEX3RD_API int WINAPI etf_wxrg(char *pGDH,char *pZQDM,char *pJYS, long nRGSL, long nRGLB,char *pRGDM,double dRGJG,char *pPwd, void *pACI);

APEX3RD_API int WINAPI read_qsfy(const char *pZQDM,const char *pJYS,long nSL,double dJG,long nWTLB,double dCJJE,char **pOut,void *pACI );

APEX3RD_API int WINAPI etf_read_gpzh(const char *pYJDM,const char *pJYS,char **pOut,void *pACI );

APEX3RD_API int WINAPI etf_read_cs(const char *pYJDM,const char *pJYS,char **pOut,void *pACI );

APEX3RD_API int WINAPI read_drcj_lsh( char *pZjzh,char *pJys,char *pGdh,char *pZqdm,long lsh,char **pOut,void *pACI );