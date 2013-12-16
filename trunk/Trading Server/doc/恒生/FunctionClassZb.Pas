unit FunctionClassZb;


interface

uses Classes, Sysutils, Windows, SyncObjs, Dialogs, Packet, Processor, CommonInfo,
       glbdef, HsFunction, HotDef;
type

//周边1.01版部分
  TFunc1200 = class(TProcessor)    //客户校验功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;
  TFunc1201 = class(TProcessor)    //修改密码功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;
  TFunc1202 = class(TProcessor)    //客户退出功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;
  TFunc1203 = class(TProcessor)    //资金密码修改功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;
  TFunc1300 = class(TProcessor)    //检查合约代码功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;
  TFunc1301 = class(TProcessor)    //委托价格功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;
  TFunc1302 = class(TProcessor)    //委托确认功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;
  TFunc1303 = class(TProcessor)    //委托撤单功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;
  TFunc1400 = class(TProcessor)    //查询合约持仓统计(按合约代码、买卖方向汇总统计)功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;
  TFunc1401 = class(TProcessor)    //查询委托功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;
  TFunc1402 = class(TProcessor)    //查询成交功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;
  TFunc1404 = class(TProcessor)    //查询流水功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;
  TFunc1405 = class(TProcessor)    //查资金功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;
  TFunc1406 = class(TProcessor)    //查询行情功能1.01版接口
  private
  protected
    procedure Marshal(Pack: TPack); override;
    procedure SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer); override;
  public
  end;

function GetProcessor(iFunctionId: Integer): TProcessor;
function GetAllFunctionId: string;
function Func1200: TFunc1200;
function Func1201: TFunc1201;
function Func1202: TFunc1202;
function Func1203: TFunc1203;
function Func1300: TFunc1300;
function Func1301: TFunc1301;
function Func1302: TFunc1302;
function Func1303: TFunc1303;
function Func1400: TFunc1400;
function Func1401: TFunc1401;
function Func1402: TFunc1402;
function Func1404: TFunc1404;
function Func1405: TFunc1405;
function Func1406: TFunc1406;

implementation

var
  _Func1200: TFunc1200;
  _Func1201: TFunc1201;
  _Func1202: TFunc1202;
  _Func1203: TFunc1203;
  _Func1300: TFunc1300;
  _Func1301: TFunc1301;
  _Func1302: TFunc1302;
  _Func1303: TFunc1303;
  _Func1400: TFunc1400;
  _Func1401: TFunc1401;
  _Func1402: TFunc1402;
  _Func1404: TFunc1404;
  _Func1405: TFunc1405;
  _Func1406: TFunc1406;

function GetAllFunctionId: string;
begin
 Result := '1200,1201,1202,1203,1300,1301,1302,1303,1400,1401,1402,1404,1405,1406,';
end;

function GetProcessor(iFunctionId: Integer): TProcessor;
var
  Processor: TProcessor;
begin
    case iFunctionId of
    1200:
      begin
        Processor := TFunc1200.Create;
        Processor.Name := '客户校验';
        processor.AsFunctionId := 31751;
        processor.FunctionId := 1200;
      end;
    1201:
      begin
        Processor := TFunc1201.Create;
        Processor.Name := '修改密码';
        processor.AsFunctionId := 31752;
        processor.FunctionId := 1201;
      end;
    1202:
      begin
        Processor := TFunc1202.Create;
        Processor.Name := '客户退出';
        processor.AsFunctionId := 31753;
        processor.FunctionId := 1202;
      end;
    1203:
      begin
        Processor := TFunc1203.Create;
        Processor.Name := '资金密码修改';
        processor.AsFunctionId := 31754;
        processor.FunctionId := 1203;
      end;
    1300:
      begin
        Processor := TFunc1300.Create;
        Processor.Name := '检查合约代码';
        processor.AsFunctionId := 31755;
        processor.FunctionId := 1300;
      end;
    1301:
      begin
        Processor := TFunc1301.Create;
        Processor.Name := '委托价格';
        processor.AsFunctionId := 31756;
        processor.FunctionId := 1301;
      end;
    1302:
      begin
        Processor := TFunc1302.Create;
        Processor.Name := '委托确认';
        processor.AsFunctionId := 31757;
        processor.FunctionId := 1302;
      end;
    1303:
      begin
        Processor := TFunc1303.Create;
        Processor.Name := '委托撤单';
        processor.AsFunctionId := 31758;
        processor.FunctionId := 1303;
      end;
    1400:
      begin
        Processor := TFunc1400.Create;
        Processor.Name := '查询合约持仓统计(按合约代码、买卖方向汇总统计)';
        processor.AsFunctionId := 31763;
        processor.FunctionId := 1400;
      end;
    1401:
      begin
        Processor := TFunc1401.Create;
        Processor.Name := '查询委托';
        processor.AsFunctionId := 31764;
        processor.FunctionId := 1401;
      end;
    1402:
      begin
        Processor := TFunc1402.Create;
        Processor.Name := '查询成交';
        processor.AsFunctionId := 31765;
        processor.FunctionId := 1402;
      end;
    1404:
      begin
        Processor := TFunc1404.Create;
        Processor.Name := '查询流水';
        processor.AsFunctionId := 31767;
        processor.FunctionId := 1404;
      end;
    1405:
      begin
        Processor := TFunc1405.Create;
        Processor.Name := '查资金';
        processor.AsFunctionId := 31768;
        processor.FunctionId := 1405;
      end;
    1406:
      begin
        Processor := TFunc1406.Create;
        Processor.Name := '查询行情';
        processor.AsFunctionId := 31769;
        processor.FunctionId := 1406;
      end;
    else
       Processor := TProcessor.Create;
    end;
    Result := Processor;
End;

function Func1200: TFunc1200;
begin
  if _Func1200 = nil then _Func1200 := TFunc1200.Create;
  Result := _Func1200;
end;
procedure TFunc1200.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 9, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('vc_host_name');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_exchange_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddField('vc_password');
    Pack.Sections[0].AddField('c_passtype');
    Pack.Sections[0].AddField('vc_mac');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(Request.sHost_Name);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  7, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  8, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  9, _MaskChar));
  end;
end;

procedure TFunc1200.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
var
  i:Integer;
begin
  if (rUnpack <> nil) then
  begin
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('l_customer_id').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('vc_customer_name').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('c_enable_tran').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('c_enable_inipassword').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('c_enable_tabvalidate').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('c_have_message').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('l_summary').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('l_first_date').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('l_today_date').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('vc_last_ip').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('vc_last_mac').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('c_last_entrust_way').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('l_last_date').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('l_last_time').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('vc_rights').AsString + _MaskChar+ LENE_END_CHAR;
    for i:= 0 to rUnpack.Sections[1].RecordCount -1 do
    begin
      LAnswer^.aAnswer[i+1] := rUnpack.Sections[1].FieldByname('c_exchange_type').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_exchange_name').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_account').AsString + _MaskChar + LENE_END_CHAR;
      rUnpack.Sections[1].Next
    end;
    LAnswer^.iAnswerLines := rUnpack.Sections[1].RecordCount;
  end;
end;

function Func1201: TFunc1201;
begin
  if _Func1201 = nil then _Func1201 := TFunc1201.Create;
  Result := _Func1201;
end;
procedure TFunc1201.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 7, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_exchange_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddField('vc_password');
    Pack.Sections[0].AddField('vc_newpassword');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  7, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  8, _MaskChar));
  end;
end;

procedure TFunc1201.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
begin
end;

function Func1202: TFunc1202;
begin
  if _Func1202 = nil then _Func1202 := TFunc1202.Create;
  Result := _Func1202;
end;
procedure TFunc1202.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 5, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_account_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
  end;
end;

procedure TFunc1202.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
begin
end;

function Func1203: TFunc1203;
begin
  if _Func1203 = nil then _Func1203 := TFunc1203.Create;
  Result := _Func1203;
end;
procedure TFunc1203.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 8, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_exchange_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddField('dicpassword');
    Pack.Sections[0].AddField('drawpassword');
    Pack.Sections[0].AddField('newpassword');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  7, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  8, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  9, _MaskChar));
  end;
end;

procedure TFunc1203.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
begin
end;

function Func1300: TFunc1300;
begin
  if _Func1300 = nil then _Func1300 := TFunc1300.Create;
  Result := _Func1300;
end;
procedure TFunc1300.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 7, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_account_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddField('c_codetype');
    Pack.Sections[0].AddField('vc_code');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  7, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  8, _MaskChar));
  end;
end;

procedure TFunc1300.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
var
  i:Integer;
begin
  if (rUnpack <> nil) then
  begin
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('c_exchange_type').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('vc_report_code').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('vc_contract_name').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('vc_exchange_account').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_enable_balance').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_fetch_balance').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_price_step').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('c_price_unit').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('l_buy_amount').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('l_sale_amount').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('l_realtime_buy_amount').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('l_realtime_sale_amount').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('c_drop_flag').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('c_hedge_flag').AsString + _MaskChar+ LENE_END_CHAR;
    for i:= 0 to rUnpack.Sections[1].RecordCount -1 do
    begin
      LAnswer^.aAnswer[i+1] := rUnpack.Sections[1].FieldByname('vc_report_code').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_square_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_buy_high_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_buy_high_amount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_buy_total_amount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_sale_low_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_sale_low_amount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_sale_total_amount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_open_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_high_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_low_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_last_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_average_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_direction').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_busin_amount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_bear_amount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_busin_bala').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_uplimited_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_downlimited_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_amount_per_hand').AsString + _MaskChar + LENE_END_CHAR;
      rUnpack.Sections[1].Next
    end;
    LAnswer^.iAnswerLines := rUnpack.Sections[1].RecordCount;
  end;
end;

function Func1301: TFunc1301;
begin
  if _Func1301 = nil then _Func1301 := TFunc1301.Create;
  Result := _Func1301;
end;
procedure TFunc1301.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 11, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_account_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddField('c_exchange_type');
    Pack.Sections[0].AddField('vc_report_code');
    Pack.Sections[0].AddField('c_direction');
    Pack.Sections[0].AddField('c_bs');
    Pack.Sections[0].AddField('en_price');
    Pack.Sections[0].AddField('c_hedge');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  7, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  8, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  9, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  10, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  11, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  12, _MaskChar));
  end;
end;

procedure TFunc1301.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
begin
  if (rUnpack <> nil) then
  begin
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('l_enable_amount').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('l_min_unit').AsString + _MaskChar+ LENE_END_CHAR;
  end;
end;

function Func1302: TFunc1302;
begin
  if _Func1302 = nil then _Func1302 := TFunc1302.Create;
  Result := _Func1302;
end;
procedure TFunc1302.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 14, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_account_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddField('vc_password');
    Pack.Sections[0].AddField('c_exchange_type');
    Pack.Sections[0].AddField('vc_report_code');
    Pack.Sections[0].AddField('c_direction');
    Pack.Sections[0].AddField('c_bs');
    Pack.Sections[0].AddField('en_price');
    Pack.Sections[0].AddField('l_amount');
    Pack.Sections[0].AddField('en_appoint_price');
    Pack.Sections[0].AddField('c_hedge');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  7, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  8, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  9, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  10, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  11, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  12, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  13, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  14, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  15, _MaskChar));
  end;
end;

procedure TFunc1302.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
begin
  if (rUnpack <> nil) then
  begin
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('l_serial_no').AsString + _MaskChar+ LENE_END_CHAR;
  end;
end;

function Func1303: TFunc1303;
begin
  if _Func1303 = nil then _Func1303 := TFunc1303.Create;
  Result := _Func1303;
end;
procedure TFunc1303.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 7, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_account_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddField('vc_password');
    Pack.Sections[0].AddField('l_entrust_no');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  7, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  8, _MaskChar));
  end;
end;

procedure TFunc1303.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
begin
end;

function Func1400: TFunc1400;
begin
  if _Func1400 = nil then _Func1400 := TFunc1400.Create;
  Result := _Func1400;
end;
procedure TFunc1400.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 13, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_account_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddField('c_exchange_type');
    Pack.Sections[0].AddField('vc_report_code');
    Pack.Sections[0].AddField('c_bs');
    Pack.Sections[0].AddField('c_query_dic');
    Pack.Sections[0].AddField('l_request_col');
    Pack.Sections[0].AddField('vc_request_str');
    Pack.Sections[0].AddField('c_query_type');
    Pack.Sections[0].AddField('c_password');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  7, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  8, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  9, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  10, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  11, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  12, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  13, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  14, _MaskChar));
  end;
end;

procedure TFunc1400.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
var
  i:Integer;
begin
  if (rUnpack <> nil) then
  begin
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_current_balance').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_enable_balance').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_fetch_balance').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_froze_balance').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_realtime_hold_balanceA').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_hold_profit_f').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_rights').AsString + _MaskChar+ LENE_END_CHAR;
    for i:= 0 to rUnpack.Sections[1].RecordCount -1 do
    begin
      LAnswer^.aAnswer[i+1] := rUnpack.Sections[1].FieldByname('vc_request_str').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('c_exchange_type').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_account').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_report_code').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_code_name').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('c_bs_type').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('lcurrentamount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('lenabledamount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_last_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('eholdprofit').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('eholdbalance').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('ltodayopenamount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('lpredropamount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_avg_open_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('eholdprofit_float').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('lrealamount').AsString + _MaskChar + LENE_END_CHAR;
      rUnpack.Sections[1].Next
    end;
    LAnswer^.iAnswerLines := rUnpack.Sections[1].RecordCount;
  end;
end;

function Func1401: TFunc1401;
begin
  if _Func1401 = nil then _Func1401 := TFunc1401.Create;
  Result := _Func1401;
end;
procedure TFunc1401.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 13, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_account_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddField('l_start_date');
    Pack.Sections[0].AddField('l_end_date');
    Pack.Sections[0].AddField('c_exchange_type');
    Pack.Sections[0].AddField('vc_report_code');
    Pack.Sections[0].AddField('c_query_dic');
    Pack.Sections[0].AddField('l_request_col');
    Pack.Sections[0].AddField('vc_request_str');
    Pack.Sections[0].AddField('vc_status');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  7, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  8, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  9, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  10, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  11, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  12, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  13, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  14, _MaskChar));
  end;
end;

procedure TFunc1401.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
var
  i:Integer;
begin
  if (rUnpack <> nil) then
  begin
    LAnswer^.sRequest := LAnswer^.sRequest + _MaskChar +  LENE_END_CHAR;
    for i:= 0 to rUnpack.Sections[1].RecordCount -1 do
    begin
      LAnswer^.aAnswer[i+1] := rUnpack.Sections[1].FieldByname('vc_request_str').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_detail_serial').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('c_exchange_type').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_account').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_report_code').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_contract_name').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('c_direction').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('c_bs').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_amount_t').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_rpt_time').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('c_status').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_status_name').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_busin_amount_t').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_cancel_amount_t').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_hold_balance').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_amount_per_hand').AsString + _MaskChar + LENE_END_CHAR;
      rUnpack.Sections[1].Next
    end;
    LAnswer^.iAnswerLines := rUnpack.Sections[1].RecordCount;
  end;
end;

function Func1402: TFunc1402;
begin
  if _Func1402 = nil then _Func1402 := TFunc1402.Create;
  Result := _Func1402;
end;
procedure TFunc1402.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 13, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_account_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddField('l_start_date');
    Pack.Sections[0].AddField('l_end_date');
    Pack.Sections[0].AddField('c_exchange_type');
    Pack.Sections[0].AddField('vc_report_code');
    Pack.Sections[0].AddField('c_query_dic');
    Pack.Sections[0].AddField('l_request_col');
    Pack.Sections[0].AddField('vc_request_str');
    Pack.Sections[0].AddField('c_query_type');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  7, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  8, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  9, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  10, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  11, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  12, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  13, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  14, _MaskChar));
  end;
end;

procedure TFunc1402.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
var
  i:Integer;
begin
  if (rUnpack <> nil) then
  begin
    LAnswer^.sRequest := LAnswer^.sRequest + _MaskChar +  LENE_END_CHAR;
    for i:= 0 to rUnpack.Sections[1].RecordCount -1 do
    begin
      LAnswer^.aAnswer[i+1] := rUnpack.Sections[1].FieldByname('vc_request_str').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_date').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('c_exchange_type').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_account').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_report_code').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_contract_name').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('c_direction').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('c_bs').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_amount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_business_time').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_flag').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_business_name').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_entrust_detail').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_fare').AsString + _MaskChar + LENE_END_CHAR;
      rUnpack.Sections[1].Next
    end;
    LAnswer^.iAnswerLines := rUnpack.Sections[1].RecordCount;
  end;
end;

function Func1404: TFunc1404;
begin
  if _Func1404 = nil then _Func1404 := TFunc1404.Create;
  Result := _Func1404;
end;
procedure TFunc1404.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 10, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_account_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddField('l_start_date');
    Pack.Sections[0].AddField('l_end_date');
    Pack.Sections[0].AddField('c_query_dic');
    Pack.Sections[0].AddField('l_request_col');
    Pack.Sections[0].AddField('vc_request_str');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  7, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  8, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  9, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  10, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  11, _MaskChar));
  end;
end;

procedure TFunc1404.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
var
  i:Integer;
begin
  if (rUnpack <> nil) then
  begin
    LAnswer^.sRequest := LAnswer^.sRequest + _MaskChar +  LENE_END_CHAR;
    for i:= 0 to rUnpack.Sections[1].RecordCount -1 do
    begin
      LAnswer^.aAnswer[i+1] := rUnpack.Sections[1].FieldByname('vc_request_str').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_date').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_flag').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('business_name').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_pre_balance').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_post_balance').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('c_op_way').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('vc_dic_caption').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('t_occur_bala').AsString + _MaskChar + LENE_END_CHAR;
      rUnpack.Sections[1].Next
    end;
    LAnswer^.iAnswerLines := rUnpack.Sections[1].RecordCount;
  end;
end;

function Func1405: TFunc1405;
begin
  if _Func1405 = nil then _Func1405 := TFunc1405.Create;
  Result := _Func1405;
end;
procedure TFunc1405.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 5, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_exchange_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
  end;
end;

procedure TFunc1405.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
begin
  if (rUnpack <> nil) then
  begin
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_current_balance').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_enable_balance').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_fetch_balance').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_froze_balance').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_realtime_hold_balanceA').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_hold_profit_f').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_rights').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_interest_balance').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_hold_profit').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_float_rights').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_drop_profit').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_drop_profit_f').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('en_fare').AsString + _MaskChar+ LENE_END_CHAR;
  end;
end;

function Func1406: TFunc1406;
begin
  if _Func1406 = nil then _Func1406 := TFunc1406.Create;
  Result := _Func1406;
end;
procedure TFunc1406.Marshal(Pack: TPack);
begin
  if AsFunctionId > 0 then
  begin
    Pack.Sections[0].SetRange( 7, 1);
    Pack.Sections[0].AddField('version');
    Pack.Sections[0].AddField('vc_station_address');
    Pack.Sections[0].AddField('c_entrust_way');
    Pack.Sections[0].AddField('c_account_type');
    Pack.Sections[0].AddField('vc_account');
    Pack.Sections[0].AddField('c_exchange_type');
    Pack.Sections[0].AddField('vc_report_code');
    Pack.Sections[0].AddValue('1');
    Pack.Sections[0].AddValue(Request.sIPAddress);
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  4, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  5, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  6, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  7, _MaskChar));
    Pack.Sections[0].AddValue(GetCol(Request.sRequest,  8, _MaskChar));
  end;
end;

procedure TFunc1406.SetAnswer(rUnpack: TUnpack; LAnswer: PAnswer);
var
  i:Integer;
begin
  if (rUnpack <> nil) then
  begin
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('vc_report_code').AsString + _MaskChar;
    LAnswer^.sRequest := LAnswer^.sRequest
      + rUnpack.Sections[0].FieldByname('vc_contract_name').AsString + _MaskChar+ LENE_END_CHAR;
    for i:= 0 to rUnpack.Sections[1].RecordCount -1 do
    begin
      LAnswer^.aAnswer[i+1] := rUnpack.Sections[1].FieldByname('vc_report_code').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_square_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_buy_high_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_buy_high_amount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_buy_total_amount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_sale_low_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_sale_low_amount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_sale_total_amount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_open_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_high_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_low_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_last_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_average_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_direction').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_busin_amount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('l_bear_amount').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_busin_bala').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_uplimited_price').AsString + _MaskChar;
      LAnswer^.aAnswer[i+1] := LAnswer^.aAnswer[i+1]+rUnpack.Sections[1].FieldByname('en_downlimited_price').AsString + _MaskChar + LENE_END_CHAR;
      rUnpack.Sections[1].Next
    end;
    LAnswer^.iAnswerLines := rUnpack.Sections[1].RecordCount;
  end;
end;


initialization
finalization
    if _Func1200<> nil then begin _Func1200.Free; _Func1200:= nil; end;
    if _Func1201<> nil then begin _Func1201.Free; _Func1201:= nil; end;
    if _Func1202<> nil then begin _Func1202.Free; _Func1202:= nil; end;
    if _Func1203<> nil then begin _Func1203.Free; _Func1203:= nil; end;
    if _Func1300<> nil then begin _Func1300.Free; _Func1300:= nil; end;
    if _Func1301<> nil then begin _Func1301.Free; _Func1301:= nil; end;
    if _Func1302<> nil then begin _Func1302.Free; _Func1302:= nil; end;
    if _Func1303<> nil then begin _Func1303.Free; _Func1303:= nil; end;
    if _Func1400<> nil then begin _Func1400.Free; _Func1400:= nil; end;
    if _Func1401<> nil then begin _Func1401.Free; _Func1401:= nil; end;
    if _Func1402<> nil then begin _Func1402.Free; _Func1402:= nil; end;
    if _Func1404<> nil then begin _Func1404.Free; _Func1404:= nil; end;
    if _Func1405<> nil then begin _Func1405.Free; _Func1405:= nil; end;
    if _Func1406<> nil then begin _Func1406.Free; _Func1406:= nil; end;
end.
