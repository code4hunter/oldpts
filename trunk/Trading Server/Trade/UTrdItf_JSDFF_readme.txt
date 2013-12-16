--JSDFF,不同之处
QryMoney.Balance = StrToFloatDef(lstDD->Strings[INDEX(22)] ,-1);     //总保证金
QryMoney.Available = StrToFloatDef(lstDD->Strings[INDEX(10)],-1);    //可用资金

QryStocks.StockInfo->Balance       = lstDD->Strings[INDEX(5)].ToIntDef(0);          //买持仓
QryStocks.StockInfo->Available     = lstDD->Strings[INDEX(7)].ToIntDef(0);          //卖持仓
QryStocks.StockInfo->ProfitAndLoss = StrToFloatDef(lstDD->Strings[INDEX(13)], -1);  //浮动盈亏
QryStocks.StockInfo->CostPrice     = StrToFloatDef(lstDD->Strings[INDEX(6)], -1);   //买均价
QryStocks.StockInfo->CurPrice      = StrToFloatDef(lstDD->Strings[INDEX(8)], -1);   //卖均价
