//---------------------------------------------------------------------------


#pragma hdrstop

#include "FixCommWapp.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

aboss_3rd::aboss_3rd()
{
    m_Counterchange     = NULL;
    m_SetFixCommVersion = NULL;
    m_SetFixCommSource  = NULL;
    m_SetFixCommTarget  = NULL;
    m_SetFixCommWtfs    = NULL;
    m_SetFixCommUser    = NULL;
    m_SetFixCommNode    = NULL;
    m_FixConnect        = NULL;
    m_FixConnectEx      = NULL;
    m_FixClose          = NULL;
    m_FixCreate         = NULL;
    m_FixSet            = NULL;
    m_FixGet            = NULL;
    m_FixSetInt         = NULL;
    m_FixSetDouble      = NULL;
    m_FixGetInt         = NULL;
    m_FixGetDouble      = NULL;
    m_FixWrite          = NULL;
    m_FixRead           = NULL;
    m_FixReadEx         = NULL;
    m_FixSetBuffer      = NULL;
    m_FixGetBuffer      = NULL;
    m_FixGetFunCode     = NULL;
    m_FixGetRecNo       = NULL;
    m_FixGetSequence    = NULL;
    m_FixIsConnect      = NULL;
                        

    m_SetFixCommSourceEx = NULL;
    m_SetFixCommTargetEx = NULL;
    m_SetFixCommWtfsEx   = NULL;
    m_SetFixCommUserEx   = NULL;
    m_SetFixCommNodeEx   = NULL;

    FDllHandle = LoadLibrary("FixComm.dll");

    if(!FDllHandle)
    {
        MessageBox(NULL,"导入动态链接库\"FixComm.dll\"失败！将退出应用程序。","ERROR!",MB_ICONERROR);
        return;
    }
    else
    {
        m_Counterchange     = (FCounterchange     )GetProcAddress(FDllHandle, "counterchange");
        m_SetFixCommVersion = (FSetFixCommVersion )GetProcAddress(FDllHandle, "SetFixCommVersion");
        m_SetFixCommSource  = (FSetFixCommSource  )GetProcAddress(FDllHandle, "SetFixCommSource");
        m_SetFixCommTarget  = (FSetFixCommTarget  )GetProcAddress(FDllHandle, "SetFixCommTarget");
        m_SetFixCommWtfs    = (FSetFixCommWtfs    )GetProcAddress(FDllHandle, "SetFixCommWtfs");
        m_SetFixCommUser    = (FSetFixCommUser    )GetProcAddress(FDllHandle, "SetFixCommUser");
        m_SetFixCommNode    = (FSetFixCommNode    )GetProcAddress(FDllHandle, "SetFixCommNode");
        m_FixConnect        = (FFixConnect        )GetProcAddress(FDllHandle, "FixConnect");
        m_FixConnectEx      = (FFixConnectEx      )GetProcAddress(FDllHandle, "FixConnectEx");
        m_FixClose          = (FFixClose          )GetProcAddress(FDllHandle, "FixClose");
        m_FixCreate         = (FFixCreate         )GetProcAddress(FDllHandle, "FixCreate");
        m_FixSet            = (FFixSet            )GetProcAddress(FDllHandle, "FixSet");
        m_FixGet            = (FFixGet            )GetProcAddress(FDllHandle, "FixGet");
        m_FixSetInt         = (FFixSetInt         )GetProcAddress(FDllHandle, "FixSetInt");
        m_FixSetDouble      = (FFixSetDouble      )GetProcAddress(FDllHandle, "FixSetDouble");
        m_FixGetInt         = (FFixGetInt         )GetProcAddress(FDllHandle, "FixGetInt");
        m_FixGetDouble      = (FFixGetDouble      )GetProcAddress(FDllHandle, "FixGetDouble");
        m_FixWrite          = (FFixWrite          )GetProcAddress(FDllHandle, "FixWrite");
        m_FixRead           = (FFixRead           )GetProcAddress(FDllHandle, "FixRead");
        m_FixReadEx         = (FFixReadEx         )GetProcAddress(FDllHandle, "FixReadEx");
        m_FixSetBuffer      = (FFixSetBuffer      )GetProcAddress(FDllHandle, "FixSetBuffer");
        m_FixGetBuffer      = (FFixGetBuffer      )GetProcAddress(FDllHandle, "FixGetBuffer");
        m_FixGetFunCode     = (FFixGetFunCode     )GetProcAddress(FDllHandle, "FixGetFunCode");
        m_FixGetRecNo       = (FFixGetRecNo       )GetProcAddress(FDllHandle, "FixGetRecNo");
        m_FixGetSequence    = (FFixGetSequence    )GetProcAddress(FDllHandle, "FixGetSequence");
        m_FixIsConnect      = (FFixIsConnect      )GetProcAddress(FDllHandle, "FixIsConnect");
        
        m_SetFixCommSourceEx = (FSetFixCommSourceEx)GetProcAddress(FDllHandle, "SetFixCommSourceEx");
        m_SetFixCommTargetEx = (FSetFixCommTargetEx)GetProcAddress(FDllHandle, "SetFixCommTargetEx");
        m_SetFixCommWtfsEx   = (FSetFixCommWtfsEx  )GetProcAddress(FDllHandle, "SetFixCommWtfsEx");
        m_SetFixCommUserEx   = (FSetFixCommUserEx  )GetProcAddress(FDllHandle, "SetFixCommUserEx");
        m_SetFixCommNodeEx   = (FSetFixCommNodeEx  )GetProcAddress(FDllHandle, "SetFixCommNodeEx");

        if (!(m_Counterchange     ||
            m_SetFixCommVersion   ||
            m_SetFixCommSource    ||
            m_SetFixCommTarget    ||
            m_SetFixCommWtfs      ||
            m_SetFixCommUser      ||
            m_SetFixCommNode      ||
            m_FixConnect          ||
            m_FixConnectEx        ||
            m_FixClose            ||
            m_FixCreate           ||
            m_FixSet              ||
            m_FixGet              ||
            m_FixSetInt           ||
            m_FixSetDouble        ||
            m_FixGetInt           ||
            m_FixGetDouble        ||
            m_FixWrite            ||
            m_FixRead             ||
            m_FixReadEx           ||
            m_FixSetBuffer        ||
            m_FixGetBuffer        ||
            m_FixGetFunCode       ||
            m_FixGetRecNo         ||
            m_FixGetSequence      ||
            m_FixIsConnect        ||
            m_SetFixCommSourceEx  ||
            m_SetFixCommTargetEx  ||
            m_SetFixCommWtfsEx    ||
            m_SetFixCommUserEx    ||
            m_SetFixCommNodeEx
            ))
        {
            bLoaded = false;
            MessageBox(NULL,"动态链接库中某些函数不存在！","ERROR!",MB_ICONERROR);
        }
        else
        {
            bLoaded = true;
        }
    }
}

aboss_3rd::~aboss_3rd()
{
    if (FDllHandle)
        FreeLibrary(FDllHandle);
}

char * aboss_3rd::counterchange( char *pData )
{
    if (m_Counterchange)
        return m_Counterchange(pData);   
    else
        return "";
}

void aboss_3rd::SetFixCommVersion( const char *pVersion )
{
    if (m_SetFixCommVersion)
        m_SetFixCommVersion(pVersion);
}

void aboss_3rd::SetFixCommSource( const char * pSource )
{
    if (m_SetFixCommSource)
        m_SetFixCommSource(pSource);
}

void aboss_3rd::SetFixCommTarget( const char * pTarget )
{
    if (m_SetFixCommTarget)
        m_SetFixCommTarget(pTarget);
}

void aboss_3rd::SetFixCommWtfs( const char *pWtfs )
{
    if (m_SetFixCommWtfs)
        m_SetFixCommWtfs(pWtfs);
}

void aboss_3rd::SetFixCommUser( const char *pUser )
{
    if (m_SetFixCommUser)
        m_SetFixCommUser(pUser);
}

void aboss_3rd::SetFixCommNode( const char *pNode )
{
    if (m_SetFixCommNode)
        m_SetFixCommNode(pNode);
}

void *  aboss_3rd::FixConnect(const char *pDest,const char *pRemote)
{
    if (m_FixConnect)
        return m_FixConnect(pDest, pRemote);
    else
        return NULL;
}

void *  aboss_3rd::FixConnectEx(const char *pDest,const char *pRemote,int nTimeOut)
{
    if (m_FixConnectEx)
        return m_FixConnectEx(pDest, pRemote, nTimeOut);
    else
        return NULL;
}

void aboss_3rd::FixClose( void *pFix )
{
    if (m_FixClose)
        m_FixClose(pFix);
}

void aboss_3rd::FixCreate( void *pFix,int nFunCode )
{
    if (m_FixCreate)
        m_FixCreate(pFix, nFunCode);
}

void aboss_3rd::FixSet( void *pFix,int nItem,const char *pItem )
{
    if (m_FixSet)
        m_FixSet(pFix, nItem, pItem);
}

char *  aboss_3rd::FixGet( void *pFix,int nItem,char *pItem,int nMaxSize )
{
    if (m_FixGet)
        return m_FixGet(pFix, nItem, pItem, nMaxSize);
    else
        return "";
}

void aboss_3rd::FixSetInt( void *pFix,int nItem,int nValue )
{
    if (m_FixSetInt)
        m_FixSetInt(pFix, nItem, nValue);
}

void aboss_3rd::FixSetDouble( void *pFix,int nItem,double lfValue )
{
    if (m_FixSetDouble)
        m_FixSetDouble(pFix, nItem, lfValue);
}

int  aboss_3rd::FixGetInt( void *pFix,int nItem )
{
    if (m_FixGetInt)
        return m_FixGetInt(pFix, nItem);
    else
        return 0;
}

double aboss_3rd::FixGetDouble( void *pFix,int nItem )
{
    if (m_FixGetDouble)
        return m_FixGetDouble(pFix, nItem);
    else
        return 0;
}

int aboss_3rd::FixWrite( void *pFix )
{
    if (m_FixWrite)
        return m_FixWrite(pFix);
    else
        return 0;
}

int aboss_3rd::FixRead( void *pFix )
{
    if (m_FixRead)
        return m_FixRead(pFix);
    else
        return 0;
}

int aboss_3rd::FixReadEx( void *pFix,int nTimeout )
{
    if (m_FixReadEx)
        return m_FixReadEx(pFix, nTimeout);
    else
        return 0;
}

BOOL aboss_3rd::FixSetBuffer( void *pFix,const char *pData )
{
    if (m_FixSetBuffer)
        return m_FixSetBuffer(pFix, pData);
    else
        return false;
}

BOOL aboss_3rd::FixGetBuffer( void *pFix,char *pData,int nMaxSize )
{
    if (m_FixGetBuffer)
        return m_FixGetBuffer(pFix, pData, nMaxSize);
    else
        return false;
}

int aboss_3rd::FixGetFunCode( void *pFix )
{
    if (m_FixGetFunCode)
        return m_FixGetFunCode(pFix);
    else
        return 0;
}

int aboss_3rd::FixGetRecNo( void *pFix )
{
    if (m_FixGetRecNo)
        return m_FixGetRecNo(pFix);
    else
        return 0;
}

int	aboss_3rd::FixGetSequence( void *pFix)
{
    if (m_FixGetSequence)
        return m_FixGetSequence(pFix);
    else
        return 0;
}

BOOL aboss_3rd::FixIsConnect( void *pFix)
{
    if (m_FixIsConnect)
        return m_FixIsConnect(pFix);
    else
        return 0;
}

void aboss_3rd::SetFixCommSourceEx	(void *pFix, const char * pSource)
{
    if (m_SetFixCommSourceEx)
        m_SetFixCommSourceEx(pFix, pSource);
}

void aboss_3rd::SetFixCommTargetEx	(void *pFix, const char * pTarget)
{
    if (m_SetFixCommTargetEx)
        m_SetFixCommTargetEx(pFix, pTarget);
}

void aboss_3rd::SetFixCommWtfsEx	(void *pFix, const char *pWtfs)
{
    if (m_SetFixCommWtfsEx)
        m_SetFixCommWtfsEx(pFix, pWtfs);

}

void aboss_3rd::SetFixCommUserEx	( void *pFix,const char *pUser)
{
    if (m_SetFixCommUserEx)
        m_SetFixCommUserEx(pFix, pUser);
}

void aboss_3rd::SetFixCommNodeEx	( void *pFix,const char *pNode )
{
    if (m_SetFixCommNodeEx)
        m_SetFixCommNodeEx(pFix, pNode);
}

