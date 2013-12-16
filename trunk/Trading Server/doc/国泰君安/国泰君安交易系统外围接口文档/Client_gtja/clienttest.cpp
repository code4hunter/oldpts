// clientTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kcbpcli.h"

int main(int _argc, char* _argv[])
{
	int  i, j, z=0;
	char UserName[64];
	char Password[64];	
	char tmpbuf[1024];
	int  nReturnCode;
	int  nCol;
	int  iErrCode;
	char szErrMsg[256];
	KCBPCLIHANDLE hHandle;
	
	strcpy(UserName, "KCXP00");
	strcpy(Password, "888888");
	
	tagKCBPConnectOption stKCBPConnection;
	memset(&stKCBPConnection, 0 , sizeof(stKCBPConnection));
	
	strcpy(stKCBPConnection.szServerName, "ctskcxp");
	stKCBPConnection.nProtocal = 0;
	strcpy(stKCBPConnection.szAddress, "10.100.218.150");
	stKCBPConnection.nPort = 21000;
	strcpy(stKCBPConnection.szSendQName, "req1");
	strcpy(stKCBPConnection.szReceiveQName, "ans1");
	
	/*新建KCBP实例*/
	if( KCBPCLI_Init( &hHandle ) != 0 )
	{
		printf( "KCBPCLI_Init error" );
		return -1;
	}

	/*连接KCBP服务器*/
	if( KCBPCLI_SetConnectOption( hHandle, stKCBPConnection ) )
	{
		printf( "KCBPCLI_SetConnectOption error" );
		KCBPCLI_Exit( hHandle );
		return -1;
	}

	if( KCBPCLI_SetCliTimeOut( hHandle, 20 ) )
	{
		printf( "KCBPCLI_SetCliTimeOut error" );
		KCBPCLI_Exit( hHandle );
		return -1;
	}

	if( KCBPCLI_SetSystemParam(hHandle, KCBP_PARAM_RESERVED, "3115" ) )   //必须设置营业部代码
	{
		printf( "KCBPCLI_SetSystemParam error" );
		KCBPCLI_Exit( hHandle );
		return -1;
	}

	nReturnCode = KCBPCLI_SQLConnect( hHandle, stKCBPConnection.szServerName, UserName, Password );
	if(nReturnCode)
	{
		printf("\nSqlconnect return code %d", nReturnCode);
		return(0);
	}

	/*初始化传入参数缓冲区*/
	nReturnCode = KCBPCLI_BeginWrite(hHandle);
	if( nReturnCode !=0 ) 
	{
		printf("KCBPCLI_BeginWrite ErrCode=%d ErrMsg=%s\n", iErrCode, szErrMsg);
		break;
	}
	
	KCBPCLI_SetValue(hHandle, "colName01", "colVal01");
	KCBPCLI_SetValue(hHandle, "colName02", "colVal02");
	KCBPCLI_SetValue(hHandle, "colName03", "colVal03");
	
	/*客户端向服务器提交请求*/
	nReturnCode  = KCBPCLI_SQLExecute(hHandle, "10000001");
	if( nReturnCode !=0 ) 
	{
		printf("SqlExecute Program ErrCode=%d ", nReturnCode );
		continue;
	}
		
	KCBPCLI_GetErrorCode(hHandle, &iErrCode);
	if( iErrCode != 0 )
	{
		KCBPCLI_GetErrorMsg( hHandle, szErrMsg );
		printf( "ErrCode:%d, ErrMsg:%s", iErrCode, szErrMsg );
		KCBPCLI_Exit( hHandle );
		return -1;
	}

	if( KCBPCLI_RsOpen(hHandle) != 0 )
	{
		printf("KCBPCLI_RsOpen error");
		KCBPCLI_Exit( hHandle );
		return -1;
	}

    KCBPCLI_SQLMoreResults(hHandle);
    
	KCBPCLI_SQLFetch(hHandle);

	if( KCBPCLI_RsGetColByName( hHandle, "CODE", tmpbuf ) )
	{
		printf( "Get CODE Fail" );
		KCBPCLI_Exit( hHandle );
		return -1;
	}
	
	if( atoi(tmpbuf) != 0 )
	{
		printf( "error code :%s ", tmpbuf );
		KCBPCLI_RsGetColByName( hHandle, "LEVEL", tmpbuf );
		printf( "error level :%s ", tmpbuf );
		KCBPCLI_RsGetColByName( hHandle, "MSG", tmpbuf );
		printf( "error msg :%s\n", tmpbuf );
		KCBPCLI_Exit( hHandle );
		return -1;
	}
	
	if( KCBPCLI_SQLMoreResults(hHandle) == 0 )
	{
	
		KCBPCLI_RsGetColNum(hHandle, &nCol);
		while( !KCBPCLI_RsFetchRow(hHandle) )
		{
			for( int i = 1; i <= nCol; i++ )
			{
				KCBPCLI_RsGetColName( hHandle, i, tmpbuf, sizeof(tmpbuf) );
				printf( "%s", tmpbuf );
				KCBPCLI_RsGetColByName( hHandle, tmpbuf, tmpbuf );
				printf( " = %s\n", tmpbuf );
			}
			printf( "\n" );
		}
	}
	
	KCBPCLI_SQLCloseCursor();

	/*断开KCBP连接*/
	KCBPCLI_SQLDisconnect();
	KCBPCLI_Exit( hHandle );
	
	return 0;
}

