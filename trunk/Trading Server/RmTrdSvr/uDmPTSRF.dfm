object DataModule1: TDataModule1
  OldCreateOrder = False
  OnDestroy = DataModuleDestroy
  Height = 150
  Width = 215
  object cn: TADOConnection
    CommandTimeout = 40
    LoginPrompt = False
    Provider = 'SQLOLEDB'
    Left = 40
    Top = 16
  end
end
