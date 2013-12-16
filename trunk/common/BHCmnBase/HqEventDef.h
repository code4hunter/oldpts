#ifndef HQEventDefH
#define HQEventDefH

//
//������20060602
//˵�������PTS���鷢�����������ݼ��ʵ�ã��ʶ�ԭ�����鷢�Ͱ����о���
//�ο���PTS2���ϵͳ�ܹ�1.0
//

#include "UDynStr.h"
//---------------------------------------------------------------------------
//DBF�ļ�ͷ�ṹ--------------------------------------------------------------
//---------------------------------------------------------------------------
//struct DbfHead �������UDynStr.h

//---------------------------------------------------------------------------
//��֤����-------------------------------------------------------------------
//---------------------------------------------------------------------------
//struct TShow128 �������UDynStr.h
//---------------------------------------------------------------------------
//��ȯ����-------------------------------------------------------------------
//---------------------------------------------------------------------------
//struct TSjsHQ �������UDynStr.h

//---------------------------------------------------------------------------
//��֤֤ȯ��Ϣ---------------------------------------------------------------
//---------------------------------------------------------------------------
//struct TSjsXX �������UDynStr.h

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//�Զ���ṹ�ͷ������ݵ���֯-------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//enum TGuideType  �������UDynStr.h

#pragma pack(push, 1)

enum TFieldType{FT_COMBO=1, FT_COLOR=2, FT_FONT=3, FT_PATH=4, FT_FILENAME=5, FT_MULTFILENAME=6, FT_PICTURE=7, FT_CONNSTR=8, FT_INT=10,FT_DOUBLE=11,FT_BSTR=12};

struct THqEventHead
{
  int id;               //�¼���id	�뷢�������ProgIDһһ��Ӧ������Ψһ�����ֳ��¼������͡���������ֵ�event_id
  char type;            //�¼�����	���ڲ�ͬ���¼�,��ֵ���岻����ͬ����Ҫ���ڽ�һ�����ָ��¼���
  int count;            //��������	�����¼��ļ�¼����
  int date;             //��������	��ʾ���¼�����������
  int time;             //����ʱ��	�¼�������ʱ�䡣���缴ʱ���鷢����ʱ���ɽ��ر����ص�ʱ���
  char reserved[8];	    //�����ֶ�
  int fieldcnt;         //�������ݰ��ֶθ���	�ֶ��������event_desc
  int eventsize;        //�������ݰ��ֶδ�С	����event_data�����ݰ�ռ�õ��ֽ���
};

struct THqEventFields
{
  char name[8];			//�ֶ���	
  char type;			//�ֶ�����	��������ֵ�field_type
  int size;				//�ֶδ�С	�õض�ռ�õ��ֽ���
};

#define ACT_SECUCODE_LEN	30

enum THqSrc{hsSh=101, hsSz=102, hsHk=201/*���*/};
struct TSecuEventData
{
  unsigned long index;  //��Ʊ���ڴ��е����--��0��ʼ
  short src;		//��PTS,֤ȯ����ԴTHqSrc��101-��֤��102-��֤
  char code[ACT_SECUCODE_LEN+1];       //֤ȯ����
  char desc[9];     //֤ȯ���
  char type;            //֤ȯ����        ��  a�ɡ�b��
  unsigned long lc;     //ǰ���̼�

  unsigned long vlm;    //���ۼƳɽ�����
  unsigned long cv;     //��ǰ��
  unsigned long co;     //���̼�
  unsigned long ch;     //��߼�
  unsigned long cl;     //��ͼ�
  unsigned long cp;     //���¼�

  unsigned long bv1;    //����һ
  unsigned long bv2;    //������
  unsigned long bv3;    //������
  unsigned long bv4;    //������
  unsigned long bv5;    //������

  unsigned long bp1;    //���һ
  unsigned long bp2;    //��۶�
  unsigned long bp3;    //�����
  unsigned long bp4;    //�����
  unsigned long bp5;    //�����

  unsigned long sv1;    //����һ
  unsigned long sv2;    //������
  unsigned long sv3;    //������
  unsigned long sv4;    //������
  unsigned long sv5;    //������
  
  unsigned long sp1;    //����һ
  unsigned long sp2;    //���۶�
  unsigned long sp3;    //������
  unsigned long sp4;    //������
  unsigned long sp5;    //������
};

struct TSecuEventData2:TSecuEventData
{
	unsigned long preSettlePrice;			//���ս���
	
	//��ָ�ڻ��ĵ��ս�������ڻ���Լ���һСʱ�ɽ��۸��ճɽ����ļ�Ȩƽ���ۡ�
	unsigned long settlePrice;				//���ս���
};

struct TSecuEventData3
{
  unsigned long index;  //��Ʊ���ڴ��е����--��0��ʼ
  short src;		    //��PTS,֤ȯ����ԴTHqSrc��101-��֤��102-��֤
  char code[ACT_SECUCODE_LEN+1];       //֤ȯ����
  char desc[9];         //֤ȯ���
  char type;            //֤ȯ����        ��  a�ɡ�b��
  float lc;     //�������̼�

  unsigned long vlm;    //���ۼƳɽ�����
  unsigned long cv;     //��ǰ��
  float co;     //���̼�
  float ch;     //��߼�
  float cl;     //��ͼ�
  float cp;     //���¼�

  unsigned long bv1;    //����һ
  unsigned long bv2;    //������
  unsigned long bv3;    //������
  unsigned long bv4;    //������
  unsigned long bv5;    //������

  float bp1;    //���һ
  float bp2;    //��۶�
  float bp3;    //�����
  float bp4;    //�����
  float bp5;    //�����

  unsigned long sv1;    //����һ
  unsigned long sv2;    //������
  unsigned long sv3;    //������
  unsigned long sv4;    //������
  unsigned long sv5;    //������
  
  float sp1;    //����һ
  float sp2;    //���۶�
  float sp3;    //������
  float sp4;    //������
  float sp5;    //������

  double turnover; //�ɽ����
  float preSettlePrice;	//���ս���
  float settlePrice;    //���ս���
  //float closePrice;	    //����
  float chgPrice;       //�ǵ�
  float upperLimitPrice;//��ͣ��
  float lowerLimitPrice;//��ͣ��
  unsigned long ltime; //ʱ�� hhmmss
};

//---------------------------------------------------------------------------
#pragma pack(pop)

#endif
