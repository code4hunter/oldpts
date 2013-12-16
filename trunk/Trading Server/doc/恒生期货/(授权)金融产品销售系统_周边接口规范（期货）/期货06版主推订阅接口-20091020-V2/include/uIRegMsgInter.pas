{/*=============================================================================
 * 文 件 名：主推订阅接口函数定义					       *
 * 作    者： Hundsun							       *
 * 修改记录：  								       *
 * 20090917  xdx 修改了接口的调用规约为stdcall
                 修改了参数形式array of char为PChar			       *
===============================================================================}
unit uIRegMsgInter;

interface

uses
 SysUtils,Classes,FutuDataStruct;

type
  TIRegMsgInterMaint = class (TObject)
  public
    {***************************************************************************
    * 函数名称：设置代理参数SetProxyParam       			       *
    * 函数功能：							       *
    * 参数描述：  szProxyIP    	：	代理服务器地址			       *
    *		  dwdProxyPort 	:	代理服务器端口			       *
    *             szUserName    :       代理验证用户名(如果不需要校验，请输入空)*
    *             szUserpass    :       代理验证密码(如果不需要校验，请输入空) *
    *             dProxyType    :       代理类型(0:socks4代理/1:socks5代理/2:http代理)*
    * 作    者：Hundsun							       *
    * 修改记录：						   	       *
    *                                                                          *
    ****************************************************************************}
    //xdx 修改了参数形式PChar
    procedure SetProxyParam(const szProxyIP:PChar;dProxyPort:Word;const szUserName:PChar;const szUserpass:PChar;dProxyType:Word);virtual;stdcall;abstract;
    {***************************************************************************
    * 函数名称：设置连接参数SetCommParam				       *
    * 函数功能：							       *
    * 参数描述：  szIP		：	主推服务器地址			       *
    *		  dwPort       	:	主推服务器端口			       *
    *		  dwCheckIDPort	:	身份验证端口			       *
    * 作    者：Hundsun							       *
    * 修改记录：						   	       *
    *                                                                          *
    ****************************************************************************}
    procedure SetCommParam(const szIP:PChar;dwPort:Word;dwCheckIDPort:Word);virtual;stdcall;abstract;
    {***************************************************************************
    * 函数名称：启动服务 StartService					       *
    * 函数功能：							       *
    * 参数描述：							       *
    *		 	                                                       *
    *		                                                               *
    * 作    者：Hundsun							       *
    * 修改记录：						   	       *
    *                                                                          *
    ****************************************************************************}
    function StartService : Integer;virtual;stdcall;abstract;
    {***************************************************************************
    * 函数名称：登录 DoLogin	         				       *
    * 函数功能：						               *
    * 参数描述：szUserID  	：      用户名    			       *
    *		szUSerPass  	：      用户密码                               *
    *		                                                               *
    * 作    者：Hundsun							       *
    * 修改记录：						   	       *
    *                                                                          *
    ****************************************************************************}
    function DoLogin(const szUserID,szUSerPass:PChar):Integer;virtual;stdcall;abstract;
    {***************************************************************************
    * 函数名称：登出 DoLogOut			        		       *
    * 函数功能：							       *
    * 参数描述：							       *
    *		 	                                                       *
    *		                                                               *
    * 作    者：Hundsun							       *
    * 修改记录：						   	       *
    *                                                                          *
    ****************************************************************************}
    function DoLogOut:Integer;virtual;stdcall;abstract;
    {***************************************************************************
    * 函数名称：订阅请求 RegFutuPrice	                 		       *
    * 函数功能：						               *
    * 参数描述：PriceCodesStr  	:      订阅行情代码字符串 ，以逗号间隔         *
    *	                                如：WS905,a0905,cu0905,IF0905,         *
    *		iType           :      0:订阅    1：查询快照                   *
    * 作    者：Hundsun							       *
    * 修改记录：						   	       *
    *                                                                          *
    ****************************************************************************}
    function RegFutuPrice(const PriceCodesStr:PChar;iType:Integer):Integer;virtual;stdcall;abstract;
    {***************************************************************************
    * 函数名称：关闭服务 StopService					       *
    * 函数功能：							       *
    * 参数描述：							       *
    *		 	                                                       *
    *		                                                               *
    * 作    者：Hundsun							       *
    * 修改记录：						   	       *
    *                                                                          *
    ****************************************************************************}
    function StopService : Integer;virtual;stdcall;abstract;
    {***************************************************************************
    * 函数名称：记录日志 EnableLog	         			       *
    * 函数功能：记录日志会影响性能，一般仅在调试时使用，日志会生成在API所在目录*
    * 参数描述：iLogRspFlag  	： 订阅反馈日志 如行情成交回报 :0 不记录 1 记录*
    *		iLogOtherFlag  	： 其他操作日志 如连接成功 连接断开            *
    *		                                                               *
    * 作    者：Hundsun							       *
    * 修改记录：						   	       *
    *                                                                          *
    ****************************************************************************}
    function EnableLog(iLogRspFlag,iLogOtherFlag:Integer): Integer;virtual;stdcall;abstract;
    {***************************************************************************
    * 函数名称：对象创建 create	         				       *
    * 函数功能：							       *
    * 参数描述：							       *
    *		 	                                                       *
    *		                                                               *
    * 作    者：Hundsun							       *
    * 修改记录：						   	       *
    *                                                                          *
    ****************************************************************************}
   constructor create;virtual;abstract;
   end;

   TIRegMsgInterMaintClass = class of TIRegMsgInterMaint;

implementation

end.
