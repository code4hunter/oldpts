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

// $Rev: 5081 $
// File generated on 2009-5-6 10:00:16 from Type Library described below.

// ************************************************************************  //
// Type Lib: g:\PTS\trunk\Bin\PTS HOST\HQPoolSvr.exe (1)
// LIBID: {808C9377-A154-4906-8C0E-DBCC0CCCF48B}
// LCID: 0
// Helpfile: 
// HelpString: HQPoolSvr 1.0 ¿‡–Õø‚
// DepndLst: 
//   (1) v2.0 stdole, (K:\WINDOWS\system32\stdole2.tlb)
// Errors:
//   Error creating palette bitmap of (TPool) : Server g:\PTS\trunk\Bin\PTS HOST\HQPoolSvr.exe contains no icons
//   Error creating palette bitmap of (TManager) : Server g:\PTS\trunk\Bin\PTS HOST\HQPoolSvr.exe contains no icons
//   Error creating palette bitmap of (TQuote2) : Server g:\PTS\trunk\Bin\PTS HOST\HQPoolSvr.exe contains no icons
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include <olectrls.hpp>
#include <oleserver.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#include "HQPoolSvrLib_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Hqpoolsvrlib_tlb
{

IPoolPtr& TPool::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TPool::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TPool::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TPool::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TPool::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TPool::ConnectTo(IPoolPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TPool::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_Pool;
  sd.IntfIID = __uuidof(IPool);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

long __fastcall TPool::Find(BSTR code/*[in]*/, long src/*[in]*/)
{
  long index;
  OLECHECK(GetDefaultInterface()->Find(code, src, (long*)&index));
  return index;
}

Hqpoolsvrlib_tlb::IQuote2* __fastcall TPool::GetItem(long index/*[in]*/)
{
  Hqpoolsvrlib_tlb::IQuote2* quote = 0;
  OLECHECK(GetDefaultInterface()->GetItem(index, (Hqpoolsvrlib_tlb::IQuote2**)&quote));
  return quote;
}

long __fastcall TPool::get_Count(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_Count((long*)&pVal));
  return pVal;
}

IManagerPtr& TManager::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TManager::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TManager::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TManager::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TManager::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TManager::ConnectTo(IManagerPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TManager::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_Manager;
  sd.IntfIID = __uuidof(IManager);
  sd.EventIID= __uuidof(_IManagerEvents);
  ServerData = &sd;
}

void __fastcall TManager::InvokeEvent(int id, Oleserver::TVariantArray& params)
{
  switch(id)
  {
    case 1: {
      if (OnError) {
        (OnError)(this, params[0].bstrVal, params[1], params[2].bstrVal);
      }
      break;
      }
    case 2: {
      if (OnEvent) {
        (OnEvent)(this, params[0].bstrVal, params[1], params[2].pdispVal, params[3].pdispVal);
      }
      break;
      }
    default:
      break;
  }
}

void __fastcall TManager::Start(void)
{
  GetDefaultInterface()->Start();
}

void __fastcall TManager::Stop(void)
{
  GetDefaultInterface()->Stop();
}

void __fastcall TManager::ShowProperty(OLE_HANDLE ParentWnd/*[in]*/)
{
  GetDefaultInterface()->ShowProperty(ParentWnd/*[in]*/);
}

void __fastcall TManager::Reset(void)
{
  GetDefaultInterface()->Reset();
}

void __fastcall TManager::SetPTSSession(LPDISPATCH Session/*[in]*/)
{
  GetDefaultInterface()->SetPTSSession(Session/*[in]*/);
}

VARIANT_BOOL __fastcall TManager::get_Active(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_Active((VARIANT_BOOL*)&pVal));
  return pVal;
}

long __fastcall TManager::get_ActiveTopic(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_ActiveTopic((long*)&pVal));
  return pVal;
}

long __fastcall TManager::get_TopicCount(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_TopicCount((long*)&pVal));
  return pVal;
}

long __fastcall TManager::get_EventCount(long index/*[in]*/)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_EventCount(index, (long*)&pVal));
  return pVal;
}

IQuote2Ptr& TQuote2::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TQuote2::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TQuote2::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TQuote2::Disconnect()
{
  if (m_DefaultIntf) {
    
    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TQuote2::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TQuote2::ConnectTo(IQuote2Ptr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TQuote2::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_Quote2;
  sd.IntfIID = __uuidof(IQuote2);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

long __fastcall TQuote2::get_SeqNo(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_SeqNo((long*)&pVal));
  return pVal;
}

BSTR __fastcall TQuote2::get_Symbol(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_Symbol((BSTR*)&pVal));
  return pVal;
}

BSTR __fastcall TQuote2::get_InstID(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_InstID((BSTR*)&pVal));
  return pVal;
}

long __fastcall TQuote2::get_InstIDSource(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_InstIDSource((long*)&pVal));
  return pVal;
}

long __fastcall TQuote2::get_LastQty(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_LastQty((long*)&pVal));
  return pVal;
}

double __fastcall TQuote2::get_LastPrice(void)
{
  double pVal;
  OLECHECK(GetDefaultInterface()->get_LastPrice((double*)&pVal));
  return pVal;
}

BSTR __fastcall TQuote2::get_LastTime(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_LastTime((BSTR*)&pVal));
  return pVal;
}

double __fastcall TQuote2::get_PreClosePrice(void)
{
  double pVal;
  OLECHECK(GetDefaultInterface()->get_PreClosePrice((double*)&pVal));
  return pVal;
}

double __fastcall TQuote2::get_ClosePrice(void)
{
  double pVal;
  OLECHECK(GetDefaultInterface()->get_ClosePrice((double*)&pVal));
  return pVal;
}

double __fastcall TQuote2::get_OpenPrice(void)
{
  double pVal;
  OLECHECK(GetDefaultInterface()->get_OpenPrice((double*)&pVal));
  return pVal;
}

double __fastcall TQuote2::get_SettlPrice(void)
{
  double pVal;
  OLECHECK(GetDefaultInterface()->get_SettlPrice((double*)&pVal));
  return pVal;
}

double __fastcall TQuote2::get_LowPrice(void)
{
  double pVal;
  OLECHECK(GetDefaultInterface()->get_LowPrice((double*)&pVal));
  return pVal;
}

double __fastcall TQuote2::get_HighPrice(void)
{
  double pVal;
  OLECHECK(GetDefaultInterface()->get_HighPrice((double*)&pVal));
  return pVal;
}

double __fastcall TQuote2::get_Turnover(void)
{
  double pVal;
  OLECHECK(GetDefaultInterface()->get_Turnover((double*)&pVal));
  return pVal;
}

long __fastcall TQuote2::get_DayQty(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_DayQty((long*)&pVal));
  return pVal;
}

double __fastcall TQuote2::get_FixPrice(void)
{
  double pVal;
  OLECHECK(GetDefaultInterface()->get_FixPrice((double*)&pVal));
  return pVal;
}

long __fastcall TQuote2::get_AskQty(VARIANT index/*[in]*/)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_AskQty(index, (long*)&pVal));
  return pVal;
}

double __fastcall TQuote2::get_AskPrice(VARIANT index/*[in]*/)
{
  double pVal;
  OLECHECK(GetDefaultInterface()->get_AskPrice(index, (double*)&pVal));
  return pVal;
}

long __fastcall TQuote2::get_BidQty(VARIANT index/*[in]*/)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_BidQty(index, (long*)&pVal));
  return pVal;
}

double __fastcall TQuote2::get_BidPrice(VARIANT index/*[in]*/)
{
  double pVal;
  OLECHECK(GetDefaultInterface()->get_BidPrice(index, (double*)&pVal));
  return pVal;
}

BSTR __fastcall TQuote2::get_TradingDay(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_TradingDay((BSTR*)&pVal));
  return pVal;
}

long __fastcall TQuote2::get_LevelCount(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_LevelCount((long*)&pVal));
  return pVal;
}


};     // namespace Hqpoolsvrlib_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Hqpoolsvrlib_ocx
{

void __fastcall PACKAGE Register()
{
  // [3]
  TComponentClass cls_svr[] = {
                              __classid(Hqpoolsvrlib_tlb::TPool), 
                              __classid(Hqpoolsvrlib_tlb::TManager), 
                              __classid(Hqpoolsvrlib_tlb::TQuote2)
                           };
  RegisterComponents("ActiveX", cls_svr,
                     sizeof(cls_svr)/sizeof(cls_svr[0])-1);
}

};     // namespace Hqpoolsvrlib_ocx
