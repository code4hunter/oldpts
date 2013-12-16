//---------------------------------------------------------------------------
#pragma hdrstop

#include "xCrypto.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
/*szSourceΪҪ���ܵ��ļ�����,szDestinationΪ���ܹ����ļ�����,szPasswordΪ���ܿ���*/

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

hSource= fopen(szSource,"rb"));// ��Դ�ļ�

hDestination = fopen(szDestination,"wb") ;//.��Ŀ���ļ�

// ����ȱʡ��CSP

CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0));

if(szPassword == NULL) {

//����Ϊ��,ʹ����������ĻỰ��Կ����

// ��������Ự��Կ��

CryptGenKey(hProv, ENCRYPT_ALGORITHM, CRYPT_EXPORTABLE, &hKey)

// ȡ����Կ�����ԵĹ�����Կ

CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hXchgKey);

// �������볤�Ȳ����仺����

CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, NULL, &dwKeyBlobLen);

pbKeyBlob=malloc(dwKeyBlobLen)) == NULL) ;

// ���Ự��Կ���������

CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, pbKeyBlob, &dwKeyBlobLen))

// �ͷ���Կ�����Եľ��

CryptDestroyKey(hXchgKey);

hXchgKey = 0;

// �����볤��д��Ŀ���ļ�

fwrite(&dwKeyBlobLen, sizeof(DWORD), 1, hDestination);

//�����볤��д��Ŀ���ļ�

fwrite(pbKeyBlob,1,dwKeyBlobLen, hDestination);

} else {

//���Ϊ��, ʹ�ôӿ�������������Կ�����ļ�

CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash);// ����ɢ�б�

CryptHashData(hHash, szPassword,

strlen(szPassword), 0); //ɢ�п���

// ��ɢ�б���������Կ

CryptDeriveKey(hProv, ENCRYPT_ALGORITHM, hHash, 0, &hKey);

// ɾ��ɢ�б�

CryptDestroyHash(hHash);

hHash = 0;

}

//����һ�μ��ܵ������ֽ���,����ΪENCRYPT_BLOCK_SIZE��������dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;

//���ʹ�ÿ����,����Ҫ����ռ�

if(ENCRYPT_BLOCK_SIZE > 1) {

dwBufferLen=dwBlockLen + ENCRYPT_BLOCK_SIZE;

} else {

dwBufferLen = dwBlockLen;

}

//���仺����

pbBuffer = malloc(dwBufferLen);

//����Դ�ļ���д��Ŀ���ļ�

do {

// ��Դ�ļ��ж���dwBlockLen���ֽ�

dwCount = fread(pbBuffer, 1, dwBlockLen, hSource);

eof = feof(hSource);

//��������

CryptEncrypt(hKey, 0, eof, 0, pbBuffer, &dwCount, dwBufferLen);

// �����ܹ�������д��Ŀ���ļ�

fwrite(pbBuffer, 1, dwCount, hDestination);

} while(!feof(hSource));

printf("OK\n");

......//�ر��ļ����ͷ��ڴ�

}

//�ļ�����

void CAPIDecryptFile(PCHAR szSource, PCHAR szDestination, PCHAR szPassword)

{

......//�����������ļ�����ͬ�ļ����ܳ���

CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0);

if(szPassword == NULL) {

// ����Ϊ��,ʹ�ô洢�ڼ����ļ��еĻỰ��Կ����

// ������ĳ��Ȳ������ڴ�

fread(&dwKeyBlobLen,sizeof(DWORD),1,hSource);

pbKeyBlob=malloc(dwKeyBlobLen))== NULL);

// ��Դ�ļ��ж�����.

fread(pbKeyBlob, 1, dwKeyBlobLen, hSource);

// ����������CSP

CryptImportKey(hProv, pbKeyBlob, dwKeyBlobLen, 0, 0, &hKey);

} else {

// ���Ϊ��, ʹ�ôӿ�������������Կ�����ļ�

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

//����Դ�ļ���д��Ŀ���ļ�

do {

dwCount = fread(pbBuffer, 1, dwBlockLen,hSource);

eof = feof(hSource);

// ��������

CryptDecrypt(hKey, 0, eof, 0, pbBuffer, &dwCount);

// �����ܹ�������д��Ŀ���ļ�

fwrite(pbBuffer, 1, dwCount, hDestination);

} while(!feof(hSource));

printf("OK\n");

......//�ر��ļ����ͷ��ڴ�}

 