unit xDesktop;

interface

uses Windows, Messages, SysUtils, Forms, Controls, Graphics, ShellAPI, Registry;

function GetDesktopDefView: HWND;
function GetDesktopListView: HWND;
function GetActiveDesktopWindow: HWND;

procedure RebuildIconCache;

function IsScreenSaverRunning(KillIt: Boolean): Boolean;


implementation

uses xStrings, xFiles;

function GetDesktopDefView: HWND;
begin
  Result := GetWindow(FindWindow(PChar('ProgMan'), nil), GW_CHILD);
end;

function GetDesktopListView: HWND;
begin
  Result := GetWindow(GetWindow(FindWindow(PChar('ProgMan'), nil), GW_CHILD), GW_CHILD);
end;

function GetActiveDesktopWindow: HWND;
var
  Buf: array[0..255] of Char;
begin
  Result := GetDesktopListView;
  repeat
    Result := GetWindow(Result, GW_HWNDNEXT);
    if Result = 0 then Exit;
    GetClassName(Result, Buf, 256);
  until StrIComp(Buf, 'Internet Explorer_Server') = 0;
end;

procedure RebuildIconCache;
var
  IconW: Integer;
begin
  IconW := GetSystemMetrics(SM_CXICON);
  with TRegIniFile.Create('Control Panel\Desktop') do
    try
      WriteString('WindowMetrics', 'Shell Icon Size', IntToStr(IconW - 1));
      SendMessage(HWND_BROADCAST, WM_WININICHANGE, 0, 0);
      WriteString('WindowMetrics', 'Shell Icon Size', IntToStr(IconW));
      SendMessage(HWND_BROADCAST, WM_WININICHANGE, 0, 0);
    finally
      Free;
    end;
end;

function IsScreenSaverRunning(KillIt: Boolean): Boolean;
var
  hd: HDESK;
  hw: HWND;
  PT: TPoint;
begin
  Result := False;

  if Win32Platform = VER_PLATFORM_WIN32_NT then { Windows NT }
  begin
    // 螢幕保護程式所在的 desktop
    hd := OpenDesktop('Screen-saver', 0, False, 0);
    if hd <> 0 then
    begin
      Result := True; // 正在執行
      CloseDesktop(hd);
    end else
    begin
      // 權限不足
      if GetLastError = ERROR_ACCESS_DENIED then Result := True;
    end;
  end else
  begin { Windows 95/98 or Win32s }
    // 取得螢幕保護程式的視窗 handle
    hw := FindWindow('WindowsScreenSaverClass', nil);
    if hw <> 0 then
    begin
      Result := True; // 正在執行
    end;
  end;

  if Result and KillIt then
  begin
    GetCursorPos(PT); // 取得目前滑鼠指標
    SetCursorPos(PT.X + 20, PT.Y + 20); // 設定滑鼠指標, 偏移位置
  end;
end;

end.

