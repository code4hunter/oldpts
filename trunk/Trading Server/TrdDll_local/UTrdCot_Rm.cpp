#include <ZLib.hpp>
// ---------------------------------------------------------------------------
#include "UTrdCot_Rm.h"

// ---------------------------------------------------------------------------
__fastcall TTrdCot_Rm::TTrdCot_Rm() : TTrdCot() {
	_trditf = NULL;
	FCS = new TCriticalSection();
}

// ---------------------------------------------------------------------------
__fastcall TTrdCot_Rm::~TTrdCot_Rm() {
	if( _trditf!=NULL )
	{
		_trditf->CloseLink();
		_pw.free_itf(_trditf);
    }
}

// ---------------------------------------------------------------------------
int __fastcall TTrdCot_Rm::Request(TRequest Request, TAnswer **Answer,
	int &AnsCount) {
	int retVal = 0;
	Request.Head.Version = 2010;

	try {
		FCS->Enter();
		try {
			if( _trditf == NULL )
			{
				return -100;
			}
			else
			{
                return _trditf->Request(Request,Answer,AnsCount);
            }
		}
		__finally {
			FCS->Leave();
		}
	}
	catch (...) {
		retVal = ERR_REMOTE_OTHER_FAILED;
	}
	return retVal;
}
// ---------------------------------------------------------------------------
