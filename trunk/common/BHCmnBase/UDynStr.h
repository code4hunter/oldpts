#ifndef UDynStrH
#define UDynStrH

//---------------------------------------------------------------------------
//DBF�ļ�ͷ�ṹ--------------------------------------------------------------
//---------------------------------------------------------------------------
struct DbfHead {
  char  Flag;
  char  Year;
  char  Month;
  char  Day;
  int   RecNum;
  short HeadLen;
  short RecLen;
};
//---------------------------------------------------------------------------
//��֤����-------------------------------------------------------------------
//---------------------------------------------------------------------------
struct TShow128 {
  char DelFlag;
  char SecuID[6];           //��Ʊ����                 S1 C 6
  char SecuDesc[8];         //��Ʊ����                 S2 C 8
  char Lc[8];               //�������̼�               S3 N 8 3
  char Co[8];               //���̼�                   S4 N 8 3
  char Mny[12];             //�ۼƳɽ����             S5 N 12
  char Ch[8];               //��߼�                   S6 N 8 3
  char Cl[8];               //��ͼ�                   S7 N 8 3
  char Cp[8];               //���¼�                   S8 N 8 3
  char Cbp[8];              //��ǰ�����               S9 N 8 3
  char Csp[8];              //��ǰ������               S10 N 8 3
  char Vlm[10];             //�ۼƳɽ���               S11 N 10
  char Pe[8];               //��ӯ��                   S13 N 8 3
  char Bv1[10];             //����һ                   S15 N 10
  char Bp2[8];              //��۶�                   S16 N 8 3
  char Bv2[10];             //������                   S17 N 10
  char Bp3[8];              //�����                   S18 N 8 3
  char Bv3[10];             //������                   S19 N 10
  char Sv1[10];             //����һ                   S21 N 10
  char Sp2[8];              //���۶�                   S22 N 8 3
  char Sv2[10];             //������                   S23 N 10
  char Sp3[8];              //������                   S24 N 8 3
  char Sv3[10];             //������                   S25 N 10
  //�¼�
  char Bp4[8]; 	    //�������                 S26 N 8 3
  char Bv4[10];             //��������                 S27 N 10
  char Bp5[8]; 	    //�������                 S28 N 8 3
  char Bv5[10];             //��������                 S29 N 10
  char Sp4[8];              //��������                 S30 N 8 3
  char Sv4[10];             //��������                 S31 N 10
  char Sp5[8];              //��������                 S32 N 8 3
  char Sv5[10];             //��������                 S33 N 10

};
//---------------------------------------------------------------------------
//��ȯ����-------------------------------------------------------------------
//---------------------------------------------------------------------------
struct TSjsHQ {
  char DelFlag;
  char SecuID[6];           //֤ȯ����                 HQZQDM C 6
  char SecuDesc[8];         //֤ȯ����                 HQZQJC C 8
  char Lc[9];               //ǰ���̼�                 HQZRSP N 9 3
  char Co[9];               //���̼�                 HQJRKP N 9 3
  char Cp[9];               //���¼�                   HQZJCJ N 9 3
  char Vlm[12];             //���ۼƳɽ�����           HQCJSL N 12 0
  char Mny[17];             //���ۼƳɽ����  ��Ԫ��   HQCJJE N 17 3
  char NotUsed1[9];         //�ɽ�����                 HQCJBS N 9 0
  char Ch[9];               //��߼�                   HQZGCJ N 9 3
  char Cl[9];               //��ͼ�                   HQZDCJ N 9 3
  char Pe[7];               //��ӯ��1                  HQSYL1 N 7 2
  char NotUsed2[7];         //��ӯ��2                  HQSYL2 N 7 2
  char NotUsed3[9];         //�۸�����1                HQJSD1 N 9 3
  char NotUsed4[9];         //�۸�����2                HQJSD2 N 9 3
  char NotUsed5[12];        //��Լ�ֲ���               HQHYCC N 12 0
  char Sp5[9];              //������                   HQSJW5 N 9 3  +
  char Sv5[12];             //������                   HQSSL5 N 12 0 +
  char Sp4[9];              //������                   HQSJW4 N 9 3
  char Sv4[12];             //������                   HQSSL4 N 12 0
  char Sp3[9];              //������                   HQSJW3 N 9 3
  char Sv3[12];             //������                   HQSSL3 N 12 0
  char Sp2[9];              //���۶�                   HQSJW2 N 9 3
  char Sv2[12];             //������                   HQSSL2 N 12 0
  char Csp[9];              //����һ                   HQSJW1 N 9 3
  char Sv1[12];             //����һ                   HQSSL1 N 12 0
  char Cbp[9];              //���һ                   HQBJW1 N 9 3
  char Bv1[12];             //����һ                   HQBSL1 N 12 0
  char Bp2[9];              //��۶�                   HQBJW2 N 9 3
  char Bv2[12];             //������                   HQBSL2 N 12 0
  char Bp3[9];              //�����                   HQBJW3 N 9 3
  char Bv3[12];             //������                   HQBSL3 N 12 0
  char Bp4[9];              //�����                   HQBJW4 N 9 3
  char Bv4[12];             //������                   HQBSL4 N 12 0
  char Bp5[9];              //�����                   HQBJW5 N 9 3   +
  char Bv5[12];             //������                   HQBSL5 N 12 0  +
};
//---------------------------------------------------------------------------
//��֤֤ȯ��Ϣ20060406-------------------------------------------------------------------
//---------------------------------------------------------------------------
struct TSjsXX {
  char DelFlag;
  char SecuID[6];//XXZQDM	֤ȯ����	C	6
  char SecuDesc[8];//XXZQJC	֤ȯ���	C	8
  char DescEn[20];//XXYWJC	Ӣ�ļ��	C	20
  char Unit[4];//XXJYDW	���׵�λ	N	4,0
  char IndType[3];//XXHYZL	��ҵ����	C	3
  char MnyType[2];//XXHBZL	��������	C	2
  char FaceVal[7];//XXMGMZ	ÿ����ֵ	N	7,2
  char TolVol[12];//XXZFXL	�ܷ�����	N	12,0
  char Turnover[12];//XXLTGS	��ͨ����	N	12,0
  char LProfit[9];//XXSNLR	����ÿ������	N	9,4
  char TProfit[9];//XXBNLR	����ÿ������	N	9,4
  char HandTax[7];//XXJSFL	���ַ���	N	7,6  	���ɽ�������
  char PrtTax[7];//XXYHSL	ӡ��˰��	N	7,6  	���ɽ�������
  char TranTax[7];//XXGHFL	��������	N	7,6
  char IpoDate[8];//XXSSRQ	��������	D	8    	CCYYMMDD
  char ExpDate[8];//XXDJRQ	����/������	D	8    	CCYYMMDD
  char LimitVol[9];//XXMBXL	ÿ������	N	9,0
  char BuyNum[6];//XXBLDW	��������λ	N	6,0
  char SelNum[6];//XXSLDW	��������λ	N	6,0
  char PrcGrade[5];//XXJGDW	�۸�λ	N	5,3
  char SetPara[7];//XXJHCS	���Ͼ����޼۲���	N	7,3
  char ConPara[7];//XXLXCS	���������޼۲���	N	7,3
  char LimitPro;//XXXJXZ	�޼۲�������	N	1,0
  char MaxPrc[9];//XXZTJG	��ͣ�۸�	N	9,3
  char MinPrc[9];//XXDTJG	��ͣ�۸�	N	9,3
  char ConRatio[5];//XXZHBL	�ۺϱ���	N	5,2
  char TrdStatus;//XXJYZT	����״̬	C	1
  char SecuRank;//XXZQJB	֤ȯ����	C	1
  char StopFlag;//XXTPBZ	ͣ�Ʊ�־	C	1
  char BonusFlag;//XXCQCX	��Ȩ��Ϣ��־	C	1
  char ElemFlag;//XXCFBZ	�ɷݹɱ�־	C	1
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//�Զ���ṹ�ͷ������ݵ���֯-------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#pragma pack(push, 1)

struct TPListHead  {        //CurPList�ļ���ͷ
  long ShStockNum;          //��֤��Ʊ������������A��B��F��I��D)
  long ShSendTime;          //��֤���鷢��ʱ��
  long SzStockNum;          //��֤��Ʊ����
  long SzSendTime;          //��֤���鷢��ʱ��
  long PtfNum;
  long NoUsed[3];
};
//---------------------------------------------------------------------------
struct TSecuDesc {
  char SecuID[8];           //֤ȯ����        �Ϻ�  H+��Ʊ����   ����   S+��Ʊ����
  char SecuDesc[9];         //֤ȯ����
};
//---------------------------------------------------------------------------
struct TUDPSecuDesc {
  long SecuNo;     	        //��Ʊ���ڴ��е����
};
//---------------------------------------------------------------------------
//���Ͱ��ṹ-----------------------------------------------------------------
//---------------------------------------------------------------------------
struct TUDPPackage {
  long	PackageNo;			    //���ݱ������
  char	Type;				        //���ݱ�����P-���۵� D-��ʱ���� B���а�
  long	Sum;				        //�����͵����ݵļ�¼����
  void 	*Buf;				        //�����͵����ݼ����۵�����ʱ���ݡ����а����ݣ���С��������Ӧ��<8k��
};
//---------------------------------------------------------------------------
//���۵�---------------------------------------------------------------------
//---------------------------------------------------------------------------
struct TPriceListSta:TSecuDesc  {
  char          Type;       //֤ȯ����        ��  A�ɡ�B��
  char          Py[5];      //��Ʊ����ƴ��
  unsigned long V5da;       //ǰ5��ƽ��ÿ���ӳɽ��� Vlum of 5 Days Avg
  unsigned long FltStk;     //��ͨ�ɣ���
  unsigned long Lc;         //ǰ���̼�
  unsigned long Date;       //����
};
//---------------------------------------------------------------------------
struct TPriceListDyn {
  unsigned long Vlm;        //���ۼƳɽ�����
  double  Mny;              //���ۼƳɽ����  ��Ԫ��
  unsigned long Co;         //���̼�
  unsigned long Ch;         //��߼�
  unsigned long Cl;         //��ͼ�
  unsigned long Cp;         //���¼�
  unsigned long Pe;         //��ӯ��
  unsigned long Bv1;        //����һ
  unsigned long Bv2;        //������
  unsigned long Bv3;        //������
#ifndef USE3
	unsigned long Bv4;        //������
  unsigned long Bv5;        //������
#endif
  unsigned long Cbp;        //���һ
  unsigned long Bp2;        //��۶�
  unsigned long Bp3;        //�����
#ifndef USE3
	unsigned long Bp4;        //�����
  unsigned long Bp5;        //�����
#endif
  unsigned long Sv1;        //����һ
  unsigned long Sv2;        //������
  unsigned long Sv3;        //������
#ifndef USE3
	unsigned long Sv4;        //������
  unsigned long Sv5;        //������
#endif
  unsigned long Csp;        //����һ
  unsigned long Sp2;        //���۶�
  unsigned long Sp3;        //������
#ifndef USE3
	unsigned long Sp4;        //������
  unsigned long Sp5;        //������
#endif
  unsigned long Abv;        //����
  unsigned long Cv;         //��ǰ��
  unsigned long C5ma;       //5����ǰ���̼�  Close of 5 minutes ago
  unsigned long C4ma;       //4����ǰ���̼�
  unsigned long C3ma;       //3����ǰ���̼�
  unsigned long C2ma;       //2����ǰ���̼�
  unsigned long C1ma;       //1����ǰ���̼�
  unsigned long Time;       //ʱ��
  unsigned long Cmv;        //���µķ��ӳɽ���
  double        Cmm;        //���µķ��ӳɽ����
  unsigned long PVlm;       //�ϴ��ۼƳɽ�����
};
//---------------------------------------------------------------------------
struct TPriceList:TPriceListSta,TPriceListDyn {
};
//---------------------------------------------------------------------------
struct TUDPPriceListSta:TUDPSecuDesc,TPriceListSta{
};
//TUDPPriceList--------------------------------------------------------------
struct TUDPPriceList:TUDPSecuDesc,TPriceListDyn {
};
//---------------------------------------------------------------------------
//20050517----��ʼ����������ʱ�����������ݱ�Type='I'����Type='S'
struct TUDPPriceListInit : TUDPSecuDesc,TPriceList{
};
//---------------------------------------------------------------------------
//#pragma pack(push, 4)	
struct TUDPPriceListT{
  long SecuNo;     	        //��Ʊ���ڴ��е����
  unsigned long Vlm;        //���ۼƳɽ�����
  long me1;
  double  Mny;              //���ۼƳɽ����  ��Ԫ��
  unsigned long Co;         //���̼�
  unsigned long Ch;         //��߼�
  unsigned long Cl;         //��ͼ�
  unsigned long Cp;         //���¼�
  unsigned long Pe;         //��ӯ��
	unsigned long Bv1;        //����һ
  unsigned long Bv2;        //������
  unsigned long Bv3;        //������
#ifndef USE3
	unsigned long Bv4;        //������
  unsigned long Bv5;        //������
#endif
  unsigned long Cbp;        //���һ
  unsigned long Bp2;        //��۶�
  unsigned long Bp3;        //�����
#ifndef USE3
	unsigned long Bp4;        //�����
  unsigned long Bp5;        //�����
#endif
  unsigned long Sv1;        //����һ
  unsigned long Sv2;        //������
  unsigned long Sv3;        //������
#ifndef USE3
	unsigned long Sv4;        //������
  unsigned long Sv5;        //������
#endif
  unsigned long Csp;        //����һ
  unsigned long Sp2;        //���۶�
  unsigned long Sp3;        //������
#ifndef USE3
	unsigned long Sp4;        //������
  unsigned long Sp5;        //������
#endif
  unsigned long Abv;        //����
  unsigned long Cv;         //��ǰ��
  unsigned long C5ma;       //5����ǰ���̼�  Close of 5 minutes ago
  unsigned long C4ma;       //4����ǰ���̼�
  unsigned long C3ma;       //3����ǰ���̼�
  unsigned long C2ma;       //2����ǰ���̼�
  unsigned long C1ma;       //1����ǰ���̼�
  unsigned long Time;       //ʱ��
  unsigned long Cmv;        //���µķ��ӳɽ���
  double        Cmm;        //���µķ��ӳɽ����
  unsigned long PVlm;       //�ϴ��ۼƳɽ�����
  long me2;
  long me3;
};
#pragma pack(pop)

//---------------------------------------------------------------------------
//�ɽ���ϸ-------------------------------------------------------------------
//---------------------------------------------------------------------------
struct  TDetailDeal {
  unsigned long Time;       //ʱ��   HHMMSS
  unsigned long Cp;         //���¼۸�
  unsigned long Cv;         //����
};
//---------------------------------------------------------------------------
struct TDetailHead {
  unsigned long Date;
  long ShStockNum;          //��֤��Ʊ������������A��B��F��I��D)
  long SzStockNum;          //��֤��Ʊ����
  long PtfNum;
  long NoUsed[4];
  char IdxId[80000];
};
//---------------------------------------------------------------------------
struct TDetailTick {        //һ֧��Ʊ����ϸ����
  int  ExgNum;              //���״���
  unsigned long Lc;         //�������̼�
  TDetailDeal Dtl[2400];    //2400���ֱ�����
};
//---------------------------------------------------------------------------
struct  TDetailMin {
  unsigned long Time;
  unsigned long Ch;         //һ�������
  unsigned long Cl;         //һ�������
  unsigned long Co;         //һ���ӿ���
  unsigned long Ce;         //һ��������
  unsigned long Vlm;        //һ��������
  double        Mny;        //һ���ӽ��
};
//---------------------------------------------------------------------------
struct TDetailSecu {        //һ֧��Ʊ�ķ�������
  unsigned long Date;       //��������
  TDetailMin Min[242];      //242����������
};
//---------------------------------------------------------------------------
struct TDetailDynMin {      //һ֧��Ʊ�ķ�������
  int RecNum;               //���Ӽ�¼��
  unsigned long Date;
  TDetailMin Min[242];      //242����������
};
//---------------------------------------------------------------------------
//TUDPDetailDeal-------------------------------------------------------------
struct TUDPDetailDeal:TUDPSecuDesc,TDetailDeal {
};
//---------------------------------------------------------------------------
//���а�---------------------------------------------------------------------
//---------------------------------------------------------------------------
const int BrdStockAllNum = 480;    //12��ָ��*10������*4������
//---------------------------------------------------------------------------
struct TBillBoard:TSecuDesc{       //���а�ṹ
  unsigned long Cp;         //���¼�
  unsigned long Lc;         //��������
  long          IndexData;  //��Ҫ�����ָ������
};
//TUDPBillBoard--------------------------------------------------------------
struct TUDPBillBoard:TUDPSecuDesc,TBillBoard  {
};
//---------------------------------------------------------------------------
struct TMemPListDtlDl:TPriceList	{
	//ʮ��ָ��
	double Rc;   //ί��                Ration of Commision
	double Dc;   //ί��                Difference of commision
	double Rv;   //����                Ratio of Volum
	double Ap;   //����                Average price
	double Ef;   //�ǵ���              Extent of Fluctuate
	double Ft;   //�ǵ�                Fluctuate
	double Asv;  //����                Vlum of Sell
	double El;   //���                Extent of Librate
	double Re;   //������              Ratio of Exchange
};
//---------------------------------------------------------------------------
//ö��������ʾָ�������-----------------------------------------------------
//---------------------------------------------------------------------------
enum TDynType{
  dtSecuID,     //��Ʊ����
  dtSecuDesc,   //��Ʊ����
  dtRc,         //ί��
  dtDc,         //ί��
  dtRv,         //����
  dtAp,         //����
  dtEf,         //�ǵ�����%��
  dtFt,         //�ǵ�
  dtAbv,        //����
  dtAsv,        //����
  dtEl,         //���
  dtRe,         //������
  dtCp,         //�������¼�
  dtCo,         //���̼�
  dtCh,         //��߼�
  dtCl,         //��ͼ�
  dtVlm,        //�ɽ���
  dtMny,        //�ɽ���
  dtPe,         //��ӯ��
  dtTime,       //ʱ��
  dtDate,       //����
  dtCv,         //��ǰ��
  dtCbp,        //��ǰί���
  dtBp2,        //��۶�
  dtBp3,        //�����
  dtBv1,        //����һ
  dtBv2,        //������
  dtBv3,        //������
  dtCsp,        //��ǰί����
  dtSp2,        //���۶�
  dtSp3,        //������
  dtSv1,        //����һ
  dtSv2,        //������
  dtSv3,        //������
  dtC5ma,       //5����ǰ���̼�
  dtType,       //����
  dtPy,         //ƴ��
  dtV5da,       //ǰ5��ƽ��ÿ���ӳɽ���
  dtFltStk,     //��ͨ����
  dtLc,         //�������̼�
  dtCmv,        //���·��ӳɽ���
  dtCmm,        //���·��ӳɽ����
  dtPVlm
};
//---------------------------------------------------------------------------
enum TGuideType{gtIdx,gtHA,gtHB,gtSA,gtSB,gtFund,gtND};
//---------------------------------------------------------------------------
#endif
