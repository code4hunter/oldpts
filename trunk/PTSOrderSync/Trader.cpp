#include <Trader.h>
#include <OrderSyncServer.h>
#include <IceUtil/Options.h>

using namespace std;
namespace PTS2
{
    
Trader::Trader(const AccountInfo& acctInfo, const Ice::LoggerPtr& logger):
	_acctInfo(acctInfo),
    _logger(logger)
{
	_isConnected = false;
    _itftrd = new TItfTrd();
}

Trader::~Trader()
{    
    cout << "~TradeAdapter" << endl;
    if (_itftrd)
    {
        _itftrd->Close();
        delete _itftrd;
        _itftrd = NULL;
    }    
}

void 
Trader::destroy()
{
    IceUtil::Mutex::Lock lock(_mutex); 

    _isConnected = false;
    _cancelOrders.clear();
}

void 
Trader::check()
{

	TMoneyInfo info = {};
    int ret = _itftrd->QryMoney(motRMB, info);
    if (ret != 0)
    {
        char error[256] = {0};
        char sender[128] = {0};
        _isConnected = false;
        _itftrd->GetLastError(error, 256, sender, 128);
    }

    if (!checkConnect())
    {
        throw FailureException(__FILE__, __LINE__, "Not connected to the server.");
    }
}
    
std::string 
Trader::sendOrder(const OrderInfo& order)
{
    IceUtil::Mutex::Lock lock(_mutex);
    if (!checkConnect())
    {
        throw FailureException(__FILE__, __LINE__, "Not connected to the server.");
    }

    char orderId[128] = {0};
    market_type marketType;
    order_type orderType;
    switch (order.inst.marketId)
    {
        case 101 : marketType = mtSHA; break;
        case 102 : marketType = mtSZA; break;
        case 103 : marketType = mtFSH; break;
        case 104 : marketType = mtFDL; break;
        case 105 : marketType = mtFZZ; break;
        case 106 : marketType = mtJJS; break;
        case 107 : marketType = mtHK; break;
        default : marketType = mtNo;
    }
    
    if (order.inst.marketId != 101 && order.inst.marketId != 102)
    {
        if (order.side == Buy && order.effect == Open)
            orderType = otOpenBuy;
        else if (order.side == Sell && order.effect == Open)
            orderType = otOpenSell;
        else if (order.side == Buy && order.effect == Close)
        {
            if (order.inst.marketId == 103 && order.isTodayQty)
                orderType = otCloseTodayBuy;
            else
                orderType = otCloseBuy;
        }
        else if (order.side == Sell && order.effect == Close)
        {
            if (order.inst.marketId == 103 && order.isTodayQty)
                orderType = otCloseTodaySell;
            else
                orderType = otCloseSell;
        }        
    }
    else
    {
        if (order.side == Buy)
            orderType = otBuy;
        else if (order.side == Sell)
            orderType = otSell;
        else if (order.side == Subscribe)
            orderType = otETFSub;
        else if (order.side == Redeem)
            orderType = otETFRed;
    }

    int ret = _itftrd->Order(order.inst.code.c_str(), order.orderPrice, order.orderQty, 
                             marketType, orderType, orderId, 128);
    if (ret !=0)
    {
        char error[256] = {0};
        char sender[128] = {0};
        int code = _itftrd->GetLastError(error, 256, sender, 128);

		if(ret<=ERR_REMOTE_SEND_FAILED && ret>=ERR_TRDSVR_OTHER_FAILED)
		{
			_isConnected = false;
			
			if (!checkConnect())
			{
				throw FailureException(__FILE__, __LINE__, "Can not reconnect to the server.");
			}
			else
			{
				//resend order
				ret = _itftrd->Order(order.inst.code.c_str(), order.orderPrice, order.orderQty, 
                             marketType, orderType, orderId, 128);
				if (ret !=0)
				{
					char error[256] = {0};
					char sender[128] = {0};
					int code = _itftrd->GetLastError(error, 256, sender, 128);

					check();
					if (!checkConnect())
					{
						throw FailureException(__FILE__, __LINE__, "Can not reconnect to the server.");
					}

					throw FailureException(__FILE__, __LINE__, "Send order failure: " + std::string(error));
				}
			}
		}

		if( ret == -1 )
		{
			_isConnected = false;
		}

		if (!checkConnect())
		{
			throw FailureException(__FILE__, __LINE__, "Can not reconnect to the server.");
		}

        throw FailureException(__FILE__, __LINE__, "Send order failure: " + std::string(error));
    }

    
    return std::string(orderId);
}

void
Trader::cancelOrder(const std::string& orderId, const std::string& reason)
{
    IceUtil::Mutex::Lock lock(_mutex);
    if (!checkConnect())
    {
        throw FailureException(__FILE__, __LINE__, "Not connected to the server.");
    }

    int ret = _itftrd->Undo(orderId.c_str(), mtNo);
    if (_isSyncCancelOrder)
    {
        _cancelOrders.push_back(orderId);
        Ice::Trace out(_logger, "TradeAdapter");
        out << "cancel order:" << orderId << "," << reason;
    }        
	
	if(ret<=ERR_REMOTE_SEND_FAILED && ret>=ERR_TRDSVR_OTHER_FAILED)
	{
		_isConnected = false;
		
		if (!checkConnect())
		{
			throw FailureException(__FILE__, __LINE__, "Can not reconnect to the server.");
		}
		else
		{
			//resend order
			ret = _itftrd->Undo(orderId.c_str(), mtNo);
		}
	}

	if( ERR_UNDO_CANNOT_CANCLE== ret )
	{
		Sleep(800);
		ret = _itftrd->Undo(orderId.c_str(), mtNo);
	}

	if (ret != 0 && ret != ERR_UNDO_ALREADY_FILLED && ret != ERR_UNDO_REPEAL && 
        ret != ERR_UNDO_ALREADY_CANCLED)
    {
        char error[256] = {0};
        char sender[128] = {0};
        _itftrd->GetLastError(error, 256, sender, 128);
        std::ostringstream os;
        os << "Cancel order failure: " << error << "," << orderId << "," << ret << "," << reason;
        throw FailureException(__FILE__, __LINE__, os.str());
    }
}

OrderStatusInfo 
Trader::queryOrder(const std::string& orderId)
{
    IceUtil::Mutex::Lock lock(_mutex);
    
    if (!checkConnect())
    {
        throw FailureException(__FILE__, __LINE__, "Not connected to the server.");
    }    
    
    OrderStatusInfo info = {}; 
    TOrderInfo *oi;
    int num = 1;
    int ret = _itftrd->QryOrder(orderId.c_str(), "", &oi, num);
    if (ret != 0 || num != 1)
    {
        throw FailureException(__FILE__, __LINE__, "Query order failed.");
    }
    
    info.orderQty = oi[0].CsnVol;
    info.tradeQty = oi[0].TrdVol;
    info.cancelQty = oi[0].State == osyf ? -abs(oi[0].CsnVol) : -abs(oi[0].CancelVol);
    info.orderPrice = oi[0].CsnPrice;
    info.tradePrice = oi[0].TrdPrice;    
    
    switch(oi[0].State)
    {
    case osyb: //已报(已经报了,但没有任何成交,等待成交中...)
        info.status = Confirmed;
        break;
    case osdc: //待撤(撤单命令已下等待撤单)
    case osbw: //部撤(确定状态,部分撤销，部分成交)
    case osbc: //部成(已经有成交了,正在成交中...
        info.status = Partial;
        break;
    case osyf: //已废(确定状态,系统撤单)
    case osyc: //已撤(确定状态,全部撤销了)
        info.status = Canceled;
        break;
    case oscj: //已成(确定状态,完全成交)
        info.status = Filled;
        break;
    default : 
        info.status = New;
    }

    _itftrd->FreeAnswer(oi);

    return info;
}

TradeInfoSeq 
Trader::getTradeInfos(const std::string& seqNum, int maxCount)
{
    TradeInfoSeq result;
    IceUtil::Mutex::Lock lock(_mutex);
    
    if (!checkConnect())
    {
        return result;
    }
        
    int num = maxCount;
    TTradeInfo *ti;
    int ret = _itftrd->QryTrade("", seqNum.c_str(), &ti, num);
    if (ret != 0)
    {
        _isConnected = false;
        Ice::Error out(_logger);
        out << "Query execute reports failed: " << ret;
        return result;
    }

    for (int i = 0; i < num; i++)
    {
        TradeInfo info = {};
		info.brokerId = _acctInfo.brokerId;
		info.account = _acctInfo.account;
		info.instId = ti[i].SecuID;
        info.orderId = ti[i].ContractID;
        info.execId = ti[i].TrdID;
		info.ordtype = getOrderType(ti[i].Type);
        info.tradeDate = ti[i].Date;
        info.transactTime = ti[i].Time;
        info.volume = ti[i].Vol;
        info.price = ti[i].Price;
        info.seqNum = ti[i].SeqNum;
        result.push_back(info);
    } 
    
    _itftrd->FreeAnswer(ti);
    
    if (_isSyncCancelOrder)
    {
        std::list<std::string>::iterator p = _cancelOrders.begin();
        while (p != _cancelOrders.end())
        {
            TOrderInfo *oi;
            int num = 1;
            int ret = _itftrd->QryOrder((*p).c_str(), "", &oi, num);
            if (ret!=0)
            {
                _isConnected = false;
                Ice::Error out(_logger);
                out << "Query order failed: ";
                break;
            }
            
            //if (num == 1 && (oi[0].State == osbw || oi[0].State == osyc || oi[0].State == osyf) && 
            //    oi[0].CsnVol == oi[0].TrdVol+abs(oi[0].CancelVol))
            if(num > 0 && (oi[0].State == osyf || (oi[0].CsnVol == oi[0].TrdVol+abs(oi[0].CancelVol))))
            {
                TradeInfo info = {};
				info.brokerId = _acctInfo.brokerId;
				info.account = _acctInfo.account;
				info.instId = oi[0].SecuID;
                info.orderId = oi[0].ContractID;
				info.ordtype = getOrderType(oi[0].Type);
                info.execId = "";
                info.tradeDate = 0;
                info.transactTime = 0;
                info.volume = oi[0].State == osyf ? -abs(oi[0].CsnVol) : -abs(oi[0].CancelVol);
                info.price = 0;
                info.seqNum = "";
                result.push_back(info);
                _itftrd->FreeAnswer(oi);
                p = _cancelOrders.erase(p);
            }
            else
            {
                ++p;
            }
        }        
    }
    
    return result;
}

bool 
Trader::checkConnect()
{
    if (!_isConnected)
    {
        _itftrd->Close();
        if (_acctInfo.syncType == 0)
            _isSyncCancelOrder = true;
        else
            _isSyncCancelOrder = false;
                
        //std::ostringstream os;
        //os << _acctInfo.host << ":" << _acctInfo.port;
        if (_itftrd->Init(_acctInfo.host.c_str()) != 0)
        {
            Ice::Error out(_logger);
            out << "Can not connect to trade server:" <<_acctInfo.host;
            return false;
        }
        
        if (_itftrd->Login(_acctInfo.account.c_str(), asCA, _acctInfo.password.c_str()) != 0)
        {
            char error[256] = {0};
            char sender[128] = {0};
            _itftrd->GetLastError(error, 256, sender, 128);
            Ice::Error out(_logger);
            out << "Login trade server failure: " << error;
            return false;
        }

        _isConnected = true;
    }
    
    return _isConnected;
}

account_type 
Trader::stringToAccountType(const std::string& type)
{
    if (type == "SHA")
        return asSHA;
    else if (type == "SZA")
        return asSZA;
    else if (type == "JJS")
        return asJJS;
    else if (type == "FDL")
        return asFDL;
    else if (type == "FZZ")
        return asFZZ;
    else if (type == "FSH")
        return asFSH;
    else if (type == "HK")
        return asHK;
    else
        return asCA;
}

std::string
Trader::getOrderType(order_type ot)
{
    switch(ot)
    {
	case otBuy		 : return "买";
	case otSell      : return "卖";
	case otETFSub    : return "ETF申购";
	case otETFRed    : return "ETF赎回";
	case otOpenBuy   : return "开仓买";
	case otOpenSell  : return "开仓卖";
	case otCloseBuy  : return "平仓买";
	case otCloseSell : return "平仓卖";
	case otLoanBuy   : return "融资买";
	case otLoanSell  : return "融券卖";
	case otBuyRepay  : return "买券还券";
	case otSellRepay : return "卖券还款";
	case otCloseTodayBuy : return "平今仓买";
	case otCloseTodaySell : return "平今仓卖";
	case otNo       :  return "其他";
    }
	return "未知";
}

} /* BlackBox */