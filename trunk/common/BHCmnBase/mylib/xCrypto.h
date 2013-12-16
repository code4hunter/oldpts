//---------------------------------------------------------------------------

#ifndef xCryptoH
#define xCryptoH

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wincrypt.h>
//---------------------------------------------------------------------------
//确定使用RC2块编码或是RC4流式编码

#ifdef USE_BLOCK_CIPHER
#define ENCRYPT_ALGORITHM CALG_RC2
#define ENCRYPT_BLOCK_SIZE 8
#else
#define ENCRYPT_ALGORITHM CALG_RC4
#define ENCRYPT_BLOCK_SIZE 1
#endif

void CAPIEncryptFile(PCHAR szSource, PCHAR szDestination, PCHAR szPassword);
void CAPIDecryptFile(PCHAR szSource, PCHAR szDestination, PCHAR szPassword);


#endif
