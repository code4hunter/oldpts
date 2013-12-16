//---------------------------------------------------------------------------

#ifndef FixCommWappH
#define FixCommWappH
//---------------------------------------------------------------------------
#include <windows.h>
#include "FixComm.h"
#include "FIXDEF.H"   //FIXDEF.H 在其他文档中提供

typedef char * WINAPI (* FCounterchange)( char *pData );
typedef void   WINAPI (* FSetFixCommVersion)( const char *pVersion );
typedef void   WINAPI (* FSetFixCommSource)( const char * pSource );
typedef void   WINAPI (* FSetFixCommTarget)( const char * pTarget );
typedef void   WINAPI (* FSetFixCommWtfs)( const char *pWtfs );
typedef void   WINAPI (* FSetFixCommUser)( const char *pUser );
typedef void   WINAPI (* FSetFixCommNode)( const char *pNode );
typedef void * WINAPI (* FFixConnect)(const char *pDest,const char *pRemote);
typedef void * WINAPI (* FFixConnectEx)(const char *pDest,const char *pRemote,int nTimeOut);
typedef void   WINAPI (* FFixClose)( void *pFix );
typedef void   WINAPI (* FFixCreate)( void *pFix,int nFunCode );
typedef void   WINAPI (* FFixSet)( void *pFix,int nItem,const char *pItem );
typedef char * WINAPI (* FFixGet)( void *pFix,int nItem,char *pItem,int nMaxSize );
typedef void   WINAPI (* FFixSetInt)( void *pFix,int nItem,int nValue );
typedef void   WINAPI (* FFixSetDouble)( void *pFix,int nItem,double lfValue );
typedef int    WINAPI (* FFixGetInt)( void *pFix,int nItem );
typedef double WINAPI (* FFixGetDouble)( void *pFix,int nItem );
typedef int    WINAPI (* FFixWrite)( void *pFix );
typedef int    WINAPI (* FFixRead)( void *pFix );
typedef int    WINAPI (* FFixReadEx)( void *pFix,int nTimeout );
typedef BOOL   WINAPI (* FFixSetBuffer)( void *pFix,const char *pData );
typedef BOOL   WINAPI (* FFixGetBuffer)( void *pFix,char *pData,int nMaxSize );
typedef int    WINAPI (* FFixGetFunCode)( void *pFix );
typedef int    WINAPI (* FFixGetRecNo)( void *pFix );
typedef int	   WINAPI (* FFixGetSequence)( void *pFix);
typedef BOOL   WINAPI (* FFixIsConnect)( void *pFix);


typedef void WINAPI (* FSetFixCommSourceEx)(void *pFix, const char * pSource	);
typedef void WINAPI (* FSetFixCommTargetEx)(void *pFix, const char * pTarget	);
typedef void WINAPI (* FSetFixCommWtfsEx)(void *pFix, const char *pWtfs		);
typedef void WINAPI (* FSetFixCommUserEx)( void *pFix,const char *pUser		);
typedef void WINAPI (* FSetFixCommNodeEx)( void *pFix,const char *pNode );

class aboss_3rd
{
private:
    FCounterchange               m_Counterchange;
    FSetFixCommVersion           m_SetFixCommVersion ;
    FSetFixCommSource            m_SetFixCommSource;
    FSetFixCommTarget            m_SetFixCommTarget;
    FSetFixCommWtfs              m_SetFixCommWtfs;
    FSetFixCommUser              m_SetFixCommUser;
    FSetFixCommNode              m_SetFixCommNode;
    FFixConnect                  m_FixConnect;
    FFixConnectEx                m_FixConnectEx;
    FFixClose                    m_FixClose ;
    FFixCreate                   m_FixCreate ;
    FFixSet                      m_FixSet ;
    FFixGet                      m_FixGet ;
    FFixSetInt                   m_FixSetInt;
    FFixSetDouble                m_FixSetDouble  ;
    FFixGetInt                   m_FixGetInt   ;
    FFixGetDouble                m_FixGetDouble ;
    FFixWrite                    m_FixWrite ;
    FFixRead                     m_FixRead  ;
    FFixReadEx                   m_FixReadEx;
    FFixSetBuffer                m_FixSetBuffer;
    FFixGetBuffer                m_FixGetBuffer ;
    FFixGetFunCode               m_FixGetFunCode ;
    FFixGetRecNo                 m_FixGetRecNo   ;
    FFixGetSequence              m_FixGetSequence ;
    FFixIsConnect                m_FixIsConnect ;


    FSetFixCommSourceEx          m_SetFixCommSourceEx ;
    FSetFixCommTargetEx          m_SetFixCommTargetEx;
    FSetFixCommWtfsEx            m_SetFixCommWtfsEx  ;
    FSetFixCommUserEx            m_SetFixCommUserEx ;
    FSetFixCommNodeEx            m_SetFixCommNodeEx  ;

    HINSTANCE  FDllHandle;

    bool bLoaded;

public:
    aboss_3rd();
    ~aboss_3rd();

    char *  counterchange( char *pData );
    void    SetFixCommVersion( const char *pVersion );
    void    SetFixCommSource( const char * pSource );
    void    SetFixCommTarget( const char * pTarget );
    void    SetFixCommWtfs( const char *pWtfs );
    void    SetFixCommUser( const char *pUser );
    void    SetFixCommNode( const char *pNode );
    void *  FixConnect(const char *pDest,const char *pRemote);
    void *  FixConnectEx(const char *pDest,const char *pRemote,int nTimeOut);
    void    FixClose( void *pFix );
    void    FixCreate( void *pFix,int nFunCode );
    void    FixSet( void *pFix,int nItem,const char *pItem );
    char *  FixGet( void *pFix,int nItem,char *pItem,int nMaxSize );
    void    FixSetInt( void *pFix,int nItem,int nValue );
    void    FixSetDouble( void *pFix,int nItem,double lfValue );
    int     FixGetInt( void *pFix,int nItem );
    double  FixGetDouble( void *pFix,int nItem );
    int     FixWrite( void *pFix );
    int     FixRead( void *pFix );
    int     FixReadEx( void *pFix,int nTimeout );
    BOOL    FixSetBuffer( void *pFix,const char *pData );
    BOOL    FixGetBuffer( void *pFix,char *pData,int nMaxSize );
    int     FixGetFunCode( void *pFix );
    int     FixGetRecNo( void *pFix );
    int	    FixGetSequence( void *pFix);
    BOOL    FixIsConnect( void *pFix);


    void    SetFixCommSourceEx	(void *pFix, const char * pSource	);
    void    SetFixCommTargetEx	(void *pFix, const char * pTarget	);
    void    SetFixCommWtfsEx	(void *pFix, const char *pWtfs		);
    void    SetFixCommUserEx	( void *pFix,const char *pUser		);
    void    SetFixCommNodeEx	( void *pFix,const char *pNode );
};

#endif
