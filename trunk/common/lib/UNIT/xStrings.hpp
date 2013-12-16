// CodeGear C++Builder
// Copyright (c) 1995, 2009 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xstrings.pas' rev: 21.00

#ifndef XstringsHPP
#define XstringsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Filectrl.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Xstrings
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
#define DEFAULT_DELIMITERS (Set<char, 0, 255> () << '\x9' << '\xa' << '\xd' << '\x20' )
extern PACKAGE System::UnicodeString __fastcall GetToken(const System::UnicodeString S, int index, bool bTrail = false, const Sysutils::TSysCharSet &Delimiters = (Sysutils::TSysCharSet() << '\x9' << '\xa' << '\xd' << '\x20' ));
extern PACKAGE int __fastcall CountWords(System::UnicodeString S, const Sysutils::TSysCharSet &Delimiters = (Sysutils::TSysCharSet() << '\x9' << '\xa' << '\xd' << '\x20' ));
extern PACKAGE bool __fastcall IsContainingCRLF(const System::UnicodeString S);
extern PACKAGE void __fastcall TruncateCRLF(System::UnicodeString &S);
extern PACKAGE bool __fastcall ReplaceString(System::UnicodeString &S, const System::UnicodeString Token, const System::UnicodeString NewToken, bool bCaseSensitive);
extern PACKAGE void __fastcall Simple_ReplaceString(System::UnicodeString &S, const System::UnicodeString Substr, int index, int Count);
extern PACKAGE System::UnicodeString __fastcall BracketString(const System::UnicodeString S);
extern PACKAGE System::UnicodeString __fastcall UnquoteString(const System::UnicodeString S);
extern PACKAGE System::UnicodeString __fastcall FirstToken(System::UnicodeString &S, const System::UnicodeString Delimiter, bool Remove);
extern PACKAGE System::UnicodeString __fastcall CompositeStrings(Classes::TStrings* SL, const System::UnicodeString Delimiter);
extern PACKAGE System::UnicodeString __fastcall AddTimeStamp(const System::UnicodeString S);
extern PACKAGE bool __fastcall SafeLoadStrings(Classes::TStrings* SL, const System::UnicodeString Filename);
extern PACKAGE void __fastcall SafeSaveStrings(Classes::TStrings* SL, const System::UnicodeString Filename);
extern PACKAGE int __fastcall PartialIndexOf(Classes::TStrings* SL, System::UnicodeString S, int StartIndex, bool bForward);
extern PACKAGE void __fastcall RemoveDuplicates(Classes::TStrings* SL);
extern PACKAGE int __fastcall ParseRPLNo(System::UnicodeString &Msg);
extern PACKAGE int __fastcall RPos(const System::WideChar C, const System::UnicodeString S);
extern PACKAGE int __fastcall AnsiIPos(const System::UnicodeString Substr, const System::UnicodeString S);
extern PACKAGE int __fastcall MatchString(System::UnicodeString S, System::UnicodeString SubS, Dialogs::TFindOptions Options);

}	/* namespace Xstrings */
using namespace Xstrings;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// XstringsHPP
