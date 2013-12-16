object frmMain: TfrmMain
  Left = 237
  Top = 122
  BorderWidth = 3
  Caption = 'Test Trade2'
  ClientHeight = 592
  ClientWidth = 949
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clSilver
  Font.Height = -12
  Font.Name = #26032#23435#20307
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 12
  object Splitter1: TSplitter
    Left = 233
    Top = 0
    Width = 4
    Height = 592
    ExplicitLeft = 273
    ExplicitHeight = 583
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 233
    Height = 592
    Align = alLeft
    BevelOuter = bvNone
    Caption = 'Panel1'
    TabOrder = 0
    Visible = False
    object GroupBox2: TGroupBox
      Left = 0
      Top = 0
      Width = 233
      Height = 592
      Align = alClient
      Caption = #26222#36890#19979#21333':'
      Color = clBtnFace
      ParentColor = False
      TabOrder = 0
      ExplicitLeft = 2
      object Label1: TLabel
        Left = 34
        Top = 180
        Width = 36
        Height = 12
        Caption = #20195#30721#65306
      end
      object Label2: TLabel
        Left = 34
        Top = 204
        Width = 36
        Height = 12
        Caption = #20215#26684#65306
      end
      object Label3: TLabel
        Left = 22
        Top = 302
        Width = 48
        Height = 12
        Caption = #22996#25176#21495#65306
      end
      object Label4: TLabel
        Left = 34
        Top = 228
        Width = 36
        Height = 12
        Caption = #25968#37327#65306
      end
      object Label5: TLabel
        Left = 10
        Top = 252
        Width = 60
        Height = 12
        Caption = #22996#25176#26041#24335#65306
      end
      object Bevel1: TBevel
        Left = 9
        Top = 161
        Width = 216
        Height = 7
        Shape = bsBottomLine
      end
      object Bevel2: TBevel
        Left = 9
        Top = 396
        Width = 216
        Height = 9
        Shape = bsBottomLine
      end
      object Label6: TLabel
        Left = 34
        Top = 277
        Width = 36
        Height = 12
        Caption = #24066#22330#65306
      end
      object Label7: TLabel
        Left = 10
        Top = 19
        Width = 60
        Height = 12
        Caption = #36135#24065#31867#22411#65306
      end
      object Label8: TLabel
        Left = 10
        Top = 45
        Width = 60
        Height = 12
        Caption = #22996#25176#23450#20301#65306
      end
      object Label9: TLabel
        Left = 10
        Top = 69
        Width = 60
        Height = 12
        Caption = #25104#20132#23450#20301#65306
      end
      object Label10: TLabel
        Left = 18
        Top = 416
        Width = 48
        Height = 12
        Caption = #26381#21153#22120#65306
      end
      object btLogin: TButton
        Left = 70
        Top = 531
        Width = 155
        Height = 21
        Caption = #30331#38470
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = btLoginClick
      end
      object btWithdraw: TButton
        Left = 71
        Top = 371
        Width = 154
        Height = 21
        Caption = #25764#21333
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 5
        OnClick = btWithdrawClick
      end
      object edCode: TEdit
        Left = 71
        Top = 177
        Width = 154
        Height = 20
        ImeMode = imDisable
        TabOrder = 7
      end
      object edPrice: TEdit
        Tag = 1
        Left = 71
        Top = 201
        Width = 154
        Height = 20
        ImeMode = imDisable
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 8
      end
      object edOrderID: TEdit
        Left = 70
        Top = 299
        Width = 99
        Height = 20
        ImeMode = imDisable
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 11
      end
      object btQryMoney: TButton
        Left = 70
        Top = 92
        Width = 76
        Height = 21
        Caption = #26597#38065
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = btQryMoneyClick
      end
      object btQryOrderByID: TButton
        Left = 71
        Top = 347
        Width = 154
        Height = 21
        Caption = #26597#25351#23450#22996#25176#21495
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = btQryOrderByIDClick
      end
      object edOrdNum: TEdit
        Tag = 2
        Left = 71
        Top = 225
        Width = 154
        Height = 20
        ImeMode = imDisable
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 9
      end
      object btQryStocks: TButton
        Left = 70
        Top = 116
        Width = 76
        Height = 21
        Caption = #26597#32929#20221
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = btQryStocksClick
      end
      object btQryOrder: TButton
        Left = 150
        Top = 92
        Width = 75
        Height = 21
        Caption = #26597#22996#25176
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = btQryOrderClick
      end
      object btQryTrade: TButton
        Left = 150
        Top = 116
        Width = 75
        Height = 21
        Caption = #26597#20132#26131
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 6
        OnClick = btQryTradeClick
      end
      object edAccount: TLabeledEdit
        Left = 70
        Top = 457
        Width = 155
        Height = 20
        EditLabel.Width = 36
        EditLabel.Height = 12
        EditLabel.Caption = #36134#21495#65306
        ImeMode = imDisable
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        LabelPosition = lpLeft
        TabOrder = 12
      end
      object edPassword: TLabeledEdit
        Left = 70
        Top = 480
        Width = 155
        Height = 20
        EditLabel.Width = 36
        EditLabel.Height = 12
        EditLabel.Caption = #23494#30721#65306
        ImeMode = imDisable
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        LabelPosition = lpLeft
        PasswordChar = '*'
        TabOrder = 13
      end
      object cbOrderType: TComboBox
        Tag = 3
        Left = 71
        Top = 249
        Width = 154
        Height = 20
        Style = csDropDownList
        ImeMode = imDisable
        ItemIndex = 0
        TabOrder = 10
        Text = 'B '#20080
        Items.Strings = (
          'B '#20080
          'S '#21334
          'C ETF'#30003#36141
          'R ETF'#36174#22238
          '1 '#24320#20179#20080
          '2 '#24320#20179#21334
          '3 '#24179#20179#20080
          '4 '#24179#20179#21334
          '5 '#34701#36164#20080
          '6 '#34701#21048#21334
          '7 '#20080#21048#36824#21048
          '8 '#21334#21048#36824#27454
          'N '#20854#20182
          'b '#24179#20170#20179#20080
          's '#24179#20170#20179#21334
          '')
      end
      object btGetAccount: TButton
        Left = 70
        Top = 140
        Width = 76
        Height = 21
        BiDiMode = bdLeftToRight
        Caption = #33719#21462#24080#21495
        ParentBiDiMode = False
        TabOrder = 14
        OnClick = btGetAccountClick
      end
      object cbHistoryAccount: TComboBox
        Left = 70
        Top = 434
        Width = 155
        Height = 20
        Style = csDropDownList
        ImeMode = imDisable
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 15
        OnChange = cbHistoryAccountChange
      end
      object btGetLastErr: TButton
        Left = 150
        Top = 140
        Width = 75
        Height = 21
        Caption = #26368#21518#38169#35823
        TabOrder = 16
        OnClick = btGetLastErrClick
      end
      object btLogout: TButton
        Left = 70
        Top = 555
        Width = 155
        Height = 21
        Caption = #30331#20986
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 17
        OnClick = btLogoutClick
      end
      object cbMarket: TComboBox
        Tag = 3
        Left = 71
        Top = 273
        Width = 154
        Height = 20
        Style = csDropDownList
        ImeMode = imDisable
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemIndex = 0
        TabOrder = 18
        Text = 'e '#19978#28023#35777#21048#20132#26131#25152
        Items.Strings = (
          'e '#19978#28023#35777#21048#20132#26131#25152
          'f '#28145#22323#35777#21048#20132#26131#25152
          'j '#19978#28023#37329#34701#20132#26131#25152
          'g '#19978#28023#21830#21697#26399#36135#20132#26131#25152
          'i '#37073#24030#21830#21697#26399#36135#20132#26131
          'h '#22823#36830#21830#21697#26399#36135#20132#26131
          'k '#39321#28207#32852#20132#25152
          'N '#26410#30693)
      end
      object cbLoginType: TComboBox
        Tag = 3
        Left = 70
        Top = 503
        Width = 155
        Height = 20
        Style = csDropDownList
        ImeMode = imDisable
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemIndex = 6
        TabOrder = 19
        Text = 'Z '#36164#37329#24080#21495
        Items.Strings = (
          '0 '#19978#28023#20132#26131#25152#30340#32929#19996#20195#30721
          '1 '#28145#22323#20132#26131#25152#30340#32929#19996#20195#30721
          '2 '#19978#28023#37329#34701#20132#26131#25152#23458#25143#20195#30721
          '3 '#22823#36830#21830#21697#26399#36135#20132#26131#25152
          '4 '#37073#24030#21830#21697#26399#36135#20132#26131#25152
          '5 '#19978#28023#21830#21697#26399#36135#20132#26131#25152
          'Z '#36164#37329#24080#21495)
      end
      object btOrder: TButton
        Left = 71
        Top = 323
        Width = 154
        Height = 21
        Caption = #22996#25176
        Font.Charset = GB2312_CHARSET
        Font.Color = clSilver
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 20
        OnClick = btOrderClick
      end
      object cbMoneyType: TComboBox
        Left = 70
        Top = 16
        Width = 155
        Height = 20
        Style = csDropDownList
        ImeMode = imDisable
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemIndex = 0
        TabOrder = 21
        Text = 'RMB'
        Items.Strings = (
          'RMB'
          'USD'
          'HKD'
          'N')
      end
      object edQryTrdSeq: TEdit
        Left = 70
        Top = 66
        Width = 110
        Height = 20
        ImeMode = imDisable
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 22
      end
      object edSvr: TEdit
        Left = 71
        Top = 411
        Width = 155
        Height = 20
        ImeMode = imDisable
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 23
        Text = '127.0.0.1:2005'
      end
      object edQryOrderSeq: TEdit
        Left = 70
        Top = 42
        Width = 110
        Height = 20
        ImeMode = imDisable
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 24
      end
      object edQryNum: TEdit
        Left = 186
        Top = 42
        Width = 37
        Height = 20
        ImeMode = imDisable
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 25
        Text = '10'
      end
      object btMultThTest: TButton
        Left = 10
        Top = 323
        Width = 55
        Height = 21
        Caption = #22810#32447#31243
        TabOrder = 26
        OnClick = btMultThTestClick
      end
      object edThreadNum: TEdit
        Left = 10
        Top = 371
        Width = 55
        Height = 20
        TabOrder = 27
        Text = '10'
      end
      object edOrderNum: TEdit
        Left = 10
        Top = 347
        Width = 55
        Height = 20
        TabOrder = 28
        Text = '100'
      end
      object cbTestSpeed: TCheckBox
        Left = 10
        Top = 143
        Width = 54
        Height = 17
        Caption = #27979#36895
        Checked = True
        State = cbChecked
        TabOrder = 29
      end
      object cbautoqry: TCheckBox
        Left = 3
        Top = 558
        Width = 67
        Height = 17
        Caption = #33258#21160#26597
        TabOrder = 30
        OnClick = cbautoqryClick
      end
      object btAddAccToqc: TButton
        Left = 10
        Top = 432
        Width = 55
        Height = 21
        Caption = '>>'
        TabOrder = 31
        OnClick = btAddAccToqcClick
      end
      object Button8: TButton
        Left = 175
        Top = 299
        Width = 48
        Height = 20
        Caption = '>>'
        TabOrder = 32
        OnClick = Button8Click
      end
    end
  end
  object PageControl1: TPageControl
    Left = 237
    Top = 0
    Width = 712
    Height = 592
    ActivePage = TabSheet1
    Align = alClient
    Font.Charset = GB2312_CHARSET
    Font.Color = clSilver
    Font.Height = -12
    Font.Name = #26032#23435#20307
    Font.Style = []
    ParentFont = False
    Style = tsFlatButtons
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'out'
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 704
        Height = 561
        Align = alClient
        Color = clSilver
        Font.Charset = GB2312_CHARSET
        Font.Color = clSilver
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        Lines.Strings = (
          '// '#26102#38388'    HHMMSS'
          '// '#26085#26399'    YYYYMMDD'
          ''
          '//'#36164#37329#31867#21035
          'enum money_type'
          '{'
          #9'motRMB = '#39'R'#39', //RMB'
          #9'motUSD = '#39'U'#39', //USD'
          #9'motHKD = '#39'H'#39', //HKD'
          #9'motNo  = '#39'N'#39'  //'#26410#30693
          '};'
          ''
          '//'#24080#21495#31867#21035
          'enum account_type'
          '{'
          #9'asSHA = '#39'0'#39',  //'#19978#28023#20132#26131#25152#30340#32929#19996#20195#30721
          #9'asSZA = '#39'1'#39',  //'#28145#22323#20132#26131#25152#30340#32929#19996#20195#30721
          #9'asJJS = '#39'2'#39',  //'#19978#28023#37329#34701#20132#26131#25152#23458#25143#20195#30721
          #9'asFDL = '#39'3'#39',  //'#22823#36830#21830#21697#26399#36135#20132#26131#25152
          #9'asFZZ = '#39'4'#39',  //'#37073#24030#21830#21697#26399#36135#20132#26131#25152
          #9'asFSH = '#39'5'#39',  //'#19978#28023#21830#21697#26399#36135#20132#26131#25152
          #9'asHK  = '#39'6'#39',  //'#39321#28207#32852#20132#25152#36134#25143
          #9'//'#34701#21048#19987#29992#35777#21048#36134#25143
          #9'//'#23458#25143#20449#29992#20132#26131#25285#20445#35777#21048#36134#25143
          #9'//'#34701#36164#19987#29992#36164#37329#36134#25143
          #9'//'#23458#25143#20449#29992#20132#26131#25285#20445#36164#37329#36134#25143
          #9'asCA  = '#39'Z'#39'   //'#36164#37329#24080#21495
          '};'
          ''
          '//'#20132#26131#25152
          'enum market_type'
          '{'
          #9'mtSHA = '#39'e'#39',  //'#19978#28023#35777#21048#20132#26131#25152
          #9'mtSZA = '#39'f'#39',  //'#28145#22323#35777#21048#20132#26131#25152
          #9'mtJJS = '#39'j'#39',  //'#19978#28023#37329#34701#20132#26131#25152
          #9'mtFSH = '#39'g'#39',  //'#19978#28023#21830#21697#26399#36135#20132#26131#25152
          #9'mtFZZ = '#39'i'#39',  //'#37073#24030#21830#21697#26399#36135#20132#26131#25152
          #9'mtFDL = '#39'h'#39',  //'#22823#36830#21830#21697#26399#36135#20132#26131#25152
          #9'mtHK  = '#39'k'#39',  //'#39321#28207#32852#21512#20132#26131#25152
          #9'mtNo  = '#39'N'#39
          '};'
          ''
          '//'#20080#21334#31867#21035' Type'
          'enum order_type'
          '{'
          #9'otBuy      = '#39'B'#39', //'#20080
          #9'otSell     = '#39'S'#39', //'#21334
          #9'otETFSub   = '#39'C'#39', //ETF'#30003#36141
          #9'otETFRed   = '#39'R'#39', //ETF'#36174#22238
          #9'otOpenBuy  = '#39'1'#39', //'#24320#20179#20080
          #9'otOpenSell = '#39'2'#39', //'#24320#20179#21334
          #9'otCloseBuy = '#39'3'#39', //'#24179#20179#20080
          #9'otCloseSell= '#39'4'#39', //'#24179#20179#21334
          #9'otLoanBuy  = '#39'5'#39', //'#34701#36164#20080
          #9'otLoanSell = '#39'6'#39', //'#34701#21048#21334
          #9'otBuyRepay = '#39'7'#39', //'#20080#21048#36824#21048
          #9'otSellRepay= '#39'8'#39', //'#21334#21048#36824#27454
          #9'otCloseTodayBuy ='#39'b'#39'// '#24179#20170#20179#20080
          #9'otCloseTodaySell='#39's'#39'// '#24179#20170#20179#21334
          #9'otNo       = '#39'N'#39'  //'#20854#20182
          '};'
          ''
          '//'#22996#25176#29366#24577
          'enum order_state'
          '{'
          '        oswb = '#39'0'#39', //'#26410#25253
          '        osyb = '#39'1'#39', //'#24050#25253
          '        osdc = '#39'2'#39', //'#24453#25764
          '        osbw = '#39'3'#39', //'#37096#25764
          '        osyc = '#39'4'#39', //'#24050#25764
          '        oscj = '#39'5'#39', //'#24050#25104
          '        osyf = '#39'6'#39', //'#24050#24223
          '        osbc = '#39'7'#39', //'#37096#25104
          '        osno = '#39'N'#39'  //'#26410#30693
          '};'
          ''
          '//'#20179#20301#31867#21035
          'enum pos_direction'
          '{'
          #9'pdNo    = '#39'U'#39', // '#26410#30693
          #9'pdNet   = '#39'N'#39', // '#20928
          #9'pdLong'#9'= '#39'L'#39', // '#22810#22836
          #9'pdShort = '#39'S'#39'  // '#31354#22836
          '};'
          ''
          
            '----------------------------------------------------------------' +
            '-------------')
        ParentFont = False
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'wk...'
      ImageIndex = 1
      object lvWorking: TListView
        Left = 0
        Top = 0
        Width = 704
        Height = 532
        Align = alClient
        Color = clBlack
        Columns = <>
        Font.Charset = GB2312_CHARSET
        Font.Color = clLime
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ReadOnly = True
        RowSelect = True
        ParentFont = False
        SmallImages = ImageList1
        TabOrder = 0
        ViewStyle = vsReport
      end
      object Panel3: TPanel
        Left = 0
        Top = 532
        Width = 704
        Height = 29
        Align = alBottom
        BevelOuter = bvNone
        TabOrder = 1
        object Label11: TLabel
          Left = 392
          Top = 8
          Width = 60
          Height = 12
          Caption = #26410#25104#20132#24066#20540
        end
        object btrefOrders: TButton
          Left = 223
          Top = 5
          Width = 75
          Height = 21
          Caption = #21047#26032
          TabOrder = 0
          OnClick = btrefOrdersClick
        end
        object btCancelAll: TButton
          Left = 0
          Top = 5
          Width = 75
          Height = 21
          Caption = #20840#37096#25764#28040
          TabOrder = 1
          OnClick = btCancelAllClick
        end
        object btLoadAll: TButton
          Left = 91
          Top = 6
          Width = 126
          Height = 21
          Caption = #36733#20837#25152#26377#26410#25104#20132#22996#25176
          TabOrder = 2
          OnClick = btLoadAllClick
        end
        object Button5: TButton
          Left = 304
          Top = 5
          Width = 75
          Height = 21
          Caption = 'copy'
          TabOrder = 3
          OnClick = Button5Click
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'pos'
      ImageIndex = 2
      object lvPos: TListView
        Left = 0
        Top = 0
        Width = 519
        Height = 532
        Align = alClient
        Color = clBlack
        Columns = <
          item
            Caption = #20195#30721
            Width = 60
          end
          item
            Caption = #32929#19996#36134#25143
            Width = 60
          end
          item
            Caption = #20313#39069
            Width = 60
          end
          item
            Caption = #21487#29992
            Width = 60
          end
          item
            Caption = #25317#26377#32929#25968
            Width = 60
          end
          item
            Caption = #25104#26412#20215
            Width = 70
          end
          item
            Caption = #24403#21069#20215
            Width = 70
          end
          item
            Caption = #37096#20301
            Width = 60
          end
          item
            Caption = #24066#22330
            Width = 60
          end
          item
            Caption = #28014#21160#30408#20111
            Width = 70
          end>
        Font.Charset = GB2312_CHARSET
        Font.Color = clLime
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ReadOnly = True
        RowSelect = True
        ParentFont = False
        SmallImages = ImageList1
        TabOrder = 0
        ViewStyle = vsReport
      end
      object Panel2: TPanel
        Left = 0
        Top = 532
        Width = 704
        Height = 29
        Align = alBottom
        BevelOuter = bvNone
        TabOrder = 1
        object lbMktValue: TLabel
          Left = 336
          Top = 8
          Width = 36
          Height = 12
          Caption = #24635#24066#20540
        end
        object btRfPosition: TButton
          Left = 1
          Top = 5
          Width = 75
          Height = 21
          Caption = #21047#26032
          TabOrder = 0
          OnClick = btRfPositionClick
        end
        object btClear: TButton
          Left = 82
          Top = 5
          Width = 85
          Height = 21
          Caption = #28165#20179
          TabOrder = 1
          OnClick = btClearClick
        end
        object edFixPrc: TEdit
          Left = 173
          Top = 6
          Width = 84
          Height = 20
          Hint = #20197#24403#21069#20215#19978#28014'N'#20803#38065#19979#21333
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
          Text = #19968#26723#20215
        end
        object cbAllStk: TCheckBox
          Left = 607
          Top = 0
          Width = 97
          Height = 29
          Align = alRight
          Caption = #25152#26377#32929#20221
          Checked = True
          State = cbChecked
          TabOrder = 3
        end
        object edCloseAmt: TEdit
          Left = 263
          Top = 6
          Width = 66
          Height = 20
          Hint = #19968#27425#28165#20179#30340#24066#20540
          ParentShowHint = False
          ShowHint = True
          TabOrder = 4
          Text = '1000000'
        end
        object cbPrint: TCheckBox
          Left = 495
          Top = 0
          Width = 112
          Height = 29
          Align = alRight
          Caption = #21482#29983#25104#22996#25176#21015#34920
          Checked = True
          State = cbChecked
          TabOrder = 5
        end
      end
      object moExcept: TMemo
        Left = 519
        Top = 0
        Width = 185
        Height = 532
        Align = alRight
        Lines.Strings = (
          '000001,17400'
          '510050,1000000'
          '600000,105600'
          '600015,60000'
          '600016,192000'
          '600036,131000'
          '601009,75000'
          '601166,72000'
          '601288,990756'
          '601328,132000'
          '601398,242900'
          '601939,381900')
        TabOrder = 2
      end
    end
    object TabSheet4: TTabSheet
      ImageIndex = 3
      object lbQryCount: TLabel
        Left = 176
        Top = 8
        Width = 6
        Height = 12
        Caption = '0'
      end
      object lbSeq: TLabel
        Left = 698
        Top = 0
        Width = 6
        Height = 30
        Align = alRight
        Alignment = taCenter
        Layout = tlCenter
        ExplicitHeight = 12
      end
      object btStartQry: TButton
        Left = 3
        Top = 3
        Width = 75
        Height = 22
        Caption = #24320#22987#26597
        TabOrder = 0
        OnClick = btStartQryClick
      end
      object btStopQry: TButton
        Left = 84
        Top = 3
        Width = 75
        Height = 22
        Caption = #20572#27490
        Enabled = False
        TabOrder = 1
        OnClick = btStopQryClick
      end
      object moTrade: TMemo
        Left = 0
        Top = 30
        Width = 704
        Height = 531
        Align = alBottom
        Anchors = [akLeft, akTop, akRight, akBottom]
        Color = clBlack
        Font.Charset = GB2312_CHARSET
        Font.Color = clYellow
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 2
        WordWrap = False
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'fuck'
      ImageIndex = 4
      DesignSize = (
        704
        561)
      object Splitter2: TSplitter
        Left = 0
        Top = 24
        Width = 704
        Height = 3
        Cursor = crVSplit
        Align = alTop
        ExplicitTop = 54
        ExplicitWidth = 466
      end
      object moccAccs: TMemo
        Left = 0
        Top = 0
        Width = 704
        Height = 24
        Align = alTop
        Color = clWhite
        ScrollBars = ssVertical
        TabOrder = 0
        WordWrap = False
      end
      object qcListview: TListView
        Left = 0
        Top = 27
        Width = 480
        Height = 505
        Align = alClient
        Color = clGray
        Columns = <>
        Font.Charset = GB2312_CHARSET
        Font.Color = clSilver
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ReadOnly = True
        RowSelect = True
        ParentFont = False
        SmallImages = ImageList1
        TabOrder = 1
        ViewStyle = vsReport
        ExplicitTop = 246
        ExplicitWidth = 448
        ExplicitHeight = 286
      end
      object Panel4: TPanel
        Left = 0
        Top = 532
        Width = 704
        Height = 29
        Align = alBottom
        BevelOuter = bvNone
        TabOrder = 2
        object Button2: TButton
          Left = 300
          Top = 6
          Width = 75
          Height = 21
          Caption = 'r'
          TabOrder = 0
          OnClick = Button2Click
        end
        object Button3: TButton
          Left = 219
          Top = 6
          Width = 75
          Height = 21
          Caption = 'c'
          TabOrder = 1
          OnClick = Button3Click
        end
        object Button4: TButton
          Left = 87
          Top = 6
          Width = 126
          Height = 21
          Caption = 'wcj'
          TabOrder = 2
          OnClick = Button4Click
        end
        object Button1: TButton
          Left = 381
          Top = 6
          Width = 85
          Height = 21
          TabOrder = 3
          Visible = False
          OnClick = Button1Click
        end
        object btLoadItf: TButton
          Left = 2
          Top = 6
          Width = 79
          Height = 21
          Caption = 'l'
          TabOrder = 4
          OnClick = btLoadItfClick
        end
        object cbonlylist: TCheckBox
          Left = 591
          Top = 0
          Width = 113
          Height = 29
          Align = alRight
          Caption = #21482#29983#25104#22996#25176#21015#34920
          Checked = True
          State = cbChecked
          TabOrder = 5
        end
      end
      object Memo2: TMemo
        Left = 480
        Top = 27
        Width = 224
        Height = 505
        Align = alRight
        Color = clSilver
        Lines.Strings = (
          '-'#24080#21495','#20195#30721','#24066#22330','#37327','#20215#26684','#22996#25176#26041#24335)
        ScrollBars = ssBoth
        TabOrder = 3
        WordWrap = False
      end
      object Button6: TButton
        Left = 283
        Top = 468
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = 'fuck me'
        TabOrder = 4
        OnClick = Button6Click
      end
      object Button7: TButton
        Left = 283
        Top = 437
        Width = 75
        Height = 25
        Anchors = [akTop, akRight]
        Caption = 'c'
        TabOrder = 5
        OnClick = Button7Click
      end
    end
  end
  object cbFilter: TCheckBox
    Left = 766
    Top = 4
    Width = 97
    Height = 17
    Caption = #25490#38500#37327
    Checked = True
    State = cbChecked
    TabOrder = 2
  end
  object ImageList1: TImageList
    Left = 88
    Top = 248
    Bitmap = {
      494C010114007400740010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000006000000001002000000000000060
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CE9C63009C3100009C310000CE9C63000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B5B5B5009C9C9C009C9C9C00B5B5B5000000000000000000000000000000
      000000000000000000000000000000000000000000009C3100009C3100009C31
      00009C31000000000000000000000000000000000000000000009C3100009C31
      00009C3100009C3100000000000000000000000000009C9C9C009C9C9C009C9C
      9C009C9C9C0000000000000000000000000000000000000000009C9C9C009C9C
      9C009C9C9C009C9C9C0000000000000000000000000000000000000000009C31
      00009C310000CE630000CE6300009C3100000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C009C9C9C00CECECE00CECECE009C9C9C000000000000000000000000000000
      000000000000000000000000000000000000000000009C310000CE630000CE63
      0000CE6300009C3100000000000000000000000000009C310000CE630000CE63
      0000CE6300009C3100000000000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE009C9C9C000000000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE009C9C9C00000000000000000000000000000000009C310000CE63
      0000CE6300009C3100009C310000CE9C63000000000000000000000000000000
      00000000000000000000000000000000000000000000000000009C9C9C00CECE
      CE00CECECE009C9C9C009C9C9C00B5B5B5000000000000000000000000000000
      00000000000000000000000000000000000000000000000000009C310000CE63
      0000CE630000CE6300009C310000000000009C310000CE630000CE630000CE63
      00009C31000000000000000000000000000000000000000000009C9C9C00CECE
      CE00CECECE00CECECE009C9C9C00000000009C9C9C00CECECE00CECECE00CECE
      CE009C9C9C0000000000000000000000000000000000CE9C63009C310000CE63
      00009C310000CE9C630000000000000000009C3100009C3100009C3100009C31
      00009C3100009C3100009C3100000000000000000000B5B5B5009C9C9C00CECE
      CE009C9C9C00B5B5B50000000000000000009C9C9C009C9C9C009C9C9C009C9C
      9C009C9C9C009C9C9C009C9C9C00000000000000000000000000000000009C31
      0000CE630000CE630000CE6300009C310000CE630000CE630000CE6300009C31
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C00CECECE00CECECE00CECECE009C9C9C00CECECE00CECECE00CECECE009C9C
      9C0000000000000000000000000000000000000000009C310000CE6300009C31
      0000CE9C63000000000000000000000000009C310000CE630000CE630000CE63
      0000CE630000CE6300009C31000000000000000000009C9C9C00CECECE009C9C
      9C00B5B5B5000000000000000000000000009C9C9C00CECECE00CECECE00CECE
      CE00CECECE00CECECE009C9C9C00000000000000000000000000000000000000
      00009C310000CE630000CE630000CE630000CE630000CE6300009C3100000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009C9C9C00CECECE00CECECE00CECECE00CECECE00CECECE009C9C9C000000
      000000000000000000000000000000000000000000009C310000CE6300009C31
      000000000000000000000000000000000000000000009C310000CE630000CE63
      0000CE630000CE6300009C31000000000000000000009C9C9C00CECECE009C9C
      9C0000000000000000000000000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE00CECECE009C9C9C00000000000000000000000000000000000000
      0000000000009C310000CE630000CE630000CE6300009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C9C9C00CECECE00CECECE00CECECE009C9C9C00000000000000
      000000000000000000000000000000000000000000009C310000CE6300009C31
      0000CE9C630000000000000000000000000000000000CE9C63009C310000CE63
      0000CE630000CE6300009C31000000000000000000009C9C9C00CECECE009C9C
      9C00B5B5B50000000000000000000000000000000000B5B5B5009C9C9C00CECE
      CE00CECECE00CECECE009C9C9C00000000000000000000000000000000000000
      00009C310000CE630000CE630000CE630000CE630000CE6300009C3100000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009C9C9C00CECECE00CECECE00CECECE00CECECE00CECECE009C9C9C000000
      00000000000000000000000000000000000000000000CE9C63009C310000CE63
      00009C310000CE9C630000000000CE9C63009C3100009C310000CE6300009C31
      0000CE630000CE6300009C3100000000000000000000B5B5B5009C9C9C00CECE
      CE009C9C9C00B5B5B50000000000B5B5B5009C9C9C009C9C9C00CECECE009C9C
      9C00CECECE00CECECE009C9C9C00000000000000000000000000000000009C31
      0000CE630000CE630000CE6300009C310000CE630000CE630000CE6300009C31
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C00CECECE00CECECE00CECECE009C9C9C00CECECE00CECECE00CECECE009C9C
      9C000000000000000000000000000000000000000000000000009C310000CE63
      0000CE6300009C3100009C3100009C310000CE630000CE6300009C310000CE9C
      63009C310000CE6300009C3100000000000000000000000000009C9C9C00CECE
      CE00CECECE009C9C9C009C9C9C009C9C9C00CECECE00CECECE009C9C9C00B5B5
      B5009C9C9C00CECECE009C9C9C000000000000000000000000009C310000CE63
      0000CE630000CE6300009C310000000000009C310000CE630000CE630000CE63
      00009C31000000000000000000000000000000000000000000009C9C9C00CECE
      CE00CECECE00CECECE009C9C9C00000000009C9C9C00CECECE00CECECE00CECE
      CE009C9C9C000000000000000000000000000000000000000000000000009C31
      00009C310000CE630000CE630000CE6300009C3100009C310000000000000000
      0000000000009C3100009C310000000000000000000000000000000000009C9C
      9C009C9C9C00CECECE00CECECE00CECECE009C9C9C009C9C9C00000000000000
      0000000000009C9C9C009C9C9C0000000000000000009C310000CE630000CE63
      0000CE6300009C3100000000000000000000000000009C310000CE630000CE63
      0000CE6300009C3100000000000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE009C9C9C000000000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE009C9C9C0000000000000000000000000000000000000000000000
      0000CE9C63009C3100009C3100009C310000CE9C630000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B5B5B5009C9C9C009C9C9C009C9C9C00B5B5B50000000000000000000000
      000000000000000000000000000000000000000000009C3100009C3100009C31
      00009C31000000000000000000000000000000000000000000009C3100009C31
      00009C3100009C3100000000000000000000000000009C9C9C009C9C9C009C9C
      9C009C9C9C0000000000000000000000000000000000000000009C9C9C009C9C
      9C009C9C9C009C9C9C0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009C3100009C31000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009C9C9C009C9C9C0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009C31
      0000CE630000CE6300009C310000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C00CECECE00CECECE009C9C9C00000000000000000000000000000000000000
      000000000000000000000000000000000000000000009C3100009C3100009C31
      00009C3100009C3100009C3100009C3100009C3100009C3100009C3100009C31
      00009C3100009C3100000000000000000000000000009C9C9C009C9C9C009C9C
      9C009C9C9C009C9C9C009C9C9C009C9C9C009C9C9C009C9C9C009C9C9C009C9C
      9C009C9C9C009C9C9C00000000000000000000000000000000009C310000CE63
      0000CE630000CE630000CE6300009C3100000000000000000000000000000000
      00000000000000000000000000000000000000000000000000009C9C9C00CECE
      CE00CECECE00CECECE00CECECE009C9C9C000000000000000000000000000000
      000000000000000000000000000000000000000000009C310000CE630000CE63
      0000CE630000CE630000CE630000CE630000CE630000CE630000CE630000CE63
      0000CE6300009C3100000000000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE009C9C9C000000000000000000000000009C310000CE630000CE63
      0000CE630000CE630000CE630000CE6300009C31000000000000000000000000
      000000000000000000000000000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE009C9C9C0000000000000000000000
      00000000000000000000000000000000000000000000000000009C310000CE63
      0000CE630000CE630000CE630000CE630000CE630000CE630000CE630000CE63
      00009C31000000000000000000000000000000000000000000009C9C9C00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE009C9C9C00000000000000000000000000000000009C310000CE630000CE63
      00009C3100009C310000CE630000CE630000CE6300009C310000000000000000
      000000000000000000000000000000000000000000009C9C9C00CECECE00CECE
      CE009C9C9C009C9C9C00CECECE00CECECE00CECECE009C9C9C00000000000000
      0000000000000000000000000000000000000000000000000000000000009C31
      0000CE630000CE630000CE630000CE630000CE630000CE630000CE6300009C31
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE009C9C
      9C0000000000000000000000000000000000000000009C310000CE6300009C31
      000000000000000000009C310000CE630000CE630000CE6300009C3100000000
      000000000000000000000000000000000000000000009C9C9C00CECECE009C9C
      9C0000000000000000009C9C9C00CECECE00CECECE00CECECE009C9C9C000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009C310000CE630000CE630000CE630000CE630000CE6300009C3100000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009C9C9C00CECECE00CECECE00CECECE00CECECE00CECECE009C9C9C000000
      000000000000000000000000000000000000000000009C3100009C3100000000
      00000000000000000000000000009C310000CE630000CE630000CE6300009C31
      000000000000000000000000000000000000000000009C9C9C009C9C9C000000
      00000000000000000000000000009C9C9C00CECECE00CECECE00CECECE009C9C
      9C00000000000000000000000000000000000000000000000000000000000000
      0000000000009C310000CE630000CE630000CE6300009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C9C9C00CECECE00CECECE00CECECE009C9C9C00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009C310000CE630000CE630000CE63
      00009C3100000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009C9C9C00CECECE00CECECE00CECE
      CE009C9C9C000000000000000000000000000000000000000000000000000000
      000000000000000000009C310000CE6300009C31000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C9C9C00CECECE009C9C9C0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000009C310000CE630000CE63
      0000CE6300009C31000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE009C9C9C0000000000000000000000000000000000000000000000
      00000000000000000000000000009C3100000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000009C9C9C000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000009C310000CE63
      0000CE6300009C31000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000009C9C9C00CECE
      CE00CECECE009C9C9C0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009C31
      0000CE6300009C31000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C00CECECE009C9C9C0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009C3100009C31000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009C9C9C009C9C9C0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C3100009C3100009C3100009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C9C9C009C9C9C009C9C9C009C9C9C00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C310000CE630000CE6300009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C9C9C00CECECE00CECECE009C9C9C00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C310000CE630000CE6300009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C9C9C00CECECE00CECECE009C9C9C00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C310000CE630000CE6300009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C9C9C00CECECE00CECECE009C9C9C00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000009C3100009C31
      00009C3100009C3100009C310000CE630000CE6300009C3100009C3100009C31
      00009C3100009C310000000000000000000000000000000000009C9C9C009C9C
      9C009C9C9C009C9C9C009C9C9C00CECECE00CECECE009C9C9C009C9C9C009C9C
      9C009C9C9C009C9C9C00000000000000000000000000000000009C3100009C31
      00009C3100009C3100009C3100009C3100009C3100009C3100009C3100009C31
      00009C3100009C310000000000000000000000000000000000009C9C9C009C9C
      9C009C9C9C009C9C9C009C9C9C009C9C9C009C9C9C009C9C9C009C9C9C009C9C
      9C009C9C9C009C9C9C00000000000000000000000000000000009C310000CE63
      0000CE630000CE630000CE630000CE630000CE630000CE630000CE630000CE63
      0000CE6300009C310000000000000000000000000000000000009C9C9C00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE009C9C9C00000000000000000000000000000000009C310000CE63
      0000CE630000CE630000CE630000CE630000CE630000CE630000CE630000CE63
      0000CE6300009C310000000000000000000000000000000000009C9C9C00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE009C9C9C00000000000000000000000000000000009C310000CE63
      0000CE630000CE630000CE630000CE630000CE630000CE630000CE630000CE63
      0000CE6300009C310000000000000000000000000000000000009C9C9C00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE009C9C9C00000000000000000000000000000000009C310000CE63
      0000CE630000CE630000CE630000CE630000CE630000CE630000CE630000CE63
      0000CE6300009C310000000000000000000000000000000000009C9C9C00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE009C9C9C00000000000000000000000000000000009C3100009C31
      00009C3100009C3100009C310000CE630000CE6300009C3100009C3100009C31
      00009C3100009C310000000000000000000000000000000000009C9C9C009C9C
      9C009C9C9C009C9C9C009C9C9C00CECECE00CECECE009C9C9C009C9C9C009C9C
      9C009C9C9C009C9C9C00000000000000000000000000000000009C3100009C31
      00009C3100009C3100009C3100009C3100009C3100009C3100009C3100009C31
      00009C3100009C310000000000000000000000000000000000009C9C9C009C9C
      9C009C9C9C009C9C9C009C9C9C009C9C9C009C9C9C009C9C9C009C9C9C009C9C
      9C009C9C9C009C9C9C0000000000000000000000000000000000000000000000
      000000000000000000009C310000CE630000CE6300009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C9C9C00CECECE00CECECE009C9C9C00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C310000CE630000CE6300009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C9C9C00CECECE00CECECE009C9C9C00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C310000CE630000CE6300009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C9C9C00CECECE00CECECE009C9C9C00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C3100009C3100009C3100009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C9C9C009C9C9C009C9C9C009C9C9C00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C3100009C310000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C9C9C009C9C9C00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009C31
      00009C31000000000000000000009C3100009C31000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C009C9C9C0000000000000000009C9C9C009C9C9C0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C310000CE6300009C3100000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C9C9C00CECECE009C9C9C000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009C31
      0000CE6300009C310000000000009C310000CE6300009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C00CECECE009C9C9C00000000009C9C9C00CECECE009C9C9C00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C310000CE630000CE6300009C31000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C9C9C00CECECE00CECECE009C9C9C0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009C31
      0000CE630000CE6300009C3100009C310000CE630000CE6300009C3100000000
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C00CECECE00CECECE009C9C9C009C9C9C00CECECE00CECECE009C9C9C000000
      0000000000000000000000000000000000000000000000000000000000009C31
      00009C3100009C310000CE630000CE630000CE6300009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C009C9C9C009C9C9C00CECECE00CECECE00CECECE009C9C9C00000000000000
      000000000000000000000000000000000000000000009C3100009C3100009C31
      0000CE630000CE630000CE6300009C310000CE630000CE630000CE6300009C31
      000000000000000000000000000000000000000000009C9C9C009C9C9C009C9C
      9C00CECECE00CECECE00CECECE009C9C9C00CECECE00CECECE00CECECE009C9C
      9C00000000000000000000000000000000000000000000000000000000009C31
      0000CE630000CE630000CE630000CE630000CE630000CE6300009C3100000000
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE009C9C9C000000
      000000000000000000000000000000000000000000009C310000CE630000CE63
      0000CE630000CE630000CE630000CE6300009C310000CE630000CE630000CE63
      00009C310000000000000000000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE009C9C9C00CECECE00CECECE00CECE
      CE009C9C9C000000000000000000000000000000000000000000000000009C31
      0000CE630000CE630000CE630000CE630000CE630000CE630000CE6300009C31
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE009C9C
      9C0000000000000000000000000000000000000000009C310000CE630000CE63
      0000CE630000CE630000CE630000CE630000CE6300009C310000CE630000CE63
      0000CE6300009C3100000000000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE009C9C9C00CECECE00CECE
      CE00CECECE009C9C9C0000000000000000000000000000000000000000009C31
      0000CE630000CE630000CE630000CE630000CE630000CE630000CE630000CE63
      00009C3100000000000000000000000000000000000000000000000000009C9C
      9C00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE009C9C9C00000000000000000000000000000000009C310000CE630000CE63
      0000CE630000CE630000CE630000CE630000CE630000CE6300009C310000CE63
      0000CE630000CE6300009C31000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE009C9C9C00CECE
      CE00CECECE00CECECE009C9C9C00000000000000000000000000000000009C31
      0000CE630000CE630000CE630000CE630000CE630000CE630000CE6300009C31
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE009C9C
      9C0000000000000000000000000000000000000000009C310000CE630000CE63
      0000CE630000CE630000CE630000CE630000CE6300009C310000CE630000CE63
      0000CE6300009C3100000000000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE009C9C9C00CECECE00CECE
      CE00CECECE009C9C9C0000000000000000000000000000000000000000009C31
      0000CE630000CE630000CE630000CE630000CE630000CE6300009C3100000000
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE009C9C9C000000
      000000000000000000000000000000000000000000009C310000CE630000CE63
      0000CE630000CE630000CE630000CE6300009C310000CE630000CE630000CE63
      00009C310000000000000000000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE009C9C9C00CECECE00CECECE00CECE
      CE009C9C9C000000000000000000000000000000000000000000000000009C31
      00009C3100009C310000CE630000CE630000CE6300009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C009C9C9C009C9C9C00CECECE00CECECE00CECECE009C9C9C00000000000000
      000000000000000000000000000000000000000000009C3100009C3100009C31
      0000CE630000CE630000CE6300009C310000CE630000CE630000CE6300009C31
      000000000000000000000000000000000000000000009C9C9C009C9C9C009C9C
      9C00CECECE00CECECE00CECECE009C9C9C00CECECE00CECECE00CECECE009C9C
      9C00000000000000000000000000000000000000000000000000000000000000
      0000000000009C310000CE630000CE6300009C31000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C9C9C00CECECE00CECECE009C9C9C0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009C31
      0000CE630000CE6300009C3100009C310000CE630000CE6300009C3100000000
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C00CECECE00CECECE009C9C9C009C9C9C00CECECE00CECECE009C9C9C000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C310000CE6300009C3100000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C9C9C00CECECE009C9C9C000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009C31
      0000CE6300009C310000000000009C310000CE6300009C310000000000000000
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C00CECECE009C9C9C00000000009C9C9C00CECECE009C9C9C00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C3100009C310000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C9C9C009C9C9C00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009C31
      00009C31000000000000000000009C3100009C31000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009C9C
      9C009C9C9C0000000000000000009C9C9C009C9C9C0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000009C3100009C31000000000000000000009C31
      00009C3100000000000000000000000000000000000000000000000000000000
      00000000000000000000000000009C9C9C009C9C9C0000000000000000009C9C
      9C009C9C9C000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000009C3100009C3100000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000009C9C9C009C9C9C000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C310000CE6300009C310000000000009C310000CE63
      00009C3100000000000000000000000000000000000000000000000000000000
      000000000000000000009C9C9C00CECECE009C9C9C00000000009C9C9C00CECE
      CE009C9C9C000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009C310000CE6300009C3100000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009C9C9C00CECECE009C9C9C000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C310000CE630000CE6300009C3100009C310000CE630000CE63
      00009C3100000000000000000000000000000000000000000000000000000000
      0000000000009C9C9C00CECECE00CECECE009C9C9C009C9C9C00CECECE00CECE
      CE009C9C9C000000000000000000000000000000000000000000000000000000
      00000000000000000000000000009C310000CE630000CE6300009C3100000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000009C9C9C00CECECE00CECECE009C9C9C000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009C310000CE630000CE630000CE6300009C310000CE630000CE630000CE63
      00009C3100009C3100009C310000000000000000000000000000000000000000
      00009C9C9C00CECECE00CECECE00CECECE009C9C9C00CECECE00CECECE00CECE
      CE009C9C9C009C9C9C009C9C9C00000000000000000000000000000000000000
      000000000000000000009C310000CE630000CE630000CE6300009C3100009C31
      00009C3100000000000000000000000000000000000000000000000000000000
      000000000000000000009C9C9C00CECECE00CECECE00CECECE009C9C9C009C9C
      9C009C9C9C000000000000000000000000000000000000000000000000009C31
      0000CE630000CE630000CE6300009C310000CE630000CE630000CE630000CE63
      0000CE630000CE6300009C310000000000000000000000000000000000009C9C
      9C00CECECE00CECECE00CECECE009C9C9C00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE009C9C9C00000000000000000000000000000000000000
      0000000000009C310000CE630000CE630000CE630000CE630000CE630000CE63
      00009C3100000000000000000000000000000000000000000000000000000000
      0000000000009C9C9C00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE009C9C9C0000000000000000000000000000000000000000009C310000CE63
      0000CE630000CE6300009C310000CE630000CE630000CE630000CE630000CE63
      0000CE630000CE6300009C3100000000000000000000000000009C9C9C00CECE
      CE00CECECE00CECECE009C9C9C00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE009C9C9C00000000000000000000000000000000000000
      00009C310000CE630000CE630000CE630000CE630000CE630000CE630000CE63
      00009C3100000000000000000000000000000000000000000000000000000000
      00009C9C9C00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE009C9C9C00000000000000000000000000000000009C310000CE630000CE63
      0000CE6300009C310000CE630000CE630000CE630000CE630000CE630000CE63
      0000CE630000CE6300009C31000000000000000000009C9C9C00CECECE00CECE
      CE00CECECE009C9C9C00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE009C9C9C00000000000000000000000000000000009C31
      0000CE630000CE630000CE630000CE630000CE630000CE630000CE630000CE63
      00009C3100000000000000000000000000000000000000000000000000009C9C
      9C00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE009C9C9C0000000000000000000000000000000000000000009C310000CE63
      0000CE630000CE6300009C310000CE630000CE630000CE630000CE630000CE63
      0000CE630000CE6300009C3100000000000000000000000000009C9C9C00CECE
      CE00CECECE00CECECE009C9C9C00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE009C9C9C00000000000000000000000000000000000000
      00009C310000CE630000CE630000CE630000CE630000CE630000CE630000CE63
      00009C3100000000000000000000000000000000000000000000000000000000
      00009C9C9C00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE009C9C9C000000000000000000000000000000000000000000000000009C31
      0000CE630000CE630000CE6300009C310000CE630000CE630000CE630000CE63
      0000CE630000CE6300009C310000000000000000000000000000000000009C9C
      9C00CECECE00CECECE00CECECE009C9C9C00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE009C9C9C00000000000000000000000000000000000000
      0000000000009C310000CE630000CE630000CE630000CE630000CE630000CE63
      00009C3100000000000000000000000000000000000000000000000000000000
      0000000000009C9C9C00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE009C9C9C000000000000000000000000000000000000000000000000000000
      00009C310000CE630000CE630000CE6300009C310000CE630000CE630000CE63
      00009C3100009C3100009C310000000000000000000000000000000000000000
      00009C9C9C00CECECE00CECECE00CECECE009C9C9C00CECECE00CECECE00CECE
      CE009C9C9C009C9C9C009C9C9C00000000000000000000000000000000000000
      000000000000000000009C310000CE630000CE630000CE6300009C3100009C31
      00009C3100000000000000000000000000000000000000000000000000000000
      000000000000000000009C9C9C00CECECE00CECECE00CECECE009C9C9C009C9C
      9C009C9C9C000000000000000000000000000000000000000000000000000000
      0000000000009C310000CE630000CE6300009C3100009C310000CE630000CE63
      00009C3100000000000000000000000000000000000000000000000000000000
      0000000000009C9C9C00CECECE00CECECE009C9C9C009C9C9C00CECECE00CECE
      CE009C9C9C000000000000000000000000000000000000000000000000000000
      00000000000000000000000000009C310000CE630000CE6300009C3100000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000009C9C9C00CECECE00CECECE009C9C9C000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000009C310000CE6300009C310000000000009C310000CE63
      00009C3100000000000000000000000000000000000000000000000000000000
      000000000000000000009C9C9C00CECECE009C9C9C00000000009C9C9C00CECE
      CE009C9C9C000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009C310000CE6300009C3100000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009C9C9C00CECECE009C9C9C000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000009C3100009C31000000000000000000009C31
      00009C3100000000000000000000000000000000000000000000000000000000
      00000000000000000000000000009C9C9C009C9C9C0000000000000000009C9C
      9C009C9C9C000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000009C3100009C3100000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000009C9C9C009C9C9C000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000600000000100010000000000000300000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFF0FFF0FF87C387C3E0FFE0FF83838383C0FFC0FFC107C10783018301
      E00FE00F87018701F01FF01F8F818F81F83FF83F87818781F01FF01F82018201
      E00FE00FC001C001C107C107E039E03983838383F07FF07F87C387C3FFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFF3FFF3FFFFFFFFFFE1FFE1FF80038003C0FFC0FF80038003807F807F
      C007C007803F803FE00FE00F8C1F8C1FF01FF01F9E0F9E0FF83FF83FFF07FF07
      FC7FFC7FFF83FF83FEFFFEFFFFC3FFC3FFFFFFFFFFE3FFE3FFFFFFFFFFF3FFF3
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FC3FFC3FFFFFFFFFFC3FFC3FFFFFFFFFFC3FFC3FFFFFFFFFFC3FFC3FFFFFFFFF
      C003C003C003C003C003C003C003C003C003C003C003C003C003C003C003C003
      FC3FFC3FFFFFFFFFFC3FFC3FFFFFFFFFFC3FFC3FFFFFFFFFFC3FFC3FFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      F9FFF9FFE67FE67FF8FFF8FFE23FE23FF87FF87FE01FE01FE03FE03F800F800F
      E01FE01F80078007E00FE00F80038003E007E00780018001E00FE00F80038003
      E01FE01F80078007E03FE03F800F800FF87FF87FE01FE01FF8FFF8FFE23FE23F
      F9FFF9FFE67FE67FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FE67FE67FF9FFF9FFC47FC47FF1FFF1FF807F807FE1FFE1FF001F001FC07FC07
      E001E001F807F807C001C001F007F00780018001E007E007C001C001F007F007
      E001E001F807F807F001F001FC07FC07F807F807FE1FFE1FFC47FC47FF1FFF1F
      FE67FE67FF9FFF9FFFFFFFFFFFFFFFFF00000000000000000000000000000000
      000000000000}
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 500
    OnTimer = Timer1Timer
    Left = 656
    Top = 120
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 500
    OnTimer = Timer2Timer
    Left = 648
    Top = 192
  end
end
