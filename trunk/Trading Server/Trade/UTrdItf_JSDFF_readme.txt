--JSDFF,��֮ͬ��
QryMoney.Balance = StrToFloatDef(lstDD->Strings[INDEX(22)] ,-1);     //�ܱ�֤��
QryMoney.Available = StrToFloatDef(lstDD->Strings[INDEX(10)],-1);    //�����ʽ�

QryStocks.StockInfo->Balance       = lstDD->Strings[INDEX(5)].ToIntDef(0);          //��ֲ�
QryStocks.StockInfo->Available     = lstDD->Strings[INDEX(7)].ToIntDef(0);          //���ֲ�
QryStocks.StockInfo->ProfitAndLoss = StrToFloatDef(lstDD->Strings[INDEX(13)], -1);  //����ӯ��
QryStocks.StockInfo->CostPrice     = StrToFloatDef(lstDD->Strings[INDEX(6)], -1);   //�����
QryStocks.StockInfo->CurPrice      = StrToFloatDef(lstDD->Strings[INDEX(8)], -1);   //������
