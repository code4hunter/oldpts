object dmPTSDB: TdmPTSDB
  OldCreateOrder = False
  OnDestroy = DataModuleDestroy
  Height = 150
  Width = 215
  object cn: TADOConnection
    Provider = 'SQLOLEDB'
    Left = 40
    Top = 24
  end
end
