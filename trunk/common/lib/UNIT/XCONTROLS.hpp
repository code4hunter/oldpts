// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xcontrols.pas' rev: 21.00

#ifndef XcontrolsHPP
#define XcontrolsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Comctrls.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Xcontrols
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall EnableControl(Controls::TControl* AControl, bool Enable);
extern PACKAGE void __fastcall EnableChildControls(Controls::TControl* AControl, bool Enable);
extern PACKAGE void __fastcall EnableClassControl(Controls::TControl* AControl, bool Enable, Controls::TControlClass ControlClass);
extern PACKAGE void __fastcall SelectPageIndex(const Comctrls::TPageControl* PC, const int iIndex, const bool Animated);
extern PACKAGE void __fastcall MakeSureTabVisible(const Comctrls::TPageControl* PC);
extern PACKAGE void __fastcall LoadTreeViewFromTextFile(Comctrls::TTreeNodes* Nodes, System::UnicodeString Filename);
extern PACKAGE void __fastcall SaveTreeViewToTextFile(Comctrls::TTreeNodes* Nodes, System::UnicodeString Filename);

}	/* namespace Xcontrols */
using namespace Xcontrols;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// XcontrolsHPP
