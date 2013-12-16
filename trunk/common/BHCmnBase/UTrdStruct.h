#ifndef UTrdStructH
#define UTrdStructH

// Attention
// Use Interger-Sized enums to compile this header

#define CODE_LEN    30        // ���볤��
#define SEQ_LEN     100       // ��ų���
#define ACC_LEN     20        // �ʺų���
#define PWD_LEN     20        // ���볤��
#define MAX_TEXT    256

#pragma pack(1)
// ʱ��    HHMMSS
// ����    YYYYMMDD

//�ʽ����
enum money_type
{
	motRMB = 'R', //RMB
	motUSD = 'U', //USD
	motHKD = 'H', //HKD
	motNo  = 'N'  //δ֪
};

//�ʺ����
enum account_type
{
	asSHA = '0',  //�Ϻ��������Ĺɶ�����
	asSZA = '1',  //���ڽ������Ĺɶ�����
	asJJS = '2',  //�Ϻ����ڽ������ͻ�����
	asFDL = '3',  //������Ʒ�ڻ�������
	asFZZ = '4',  //֣����Ʒ�ڻ�������
	asFSH = '5',  //�Ϻ���Ʒ�ڻ�������
	asHK  = '6',  //����������˻�
	//��ȯר��֤ȯ�˻�
	//�ͻ����ý��׵���֤ȯ�˻�
	//����ר���ʽ��˻�
	//�ͻ����ý��׵����ʽ��˻�
	asCA  = 'Z'   //�ʽ��ʺ�
};

//������
enum market_type
{
	mtSHA = 'e',  //�Ϻ�֤ȯ������
	mtSZA = 'f',  //����֤ȯ������
	mtJJS = 'j',  //�Ϻ����ڽ�����
	mtFSH = 'g',  //�Ϻ���Ʒ�ڻ�������
	mtFZZ = 'i',  //֣����Ʒ�ڻ�������
	mtFDL = 'h',  //������Ʒ�ڻ�������
	mtHK  = 'k',  //������Ͻ�����
	mtNo  = 'N'
};

//������� Type
enum order_type
{
	otBuy      = 'B', //��
	otSell     = 'S', //��
	otETFSub   = 'C', //ETF�깺
	otETFRed   = 'R', //ETF���
	otOpenBuy  = '1', //������
	otOpenSell = '2', //������
	otCloseBuy = '3', //ƽ����
	otCloseSell= '4', //ƽ����
	otLoanBuy  = '5', //������
	otLoanSell = '6', //��ȯ��
	otBuyRepay = '7', //��ȯ��ȯ
	otSellRepay= '8', //��ȯ����
	otCloseTodayBuy ='b',// ƽ�����
	otCloseTodaySell='s',// ƽ�����
	otNo       = 'N'  //����
};

//ί��״̬
enum order_state
{
	oswb = '0', //δ��(�ȴ��걨��...)
	osyb = '1', //�ѱ�(�Ѿ�����,��û���κγɽ�,�ȴ��ɽ���...)
	osdc = '2', //����(�����������µȴ�����)
	osbw = '3', //����(ȷ��״̬,���ֳ��������ֳɽ�)
	osyc = '4', //�ѳ�(ȷ��״̬,ȫ��������)
	oscj = '5', //�ѳ�(ȷ��״̬,��ȫ�ɽ�)
	osyf = '6', //�ѷ�(ȷ��״̬,ϵͳ����)
  osbc = '7', //����(�Ѿ��гɽ���,���ڳɽ���...
  osno = 'N'  //δ֪
};

//��λ���
enum pos_direction
{
	pdNo    = 'U', // δ֪
	pdNet   = 'N', // ��
	pdLong	= 'L', // ��ͷ
	pdShort = 'S'	 // ��ͷ
};

//ί����Ϣ
typedef struct
{
	 char     ContractID[SEQ_LEN+1];         //��ͬ���
	 char     SecuID[CODE_LEN+1];            //֤ȯ����
	 market_type  Market;                    //�����г�
	 long     Time;                          //ί��ʱ��  hhmmss
	 long     Date;                          //ί������  yyyymmdd
	 order_type  Type;                       //ί������
	 order_state State;                      //ί��״̬
	 long     CsnVol;                        //ί������
	 long     TrdVol;                        //�ɽ�����
	 long     CancelVol;                     //��������
	 double   CsnPrice;                      //ί�м۸�
	 double   TrdPrice;                      //�ɽ��۸�
	 char     Account[ACC_LEN+1];            //�ɶ���������ڻ����ױ��
	 char     SeqNum[SEQ_LEN+1];
} TOrderInfo;

//�ɽ���Ϣ
typedef struct  {
   char     ContractID[SEQ_LEN+1];         //��ͬ���
   char     SecuID[CODE_LEN+1];            //֤ȯ����
   char     TrdID[SEQ_LEN+1];              //�ɽ���ź�
   long     Time;                          //�ɽ�ʱ�� hhmmss
   long     Date;                          //�ɽ����� yyyymmdd
   order_type Type;                        //������� B,S
   long     Vol;                           //�ɽ�����Ϊ������ʾ����
   double   Price;                         //�ɽ��۸�
   market_type Market;                     //�г�
   char     Account[ACC_LEN+1];            //�ɶ���������ڻ����ױ��
   char     SeqNum[SEQ_LEN+1];             //��λ��


} TTradeInfo;

//�ɷ���Ϣ
typedef struct {
  char   SecuID[CODE_LEN+1];              //����
  char   Account[ACC_LEN+1];              //֤ȯ�ɶ��ʺŻ��߽������˺�
  pos_direction PosDir;                   //��λ����
  market_type  Market;

  int    Balance;                         //�������
  int    PosNum;                          //��ǰӵ����
  int    Available;                       //�ɷݿ�ƽ����

  double CostPrice;                       //�ο��ɱ���
  double CurPrice;                        //�ο��м�
}TStockInfo;

//�ʺ���Ϣ
typedef struct {
  account_type lt;         //�洢��¼ʱ���˻�����
  char Capital[ACC_LEN+1]; //�ʽ��ʺ�
  char SH[ACC_LEN+1];      //�Ϻ��������ɶ�����
  char SZ[ACC_LEN+1];      //���ڽ������ɶ�����
  char FJJS[ACC_LEN+1];    //�����ڻ��������������˺�
  char FDL[ACC_LEN+1];     //�����ڻ��������������˺�
  char FZZ[ACC_LEN+1];     //֣���ڻ��������������˺�
  char FSH[ACC_LEN+1];     //�Ϻ��ڻ��������������˺�
  char FHK[ACC_LEN+1];     //���������Ͷ�����˻�
  char PW[PWD_LEN+1];      //�ʺ�����
}TAccountInfo;

//�ʽ���Ϣ
typedef struct{
	money_type MoneyType;
  double balance;     //�ʽ����
  double available;   //�����ʽ�
}TMoneyInfo;

//������Ϣ
typedef struct {
	char Sender[SEQ_LEN+1];         // ����ķ����ߣ��ջ���SYSTEM��ʾTRDSVR���򷢳��Ĵ���
	long ErrorCode;          // ErrorCodeΪ0��ʾû�д���
  char Text[MAX_TEXT+1];
}TInterfaceError;


//Error Code ����
#define ERR_UNDO_ALREADY_FILLED -888100      // �Ѿ��ɽ���
#define ERR_UNDO_REPEAL         -888200      // �ϵ��޷�����
#define ERR_UNDO_ALREADY_CANCLED -888300     // �Ѿ�������
#define ERR_UNDO_CANNOT_CANCLE  -888301      // �޷�����(�����ٳ�����)
#define ERR_TRDSVR_SEND_FAILED  -888904      // TRDSVR ��������ʧ��
#define ERR_TRDSVR_RECV_FAILED  -888905      // TRDSVR ��������ʧ��
#define ERR_TRDSVR_OTHER_FAILED -888906      // TRDSVR �շ������е���������
#define ERR_REMOTE_SEND_FAILED  -888901      // Զ�̹�̨��������ʧ�ܣ�����δ���ͳɹ���
#define ERR_REMOTE_RECV_FAILED  -888902      // Զ�̹�̨��������ʧ�ܣ���������Ѿ����ͳɹ���
#define ERR_REMOTE_OTHER_FAILED -888903      // Զ�̹�̨�շ������е���������
#pragma pack()
//------------------------------------------------------------------------------
#endif
