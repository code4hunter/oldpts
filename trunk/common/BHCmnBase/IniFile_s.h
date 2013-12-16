#ifndef IniFile_sH
#define IniFile_sH

#include <Windows.h>
#include <TCHAR.h>

class CIniFile
{
protected:
	TCHAR m_PathName[MAX_PATH+1];
public:
	CIniFile(TCHAR * PathName);
	~CIniFile(void);

	bool WriteString(TCHAR * Section,TCHAR * Item,TCHAR * Text);
	bool WriteInteger(TCHAR * Section ,TCHAR * Item,int Val);
	bool WriteDouble(TCHAR * Section ,TCHAR * Item,double Val);
	bool WriteFloat(TCHAR * Section ,TCHAR * Item,float Val);
	bool WriteBoolean(TCHAR * Section ,TCHAR * Item,bool Val);
    
	int ReadString(TCHAR * Section,TCHAR * Item,TCHAR * RetText,int Length,TCHAR * DefText=_T(""));
	int ReadInteger(TCHAR * Section ,TCHAR * Item,int DefVal=0);
	double ReadDouble(TCHAR * Section ,TCHAR * Item,double DefVal=0);
	float ReadFloat(TCHAR * Section ,TCHAR * Item,float DefVal=0);
	bool ReadBoolean(TCHAR * Section ,TCHAR * Item,bool DefVal=false);

	TCHAR *GetCFGFile(void)
	{
		return m_PathName;
	}
};

#endif
