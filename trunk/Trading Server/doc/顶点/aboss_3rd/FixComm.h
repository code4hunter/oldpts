#ifndef  APEX_FIXCOMM_API_INCLUDE
   #define  APEX_FIXCOMM_API_INCLUDE

#ifdef FIXCOMM_EXPORTS
#define FIXCOMM_API __declspec(dllexport)
#else
#define FIXCOMM_API __declspec(dllimport)
#endif

//简单加密函数(用户密码加密)
FIXCOMM_API char * WINAPI counterchange( char *pData );
FIXCOMM_API void   WINAPI SetFixCommVersion( const char *pVersion );
FIXCOMM_API void   WINAPI SetFixCommSource( const char * pSource );
FIXCOMM_API void   WINAPI SetFixCommTarget( const char * pTarget );
FIXCOMM_API void   WINAPI SetFixCommWtfs( const char *pWtfs );
FIXCOMM_API void   WINAPI SetFixCommUser( const char *pUser );
FIXCOMM_API void   WINAPI SetFixCommNode( const char *pNode );
FIXCOMM_API void * WINAPI FixConnect(const char *pDest,const char *pRemote);
FIXCOMM_API void * WINAPI FixConnectEx(const char *pDest,const char *pRemote,int nTimeOut);
FIXCOMM_API void   WINAPI FixClose( void *pFix );
FIXCOMM_API void   WINAPI FixCreate( void *pFix,int nFunCode );
FIXCOMM_API void   WINAPI FixSet( void *pFix,int nItem,const char *pItem );
FIXCOMM_API char * WINAPI FixGet( void *pFix,int nItem,char *pItem,int nMaxSize );
FIXCOMM_API void   WINAPI FixSetInt( void *pFix,int nItem,int nValue );
FIXCOMM_API void   WINAPI FixSetDouble( void *pFix,int nItem,double lfValue );
FIXCOMM_API int    WINAPI FixGetInt( void *pFix,int nItem );
FIXCOMM_API double WINAPI FixGetDouble( void *pFix,int nItem );
FIXCOMM_API int    WINAPI FixWrite( void *pFix );
FIXCOMM_API int    WINAPI FixRead( void *pFix );
FIXCOMM_API int    WINAPI FixReadEx( void *pFix,int nTimeout );
FIXCOMM_API BOOL   WINAPI FixSetBuffer( void *pFix,const char *pData );
FIXCOMM_API BOOL   WINAPI FixGetBuffer( void *pFix,char *pData,int nMaxSize );
FIXCOMM_API int    WINAPI FixGetFunCode( void *pFix );
FIXCOMM_API int    WINAPI FixGetRecNo( void *pFix );
FIXCOMM_API int	   WINAPI FixGetSequence( void *pFix);
FIXCOMM_API BOOL   WINAPI FixIsConnect( void *pFix);


FIXCOMM_API void WINAPI SetFixCommSourceEx	(void *pFix, const char * pSource	);
FIXCOMM_API void WINAPI SetFixCommTargetEx	(void *pFix, const char * pTarget	);
FIXCOMM_API void WINAPI SetFixCommWtfsEx	(void *pFix, const char *pWtfs		);
FIXCOMM_API void WINAPI SetFixCommUserEx	( void *pFix,const char *pUser		);
FIXCOMM_API void WINAPI SetFixCommNodeEx	( void *pFix,const char *pNode );

#endif
