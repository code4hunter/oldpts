unit xFiles;

interface

uses SysUtils, Windows, ShellAPI, Forms;

type
  TEnumDirectoryFileProc = procedure (Filename: string; var bContinue: Boolean) of object;
  
function PathWithoutSlash(const Path: string): string;
function PathWithSlash(const Path: string): string;
function RelativePath(BaseDir, FilePath: string): string;

function MyShellExecute(const sAction, sFileName, sPara: string): Boolean;
function Execute(const Command: string; bWaitExecute: Boolean; bShowWindow: Boolean; PI: PProcessInformation): Boolean;

function ExtractFileNameNoExt(Filename: string): string;
function MyGetFileSize(const Filename: string): DWORD;
procedure MyCopyFile(const sSrcFile, sDstFile: string);

function TruncateTrailNumber(var S: string): Integer;
function TruncateTrailIfNotDLL(S: string): string;
function FileExistsAfterTruncate(Filename: string): Boolean;

function TruncateDirSpecifier(const Path: string): string;

function ComparePath(const Path1, Path2: string): Boolean;
function ParentDirectory(Path: string): string;

function SystemDirFile(const Filename: string): string;
function WindowsDirFile(const Filename: string): string;
function SystemDriveFile(const Filename: string): string;

procedure EnumDirectoryFiles(sDir, SMASK: string; Attr: Integer; EnumDirectoryFileProc: TEnumDirectoryFileProc);
procedure CleanDirectory(sDir: string);
procedure CopyDirectory(sDir, tDir: string; bRecursive: Boolean);

function GetUniqueFileName(const Path: string; Filename: string): string;
function GetTemporaryFileName: string;

function GetSystemPath: string;
function GetWindowsPath: string;

function GetRootDir(var sPath: string): string;
function GetLeafDir(var sPath: string): string;

var
  AppDir: string;

implementation

uses xUtils, Filectrl;

function PathWithoutSlash(const Path: string): string;
begin
  if (Length(Path) > 0) and (Path[Length(Path)] = '\') then Result := Copy(Path, 1, Length(Path) - 1)
  else Result := Path;
end;

function PathWithSlash(const Path: string): string;
begin
  Result := Path;
  if (Length(Result) > 0) and (Result[Length(Result)] <> '\') then AppendStr(Result, '\');
end;

function RelativePath(BaseDir, FilePath: string): string;
begin
  Result := FilePath;
  BaseDir := AnsiUpperCaseFileName(PathWithSlash(BaseDir));
  FilePath := AnsiUpperCaseFileName(FilePath);
  if Copy(FilePath, 1, Length(BaseDir)) = BaseDir then
    Delete(Result, 1, Length(BaseDir));
end;

function MyShellExecute(const sAction, sFileName, sPara: string): Boolean;
begin
  Result := ShellExecute(Application.Handle, PChar(sAction), PChar(sFileName), PChar(sPara), PChar(''), SW_SHOW) > 32;
  if not Result then RaiseLastError('ShellExecute');
end;


function Execute(const Command: string; bWaitExecute: Boolean; bShowWindow: Boolean; PI: PProcessInformation): Boolean;
var
  StartupInfo       : TStartupInfo;       
  ProcessInformation: TProcessInformation;
begin
  FillChar(StartupInfo, SizeOf(TStartupInfo), 0);
  with StartupInfo do
  begin
    cb := SizeOf(TStartupInfo);
    dwFlags := STARTF_USESHOWWINDOW;
    if bShowWindow then
      wShowWindow := SW_NORMAL
    else
      wShowWindow := SW_HIDE;
  end;
  
  Result := CreateProcess(nil, PChar(Command),
    nil, nil, True, NORMAL_PRIORITY_CLASS, nil, nil,
    StartupInfo, ProcessInformation);
  
  if not Result then Exit;
  
  if bWaitExecute then
    WaitForSingleObject(ProcessInformation.hProcess, INFINITE);
  
  if Assigned(PI) then
    Move(ProcessInformation, PI^, SizeOf(ProcessInformation));
end;

function ExtractFileNameNoExt(Filename: string): string;
begin
  Result := Copy(Filename, 1, Length(Filename) - Length(ExtractFileExt(Filename)));
end;

function MyGetFileSize(const Filename: string): DWORD;
var
  HFILE: THandle;
begin
  HFILE := CreateFile(PChar(Filename), GENERIC_READ, FILE_SHARE_READ, nil, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if HFILE <> INVALID_HANDLE_VALUE then
  begin
    Result := GetFileSize(HFILE, nil);
    CloseHandle(HFILE);
  end else
    Result := 0;
end;

procedure MyCopyFile(const sSrcFile, sDstFile: string);
begin
  if AnsiCompareFileName(sSrcFile, sDstFile) <> 0 then
    CopyFile(PChar(sSrcFile), PChar(sDstFile), False);
end;


function GetTemporaryFileName: string;
var
  Buf, Buf1: array[0..255] of Char;
begin
  GetTempPath(255, @Buf);
  GetTempFileName(@Buf, 'xpd', 0, @Buf1);
  Result := StrPas(@Buf1);
end;

function TruncateTrailNumber(var S: string): Integer;
var
  I: Integer;
begin
  Result := -1;
  
  I := Pos(',', S);
  if I <> 0 then
  begin
    Result := StrToIntDef(Copy(S, I + 1, Length(S)), - 1);
    Delete(S, I, Length(S));
  end;
end;

function TruncateTrailIfNotDLL(S: string): string;
begin
  Result := S;
  TruncateTrailNumber(S);
  
  if (CompareText(ExtractFileExt(S), '.DLL') <> 0) and
    (CompareText(ExtractFileExt(S), '.ICL') <> 0) and
    (CompareText(ExtractFileExt(S), '.EXE') <> 0) then Result := S;
end;

function FileExistsAfterTruncate(Filename: string): Boolean;
begin
  TruncateTrailNumber(Filename);
  Result := FileExists(Filename);
end;

function TruncateDirSpecifier(const Path: string): string;
var
  I1, I2: Integer;
begin
  Result := Path;
  
  I1 := AnsiPos('%', Path);
  I2 := AnsiPos('%', Copy(Path, I1 + 1, Length(Path)));
  if (I1 = 0) or (I2 = 0) then Exit;

  Result := Copy(Path, I2 + I1 + 1, Length(Path));
end;

function ParentDirectory(Path: string): string;
var
  iLastAntiSlash: Integer;
  
  function CountAntiSlash: Integer;
  var
    I: Integer;
  begin
    Result := 0;
    I := 1;
    repeat
      if IsDBCSLeadByte(Ord(Path[I])) then
        Inc(I, 2)
      else
      begin
        if Path[I] = '\' then
        begin
          iLastAntiSlash := I;
          Inc(Result);
        end;
        Inc(I);
      end;
    until I > Length(Path);
  end;
  
  function UpOneDirectory: string;
  begin
    Result := Copy(Path, 1, iLastAntiSlash); // with slash
  end;
  
begin
  // 'c:\windows\system\' => 'c:\window\'
  // 'f:\' => 'f:\'
  // '\\xshadow\f\fonts' => '\\xshadow\f\'
  // '\\xshadow\f\' => '\\xshadow\f\'
  Path := PathWithoutSlash(Path);
  
  if Length(Path) > 3 then
  begin
    if (Path[1] = '\') and (Path[2] = '\') then // UNC path
    begin
      if CountAntiSlash > 3 then
        Result := UpOneDirectory;
    end else
    begin
      if CountAntiSlash > 1 then
        Result := UpOneDirectory;
    end;
  end else Result := Path;
end;

function SystemDirFile(const Filename: string): string;
var
  Buf: array[0..255] of Char;
begin
  GetSystemDirectory(@Buf, 255);
  Result := PathWithSlash(StrPas(@Buf)) + Filename;
end;

function WindowsDirFile(const Filename: string): string;
var
  Buf: array[0..255] of Char;
begin
  GetWindowsDirectory(@Buf, 255);
  Result := PathWithSlash(StrPas(@Buf)) + Filename;
end;

function SystemDriveFile(const Filename: string): string;
var
  Buf: array[0..255] of Char;
begin
  GetSystemDirectory(@Buf, 255);
  Result := PathWithSlash(ExtractFileDrive(StrPas(@Buf))) + Filename;
end;

function ComparePath(const Path1, Path2: string): Boolean;
begin
  Result := AnsiCompareFileName(PathWithoutSlash(Path1), PathWithoutSlash(Path2)) = 0;
end;

procedure EnumDirectoryFiles(sDir, SMASK: string; Attr: Integer; EnumDirectoryFileProc: TEnumDirectoryFileProc);
var
  SearchRec: TSearchRec;
  Status   : Integer;   
  bContinue: Boolean;   
begin
  sDir := PathWithSlash(sDir);
  
  // traverse child directories
  Status := FindFirst(sDir + '*.*', faDirectory, SearchRec);
  try
    while Status = 0 do
    begin
      if (SearchRec.name <> '.') and (SearchRec.name <> '..') then
        EnumDirectoryFiles(sDir + SearchRec.name, SMASK, Attr, EnumDirectoryFileProc);
      
      Status := FindNext(SearchRec);
    end;
  finally
    SysUtils.FindClose(SearchRec);
  end;
  
  // exam each valid file and invoke the callback func
  Status := FindFirst(sDir + SMASK, faAnyFile, SearchRec);
  try
    while Status = 0 do
    begin
      if (SearchRec.Attr and Attr <> 0) and (FileExists(sDir + SearchRec.name) or DirectoryExists(sDir + SearchRec.name)) and
        not ((SearchRec.Attr and faDirectory <> 0) and ((SearchRec.name = '.') or (SearchRec.name = '..'))) then
      begin
        bContinue := True;
        EnumDirectoryFileProc(sDir + SearchRec.name, bContinue);
        if not bContinue then Break;
      end;
      
      Status := FindNext(SearchRec);
    end;
  finally
    SysUtils.FindClose(SearchRec);
  end;
end;

type
  TMyClass = class
  private
    procedure CleanDirectoryProc(sFileName: string; var bContinue: Boolean);
  end;
  
procedure TMyClass.CleanDirectoryProc(sFileName: string; var bContinue: Boolean);
var
  Attr: Integer;
begin
  Attr := FileGetAttr(sFileName);
  Attr := (not faReadOnly) and Attr; // Turn off ReadOnly attribute
  Attr := (not faHidden) and Attr; // Turn off Hidden attribute
  FileSetAttr(sFileName, Attr);

  if Attr and faDirectory <> 0 then
    RMDir(sFileName)
  else
    SysUtils.DeleteFile(sFileName);
end;

procedure CleanDirectory(sDir: string);
begin
  with TMyClass.Create do
    try
      EnumDirectoryFiles(sDir, '*.*', faAnyFile, CleanDirectoryProc);
    finally
      Free;
    end;
  RMDir(sDir);
end;

procedure CopyDirectory(sDir, tDir: string; bRecursive: Boolean);
var
  SearchRec: TSearchRec;
  Status   : Integer;   
begin
  sDir := PathWithSlash(sDir);
  tDir := PathWithSlash(tDir);

  Status := FindFirst(sDir + '*.*', faAnyFile, SearchRec);
  try
    while Status = 0 do
    begin
      if bRecursive and (SearchRec.Attr and faDirectory = faDirectory) then
      begin
        if (SearchRec.name <> '.') and (SearchRec.name <> '..') then
          CopyDirectory(sDir + SearchRec.name, tDir, bRecursive);
      end else CopyFile(PChar(sDir + SearchRec.name), PChar(tDir + SearchRec.name), False);

      Status := FindNext(SearchRec);
    end;
  finally
    SysUtils.FindClose(SearchRec);
  end;
end;

function GetUniqueFileName(const Path: string; Filename: string): string;
var
  I   : Integer;
  sExt: string;
begin
  Result := Filename;

  sExt := ExtractFileExt(Filename);
  Filename := ExtractFileNameNoExt(Filename);

  I := 1;
  repeat
    if not FileExists(PathWithSlash(Path) + Result) then Break;

    Result := Filename + IntToStr(I) + sExt;
    Inc(I);
  until False;

  Result := PathWithSlash(Path) + Filename + sExt;
end;


function GetSystemPath: string;
var
  Buf: array[0..255] of Char;
begin
  GetSystemDirectory(@Buf, 255);
  Result := PathWithSlash(StrPas(@Buf));
end;

function GetWindowsPath: string;
var
  Buf: array[0..255] of Char;
begin
  GetWindowsDirectory(@Buf, 255);
  Result := PathWithSlash(StrPas(@Buf));
end;

function GetRootDir(var sPath: string): string;
var
  I: Integer;
begin
  I := AnsiPos('\', sPath);
  if I <> 0 then
    Result := Copy(sPath, 1, I)
  else
    Result := sPath;

  Delete(sPath, 1, Length(Result));
  Result := PathWithoutSlash(Result);
end;

function GetLeafDir(var sPath: string): string;
begin
  sPath := PathWithoutSlash(sPath);
  Result := ExtractFileName(sPath);
  sPath := ExtractFilePath(sPath);
end;

initialization
  GetDir(0, AppDir);
  AppDir := PathWithSlash(AppDir);
end.

