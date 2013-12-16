{/*=============================================================================
 * 文 件 名：主推订阅接口相关数据包定义					       *
 * 作    者： Hundsun							       *
 * 修改记录：
 * 20090917  增加定义TOrderRspInfo和TRealRspInfo                               *
 *									       *
===============================================================================}
unit FutuDataStruct;

interface

const
  MATCHSTR_LENGTH = 256;

  ErrNo_Heart          = 1001;   //'已经多次未收到心跳应答，请检查连接是否已断！';
  ErrNo_ReadFEM        = 1002;   //'读取FEM文件错误，操作终止！';
  ErrNo_NotFoundFEM    = 1003;   //'FEM文件未找到，操作终止！';
  Error_NotFoundLicence = 1004;  //Licence文件未找到
  Error_InvalidDate    = 1005;   //'API已过有效期';
  Error_LoadProxyDll   = 1006;   //'代理通讯动态链接库调用失败！'
  Error_GetProcAddress = 1007;   //'GetProcAddress错误！'
  Error_ConnProxy      = 1008;   //'连接代理服务器失败！'

type
  // 单腿行情
  pTMarketInfo = ^TMarketInfo;
  TMarketInfo = record
    contract_code: array[0..12] of Char;   //0 合约代码,
    pre_square_price: Double;              //1 昨日交割结算价
    futu_open_price: Double;               //2 开盘价
    futu_last_price: Double;               //3 最新价格
    buy_high_price: Double;                //4 最高买入价
    buy_high_amount: Integer;              //5 最高买入价买量
    buy_total_amount: Integer;             //6 全部买量
    sale_low_price: Double;                //7 最低卖价价格
    sale_low_amount: Integer;              //8 最低卖价卖量
    sale_total_amount: Integer;            //9 全部卖量
    futu_high_price: Double;               //10 最高价
    futu_low_price: Double;                //11 最低价
    average_price: Double;                 //12 均价
    change_direction: Double;              //13 趋势
    business_amount: Integer;              //14 成交量
    bear_amount: Integer;                  //15 总持量
    business_balance: Double;              //16 成交额
    uplimited_price: Double;               //17 涨停板
    downlimited_price: Double;             //18 跌停板
    futu_exch_type: array[0..2] of Char;   //19 交易类别
    form_buy_price: Double;                //20 组合买入价格
    form_sale_price: Double;               //21 组合卖出价格
    form_buy_amount: Integer;              //22 组合买入数量
    form_sale_amount: Integer;             //23 组合卖出数量
    pre_close_price: Double;               //24 昨日收盘价
    pre_open_interest: Double;             //25 昨日空盘量
    futu_close_price: Double;              //26 今日收盘价
    square_price: Double;                  //27 结算价
    pre_delta: Double;                     //28 昨日虚实度
    curr_delta: Double;                    //29 今日虚实度
    bid_price2: Double;                    //30 买二价
    bid_volume2: Integer;                  //31 买二量
    bid_price3: Double;                    //32 买三价
    bid_volume3: Integer;                  //33 买三量
    bid_price4: Double;                    //34 买四价
    bid_volume4: Integer;                  //35 买四量
    bid_price5: Double;                    //36 买五价
    bid_volume5: Integer;                  //37 买五量
    ask_price2: Double;                    //38 卖二价
    ask_volume2: Integer;                  //39 卖二量
    ask_price3: Double;                    //40 卖三价
    ask_volume3: Integer;                  //41 卖三量
    ask_price4: Double;                    //42 卖四价
    ask_volume4: Integer;                  //43 卖四量
    ask_price5: Double;                    //44 卖五价
    ask_volume5: Integer;                  //45 卖五量
  end;

  // 组合行情
  pTArgMarketInfo = ^TArgMarketInfo;
  TArgMarketInfo = record
    arbicontract_id: array[0..80] of Char; //0 套利合约号
    futu_exch_type: array[0..2] of Char;   //1 交易类别
    first_code: array[0..12] of Char;      //2 第一腿
    second_code: array[0..12] of Char;     //3 第二腿
    arbi_type: Char;                       //4 组合类型1-SPD, 2 -IPS
    buy_price: Double;                     //5 最高买入价
    buy_amount: Integer;                   //6 最高买入价买量
    buy_total_amount: Integer;             //7 全部买量
    sale_price: Double;                    //8 最低卖价价格
    sale_amount: Integer;                  //9 最低卖价卖量
    sale_total_amount: Integer;            //10 全部卖量
    futu_high_price: Double;               //11 最高价
    futu_low_price: Double;                //12 最低价
    uplimited_price: Double;               //13 涨停板价格
    downlimited_price: Double;             //14 跌停板价格
  end;

  //委托反馈信息
  pTOrderRspInfo = ^TOrderRspInfo;
  TOrderRspInfo = record
    entrust_no: Integer; //0 委托号
    futures_account: array[0..20] of Char; //1 交易编码
    futu_exch_type: array[0..10] of Char;  //2 交易所名称
    contract_code: array[0..12] of Char;   //3 合约代码
    entrust_name: array[0..8] of Char;     //4 买卖名称
    direction_name: array[0..8] of Char;   //6 开平名称
    hedge_name: array[0..8] of Char;       //7 套保名称
    fund_account: Integer;                 //8 资金账户
    futu_report_no: array[0..20] of Char;  //9 本地单号
    firm_no: array[0..8] of Char;          //10 会员号
    operator_no: array[0..8] of Char;      //11 操作员号
    client_group: Integer;                 //12 客户类别
    entrust_amount: Integer;               //13 委托数量
    business_total_amount: Integer;        //14 成交总数量
    cacel_amount: Integer;                 //15 撤单数量
    entrust_price: Double;                 //16 委托价格
    entrust_status: Char;                  //17 委托状态
    branch_no: Integer;                    //18 营业部号
    batch_no: Integer;                     //19 委托批号
    futu_entrust_type: Char;               //20 委托类型
    amount_per_hand: Integer;              //21 合约称数
    forceclose_reason: Char;               //22 强平原因
    init_date : Integer;                   //23 交易日期
    curr_time :Integer;                    //24 当前时间
    confirm_no : array[0..20] of Char;     //25 主场单号
    weave_type : Integer;                  //26 组合委托类型
    arbitrage_code : array[0..20] of Char; //27 组合委托类型
    time_condition : Integer;              //28 有效期类型
    volume_condition  : Integer;           //29 成交量类型
    futu_entrust_prop : Integer;           //30 期货委托属性
    frozen_fare : Double;                  //31 冻结总费用
  end;

  //成交反馈信息
  pTRealRspInfo = ^TRealRspInfo;
  TRealRspInfo = record
    entrust_no: Integer;                   //0 委托号
    futures_account: array[0..20] of Char; //1 交易编码
    futu_exch_type: array[0..10] of Char;  //2 交易所名称
    business_no: array[0..20] of Char;     //3 成交编号
    contract_code: array[0..12] of Char;   //4 合约代码
    entrust_name: array[0..8] of Char;     //5 买卖名称
    direction_name: array[0..8] of Char;   //6 开平名称
    business_price: Double;                //7 成交价格
    business_amount: Double;               //8 成交数量
    hedge_name: array[0..8] of Char;       //9 套保名称
    fund_account: Integer;                 //10 资金账户
    futu_report_no: array[0..20] of Char;  //11 本地单号
    firm_no: array[0..8] of Char;          //12 会员号
    operator_no: array[0..8] of Char;      //13 操作员号
    client_group: Integer;                 //14 客户类别
    entrust_amount: Integer;               //15 委托数量
    business_total_amount: Integer;        //16 成交总数量
    cacel_amount: Integer;                 //17 撤单数量
    entrust_price: Double;                 //18 委托价格
    entrust_status: Char;                  //19 委托状态
    branch_no: Integer;                    //20 营业部号
    batch_no: Integer;                     //21 委托批号
    futu_entrust_type: Char;               //22 委托类型
    amount_per_hand: Integer;              //23 合约称数
    forceclose_reason: Char;               //24 强平原因
    init_date : Integer;                   //25 交易日期
    business_time :Integer;                //26 成交时间
    confirm_no : array[0..20] of Char;     //27 主场单号
    frozen_fare : Double;                  //28 冻结总费用
  end;
 
implementation

end.











