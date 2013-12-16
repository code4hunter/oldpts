unit xKernel;

interface

uses Windows, SysUtils, TlHelp32, Psapi;

type
  TxEnumProcesses_ToolHelp = function (ProcessEntry: TProcessEntry32; pContext: Pointer): Boolean;
  TxEnumProcesses_Psapi = function (ProcessID: DWORD; pContext: Pointer): Boolean;

procedure DebugStr(S: string);
procedure DebugStrFmt(const Format: string; const Args: array of const);

function GetWindowModuleFileName(Wnd: HWND): string;

implementation

uses xStrings, xUtils;

procedure DebugStr(S: string);
begin
  if not IsContainCRLF(S) then S := S + #13#10;
  OutputDebugString(PChar(S));
end;

procedure DebugStrFmt(const Format: string; const Args: array of const);
begin
  DebugStr(SysUtils.Format(Format, Args));
end;

procedure xEnumProcesses_ToolHelp(EnumProc: TxEnumProcesses_ToolHelp; pContext: Pointer);
var
  hSnapshot   : THandle;        
  bResult     : Boolean;        
  ProcessEntry: TProcessEntry32;
begin
  if not Assigned(EnumProc) then Exit;
  
  hSnapshot := CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if hSnapshot = 0 then
    RaiseLastError('CreateToolhelp32Snapshot');;
  
  ProcessEntry.dwSize := sizeof(ProcessEntry);
  bResult := Process32First(hSnapshot, ProcessEntry);
  while bResult do
  begin
    if not EnumProc(ProcessEntry, pContext) then break;
    
    ProcessEntry.dwSize := sizeof(ProcessEntry);
    bResult := Process32Next(hSnapshot, ProcessEntry);
  end;
  
  CloseHandle(hSnapshot);
end;

procedure xEnumProcesses_Psapi(EnumProc: TxEnumProcesses_Psapi; pContext: Pointer);
var
  cbNeeded: DWORD;  
  P, PP   : PDWORD; 
  I       : Integer;
begin
  if not Assigned(EnumProc) then Exit;
  
  EnumProcesses(nil, 0, cbNeeded);
  GetMem(P, cbNeeded);
  try
    if not EnumProcesses(P, cbNeeded, cbNeeded) then
      RaiseLastError('EnumProcesses');
    
    PP := P;
    for I := 0 to cbNeeded div sizeof(DWORD) - 1 do
    begin
      if not EnumProc(PP^, pContext) then break;
      Inc(PP);
    end;
  finally
    FreeMem(P);
  end;
end;

var
  WindowModuleFileName: string;
  
function xEnumProcesses_ToolHelp_GetWindowModuleFileName_Proc(ProcessEntry: TProcessEntry32; pContext: Pointer): Boolean;
begin
  Result := ProcessEntry.th32ProcessID <> DWORD(pContext);
  if not Result then WindowModuleFileName := ProcessEntry.szExeFile;
end;

function GetWindowModuleFileName(Wnd: HWND): string;
var
  Buf              : array[0..255] of char;
  ProcessID        : DWORD;                
  hProcess, hModule: THandle;              
  cbNeeded         : DWORD;                
begin
  GetWindowThreadProcessId(Wnd, @ProcessID);
  if Win32Platform = VER_PLATFORM_WIN32_WINDOWS then
  begin
    xEnumProcesses_ToolHelp(xEnumProcesses_ToolHelp_GetWindowModuleFileName_Proc, Pointer(ProcessID));
    Result := WindowModuleFileName;
  end else
  begin
    hProcess := OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID);
    hModule := 0;
    // 取得第一個 module handle
    EnumProcessModules(hProcess, @hModule, 4, cbNeeded);
    GetModuleFileNameEx(hProcess, hModule, Buf, sizeof(Buf));
    Result := strpas(Buf);
    CloseHandle(hProcess);
  end;
end;

end.

