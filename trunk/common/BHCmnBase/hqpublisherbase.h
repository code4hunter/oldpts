//#pragma once
#ifndef HQPublisherBase_H
#define HQPublisherBase_H

#include "UDynStr.h"
#include <comutil.h>
#pragma comment(lib, "comsupp.lib")
#pragma comment(lib, "comsuppw.lib")


#define USE_MICRO_HQ	//使用细节数据
#define MAX_RANGE_MSG_LEN	200

#define MAKE_HRESULT_ERROR(nError) \
    MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, nError)

[
	export,
	uuid(39FB3AB1-DE17-4a10-A3DB-95236C055135), 
	helpstring("Possible error return codes")
] 
enum HQError
{  
	//[helpstring("Open file error")] 
	hqErrorOpenFile = MAKE_HRESULT_ERROR(0xffff),

	//[helpstring("Read file error")] 
	hqErrorReadFile = MAKE_HRESULT_ERROR(0xfffe),

	//[helpstring("Init HQ error: Open HQ file error or Read HQ file error")] 
	hqErrorInitHQ = MAKE_HRESULT_ERROR(0xfffd),

	//[helpstring("unexpected error")] 
	hqErrorUnknown = MAKE_HRESULT_ERROR(0xfffc),

	//[helpstring("no init data according to the filter")] 
	hqErrorNoInitData = MAKE_HRESULT_ERROR(0xfffb),

	//[helpstring("invalid raw filter")] 
	hqErrorRawFilter = MAKE_HRESULT_ERROR(0xfffa),

	//[helpstring("current time is less than InitTime")] 
	hqErrorInitTime = MAKE_HRESULT_ERROR(0xfff9),

	//[helpstring("the number of stocks is less than or equal to zero")] 
	hqErrorStockNum = MAKE_HRESULT_ERROR(0xfff8),	

	//[helpstring("error in sorting stocks with id")] 
	hqErrorSortStock = MAKE_HRESULT_ERROR(0xfff7),	
};

// IPublisherBase
[
	object,
	uuid("26771309-83C6-4578-8B54-3C1F3BE2DDE2"),
	dual,	helpstring("IPublisherBase 接口"),
	pointer_default(unique)
]
__interface IPublisherBase : IDispatch
{
	[propget, id(1), helpstring("属性 DESC")] HRESULT DESC([out, retval] BSTR* pVal);
	[propget, id(2), helpstring("属性 Config")] HRESULT Config([out, retval] BSTR* pVal);
	[propput, id(2), helpstring("属性 Config")] HRESULT Config([in] BSTR newVal);
	[id(3), helpstring("方法GetInitData")] HRESULT GetInitData([in,satype(BYTE)] SAFEARRAY * Filter, [out, satype(BYTE)] SAFEARRAY ** DataPtr);
	[id(4), helpstring("方法FixFilter")] HRESULT FixFilter([in,satype(BYTE)] SAFEARRAY * Filter, [out, satype(BYTE)] SAFEARRAY ** FixedFilter);
	[id(5), helpstring("方法GetEvent")] HRESULT GetEvent([out, satype(BYTE)] SAFEARRAY ** DataPtr, [out] LONG * state);
	[propget, id(6), helpstring("属性 TopicName")] HRESULT TopicName([out, retval] BSTR* pVal);
	[propput, id(6), helpstring("属性 TopicName")] HRESULT TopicName([in] BSTR newVal);
};

// ISetup
[
	object,
	uuid("00795A4F-3B1A-49A2-875E-93DF152E7F4B"),
	dual,	helpstring("ISetup 接口"),
	pointer_default(unique)
]
__interface ISetup : IDispatch
{
	[id(1), helpstring("方法 EnumFields")] HRESULT EnumFields([out, satype(BSTR)] SAFEARRAY ** Fields, [out, satype(VARIANT)] SAFEARRAY ** Values, [in] BOOL bValue);
	[id(2), helpstring("方法 GetValue")] HRESULT GetValue([in] BSTR FieldName, [out] VARIANT* Value);
	[id(3), helpstring("方法 SetValue")] HRESULT SetValue([in] BSTR FieldName, [in] VARIANT Value);
};

//操作注册表
LONG RegGetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData, HKEY hKey = HKEY_LOCAL_MACHINE);
LONG RegSetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwType, const BYTE* lpData, DWORD cbData, HKEY hKey = HKEY_LOCAL_MACHINE);
HRESULT RegGetValue(LPCTSTR lpSubKey, BSTR FieldName, VARIANT* Value);
HRESULT RegSetValue(LPCTSTR lpSubKey, BSTR FieldName, VARIANT Value);

//股票代码排序
int CompareSecuID(const void *a, const void *b);

//生成SAFEARRAY，并进行数据复制
HRESULT MemAllocSafeArray(SAFEARRAY **pArray, LONG lSize, void *pData);

//解析过滤器
bool ParseFilter(TPriceList *pPrice, long lStockNum, BYTE * Filter, LONG FilterSize, long **NewFilter, long &FilterCount);

//数据拷贝复制
void MemcpyUDPPList(char *ABuf, TPriceList *APrice, int ANo);
void MemcpyUDPPListInit(char *ABuf, TPriceList *APrice, int ANo);

//操作注册表
LONG RegGetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData, HKEY hKey)
{
    HKEY phkResult; 
    LONG lRet = 0;
	DWORD dwBufLen = 0;

    lRet = RegOpenKeyEx(hKey, lpSubKey, NULL, KEY_ALL_ACCESS, &phkResult); 
	if( lRet != ERROR_SUCCESS )
		return lRet;

	lRet = RegQueryValueEx( phkResult, lpValueName, NULL, lpType, lpData, lpcbData);
	if( lRet != ERROR_SUCCESS)
	{
		RegCloseKey(phkResult); 
		return lRet;
	}

	return RegCloseKey(phkResult); 
}

LONG RegSetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwType, const BYTE* lpData, DWORD cbData, HKEY hKey)
{
	HKEY phkResult; 
	LONG lRet = 0;

	lRet = RegCreateKeyEx( hKey,									\
							lpSubKey,								\
							0,										\
							NULL,									\
							REG_OPTION_NON_VOLATILE,				\
							KEY_CREATE_SUB_KEY|KEY_WRITE|KEY_READ,	\
							NULL, 
							&phkResult, 
							NULL );

	//REG_OPTION_NON_VOLATILE 指明键永久保留.安全结构指明NULL,自动获得一默认值
	//成功返回ERROR_SUCCESS,否则返回错误代码 

	if( lRet != ERROR_SUCCESS )
		return lRet;
	
	lRet = RegSetValueEx(phkResult,             // subkey handle 
            lpValueName,			       // value name 
            0,							   // must be zero 
            dwType,						   // value type 
            lpData,							// pointer to value data 
            cbData);						// length of value data 

	if( lRet != ERROR_SUCCESS )
	{
		RegCloseKey(phkResult);
		return lRet;
	}

	return RegCloseKey(phkResult); 
}

HRESULT RegGetValue(LPCTSTR lpSubKey, BSTR FieldName, VARIANT* Value)
{
	char *lpszField = _com_util::ConvertBSTRToString(FieldName);

	DWORD dwType;
	char szBuffer[MAX_PATH + 1];
	ZeroMemory(szBuffer, MAX_PATH + 1);
	DWORD dwBufLen = MAX_PATH;

	LONG lRet = ::RegGetValue(HKEY_LOCAL_MACHINE,						\
							lpSubKey,									 \
							FieldName,											\
							RRF_RT_ANY,										\
							&dwType,									 \
							(PVOID)szBuffer,							 \
							&dwBufLen);

	if( (lRet != ERROR_SUCCESS) || (dwBufLen > MAX_PATH) )
		return lRet;

	switch(dwType)
	{
	case REG_DWORD:
		Value->vt = VT_I4;
		Value->lVal = *((long *)szBuffer);
	break;

	case REG_SZ:
		Value->vt = VT_BSTR;
		Value->bstrVal = _com_util::ConvertStringToBSTR(szBuffer);//SysAllocString(FieldName/*OLESTR()*/);
	break;

	default:
		return S_FALSE;
	}

	return S_OK;
}

HRESULT RegSetValue(LPCTSTR lpSubKey, BSTR FieldName, VARIANT Value)
{
	char *lpszField = _com_util::ConvertBSTRToString(FieldName);

	DWORD dwType;
	char *lpszBuffer = NULL;
	DWORD dwBufLen = 0;

	switch(Value.vt)
	{
	case VT_I4:
		dwType = REG_DWORD;
		lpszBuffer = (char *)&(Value.lVal);
		dwBufLen = 4;
	break;

	case VT_BSTR:
		dwType = REG_SZ;
		lpszBuffer = _com_util::ConvertBSTRToString(Value.bstrVal);
		dwBufLen = strlen(lpszBuffer) + 1;
	break;
	default:
		return S_FALSE;
	}

	LONG lRet = RegSetValue(lpSubKey, FieldName, dwType, (BYTE *)lpszBuffer, dwBufLen);
	
	if(lRet != ERROR_SUCCESS)
		return lRet;
	
	return S_OK;
}

int CompareSecuID(const void *a, const void *b)
{
  return memicmp((char *)a+sizeof(char), (char *)b+sizeof(char), 6);
}


HRESULT MemAllocSafeArray(SAFEARRAY **pArray, LONG lSize, void *pData)
{
	SAFEARRAYBOUND sabound[1]; 
	sabound[0].cElements = lSize; 
	sabound[0].lLbound = 0; 
	*pArray = SafeArrayCreate(VT_UI1, 1, sabound); 
	
	void *pBuf = NULL; 
	HRESULT hr = SafeArrayAccessData(*pArray, &pBuf); 
	if( FAILED(hr) )
		return hr;

	memcpy(pBuf, pData, lSize);
	SafeArrayUnaccessData(*pArray); 

	return S_OK;
}

//解析过滤器
bool GetAStockCode(char *Filter, char *szCode, int &Offset)
{
	int nLen = strlen(Filter);
	int nStartPos = -1, nEndPos = -1;
	for(int i=0; i<nLen; i++)
	{
		if(Filter[i] == '"')////
		{
			nStartPos = i;
			break;
		}
	}

	if(nStartPos != -1)
	{
		for(int i=nStartPos+1; i<nLen; i++)
		{
			if(Filter[i] == '"')////
			{
				nEndPos = i;
				break;
			}
		}
	}

	if(nStartPos != -1 && nEndPos != -1)
	{
		nLen = nEndPos - nStartPos;
		if(nLen > 1  && nLen < 8)
		{
			strncpy(szCode, Filter+nStartPos+1, nLen-1);
			szCode[nLen] = '\0';
			Offset = nEndPos + 1;//下一次的检索位置

			return true;
		}
	}

	return false;
}

int GetCodeIndex(char *szCode, TPriceList *pPrice, long lStockNum)
{
	for(int i=0; i<lStockNum; i++)
	{
		if(strcmpi(szCode, pPrice[i].SecuID+1) == 0)
			return i;
	}

	return -1;
}

bool GetCodeIndexes(char *szCode, long *NewFilter, long &FilterCount, TPriceList *pPrice, long lStockNum)
{
	FilterCount = 0;

	//"600*"
	int nLen = strlen(szCode);
	int nPos = -1;
	for(int i=0; i<nLen; i++)
	{
		if(szCode[i] == '*')
			nPos = i;
	}

	//没有"*"
	if(nPos == -1)
	{
		nPos = 6;//直接比较此代码
	}

	if(nPos == 0)//"*"在首位
	{
		int nOffset = nLen - 1;//实际比较位数
		nOffset = 6 - nOffset;//7 = sizeof(TSecuDesc::SecuID) - 1
		if(nOffset < 0)
			return false;

		FilterCount = 0;
		for(int i=0; i<lStockNum; i++)
		{
			if(strcmpi(szCode+1, pPrice[i].SecuID+nOffset+1) == 0)//+1---忽略'H'or 'S'
			{
				NewFilter[FilterCount] = i;
				FilterCount++;
			}
		}
	}
	else
	{
		FilterCount = 0;
		for(int i=0; i<lStockNum; i++)
		{
			if(strnicmp(szCode, pPrice[i].SecuID+1, nPos) == 0)//+1---忽略'H'or 'S'
			{
				NewFilter[FilterCount] = i;
				FilterCount++;
			}
		}
	}

	return true;
}

int GetPos(char *lpszString, char ch)
{
	int nLen = strlen(lpszString);
	for(int i=0; i<nLen; i++)
	{
		if(lpszString[i] == ch)////
			return i;
	}

	return -1;
}

bool ParseFilter(TPriceList *pPrice, long lStockNum, BYTE * Filter, LONG FilterSize, long **NewFilter, long &FilterCount)
{
	char *szFilter = (char *)Filter;

	char szName[10] = {0x0, };
	char szKeyWord[8] = {0x0, };
	char szCode[8] = {0x0, };
	bool bUseKeyLike = false;

	sscanf(szFilter, "%9s%7s", szName, szKeyWord);

	if(strcmpi(szName, "code") != 0)
		return false;

	if(strcmpi(szKeyWord, "IN") != 0)
	{
		if(strcmpi(szKeyWord, "LIKE") != 0)
			return false;

		bUseKeyLike = true;
	}

	*NewFilter = new long[lStockNum];
	ZeroMemory(*NewFilter, sizeof(long) * lStockNum);
	int nIndex = -1;
	int nOffset = 0;
	if(bUseKeyLike)
	{
		if(!GetAStockCode(szFilter, szCode, nOffset))
		{
			delete [] *NewFilter;
			*NewFilter = NULL;
			return false;
		}
		
		if(!GetCodeIndexes(szCode, *NewFilter, FilterCount, pPrice, lStockNum))
		{
			delete [] *NewFilter;
			*NewFilter = NULL;
			return false;
		}
	}
	else
	{
		FilterCount = 0;
		while(true)
		{
			szFilter += nOffset;
			if(!GetAStockCode(szFilter, szCode, nOffset))
				break;

			nIndex = GetCodeIndex(szCode, pPrice, lStockNum);
			if(nIndex < 0 || nIndex >= lStockNum)
				break;
			
			(*NewFilter)[FilterCount] = nIndex;
			FilterCount++;				
		}
	}

	if(FilterCount == 0)
	{
		delete [] *NewFilter;
		*NewFilter = NULL;
	}
	else
	{
		FilterCount *= sizeof(long);//返回实际过滤器的字节数
	}

	return true;
}

void MemcpyUDPPList(char *ABuf, TPriceList *APrice, int ANo)
{
	TUDPPriceList AUDPPrice;

	AUDPPrice.SecuNo = ANo;
	AUDPPrice.Vlm    = APrice->Vlm;
	AUDPPrice.PVlm    = APrice->PVlm;
	AUDPPrice.Mny    = APrice->Mny;
	AUDPPrice.Co     = APrice->Co;
	AUDPPrice.Ch     = APrice->Ch;
	AUDPPrice.Cl     = APrice->Cl;
	AUDPPrice.Cp     = APrice->Cp;
	AUDPPrice.Pe     = APrice->Pe;

	AUDPPrice.Bv1    = APrice->Bv1;
	AUDPPrice.Bv2    = APrice->Bv2;
	AUDPPrice.Bv3    = APrice->Bv3;
	AUDPPrice.Bv4    = APrice->Bv4;
	AUDPPrice.Bv5    = APrice->Bv5;

	AUDPPrice.Cbp    = APrice->Cbp;
	AUDPPrice.Bp2    = APrice->Bp2;
	AUDPPrice.Bp3    = APrice->Bp3;
	AUDPPrice.Bp4    = APrice->Bp4;
	AUDPPrice.Bp5    = APrice->Bp5;

	AUDPPrice.Sv1    = APrice->Sv1;
	AUDPPrice.Sv2    = APrice->Sv2;
	AUDPPrice.Sv3    = APrice->Sv3;
	AUDPPrice.Sv4    = APrice->Sv4;
	AUDPPrice.Sv5    = APrice->Sv5;

	AUDPPrice.Csp    = APrice->Csp;
	AUDPPrice.Sp2    = APrice->Sp2;
	AUDPPrice.Sp3    = APrice->Sp3;
	AUDPPrice.Sp4    = APrice->Sp4;
	AUDPPrice.Sp5    = APrice->Sp5;

	AUDPPrice.Abv    = APrice->Abv;
	AUDPPrice.Cv     = APrice->Cv;
	AUDPPrice.Time   = APrice->Time;

	AUDPPrice.Cmv    = APrice->Cmv;
	AUDPPrice.Cmm    = APrice->Cmm;
	AUDPPrice.C5ma   = APrice->C5ma;
	AUDPPrice.C4ma   = APrice->C4ma;
	AUDPPrice.C3ma   = APrice->C3ma;
	AUDPPrice.C2ma   = APrice->C2ma;
	AUDPPrice.C1ma   = APrice->C1ma;

	memcpy(ABuf, &AUDPPrice, sizeof(TUDPPriceList));
}

void MemcpyUDPPListInit(char *ABuf, TPriceList *APrice, int ANo)
{
	long lSecuNo = ANo;
	memcpy(ABuf, &lSecuNo, sizeof(long));
	memcpy(ABuf + sizeof(long), APrice, sizeof(TPriceList));
}

#endif