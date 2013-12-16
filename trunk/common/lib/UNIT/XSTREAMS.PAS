unit xStreams;

interface

uses Windows, SysUtils, Classes, Forms, TypInfo;

procedure SavePropertyToStream(Stream: TStream; Instance: TPersistent; PropName: string);
procedure LoadPropertyFromStream(Stream: TStream; Instance: TPersistent);

procedure ReadFormAsText(AExeName, AClassName: string; Strings: TStrings);
procedure WriteFormAsBinary(AExeName, AClassName: string; Strings: TStrings);

function VisualizeForm(Strings: TStrings): TForm;
procedure TextizeForm(AForm: TForm; Strings: TStrings);

implementation

type
  TMyWriter = class(TWriter)
  public
    procedure WriteProperty(Instance: TPersistent; PropInfo: Pointer);
  end;

  TMyReader = class(TReader)
  public
    procedure ReadProperty(Instance: TPersistent);
  end;

  { TMyWriter }

procedure TMyWriter.WriteProperty(Instance: TPersistent; PropInfo: Pointer);
begin
  inherited WriteProperty(Instance, PropInfo);
end;

  { TMyReader }

procedure TMyReader.ReadProperty(Instance: TPersistent);
begin
  inherited ReadProperty(Instance);
end;

procedure SavePropertyToStream(Stream: TStream; Instance: TPersistent; PropName: string);
begin
  with TMyWriter.Create(Stream, 4096) do
    try
      WriteListBegin;
      WriteProperty(Instance, GetPropInfo(Instance.ClassInfo, PropName));
      WriteListEnd;
    finally
      Free;
    end;
end;

procedure LoadPropertyFromStream(Stream: TStream; Instance: TPersistent);
begin
  with TMyReader.Create(Stream, 4096) do
    try
      ReadListBegin;
      while not EndOfList do ReadProperty(Instance);
      ReadListEnd;
    finally
      Free;
    end;
end;

// 將 form 以 text 形式從 executable 的 resource table 讀出
procedure ReadFormAsText(AExeName, AClassName: string; Strings: TStrings);
var
  hLib: THandle;        
  RS  : TResourceStream;
  ms  : TMemoryStream;  
begin
  hLib := LoadLibrary(PChar(AExeName));
  try
    RS := TResourceStream.Create(hLib, AClassName, RT_RCDATA);
    ms := TMemoryStream.Create;
    try
      ObjectBinaryToText(RS, ms);
      ms.Position := 0;
      Strings.LoadFromStream(ms);
    finally
      RS.Free;
      ms.Free;
    end;
  finally
    FreeLibrary(hLib);
  end;
end;

function CheckFormTextValidity(Strings: TStrings): Boolean;
var
  ms1, ms2: TMemoryStream;
begin
  Result := False;
  
  ms1 := TMemoryStream.Create;
  ms2 := TMemoryStream.Create;
  try
    Strings.SaveToStream(ms1);
    ms1.Position := 0;
    try
      ObjectTextToBinary(ms1, ms2);
      Result := True;
    except
    end;
  finally
    ms1.Free;
    ms2.Free;
  end;
end;

// 將 form 以 text 形式寫入 executable 的 resource table
procedure WriteFormAsBinary(AExeName, AClassName: string; Strings: TStrings);
var
  hLib: THandle;        
  RS  : TResourceStream;
  ms  : TMemoryStream;  
begin
  CheckFormTextValidity(Strings);
  
  hLib := LoadLibrary(PChar(AExeName));
  try
    RS := TResourceStream.Create(hLib, AClassName, RT_RCDATA);
    ms := TMemoryStream.Create;
    try
      Strings.SaveToStream(ms);
      ms.Position := 0;
      ObjectTextToBinary(ms, RS);
    finally
      RS.Free;
      ms.Free;
    end;
  finally
    FreeLibrary(hLib);
  end;
end;

function VisualizeForm(Strings: TStrings): TForm;
var
  ms1, ms2: TMemoryStream;
begin
  ms1 := TMemoryStream.Create;
  ms2 := TMemoryStream.Create;
  try
    Strings.SaveToStream(ms1);
    ms1.Position := 0;
    ObjectTextToBinary(ms1, ms2);
    ms2.Position := 0;
    TComponent(Result) := ms2.ReadComponent(nil);
  finally
    ms1.Free;
    ms2.Free;
  end;
end;

procedure TextizeForm(AForm: TForm; Strings: TStrings);
var
  ms1, ms2: TMemoryStream;
begin
  ms1 := TMemoryStream.Create;
  ms2 := TMemoryStream.Create;
  try
    ms1.WriteComponent(AForm);
    ms1.Position := 0;
    ObjectBinaryToText(ms1, ms2);
    ms2.Position := 0;
    Strings.LoadFromStream(ms2);
  finally
    ms1.Free;
    ms2.Free;
  end;
end;

end.

