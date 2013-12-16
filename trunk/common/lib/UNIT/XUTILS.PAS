unit xUtils;

interface

uses Windows, Messages, Classes, SysUtils, Forms, Controls;

procedure MsgBox(const Msg: string);
procedure ErrBox(const Msg: string);
function YesNoBox(const Msg: string): Boolean;
function YesNoCancelBox(const Msg: string): Integer;

procedure ShowLastError(const Msg: string = 'API Error');
procedure RaiseLastError(const Msg: string = 'API Error');

procedure FreeStringsObjects(SL: TStrings);

implementation

procedure MsgBox(const Msg: string);
begin
  Application.MessageBox(PChar(Msg), PChar(Application.Title), MB_ICONINFORMATION);
end;

procedure ErrBox(const Msg: string);
begin
  Application.MessageBox(PChar(Msg), PChar(Application.Title), MB_ICONERROR);
end;

function YesNoBox(const Msg: string): Boolean;
begin
  Result := Application.MessageBox(PChar(Msg), PChar(Application.Title), MB_ICONQUESTION or
    MB_YESNO or MB_DEFBUTTON1) = IDYES;
end;

function YesNoCancelBox(const Msg: string): Integer;
begin
  Result := Application.MessageBox(PChar(Msg),
    PChar(Application.Title), MB_ICONQUESTION or MB_YESNOCANCEL or MB_DEFBUTTON1)
end;

function GetLastErrorStr: string;
var
  Buf: PChar;
begin
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER or FORMAT_MESSAGE_FROM_SYSTEM,
    nil, GetLastError, LANG_USER_DEFAULT, @Buf, 0, nil);
  try
    Result := StrPas(Buf);
  finally
    LocalFree(HLOCAL(Buf));
  end;
end;

procedure ShowLastError(const Msg: string = 'API Error');
begin
  MsgBox(Msg + ': ' + GetLastErrorStr);
end;

procedure RaiseLastError(const Msg: string = 'API Error');
begin
  raise Exception.Create(Msg + ': ' + GetLastErrorStr);
end;

procedure FreeStringsObjects(SL: TStrings);
var
  I: Integer;
begin
  for I := 0 to SL.count - 1 do
    if assigned(SL.objects[I]) then
    begin
      Dispose(pointer(SL.objects[I]));
      SL.objects[I] := nil;
    end;
end;

end.

