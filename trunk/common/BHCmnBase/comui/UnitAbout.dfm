object AboutBox: TAboutBox
  Left = 293
  Top = 160
  BorderStyle = bsDialog
  ClientHeight = 186
  ClientWidth = 385
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #23435#20307
  Font.Style = []
  OldCreateOrder = True
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 12
  object Label2: TLabel
    Left = 9
    Top = 82
    Width = 336
    Height = 16
    AutoSize = False
    Font.Charset = GB2312_CHARSET
    Font.Color = clGray
    Font.Height = -16
    Font.Name = #23435#20307
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = True
  end
  object Label1: TLabel
    Left = 8
    Top = 81
    Width = 337
    Height = 16
    AutoSize = False
    Color = clCaptionText
    Font.Charset = GB2312_CHARSET
    Font.Color = clBlack
    Font.Height = -16
    Font.Name = #23435#20307
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    Transparent = True
  end
  object Label3: TLabel
    Left = 11
    Top = 109
    Width = 333
    Height = 13
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label5: TLabel
    Left = 8
    Top = 145
    Width = 160
    Height = 14
    Cursor = crHandPoint
    Caption = 'http://www.BoHongFund.com'
    DragCursor = crHandPoint
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
    OnClick = Label5Click
    OnMouseEnter = Label5MouseEnter
    OnMouseLeave = Label5MouseLeave
  end
  object Bevel1: TBevel
    Left = 8
    Top = 126
    Width = 369
    Height = 7
    Shape = bsBottomLine
  end
  object Label4: TLabel
    Left = 8
    Top = 165
    Width = 258
    Height = 12
    Caption = 'Copyright 2003-2004 BoHong Fund Corporation'
    Font.Charset = GB2312_CHARSET
    Font.Color = clMaroon
    Font.Height = -12
    Font.Name = #23435#20307
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
  object OKButton: TButton
    Left = 301
    Top = 154
    Width = 75
    Height = 22
    Caption = #30830#23450'(&O)'
    Default = True
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #23435#20307
    Font.Style = []
    ModalResult = 1
    ParentFont = False
    TabOrder = 0
  end
end
