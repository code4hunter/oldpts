#ifndef UTrdStruct1.0H
#define UTrdStruct1.0H

namespace PTRDDLL1
{
////////////�ʺ����////////////////////////////////////////////////////////////
enum TAccountSort
{
  asSH = '0',          //�Ϻ��������Ĺɶ�����
  asSZ = '1',          //���ڽ������Ĺɶ�����
  asJJS = '2',         //�Ϻ����ڽ������ͻ�����
  asCA = 'Z'           //�ʽ��ʺ�
};

////////////������////////////////////////////////////////////////////////////
enum TBourse
{
  bsSH = '0',  //�Ϻ�������
  bsSZ = '1',   //���ڽ�����
  bsJJS = '2'  //�Ϻ����ڽ�����
};

//������� Type
enum bs_type
{
  btBuy = 'B', //��
  btSell= 'S', //��
  btNo  = 'N'  //����
};

//ί��״̬
enum wt_state
{
  //'0'��δ��  '1'���ѱ�   '2'������  '3'������  '4'���ѳ�  '5'--�ѳ�  '6'--�ѷ�
  wswb = '0',
  wsyb = '1',
  wsdc = '2',
  wsbw = '3',
  wsyc = '4',
  wscj = '5',
  wsyf = '6',
  wsbc = '7',  //����
  wsno = 'N'
};
// ʱ��    HHMMSS
// ����    YYYYMMDD
// ֤ȯ�����ʽ �Ͻ����Ĺ�Ʊ ǰ���'H',����ļ�'S' ,�����ڻ�'F'

////////////������Ϣ���̿����ݣ�////////////////////////////////////////////////
#pragma pack(1)
typedef struct
{
  double ZXJ;         //���¼�
  double Price1;      //���1
  double Price2;      //���2
  double Price3;      //���3

  int   CJSL;        //�ɽ�����
  int   Volum1;      //����1
  int   Volum2;      //����2
  int   Volum3;      //����4
} TDealInfo;

///////////ί����Ϣ////////////////////////////////
typedef struct
{
   char     ContractID[8];         //��ͬ��� 
   char     SecuID[8];             //֤ȯ���� 
   char     SecuDesc[9];           //֤ȯ����
   char     Bourse;                //������
   char     NoUse[6];
   char     Time[9];               //ί��ʱ��
   char     Date[9];               //ί������
   char     Type;                  //bs_type
   char     State;                 //wt_state
   long     CsnVol;                //ί������
   long     TrdVol;                //�ɽ�����
   long     CancelVol;             //��������
   double   CsnPrice;              //ί�м۸�
   double   TrdPrice;              //�ɽ��۸�
} TConsignInfo;

//////////////�ɽ���Ϣ//////////////////////////////////////////
typedef struct  {
   char     SecuID[8];             //֤ȯ���� 
   char     SecuDesc[9];           //֤ȯ����
   char     Time[9];               //�ɽ�ʱ��
   char     Date[9];               //ί������
   char     Type;                  //������� B,S
   long     Vol;                   //�ɽ�����
   double   Price;                 //�ɽ��۸�
} TTradeInfo;

/////////////�ʽ���ˮ///////////////////////////////////////////
typedef struct  {
   char     Date[9];               //ί������
   char     SecuID[8];             //֤ȯ����
   char     SecuDesc[9];           //֤ȯ����
   char     Type[13];              //�������˵��
   char     NoUse[5];
   long     Vol;                   //�ɽ�����
   double   Price;                 //�ɽ��۸�
   double   TrdMny;                //�ɽ����
   double   Balance;               //�ʽ����
}TFundInfo;

/////////////�ɷ���Ϣ/////////////////////////////////////////////////////////
typedef struct {
  char   SecuID[8];       //֤ȯ����            
  char   SecuDesc[12];    //֤ȯ�ɶ�������߽������˺�
  int    Balance;         //���                F��ֲ�
  int    Available;       //������              F���ֲ�
 
  int    BuyFreeze;       //���붳��
  int    SellFreeze;      //��������
  int    AbnorFreeze;     //�쳣���� 
  
  double Cost;            //�ο��ɱ�            
  double CostPrice;       //�ο��ɱ���          F�����
  double CurVal;          //�ο���ֵ
  double CurPrice;        //�ο��м�            F������
  double ProfitAndLoss;   //�ο�ӯ��
  
}TStockInfo;

////////////�ʺ���Ϣ/////////////////////////////////////////////////////////
typedef struct {
  char Capital[13]; //�ʽ��ʺ�
  char SH[13];      //�Ϻ��������ɶ�����  ,�����ڻ��ʺ�
  char SZ[13];      //���ڽ������ɶ�����
  char PW[13];      //�ʺ�����
}TAccountInfo;

typedef struct {
  char exchange[10];
//��1�� ����������
//��2�� ����������
//��3�� ��Լ����
//��4�� ��Լ����
//��5�� ÿ������
//��6�� Ͷ��
//��7�� ��ֵ
//��8�� �������
//��9�� �������
//��10�����ֲ�
}TFuctureCode;


#define MAX_TEXT 256

typedef struct {
  char Sender[10];         // ����ķ����ߣ��ջ���SYSTEM��ʾTRDSVR���򷢳��Ĵ���
  long ErrorCode;          // ErrorCodeΪ0��ʾû�д���
  char Text[MAX_TEXT+1];
}TInterfaceError;

#pragma pack()

}
//------------------------------------------------------------------------------
#endif
