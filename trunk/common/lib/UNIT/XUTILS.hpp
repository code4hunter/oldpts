// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xutils.pas' rev: 21.00

#ifndef XutilsHPP
#define XutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Xutils
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall MsgBox(const System::UnicodeString Msg);
extern PACKAGE void __fastcall ErrBox(const System::UnicodeString Msg);
extern PACKAGE bool __fastcall YesNoBox(const System::UnicodeString Msg);
extern PACKAGE int __fastcall YesNoCancelBox(const System::UnicodeString Msg);
extern PACKAGE void __fastcall ShowLastError(const System::UnicodeString Msg = L"API Error");
extern PACKAGE void __fastcall RaiseLastError(const System::UnicodeString Msg = L"API Error");
extern PACKAGE void __fastcall FreeStringsObjects(Classes::TStrings* SL);

}	/* namespace Xutils */
using namespace Xutils;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// XutilsHPP
