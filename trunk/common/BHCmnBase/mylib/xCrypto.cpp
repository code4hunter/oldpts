//---------------------------------------------------------------------------
#pragma hdrstop

#include "xCrypto.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
/*szSource为要加密的文件名称,szDestination为加密过的文件名称,szPassword为加密口令*/

void CAPIEncryptFile(PCHAR szSource, PCHAR szDestination, PCHAR szPassword)
{

FILE *hSource = NULL;

FILE *hDestination = NULL;

INT eof = 0;

HCRYPTPROV hProv = 0;

HCRYPTKEY hKey = 0;

HCRYPTKEY hXchgKey = 0;

HCRYPTHASH hHash = 0;

PBYTE pbKeyBlob = NULL;

DWORD dwKeyBlobLen;

PBYTE pbBuffer = NULL;

DWORD dwBlockLen;

DWORD dwBufferLen;

DWORD dwCount;

hSource= fopen(szSource,"rb"));// 打开源文件

hDestination = fopen(szDestination,"wb") ;//.打开目标文件

// 连接缺省的CSP

CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0));

if(szPassword == NULL) {

//口令为空,使用随机产生的会话密钥加密

// 产生随机会话密钥。

CryptGenKey(hProv, ENCRYPT_ALGORITHM, CRYPT_EXPORTABLE, &hKey)

// 取得密钥交换对的公共密钥

CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hXchgKey);

// 计算隐码长度并分配缓冲区

CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, NULL, &dwKeyBlobLen);

pbKeyBlob=malloc(dwKeyBlobLen)) == NULL) ;

// 将会话密钥输出至隐码

CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, pbKeyBlob, &dwKeyBlobLen))

// 释放密钥交换对的句柄

CryptDestroyKey(hXchgKey);

hXchgKey = 0;

// 将隐码长度写入目标文件

fwrite(&dwKeyBlobLen, sizeof(DWORD), 1, hDestination);

//将隐码长度写入目标文件

fwrite(pbKeyBlob,1,dwKeyBlobLen, hDestination);

} else {

//口令不为空, 使用从口令派生出的密钥加密文件

CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash);// 建立散列表

CryptHashData(hHash, szPassword,

strlen(szPassword), 0); //散列口令

// 从散列表中派生密钥

CryptDeriveKey(hProv, ENCRYPT_ALGORITHM, hHash, 0, &hKey);

// 删除散列表

CryptDestroyHash(hHash);

hHash = 0;

}

//计算一次加密的数据字节数,必须为ENCRYPT_BLOCK_SIZE的整数倍dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;

//如果使用块编码,则需要额外空间

if(ENCRYPT_BLOCK_SIZE > 1) {

dwBufferLen=dwBlockLen + ENCRYPT_BLOCK_SIZE;

} else {

dwBufferLen = dwBlockLen;

}

//分配缓冲区

pbBuffer = malloc(dwBufferLen);

//加密源文件并写入目标文件

do {

// 从源文件中读出dwBlockLen个字节

dwCount = fread(pbBuffer, 1, dwBlockLen, hSource);

eof = feof(hSource);

//加密数据

CryptEncrypt(hKey, 0, eof, 0, pbBuffer, &dwCount, dwBufferLen);

// 将加密过的数据写入目标文件

fwrite(pbBuffer, 1, dwCount, hDestination);

} while(!feof(hSource));

printf("OK\n");

......//关闭文件、释放内存

}

//文件解密

void CAPIDecryptFile(PCHAR szSource, PCHAR szDestination, PCHAR szPassword)

{

......//变量声明、文件操作同文件加密程序

CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0);

if(szPassword == NULL) {

// 口令为空,使用存储在加密文件中的会话密钥解密

// 读隐码的长度并分配内存

fread(&dwKeyBlobLen,sizeof(DWORD),1,hSource);

pbKeyBlob=malloc(dwKeyBlobLen))== NULL);

// 从源文件中读隐码.

fread(pbKeyBlob, 1, dwKeyBlobLen, hSource);

// 将隐码输入CSP

CryptImportKey(hProv, pbKeyBlob, dwKeyBlobLen, 0, 0, &hKey);

} else {

// 口令不为空, 使用从口令派生出的密钥解密文件

CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash);

CryptHashData(hHash, szPassword, strlen(szPassword), 0);

CryptDeriveKey(hProv, ENCRYPT_ALGORITHM,hHash, 0, &hKey);

CryptDestroyHash(hHash);

hHash = 0;

}

dwBlockLen=1000-1000%ENCRYPT_BLOCK_SIZE;

if(ENCRYPT_BLOCK_SIZE > 1) {

dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE;

} else {

dwBufferLen = dwBlockLen;

}

pbBuffer = malloc(dwBufferLen);

//解密源文件并写入目标文件

do {

dwCount = fread(pbBuffer, 1, dwBlockLen,hSource);

eof = feof(hSource);

// 解密数据

CryptDecrypt(hKey, 0, eof, 0, pbBuffer, &dwCount);

// 将解密过的数据写入目标文件

fwrite(pbBuffer, 1, dwCount, hDestination);

} while(!feof(hSource));

printf("OK\n");

......//关闭文件、释放内存}

 