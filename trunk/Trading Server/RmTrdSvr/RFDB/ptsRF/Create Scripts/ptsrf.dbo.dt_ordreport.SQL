/****** 对象:  Table [dbo].[dt_ordreport]    脚本日期: 11/01/2008 17:19:41 ******/
IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[dt_ordreport]') AND type in (N'U'))
DROP TABLE [dbo].[dt_ordreport]
GO
/****** 对象:  Table [dbo].[dt_ordreport]    脚本日期: 11/01/2008 17:19:41 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[dt_ordreport]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[dt_ordreport](
	[ID] [bigint] IDENTITY(1,1) NOT NULL,
	[OrderID] [bigint] NOT NULL,
	[Instid] [nvarchar](50) NOT NULL,
	[Execid] [nvarchar](50) NOT NULL,
	[ExecTime] [int] NOT NULL,
	[ExecDate] [int] NOT NULL,
	[ExecType] [nvarchar](2) NOT NULL,
	[ExecQty] [numeric](18, 0) NOT NULL,
	[ExecPrice] [numeric](13, 5) NOT NULL,
	[Account] [nvarchar](50) NOT NULL,
 CONSTRAINT [PK_dt_ordreport] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO

/****** 对象:  Index [id_account]    脚本日期: 11/01/2008 17:19:41 ******/
IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[dt_ordreport]') AND name = N'id_account')
CREATE NONCLUSTERED INDEX [id_account] ON [dbo].[dt_ordreport] 
(
	[ID] ASC,
	[OrderID] ASC,
	[ExecDate] ASC
)WITH (IGNORE_DUP_KEY = OFF) ON [PRIMARY]
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'	otBuy      = ''B'', //买
	otSell     = ''S'', //卖
	otETFSub   = ''C'', //ETF申购
	otETFRed   = ''R'', //ETF赎回
	otOpenBuy  = ''1'', //开仓买
	otOpenSell = ''2'', //开仓卖
	otCloseBuy = ''3'', //平仓买
	otCloseSell= ''4'', //平仓卖
	otLoanBuy  = ''5'', //融资买
	otLoanSell = ''6'', //融券卖
	otBuyRepay = ''7'', //买券还券
	otSellRepay= ''8'', //卖券还款
	otNo       = ''N''  //其他' ,@level0type=N'SCHEMA', @level0name=N'dbo', @level1type=N'TABLE', @level1name=N'dt_ordreport', @level2type=N'COLUMN', @level2name=N'ExecType'

GO
IF NOT EXISTS (SELECT * FROM sys.foreign_keys WHERE object_id = OBJECT_ID(N'[dbo].[FK_dt_ordreport_dt_orders]') AND parent_object_id = OBJECT_ID(N'[dbo].[dt_ordreport]'))
ALTER TABLE [dbo].[dt_ordreport]  WITH CHECK ADD  CONSTRAINT [FK_dt_ordreport_dt_orders] FOREIGN KEY([OrderID])
REFERENCES [dbo].[dt_orders] ([ID])
ON DELETE CASCADE
GO
