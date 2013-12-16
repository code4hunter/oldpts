#include <ZLib.hpp>
//---------------------------------------------------------------------------
#include "UTrdCot_Rm.h"
//---------------------------------------------------------------------------
__fastcall TTrdCot_Rm::TTrdCot_Rm() : TTrdCot()
{
  FTcpClt = NULL;
  FCS=new TCriticalSection();
}
//---------------------------------------------------------------------------
__fastcall TTrdCot_Rm::~TTrdCot_Rm()
{
	try
	{
	  if( FTcpClt )
		delete FTcpClt;

	  delete FCS;
	}
	catch(...)
	{

    }
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot_Rm::Request(TRequest Request,TAnswer **Answer,int &AnsCount)
{
	TAnswer answer;
	int     retVal     = 0;
	Request.Head.Version = 2010;

	try
	{
		TMemoryStream* dest = new TMemoryStream();
		int orgsize = sizeof(Request) ;
		dest->Write(&orgsize,sizeof(int));
		TCompressionStream * cs = new TCompressionStream(Zlib::clDefault,dest);
		TMemoryStream *source = new TMemoryStream();
		TDecompressionStream *ds = new TDecompressionStream(source);

		FCS->Enter();
		try
		{
			memset(&answer,0,sizeof(TAnswer));
			if( Request.Head.FuncType == ftInit)
			{
				this->Connect();
				if( FTcpClt->Connected() == false )
				  return ERR_TRDSVR_SEND_FAILED;
				FTcpClt->Socket->UseNagle = false;
			}
			cs->Write(&Request,sizeof(Request));
			delete cs;
			cs = NULL;

			if( FTcpClt == NULL ) return -1000;
			// 发送请求
			try
			{
				FTcpClt->IOHandler->LargeStream = false;
				FTcpClt->IOHandler->Write(dest,0x000000000,true);
			}
			catch(...)
			{
				retVal = ERR_TRDSVR_SEND_FAILED;
				FTcpClt->Disconnect();
				return retVal;
			}
			delete dest;
			dest = NULL;


			// 接收响应

			try
			{
				int size = FTcpClt->IOHandler->ReadInteger(false);
				if( size >0 )
				{
					orgsize = FTcpClt->IOHandler->ReadInteger(false);
					FTcpClt->IOHandler->ReadStream(source,size-sizeof(int),false);
					if( sizeof(TAnswer) != ds->Read(&answer,sizeof(TAnswer)) )
					{
						throw "";
					}
				}
				else
				{
					throw "";
				}
			}
			catch(...)
			{
				retVal = ERR_TRDSVR_RECV_FAILED;
				FTcpClt->Disconnect();
				return retVal;
			}

			retVal   = answer.Head.RetVal;

			if(retVal==0)
			{
				AnsCount = answer.Head.AnsCount;

				if(AnsCount>0)
				{
					*Answer  = new TAnswer[AnsCount];
					try
					{
						memcpy(&(*Answer)[0],&answer,sizeof(TAnswer));
						int len = sizeof(TAnswer)*(AnsCount-1);
						if( len!= ds->Read(&(*Answer)[1],len))
						{
							throw "";
						}
					}
					catch(...)
					{
						delete []  (*Answer);
						retVal= ERR_TRDSVR_RECV_FAILED;
						FTcpClt->Disconnect();
						return  retVal;
					}
				}
			}

			delete source;
			source = NULL;
			delete ds;
			ds = NULL;
		}
		__finally
		{
			FCS->Leave();
			if( dest ) delete dest;
			if( source) delete source;
			if( ds ) delete ds;
			if (cs) delete cs;
		}
	}
    catch(...)
    {
      retVal= ERR_REMOTE_OTHER_FAILED;
	}
	return retVal;
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot_Rm::Connect()
{
	try
	{
		if( FTcpClt )
			delete FTcpClt;

		FTcpClt = new TIdTCPClient(NULL);
		FTcpClt->Host = FSvrIp;
		FTcpClt->Port = FPort;
	}
	catch(...)
	{
	}

  	int ntry = 1; // 重试

retry:

    try
    {
    	FTcpClt->Connect();
    }
	catch(...)
    {
    	::Sleep(200);

		if( ntry-- > 0)
			goto retry;
		else
			return -1;
    }

    return 0;
}
//---------------------------------------------------------------------------
