//---------------------------------------------------------------------------
#pragma hdrstop
#include "xGost.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <malloc.h>

#pragma package(smart_init)
//---------------------------------------------------------------------------
typedef  int INT32;
typedef  char INT8;
typedef  unsigned char  ULONG8;
typedef  unsigned short ULONG16;
typedef  unsigned long  ULONG32;

#define SUCCESS 0
#define FAIL -1

/*函数申明*/
/*加密接口函数*/
INT32 gost_enc(ULONG32 *data , ULONG32 *key);
/*解密接口函数*/
INT32 gost_dec(ULONG32 *data, ULONG32 *key);
INT32 encry_data( ULONG32 *Ldata,ULONG32 *Rdata,ULONG32 *key);
INT32 dencry_data( ULONG32 *Ldata,ULONG32 *Rdata,ULONG32 *key);
INT32 f(ULONG32 x);/*s-盒替换、循环左移11位操作*/
/*左右值交换*/
INT32 gost_swap( ULONG32 *Ldata,ULONG32 *Rdata);

/*Gost的s-盒*/
ULONG8 wz_sp[8][16] =
{
	{ 0x4,0xa,0x9,0x2,0xd,0x8,0x0,0xe,0x6,0xb,0x1,0xc,0x7,0xf,0x5,0x3},
	{ 0xe,0xb,0x4,0xc,0x6,0xd,0xf,0xa,0x2,0x3,0x8,0x1,0x0,0x7,0x5,0x9},
	{ 0x5,0x8,0x1,0xd,0xa,0x3,0x4,0x2,0xe,0xf,0xc,0x7,0x6,0x0,0x9,0xb},
	{ 0x7,0xd,0xa,0x1,0x0,0x8,0x9,0xf,0xe,0x4,0x6,0xc,0xb,0x2,0x5,0x3},
	{ 0x6,0xc,0x7,0x1,0x5,0xf,0xd,0x8,0x4,0xa,0x9,0xe,0x0,0x3,0xb,0x2},
	{ 0x4,0xb,0xa,0x0,0x7,0x2,0x1,0xd,0x3,0x6,0x8,0x5,0x9,0xc,0xf,0xe},
	{ 0xd,0xb,0x4,0x1,0x3,0xf,0x5,0x9,0x0,0xa,0xe,0x7,0x6,0x8,0x2,0xc},
	{ 0x1,0xf,0xd,0x0,0x5,0x7,0xa,0x4,0x9,0x2,0x3,0xe,0x6,0xb,0x8,0xc}
};

/*加密密钥使用顺序表*/
ULONG32 wz_spkey[32] =
{
	0,1,2,3,4,5,6,7,
	0,1,2,3,4,5,6,7,
	0,1,2,3,4,5,6,7,
	7,6,5,4,3,2,1,0
};

/*s-盒替换、循环左移11位操作*/
INT32 f (ULONG32 x)
{
	x = wz_sp[7][(x>>28)&0xf]<<28 | wz_sp[6][(x>>24)&0xf]<<24
		| wz_sp[5][(x>>20)&0xf]<<20 | wz_sp[4][(x>>16)&0xf]<<16
		| wz_sp[3][(x>>12)&0xf]<<12 | wz_sp[2][(x>>8)&0xf]<<8
		| wz_sp[1][(x>>4)&0xf]<< 4  |  wz_sp[0][x&0xf];
	return x <<11 | x>>21;
}

/*左右值交换*/
INT32 gost_swap( ULONG32 *Ldata,ULONG32 *Rdata)
{
	ULONG32 tempbuf;
	tempbuf = *Rdata;
	*Rdata = *Ldata ;
	*Ldata = tempbuf;
	return SUCCESS;
}

/*32轮解密操作*/
INT32 dencry_data( ULONG32 *Ldata,ULONG32 *Rdata,ULONG32 *key)
{
	ULONG32 i = 0 ;
	//ULONG32 tempbuf =  0 ;
	for (i = 0 ; i < 32;i++)
	{
		*Rdata ^=f(*Ldata + key[wz_spkey[31-i]]);
		gost_swap(Ldata,Rdata); /*左右值交换*/
	}
	gost_swap(Ldata,Rdata);	/*左右值交换*/
	return SUCCESS;
}

/*解密接口函数*/
INT32 gost_dec(ULONG32 *data ,/*待解密数据首地址,内容需保证是64位长*/
  ULONG32 *key/*用户输入密钥首地址,内容需保证是256位长*/)
{
	ULONG32 *Ldata  ;
	ULONG32 *Rdata ;
	Ldata = data ;
	Rdata = &Ldata[1];/*分成左右两个部分,每部分32字节*/
	dencry_data( Ldata, Rdata,key ) ;
	/*明文可用data读出*/
	return SUCCESS;
}

INT32 gost_enc(ULONG32 *data , /*待加密数据首地址,内容需保证是64位长*/
 ULONG32 *key/*用户输入密钥首地址,内容需保证是256位长*/)
{
	ULONG32 *Ldata  ;
	ULONG32 *Rdata ;
	Ldata = data ;
	Rdata = &Ldata[1];/*分成左右两个部分,每部分32字节*/
	encry_data( Ldata, Rdata,key ) ;
	/*密文可用data读出*/
	return SUCCESS;
}

/*32轮加密操作*/
INT32 encry_data( ULONG32 *Ldata,ULONG32 *Rdata,ULONG32 *key)
{
	ULONG32 i = 0 ;
	//ULONG32 tempbuf  =  0;
	for (i = 0 ; i < 32;i++)
	{
		*Rdata ^=f(*Ldata + key[wz_spkey[i]]);
		gost_swap(Ldata,Rdata); /*左右值交换*/
	}
	gost_swap(Ldata,Rdata);	/*左右值交换*/
	return SUCCESS;
}
/*算法实现代码结束*/

//-----------------------------------------------------------------------------
#define WZ_COMMEND_NUM 4
#define WZUSEHELPNUM 7
#define READFILESIZE 1024 /*一次从文件中读取多少字节,可以根据内存的大小调节*/
INT32 file_enc(FILE *readfile, FILE *writefile,ULONG8 *key);/*加密文件*/
INT32 file_dec(FILE *readfile, FILE *writefile,ULONG8 *key);/*解密文件*/
INT32 hextofile(ULONG8 *buf ,FILE *writefile, ULONG32 length);/*以16进制写入文件*/
INT32 encodehex(ULONG8 *tobuf,ULONG8 *frombuf,ULONG32 len);/*16进制解码*/


void gost(bool Encode,char *SrcFile,char * DestFile,char *Password)
{
	INT8 *FILENAME1,*FILENAME2;
	FILE *fp, *fp2;
	ULONG8 key[33] = { 0 };	/*密钥容器*/
	FILENAME1 = SrcFile;
	FILENAME2 = DestFile;
	if ((fp= fopen(FILENAME1,"rb")) == NULL	|| (fp2 = fopen(FILENAME2,"wb"))==NULL)
	{
		return ;
	}
    memcpy( key, Password , strlen(Password) );/*取得密钥*/
	if(Encode)
	{
	  /*加密操作*/
		file_enc(fp,fp2,key);
  }
  else
  {
		/*解密*/
		file_dec(fp,fp2,key);
	}

	fclose(fp);
	fclose(fp2);
}

INT32 hextofile( ULONG8 *buf ,FILE *writefile, ULONG32 length)
{
	ULONG32 writelen = 0 ;
		/*以16进制形式写入文件*/
    while( writelen < length)
	{
		if(buf[writelen] == 0)
		{
			fprintf( writefile, "%x", 0 );
			fprintf( writefile, "%x", 0 );
		}
		else if (buf[writelen] < 0x10)
		{
			fprintf( writefile, "%x", 0 );
			fprintf( writefile, "%x", buf[writelen] );
		}
		else
		{
			fprintf( writefile, "%x", buf[writelen] );

		}
		writelen++;
	}
	return SUCCESS;
}

INT32 file_enc( FILE *readfile, FILE *writefile,ULONG8 *key)
{
	INT32 filelen = 0;
	ULONG32 totalfilelen = 0 ;/*统计实际的文件的长度*/
	INT32 i;
	ULONG8 readbuf[READFILESIZE] = { 0 };
	filelen = fread( readbuf, sizeof( INT8 ), READFILESIZE, readfile );
	while( filelen == READFILESIZE )
	{
		totalfilelen += READFILESIZE;
		for ( i = 0 ; i < READFILESIZE ; i += 8)
		{
			gost_enc( (ULONG32*)&readbuf[i] ,(ULONG32*) key);/*加密*/
		}
		hextofile( readbuf, writefile, READFILESIZE );/*以16进制形式写入文件*/
		memset(readbuf,0,READFILESIZE);
		filelen = fread( readbuf, sizeof( INT8 ), READFILESIZE, readfile );
	}
	/*这是从文件中读出的最后一批数据,长度可能会等于0,所以要先判断*/

	if ( filelen > 0 )
	{
		/*如果从文件中读出的长度不等于0,那么肯定有8个字节以上的空间
		文件长度存在最后8个字节中*/
		totalfilelen += filelen;
		memcpy( &readbuf[READFILESIZE-8], (ULONG8*)&totalfilelen,4);	
		for ( i = 0 ; i < READFILESIZE ; i += 8)
		{
			gost_enc( (ULONG32*)&readbuf[i] ,(ULONG32*) key);/*加密*/
		}		
		hextofile( readbuf, writefile,READFILESIZE );/*以16进制形式写入文件*/		
		memset(readbuf,0 ,READFILESIZE);
	}
	else /*filelen == 0*/
	{
		memcpy( &readbuf[0], (ULONG8*)&totalfilelen,4);			
		gost_enc( (ULONG32*)&readbuf[0] ,(ULONG32*) key);/*加密*/		
		hextofile( readbuf, writefile, 8);/*以16进制形式写入文件*/		
	}
	return SUCCESS;
}

INT32 file_dec( FILE *readfile, FILE *writefile,ULONG8 *key)
{
	INT32 filelen ,readlen,writelen;
	ULONG32 totalfilelen = 0 ;/*统计实际的文件的长度*/
	INT32 i,num;
	ULONG8 readbuf[READFILESIZE] = { 0 };
	ULONG8 sendbuf[READFILESIZE*2] = { 0 };	
	
	fseek(readfile,-16,SEEK_END);/*最后16个字节的表示文件长度的空间*/
  //fread( sendbuf, sizeof( INT8 ), 16, readfile );
	filelen = fread( sendbuf, sizeof( INT8 ), 16, readfile );
	encodehex( readbuf,sendbuf,8);	
	gost_dec( (ULONG32*)&readbuf[0] ,(ULONG32*) key);/*解密*/
	memcpy((ULONG8*)&totalfilelen, &readbuf[0],4);/*得到文件总长*/
	memset(readbuf,0 ,8);
	memset(sendbuf,0 ,16);

  if(totalfilelen>1024*1024)
    totalfilelen=0;
      
	num = totalfilelen/READFILESIZE;/*有几个READFILESIZE组*/
	totalfilelen %= READFILESIZE;

	fseek(readfile,0,SEEK_SET);/*跳到文件头*/	
	while(num--)
	{	
    //fread( sendbuf, sizeof( INT8 ), READFILESIZE*2, readfile );
		filelen = fread( sendbuf, sizeof( INT8 ), READFILESIZE*2, readfile );
		encodehex( readbuf,sendbuf,READFILESIZE);
		for ( i = 0 ; i < READFILESIZE ; i += 8)
		{
			gost_dec( (ULONG32*)&readbuf[i] ,(ULONG32*) key);/*解密*/
		}				
    //fwrite(readbuf, sizeof( INT8 ), READFILESIZE, writefile);
		writelen = fwrite(readbuf, sizeof( INT8 ), READFILESIZE, writefile);
		memset(readbuf,0 ,READFILESIZE);
		memset(sendbuf,0 ,READFILESIZE*2);			
	}
	if ( totalfilelen > 0 )/*最后一块有多余的元素*/
	{
    //fread( sendbuf, sizeof( INT8 ), READFILESIZE*2, readfile );
		filelen = fread( sendbuf, sizeof( INT8 ), READFILESIZE*2, readfile );
		encodehex( readbuf,sendbuf,READFILESIZE);
		for ( i = 0 ; i < READFILESIZE ; i += 8)
		{
			gost_dec( (ULONG32*)&readbuf[i] ,(ULONG32*) key);/*解密*/
		}		
    //fwrite(readbuf, sizeof( INT8 ), totalfilelen, writefile);
		writelen = fwrite(readbuf, sizeof( INT8 ), totalfilelen, writefile);
		memset(readbuf,0 ,READFILESIZE);
		memset(sendbuf,0 ,READFILESIZE*2);
	}
	return SUCCESS;
}

INT32 encodehex(ULONG8 *tobuf,ULONG8 *frombuf,ULONG32 len)
{
	ULONG8 *readfirst = frombuf ;
	ULONG8 *readend = &frombuf[1] ;
	INT8 *s;
	ULONG8 y[2] ;
	ULONG32 i;
	for ( i = 0 ; i < len ; i++)
	{
		y[0] = *readfirst ;
		y[1] = *readend ;
		readfirst += 2 ;
		readend += 2 ;
		tobuf[i] = (ULONG8)strtol((INT8*)y, &s, 16);
	}
	return SUCCESS;
}

/*
void GostBuf(bool Encode,char * SrcBuf,char *DestBuf,char * Password)
{
  if(Encode)
  {
    //加密
      gost_enc((ULONG32*)SrcBuf ,(ULONG32*)Password);
  }
  else
  {
    //解密
    gost_dec((ULONG32*)SrcBuf ,(ULONG32*)Password);
  }
}
*/
