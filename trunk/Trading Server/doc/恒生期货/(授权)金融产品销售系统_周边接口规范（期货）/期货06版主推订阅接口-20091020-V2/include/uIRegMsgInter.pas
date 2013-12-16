{/*=============================================================================
 * �� �� �������ƶ��Ľӿں�������					       *
 * ��    �ߣ� Hundsun							       *
 * �޸ļ�¼��  								       *
 * 20090917  xdx �޸��˽ӿڵĵ��ù�ԼΪstdcall
                 �޸��˲�����ʽarray of charΪPChar			       *
===============================================================================}
unit uIRegMsgInter;

interface

uses
 SysUtils,Classes,FutuDataStruct;

type
  TIRegMsgInterMaint = class (TObject)
  public
    {***************************************************************************
    * �������ƣ����ô������SetProxyParam       			       *
    * �������ܣ�							       *
    * ����������  szProxyIP    	��	�����������ַ			       *
    *		  dwdProxyPort 	:	����������˿�			       *
    *             szUserName    :       ������֤�û���(�������ҪУ�飬�������)*
    *             szUserpass    :       ������֤����(�������ҪУ�飬�������) *
    *             dProxyType    :       ��������(0:socks4����/1:socks5����/2:http����)*
    * ��    �ߣ�Hundsun							       *
    * �޸ļ�¼��						   	       *
    *                                                                          *
    ****************************************************************************}
    //xdx �޸��˲�����ʽPChar
    procedure SetProxyParam(const szProxyIP:PChar;dProxyPort:Word;const szUserName:PChar;const szUserpass:PChar;dProxyType:Word);virtual;stdcall;abstract;
    {***************************************************************************
    * �������ƣ��������Ӳ���SetCommParam				       *
    * �������ܣ�							       *
    * ����������  szIP		��	���Ʒ�������ַ			       *
    *		  dwPort       	:	���Ʒ������˿�			       *
    *		  dwCheckIDPort	:	�����֤�˿�			       *
    * ��    �ߣ�Hundsun							       *
    * �޸ļ�¼��						   	       *
    *                                                                          *
    ****************************************************************************}
    procedure SetCommParam(const szIP:PChar;dwPort:Word;dwCheckIDPort:Word);virtual;stdcall;abstract;
    {***************************************************************************
    * �������ƣ��������� StartService					       *
    * �������ܣ�							       *
    * ����������							       *
    *		 	                                                       *
    *		                                                               *
    * ��    �ߣ�Hundsun							       *
    * �޸ļ�¼��						   	       *
    *                                                                          *
    ****************************************************************************}
    function StartService : Integer;virtual;stdcall;abstract;
    {***************************************************************************
    * �������ƣ���¼ DoLogin	         				       *
    * �������ܣ�						               *
    * ����������szUserID  	��      �û���    			       *
    *		szUSerPass  	��      �û�����                               *
    *		                                                               *
    * ��    �ߣ�Hundsun							       *
    * �޸ļ�¼��						   	       *
    *                                                                          *
    ****************************************************************************}
    function DoLogin(const szUserID,szUSerPass:PChar):Integer;virtual;stdcall;abstract;
    {***************************************************************************
    * �������ƣ��ǳ� DoLogOut			        		       *
    * �������ܣ�							       *
    * ����������							       *
    *		 	                                                       *
    *		                                                               *
    * ��    �ߣ�Hundsun							       *
    * �޸ļ�¼��						   	       *
    *                                                                          *
    ****************************************************************************}
    function DoLogOut:Integer;virtual;stdcall;abstract;
    {***************************************************************************
    * �������ƣ��������� RegFutuPrice	                 		       *
    * �������ܣ�						               *
    * ����������PriceCodesStr  	:      ������������ַ��� ���Զ��ż��         *
    *	                                �磺WS905,a0905,cu0905,IF0905,         *
    *		iType           :      0:����    1����ѯ����                   *
    * ��    �ߣ�Hundsun							       *
    * �޸ļ�¼��						   	       *
    *                                                                          *
    ****************************************************************************}
    function RegFutuPrice(const PriceCodesStr:PChar;iType:Integer):Integer;virtual;stdcall;abstract;
    {***************************************************************************
    * �������ƣ��رշ��� StopService					       *
    * �������ܣ�							       *
    * ����������							       *
    *		 	                                                       *
    *		                                                               *
    * ��    �ߣ�Hundsun							       *
    * �޸ļ�¼��						   	       *
    *                                                                          *
    ****************************************************************************}
    function StopService : Integer;virtual;stdcall;abstract;
    {***************************************************************************
    * �������ƣ���¼��־ EnableLog	         			       *
    * �������ܣ���¼��־��Ӱ�����ܣ�һ����ڵ���ʱʹ�ã���־��������API����Ŀ¼*
    * ����������iLogRspFlag  	�� ���ķ�����־ ������ɽ��ر� :0 ����¼ 1 ��¼*
    *		iLogOtherFlag  	�� ����������־ �����ӳɹ� ���ӶϿ�            *
    *		                                                               *
    * ��    �ߣ�Hundsun							       *
    * �޸ļ�¼��						   	       *
    *                                                                          *
    ****************************************************************************}
    function EnableLog(iLogRspFlag,iLogOtherFlag:Integer): Integer;virtual;stdcall;abstract;
    {***************************************************************************
    * �������ƣ����󴴽� create	         				       *
    * �������ܣ�							       *
    * ����������							       *
    *		 	                                                       *
    *		                                                               *
    * ��    �ߣ�Hundsun							       *
    * �޸ļ�¼��						   	       *
    *                                                                          *
    ****************************************************************************}
   constructor create;virtual;abstract;
   end;

   TIRegMsgInterMaintClass = class of TIRegMsgInterMaint;

implementation

end.
