#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "inifile.h"

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

bool CIniFile::WriteString(char * Section,char * Item,char * Text)
{
	return (WritePrivateProfileString(Section,Item,Text,m_PathName)==TRUE); 
}

bool CIniFile::WriteInteger(char * Section ,char * Item,int Val)
{
	char buf[100];
	sprintf(buf,"%d",Val);
	return WriteString(Section,Item,buf); 
}

bool CIniFile::WriteDouble(char * Section ,char * Item,double Val)
{
	char buf[100];
	sprintf(buf,"%.15f",Val);
	return WriteString(Section,Item,buf); 
}

bool CIniFile::WriteFloat(char * Section ,char * Item,float Val)
{
	char buf[100];
	sprintf(buf,"%.7f",Val);
	return WriteString(Section,Item,buf); 
}

bool CIniFile::WriteBoolean(char * Section ,char * Item,bool Val)
{
	return WriteString(Section,Item,Val==1 ? "1" : "0"); 
}

int CIniFile::ReadString(char * Section,char * Item,char * RetText,int Length,char * DefText)
{
	return GetPrivateProfileString(Section,Item,DefText,RetText,Length,m_PathName);
}

int CIniFile::ReadInteger(char * Section ,char * Item,int DefVal)
{
	char buf[100];
	char * stopstring;
	if(ReadString(Section,Item,buf,100)>0)
	{
		int x = strtol(buf,&stopstring,0);
		if(strlen(stopstring)>0)
			return DefVal;
		else 
			return x;
	}
	else return DefVal;
}

double CIniFile::ReadDouble(char * Section ,char * Item,double DefVal)
{
	char buf[100];
	char * stopstring;
	if(ReadString(Section,Item,buf,100)>0)
	{
		double x = strtod( buf, &stopstring);
		if(strlen(stopstring)>0)
			return DefVal;
		else
			return x;
	}
	else return DefVal;
}

float CIniFile::ReadFloat(char * Section ,char * Item,float DefVal)
{
	char buf[100];
	char * stopstring;
	if(ReadString(Section,Item,buf,100)>0)
	{
		float x =(float)strtod( buf, &stopstring);
		if(strlen(stopstring)>0)
			return DefVal;
		else
			return x;
	}
	else return DefVal;
}

bool CIniFile::ReadBoolean(char * Section ,char * Item,bool DefVal)
{
	char buf[100];
	char * stopstring;
	if(ReadString(Section,Item,buf,100)>0)
	{
		bool x =(strtol(buf,&stopstring,0)==1);
		if(strlen(stopstring)>0)
			return DefVal;
		else 
			return x;
	}
	else return DefVal;
}