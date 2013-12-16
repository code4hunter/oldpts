# -*- coding:gb2312 -*-

import time
import win32com.client
import os.path
import ConfigParser
import sys
import os

LGN_Login			        = "00000000"	#柜员登录
LGN_Logout			        = "00000001"	#柜员注销	
TRD_CustLogin			    = "00100211"	#客户身份验证（返回全部股东）
TRD_NormalOrder			    = "00100030"	#普通委托
TRD_WithdrawOrder		    = "00100070"	#撤单委托			
QUERY_GetTodayOrderInfo	    = "00800010"	#当日委托查询
QUERY_GetSingleAcctId	    = "00800100"	#查询帐户资产信息
QUERY_StockListCombineQuery	= "00800220"	#股份查询
QUERY_GetTodayKnockInfo		= "00800030"	#当日成交查询

CONFIG_FILE = 'config.client.txt'

def load_config(filename):
    if not os.path.exists(filename):
        raise(Exception("Cann't find file:"+filename))

    config = ConfigParser.ConfigParser()
    config.readfp(open(filename))
    return config

def ODS(errType,message):
    #ERR,MSG,O-K
    print errType,"->",time.asctime(),message

if __name__ == "__main__":
    try:
        ODS("MSG","Loading config file," + CONFIG_FILE)
        #load config file
        cfg = load_config(CONFIG_FILE)
        optId  = cfg.get('basic','optId')
        optPwd = cfg.get('basic','optPwd')
        optMode = cfg.get('basic','optMode')
        exchId_SH = cfg.get('basic','exchId_SH')
        exchId_SZ = cfg.get('basic','exchId_SZ')
        acctId = cfg.get('basic','acctId')
        tradePwd = cfg.get('basic','tradePwd')
        
        #testing
        itf = win32com.client.Dispatch("GWstock.Package")
        
        #------------------------------------接口机认证-------------------------------------
        if itf.SetFunctionCode(LGN_Login)==False:
            ODS("ERR","SetFunctionCode")
            
        itf.flags = 0
        itf.serialno='00000000'
        itf.SetRecordCount(1)

        #设定发送记录内容：
        itf.SetValue(1, "optId",optId)		    #柜员代码
        itf.SetValue(1, "optPwd",optPwd)		#柜员口令
        itf.SetValue(1, "optMode",optMode)	    #委托方式
        
        #Send
        if itf.ExchangeMessage == True:
            if itf.GetSuccessFlg:
                ODS("O-K","LGN_Login")
            else:
                csErrId  = itf.GetErrId
                csErrMsg = itf.GetErrMsg
                ODS("ERR","LGN_Login ,ErrId=" + csErrId + ",ErrMsg="  + csErrMsg)
        else:
            ODS("ERR","LGN_Login ,ExchangeMessage Error")
        
        #------------------------------------客户身份验证-------------------------------------
        if itf.SetFunctionCode(TRD_CustLogin)==False:
            ODS("ERR","SetFunctionCode")
            
        itf.flags = 0
        itf.serialno='00000001'
        itf.SetRecordCount(1)

        #设定发送记录内容：
        itf.SetValue(1, "optId",optId)		    #柜员代码
        itf.SetValue(1, "optPwd",optPwd)		#柜员口令
        itf.SetValue(1, "optMode",optMode)      #委托方式
        itf.SetValue(1, "acctId",acctId)	    #资金帐号
        itf.SetValue(1, "tradePwd",tradePwd)    #口令
        #Send
        if itf.ExchangeMessage == True:
            if itf.GetSuccessFlg:
                ODS("O-K","TRD_CustLogin")
                retNum = itf.GetRecordCount
                ODS("MSG","------START------")
                for row in range(0,retNum):
                    ODS("MSG",itf.GetValue(row, "currencyId"))
                    ODS("MSG",itf.GetValue(row, "acctId"))
                    ODS("MSG",itf.GetValue(row, "acctName"))
                    ODS("MSG",itf.GetValue(row, "usableAmt"))
                    ODS("MSG",itf.GetValue(row, "currentAmt"))
                    ODS("MSG",itf.GetValue(row, "stkvalue"))
                    ODS("MSG",itf.GetValue(row, "exchId"))
                    ODS("MSG",itf.GetValue(row, "regId"))
                    ODS("MSG",itf.GetValue(row, "regName"))
                    ODS("MSG",itf.GetValue(row, "regmatchnum"))
                    ODS("MSG",itf.GetValue(row, "bankId"))
                    ODS("MSG",itf.GetValue(row, "isOrgFlag"))
                    ODS("MSG",itf.GetValue(row, "stdRegId"))
                    ODS("MSG",itf.GetValue(row, "acctId1"))
                ODS("MSG","------END------")
            else:
                csErrId  = itf.GetErrId
                csErrMsg = itf.GetErrMsg
                ODS("ERR","TRD_CustLogin ,ErrId=" + csErrId + ",ErrMsg="  + csErrMsg)
        else:
            ODS("ERR","TRD_CustLogin ,ExchangeMessage Error")
        
        #------------------------------------接口机注销-------------------------------------
        if itf.SetFunctionCode(LGN_Logout)==False:
            ODS("ERR","SetFunctionCode")
            
        itf.flags = 0
        itf.serialno='00000000'
        itf.SetRecordCount(1)

        #设定发送记录内容：
        itf.SetValue(1, "optId",optId)		    #柜员代码
        itf.SetValue(1, "optPwd",optPwd)		#柜员口令
        itf.SetValue(1, "optMode",optMode)	    #委托方式
        
        #Send
        if itf.ExchangeMessage == True:
            if itf.GetSuccessFlg:
                ODS("O-K","LGN_Logout")
            else:
                csErrId  = itf.GetErrId
                csErrMsg = itf.GetErrMsg
                ODS("ERR","LGN_Logout ,ErrId=" + csErrId + ",ErrMsg="  + csErrMsg)
        else:
            ODS("ERR","LGN_Logout ,ExchangeMessage Error")
    except: 
        ODS("ERR","Unexpected error:" + str(sys.exc_info()) )
    
    #os.system("PAUSE")