һ��˵��
	1�����ĵ��������ڶ���A.BOSS��̨ϵͳ�м������Χ�ӿڡ�
	2������A.BOSSϵͳ��ǰ�˵����ݽӿ�ʹ��FIX��ʽ��
	3������A.BOSS�������м���ӿڰ��������ļ���
	   FIXCOMM.DLL,FIXCOMM.H,FIXCOMM.LIB,README.TXT
	4��FIXCOMM.DLL ΪWin32 ��̬���ӿ⡣
	5��ʹ��MS VC++��д����A.BOSS�������м���ӿ�ʱ��ʹ��FIXCOMM.LIB��
	6�����ĵ������������ҵ��ӿڣ����㹫˾�����������ĵ����ṩ��
	7������ʹ�ó����ӡ�

���������б�
	����A.BOSS�������ӿ��ṩ���»���������
	1�� FIXCOMM_API char * WINAPI counterchange( char *pData );
	2�� FIXCOMM_API void   WINAPI SetFixCommVersion( const char *pVersion );
	3�� FIXCOMM_API void   WINAPI SetFixCommSource( const char * pSource );
	4�� FIXCOMM_API void   WINAPI SetFixCommTarget( const char * pTarget );
	5�� FIXCOMM_API void   WINAPI SetFixCommWtfs( const char *pWtfs );
	6�� FIXCOMM_API void   WINAPI SetFixCommUser( const char *pUser );
	7�� FIXCOMM_API void * WINAPI FixConnect(const char *pDest,const char *pRemote );
	8�� FIXCOMM_API void * WINAPI FixConnectEx(const char *pDest,const char *pRemote,int nTimeOut);
	9�� FIXCOMM_API void   WINAPI FixClose( void *pFix );
	10��FIXCOMM_API void   WINAPI FixCreate( void *pFix,int nFunCode );
	11��FIXCOMM_API void   WINAPI FixSet( void *pFix,int nItem,const char *pItem );
	12��FIXCOMM_API void   WINAPI FixSetInt( void *pFix,int nItem,int nValue );
	13��FIXCOMM_API void   WINAPI FixSetDouble( void *pFix,int nItem,double lfValue );
	14��FIXCOMM_API char * WINAPI FixGet( void *pFix,int nItem,char *pItem,int nMaxSize );
	15��FIXCOMM_API int    WINAPI FixGetInt( void *pFix,int nItem );
	16��FIXCOMM_API double WINAPI FixGetDouble( void *pFix,int nItem );
	17��FIXCOMM_API int    WINAPI FixWrite( void *pFix );
	18��FIXCOMM_API int    WINAPI FixRead( void *pFix );
	19��FIXCOMM_API int    WINAPI FixReadEx( void *pFix,int nTimeout );
    20��FIXCOMM_API BOOL   WINAPI FixSetBuffer( void *pFix,const char *pData );
    21��FIXCOMM_API BOOL   WINAPI FixGetBuffer( void *pFix,char *pData,int nMaxSize );
	22��FIXCOMM_API int    WINAPI FixGetFunCode( void *pFix );
	23��FIXCOMM_API int    WINAPI FixGetRecNo( void *pFix );
	24��FIXCOMM_API void   WINAPI SetFixCommSourceEx(void *pFix, const char * pSource );
	25��FIXCOMM_API void   WINAPI SetFixCommTargetEx(void *pFix, cnst char * pTarget );
	26��FIXCOMM_API void   WINAPI SetFixCommWtfsEx(void *pFix  , const char *pWtfs );
	27��FIXCOMM_API void   WINAPI SetFixCommUserEx(void *pFix  , const char *pUser );
	28��FIXCOMM_API void    WINAPI SetFixCommNode( const char *pNode );
	29��FIXCOMM_API void    WINAPI SetFixCommNodeEx(void *pFix  ,  const char *pNode );



��������˵��
	1�� �򵥼��ܺ�����
		 FIXCOMM_API char * WINAPI counterchange( char *pData );
		 ˵�������������ֶ����û�����ļ��ܴ���
	2�� ���ýӿ�ʹ�õİ汾�š�
	    FIXCOMM_API void   WINAPI SetFixCommVersion( const char *pVersion );
		 ˵������������ʱ��ʹ�á�
	3�� ����ԴӪҵ�����롣
	    FIXCOMM_API void   WINAPI SetFixCommSource( const char * pSource );
	    ˵����ԴӪҵ������������Ӫҵ���ṩ��һ��Ӧ�������ļ�ȡ�ã���ʼֵΪ��"00000001"
	4�� ����Ŀ��Ӫҵ�����롣
		 FIXCOMM_API void   WINAPI SetFixCommTarget( const char * pTarget );
		 ˵����Ŀ��Ӫҵ��������ʱδʹ�ã�������
	5�� ����ί�з�ʽ��
		 FIXCOMM_API void   WINAPI SetFixCommWtfs( const char *pWtfs );
		 ˵������Ҫ�������·�ʽ��GT:��̨,CK:�ſ�,RJ:�ȼ�,DH:�绰,YC:Զ�̵ȡ�
	6�� �����û���
	    FIXCOMM_API void   WINAPI SetFixCommUser( const char *pUser );
	    ˵������Χ�ӿ��е��û����Բ��ǹ�̨����Ч���û�����Ҫ����ϵͳ������ͳ�ƣ���ʼֵΪ��"00000000"��
	7�� ���Ӷ����м����
		 FIXCOMM_API void * WINAPI FixConnect(const char *pDest,const char *pRemote );
		 ˵����pDestΪ�����м�������ַ����ʽΪ����ַ,�˿ں�/Э�飬�磺
		 		 192.168.0.1,9001/tcp    ��
		 		 00000001,00123456789A,8001/spx
		 		 pRemote��ʱδ�ã�����ա�
		 		 ����ֵΪδ�����͵�ָ�룬���Ժ�ĺ�������Ϊ��һ�����ʹ�ã������º����е�void *pFix��
		 		 �ɹ�ʱָ��ǿ�(NULL)��
	8�� ���Ӷ����м����
		 FIXCOMM_API void * WINAPI FixConnectEx(const char *pDest,const char *pRemote,int nTimeOut);
		 ˵����pDestΪ�����м�������ַ����ʽΪ����ַ,�˿ں�/Э�飬�磺
		 		 192.168.0.1,9001/tcp    ��
		 		 00000001,00123456789A,8001/spx
		 		 pRemote��ʱδ�ã�����ա�
			   nTimeOutΪ���ӳ�ʱʱ��(��λΪ��),Ҫ������һ������0����
		 		 ����ֵΪδ�����͵�ָ�룬���Ժ�ĺ�������Ϊ��һ�����ʹ�ã������º����е�void *pFix��
		 		 �ɹ�ʱָ��ǿ�(NULL)��
	9�� �Ͽ����м�������ӡ�
		 FIXCOMM_API void   WINAPI FixClose( void *pFix );
		 ˵����pFixΪ�ɹ�����FixConnect������ķ���ֵ��������ͬ��
		 		 ����FixClose��pFixָ�벻����ʹ�ã��������һ����FixClose��pFix��Ϊ��ֵ(NULL)��
	10����ʼ��FIX���ݰ���
		 FIXCOMM_API void   WINAPI FixCreate( void *pFix,int nFunCode );
		 ˵����nFunCodeΪ���ܺţ�����Ĺ��ܺ�˵���������ĵ���������
             FixCreate������������ݻ������������ȵ���FixCreate�������FixSet�Ⱥ����������塣
	11������FIX���ֵ��
		 FIXCOMM_API void   WINAPI FixSet( void *pFix,int nItem,const char *pItem );
	    FIXCOMM_API void   WINAPI FixSetInt( void *pFix,int nItem,int nValue );
	    FIXCOMM_API void   WINAPI FixSetDouble( void *pFix,int nItem,double lfValue );
		 ˵����nItemΪFIX��ı�ʶ������ҵ�������õ����������ĵ���������
	14��ȡFIX���ֵ��
		 FIXCOMM_API char * WINAPI FixGet( void *pFix,int nItem,char *pItem,int nMaxSize );
	    FIXCOMM_API int    WINAPI FixGetInt( void *pFix,int nItem );
	    FIXCOMM_API double WINAPI FixGetDouble( void *pFix,int nItem );
		 ˵����nItemΪFIX��ı�ʶ������ҵ������ķ������������ĵ���������
	17����������
		 FIXCOMM_API int    WINAPI FixWrite( void *pFix );
		 ˵���������úõ�FIX�����͵������м����
		       ����ֵ<0��ʾ����ʧ�ܡ�
	18���Ӷ����м����ȡ��¼��
		 FIXCOMM_API int    WINAPI FixRead( void *pFix );
		 ˵�������������м����ȡ��¼������ֵ<0ʱ��ʾ��ȡʧ�ܣ����������ѶϿ���
		                                     ==0ʱ��ʾ��ʱ�����ݿɶ���
		                                     >0��ʾ��ȡ��¼�ɹ���
		       ���ñ������󣬻������������ѱ����¡�
		       һ��ģ��ڵ���FixWrite��������ѭ������FixReadֱ������ֵ��Ϊ�㡣
	19���Ӷ����м����ȡ��¼��
	    FIXCOMM_API int    WINAPI FixReadEx( void *pFix,int nTimeout );
	    ˵�������������м����ȡ���������ļ�¼������ֵͬFixRead��
	          nTimeoutΪ��ȡ�������ʱʱ�䣬��λΪ���룬�����ָ��ʱ����û�ж������ݷ���ֵΪ0��
	          ������ȡ��¼�Ĺ��ܺź�FixCreate�Ĺ��ܺ���ͬ��ʱ�������ŷ��ء�
    20��ֱ���������ݻ�������
       FIXCOMM_API BOOL   WINAPI FixSetBuffer( void *pFix,const char *pData );
       ˵����������һ���FixGetBuffer�������ʹ�ã����������ݵ�ֱ�Ӳ�����
    21���������ݻ�������
       FIXCOMM_API BOOL   WINAPI FixGetBuffer( void *pFix,char *pData,int nMaxSize );
       ˵����FIX���ݻ���������󳤶�Ϊ512��
	22��ȡ���ܺš�
	    FIXCOMM_API int    WINAPI FixGetFunCode( void *pFix );
	    ˵��������FIX���ݰ��Ĺ��ܺ�
	23��ȡ��¼��š�
	    FIXCOMM_API int    WINAPI FixGetRecNo( void *pFix );
	    ˵�������Կ����ж������ؼ�¼�Ĺ������󣬷��ؼ�¼�в��м�¼�����
	          ���ڽ���һ����¼�Ĺ���������ɶ�У�飬���ؼ�¼��û�м�¼����򣬲��������FID_CODE�з��أ�
	      ���˵����FID_MESSAGE�з��أ����Ե���FixGetInt��FixGetȡ��(ע���ɶ�У�飬FID_CODE��FID_MESSAGE
	      �������ĵ�������)��


	24�� ����ԴӪҵ������(ֻ������ĳ�����ӵĲ���)��
	    FIXCOMM_API void   WINAPI SetFixCommSourceEx(void *pFix, const char * pSource );
	    ˵����ԴӪҵ������������Ӫҵ���ṩ��һ��Ӧ�������ļ�ȡ�ã���ʼֵΪ��"00000001"

	25�� ����Ŀ��Ӫҵ������(ֻ������ĳ�����ӵĲ���)��
		 FIXCOMM_API void   WINAPI SetFixCommTargetEx(void *pFix, const char * pTarget );
		 ˵����Ŀ��Ӫҵ��������ʱδʹ�ã�������

	26�� ����ί�з�ʽ(ֻ������ĳ�����ӵĲ���)��
		 FIXCOMM_API void   WINAPI SetFixCommWtfsEx(void *pFix, const char *pWtfs );
		 ˵������Ҫ�������·�ʽ��GT:��̨,CK:�ſ�,RJ:�ȼ�,DH:�绰,YC:Զ�̵ȡ�

	27�� �����û�(ֻ������ĳ�����ӵĲ���)��
	     FIXCOMM_API void   WINAPI SetFixCommUserEx(void *pFix, const char *pUser );
	     ˵������Χ�ӿ��е��û����Բ��ǹ�̨����Ч���û�����Ҫ����ϵͳ������ͳ�ƣ���ʼֵΪ��"00000000"��

	28�� ���ýڵ��ַ
	      FIXCOMM_API void    WINAPI SetFixCommNode( const char *pNode );
		  ˵������Χ�ӿڿ���ָ�����ӿ��ڲ��ڵ��ַ����ΪIP��ַ����������������ı�ʶֵ, ������Ϊ�����ڵ��ַ
	29�� ���ýڵ��ַ(ֻ������ĳ�����ӵĲ���)
	      FIXCOMM_API void    WINAPI SetFixCommNodeEx(void *pFix,  const char *pNode );
		  ˵������Χ�ӿڿ���ָ�������Ӿ���Ľڵ��ַ����ΪIP��ַ����������������ı�ʶֵ, ������Ϊ�����ڵ��ַ



����ʾ��

   #include "stdafx.h"
   #include "FixComm.h"
   #include "FIXDEF.H"                                         //FIXDEF.H �������ĵ����ṩ

	void *pFix;
	int nResult;
	char buffer[512];
	pFix = FixConnect( "192.168.0.123,7001/tcp","" );
	if ( pFix )
	{
		FixCreate( pFix,FUNC_XT_GETALLJYS );                     //FUNC_XT_GETALLJYS ��FIXDEF.H�ж��塣
		nResult = FixWrite( pFix );
		while ( 1 )
		{
			nResult = FixReadEx( pFix,1000 );
			FixGetBuffer( pFix,buffer,sizeof(buffer)-1 );
			if ( nResult <= 0 ) break;
			if ( FixGetRecNo( pFix ) < 0 ) break;
			FixGet( pFix,FID_JYS,buffer,0 );                      //FID_JYS ��FIXDEF.H�ж��塣
			FixGet( pFix,FID_JYSJC,buffer,0 );                    //FID_JYSJC ��FIXDEF.H�ж��塣
		}
		FixClose( pFix );
		pFix = NULL;
	}

	