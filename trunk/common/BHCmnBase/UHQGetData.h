#ifndef UHQGetDataH
#define UHQGetDataH
#include "UDynStr.h"

#define HQ_FILE_PATH_LEN   200
#define HQ_FILE_NAME_LEN   300

typedef void (WINAPI  *PCALLBACK)(char *Msg, int Count); 

class THQGetData
{
private:
  PCALLBACK FCallBack;
  char FFilePath[HQ_FILE_PATH_LEN];

  int GetSecuNo(char *Code, char *Buf);
  bool AddFreshData(char *Buf, TPriceListDyn *DataBuf, const int LastCount, const int iCount, const int SecuNo, const int Count);
  void ReorderData(TPriceListDyn *DataBuf, int iCurCount, int iCount);

public:
  THQGetData(char *FilePath, PCALLBACK Func);
  ~THQGetData(void);


  //if the function fails, return value < 0,
  //otherwise, return value is the number of records actually obtained;
  int  GetData(TPriceListDyn *DataBuf, char *Code, int Count, bool Mode=false);///Mode---false--not include the current day;
  static bool OutputDebugFile(char* FileName, TPriceListDyn *Data, int Count);

  //date process functions;
  static int GetDate(SYSTEMTIME &Time);//return vlue as: yyyymmdd
  static int GetDate(SYSTEMTIME &Time, int Increment);//Increment-- days difference from the current day;
  static short DateCmp(const SYSTEMTIME &SrcT, const SYSTEMTIME &DstT);//return: -1, 0, 1;
  static bool IsLeapYear(const SYSTEMTIME &Time);
  static WORD DaysOfAMonth(const SYSTEMTIME &Time);//return: 31, 30, 29, 28;
};

#endif
 