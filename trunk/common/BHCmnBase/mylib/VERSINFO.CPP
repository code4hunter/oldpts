#ifndef _VERSINFO_
#include "versinfo.hpp"
#endif

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

//#include <iostream>
using namespace std;

//--------------------------------------------------------------------------------
VersionInfo::VersionInfo (const char * const inFileName)
: theVersionInfo (NULL)
, theFixedInfo (NULL)
{
	unsigned long aVersionInfoSize
		= GetFileVersionInfoSizeA ( const_cast<char*> (inFileName)
		, &aVersionInfoSize);
	if (aVersionInfoSize)
	{
		theVersionInfo = new char [aVersionInfoSize];
		if (!GetFileVersionInfoA ( const_cast<char*> (inFileName)
			, 0
			, aVersionInfoSize
			, theVersionInfo
			) )
		{
			throw ("VersionInfo: can not retrieve version information");
		} // endif
		unsigned int aSize = 0;
		if (!VerQueryValueA( theVersionInfo
			, "\\"
			, &theFixedInfo
			, &aSize))
		{
			throw ("VersionInfo: can not retrieve version information");
		} // endif
	} // endif
} // end constructor


//--------------------------------------------------------------------------------
VersionInfo::~VersionInfo ()
{
	delete[] theVersionInfo;
} // end destructor


//--------------------------------------------------------------------------------
unsigned short VersionInfo::majorVersion () const
{
	if (!theFixedInfo) return 0;
	VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) theFixedInfo;
	return (aInfo -> dwFileVersionMS >> 16);
} // end VersionInfo::majorVersion () const


//--------------------------------------------------------------------------------
unsigned short VersionInfo::minorVersion () const
{
	if (!theFixedInfo) return 0;
	VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) theFixedInfo;
	return (aInfo -> dwFileVersionMS);
} // end VersionInfo::minorVersion () const


//--------------------------------------------------------------------------------
unsigned short VersionInfo::build () const
{
	if (!theFixedInfo) return 0;
	VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) theFixedInfo;
	return (aInfo -> dwFileVersionLS >> 16);
} // end VersionInfo::build () const


//--------------------------------------------------------------------------------
unsigned short VersionInfo::subBuild () const
{
	if (!theFixedInfo) return 0;
	VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) theFixedInfo;
	return (aInfo -> dwFileVersionLS);
} // end VersionInfo::subBuild () const


//--------------------------------------------------------------------------------
unsigned short VersionInfo::productMajorVersion () const
{
	if (!theFixedInfo) return 0;
	VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) theFixedInfo;
	return (aInfo -> dwProductVersionMS >> 16);
} // end VersionInfo::productMajorVersion () const


//--------------------------------------------------------------------------------
unsigned short VersionInfo::productMinorVersion () const
{
	if (!theFixedInfo) return 0;
	VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) theFixedInfo;
	return (aInfo -> dwProductVersionMS);
} // end VersionInfo::productMinorVersion () const


//--------------------------------------------------------------------------------
unsigned short VersionInfo::productBuild () const
{
	if (!theFixedInfo) return 0;
	VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) theFixedInfo;
	return (aInfo -> dwProductVersionLS >> 16);
} // end VersionInfo::productBuild () const


//--------------------------------------------------------------------------------
unsigned short VersionInfo::productSubBuild () const
{
	if (!theFixedInfo) return 1;
	VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) theFixedInfo;
	return (aInfo -> dwProductVersionLS);
} // end VersionInfo::productSubBuild () const


