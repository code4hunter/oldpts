#include <Database.h>
#include <Freeze/Freeze.h>
#include <fstream>
#include <OrderSyncServer.h>

using namespace std;
using namespace IceUtil;

string GetComError(_com_error &e)
{
    _bstr_t bstrSource(e.Source());
    _bstr_t bstrDescription(e.Description());

	ostringstream os;
	//os << "[" << (LPCTSTR)bstrSource << "]" << e.Error() << "," << e.ErrorMessage() << ":" << (LPCTSTR)bstrDescription;
    os << (LPCTSTR)bstrDescription;
	return os.str();
}

namespace PTS2
{
    
Database::Database(const std::string& connString, const Ice::CommunicatorPtr& communicator, const Ice::LoggerPtr& logger):
    _connString(connString),
    _logger(logger),
	_envName("db"),
    _connection(Freeze::createConnection(communicator, _envName)),
	_properties(_connection, "properties"),
    _communicator(communicator)
{
}

int 
Database::getCheckDelay()
{
    return _communicator->getProperties()->getPropertyAsIntWithDefault("Check.Delay", 100);
}

int 
Database::getInitializeDate()
{
	int currDate = 0;
	_ConnectionPtr conn;
    _CommandPtr cmd;
    variant_t recaffected;
    try
    {
        conn.CreateInstance(__uuidof(Connection));
        conn->Open(_connString.c_str(), L"", L"", NULL);

        cmd.CreateInstance(__uuidof(Command));
        cmd->ActiveConnection = conn;
        cmd->CommandText = L"dp_sys_getstrparam";
        cmd->CommandType = adCmdStoredProc;
        cmd->Parameters->Append(cmd->CreateParameter(L"@ownerid", adInteger, adParamInput, 4));
        cmd->Parameters->Append(cmd->CreateParameter(L"@paramname", adVarChar, adParamInput, 128));
        cmd->Parameters->Append(cmd->CreateParameter(L"@value", adVarChar, adParamOutput, 256));
        cmd->Parameters->Item[L"@ownerid"]->Value = (long)-1;
        cmd->Parameters->Item[L"@paramname"]->Value = "curr_date";
        
        cmd->Execute(&recaffected, NULL, adCmdStoredProc);

		std::string value = (LPCSTR)_bstr_t(cmd->Parameters->Item[L"@value"]->Value);
		std::istringstream v(value);
        if (!(v >> currDate) || !v.eof())
        {
            Ice::Warning out(_logger);
            out << "long property curr_date set to non-long value.";
        }

        cmd->ActiveConnection = NULL;
    }
    catch (_com_error &e)
    {
        Ice::Error err(_logger);
        err << "getInitializeDate:" << GetComError(e);
    }

    if (conn && conn->State == adStateOpen)
        conn->Close();

	return currDate;
}

AccountInfoSeq 
Database::getAccounts()
{
    AccountInfoSeq accounts;
    _RecordsetPtr rs;
    _ConnectionPtr conn;

    try
    {
        conn.CreateInstance(__uuidof(Connection));
        conn->Open(_connString.c_str(), L"", L"", NULL);

        string sql;
        sql = "SELECT brkid, idfrombrk, pwd=convert(varchar,pwd), svrname, svrport, sync_type FROM \
                dt_brokeraccounts a, dt_brokers b where a.brkid=b.id and a.status='N'";

        rs.CreateInstance(__uuidof(Recordset));

        rs->CursorType = adOpenStatic;
        rs->CursorLocation = adUseClient;
        rs->Open(sql.c_str(), conn.GetInterfacePtr(), adOpenKeyset, adLockBatchOptimistic, adCmdText);

        while (VARIANT_FALSE == rs->adoEOF)
        {
            AccountInfo info;
            info.account = (LPCSTR)_bstr_t(rs->Fields->Item[L"idfrombrk"]->Value);
            info.password = (LPCSTR)_bstr_t(rs->Fields->Item[L"pwd"]->Value);
            info.host = (LPCSTR)_bstr_t(rs->Fields->Item[L"svrname"]->Value);
            info.port = rs->Fields->Item[L"svrport"]->Value;
            info.brokerId = rs->Fields->Item[L"brkid"]->Value;
            info.syncType = rs->Fields->Item[L"sync_type"]->Value;
            
            accounts.push_back(info);

            rs->MoveNext();
        }

        
    }
    catch (_com_error &e)
    {
        Ice::Error err(_logger);
        err << GetComError(e);
    }
    
    if (conn && conn->State == adStateOpen)
        conn->Close();

    return accounts;    
}
    
OrderInfoSeq 
Database::getOrders(int date, int startIndex, int maxCount)
{
    OrderInfoSeq orders;
    _RecordsetPtr rs;
    _ConnectionPtr conn;

    try
    {
        conn.CreateInstance(__uuidof(Connection));
        conn->Open(_connString.c_str(), L"", L"", NULL);

        ostringstream sql;
        sql << "SELECT * FROM dt_syncorders WHERE id > " << startIndex; // << " and id < " << startIndex+maxCount;

        rs.CreateInstance(__uuidof(Recordset));

        rs->CursorType = adOpenStatic;
        rs->CursorLocation = adUseClient;
        rs->Open(sql.str().c_str(), conn.GetInterfacePtr(), adOpenKeyset, adLockBatchOptimistic, adCmdText);

        while (VARIANT_FALSE == rs->adoEOF)
        {
            OrderInfo info;
			info.seqno = rs->Fields->Item[L"id"]->Value;
			info.type = (LPCSTR)_bstr_t(rs->Fields->Item[L"ordtype"]->Value);
            info.account = (LPCSTR)_bstr_t(rs->Fields->Item[L"acctnum"]->Value);
			info.orderId = (LPCSTR)_bstr_t(rs->Fields->Item[L"ordid"]->Value);
            info.clOrdId = rs->Fields->Item[L"clordid"]->Value;
            info.inst.code = (LPCSTR)_bstr_t(rs->Fields->Item[L"instid"]->Value);
            info.inst.marketId = rs->Fields->Item[L"instidsrc"]->Value;
            std::string ntordtype = (LPCSTR)_bstr_t(rs->Fields->Item[L"ntordtype"]->Value);
            if(ntordtype == "ER")
                info.side = Redeem;
            else if (ntordtype == "EC")
                info.side = Subscribe;
            else 
            {
                std::string temp = (LPCSTR)_bstr_t(rs->Fields->Item[L"side"]->Value);
                if (temp == "S")
                    info.side = Sell;
                else
                    info.side = Buy;
            }
                
            std::string temp = (LPCSTR)_bstr_t(rs->Fields->Item[L"effect"]->Value);
            if (temp == "O")    
                info.effect = Open;
            else if (temp == "C")
                info.effect = Close;
            else
                info.effect = Invalid;
                
            info.orderQty = rs->Fields->Item[L"ordqty"]->Value;
            info.orderPrice = rs->Fields->Item[L"ordpx"]->Value;
            
			temp = (LPCSTR)_bstr_t(rs->Fields->Item[L"date"]->Value);
			info.date = atoi(temp.c_str());

            orders.push_back(info);

            rs->MoveNext();
        }

        
    }
    catch (_com_error &e)
    {
        Ice::Error err(_logger);
        err << "GetOrder:" << GetComError(e);
    }
    
    if (conn && conn->State == adStateOpen)
        conn->Close();

    return orders;
}

void 
Database::orderCanceled(long clordid, const std::string& ordid)
{
    _ConnectionPtr conn;
    _CommandPtr cmd;
    variant_t recaffected;
    try
    {
        conn.CreateInstance(__uuidof(Connection));
        conn->Open(_connString.c_str(), L"", L"", NULL);

        cmd.CreateInstance(__uuidof(Command));
        cmd->ActiveConnection = conn;
        cmd->CommandText = L"dp_order_canceled";
        cmd->CommandType = adCmdStoredProc;
        cmd->Parameters->Append(cmd->CreateParameter(L"@callerid", adInteger, adParamInput, 4));
        cmd->Parameters->Append(cmd->CreateParameter(L"@clordid", adInteger, adParamInput, 4));
        cmd->Parameters->Append(cmd->CreateParameter(L"@ordid", adVarChar, adParamInput, 256));
        cmd->Parameters->Append(cmd->CreateParameter(L"@text", adVarChar, adParamInput, 256));
        cmd->Parameters->Item[L"@callerid"]->Value = (long)1500;
        cmd->Parameters->Item[L"@clordid"]->Value = (long)clordid;
        cmd->Parameters->Item[L"@ordid"]->Value = ordid.c_str();
        cmd->Parameters->Item[L"@text"]->Value = "";
        
        cmd->Execute(&recaffected, NULL, adCmdStoredProc);
        cmd->ActiveConnection = NULL;
    }
    catch (_com_error &e)
    {
        Ice::Error err(_logger);
        err << "OrderCanceled:" << GetComError(e);
    }

    if (conn && conn->State == adStateOpen)
        conn->Close();
}

void 
Database::confirmOrder(long clordid, const std::string& ordid)
{
    _ConnectionPtr conn;
    _CommandPtr cmd;
    variant_t recaffected;
    try
    {
        conn.CreateInstance(__uuidof(Connection));
        conn->Open(_connString.c_str(), L"", L"", NULL);

        cmd.CreateInstance(__uuidof(Command));
        cmd->ActiveConnection = conn;
        cmd->CommandText = L"dp_order_confirm";
        cmd->CommandType = adCmdStoredProc;
        cmd->Parameters->Append(cmd->CreateParameter(L"@callerid", adInteger, adParamInput, 4));
        cmd->Parameters->Append(cmd->CreateParameter(L"@clordid", adInteger, adParamInput, 4));
        cmd->Parameters->Append(cmd->CreateParameter(L"@ordid", adVarChar, adParamInput, 256));
        cmd->Parameters->Append(cmd->CreateParameter(L"@text", adVarChar, adParamInput, 256));
        cmd->Parameters->Item[L"@callerid"]->Value = (long)1500;
        cmd->Parameters->Item[L"@clordid"]->Value = (long)clordid;
        cmd->Parameters->Item[L"@ordid"]->Value = ordid.c_str();
        cmd->Parameters->Item[L"@text"]->Value = "";
        
        cmd->Execute(&recaffected, NULL, adCmdStoredProc);
        cmd->ActiveConnection = NULL;
    }
    catch (_com_error &e)
    {
        Ice::Error err(_logger);
        err << "ConfirmOrder:" << GetComError(e);
    }

    if (conn && conn->State == adStateOpen)
        conn->Close();
}

void 
Database::rejectOrder(long clordid, const std::string& reason)
{
    _ConnectionPtr conn;
    _CommandPtr cmd;
    variant_t recaffected;
    try
    {
        conn.CreateInstance(__uuidof(Connection));
        conn->Open(_connString.c_str(), L"", L"", NULL);

        cmd.CreateInstance(__uuidof(Command));
        cmd->ActiveConnection = conn;
        cmd->CommandText = L"dp_order_reject";
        cmd->CommandType = adCmdStoredProc;
        cmd->Parameters->Append(cmd->CreateParameter(L"@callerid", adInteger, adParamInput, 4));
        cmd->Parameters->Append(cmd->CreateParameter(L"@clordid", adInteger, adParamInput, 4));
        cmd->Parameters->Append(cmd->CreateParameter(L"@reason", adVarChar, adParamInput, 256));
        cmd->Parameters->Item[L"@callerid"]->Value = (long)1500;
        cmd->Parameters->Item[L"@clordid"]->Value = (long)clordid;
        cmd->Parameters->Item[L"@reason"]->Value = reason.c_str();
        
        cmd->Execute(&recaffected, NULL, adCmdStoredProc);
        cmd->ActiveConnection = NULL;
    }
    catch (_com_error &e)
    {
        Ice::Error err(_logger);
        err << "RejectOrder:" << GetComError(e);
    }

    if (conn && conn->State == adStateOpen)
        conn->Close();
}

void 
Database::fillOrder(const TradeInfo& ti)
{
    _ConnectionPtr conn;
    _CommandPtr cmd;
    variant_t recaffected;
    try
    {
        conn.CreateInstance(__uuidof(Connection));
        conn->Open(_connString.c_str(), L"", L"", NULL);

        cmd.CreateInstance(__uuidof(Command));
        cmd->ActiveConnection = conn;
        cmd->CommandText = L"dp_sync_addexecreport";
        cmd->CommandType = adCmdStoredProc;
        cmd->Parameters->Append(cmd->CreateParameter(L"@brokerid", adInteger, adParamInput, 4));
        cmd->Parameters->Append(cmd->CreateParameter(L"@acctnum", adVarChar, adParamInput, 50));
        cmd->Parameters->Append(cmd->CreateParameter(L"@ordid", adVarChar, adParamInput, 256));
        cmd->Parameters->Append(cmd->CreateParameter(L"@exeid", adVarChar, adParamInput, 50));
		cmd->Parameters->Append(cmd->CreateParameter(L"@instid", adVarChar, adParamInput, 20));
		cmd->Parameters->Append(cmd->CreateParameter(L"@ordtype", adVarChar, adParamInput, 10));
        cmd->Parameters->Append(cmd->CreateParameter(L"@cxlqty", adInteger, adParamInput, 4));
        cmd->Parameters->Append(cmd->CreateParameter(L"@exeqty", adInteger, adParamInput, 4));
        cmd->Parameters->Append(cmd->CreateParameter(L"@exepx", adDouble, adParamInput, 4));
        cmd->Parameters->Append(cmd->CreateParameter(L"@exedate", adVarChar, adParamInput, 8));
        cmd->Parameters->Append(cmd->CreateParameter(L"@exetime", adVarChar, adParamInput, 8));
        cmd->Parameters->Append(cmd->CreateParameter(L"@seqno", adVarChar, adParamInput, 128));
        cmd->Parameters->Append(cmd->CreateParameter(L"@remark", adVarChar, adParamInput, 256));

        cmd->Parameters->Item[L"@brokerid"]->Value = (long)ti.brokerId;
        cmd->Parameters->Item[L"@acctnum"]->Value = ti.account.c_str();
        cmd->Parameters->Item[L"@ordid"]->Value = ti.orderId.c_str();
		cmd->Parameters->Item[L"@exeid"]->Value = ti.execId.c_str();
		cmd->Parameters->Item[L"@instid"]->Value = ti.instId.c_str();
		cmd->Parameters->Item[L"@ordtype"]->Value = ti.ordtype.c_str();

		if (ti.volume < 0)
		{
			cmd->Parameters->Item[L"@cxlqty"]->Value = (long)abs(ti.volume);
			cmd->Parameters->Item[L"@exeqty"]->Value = (long)0;
		}
		else
		{
			cmd->Parameters->Item[L"@cxlqty"]->Value = (long)0;
			cmd->Parameters->Item[L"@exeqty"]->Value = (long)ti.volume;
		}

		cmd->Parameters->Item[L"@exepx"]->Value = ti.price;
	
		ostringstream date;
		date << ti.tradeDate;
        cmd->Parameters->Item[L"@exedate"]->Value = date.str().c_str();

		ostringstream time;
		time << (long)(ti.transactTime/10000) << ":" << (long)(ti.transactTime%10000/100) << ":" << (long)(ti.transactTime%100);
        cmd->Parameters->Item[L"@exetime"]->Value = time.str().c_str();
        cmd->Parameters->Item[L"@seqno"]->Value = ti.seqNum.c_str();
        cmd->Parameters->Item[L"@remark"]->Value = "";
        
        cmd->Execute(&recaffected, NULL, adCmdStoredProc);
        cmd->ActiveConnection = NULL;
    }
    catch (_com_error &e)
    {
        Ice::Error err(_logger);
		err << "FillOrder:" << ti.orderId << GetComError(e);
		throw FailureException(__FILE__, __LINE__, "fill order failure.");
    }

    if (conn && conn->State == adStateOpen)
        conn->Close();
}

void 
Database::setProperty(const std::string& name, const std::string& value)
{
    /*
    IceUtil::Mutex::Lock sync(_mutex);
    StringStringDict::iterator p = _properties.find(name);
    if (p != _properties.end())
    {
        p.set(value);            
    }
    else
    {
        _properties.put(StringStringDict::value_type(name, value));
    }
    */
	_ConnectionPtr conn;
    _CommandPtr cmd;
    variant_t recaffected;
    try
    {
        conn.CreateInstance(__uuidof(Connection));
        conn->Open(_connString.c_str(), L"", L"", NULL);

        cmd.CreateInstance(__uuidof(Command));
        cmd->ActiveConnection = conn;
        cmd->CommandText = L"dp_sys_setstrparam";
        cmd->CommandType = adCmdStoredProc;
        cmd->Parameters->Append(cmd->CreateParameter(L"@ownerid", adInteger, adParamInput, 4));
        cmd->Parameters->Append(cmd->CreateParameter(L"@paramname", adVarChar, adParamInput, 128));
        cmd->Parameters->Append(cmd->CreateParameter(L"@value", adVarChar, adParamInput, 256));
        cmd->Parameters->Item[L"@ownerid"]->Value = (long)-100;
        cmd->Parameters->Item[L"@paramname"]->Value = name.c_str();
        cmd->Parameters->Item[L"@value"]->Value = value.c_str();
        
        cmd->Execute(&recaffected, NULL, adCmdStoredProc);
        cmd->ActiveConnection = NULL;
    }
    catch (_com_error &e)
    {
        Ice::Error err(_logger);
        err << "setProperty:" << GetComError(e);
    }

    if (conn && conn->State == adStateOpen)
        conn->Close();

}

void 
Database::setLongProperty(const std::string& name, long value)
{
    ostringstream os;
    os << value;
    
    setProperty(name, os.str());
}

std::string
Database::getProperty(const std::string& name)
{
    /*
    IceUtil::Mutex::Lock sync(_mutex);
    StringStringDict::iterator p = _properties.find(name);
    if (p != _properties.end())
    {
        return p->second;          
    }

    return "";
    */

    std::string value = "";
	_ConnectionPtr conn;
    _CommandPtr cmd;
    variant_t recaffected;
    try
    {
        conn.CreateInstance(__uuidof(Connection));
        conn->Open(_connString.c_str(), L"", L"", NULL);

        cmd.CreateInstance(__uuidof(Command));
        cmd->ActiveConnection = conn;
        cmd->CommandText = L"dp_sys_getstrparam";
        cmd->CommandType = adCmdStoredProc;
        cmd->Parameters->Append(cmd->CreateParameter(L"@ownerid", adInteger, adParamInput, 4));
        cmd->Parameters->Append(cmd->CreateParameter(L"@paramname", adVarChar, adParamInput, 128));
        cmd->Parameters->Append(cmd->CreateParameter(L"@value", adVarChar, adParamOutput, 256));
        cmd->Parameters->Item[L"@ownerid"]->Value = (long)-100;
        cmd->Parameters->Item[L"@paramname"]->Value = name.c_str();
        
        cmd->Execute(&recaffected, NULL, adCmdStoredProc);

		value = (LPCSTR)_bstr_t(cmd->Parameters->Item[L"@value"]->Value);

        cmd->ActiveConnection = NULL;
    }
    catch (_com_error &e)
    {
        Ice::Error err(_logger);
        err << "getProperty:" << GetComError(e);
    }

    if (conn && conn->State == adStateOpen)
        conn->Close();

	return value;
}

double 
Database::getPropertyAsDouble(const std::string& name)
{
    /*
    IceUtil::Mutex::Lock sync(_mutex);
    double value = 0;
    StringStringDict::iterator p = _properties.find(name);
    if (p != _properties.end())
    {
        std::istringstream v(p->second);
        if (!(v >> value) || !v.eof())
        {
            Ice::Warning out(_logger);
            out << "float property " << name << " set to non-float value.";
        }
    }
    return value;
*/

    std::string ret = getProperty(name);

    return atof(ret.c_str());
}

int 
Database::getPropertyAsInt(const std::string& name)
{
    /*
    IceUtil::Mutex::Lock sync(_mutex);
    long value = 0;
    StringStringDict::iterator p = _properties.find(name);
    if (p != _properties.end())
    {
         std::istringstream v(p->second);
        if (!(v >> value) || !v.eof())
        {
            Ice::Warning out(_logger);
            out << "long property " << name << " set to non-long value.";
        }
    }

    return value;*/

    std::string ret = getProperty(name);

    return atoi(ret.c_str());
}

/*
::Ice::StringSeq 
Database::getAllPropertyNames() const
{

    IceUtil::Mutex::Lock sync(_mutex);
    ::Ice::StringSeq result;
    StringStringDict::const_iterator p = _properties.begin();
    while (p != _properties.end())
    {
        result.push_back(p->first);        
        ++p;
    }

    return result;
    
}
*/

void
Database::saveLog(const std::string& message)
{
    SYSTEMTIME st;
    GetLocalTime(&st);	
    long time = st.wHour * 10000 + st.wMinute * 100 + st.wSecond;
    long date = st.wYear * 10000 + st.wMonth * 100 + st.wDay;

    std::ostringstream oss;
    oss << date << "-log.csv";

    std::ifstream infile(oss.str().c_str());
    if (!infile)
    {
        std::ofstream outfile(oss.str().c_str(), ios::app);   
        std::string s = "Ê±¼ä,ÃèÊö\n";

        outfile << s;
    }

    std::ofstream outfile(oss.str().c_str(), ios::app);   
    std::ostringstream os;

    os <<  time << "," << message << "\n";
    outfile << os.str();
}

}