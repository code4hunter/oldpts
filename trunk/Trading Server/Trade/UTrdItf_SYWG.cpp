//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <SysUtils.hpp>
#include "UTrdItf_SYWG.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
TTrdItf_SYWG::TTrdItf_SYWG(TSYWGSet *pSet)
{
  m_CnID = 0;
  m_AccType = 0;
  CopyMemory(&FSYWGSet, pSet, sizeof(TSYWGSet));
}
//---------------------------------------------------------------------------
TTrdItf_SYWG::~TTrdItf_SYWG()
{
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::Init()  //初始化
{
  return LocalInit();
}
//---------------------------------------------------------------------------
/*
1、 功能号0x101 校验股民交易密码, 打开帐号
调用此功能，如校验股民交易密码通过，该客户的帐号将处于允许交易的打开状态，直到下列情况之一发生：
1．该连接调用功能0x103关闭帐号
2．该连接关闭。
*/
/*
#pragma pack(push, 1)
//请求消息

struct SWI_OpenAccountRequest
{
	struct SWI_BlockHead head;	// function_no==0x101, block_type == 1
	char   account_type;     	// 客户帐号类型（见数据字典说明）
	char   account[16];      	// 客户帐号
	char   pwd[8];           	// 交易密码
	//short  op_code;             // 操作员工号
	//unsigned  long   flag;         //"特殊条件"判断标志位组合,每一个二进制位对应一个"特殊条件",缺省值为0表示不判断任何"特殊条件"
	//char   productno [7];		    //产品信息编号：5位电脑网络中心产品编码+2位子
	//产品编码（共7位字符）；缺省值为空。

        //char pad[7];
};
#pragma pack(pop)
*/

int TTrdItf_SYWG::SetAccount() //设置帐号
{
  if(FRequest.SetAccount.Sort == asCA)//资金帐号
    m_AccType = '0';//A股资金帐号
  else if(FRequest.SetAccount.Sort == asSH)//上海交易所的股东代码
    m_AccType = '1';//上A证号
  else if(FRequest.SetAccount.Sort == asSZ)
    m_AccType = '2';//深A证号
  else
  {
    ODS("无效的用户帐号类型:%d", FRequest.SetAccount.Sort);
    return -1;
  }

  if(OpenAccount(m_AccType, FRequest.SetAccount.Account, FRequest.SetAccount.PW) != 0)
    return -1;

  lstrcpyn(FAccInfo.Capital, FRequest.SetAccount.Account, 13);//资金帐号
  lstrcpyn(FAccInfo.PW, FRequest.SetAccount.PW, 13);//帐号密码
  strcpy(FAccInfo.SH, "");//上海交易所股东代码
  strcpy(FAccInfo.SZ, "");//深圳交易所股东代码

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::GetTrdInfo()   //取得盘口数据
{
  ////Checked200412302210!!!
  //Request;
  SWI_SecurityInfoRequest swSecurityReq;
  InitRequest(&swSecurityReq, sizeof(SWI_SecurityInfoRequest), SWI_FUNC_QUERY_SECURITY_INFO);

  swSecurityReq.exchange_no = 0;////交易所编号（见数据字典说明）0 ----- 全部A股（仅用于查询）
  //swSecurityReq.security_idx = ; //???证券序号（见注）
  lstrcpyn(swSecurityReq.security_code, FRequest.GetTrdInfo.SecuID+1, 7);// 证券代码

  if(SetRequest(&swSecurityReq, sizeof(SWI_SecurityInfoRequest)) != 0)
  {
    ODS("发送GetTrdInfo请求失败");
    return -1;
  }

    //Response;
  SWI_SecurityInfoReturn swSecurityAns;
  if(FSafeSock.RecvAnswer(&swSecurityAns, sizeof(SWI_SecurityInfoReturn)) != 0)
  {
    ODS("接收GetTrdInfo返回信息失败");
    return -2;
  }

  if(swSecurityAns.return_status <= 0)
  {
    ShowErrorMsg("GetTrdInfo请求失败", swSecurityAns.return_status);
    return -1;
  }

  //set value;
  NewAns(1);
  (*FAnswer)[0].GetTrdInfo.BuyInfo.ZXJ    = SWISmallMoneyToDouble(swSecurityAns.current_price);//最新价
  (*FAnswer)[0].GetTrdInfo.BuyInfo.Price1 = SWISmallMoneyToDouble(swSecurityAns.buy_price_1);//申价1
  (*FAnswer)[0].GetTrdInfo.BuyInfo.Price2 = SWISmallMoneyToDouble(swSecurityAns.buy_price_2);//申价2
  (*FAnswer)[0].GetTrdInfo.BuyInfo.Price3 = SWISmallMoneyToDouble(swSecurityAns.buy_price_3);//申价3
  (*FAnswer)[0].GetTrdInfo.BuyInfo.Volum1 = swSecurityAns.buy_amount_1;//申量1
  (*FAnswer)[0].GetTrdInfo.BuyInfo.Volum2 = swSecurityAns.buy_amount_2;//申量2
  (*FAnswer)[0].GetTrdInfo.BuyInfo.Volum3 = swSecurityAns.buy_amount_3;//申量3
  (*FAnswer)[0].GetTrdInfo.BuyInfo.CJSL   = swSecurityAns.amount; //成交数量

  (*FAnswer)[0].GetTrdInfo.SellInfo.ZXJ    = SWISmallMoneyToDouble(swSecurityAns.current_price);
  (*FAnswer)[0].GetTrdInfo.SellInfo.Price1 = SWISmallMoneyToDouble(swSecurityAns.sale_price_1);
  (*FAnswer)[0].GetTrdInfo.SellInfo.Price2 = SWISmallMoneyToDouble(swSecurityAns.sale_price_2);
  (*FAnswer)[0].GetTrdInfo.SellInfo.Price3 = SWISmallMoneyToDouble(swSecurityAns.sale_price_3);
  (*FAnswer)[0].GetTrdInfo.SellInfo.Volum1 = swSecurityAns.sale_amount_1;
  (*FAnswer)[0].GetTrdInfo.SellInfo.Volum2 = swSecurityAns.sale_amount_2;
  (*FAnswer)[0].GetTrdInfo.SellInfo.Volum3 = swSecurityAns.sale_amount_3;
  (*FAnswer)[0].GetTrdInfo.SellInfo.CJSL   = swSecurityAns.amount;

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryMoney()     //资金查询
{
  ////Checked200412302210!!!
  //Request;
  SWI_QueryMoneyRequest swMoneyReq;
  InitRequest(&swMoneyReq, sizeof(SWI_QueryMoneyRequest), SWI_FUNC_QUERY_MONEY);

  swMoneyReq.account_type = m_AccType;// 客户帐号类型
  lstrcpyn(swMoneyReq.account, FAccInfo.Capital, 14);// 客户帐号
  swMoneyReq.currency_type = '1'; //币种----- 人民币

  if(SetRequest(&swMoneyReq, sizeof(SWI_QueryMoneyRequest)) != 0)
    return -1;

  //Response;
  SWI_QueryMoneyReturn swMoneyAns;
  if(FSafeSock.RecvAnswer(&swMoneyAns, sizeof(SWI_QueryMoneyReturn)) != 0)
    return -2;
      
  if(swMoneyAns.return_status < 0)// <0  ------ 查询失败
  {
    ("QryMoney请求失败，return status = %d", swMoneyAns.return_status);
    return -1;
  }

  //Set value;
  NewAns(1);
  (*FAnswer)[0].QryMoney.Balance = SWIMoneyToDouble(swMoneyAns.available);//资金余额
  (*FAnswer)[0].QryMoney.Available = SWIMoneyToDouble(swMoneyAns.buyable);//资金可用额
  (*FAnswer)[0].QryMoney.asset_balance = 0;//???资产总值---没有定义

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryStock()     //股份查询
{
  //Checked200412302210!!!
  SWI_QueryStockRequest swStockReq;
  InitRequest(&swStockReq, sizeof(SWI_QueryStockRequest), SWI_FUNC_QUERY_STOCK);

  swStockReq.account_type = m_AccType;// 客户帐号类型
  lstrcpyn(swStockReq.account, FAccInfo.Capital, 16);// 客户帐号
  swStockReq.exchange_no = 0;//交易所编号：0 ----- 全部A股（仅用于查询）
  lstrcpyn(swStockReq.security_code, FRequest.QryStock.SecuID+1, 7);// 证券代码（space(6)表示全部）
  swStockReq.max_results = 1;// // 最大查询记录数---???只查一条记录
  //swStockReq.flag = ;//返回盈亏分析数据标志  =0，缺省，不返回对应值，对应字段为0  =1，返回盈亏分析数据  增加flag，要求尽量少调用flag=1,减少性能影响
  //swStockReq.stock_account = ;//查询证券帐号条件,即以证券帐号为条件过滤结果集，缺省

  if(SetRequest(&swStockReq, sizeof(SWI_QueryStockRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryStockReturn swStockAns;
  try
  {
    pResult = new TList();
    if(!GetQueryResult(pResult, SWI_FUNC_QUERY_STOCK, sizeof(SWI_QueryStockResult),  \
                            &swStockAns, sizeof(SWI_QueryStockReturn)))
      return -1;

    if(pResult->Count > 0)//有结果集返回
    {
      NewAns(1);
      //set value;
      (*FAnswer)[0].QryStock.Balance = ((SWI_QueryStockResult*)(pResult->Items[0]))->deposite;//????资金余额=股票余额
      (*FAnswer)[0].QryStock.Available = ((SWI_QueryStockResult*)(pResult->Items[0]))->available;//???资金可用额=可用余额
      (*FAnswer)[0].QryStock.BuyFreeze = 0;
      (*FAnswer)[0].QryStock.SellFreeze = 0;
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryCanBuy()    //取可买数量
{
  // 暂时不用
  ODS("QryCanBuy暂时不用");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryDetail()    //成交查询
{
  int reqry_num=0;

HH:
  //codehunter add 2005216
  if(FRequest.QryDetail.ContractID[0]==0) return -1;
  //Checked200412302210!!!
  SWI_QueryEntrustRequest swEntrustReq;
  InitRequest(&swEntrustReq, sizeof(SWI_QueryEntrustRequest), SWI_FUNC_QUERY_ENTRUST);
  
  swEntrustReq.account_type = m_AccType;// 客户帐号类型（见数据字典说明）
  lstrcpyn(swEntrustReq.account, FAccInfo.Capital, 16);// 客户帐号
  swEntrustReq.exchange_no = GetExchangeNo(FRequest.QryDetail.Bourse);// 交易所编号（见数据字典说明）
  swEntrustReq.begin_date =  StrToInt(Date().FormatString("yyyymmdd"));//起始日期（形如：yyyymmdd）
  swEntrustReq.end_date = swEntrustReq.begin_date;// 结束日期（形如：yyyymmdd）---查询当日的所有委托
//  int nEntrustSn = StrToIntDef(String(FRequest.QryDetail.ContractID).Trim(), 0);
  //if(nEntrustSn == -1)
    //return -1;
  swEntrustReq.entrust_sn = StrToIntDef(String(FRequest.QryDetail.ContractID).Trim(), 0);// 委托编号（0表示全部）
  //swEntrustReq.security_code = ;// 股票代码（空表示全部）
  swEntrustReq.max_results = 0;//最大查询记录数---???只查一条记录
  //swEntrustReq.stock_type = ;	// 证券类别, 缺省为空，查询全部证券类别.

  if(SetRequest(&swEntrustReq, sizeof(SWI_QueryEntrustRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryEntrustReturn swEntrustAns;
  try
  {
    pResult = new TList();
    if(!GetQueryResult(pResult, SWI_FUNC_QUERY_ENTRUST, sizeof(SWI_QueryEntrustResult),  \
                                  &swEntrustAns, sizeof(SWI_QueryEntrustReturn)))
      return -1;

    if(pResult->Count > 0)//有结果集返回
    {
      NewAns(1);//因为只请求一条记录

      SWI_QueryEntrustResult *pRecord = NULL;
      for(int i=0; i<pResult->Count; i++)
      {
        pRecord = ((SWI_QueryEntrustResult*)(pResult->Items[i]));
        if(pResult->Count > 1 && lstrcmpi(pRecord->security_code, "510051") != 0)//????i只需要返回ETF1的那条记录
          continue;

        if(pResult->Count > 1 && lstrcmpi(pRecord->security_code, "510181") != 0)//????i只需要返回ETF1的那条记录
          continue;
        //set value;
        (*FAnswer)[0].QryDetail.Price = SWISmallMoneyToDouble(pRecord->price);//成交价格---查不出来,直接以委托价格代替（更保守）
        (*FAnswer)[0].QryDetail.Num = pRecord->bargain_ammount;//成交数量

        (*FAnswer)[0].QryDetail.UndoNum = 0;
        if(   pRecord->entrust_status == '4'
           || pRecord->entrust_status == '6'
           || (pRecord->entrust_status == '5' && pRecord->bargain_ammount > 0) )//'4'---无效委托,'6'---已撤单,'5' ----- 部分撤单
        {
          if(pRecord->entrust_status == '5' && ++reqry_num < 3 ) //如果是部撤则再查直到 reqry_num >3
          {
            ReleaseList(pResult);
            Sleep(100);
            goto HH;
          }

          (*FAnswer)[0].QryDetail.UndoNum = pRecord->bargain_ammount - pRecord->stock_ammount;//撤单数量
        }
        //(*FAnswer)[0].QryDetail.status = 0;//状态---不用填写

        //if((*FAnswer)[0].QryDetail.Price<0.001) (*FAnswer)[0].QryDetail.Num=0;
        
        break;
      }
    }
    else
    {
      ODS("QryDetail返回查询结果集为空");
      return -1;
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryHisDetail() //历史成交查询
{
  //暂时不用
  ODS("QryHisDetail暂时不用");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryCsn()       //查询某个委托合同
{
  //暂时不用
  ODS("QryCsn暂时不用");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryCurCsn()    //当日委托查询
{
  //Checked200412302210!!!
  int nDate = StrToInt(Date().FormatString("yyyymmdd"));

  return QueryEntrust(nDate, nDate);
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryHisCsn()    //历史委托查询
{
  //Checked200412302210!!!
  int nStartDate = StrToIntDef(FRequest.QryHisCsn.StartDay, StrToInt(Date().FormatString("yyyymmdd")));
  int nEndDate = StrToIntDef(FRequest.QryHisCsn.EndDay, StrToInt(Date().FormatString("yyyymmdd")));

  return QueryEntrust(nStartDate, nEndDate);
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryCurTrd()    //当日成交查询
{
  SWI_QueryBusinessRequest swBussinessReq;
  InitRequest(&swBussinessReq, sizeof(SWI_QueryBusinessRequest), SWI_FUNC_QUERY_BUSINESS);

  swBussinessReq.account_type = m_AccType;// 客户帐号类型
  lstrcpyn(swBussinessReq.account, FAccInfo.Capital, 16);// 客户帐号
  swBussinessReq.exchange_no = 0;//交易所编号 ----- 全部A股（仅用于查询）
  swBussinessReq.entrust_sn = 0;////委托编号（0表示全部）
  strcpy(swBussinessReq.security_code, "      ");//股票代码（space(6)表示全部）
  swBussinessReq.flag = 1;              //合并方式 0：不合并,1：日期、证券帐号、股票代码、买卖方向合并
  swBussinessReq.begin_serial_no = 0;//// 成交明细开始流水号（缺省值=0）
  
  if(SetRequest(&swBussinessReq, sizeof(SWI_QueryBusinessRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryBusinessReturn swBussinessAns;
  
  try
  {
    pResult = new TList();
    if(!GetQueryResult(pResult, SWI_FUNC_QUERY_BUSINESS, sizeof(SWI_QueryBusinessResult),  \
                                  &swBussinessAns, sizeof(SWI_QueryBusinessReturn)))//>0   查询成功
      return -1;
      
    if(pResult->Count > 0)//有结果集返回
    {
      NewAns(pResult->Count);
      TTradeInfo *pTrdInfo = NULL;
      SWI_QueryBusinessResult *pRecord = NULL;

      for(int i=0; i<pResult->Count; i++)//有结果集返回
      {
        pTrdInfo = &((*FAnswer)[i].QryCurTrd.TrdInfo);
        pRecord = ((SWI_QueryBusinessResult*)(pResult->Items[i]));

        pTrdInfo->SecuID[0] = (pRecord->exchange_no == 1) ? 'H' : 'S';
        lstrcpyn(pTrdInfo->SecuID+1, pRecord->security_code, 7);//证券代码
        lstrcpyn(pTrdInfo->SecuDesc, pRecord->security_name, 9) ; //证券名称

        lstrcpyn(pTrdInfo->Time, pRecord->bargain_time, 9);//成交时间
        lstrcpyn(pTrdInfo->Date, Date().FormatString("yyyymmdd").c_str(), 9);//委托日期

        if(pRecord->bs_type == '1')//'1' ----- 买入//买卖类别 B,S
          pTrdInfo->Type = 'B';
        else if(pRecord->bs_type == '2')//'2' ----- 卖出
          pTrdInfo->Type = 'S';
        else
          pTrdInfo->Type = 'N';   //codehunter add

        pTrdInfo->Vol = pRecord->stock_ammount ;//成交数量
        pTrdInfo->Price = SWISmallMoneyToDouble(pRecord->price);//成交价格
      }
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }

  return 0;  
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryHisTrd()    //历史成交查询
{
  ////Checked200412302210!!!
  SWI_QueryHisBusinessRequest swHisBussinessReq;
  InitRequest(&swHisBussinessReq, sizeof(SWI_QueryHisBusinessRequest), SWI_FUNC_QUERY_HISTORY_BUSINESS);

  swHisBussinessReq.account_type = m_AccType;// 客户帐号类型
  lstrcpyn(swHisBussinessReq.account, FAccInfo.Capital, 16);// 客户帐号
  swHisBussinessReq.exchange_no = 0;//交易所编号 ----- 全部A股（仅用于查询）
  swHisBussinessReq.begin_date = StrToInt((String)FRequest.QryHisTrd.StartDay);// 起始日期
  swHisBussinessReq.end_date = StrToInt((String)FRequest.QryHisTrd.EndDay);// 结束日期
  strcpy(swHisBussinessReq.security_code, "      ");//股票代码（space(6)表示全部）
  swHisBussinessReq.flag = 1;//合并方式 0：不合并,1：日期、证券帐号、股票代码、买卖方向合并
  swHisBussinessReq.max_results = 0;//最大查询记录数---???只查一条记录

  if(SetRequest(&swHisBussinessReq, sizeof(SWI_QueryHisBusinessRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryHisBusinessReturn swHisBussinessAns;
  
  try
  {
    pResult = new TList();
    if(!GetQueryResult(pResult, SWI_FUNC_QUERY_HISTORY_BUSINESS, sizeof(SWI_QueryHisBusinessResult),  \
                                  &swHisBussinessAns, sizeof(SWI_QueryHisBusinessReturn)))//>0   查询成功
      return -1;
      
    if(pResult->Count > 0)//有结果集返回
    {
      NewAns(pResult->Count);
      TTradeInfo *pTrdInfo = NULL;
      SWI_QueryHisBusinessResult *pRecord = NULL;

      for(int i=0; i<pResult->Count; i++)//有结果集返回
      {
        pTrdInfo = &((*FAnswer)[i].QryCurTrd.TrdInfo);
        pRecord = ((SWI_QueryHisBusinessResult*)(pResult->Items[i]));

        pTrdInfo->SecuID[0] = (pRecord->exchange_no == 1) ? 'H' : 'S';
        lstrcpyn(pTrdInfo->SecuID+1, pRecord->security_code, 7);//证券代码
        lstrcpyn(pTrdInfo->SecuDesc, pRecord->security_name, 9) ; //证券名称

        lstrcpyn(pTrdInfo->Time, pRecord->bargain_time, 9);//成交时间
        lstrcpyn(pTrdInfo->Date, IntToStr(pRecord->bargain_date).c_str(), 9);//委托日期

        if(pRecord->bs_type == '1')//'1' ----- 买入//买卖类别 B,S
          pTrdInfo->Type = 'B';
        else if(pRecord->bs_type == '2')//'2' ----- 卖出
          pTrdInfo->Type = 'S';
        else
          pTrdInfo->Type = 'N';  //codehunter

        pTrdInfo->Vol = pRecord->stock_change;//成交数量
        pTrdInfo->Price = SWISmallMoneyToDouble(pRecord->occur_price);//成交价格
      }
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryBill()      //查询资金流水（对帐单）
{
  ////Checked200412302210!!!
  SWI_QueryFundDetailRequest swFundDetailReq;
  InitRequest(&swFundDetailReq, sizeof(SWI_QueryFundDetailRequest), SWI_FUNC_QUERY_FUND_DETAIL);

  swFundDetailReq.account_type = m_AccType;// 客户帐号类型
  lstrcpyn(swFundDetailReq.account, FAccInfo.Capital, 16); // 客户帐号
  swFundDetailReq.exchange_no = 0;//交易所编号 ----- 全部A股（仅用于查询）
  swFundDetailReq.begin_date = StrToIntDef((String)FRequest.QryBill.StartDay, StrToInt(Date().FormatString("yyyymmdd")));// 起始日期（形如：yyyymmdd）
  swFundDetailReq.end_date = StrToIntDef((String)FRequest.QryBill.EndDay, StrToInt(Date().FormatString("yyyymmdd")));// 结束日期（形如：yyyymmdd）
  swFundDetailReq.currency_type = '1';///币种'1' ----- 人民币
  swFundDetailReq.max_results = 0;// 最大查询记录数
  swFundDetailReq.flag = 0;// 查询方式 0 - 资金明细

  if(SetRequest(&swFundDetailReq, sizeof(SWI_QueryFundDetailRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryFundDetailReturn swFundDetailAns;
  
  try
  {
    pResult = new TList();
    if(!GetQueryResult(pResult, SWI_FUNC_QUERY_FUND_DETAIL, sizeof(SWI_QueryFundDetailResult),  \
                                  &swFundDetailAns, sizeof(SWI_QueryFundDetailReturn))) // >0 ------ 查询成功
      return -1;
      
    if(pResult->Count > 0)//有结果集返回
    {
      NewAns(pResult->Count);
      TFundInfo *pFundInfo = NULL;
      SWI_QueryFundDetailResult *pRecord = NULL;

      for(int i=0; i<pResult->Count; i++)//有结果集返回
      {
        pFundInfo = &((*FAnswer)[i].QryBill.FundInfo);
        pRecord = ((SWI_QueryFundDetailResult*)(pResult->Items[i]));

        strcpy(pFundInfo->Date, IntToStr(pRecord->change_date).c_str());//委托日期=发生日期（形如：yyyymmdd）
        pFundInfo->SecuID[0] = 'H';//???默认上交所
        lstrcpyn(pFundInfo->SecuID+1, pRecord->security_code, 7);//证券代码
        lstrcpyn(pFundInfo->SecuDesc, pRecord->security_name, 9) ; //证券代码
        if(pRecord->stock_ammount > 0)
          strcpy(pFundInfo->Type, "Buy"); //买卖类别说明---无所谓
        else
         strcpy(pFundInfo->Type, "Sell");

        pFundInfo->Vol = abs(pRecord->stock_ammount);//成交数量 = 证券成交数量（正：买入；负：卖出）
        pFundInfo->Price = SWISmallMoneyToDouble(pRecord->price);//成交价格= 证券成交均价
        pFundInfo->TrdMny = SWIMoneyToDouble(pRecord->change);//成交金额=？？？发生金额
        pFundInfo->Balance = SWIMoneyToDouble(pRecord->deposite);//资金余额=？？？本次发生后资金余额
      }
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryStocks()    //查询帐号中所有的股份
{
  //Checked200412302210!!!
  SWI_QueryStockRequest swStockReq;
  InitRequest(&swStockReq, sizeof(SWI_QueryStockRequest), SWI_FUNC_QUERY_STOCK);
  
  swStockReq.account_type = m_AccType;// 客户帐号类型
  lstrcpyn(swStockReq.account, FAccInfo.Capital, 16);// 客户帐号
  swStockReq.exchange_no = 0;//交易所编号：0 ----- 全部A股（仅用于查询）
  //strcpy(swStockReq.security_code, "");// 证券代码,空表示查询所有股票持仓情况。
  swStockReq.max_results = 0;// // 最大查询记录数---（0表示全部）
  //swStockReq.flag = ;//返回盈亏分析数据标志  =0，缺省，不返回对应值，对应字段为0  =1，返回盈亏分析数据  增加flag，要求尽量少调用flag=1,减少性能影响
  //swStockReq.stock_account = ;//查询证券帐号条件,即以证券帐号为条件过滤结果集，缺省

  if(SetRequest(&swStockReq, sizeof(SWI_QueryStockRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryStockReturn swStockAns;
  try
  {
    pResult = new TList();
    if(!GetQueryResult(pResult, SWI_FUNC_QUERY_STOCK, sizeof(SWI_QueryStockResult),  \
                            &swStockAns, sizeof(SWI_QueryStockReturn)))
      return -1;

    if(pResult->Count > 0)//有结果集返回
    {
      NewAns(pResult->Count);
      //set value;
      for(int i=0; i<pResult->Count; i++)
      {
        TStockInfo *pStock = &(*FAnswer)[i].QryStocks.StockInfo;
        SWI_QueryStockResult *pRecord = ((SWI_QueryStockResult*)(pResult->Items[i]));

        pStock->SecuID[0] = (pRecord->exchange_no == 1) ? 'H' : 'S';
        lstrcpyn(pStock->SecuID+1, pRecord->security_code, 7);//证券代码
        //pStock->SecuDesc = ;    //证券名称
        pStock->Balance = pRecord->deposite;//余额
        pStock->Available = pRecord->available;//可用数
        pStock->BuyFreeze = 0;//买入冻结
        pStock->SellFreeze = 0;//卖出冻结
        pStock->AbnorFreeze = 0;//异常冻结

        pStock->Cost = 0;//参考成本
        pStock->CostPrice = SWISmallMoneyToDouble(pRecord->hold_price);//参考成本价
        pStock->CurVal = 0;//参考市值
        pStock->CurPrice = SWISmallMoneyToDouble(pRecord->current_price);//参考市价
        pStock->ProfitAndLoss = 0;//参考盈亏
      }
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }
  
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::Undo() //委托撤单
{
  ////Checked200412302210!!!
  //Request;
  SWI_WithdrawEntrustRequest swWithdrawReq;
  InitRequest(&swWithdrawReq, sizeof(SWI_WithdrawEntrustRequest), SWI_FUNC_WITHDRAW);
  
  swWithdrawReq.account_type = m_AccType;// 客户帐号类型
  lstrcpyn(swWithdrawReq.account, FAccInfo.Capital, 16);// 客户帐号
  swWithdrawReq.exchange_no = GetExchangeNo(FRequest.Undo.Bourse);// 交易所编号
  int nEntrustSn = StrToIntDef(String(FRequest.Undo.ContractID).Trim(), -1);
  if(nEntrustSn == -1)
    return -1;

  swWithdrawReq.entrust_sn = nEntrustSn;// 委托编号

  if(SetRequest(&swWithdrawReq, sizeof(SWI_WithdrawEntrustRequest)) != 0)
    return -1; 

  //Response;
  SWI_WithdrawEntrustReturn swWithdrawAns;
  if(FSafeSock.RecvAnswer(&swWithdrawAns, sizeof(SWI_WithdrawEntrustReturn)) != 0)
    return -2;
    
  if(swWithdrawAns.return_status < 0)//<0  ------ 撤单失败
  {
    ShowErrorMsg("Undo请求失败", swWithdrawAns.return_status);
    return -1;
  }

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::Buy()
{
  TBourse Bourse;
  if(FRequest.Buy.SecuID[0] == 'H' || FRequest.Buy.SecuID[0] == 'h')
    Bourse = bsSH;
  else if(FRequest.Buy.SecuID[0] == 'S' || FRequest.Buy.SecuID[0] == 's')
    Bourse = bsSZ;
  else
    return -1;

//#ifdef _DEBUG //
  if(lstrcmpi(FRequest.Buy.SecuID, "H510051") == 0)
  {
    FRequest.Buy.Price = 0;
  }
  else if(lstrcmpi(FRequest.Buy.SecuID, "H510181") == 0)
  {
    FRequest.Buy.Price = 0;
  }
//#endif
   
  SWI_AddEntrustReturn swAddAns;   
  if(Order('1', FRequest.Buy.SecuID+1, FRequest.Buy.Num, FRequest.Buy.Price, Bourse, &swAddAns, sizeof(SWI_AddEntrustReturn)) != 0)
    return -1;

  NewAns(1);
  strcpy((*FAnswer)[0].Buy.ContractID, IntToStr(swAddAns.entrust_sn).c_str());

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::Sell()
{
  TBourse Bourse;
  if(FRequest.Buy.SecuID[0] == 'H' || FRequest.Buy.SecuID[0] == 'h')
    Bourse = bsSH;
  else if(FRequest.Buy.SecuID[0] == 'S' || FRequest.Buy.SecuID[0] == 's')
    Bourse = bsSZ;
  else
    return -1;

//#ifdef _DEBUG
  if(lstrcmpi(FRequest.Buy.SecuID, "H510051") == 0)
  {
    FRequest.Buy.Price = 0;
  }
  else if(lstrcmpi(FRequest.Buy.SecuID, "H510181") == 0)
  {
    FRequest.Buy.Price = 0;
  }
//#endif
    
  SWI_AddEntrustReturn swAddAns;  
  if(Order('2', FRequest.Sell.SecuID+1, FRequest.Sell.Num, FRequest.Sell.Price, Bourse, &swAddAns, sizeof(SWI_AddEntrustReturn)) != 0)
    return -1;

  NewAns(1);
  strcpy((*FAnswer)[0].Sell.ContractID, IntToStr(swAddAns.entrust_sn).c_str());

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::Order(char BsType, const char *SecuID, int Num, double Price, TBourse Bourse, void *Block, int Size) //委托
{
  ////Checked200412302210!!!
  //Request;
  SWI_AddEntrustRequest swAddReq;
  InitRequest(&swAddReq, sizeof(SWI_AddEntrustRequest), SWI_FUNC_ADD_ENTRUST);
  
  swAddReq.account_type = m_AccType;// 客户帐号类型
  lstrcpyn(swAddReq.account, FAccInfo.Capital, 16);// 客户帐号
  swAddReq.exchange_no = GetExchangeNo(Bourse);// 交易所编号
  swAddReq.bs_type = BsType;// 买卖类别
  lstrcpyn(swAddReq.security_code, SecuID, 7);// 证券代码
  swAddReq.stock_amount = (long)Num;// 委托数量
  DoubleToSWISmallMoney(swAddReq.price, Price);// 委托价格
  swAddReq.effect_days = 1;//????--- 有效天数
  //SWIMoney   apply_amount;  //申请金额
  //BYTE    mark;             //是否连续赎回 1为连续赎回,0为非连续 确省为0
  //Int		Frozen_no ;        //证券端资金冻结流水号(银证通专用，缺省为0)
  //SWIMoney		fund_amount;  //委托数量(支持开放式基金小数份额)
  //Char(10)    Entrust_sign; //交易签名(缺省为'')
  //SWIMoney    Cash_limit ;  //委托资金额度

  //Response;
  if(SetRequest(&swAddReq, sizeof(SWI_AddEntrustRequest)) != 0)
    return -1;

  if(FSafeSock.RecvAnswer(Block, Size) != 0)
    return -2;
    
  if( ((SWI_AddEntrustReturn *)Block)->return_status < 0) //  <0   委托失败
  {
    ShowErrorMsg("Order请求失败", ((SWI_AddEntrustReturn *)Block)->return_status);
    return -1;
  }

  return 0;
}
//---------------------------------------------------------------------------
void TTrdItf_SYWG::InitRequest(void *Block, WORD Size, WORD FunNo)
{
  memset(Block, 0, Size);
  ((SWI_BlockHead*)Block)->block_size  = Size;
  ((SWI_BlockHead*)Block)->block_type  = SWI_BT_REQUEST;
  ((SWI_BlockHead*)Block)->function_no = FunNo;
  ((SWI_BlockHead*)Block)->cn_id       = m_CnID;
  ((SWI_BlockHead*)Block)->source_dpt  = FSYWGSet.SrcDpt;//????是否需要赋值为第一次握手请求后得到的数据
  ((SWI_BlockHead*)Block)->dest_dpt    = FSYWGSet.DestDpt;//????
}
//---------------------------------------------------------------------------
BYTE TTrdItf_SYWG::GetExchangeNo(TBourse Bourse)
{
  if(Bourse == bsSH)
    return 1;
  else if(Bourse == bsSZ)
    return 2;
  else
    return 0;
}
//---------------------------------------------------------------------------
TBourse TTrdItf_SYWG::GetBourse(BYTE ExchangeNo)
{
  if(ExchangeNo == 1)
    return bsSH;
  else if(ExchangeNo == 2)
    return bsSZ;
  else
     return bsSH;
}
//---------------------------------------------------------------------------
//金额用8字节SQLMONEY来表示，内部表示为__int64，其十进制后四位代表四位小数, 如￥12.32  表示为 123200
double TTrdItf_SYWG::SWIMoneyToDouble(SWIMoney &swMoney)
{
  __int64 nMoney = *(__int64 *)&swMoney;
  return (double(nMoney))/10000.0;
}
//---------------------------------------------------------------------------
void TTrdItf_SYWG::DoubleToSWIMoney(SWIMoney &swMoney, double Money)
{
  __int64 nMoney = Money*10000;
  //memcpy(&swMoney, &nMoney, sizeof(SWIMoney));
  swMoney = *(SWIMoney *)&nMoney;
}
//---------------------------------------------------------------------------
//价格使用LONG来表示，其十进制后三位代表三位小数，如8.18表示为8180
double TTrdItf_SYWG::SWISmallMoneyToDouble(SWISmallMoney &swSMoney)
{
  return (double)swSMoney/1000.0;
}
//---------------------------------------------------------------------------
void TTrdItf_SYWG::DoubleToSWISmallMoney(SWISmallMoney &swSMoney, double Money)
{
  //long lMoney = (int)(Money * 1000.0 + 5)/10 * 10;
  long lMoney = (Money * 10000 + 1)/10;

  swSMoney = lMoney;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::LocalInit(void)
{
  int nRet = FSafeSock.Init(FSYWGSet.ServerAddr, FSYWGSet.ServerNode, FSYWGSet.ServerPort,  \
                            FSYWGSet.ServerIP, FSYWGSet.UseProtocol, FSYWGSet.UseDesencrypt);
  if(nRet != 0)
  {
    ODS("连接AGX服务器失败，请检查网络参数设置");
    return -1;
  }

  //Init ConnectRequest
  //消息头
  SWI_ConnectRequest swReqConnect;
  memset(&swReqConnect, 0, sizeof(SWI_ConnectRequest));
  
  swReqConnect.head.block_size =  sizeof(SWI_ConnectRequest);
  swReqConnect.head.block_type = SWI_BT_CN_REQUEST;//连接请求(交换密钥) block_type == 6
  //swReqConnect.head.cn_id = 0;// 网关连接号
  //swReqConnect.head.source_dpt = 0;// 源营业部编号
  swReqConnect.head.dest_dpt = 0;//FSYWGSet.DestDpt;//目的营业部编号

  //消息体
  swReqConnect.method = (FSYWGSet.UseDesencrypt) ? 1: 0;// 客户端的加密方式（method=1）
  swReqConnect.entrust_method = FSYWGSet.EntrustMethod; // 委托方式（见数据字典说明）-=-????由开发商向申万索取。
  swReqConnect.return_cp = BYTE(0);//客户端希望的返回结构中中文字段的代码页  0 -- MBCS  （CP936简体中文）, 1 -- Unicode(Java客户需要)
  sock_client::AscToHex(swReqConnect.network, FSYWGSet.ClientAddr, 4); //客户端Novell网段号
  sock_client::AscToHex(swReqConnect.address, FSYWGSet.ClientNode, 6); //客户端网卡地址（Novell节点地址）
  swReqConnect.client_major_ver = FSYWGSet.MajorVer;//???? 客户端协议接口主版本号（用于版本协商）
  swReqConnect.client_minor_ver = FSYWGSet.MinorVer;//???? 客户端协议接口次版本号（用于版本协商）
  swReqConnect.key_length = 0;// RSA密钥长度（对method 1, key_length=0）

  SWI_ConnectResponse swCnnAns;
  if(FSafeSock.Connect((char *)&swReqConnect, sizeof(SWI_ConnectRequest), (char *)&swCnnAns, sizeof(SWI_ConnectResponse)) != 0)
  {
    ODS("向AGX发送连接请求（协商加密）失败");
    return -2;
  }

  //Check Response;
  if(swCnnAns.head.block_type != SWI_BT_CN_RESPONSE )// 消息头 block_type == 7
  {
    ODS("向AGX发送连接请求（协商加密）失败");
    return -3;
  }

  //消息头中
  m_CnID = swCnnAns.head.cn_id;
  //m_LocalDpt = swCnnAns.head.dest_dpt;
  //m_KeyLength = swCnnAns.key_length;

  if(FSYWGSet.UseDesencrypt)
  {
    SWSockClient::DesDecrypt("ExpressT", swCnnAns.des_key, 8);
    //lstrcpyn(m_DesKey, swCnnAns.des_key, 8);
    memcpy(m_DesKey, swCnnAns.des_key, 8);
    m_DesKey[8] = '\0';
    FSafeSock.SetKey(m_DesKey);//
  }

  //为了实现"应用程序版本统计"工作……
  //调用"功能号0x801"SWI_QueryCommon
  //SWI_BlockHead.cn_id=0
  //     function_id=1
  //     cmd_buf="产品名称|开发商|版本号|升版日期"
  //     返回：100成功  〈=0失败
/*  SWI_QueryCommon swQryComm;
  memset(&swQryComm, 0 ,sizeof(SWI_QueryCommon));
  
  swQryComm.head.block_size = sizeof(SWI_QueryCommon);
  swQryComm.head.cn_id = 0;
  swQryComm.head.block_type = 1;//请求
  swQryComm.head.function_no = 0x801;
  swQryComm.function_id = 1;
  sprintf(swQryComm.cmd_buf, ""); //???????

  SWI_QueryCommonReturn swQryResult;
  memset(&swQryResult, 0, sizeof(SWI_QueryCommonReturn));

  if(FSafeSock.Request(&swQryComm, sizeof(SWI_QueryCommon), &swQryResult, sizeof(SWI_QueryCommonReturn)) != 0)
    return -1;

  if(swQryResult.return_status != 100)//返回：100成功  〈=0失败
    return -1;
  */
  ODS("连接AGX成功");
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::OpenAccount(char AccountType, char *Account, char *Password)
{
  //Request;
  SWI_OpenAccountRequest swAccReq;
  InitRequest(&swAccReq, sizeof(SWI_OpenAccountRequest), SWI_FUNC_OPEN_ACCOUNT);

  swAccReq.account_type = AccountType;
  lstrcpyn(swAccReq.account, Account, 16);// 客户帐号
  lstrcpyn(swAccReq.pwd, Password, 8);// 交易密码
  //swAccReq.op_code = ;// 操作员工号
  ////////swAccReq.flag = 1;//"特殊条件"判断标志位组合,每一个二进制位对应一个"特殊条件",缺省值为0表示不判断任何"特殊条件"
  //swAccReq.productno = ;//产品信息编号：5位电脑网络中心产品编码+2位子

  if(FSafeSock.SendRequest(&swAccReq, sizeof(SWI_OpenAccountRequest)) != 0)
  {
    ODS("发送SWI_OpenAccountRequest请求失败");
    return -1;
  }

  //Response;
  SWI_OpenAccountReturn swAccAns;
  if(FSafeSock.RecvAnswer(&swAccAns, sizeof(SWI_OpenAccountReturn)) != 0)
  {
    ODS("接收SWI_OpenAccountReturn失败");
    return -2;
  }

  if(swAccAns.return_status <= 0)//>  0  成功
  {
    ShowErrorMsg("OpenAccount请求失败", swAccAns.return_status);
    return -1;
  }

  m_CnID = swAccAns.head.cn_id;//???据说此时Cn_ID才有效

  NewAns(1);
  memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));

  ODS("打开资金帐号：%s成功", Account);
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QueryEntrust(int StartDate, int EndDate)
{
  //Checked200412302210!!!
  SWI_QueryEntrustRequest swEntrustReq;
  InitRequest(&swEntrustReq, sizeof(SWI_QueryEntrustRequest), SWI_FUNC_QUERY_ENTRUST);

  swEntrustReq.account_type = m_AccType;// 客户帐号类型（见数据字典说明）
  lstrcpyn(swEntrustReq.account, FAccInfo.Capital, 16);// 客户帐号
  swEntrustReq.exchange_no = GetExchangeNo(bsSH);//// 交易所编号（见数据字典说明）---????假定为上交所
  swEntrustReq.begin_date = StartDate;// 起始日期（形如：yyyymmdd）
  swEntrustReq.end_date = EndDate;// 结束日期（形如：yyyymmdd）
  swEntrustReq.entrust_sn = 0;// 委托编号（0表示全部）
  //swEntrustReq.security_code = ;// 股票代码（空表示全部）
  swEntrustReq.max_results = 0;//最大查询记录数 ---- ??? 0表示查询所有记录

  if(SetRequest(&swEntrustReq, sizeof(SWI_QueryEntrustRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryEntrustReturn swEntrustAns;
  
  try
  {
    pResult = new TList();
    if(! GetQueryResult(pResult, SWI_FUNC_QUERY_ENTRUST, sizeof(SWI_QueryEntrustResult),  \
                                  &swEntrustAns, sizeof(SWI_QueryEntrustReturn)))//>0 ------ 查询成功
      return -1;

    if(pResult->Count > 0)//有结果集返回
    {
      NewAns(pResult->Count);
      TConsignInfo *pConsInfo = NULL;
      SWI_QueryEntrustResult *pRecord = NULL;
      bool bTodayQuery = (StartDate == EndDate == StrToInt(Date().FormatString("yyyymmdd")));

      for(int i=0; i<pResult->Count; i++)
      {
        pConsInfo = bTodayQuery ? (&(*FAnswer)[i].QryCurCsn.CsgInfo) : (&(*FAnswer)[i].QryHisCsn.CsgInfo);
        pRecord = ((SWI_QueryEntrustResult*)(pResult->Items[i]));

        strcpy(pConsInfo->ContractID, IntToStr(pRecord->entrust_sn).c_str());//合同序号
        pConsInfo->SecuID[0] = (GetBourse(pRecord->exchange_no) == bsSH) ? 'H' : 'S';
        lstrcpyn(pConsInfo->SecuID+1, pRecord->security_code, 7);//证券代码
        lstrcpyn(pConsInfo->SecuDesc, pRecord->security_account, 11);//证券名称
        pConsInfo->Bourse = GetBourse(pRecord->exchange_no);//交易所
        lstrcpyn(pConsInfo->Time, pRecord->entrust_time, 9);//委托时间
        strcpy(pConsInfo->Date, IntToStr(pRecord->entrust_date).c_str());//委托日期
        pConsInfo->Type = (pRecord->bs_type == '1') ? 'B' : 'S';//买卖类别
        //pConsInfo->State = ;///???? 撤单状态---如何赋值 
        pConsInfo->CsnVol = pRecord->stock_ammount;//委托数量
        pConsInfo->TrdVol = pRecord->bargain_ammount;//成交数量

        pConsInfo->CancelVol = 0;
        if(   pRecord->entrust_status == '4'
           || pRecord->entrust_status == '6'
           || (pRecord->entrust_status == '5' && pRecord->bargain_ammount > 0))////'4'---无效委托,'6'---已撤单,'5' ----- 部分撤单
        {
          pConsInfo->CancelVol = pRecord->bargain_ammount - pRecord->stock_ammount;//撤单数量=负值
        }
        //pConsInfo->CancelVol = (pRecord->entrust_status == '6') ? (pRecord->bargain_ammount - pRecord->stock_ammount) : 0; 

        pConsInfo->CsnPrice = SWISmallMoneyToDouble(pRecord->price);//委托价格
        pConsInfo->TrdPrice = SWISmallMoneyToDouble(pRecord->price);//成交价格---???结构体中没有相应字段
      }
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }

  return 0;
}
//---------------------------------------------------------------------------
void TTrdItf_SYWG::ReleaseMemory(char *pMem)
{
  if(pMem != NULL)
  {
    delete [] pMem;
    pMem = NULL;
  }
}
//---------------------------------------------------------------------------
void TTrdItf_SYWG::ReleaseList(TList *pList)
{
  if(pList != NULL)
  {
    char *pRecord = NULL;
    for(int i=0; i<pList->Count; i++)
    {
      pRecord = (char *)pList->Items[i];
      ReleaseMemory(pRecord);
    }
    delete pList;
    pList = NULL;
  }
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::SetRequest(void *ReqBuf, int ReqSize)
{
  int nRet = FSafeSock.SendRequest(ReqBuf, ReqSize);

  if(nRet == 0)//send request successfully
    return 0;
  else if(nRet == 1)//the connection has been gracefully closed,
  {

    ODS("发送请求失败,与服务器的连接可能(空闲超时)已断开，系统正尝试重新连接");

    //Connect agx;
    if(LocalInit() != 0)
      return -1;

    //Open account;
    if(OpenAccount(m_AccType, FAccInfo.Capital, FAccInfo.PW) != 0)
      return -1;

    //ODS("重新连接AGX成功");
    
    if(FSafeSock.SendRequest(ReqBuf, ReqSize) == 0)
      return 0;
    else
    {
      ODS("发送请求失败");
      return -1;
    }
  }
  else//socket error
  {
    ODS("socket error，发送请求失败");
    return -1;
  }
}
//---------------------------------------------------------------------------
/*bool TTrdItf_SYWG::CheckStatus(long Status)
{
  if(Rs == rsEqu)
  {
    if(Status == 0)
      return true;
  }
  else if(Rs == rsMoreEqu)
  {
    if(Status >= 0)
      return true;
  }
  else if(Rs == rsMore)
  {
    if(Status > 0)
      return true;
  }

  return false;
}*/
//---------------------------------------------------------------------------
bool TTrdItf_SYWG::GetQueryResult(TList *pList, WORD FunNo, int RecordSize, void *Answer, int AnsSize)
{
  int nRet = 0;
  char *pRecord = NULL;
  int nNewSize = RecordSize >= AnsSize ? RecordSize : AnsSize;
  if(nNewSize <= 0)
    return false;

  try
  {
    for(;;)//循环接收查询结果
    {
      pRecord = new char[nNewSize];
      nRet = FSafeSock.RecvAnswer(pRecord, nNewSize);
      if(nRet != 0)//因为之前已经请求过，所以不存在超时5分钟的问题
      {
        ReleaseMemory(pRecord);
        return false;
      }

      SWI_QueryResultHead *pHead = (SWI_QueryResultHead*)pRecord;
      if(pHead->head.block_type == SWI_BT_RESULT && pHead->head.function_no == FunNo)//block_type==3 -- 查询结果行   SWI_???Result
      {
        if(pHead->row_no != 0xFFFF)//0xFFFF -- 结果集结束(本条结果数据无效)
        {
          pList->Add(pRecord);
        }
        else
        {
          ReleaseMemory(pRecord);
          continue;
        }
      }
      else if(pHead->head.block_type == SWI_BT_RETURN)//返回的本条记录是SWI_???Return;
      {
        if(pHead->head.function_no == FunNo && ((SWI_QueryReturnHead *)pRecord)->return_status > 0)
        {
          memcpy(Answer, pRecord, AnsSize);
          ReleaseMemory(pRecord);
          return true;
        }
        else
        {
          ReleaseMemory(pRecord);
          return false;
        }
      }
      else//any other errors occurs;
      {
        ReleaseMemory(pRecord);
        return false;
      }
    }

  /*
    //Added 20050109---the following codes are Unreachable;
    //Receive the SWI_???Return;
    nRet = FSafeSock.RecvAnswer(Answer, AnsSize);
    if(nRet == 0)
    {
      if (    ((SWI_QueryReturnHead *)pRecord)->head.block_type == 2
              && ((SWI_QueryReturnHead *)pRecord)->head.function_no == FunNo   \
              && ((SWI_QueryReturnHead *)pRecord)->return_status > 0)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    } */
  }
  catch(...)
  {
    return false;
  }
}

//---------------------------------------------------------------------------
void TTrdItf_SYWG::ShowErrorMsg(char *MsgHead, long ErrorNo)
{
  //Request;
  SWI_ErrorMsgRequest swErrMsgReq;
  InitRequest(&swErrMsgReq, sizeof(SWI_ErrorMsgRequest), SWI_FUNC_ERROR_MSG);

  swErrMsgReq.error_no = ErrorNo;//出错代码

  String sMsgAdded = "";
  if(FSafeSock.SendRequest(&swErrMsgReq, sizeof(SWI_ErrorMsgRequest)) != 0)
  {
    sMsgAdded.sprintf("return_status=%d(请求出错信息解释错误)", ErrorNo);
    goto OUTPUT_ERR_MSG;
  }
    
  //Response;
  SWI_ErrorMsgReturn swErrMsgAns;
  if(FSafeSock.RecvAnswer(&swErrMsgAns, sizeof(SWI_ErrorMsgReturn)) != 0)
  {
    sMsgAdded.sprintf("return_status=%d(请求出错信息解释错误)", ErrorNo);
    goto OUTPUT_ERR_MSG;
  }
    
  if(swErrMsgAns.return_status > 0)//>  0  成功
  {
    swErrMsgAns.error_msg[39] = '\0';
    sMsgAdded = (String)swErrMsgAns.error_msg;
  }
  else
    sMsgAdded.sprintf("return_status=%d, SWI_ErrorMsgReturn.return_status=%d(请求出错信息解释错误)", ErrorNo, swErrMsgAns.return_status);

OUTPUT_ERR_MSG:
  sMsgAdded = (String)MsgHead + sMsgAdded;
  ODS(sMsgAdded.c_str());
}
//---------------------------------------------------------------------------

void TTrdItf_SYWG::CloseLink(void)
{
  FSafeSock.Disconnect();
}
