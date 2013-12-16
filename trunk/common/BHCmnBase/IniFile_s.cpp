#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "inifile_s.h"

CIniFile::CIniFile(TCHAR * PathName)
{
	lstrcpy(m_PathName,PathName);
		//È¥³ýÖ»¶Á
	DWORD Attrs=GetFileAttributes(m_PathName);
	if ((Attrs & FILE_ATTRIBUTE_READONLY)) 
	{ 
		SetFileAttributes(m_PathName, Attrs - FILE_ATTRIBUTE_READONLY); 
	} 
}

CIniFile::~CIniFile(void)
{
}

bool CIniFile::WriteString(TCHAR * Section,TCHAR * Item,TCHAR * Text)
{
	return (WritePrivateProfileString(Section,Item,Text,m_PathName)==TRUE); 
}

bool CIniFile::WriteInteger(TCHAR * Section ,TCHAR * Item,int Val)
{
	TCHAR buf[100];
	_stprintf_s(buf,100,_T("%d"),Val);
	return WriteString(Section,Item,buf); 
}

bool CIniFile::WriteDouble(TCHAR * Section ,TCHAR * Item,double Val)
{
	TCHAR buf[100];
	_stprintf_s(buf,100,_T("%.15f"),Val);
	return WriteString(Section,Item,buf); 
}

bool CIniFile::WriteFloat(TCHAR * Section ,TCHAR * Item,float Val)
{
	TCHAR buf[100];
	_stprintf_s(buf,100,_T("%.7f"),Val);
	return WriteString(Section,Item,buf); 
}

bool CIniFile::WriteBoolean(TCHAR * Section ,TCHAR * Item,bool Val)
{
	return WriteString(Section,Item,Val==1 ? _T("1") : _T("0")); 
}

int CIniFile::ReadString(TCHAR * Section,TCHAR * Item,TCHAR * RetText,int Length,TCHAR * DefText)
{
	return GetPrivateProfileString(Section,Item,DefText,RetText,Length,m_PathName);
}

int CIniFile::ReadInteger(TCHAR * Section ,TCHAR * Item,int DefVal)
{
	TCHAR buf[100];
	TCHAR * stopstring;
	if(ReadString(Section,Item,buf,100)>0)
	{
		int x = _tcstol(buf,&stopstring,0);
		if(_tcslen(stopstring)>0)
			return DefVal;
		else 
			return x;
	}
	else return DefVal;
}

double CIniFile::ReadDouble(TCHAR * Section ,TCHAR * Item,double DefVal)
{
	TCHAR buf[100];
	TCHAR * stopstring;
	if(ReadString(Section,Item,buf,100)>0)
	{
		double x = _tcstod( buf, &stopstring);
		if(_tcslen(stopstring)>0)
			return DefVal;
		else
			return x;
	}
	else return DefVal;
}

float CIniFile::ReadFloat(TCHAR * Section ,TCHAR * Item,float DefVal)
{
	TCHAR buf[100];
	TCHAR * stopstring;
	if(ReadString(Section,Item,buf,100)>0)
	{
		float x =(float)_tcstod( buf, &stopstring);
		if(_tcslen(stopstring)>0)
			return DefVal;
		else
			return x;
	}
	else return DefVal;
}

bool CIniFile::ReadBoolean(TCHAR * Section ,TCHAR * Item,bool DefVal)
{
	TCHAR buf[100];
	TCHAR * stopstring;
	if(ReadString(Section,Item,buf,100)>0)
	{
		bool x =(_tcstol(buf,&stopstring,0)==1);
		if(_tcslen(stopstring)>0)
			return DefVal;
		else 
			return x;
	}
	else return DefVal;
}