一、说明
	1、本文档仅适用于顶点A.BOSS柜台系统中间件的外围接口。
	2、顶点A.BOSS系统与前端的数据接口使用FIX格式。
	3、顶点A.BOSS第三方中间件接口包含以下文件：
	   FIXCOMM.DLL,FIXCOMM.H,FIXCOMM.LIB,README.TXT
	4、FIXCOMM.DLL 为Win32 动态链接库。
	5、使用MS VC++编写顶点A.BOSS第三方中间件接口时可使用FIXCOMM.LIB。
	6、本文档不包含具体的业务接口，顶点公司会在其他的文档中提供。
	7、建议使用长连接。

二、函数列表
	顶点A.BOSS第三方接口提供以下基本函数：
	1、 FIXCOMM_API char * WINAPI counterchange( char *pData );
	2、 FIXCOMM_API void   WINAPI SetFixCommVersion( const char *pVersion );
	3、 FIXCOMM_API void   WINAPI SetFixCommSource( const char * pSource );
	4、 FIXCOMM_API void   WINAPI SetFixCommTarget( const char * pTarget );
	5、 FIXCOMM_API void   WINAPI SetFixCommWtfs( const char *pWtfs );
	6、 FIXCOMM_API void   WINAPI SetFixCommUser( const char *pUser );
	7、 FIXCOMM_API void * WINAPI FixConnect(const char *pDest,const char *pRemote );
	8、 FIXCOMM_API void * WINAPI FixConnectEx(const char *pDest,const char *pRemote,int nTimeOut);
	9、 FIXCOMM_API void   WINAPI FixClose( void *pFix );
	10、FIXCOMM_API void   WINAPI FixCreate( void *pFix,int nFunCode );
	11、FIXCOMM_API void   WINAPI FixSet( void *pFix,int nItem,const char *pItem );
	12、FIXCOMM_API void   WINAPI FixSetInt( void *pFix,int nItem,int nValue );
	13、FIXCOMM_API void   WINAPI FixSetDouble( void *pFix,int nItem,double lfValue );
	14、FIXCOMM_API char * WINAPI FixGet( void *pFix,int nItem,char *pItem,int nMaxSize );
	15、FIXCOMM_API int    WINAPI FixGetInt( void *pFix,int nItem );
	16、FIXCOMM_API double WINAPI FixGetDouble( void *pFix,int nItem );
	17、FIXCOMM_API int    WINAPI FixWrite( void *pFix );
	18、FIXCOMM_API int    WINAPI FixRead( void *pFix );
	19、FIXCOMM_API int    WINAPI FixReadEx( void *pFix,int nTimeout );
    20、FIXCOMM_API BOOL   WINAPI FixSetBuffer( void *pFix,const char *pData );
    21、FIXCOMM_API BOOL   WINAPI FixGetBuffer( void *pFix,char *pData,int nMaxSize );
	22、FIXCOMM_API int    WINAPI FixGetFunCode( void *pFix );
	23、FIXCOMM_API int    WINAPI FixGetRecNo( void *pFix );
	24、FIXCOMM_API void   WINAPI SetFixCommSourceEx(void *pFix, const char * pSource );
	25、FIXCOMM_API void   WINAPI SetFixCommTargetEx(void *pFix, cnst char * pTarget );
	26、FIXCOMM_API void   WINAPI SetFixCommWtfsEx(void *pFix  , const char *pWtfs );
	27、FIXCOMM_API void   WINAPI SetFixCommUserEx(void *pFix  , const char *pUser );
	28、FIXCOMM_API void    WINAPI SetFixCommNode( const char *pNode );
	29、FIXCOMM_API void    WINAPI SetFixCommNodeEx(void *pFix  ,  const char *pNode );



三、函数说明
	1、 简单加密函数。
		 FIXCOMM_API char * WINAPI counterchange( char *pData );
		 说明：用于特殊字段如用户密码的加密处理。
	2、 设置接口使用的版本号。
	    FIXCOMM_API void   WINAPI SetFixCommVersion( const char *pVersion );
		 说明：本函数暂时不使用。
	3、 设置源营业部编码。
	    FIXCOMM_API void   WINAPI SetFixCommSource( const char * pSource );
	    说明：源营业部编码由所在营业部提供，一般应从配置文件取得，初始值为："00000001"
	4、 设置目标营业部编码。
		 FIXCOMM_API void   WINAPI SetFixCommTarget( const char * pTarget );
		 说明：目标营业部编码暂时未使用，保留。
	5、 设置委托方式。
		 FIXCOMM_API void   WINAPI SetFixCommWtfs( const char *pWtfs );
		 说明：主要包括以下方式：GT:柜台,CK:磁卡,RJ:热键,DH:电话,YC:远程等。
	6、 设置用户。
	    FIXCOMM_API void   WINAPI SetFixCommUser( const char *pUser );
	    说明：外围接口中的用户可以不是柜台中有效的用户，主要用于系统的数据统计，初始值为："00000000"。
	7、 连接顶点中间件。
		 FIXCOMM_API void * WINAPI FixConnect(const char *pDest,const char *pRemote );
		 说明：pDest为顶点中间件服务地址，格式为：地址,端口号/协议，如：
		 		 192.168.0.1,9001/tcp    或：
		 		 00000001,00123456789A,8001/spx
		 		 pRemote暂时未用，可填空。
		 		 返回值为未定类型的指针，在以后的函数中作为第一个入参使用，如以下函数中的void *pFix。
		 		 成功时指针非空(NULL)。
	8、 连接顶点中间件。
		 FIXCOMM_API void * WINAPI FixConnectEx(const char *pDest,const char *pRemote,int nTimeOut);
		 说明：pDest为顶点中间件服务地址，格式为：地址,端口号/协议，如：
		 		 192.168.0.1,9001/tcp    或：
		 		 00000001,00123456789A,8001/spx
		 		 pRemote暂时未用，可填空。
			   nTimeOut为连接超时时间(单位为秒),要求填入一个大于0的数
		 		 返回值为未定类型的指针，在以后的函数中作为第一个入参使用，如以下函数中的void *pFix。
		 		 成功时指针非空(NULL)。
	9、 断开与中间件的连接。
		 FIXCOMM_API void   WINAPI FixClose( void *pFix );
		 说明：pFix为成功调用FixConnect函数后的返回值，以下相同。
		 		 调用FixClose后，pFix指针不可再使用，否则出错。一般在FixClose后将pFix置为空值(NULL)。
	10、初始化FIX数据包。
		 FIXCOMM_API void   WINAPI FixCreate( void *pFix,int nFunCode );
		 说明：nFunCode为功能号，具体的功能号说明在其他文档中描述。
             FixCreate函数会清空数据缓冲区，必需先调用FixCreate，后调用FixSet等函数才有意义。
	11、设置FIX域的值。
		 FIXCOMM_API void   WINAPI FixSet( void *pFix,int nItem,const char *pItem );
	    FIXCOMM_API void   WINAPI FixSetInt( void *pFix,int nItem,int nValue );
	    FIXCOMM_API void   WINAPI FixSetDouble( void *pFix,int nItem,double lfValue );
		 说明：nItem为FIX域的标识，具体业务需设置的域在其他文档中描述。
	14、取FIX域的值。
		 FIXCOMM_API char * WINAPI FixGet( void *pFix,int nItem,char *pItem,int nMaxSize );
	    FIXCOMM_API int    WINAPI FixGetInt( void *pFix,int nItem );
	    FIXCOMM_API double WINAPI FixGetDouble( void *pFix,int nItem );
		 说明：nItem为FIX域的标识，具体业务操作的返回域在其他文档中描述。
	17、发送请求：
		 FIXCOMM_API int    WINAPI FixWrite( void *pFix );
		 说明：将设置好的FIX包发送到顶点中间件。
		       返回值<0表示发送失败。
	18、从顶点中间件读取记录。
		 FIXCOMM_API int    WINAPI FixRead( void *pFix );
		 说明：本函数从中间件读取记录，返回值<0时表示读取失败，可能连接已断开。
		                                     ==0时表示暂时无数据可读。
		                                     >0表示读取记录成功。
		       调用本函数后，缓冲区的内容已被更新。
		       一般的，在调用FixWrite函数后需循环调用FixRead直到返回值不为零。
	19、从顶点中间件读取记录。
	    FIXCOMM_API int    WINAPI FixReadEx( void *pFix,int nTimeout );
	    说明：本函数从中间件读取满足条件的记录，返回值同FixRead。
	          nTimeout为读取数据最大超时时间，单位为毫秒，如果在指定时间内没有读到数据返回值为0。
	          仅当读取记录的功能号和FixCreate的功能号相同或超时本函数才返回。
    20、直接设置数据缓冲区。
       FIXCOMM_API BOOL   WINAPI FixSetBuffer( void *pFix,const char *pData );
       说明：本函数一般和FixGetBuffer函数配合使用，可用于数据的直接操作。
    21、复制数据缓冲区。
       FIXCOMM_API BOOL   WINAPI FixGetBuffer( void *pFix,char *pData,int nMaxSize );
       说明：FIX数据缓冲区的最大长度为512。
	22、取功能号。
	    FIXCOMM_API int    WINAPI FixGetFunCode( void *pFix );
	    说明：返回FIX数据包的功能号
	23、取记录序号。
	    FIXCOMM_API int    WINAPI FixGetRecNo( void *pFix );
	    说明：仅对可能有多条返回记录的功能请求，返回记录中才有记录序号域。
	          对于仅有一条记录的功能请求，如股东校验，返回记录中没有记录序号域，操作结果在FID_CODE中返回，
	      结果说明在FID_MESSAGE中返回，可以调用FixGetInt和FixGet取得(注：股东校验，FID_CODE，FID_MESSAGE
	      在其他文档中描述)。


	24、 设置源营业部编码(只是设置某个连接的参数)。
	    FIXCOMM_API void   WINAPI SetFixCommSourceEx(void *pFix, const char * pSource );
	    说明：源营业部编码由所在营业部提供，一般应从配置文件取得，初始值为："00000001"

	25、 设置目标营业部编码(只是设置某个连接的参数)。
		 FIXCOMM_API void   WINAPI SetFixCommTargetEx(void *pFix, const char * pTarget );
		 说明：目标营业部编码暂时未使用，保留。

	26、 设置委托方式(只是设置某个连接的参数)。
		 FIXCOMM_API void   WINAPI SetFixCommWtfsEx(void *pFix, const char *pWtfs );
		 说明：主要包括以下方式：GT:柜台,CK:磁卡,RJ:热键,DH:电话,YC:远程等。

	27、 设置用户(只是设置某个连接的参数)。
	     FIXCOMM_API void   WINAPI SetFixCommUserEx(void *pFix, const char *pUser );
	     说明：外围接口中的用户可以不是柜台中有效的用户，主要用于系统的数据统计，初始值为："00000000"。

	28、 设置节点地址
	      FIXCOMM_API void    WINAPI SetFixCommNode( const char *pNode );
		  说明：外围接口可以指定本接口内部节点地址参数为IP地址或其它有特殊意义的标识值, 不设则为网卡节点地址
	29、 设置节点地址(只是设置某个连接的参数)
	      FIXCOMM_API void    WINAPI SetFixCommNodeEx(void *pFix,  const char *pNode );
		  说明：外围接口可以指定本连接句柄的节点地址参数为IP地址或其它有特殊意义的标识值, 不设则为网卡节点地址



三、示例

   #include "stdafx.h"
   #include "FixComm.h"
   #include "FIXDEF.H"                                         //FIXDEF.H 在其他文档中提供

	void *pFix;
	int nResult;
	char buffer[512];
	pFix = FixConnect( "192.168.0.123,7001/tcp","" );
	if ( pFix )
	{
		FixCreate( pFix,FUNC_XT_GETALLJYS );                     //FUNC_XT_GETALLJYS 在FIXDEF.H中定义。
		nResult = FixWrite( pFix );
		while ( 1 )
		{
			nResult = FixReadEx( pFix,1000 );
			FixGetBuffer( pFix,buffer,sizeof(buffer)-1 );
			if ( nResult <= 0 ) break;
			if ( FixGetRecNo( pFix ) < 0 ) break;
			FixGet( pFix,FID_JYS,buffer,0 );                      //FID_JYS 在FIXDEF.H中定义。
			FixGet( pFix,FID_JYSJC,buffer,0 );                    //FID_JYSJC 在FIXDEF.H中定义。
		}
		FixClose( pFix );
		pFix = NULL;
	}

	