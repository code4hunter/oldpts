// TestKdmm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"

int main(int argc, char* argv[])
{
	
	HMODULE h_kdgtmm;
	h_kdgtmm = LoadLibrary("KdGTmm.dll");

	typedef (*pfunc_KDGT_CRC)(unsigned char* lpinbuf, int nlen, unsigned char *lpoutcrccode);
	typedef (*pfunc_KDGT_Encrypt)(unsigned char *lpszkey, unsigned char* lpinbuf, int nlen, unsigned char *lpoutbuf);
	typedef (*pfunc_KDGT_Decrypt)(unsigned char *lpszkey, unsigned char* lpinbuf, int nlen, unsigned char *lpoutbuf);


	pfunc_KDGT_CRC KDGT_CRC;
	pfunc_KDGT_Encrypt KDGT_Encrypt;
	pfunc_KDGT_Decrypt KDGT_Decrypt;

	KDGT_CRC = NULL;
	KDGT_CRC = (pfunc_KDGT_CRC)GetProcAddress(h_kdgtmm, "KDGT_CRC");
	if (KDGT_CRC == NULL)
	{
		printf("Error Load KdGTmm.dll 1");
		return 0;
	}

	KDGT_Encrypt = NULL;
	KDGT_Encrypt = (pfunc_KDGT_Encrypt)GetProcAddress(h_kdgtmm, "KDGT_Encrypt");
	if (KDGT_Encrypt == NULL)
	{
		printf("Error Load KdGTmm.dll 2");
		return 0;
	}

	KDGT_Decrypt = NULL;
	KDGT_Decrypt = (pfunc_KDGT_Decrypt)GetProcAddress(h_kdgtmm, "KDGT_Decrypt");
	if (KDGT_Decrypt == NULL)
	{
		printf("Error Load KdGTmm.dll 3");
		return 0;
	}

	printf("Success Load KdGTmm.dll...\n");

	char szincrcbuf[200],szoutcrc[20];

	strcpy(szincrcbuf,"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	KDGT_CRC((unsigned char *)szincrcbuf,strlen(szincrcbuf),(unsigned char *)szoutcrc);
	printf(" KDGT_CRC TEST \n");
	printf("INPUTBUF=[%s] OUTCRC=[%s]\n",szincrcbuf,szoutcrc);

	char szinenbuf[100],szoutbuf[200];

	strcpy(szinenbuf,"EDCBA");
	KDGT_Encrypt((unsigned char *)"SZKINGDOM",(unsigned char *)szinenbuf,strlen(szinenbuf),(unsigned char *)szoutbuf);
	printf(" KDGT_Encrypt TEST \n");
	printf("INPUTBUF=[%s] ENCRYPT=[%s]\n",szinenbuf,szoutbuf);

	KDGT_Decrypt((unsigned char *)"SZKINGDOM",(unsigned char *)szoutbuf,strlen(szoutbuf),(unsigned char *)szinenbuf);
	printf(" KDGT_Decrypt TEST \n");
	printf("INPUTBUF=[%s] DECRYPT=[%s]\n",szoutbuf,szinenbuf);


	FreeLibrary(h_kdgtmm);
	return 0;
}

