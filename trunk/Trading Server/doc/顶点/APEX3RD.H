
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
//取数据缓冲区的一条记录
APEX3RD_API char * WINAPI QAGetRow( char *pData,int nIndex,char *pBuff,int nMaxSize );
//取记录中的一个域
APEX3RD_API char * WINAPI QAGetString( char *pData,int nIndex,char *pBuff,int nMaxSize );
//初始化,设置基本参数
APEX3RD_API BOOL WINAPI Apex3rdInit(const char *pUser,const char *pWtfs,const char *pYyb,const char *pRight );
//设置远程营业部
APEX3RD_API BOOL WINAPI ApexSetDestYYB( int nYYB,void *pACI );
//程序退出
APEX3RD_API void WINAPI Apex3rdExit();
//打开连接
APEX3RD_API void * WINAPI ApexOpenLink( const char *pDest,char *pRemote );
//关闭连接
APEX3RD_API void WINAPI ApexCloseLink( void *pACI );
//取上次操作返回信息
APEX3RD_API int WINAPI GetLastErrMsg( void *pACI,char *buffer);
//资金号确认
APEX3RD_API int WINAPI check_zjzh(char *pZjzh, char *pPwd, void *pACI );
//股东号确认
APEX3RD_API int WINAPI check_gdzh(char *pGdzh, char *pJys, char *pPwd, void *pACI );

//经纪人确认
APEX3RD_API int WINAPI check_jjr(char *pJjr, char *pPwd, void *pACI );

//查询经纪人客户
APEX3RD_API int WINAPI read_jjrkh(char *pJjr, char **pOut ,void *pACI );

//查询股东号
APEX3RD_API int WINAPI read_gdzh(char *pZjzh,char *pJys,char **pOut,void *pACI );
//取行情
APEX3RD_API int WINAPI read_hqinfo( char *pZqdm, char *pJys,char **pOut,void *pACI );
//取资金信息
APEX3RD_API int WINAPI read_zjxx(char *pZjzh,char *pBz,char **pOut,void *pACI);
//买入委托
APEX3RD_API int WINAPI trade_buy(char *pZjzh,char *pJys,char *pGdzh,char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
//卖出委托
APEX3RD_API int WINAPI trade_sale(char *pZjzh,char *pJys,char *pGdzh, char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
//委托撤单
APEX3RD_API int WINAPI trade_abort(char *pZjzh,char *pJys,char *pGdzh,char *pPwd,char *pHth,void *pACI);
//批量撒单
APEX3RD_API int WINAPI trade_abort_batch(char *pZjzh,char *pJys,char *pGdzh,char *pPwd,char *pZqdm,void *pACI);
//批量买入
APEX3RD_API int WINAPI trade_buy_batch(char *pZjzh,char *pJys,char *pGdzh,char *pZqdm, float nWtjg, long nWtzl,long nWtsl, char *pPwd, void *pACI);
//批量卖出
APEX3RD_API int WINAPI trade_sale_batch(char *pZjzh,char *pJys,char *pGdzh, char *pZqdm, float nWtjg, long nWtsl, char *pPwd, void *pACI);
//深圳转托管
APEX3RD_API int WINAPI trade_szztg(char *pZjzh,
										 char *pGdzh,char *pPwd,
										 char *pZqdm,long nWtsl ,const char *pQSDM, float dSFJE, int nSFFS ,void *pACI);
//nSFFS 0:为现金收费,1:转帐收费


//当日委托查询
APEX3RD_API int WINAPI read_wt_zjzh( char *pZjzh,char *pJys,char **pOut,void *pACI );
//历史委托查询
APEX3RD_API int WINAPI read_lswt_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//按资金号查询股票余额
APEX3RD_API int WINAPI read_gp_zjzh( char *pZjzh,char *pJys,char **pOut,void *pACI );
//按证券代码查询股票余额(计算可卖数量)
APEX3RD_API int WINAPI read_gp_zqdm( char *pGdzh,char *pJys,char *pZqdm,char **pOut,void *pACI );
//查询新股配号
APEX3RD_API int WINAPI read_xgph_zjzh( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//计算可买数量
APEX3RD_API int WINAPI read_kmrsl( char *pZjzh,char *pJys,char *pZqdm,double nWtjg,void *pACI,char *pGdh);
//当日成交查询
APEX3RD_API int WINAPI read_drcj_zjzh( char *pZjzh,char *pJys,char **pOut,void *pACI );
//当日成交明细查询
APEX3RD_API int WINAPI read_drcj_hth( char *pGdzh,char *pJys,char *pHth,char **pOut,void *pACI );
//历史成交查询
APEX3RD_API int WINAPI read_lscj_zjzh( char *pZjzh,char *pJys,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//回购交割查询
APEX3RD_API int WINAPI read_hgjg_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//历史成交查询(广发) 2001.05.18
APEX3RD_API int WINAPI read_gfcj_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char *pBZ,char **pOut,void *pACI );
APEX3RD_API int WINAPI read_jgrq(char *pZjzh,void *pACI);
//证券明细查询
APEX3RD_API int WINAPI read_zqmx_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char *pJys,char *pGdh,char **pOut,void *pACI );

//修改帐户密码(交易密码)
APEX3RD_API int WINAPI change_password(char *pZjzh,char *pOldPwd,char *pNewPwd,void *pACI);
//修改资金密码
APEX3RD_API int WINAPI change_zjmm(char *pZjzh,char *pOldPwd,char *pNewPwd,void *pACI);
//银行转帐(银行转到证券)
APEX3RD_API int WINAPI yhzz_yhtozq( char *pZjzh,char *pZjmm,char *pYhdm,char *pYhzh,char *pYhmm,double nZzje,char *pBZ, int nHBLB,void *pACI );
//银行转帐(证券转到银行)
APEX3RD_API int WINAPI yhzz_zqtoyh( char *pZjzh,char *pZjmm,char *pYhdm,char *pYhzh,char *pYhmm,double nZzje,char *pBZ, int nHBLB,void *pACI );
//银行余额查询申请
APEX3RD_API int WINAPI yhzz_cx_yhye( char *pZjzh,char *pZjmm,char *pYhdm,char *pYhzh,char *pYhmm,char *pBZ, int nHBLB,void *pACI );
//查询银行卡号
APEX3RD_API int WINAPI read_yhzh( char *pZjzh,char *pZhmm,char *pYhdm,char **pOut,void *pACI );
APEX3RD_API int WINAPI read_yhzh_bz( char *pZjzh,char *pZhmm,char *pYhdm,char * pBZ,char **pOut,void *pACI );
//银行转帐流水查询
APEX3RD_API int WINAPI read_yhzz_zjzh( char *pZjzh,char *pZhmm,char **pOut,void *pACI );
//银行转帐合同号查询
APEX3RD_API int WINAPI read_yhzz_hth( char *pZjzh,char *pZhmm,char *pHth,char **pOut,void *pACI );
//查询资金流水(资金明细)
APEX3RD_API int WINAPI read_zjls( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//检查股民密码
APEX3RD_API int WINAPI checkaccpass( char *pKhdm,char *pStyle,char *pJys,char *pZhmm,int nType,void *pACI );
//当日委托查询按zjzh,gdzh,hth组合
APEX3RD_API int WINAPI requestentrust( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char **pOut,void *pACI );
//当日成交查询按zjzh,gdzh,hth组合
APEX3RD_API int WINAPI entrustresult( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char **pOut,void *pACI );
//历史成交查询按zjzh,gdzh,wth组合
APEX3RD_API int WINAPI requestbusiness( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//查询股票,按zjzh,gdzh,zqdm组合
APEX3RD_API int WINAPI requeststock( char *pZjzh,char *pJys,char *pGdzh,char *pZqdm,char **pOut,void *pACI );
//设置参数
APEX3RD_API int WINAPI Apex3rdSetPara( char *pUser,char *pWtfs,char *pYyb,char *pNode );
//历史委托查询按zjzh,gdzh,hth组合
APEX3RD_API int WINAPI requesthistentrust( char *pZjzh,char *pJys,char *pGdzh,char *pHth,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//历史委托查询
APEX3RD_API int WINAPI read_lswt_zjzh( char *pZjzh,char *pKsrq,char *pJsrq,char **pOut,void *pACI );
//查询资金帐户客户信息
APEX3RD_API int WINAPI requestaccinfo( char *pZjzh,void *pACI );
APEX3RD_API int WINAPI requestaccinfoex( const  char *pZjzh,const char *pMode , const char * sLB,void *pACI );
//银行转帐业务
APEX3RD_API int WINAPI transferbusiness( int nStyle,char *pZjzh,char *pZjmm,char *pYhdm,char *pYhzh,char *pYhmm,double nZzje,char *pBz,void *pACI );


//资金存取
APEX3RD_API int WINAPI zjcq(const  char *pZjzh,const char *pZjmm,double dbje,const char * bz,
							const char *ywkm,const char *sqly,const char *sqfs,const char *zy,bool bMMBZ,void *pACI );
//资金冲帐
APEX3RD_API int WINAPI zjcz(const  char *pZjzh,const char *pZjmm,long nPzh,
							const char *sqly,const char *sqfs,const char *zy,void *pACI );

//开户
APEX3RD_API int WINAPI zjzh_found( const char *pZjzh,const char *pZhxm,const char * yyb,const char *zhqz,const char *wtfs,
									const char *fwxm,const char* sfzh,const char * dz,const char* dh,const char *jymm,const char * zhmm,
									const char *yhdm,const char *yhzh,const char* bz,	char *pNewZjzh,void *pACI );
//币种开户
APEX3RD_API int WINAPI zjzh_found_bz( const char *pZjzh,const char *pZhmm,const char *bz ,void *pACI );
//资金帐户修改
APEX3RD_API int WINAPI zjzh_modify( const char *pZjzh ,const char *pKHLB,const char *pJYS, const char *pZjmm,const char *pXgxm ,const char  *pOldValue , const char *pNewValue ,bool bModifyType, void *pACI );

//销资金户申请
APEX3RD_API int WINAPI zjzh_destroy(const  char *pZjzh,const char *pZhmm,void *pACI );
APEX3RD_API int WINAPI zjzh_destroy_request(const  char *pZjzh,const char *pZhmm,	void *pACI );
//股东开户
APEX3RD_API int WINAPI gdh_found( const char *pZjzh,const char *pZhmm,const char * gdzh,const char *gdxm,const char *jys,
								 const char* sfzh,const char * dz,const char* dh,const char *mmlb,long gdzd,void *pACI );
//销股东户
APEX3RD_API int WINAPI gdh_destory(const  char *pZjzh,const char *pZhmm,const char * gdzh,const char *jys,void *pACI );

//挂失股东帐号
APEX3RD_API int WINAPI gdh_suspend(const char *pZjzh,const char *pZhmm,const char * gdzh,const char *jys,void *pACI);
//查询所有股东号<含挂失帐户>
APEX3RD_API int WINAPI read_allgdzh(const char *pZjzh,const char *pZhmm,const char *pJys,char **pOut,void *pACI );
//查询所有银行帐户<含非正常状态>
APEX3RD_API int WINAPI read_allyhzh(const char *pZjzh,const char *pZhmm,const char *pYhdm,char **pOut,void *pACI );
//查询股东帐户信息
APEX3RD_API int WINAPI requestgdhinfo(const char *pGdzh ,const char *sJys,void *pACI );
//修改股东帐户信息
APEX3RD_API int WINAPI gdh_modify( const char *pZjzh , const char *pZhmm, const char *pGdzh ,const char *sJys, const char *pXgxm , const char *pOldValue, const char *pNewValue, void *pACI );

//解挂股东帐号
APEX3RD_API int WINAPI gdh_resume(const char *pZjzh,const char *pZhmm,const char * gdzh,const char *jys,void *pACI);

//银行帐户登记
APEX3RD_API int WINAPI yhzh_found( const char *pZjzh,const char *pZhmm,const char * pYhdm,const char *pYhzh,double dYwsf, const char *pBz ,void *pACI );
//银行帐户注销
APEX3RD_API int WINAPI yhzh_destory(const char *pZjzh,const char *pZhmm,const char * pYhdm,const char *pYhzh,void *pACI );

//柜员注册
APEX3RD_API int WINAPI user_login(const char *pUser,const char *pPwd,void *pACI);

//当日柜员业务查询
APEX3RD_API int WINAPI read_drgyye(const char * pUserName ,const char *pPwd,const char *pBZ ,char **pOut,void *pACI);

//[存折炒股] 资金帐户下的主存折的余额信息查询
APEX3RD_API int WINAPI read_czye( const char *pZjzh , const char * pZhmm , void *pACI );
//[存折炒股] 请求该银行卡余额
APEX3RD_API int WINAPI request_czye( const char *pZjzh , const char *pYhzh , const char *pYhdm , const char * pYhmm , const char *pBZ , void *pACI );

//[存折炒股] 主存折号查询
APEX3RD_API int WINAPI set_zczh(const char *pZjzh, const char *pZhmm, const char *pYhzh , const char * pYhdm ,void *pACI );

//[存折炒股] 查询客户信息 [根据主存折卡号] <专为存折炒股>
APEX3RD_API int WINAPI read_khxx_zczh( const char *pYhzh ,const char *pZhmm, const char * pYhdm , void *pACI );
   //返回:资金帐户|营业部|群组|帐户状态|委托方式|服务项目|附加信息

//[存折炒股] 设置主存折帐户
APEX3RD_API int WINAPI set_zczh(const char *pZjzh, const char *pZhmm, const char *pYhzh , const char * pYhdm ,void *pACI );
   //返回:   >0成功 ; <0 失败
//委托收费
APEX3RD_API int WINAPI send_wtsf(char *pZjzh,char *pJys,char *pZqlb,void *pACI);

//外汇宝交易
APEX3RD_API int WINAPI whb_cx_ytoz_jypj(const char *pZjzh,const char *pZjmm,const char *pYhdm ,const char *pYhzh,const char *pYhmm,const char *pMcbz,const char *pChbs,const double fMcje,const char *pMrbz,void *pACI );
APEX3RD_API int WINAPI whb_cx_ztoy_jypj(const char *pZjzh,const char *pZjmm,const char *pYhdm ,const char *pYhzh,const char *pYhmm,const char *pMcbz,const char *pChbs,const double fMcje,const char *pMrbz,void *pACI );
APEX3RD_API int WINAPI whb_cx_ztoz_jypj(const char *pZjzh,const char *pZjmm,const char *pYhdm ,const char *pZjzh2,const char *pYhmm,const char *pMcbz,const char *pChbs,const double fMcje,const char *pMrbz,void *pACI );
APEX3RD_API int WINAPI whb_ytoz_jy     (const char *pZjzh,const char *pZjmm,const char *pYhdm ,const char *pYhzh,const char *pYhmm,const char *pMcbz,const char *pChbs,const double fMcje,const char *pMrbz,double fJypj,char * pFlg,void *pACI );
APEX3RD_API int WINAPI whb_ztoy_jy     (const char *pZjzh,const char *pZjmm,const char *pYhdm ,const char *pYhzh,const char *pYhmm,const char *pMcbz,const char *pChbs,const double fMcje,const char *pMrbz,double fJypj,char * pFlg,void *pACI );
APEX3RD_API int WINAPI whb_ztoz_jy     (const char *pZjzh,const char *pZjmm,const char *pYhdm ,const char *pZjzh2,const char *pYhmm,const char *pMcbz,const char *pChbs,const double fMcje,const char *pMrbz,double fJypj,char * pFlg,void *pACI );
APEX3RD_API int WINAPI whb_zjzh_jyls   (const char *pZjzh,const char *pZhmm,const char *pYhdm ,char **pOut,void *pACI );
APEX3RD_API int WINAPI whb_wth_jyls    (const char *pZjzh,const char *pZhmm,const char *pWTH  ,char **pOut,void *pACI );

///开放式基金销售 
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

//*****以下均要求内部使用***************
//增加柜员
APEX3RD_API int WINAPI UserOper_adduser(char *pUID,char *pUName,char *pPass,char *pGroup, char *pQZ, char *pYYB, char *pGYID, void *pACI);
//权限复制
APEX3RD_API int WINAPI UserOper_CopyRight(char *pUID,char *pOPER,char *pUID2, char *pGYID,char *pGYMM, char *pOut,void *pACI);
//增加删除权限
APEX3RD_API int WINAPI UserOper_AddCanRight(char *pUID,char *pOPER,char *pRight, char *pGYID,char *pGYMM, char *pOut,void *pACI);
//更新柜员信息
APEX3RD_API int WINAPI UserOper_updateuser(char *pUID,char *pUName,char *pStatus, char *pQZXZ, char *pYYB,char *pYYBXZ, char *pGYID,char *pGYMM, void *pACI);
//删除柜员
APEX3RD_API int WINAPI UserOper_deluser(char *pUID,char *pGYID,char *pGYMM, void *pACI);
//柜员权限查询
APEX3RD_API int WINAPI read_rights(const char *pUser,const char *pPwd,char **pOut,void *pACI);
//系统帐户群组查询
APEX3RD_API int WINAPI read_zhqz(char **pOut,void *pACI);
//委托方式查询
APEX3RD_API int WINAPI read_wtfs(char **pOut,void *pACI);
//系统代码查询
APEX3RD_API int WINAPI read_xtdm(const char *pXTXM,char **pOut,void *pACI);
APEX3RD_API int WINAPI zjzh_djjd( const char *pZjzh,const char *pZhmm,const char* bz,double dFsje,int nCZType, const char *pZY , int nMMJY ,void *pACI );
//*****以下均要求内部使用***************

APEX3RD_API int WINAPI read_fjsx(char *pZjzh,char * pSXLB,char **pOut,void *pACI);
APEX3RD_API int WINAPI read_zqjydw(void *pACI );
//修改附加属性
APEX3RD_API int WINAPI Modify_fjsx(char *pZjzh,char * pSXLB,char * pNewValue,void *pACI);
//查询深圳股东托管虚拟股东号(AI_AU_CHECKSZGDTG) (只适集中交易版)
APEX3RD_API int WINAPI read_szgftg( char *pGdzh,char * pJys,char *pYyb,char **pOut,void *pACI);
//查询当日资金变动
APEX3RD_API int WINAPI read_zj_drbd( char *pZjzh,char *pBz, char **pOut,void *pACI );
//  预约存取
APEX3RD_API int WINAPI zjzh_yycq( const char *pZjzh,const char *pYyrq,const char* bz,double dFsje,int nCZType, const char *pZY ,const char * pYhdm , int nLsh ,void *pACI );
//  预约存取查询
APEX3RD_API int WINAPI read_yycq_zjzh( char *pZjzh,char *pBz,char *pKsrq,char *pJsrq,char **pOut,void *pACI );

APEX3RD_API int WINAPI etf_sgsh(char *pJYS,char *pGDH,char *pZQDM,long nWTSL,double dWTJG,char *pZJZH,char *pPwd, void *pACI);

APEX3RD_API int WINAPI etf_read_wxrg(char *pKSRQ,char *pJSRQ,char *pJYS,char *pRGDM,char *pGDH,char *pZJZH,long nSQBH,char *pRGLB,char **pOut,void *pACI );

APEX3RD_API int WINAPI etf_wxcd(long nSQBH,char *pJYS,char *pGDH,char *pPwd,char * pRGDM,void *pACI);

APEX3RD_API int WINAPI etf_wxrg(char *pGDH,char *pZQDM,char *pJYS, long nRGSL, long nRGLB,char *pRGDM,double dRGJG,char *pPwd, void *pACI);

APEX3RD_API int WINAPI read_qsfy(const char *pZQDM,const char *pJYS,long nSL,double dJG,long nWTLB,double dCJJE,char **pOut,void *pACI );

APEX3RD_API int WINAPI etf_read_gpzh(const char *pYJDM,const char *pJYS,char **pOut,void *pACI );

APEX3RD_API int WINAPI etf_read_cs(const char *pYJDM,const char *pJYS,char **pOut,void *pACI );

APEX3RD_API int WINAPI read_drcj_lsh( char *pZjzh,char *pJys,char *pGdh,char *pZqdm,long lsh,char **pOut,void *pACI );