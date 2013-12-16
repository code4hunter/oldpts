#ifndef IniFileH
#define IniFileH

#include <Windows.h>

class CIniFile
{
protected:
	TCHAR m_PathName[MAX_PATH+1];
public:
	CIniFile(char * PathName);
	~CIniFile(void);

	bool WriteString(char * Section,char * Item,char * Text);
	bool WriteInteger(char * Section ,char * Item,int Val);
	bool WriteDouble(char * Section ,char * Item,double Val);
	bool WriteFloat(char * Section ,char * Item,float Val);
	bool WriteBoolean(char * Section ,char * Item,bool Val);
    
	int ReadString(char * Section,char * Item,char * RetText,int Length,char * DefText="");
	int ReadInteger(char * Section ,char * Item,int DefVal=0);
	double ReadDouble(char * Section ,char * Item,double DefVal=0);
	float ReadFloat(char * Section ,char * Item,float DefVal=0);
	bool ReadBoolean(char * Section ,char * Item,bool DefVal=false);

	TCHAR *GetCFGFile(void)
	{
		return m_PathName;
	}
};

#endif
