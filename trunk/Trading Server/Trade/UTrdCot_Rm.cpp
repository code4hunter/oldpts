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
	TBytes buf;
	Request.Head.Version = 2008;

  FCS->Enter();
	try
	{
  	try
    {
        memset(&answer,0,sizeof(TAnswer));
        if( Request.Head.FuncType == ftInit)
        //if(!FTcpClt->Connected() || Request.Head.FuncType == ftInit)
        {
            this->Connect();
            if( FTcpClt->Connected() == false )
              return ERR_TRDSVR_SEND_FAILED;
        }

		if( FTcpClt == NULL ) return -1000;
        // 发送请求
        try
        {
            FTcpClt->IOHandler->Write(RawToBytes(&Request,sizeof(TRequest)));
        }
        catch(...)
        {
            retVal = ERR_TRDSVR_SEND_FAILED;
            FTcpClt->Disconnect();
            return retVal;
        }

        // 接收响应
        try
        {
            FTcpClt->IOHandler->ReadBytes(buf,sizeof(TAnswer),false);
            BytesToRaw(buf,&answer, sizeof(TAnswer));
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
                    FTcpClt->IOHandler->ReadBytes(buf,sizeof(TAnswer)*(AnsCount-1),false);
                    BytesToRaw(buf,&(*Answer)[1],sizeof(TAnswer)*(AnsCount-1));
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
    }
    catch(...)
    {
      retVal= ERR_REMOTE_OTHER_FAILED;
    }
	}
	__finally
	{
		FCS->Leave();
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
