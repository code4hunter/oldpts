#ifndef sh_cjhb_rec_h
#define sh_cjhb_rec_h

#define MAX_REC 50

#pragma pack(1)

/* ============================================================ */
/*   Table: ASHARE_ORDWTH                                       */
/* ============================================================ */
struct ashare_ordwth
{
    int       rec_num          ;//         not null ,
    char      date  [8+1]      ;//         null    ,
    char      time  [8+1]      ;//         null    ,
    char      reff  [10+1]     ;//         null    ,
    char      acc   [10+1]     ;//         null    ,
    char      stock [6+1]      ;//         null    ,
    char      bs               ;//         null    ,
    char      price [8+1]      ;//         null    ,
    char      qty   [8+1]      ;//         null    ,
    char      status           ;//         null    ,
    char      owflag[3+1]      ;//         null    ,
    char      ordrec[8+1]      ;//         null    ,
    char      firmid[5+1]      ;//         null    ,
    BYTE    checkord[16]       ;//         null    ,
};

struct ordwth_s
{
    char      reff  [10+1]     ;//         null    ,
    char      acc   [10+1]     ;//         null    ,
    char      stock [6+1]      ;//         null    ,
    char      bs               ;//         null    ,
    char      price [8+1]      ;//         null    ,
    char      qty   [8+1]      ;//         null    ,
	char      owflag[3+1]      ;//         null    ,
    //char      ordrec[8+1]      ;//         null    ,
    char      firmid[5+1]      ;//         null    ,
};

/* ============================================================ */
/*   Table: ASHARE_ORDWTH2                                      */
/* ============================================================ */
struct ashare_ordwth2
{
    int   rec_num              ;//         not null ,
    char  date      [8+1]      ;//         null     ,
    char  time      [8+1]      ;//         null     ,
    char  reff      [10+1]     ;//         null     ,
    char  acc       [10+1]     ;//         null     ,
    char  stock     [6+1]      ;//         null     ,
    char  bs                   ;//         null     ,
    char  price     [8+1]      ;//         null     ,
    char  qty       [8+1]      ;//         null     ,
    char  status               ;//         null     ,
    char  qty2      [8+1]      ;//         null     ,
    char  remark    [30+1]     ;//         null     ,
    char  status1              ;//         null     ,
    char  teordernum[8+1]      ;//         null     ,
    char  owflag    [3+1]      ;//         null     ,
    char  ordrec    [8+1]      ;//         null     ,
    char  firmid    [5+1]      ;//         null     ,
    BYTE  checkord  [16]       ;//         null    ,
};                  

struct ordwth2_s
{
	char  reff [10+1];
	char  status               ;//         null     ,
    char  qty2      [8+1]      ;//         null     ,
    char  remark    [30+1]     ;//         null     ,
    char  teordernum[8+1]      ;//         null     ,

	char  date      [8+1]      ;//         null     ,
    char  time      [8+1]      ;//         null     ,
	char  acc       [10+1]     ;//         null     ,
    char  stock     [6+1]      ;//         null     ,
    char  bs                   ;//         null     ,
	char  firmid    [5+1]      ;//         null     ,
};

/* ============================================================ */
/*   Table: ASHARE_CJHB                                         */
/* ============================================================ */
struct ashare_cjhb  
{                   
    char        gddm[10+1]     ;//         null ,
    char        gdxm[8+1]      ;//         null    ,
    char        bcrq[8+1]      ;//         null    ,
    int         cjbh           ;//         not null ,
    char        gsdm[5+1]      ;//         null    ,
    char        cjsl[10+1]     ;//         null    ,
    char        bcye[10+1]     ;//         null    ,
    char        zqdm[6+1]      ;//         null    ,
    char        sbsj[6+1]      ;//         null    ,
    char        cjsj[6+1]      ;//         null    ,
    char        cjjg[8+1]      ;//         null    ,
    char        cjje[12+1]     ;//         null    ,
    char        sqbh[10+1]     ;//         null    ,
    char        bs             ;//         not null ,
    char        mjbh[5+1]      ;//         null    ,
};

/* ============================================================ */
/*   ���������̨ͬ����ͨ��QryDetail��ѯ�õ������ݣ��ѷֱʣ�    */
/* ============================================================ */
struct qry_cjhb
{
	char  reff [10+1];	//ί�б��
	char  jys;	//������,����PTS�ж���
	char  cjjg[8+1];	//�ɽ��۸�
	char  cjsl[10+1];	//�ɽ�����
	char  cdsl[10+1];	//����������ע������
};

/* ============================================================ */
/*   struct: shbp_rec                                           */
/* ============================================================ */
struct shbp_rec
{
	char type;   /* 1,2,3 : ashare_ordwth ,ashare_ordwth2 ,ashare_cjhb*/
	int  n;      /* How many records*/
	union
	{
		void * ptr;
		ashare_ordwth  ao [MAX_REC];
		ashare_ordwth2 ao2[MAX_REC];
		ashare_cjhb    ac [MAX_REC];
	}rec; 
};

#define ORDWTH		0x00000001
#define ORDWTH2     0x00000010
#define CJHB        0x00000100

#define MAX_FILTER_SIZE 512

/* ============================================================ */
/*   struct: filter_rec Fix ֮��Ĺ������ṹ                          */
/* ============================================================ */

struct filter_rec
{
	DWORD table;		// combine ORDWTH,ORDWTH2,CJHB
	char  text[MAX_FILTER_SIZE];
};

/* ============================================================ */
/*   �������ݰ���ʽ                                                       */
/* ============================================================ */

/*     .____________________.
//     |shbp_send_rec       |
//     |____________________|
//     |ashare_ordwth  .... |
//     |ashare_ordwth2 .... |
//     |ashare_cjhb    .... |
//     !____________________!
*/

struct shbp_send_rec
{
	char type[3];
	int n[3];
};


#pragma pack()

#endif 