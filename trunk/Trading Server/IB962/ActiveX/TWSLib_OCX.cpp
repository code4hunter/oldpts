// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// $Rev: 18756 $
// File generated on 2010/3/18 15:58:48 from Type Library described below.

// ************************************************************************  //
// Type Lib: E:\PROGRAM\IB_API_9_62\ActiveX\Tws.ocx (1)
// LIBID: {0A77CCF5-052C-11D6-B0EC-00B0D074179C}
// LCID: 0
// Helpfile: E:\PROGRAM\IB_API_9_62\ActiveX\Tws.hlp
// HelpString: Tws ActiveX Control module
// DepndLst: 
//   (1) v2.0 stdole, (F:\Windows\system32\stdole2.tlb)
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include <olectrls.hpp>
#include <oleserver.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#include "TWSLib_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Twslib_tlb
{



// *********************************************************************//
// OCX PROXY CLASS IMPLEMENTATION
// (The following variables/methods implement the class TTws which
// allows "Tws Control" to be hosted in CBuilder IDE/apps).
// *********************************************************************//
int   TTws::EventDispIDs[44] = {
    0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006,
    0x00000007, 0x00000008, 0x0000000A, 0x0000000B, 0x0000000C, 0x0000000D,
    0x0000000E, 0x0000000F, 0x00000010, 0x00000011, 0x00000012, 0x00000013,
    0x00000014, 0x00000015, 0x00000016, 0x00000017, 0x00000018, 0x00000019,
    0x0000001A, 0x0000001B, 0x0000001C, 0x0000001D, 0x0000001E, 0x0000001F,
    0x00000020, 0x00000021, 0x00000022, 0x00000023, 0x00000024, 0x00000025,
    0x00000026, 0x00000027, 0x00000028, 0x00000064, 0x00000065, 0x00000066,
    0x00000067, 0x00000068};

TControlData2 TTws::CControlData =
{
  // GUID of CoClass and Event Interface of Control
  {0x0A77CCF8, 0x052C, 0x11D6,{ 0xB0, 0xEC, 0x00,0xB0, 0xD0, 0x74,0x17, 0x9C} }, // CoClass
  {0x0A77CCF7, 0x052C, 0x11D6,{ 0xB0, 0xEC, 0x00,0xB0, 0xD0, 0x74,0x17, 0x9C} }, // Events

  // Count of Events and array of their DISPIDs
  44, &EventDispIDs,

  // Pointer to Runtime License string
  NULL,  // HRESULT(0x80004005)

  // Flags for OnChanged PropertyNotification
  0x00000000,
  401,// (IDE Version)

  // Count of Font Prop and array of their DISPIDs
  0, Activex::PDispIDList(NULL),

  // Count of Pict Prop and array of their DISPIDs
  0, Activex::PDispIDList(NULL),
  0, // Reserved
  0, // Instance count (used internally)
  0, // List of Enum descriptions (internal)
};

GUID     TTws::DEF_CTL_INTF = {0x0A77CCF6, 0x052C, 0x11D6,{ 0xB0, 0xEC, 0x00,0xB0, 0xD0, 0x74,0x17, 0x9C} };
TNoParam TTws::OptParam;

static inline void ValidCtrCheck(TTws *)
{
   delete new TTws((TComponent*)(0));
};

void __fastcall TTws::InitControlData()
{
  ControlData = (TControlData*)&CControlData;
  CControlData.FirstEventOfs = System::PByte(&FOntickPrice) - System::PByte(this);
};

void __fastcall TTws::CreateControl()
{
  if (!m_OCXIntf)
  {
    _ASSERTE(DefaultDispatch);
    DefaultDispatch->QueryInterface(DEF_CTL_INTF, (LPVOID*)&m_OCXIntf);
  }
};

_DTwsDisp __fastcall TTws::GetDefaultInterface()
{
  CreateControl();
  return m_OCXIntf;
};

Twslib_tlb::IComboLegList* __fastcall TTws::createComboLegList(void)
{
  return  GetDefaultInterface()->createComboLegList();
}

Twslib_tlb::ITagValueList* __fastcall TTws::createTagValueList(void)
{
  return  GetDefaultInterface()->createTagValueList();
}

Twslib_tlb::IUnderComp* __fastcall TTws::createUnderComp(void)
{
  return  GetDefaultInterface()->createUnderComp();
}

void __fastcall TTws::cancelScannerSubscription(long tickerId)
{
  GetDefaultInterface()->cancelScannerSubscription(tickerId);
}

Twslib_tlb::IExecutionFilter* __fastcall TTws::createExecutionFilter(void)
{
  return  GetDefaultInterface()->createExecutionFilter();
}

Twslib_tlb::IOrder* __fastcall TTws::createOrder(void)
{
  return  GetDefaultInterface()->createOrder();
}

Twslib_tlb::IScannerSubscription* __fastcall TTws::createScannerSubscription(void)
{
  return  GetDefaultInterface()->createScannerSubscription();
}

void __fastcall TTws::placeOrderEx(long orderId, Twslib_tlb::IContract* contract, 
                                   Twslib_tlb::IOrder* order)
{
  GetDefaultInterface()->placeOrderEx(orderId, contract, order);
}

void __fastcall TTws::reqScannerSubscriptionEx(long tickerId, 
                                               Twslib_tlb::IScannerSubscription* subscription)
{
  GetDefaultInterface()->reqScannerSubscriptionEx(tickerId, subscription);
}

void __fastcall TTws::reqRealTimeBarsEx(long tickerId, Twslib_tlb::IContract* contract, long barSize, 
                                        BSTR whatToShow, long useRTH)
{
  GetDefaultInterface()->reqRealTimeBarsEx(tickerId, contract, barSize, whatToShow, useRTH);
}

Twslib_tlb::IContract* __fastcall TTws::createContract(void)
{
  return  GetDefaultInterface()->createContract();
}

void __fastcall TTws::exerciseOptionsEx(long tickerId, Twslib_tlb::IContract* contract, 
                                        long exerciseAction, long exerciseQuantity, BSTR account, 
                                        long override)
{
  GetDefaultInterface()->exerciseOptionsEx(tickerId, contract, exerciseAction, exerciseQuantity, 
                                           account, override);
}

void __fastcall TTws::reqExecutionsEx(long reqId, Twslib_tlb::IExecutionFilter* filter)
{
  GetDefaultInterface()->reqExecutionsEx(reqId, filter);
}

void __fastcall TTws::resetAllProperties(void)
{
  GetDefaultInterface()->resetAllProperties();
}

void __fastcall TTws::reqFundamentalData(long reqId, Twslib_tlb::IContract* contract, 
                                         BSTR reportType)
{
  GetDefaultInterface()->reqFundamentalData(reqId, contract, reportType);
}

void __fastcall TTws::reqCurrentTime(void)
{
  GetDefaultInterface()->reqCurrentTime();
}

void __fastcall TTws::reqMktDepthEx(long tickerId, Twslib_tlb::IContract* contract, long numRows)
{
  GetDefaultInterface()->reqMktDepthEx(tickerId, contract, numRows);
}

void __fastcall TTws::cancelMktData(long id)
{
  GetDefaultInterface()->cancelMktData(id);
}

void __fastcall TTws::cancelOrder(long id)
{
  GetDefaultInterface()->cancelOrder(id);
}

void __fastcall TTws::cancelFundamentalData(long reqId)
{
  GetDefaultInterface()->cancelFundamentalData(reqId);
}

void __fastcall TTws::reqMktDataEx(long tickerId, Twslib_tlb::IContract* contract, BSTR genericTicks, 
                                   long snapshot)
{
  GetDefaultInterface()->reqMktDataEx(tickerId, contract, genericTicks, snapshot);
}

void __fastcall TTws::reqScannerSubscription(long tickerId, long numberOfRows, BSTR instrument, 
                                             BSTR locationCode, BSTR scanCode, double abovePrice, 
                                             double belowPrice, long aboveVolume, 
                                             double marketCapAbove, double marketCapBelow, 
                                             BSTR moodyRatingAbove, BSTR moodyRatingBelow, 
                                             BSTR spRatingAbove, BSTR spRatingBelow, 
                                             BSTR maturityDateAbove, BSTR maturityDateBelow, 
                                             double couponRateAbove, double couponRateBelow, 
                                             long excludeConvertible, long averageOptionVolumeAbove, 
                                             BSTR scannerSettingPairs, BSTR stockTypeFilter)
{
  GetDefaultInterface()->reqScannerSubscription(tickerId, numberOfRows, instrument, locationCode, 
                                                scanCode, abovePrice, belowPrice, aboveVolume, 
                                                marketCapAbove, marketCapBelow, moodyRatingAbove, 
                                                moodyRatingBelow, spRatingAbove, spRatingBelow, 
                                                maturityDateAbove, maturityDateBelow, 
                                                couponRateAbove, couponRateBelow, excludeConvertible, 
                                                averageOptionVolumeAbove, scannerSettingPairs, 
                                                stockTypeFilter);
}

void __fastcall TTws::reqScannerParameters(void)
{
  GetDefaultInterface()->reqScannerParameters();
}

void __fastcall TTws::reqRealTimeBars(long tickerId, BSTR symbol, BSTR secType, BSTR expiry, 
                                      double strike, BSTR right, BSTR multiplier, BSTR exchange, 
                                      BSTR primaryExchange, BSTR currency, long isExpired, 
                                      long barSize, BSTR whatToShow, long useRTH)
{
  GetDefaultInterface()->reqRealTimeBars(tickerId, symbol, secType, expiry, strike, right, 
                                         multiplier, exchange, primaryExchange, currency, isExpired, 
                                         barSize, whatToShow, useRTH);
}

void __fastcall TTws::reqContractDetailsEx(long reqId, Twslib_tlb::IContract* contract)
{
  GetDefaultInterface()->reqContractDetailsEx(reqId, contract);
}

void __fastcall TTws::cancelRealTimeBars(long tickerId)
{
  GetDefaultInterface()->cancelRealTimeBars(tickerId);
}

void __fastcall TTws::cancelHistoricalData(long tickerId)
{
  GetDefaultInterface()->cancelHistoricalData(tickerId);
}

void __fastcall TTws::reqHistoricalDataEx(long tickerId, Twslib_tlb::IContract* contract, 
                                          BSTR endDateTime, BSTR duration, BSTR barSize, 
                                          BSTR whatToShow, long useRTH, long formatDate)
{
  GetDefaultInterface()->reqHistoricalDataEx(tickerId, contract, endDateTime, duration, barSize, 
                                             whatToShow, useRTH, formatDate);
}

void __fastcall TTws::reqHistoricalData(long id, BSTR symbol, BSTR secType, BSTR expiry, 
                                        double strike, BSTR right, BSTR multiplier, BSTR exchange, 
                                        BSTR curency, long isExpired, BSTR endDateTime, 
                                        BSTR durationStr, BSTR barSizeSetting, BSTR whatToShow, 
                                        long useRTH, long formatDate)
{
  GetDefaultInterface()->reqHistoricalData(id, symbol, secType, expiry, strike, right, multiplier, 
                                           exchange, curency, isExpired, endDateTime, durationStr, 
                                           barSizeSetting, whatToShow, useRTH, formatDate);
}

void __fastcall TTws::replaceFA(long faDataType, BSTR cxml)
{
  GetDefaultInterface()->replaceFA(faDataType, cxml);
}

void __fastcall TTws::requestFA(long faDataType)
{
  GetDefaultInterface()->requestFA(faDataType);
}

void __fastcall TTws::reqManagedAccts(void)
{
  GetDefaultInterface()->reqManagedAccts();
}

void __fastcall TTws::reqAllOpenOrders(void)
{
  GetDefaultInterface()->reqAllOpenOrders();
}

void __fastcall TTws::reqAutoOpenOrders(long bAutoBind)
{
  GetDefaultInterface()->reqAutoOpenOrders(bAutoBind);
}

void __fastcall TTws::setServerLogLevel(long logLevel)
{
  GetDefaultInterface()->setServerLogLevel(logLevel);
}

void __fastcall TTws::reqNewsBulletins(long allDaysMsgs)
{
  GetDefaultInterface()->reqNewsBulletins(allDaysMsgs);
}

void __fastcall TTws::cancelNewsBulletins(void)
{
  GetDefaultInterface()->cancelNewsBulletins();
}

void __fastcall TTws::clearComboLegs(void)
{
  GetDefaultInterface()->clearComboLegs();
}

void __fastcall TTws::addComboLeg(long conId, BSTR action, long ratio, BSTR exchange, long openClose, 
                                  long shortSaleSlot, BSTR designatedLocation)
{
  GetDefaultInterface()->addComboLeg(conId, action, ratio, exchange, openClose, shortSaleSlot, 
                                     designatedLocation);
}

void __fastcall TTws::cancelMktDepth(long id)
{
  GetDefaultInterface()->cancelMktDepth(id);
}

void __fastcall TTws::reqMktDepth2(long id, BSTR localSymbol, BSTR secType, BSTR exchange, 
                                   BSTR curency, long numRows)
{
  GetDefaultInterface()->reqMktDepth2(id, localSymbol, secType, exchange, curency, numRows);
}

void __fastcall TTws::reqMktData(long id, BSTR symbol, BSTR secType, BSTR expiry, double strike, 
                                 BSTR right, BSTR multiplier, BSTR exchange, BSTR primaryExchange, 
                                 BSTR currency, BSTR genericTicks, long snapshot)
{
  GetDefaultInterface()->reqMktData(id, symbol, secType, expiry, strike, right, multiplier, exchange, 
                                    primaryExchange, currency, genericTicks, snapshot);
}

void __fastcall TTws::reqIds(long numIds)
{
  GetDefaultInterface()->reqIds(numIds);
}

void __fastcall TTws::reqMktDepth(long id, BSTR symbol, BSTR secType, BSTR expiry, double strike, 
                                  BSTR right, BSTR multiplier, BSTR exchange, BSTR curency, 
                                  long numRows)
{
  GetDefaultInterface()->reqMktDepth(id, symbol, secType, expiry, strike, right, multiplier, 
                                     exchange, curency, numRows);
}

void __fastcall TTws::reqContractDetails2(BSTR localSymbol, BSTR secType, BSTR exchange, 
                                          BSTR curency, long includeExpired)
{
  GetDefaultInterface()->reqContractDetails2(localSymbol, secType, exchange, curency, includeExpired);
}

void __fastcall TTws::exerciseOptions(long id, BSTR symbol, BSTR secType, BSTR expiry, double strike, 
                                      BSTR right, BSTR multiplier, BSTR exchange, BSTR curency, 
                                      long exerciseAction, long exerciseQuantity, long override)
{
  GetDefaultInterface()->exerciseOptions(id, symbol, secType, expiry, strike, right, multiplier, 
                                         exchange, curency, exerciseAction, exerciseQuantity, 
                                         override);
}

void __fastcall TTws::placeOrder2(long id, BSTR action, long quantity, BSTR localSymbol, 
                                  BSTR secType, BSTR exchange, BSTR primaryExchange, BSTR curency, 
                                  BSTR orderType, double lmtPrice, double auxPrice, 
                                  BSTR goodAfterTime, BSTR group, BSTR faMethod, BSTR faPercentage, 
                                  BSTR faProfile, BSTR goodTillDate)
{
  GetDefaultInterface()->placeOrder2(id, action, quantity, localSymbol, secType, exchange, 
                                     primaryExchange, curency, orderType, lmtPrice, auxPrice, 
                                     goodAfterTime, group, faMethod, faPercentage, faProfile, 
                                     goodTillDate);
}

void __fastcall TTws::reqMktData2(long id, BSTR localSymbol, BSTR secType, BSTR exchange, 
                                  BSTR primaryExchange, BSTR currency, BSTR genericTicks, 
                                  long snapshot)
{
  GetDefaultInterface()->reqMktData2(id, localSymbol, secType, exchange, primaryExchange, currency, 
                                     genericTicks, snapshot);
}

void __fastcall TTws::reqContractDetails(BSTR symbol, BSTR secType, BSTR expiry, double strike, 
                                         BSTR right, BSTR multiplier, BSTR exchange, BSTR curency, 
                                         long includeExpired)
{
  GetDefaultInterface()->reqContractDetails(symbol, secType, expiry, strike, right, multiplier, 
                                            exchange, curency, includeExpired);
}

void __fastcall TTws::placeOrder(long id, BSTR action, long quantity, BSTR symbol, BSTR secType, 
                                 BSTR expiry, double strike, BSTR right, BSTR multiplier, 
                                 BSTR exchange, BSTR primaryExchange, BSTR curency, BSTR orderType, 
                                 double price, double auxPrice, BSTR goodAfterTime, BSTR group, 
                                 BSTR faMethod, BSTR faPercentage, BSTR faProfile, BSTR goodTillDate)
{
  GetDefaultInterface()->placeOrder(id, action, quantity, symbol, secType, expiry, strike, right, 
                                    multiplier, exchange, primaryExchange, curency, orderType, price, 
                                    auxPrice, goodAfterTime, group, faMethod, faPercentage, 
                                    faProfile, goodTillDate);
}

void __fastcall TTws::reqAccountUpdates(long subscribe, BSTR acctCode)
{
  GetDefaultInterface()->reqAccountUpdates(subscribe, acctCode);
}

void __fastcall TTws::reqOpenOrders(void)
{
  GetDefaultInterface()->reqOpenOrders();
}

void __fastcall TTws::reqExecutions(void)
{
  GetDefaultInterface()->reqExecutions();
}

void __fastcall TTws::connect(BSTR host, long port, long clientId)
{
  GetDefaultInterface()->connect(host, port, clientId);
}

void __fastcall TTws::disconnect(void)
{
  GetDefaultInterface()->disconnect();
}


};     // namespace Twslib_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Twslib_ocx
{

void __fastcall PACKAGE Register()
{
  // [1]
  TComponentClass cls_ocx[] = {
                              __classid(Twslib_tlb::TTws)
                           };
  RegisterComponents("ActiveX", cls_ocx,
                     sizeof(cls_ocx)/sizeof(cls_ocx[0])-1);
}

};     // namespace Twslib_ocx
