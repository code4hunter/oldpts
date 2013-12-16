unit xGraphics;

interface

uses Windows, Messages, SysUtils, Forms, Controls, Graphics, ShellAPI, Registry;

function ColorToRGBString(AColor: TColor): string;
function RGBStringToColor(RGBStr: string): TColor;

function MyLoadIcon(const Filename: string; DefaultIcon: HICON = 0): HICON;
function CursorToIcon(const hc: HCURSOR; bDestroyCursor: Boolean = False): HICON;

function ColorNumToStr(Num: Integer): string;

implementation

uses xStrings, xFiles;

function ColorToRGBString(AColor: TColor): string;
begin
  Result := Format('%d %d %d',[GetRValue(AColor), GetGValue(AColor), GetBValue(AColor)]);
end;

function RGBStringToColor(RGBStr: string): TColor;
var
  I      : Integer;
  R, G, B: Byte;
begin
  Result := $00000000;
  RGBStr := Trim(RGBStr);
  if CountWords(RGBStr) <> 3 then Exit;
  
  // Red Value
  I := Pos(' ', RGBStr);
  R := StrToIntDef(Copy(RGBStr, 1, I - 1), 0);
  Delete(RGBStr, 1, I);
  
  // Green Value
  I := Pos(' ', RGBStr);
  G := StrToIntDef(Copy(RGBStr, 1, I - 1), 0);
  Delete(RGBStr, 1, I);
  
  // Blue
  B := StrToIntDef(RGBStr, 0);
  
  Result := RGB(R, G, B);
end;

function MyLoadIcon(const Filename: string;
  DefaultIcon: HICON = 0): HICON;
var
  IconNo: Integer;
  S, Ext: string; 
begin
  Result := 0;
  
  S := AnsiUpperCase(Filename);
  IconNo := TruncateTrailNumber(S);
  
  Ext := ExtractFileExt(S);
  if Ext = '.ICO' then
    Result := LoadImage(HInstance, PChar(S), IMAGE_ICON, 32, 32,
    LR_LOADFROMFILE)
  else if ((Ext = '.ICL') or (Ext = '.DLL') or (Ext = '.EXE'))
    and (IconNo <> -1) then
    Result := ExtractIcon(HInstance, PChar(S), IconNo);

  // 如果失敗, 就用 default icon 代替..
  if Result = 0 then
    Result := DefaultIcon;
  // 如果 default icon 也不存在, 就用程式本身 icon 代替
  if Result = 0 then
    Result := Application.ICON.Handle;
end;

// 將游標圖案轉為 HICON 以便顯示
function CursorToIcon(const hc: HCURSOR; bDestroyCursor: Boolean = False): HICON;
var
  ii: TIconInfo;
begin
  if hc <> 0 then
  begin
    GetIconInfo(hc, ii);
    Result := CreateIconIndirect(ii);
    if bDestroyCursor then DestroyCursor(hc);
  end else
    Result := 0;
end;

function ColorNumToStr(Num: Integer): string;
begin
  case Num of
    16: Result := '4 bit';
    256: Result := '8 bit';
    32768: Result := '15 bit';
    65536: Result := '16 bit';
    16777216: Result := '24 bit';
  else Result := IntToStr(Num) + 'colors';
  end;
end;



end.

