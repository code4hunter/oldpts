#ifndef __E__pts2_trunk_TradeGateway_SqjsApi_TradeGateway_h__
#define __E__pts2_trunk_TradeGateway_SqjsApi_TradeGateway_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/LocalObject.h>
#include <Ice/Object.h>
#include <Ice/Direct.h>
#include <IceUtil/ScopedArray.h>
#include <Ice/StreamF.h>
#include <Ice/BuiltinSequences.h>
#include <Ice/Properties.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 304
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace TradeGateway
{

enum MessageType
{
    Information,
    Error,
    Warning
};

struct MessageInfo
{
    ::TradeGateway::MessageType type;
    ::std::string name;
    ::std::string value;
};

typedef ::std::vector< ::TradeGateway::MessageInfo> MessageInfoSeq;

struct AssetInfo
{
    ::std::string accountId;
    ::Ice::Double initial;
    ::Ice::Double balance;
    ::Ice::Double equity;
    ::Ice::Double available;
    ::Ice::Double frozenMargin;
    ::Ice::PropertyDict extra;
};

typedef ::std::vector< ::TradeGateway::AssetInfo> AssetInfoSeq;

enum MarketIdSource
{
    SSE,
    SZSE,
    SHFE,
    DCE,
    CZCE,
    CFFEX,
    HKEX,
    MktUnknow
};

struct InstrumentId
{
    ::std::string securityID;
    ::TradeGateway::MarketIdSource securityIDSource;
};

enum Side
{
    Buy,
    Sell,
    Subscribe,
    Redeem,
    Lend,
    Borrow,
    SideUnknow
};

enum PositionEffect
{
    Open,
    Close,
    CloseToday,
    PosEftUnknow
};

enum OrdType
{
    Market,
    Limit,
    LimitOrBetter,
    OrdTypeUnknow
};

struct Order
{
    ::std::string accountId;
    ::TradeGateway::InstrumentId inst;
    ::TradeGateway::Side s;
    ::TradeGateway::PositionEffect posEfct;
    ::TradeGateway::OrdType type;
    ::Ice::Double lmtPrice;
    ::Ice::Int ordQty;
    ::std::string ordId;
    ::Ice::Int date;
    ::Ice::Int time;
    ::Ice::PropertyDict extra;
};

typedef ::std::vector< ::TradeGateway::Order> OrderSeq;

enum OrderStatus
{
    New,
    PendingNew,
    Working,
    PendingCancel,
    Filled,
    DoneForDay,
    Canceled,
    Stopped,
    Rejected,
    OrdStatusUnknow
};

struct OrderReport
{
    ::TradeGateway::Order base;
    ::TradeGateway::OrderStatus ordStatus;
    ::Ice::Int cumQty;
    ::Ice::Double avgPx;
    ::Ice::Int leavesQty;
    ::std::string text;
    ::std::string seq;
    ::Ice::PropertyDict extra;
};

typedef ::std::vector< ::TradeGateway::OrderReport> OrderReportSeq;
enum ExecType
{
    EtCanceled,
    EtRejected,
    EtStopped,
    EtTrade,
    ExecTypeUnknow
};

struct ExecutionReport
{
    ::std::string accountId;
    ::std::string ordId;
    ::std::string execId;
    ::TradeGateway::ExecType type;
    ::std::string ordRejReason;
    ::Ice::Long lastQty;
    ::Ice::Double lastPx;
    ::Ice::Int tradeDate;
    ::Ice::Int transactTime;
    ::std::string seq;
    ::Ice::PropertyDict extra;
};

typedef ::std::vector< ::TradeGateway::ExecutionReport> ExecutionReportSeq;

enum PositionDirection
{
    DirectionLong,
    DirectionShort,
    PosDirectionUnknow
};

struct VolumePrice
{
    ::Ice::Long volume;
    ::Ice::Long frozenVolume;
    ::Ice::Double price;
};

struct PositionInfo
{
    ::std::string accountId;
    ::TradeGateway::InstrumentId inst;
    ::TradeGateway::PositionDirection direction;
    ::TradeGateway::VolumePrice previous;
    ::TradeGateway::VolumePrice today;
    ::TradeGateway::VolumePrice forETF;
    ::Ice::Double margin;
    ::Ice::Double currPrice;
    ::Ice::PropertyDict extra;
};

typedef ::std::vector< ::TradeGateway::PositionInfo> PositionInfoSeq;

enum ResumeType
{
    Restart,
    Resume,
    Quick
};

}

#endif
