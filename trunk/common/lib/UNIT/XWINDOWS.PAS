unit xWindows;

interface

uses Windows, Sysutils, Controls, Forms;

const
  DEFAULT_FOCUSRECT_WIDTH = 3;
  
function FindControl(Handle: HWND; ProcessID: DWORD = 0): TWinControl;
function IsDelphiHandle(Handle: HWND; ProcessID: DWORD = 0): Boolean;

function FindTopmostWindow(ParentWnd: HWND; Pt: TPoint): HWND;

procedure MyDrawFocusRect(DC: HDC; R: TRect; Width: Integer = DEFAULT_FOCUSRECT_WIDTH);
procedure DrawWindowFocusRect(Wnd: HWND; Width: Integer = DEFAULT_FOCUSRECT_WIDTH);
procedure DrawControlFocusRect(Control: TControl; Width: Integer = DEFAULT_FOCUSRECT_WIDTH);

implementation

uses xKernel;

var
  WindowAtom : TAtom;               
  ControlAtom: TAtom;               
  
  AtomText   : array[0..31] of Char;
  
  { Find a TWinControl given a window handle }
  
function FindControl(Handle: HWND; ProcessID: DWORD = 0): TWinControl;
begin
//  DebugStrFmt('Find Control Handle = %x',[Handle]);
  if Handle <> 0 then
  begin
    if ProcessID = 0 then
      GetWindowThreadProcessId(Handle, @ProcessID);
    WindowAtom := GlobalAddAtom(StrFmt(AtomText, 'Delphi%.8X',[ProcessID]));
    Result := Pointer(GetProp(Handle, MakeIntAtom(WindowAtom)));
//    DebugStrFmt('Find Control PID = %x Result = %p',[ProcessID, Pointer(Result)]);
  end else
    Result := nil;
end;

function IsDelphiHandle(Handle: HWND; ProcessID: DWORD = 0): Boolean;
begin
  Result := FindControl(Handle, ProcessID) <> nil;
end;

function FindTopmostWindow(ParentWnd: HWND; Pt: TPoint): HWND;
var
  R: TRect;
begin
  Result := GetWindow(ParentWnd, GW_CHILD); // 取得第一個子視窗

  while Result <> 0 do
  begin
    GetWindowRect(Result, R); // 取得視窗矩形區域

    if IsWindowVisible(Result) and PtInRect(R, Pt) then
    begin
      if Result = Application.MainForm.Handle then // 忽略程式的 Main Form
      begin
        Result := 0;
        Exit;
      end;
      Result := FindTopmostWindow(Result, Pt); // 找到視窗, 遞迴呼叫取得子視窗
      Exit;
    end;
    Result := GetWindow(Result, GW_HWNDNEXT); // 取得下一個 siblings 視窗
  end;

  Result := ParentWnd; // 找不到, 它就是我們要找的
end;

{
  使用 ChildWindowFromPoint 來尋找, 連 non-visual 視窗都會找到

function FindTopmostWindow(ParentWnd: HWND; Pt: TPoint): HWND;
begin
  repeat
    Result := ChildWindowFromPoint(ParentWnd, Pt);
    if Result = ParentWnd then break;

    if Result = Application.MainForm.Handle then // 若是 MainForm 本身, 傳回 0
    begin
      Result := 0;
      Exit;
    end;

    MapWindowPoints(ParentWnd, Result, Pt, 1);
    ParentWnd := Result;
  until false;
end;
}
procedure MyDrawFocusRect(DC: HDC; R: TRect; Width: Integer = DEFAULT_FOCUSRECT_WIDTH);
var
  I: Integer;
begin
  InflateRect(R, - Width, - Width);
  DrawFocusRect(DC, R);
  for I := 1 to Width do
  begin
    InflateRect(R, 1, 1);
    DrawFocusRect(DC, R);
  end;
end;

procedure DrawWindowFocusRect(Wnd: HWND; Width: Integer = DEFAULT_FOCUSRECT_WIDTH);
var
  DC: HDC;  
  R : TRect;
begin
  DC := getwindowdc(Wnd);
  GetWindowRect(Wnd, R);
  MapWindowPoints(HWND_DESKTOP, Wnd, R, 2);
  OffsetRect(R, - R.left, - R.top);
  MyDrawFocusRect(DC, R, Width);
  releasedc(Wnd, DC);
end;

procedure DrawControlFocusRect(Control: TControl; Width: Integer = DEFAULT_FOCUSRECT_WIDTH);
var
  Wnd: HWND; 
  DC : HDC;  
  R  : TRect;
begin
  Wnd := Control.Parent.Handle;
  DC := getdc(Wnd);
  R := Control.BoundsRect;
  MyDrawFocusRect(DC, R, Width);
  releasedc(Wnd, DC);
end;


end.

