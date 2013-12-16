unit xRegistry;

interface

uses Windows, SysUtils, Registry;

function GetAssociatedExecutable(FileExt: string; var FileDesc, MIMEType: string): string;
function SetAssociatedExecutable(FileExt, Filetype, FileDesc, MIMEType, ExecutablePath: string): Boolean;

function ReadKeyDefaultValue(REG: TRegistry; const sKey: string): string;
procedure WriteKeyDefaultValue(REG: TRegistry; const sKey, sValue: string);

implementation

uses xStrings;

function GetAssociatedExecutable(FileExt: string; var FileDesc, MIMEType: string): string;
var
  Filetype: string;
  P       : PChar; 
begin
  Result := '';
  
  if FileExt = '' then Exit;
  
  // 確保 FileExt 以逗點開頭, 如 'doc' -> '.doc'
  if FileExt[1] <> '.' then FileExt := '.' + FileExt;
  
  with TRegistry.Create do
    try
      RootKey := HKEY_CLASSES_ROOT;
      if OpenKey(FileExt, False) then
      begin
        Filetype := ReadString('');
        MIMEType := ReadString('Content Type');
        CloseKey;
      end;
      
      if Filetype = '' then Exit;
      
      if OpenKey(Filetype, False) then
      begin
        FileDesc := ReadString('');
        
        if OpenKey('shell\open\command', False) then
        begin
          Result := Trim(ReadString(''));
          
          // Truncate the '%1' token from executable path
          // Ex. 'c:\winword.exe %1' -> 'c:\winword.exe'
          if Length(Result) > 1 then
          begin
            if Result[1] = '"' then
            begin
              P := StrNew(PChar(Result));
              Result := AnsiExtractQuotedStr(P, '"');
            end else if AnsiPos('"', Result) <> 0 then
              Result := TrimRight(Copy(Result, 1, AnsiPos('"', Result) - 1));
          end;
        end;
        CloseKey;
      end;
    finally
      Free;
    end;
end;

// FileType, FileDesc and MIMEType is optional.
function SetAssociatedExecutable(FileExt, Filetype, FileDesc, MIMEType, ExecutablePath: string): Boolean;
begin
  Result := False;
  
  if (FileExt = '') or (ExecutablePath = '') then Exit;
  
  // 確保 FileExt 以逗點開頭, 如 'doc' -> '.doc'
  if FileExt[1] <> '.' then FileExt := '.' + FileExt;
  
  // 若沒有指定 FileType, 自行從副檔名轉換出 FileType, 如 '.doc' -> 'docfile'
  if Filetype = '' then Filetype := Copy(FileExt, 2, Maxint) + 'file';
  
  with TRegistry.Create do
    try
      RootKey := HKEY_CLASSES_ROOT;
      if OpenKey(FileExt, True) then
      begin
        WriteString('', Filetype);
        if MIMEType <> '' then WriteString('Content Type', MIMEType); // Write MIMEType
        CloseKey;
      end else Exit; // fails
      
      if (FileDesc <> '') and OpenKey(Filetype, True) then
      begin
        WriteString('', FileDesc); // 寫入檔案類型敘述
        CloseKey;
      end;
      
      if OpenKey(Filetype + '\DefaultIcon', True) then
      begin
        WriteString('', Trim(ExecutablePath) + ',0');
        CloseKey;
      end;
      
      if OpenKey(Filetype + '\shell\Apply Settings\command', True) then
      begin
        WriteString('', Trim(ExecutablePath) + ' /s "%1"');
        CloseKey;
      end;
      
      if OpenKey(Filetype + '\shell\open\command', True) then
      begin
        // 執行檔路徑後加上 " %1", 如 'c:\winword.exe' -> 'c:\winword.exe "%1"'
        if AnsiPos('%1', ExecutablePath) = 0 then
          ExecutablePath := Trim(ExecutablePath) + ' "%1"';
        
        WriteString('', ExecutablePath); // 寫入執行檔路徑及參數
        Result := True;
        CloseKey;
      end;
    finally
      Free; // always free
    end;
end;

function ReadKeyDefaultValue(REG: TRegistry; const sKey: string): string;
begin
  Result := '';
  with REG do
  begin
    if OpenKey(sKey, False) then
    begin
      Result := ReadString('');
      CloseKey;
    end;
  end;
end;

procedure WriteKeyDefaultValue(REG: TRegistry; const sKey, sValue: string);
begin
  with REG do
  begin
    if OpenKey(sKey, True) then
    begin
      WriteString('', sValue);
      CloseKey;
    end;
  end;
end;


end.

