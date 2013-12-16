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
// File generated on 2010/8/25 18:10:57 from Type Library described below.

// ************************************************************************  //
// Type Lib: E:\pts2\trunk\Bin\Trading Server\HsCommX.dll (1)
// LIBID: {5DD0C266-258A-49C6-8A41-82256FD308DD}
// LCID: 0
// Helpfile: 
// HelpString: WebComm Library
// DepndLst: 
//   (1) v2.0 stdole, (F:\Windows\system32\stdole2.tlb)
// Errors:
//   Hint: Symbol 'Eof' renamed to 'EOF_'
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include <olectrls.hpp>
#include <oleserver.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#include "HsCommX_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Hscommx_tlb
{

ICommPtr& TComm::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TComm::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TComm::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TComm::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TComm::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TComm::ConnectTo(ICommPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TComm::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_Comm;
  sd.IntfIID = __uuidof(IComm);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

long __fastcall TComm::Connect1(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->Connect((long*)&value));
  return value;
}

long __fastcall TComm::Send(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->Send((long*)&value));
  return value;
}

long __fastcall TComm::Receive(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->Receive((long*)&value));
  return value;
}

void __fastcall TComm::SetHead(int BranchNo/*[in]*/, int FuncNo/*[in]*/)
{
  GetDefaultInterface()->SetHead(BranchNo/*[in]*/, FuncNo/*[in]*/);
}

long __fastcall TComm::DisConnect(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->DisConnect((long*)&value));
  return value;
}

void __fastcall TComm::AddField(BSTR sField/*[in]*/)
{
  GetDefaultInterface()->AddField(sField/*[in]*/);
}

void __fastcall TComm::AddValue(BSTR sValue/*[in]*/)
{
  GetDefaultInterface()->AddValue(sValue/*[in]*/);
}

void __fastcall TComm::SetRange(long FieldCount/*[in]*/, long RowCount/*[in]*/)
{
  GetDefaultInterface()->SetRange(FieldCount/*[in]*/, RowCount/*[in]*/);
}

void __fastcall TComm::MoveBy(long Step/*[in]*/)
{
  GetDefaultInterface()->MoveBy(Step/*[in]*/);
}

BSTR __fastcall TComm::FieldByName(BSTR FieldName/*[in]*/)
{
  BSTR value = 0;
  OLECHECK(GetDefaultInterface()->FieldByName(FieldName, (BSTR*)&value));
  return value;
}

void __fastcall TComm::SetConnect(void)
{
  GetDefaultInterface()->SetConnect();
}

void __fastcall TComm::Free(void)
{
  GetDefaultInterface()->Free();
}

void __fastcall TComm::Create(void)
{
  GetDefaultInterface()->Create();
}

void __fastcall TComm::CreatePack(void)
{
  GetDefaultInterface()->CreatePack();
}

void __fastcall TComm::FreePack(void)
{
  GetDefaultInterface()->FreePack();
}

long __fastcall TComm::SendBuffer(BSTR value/*[in]*/)
{
  long valu;
  OLECHECK(GetDefaultInterface()->SendBuffer(value, (long*)&valu));
  return valu;
}

void __fastcall TComm::CreateX(long Order/*[in]*/)
{
  GetDefaultInterface()->CreateX(Order/*[in]*/);
}

long __fastcall TComm::ConnectX(long Protocol/*[in]*/, BSTR Address/*[in]*/, long Port/*[in]*/, 
                                long KeyCipher/*[in]*/, BSTR Key/*[in]*/, long KeyLen/*[in]*/)
{
  long value;
  OLECHECK(GetDefaultInterface()->ConnectX(Protocol, Address, Port, KeyCipher, Key, KeyLen, (long*)&value));
  return value;
}

BSTR __fastcall TComm::GetFieldName(long Index/*[in]*/)
{
  BSTR value = 0;
  OLECHECK(GetDefaultInterface()->GetFieldName(Index, (BSTR*)&value));
  return value;
}

long __fastcall TComm::get_ErrorNo(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->get_ErrorNo((long*)&value));
  return value;
}

BSTR __fastcall TComm::get_ErrorMsg(void)
{
  BSTR value = 0;
  OLECHECK(GetDefaultInterface()->get_ErrorMsg((BSTR*)&value));
  return value;
}

long __fastcall TComm::get_RecordCount(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->get_RecordCount((long*)&value));
  return value;
}

long __fastcall TComm::get_EOF_(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->get_EOF_((long*)&value));
  return value;
}

long __fastcall TComm::get_Bof(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->get_Bof((long*)&value));
  return value;
}

long __fastcall TComm::get_SendTimeOut(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->get_SendTimeOut((long*)&value));
  return value;
}

void __fastcall TComm::set_SendTimeOut(long value/*[in]*/)
{
  GetDefaultInterface()->set_SendTimeOut(value/*[in]*/);
}

long __fastcall TComm::get_ReceiveTimeOut(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->get_ReceiveTimeOut((long*)&value));
  return value;
}

void __fastcall TComm::set_ReceiveTimeOut(long value/*[in]*/)
{
  GetDefaultInterface()->set_ReceiveTimeOut(value/*[in]*/);
}

long __fastcall TComm::get_SectionIndex(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->get_SectionIndex((long*)&value));
  return value;
}

void __fastcall TComm::set_SectionIndex(long value/*[in]*/)
{
  GetDefaultInterface()->set_SectionIndex(value/*[in]*/);
}

long __fastcall TComm::get_SenderId(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->get_SenderId((long*)&value));
  return value;
}

void __fastcall TComm::set_SenderId(long value/*[in]*/)
{
  GetDefaultInterface()->set_SenderId(value/*[in]*/);
}

BSTR __fastcall TComm::get_Buffer(void)
{
  BSTR value = 0;
  OLECHECK(GetDefaultInterface()->get_Buffer((BSTR*)&value));
  return value;
}

void __fastcall TComm::set_Buffer(BSTR value/*[in]*/)
{
  GetDefaultInterface()->set_Buffer(value/*[in]*/);
}

long __fastcall TComm::get_FieldCount(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->get_FieldCount((long*)&value));
  return value;
}

long __fastcall TComm::get_Connection(void)
{
  long value;
  OLECHECK(GetDefaultInterface()->get_Connection((long*)&value));
  return value;
}


};     // namespace Hscommx_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Hscommx_ocx
{

void __fastcall PACKAGE Register()
{
  // [1]
  TComponentClass cls_svr[] = {
                              __classid(Hscommx_tlb::TComm)
                           };
  RegisterComponents("ActiveX", cls_svr,
                     sizeof(cls_svr)/sizeof(cls_svr[0])-1);
}

};     // namespace Hscommx_ocx
