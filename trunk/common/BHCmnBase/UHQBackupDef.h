#ifndef UHQBackupDefH
#define UHQBackupDefH

struct THQBackFileHead
{
  int date;//yyyymmdd
  int start_time;//hhmmss
  int end_time;//hhmmss
  char stock_type;//'H'---shanghai,'S'---shenzhen,'K'---hongkong;
  char reserved[20];//no use now;
  int stock_num;//
  int head_len;// = sizeof(THQBackFileHead)
};

struct THQBackPackHead
{
  unsigned int length;
  unsigned long send_time;
};

#endif


 