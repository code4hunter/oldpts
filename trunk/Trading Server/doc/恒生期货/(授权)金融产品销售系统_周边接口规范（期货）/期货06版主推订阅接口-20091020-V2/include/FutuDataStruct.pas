{/*=============================================================================
 * �� �� �������ƶ��Ľӿ�������ݰ�����					       *
 * ��    �ߣ� Hundsun							       *
 * �޸ļ�¼��
 * 20090917  ���Ӷ���TOrderRspInfo��TRealRspInfo                               *
 *									       *
===============================================================================}
unit FutuDataStruct;

interface

const
  MATCHSTR_LENGTH = 256;

  ErrNo_Heart          = 1001;   //'�Ѿ����δ�յ�����Ӧ�����������Ƿ��Ѷϣ�';
  ErrNo_ReadFEM        = 1002;   //'��ȡFEM�ļ����󣬲�����ֹ��';
  ErrNo_NotFoundFEM    = 1003;   //'FEM�ļ�δ�ҵ���������ֹ��';
  Error_NotFoundLicence = 1004;  //Licence�ļ�δ�ҵ�
  Error_InvalidDate    = 1005;   //'API�ѹ���Ч��';
  Error_LoadProxyDll   = 1006;   //'����ͨѶ��̬���ӿ����ʧ�ܣ�'
  Error_GetProcAddress = 1007;   //'GetProcAddress����'
  Error_ConnProxy      = 1008;   //'���Ӵ��������ʧ�ܣ�'

type
  // ��������
  pTMarketInfo = ^TMarketInfo;
  TMarketInfo = record
    contract_code: array[0..12] of Char;   //0 ��Լ����,
    pre_square_price: Double;              //1 ���ս�������
    futu_open_price: Double;               //2 ���̼�
    futu_last_price: Double;               //3 ���¼۸�
    buy_high_price: Double;                //4 ��������
    buy_high_amount: Integer;              //5 ������������
    buy_total_amount: Integer;             //6 ȫ������
    sale_low_price: Double;                //7 ������ۼ۸�
    sale_low_amount: Integer;              //8 �����������
    sale_total_amount: Integer;            //9 ȫ������
    futu_high_price: Double;               //10 ��߼�
    futu_low_price: Double;                //11 ��ͼ�
    average_price: Double;                 //12 ����
    change_direction: Double;              //13 ����
    business_amount: Integer;              //14 �ɽ���
    bear_amount: Integer;                  //15 �ܳ���
    business_balance: Double;              //16 �ɽ���
    uplimited_price: Double;               //17 ��ͣ��
    downlimited_price: Double;             //18 ��ͣ��
    futu_exch_type: array[0..2] of Char;   //19 �������
    form_buy_price: Double;                //20 �������۸�
    form_sale_price: Double;               //21 ��������۸�
    form_buy_amount: Integer;              //22 �����������
    form_sale_amount: Integer;             //23 �����������
    pre_close_price: Double;               //24 �������̼�
    pre_open_interest: Double;             //25 ���տ�����
    futu_close_price: Double;              //26 �������̼�
    square_price: Double;                  //27 �����
    pre_delta: Double;                     //28 ������ʵ��
    curr_delta: Double;                    //29 ������ʵ��
    bid_price2: Double;                    //30 �����
    bid_volume2: Integer;                  //31 �����
    bid_price3: Double;                    //32 ������
    bid_volume3: Integer;                  //33 ������
    bid_price4: Double;                    //34 ���ļ�
    bid_volume4: Integer;                  //35 ������
    bid_price5: Double;                    //36 �����
    bid_volume5: Integer;                  //37 ������
    ask_price2: Double;                    //38 ������
    ask_volume2: Integer;                  //39 ������
    ask_price3: Double;                    //40 ������
    ask_volume3: Integer;                  //41 ������
    ask_price4: Double;                    //42 ���ļ�
    ask_volume4: Integer;                  //43 ������
    ask_price5: Double;                    //44 �����
    ask_volume5: Integer;                  //45 ������
  end;

  // �������
  pTArgMarketInfo = ^TArgMarketInfo;
  TArgMarketInfo = record
    arbicontract_id: array[0..80] of Char; //0 ������Լ��
    futu_exch_type: array[0..2] of Char;   //1 �������
    first_code: array[0..12] of Char;      //2 ��һ��
    second_code: array[0..12] of Char;     //3 �ڶ���
    arbi_type: Char;                       //4 �������1-SPD, 2 -IPS
    buy_price: Double;                     //5 ��������
    buy_amount: Integer;                   //6 ������������
    buy_total_amount: Integer;             //7 ȫ������
    sale_price: Double;                    //8 ������ۼ۸�
    sale_amount: Integer;                  //9 �����������
    sale_total_amount: Integer;            //10 ȫ������
    futu_high_price: Double;               //11 ��߼�
    futu_low_price: Double;                //12 ��ͼ�
    uplimited_price: Double;               //13 ��ͣ��۸�
    downlimited_price: Double;             //14 ��ͣ��۸�
  end;

  //ί�з�����Ϣ
  pTOrderRspInfo = ^TOrderRspInfo;
  TOrderRspInfo = record
    entrust_no: Integer; //0 ί�к�
    futures_account: array[0..20] of Char; //1 ���ױ���
    futu_exch_type: array[0..10] of Char;  //2 ����������
    contract_code: array[0..12] of Char;   //3 ��Լ����
    entrust_name: array[0..8] of Char;     //4 ��������
    direction_name: array[0..8] of Char;   //6 ��ƽ����
    hedge_name: array[0..8] of Char;       //7 �ױ�����
    fund_account: Integer;                 //8 �ʽ��˻�
    futu_report_no: array[0..20] of Char;  //9 ���ص���
    firm_no: array[0..8] of Char;          //10 ��Ա��
    operator_no: array[0..8] of Char;      //11 ����Ա��
    client_group: Integer;                 //12 �ͻ����
    entrust_amount: Integer;               //13 ί������
    business_total_amount: Integer;        //14 �ɽ�������
    cacel_amount: Integer;                 //15 ��������
    entrust_price: Double;                 //16 ί�м۸�
    entrust_status: Char;                  //17 ί��״̬
    branch_no: Integer;                    //18 Ӫҵ����
    batch_no: Integer;                     //19 ί������
    futu_entrust_type: Char;               //20 ί������
    amount_per_hand: Integer;              //21 ��Լ����
    forceclose_reason: Char;               //22 ǿƽԭ��
    init_date : Integer;                   //23 ��������
    curr_time :Integer;                    //24 ��ǰʱ��
    confirm_no : array[0..20] of Char;     //25 ��������
    weave_type : Integer;                  //26 ���ί������
    arbitrage_code : array[0..20] of Char; //27 ���ί������
    time_condition : Integer;              //28 ��Ч������
    volume_condition  : Integer;           //29 �ɽ�������
    futu_entrust_prop : Integer;           //30 �ڻ�ί������
    frozen_fare : Double;                  //31 �����ܷ���
  end;

  //�ɽ�������Ϣ
  pTRealRspInfo = ^TRealRspInfo;
  TRealRspInfo = record
    entrust_no: Integer;                   //0 ί�к�
    futures_account: array[0..20] of Char; //1 ���ױ���
    futu_exch_type: array[0..10] of Char;  //2 ����������
    business_no: array[0..20] of Char;     //3 �ɽ����
    contract_code: array[0..12] of Char;   //4 ��Լ����
    entrust_name: array[0..8] of Char;     //5 ��������
    direction_name: array[0..8] of Char;   //6 ��ƽ����
    business_price: Double;                //7 �ɽ��۸�
    business_amount: Double;               //8 �ɽ�����
    hedge_name: array[0..8] of Char;       //9 �ױ�����
    fund_account: Integer;                 //10 �ʽ��˻�
    futu_report_no: array[0..20] of Char;  //11 ���ص���
    firm_no: array[0..8] of Char;          //12 ��Ա��
    operator_no: array[0..8] of Char;      //13 ����Ա��
    client_group: Integer;                 //14 �ͻ����
    entrust_amount: Integer;               //15 ί������
    business_total_amount: Integer;        //16 �ɽ�������
    cacel_amount: Integer;                 //17 ��������
    entrust_price: Double;                 //18 ί�м۸�
    entrust_status: Char;                  //19 ί��״̬
    branch_no: Integer;                    //20 Ӫҵ����
    batch_no: Integer;                     //21 ί������
    futu_entrust_type: Char;               //22 ί������
    amount_per_hand: Integer;              //23 ��Լ����
    forceclose_reason: Char;               //24 ǿƽԭ��
    init_date : Integer;                   //25 ��������
    business_time :Integer;                //26 �ɽ�ʱ��
    confirm_no : array[0..20] of Char;     //27 ��������
    frozen_fare : Double;                  //28 �����ܷ���
  end;
 
implementation

end.











