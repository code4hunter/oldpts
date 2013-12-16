unit xFonts;

interface

uses Classes, Graphics, SysUtils;

procedure StringToFont(sFont: string; Font: TFont; bIncludeColor: Boolean = True);
function FontToString(Font: TFont; bIncludeColor: Boolean = True): string;

implementation

const
  csfsBold      = '|Bold';     
  csfsItalic    = '|Italic';   
  csfsUnderline = '|Underline';
  csfsStrikeout = '|Strikeout';
  
  //
  // Expected format:
  //   "Arial", 9, [Bold], [clRed]
  //
procedure StringToFont(sFont: string; Font: TFont; bIncludeColor: Boolean = True);
var
  P     : Integer;
  sStyle: string; 
begin
  with Font do
    try
      // get font name
      P := Pos(',', sFont);
      name := Copy(sFont, 2, P - 3);
      Delete(sFont, 1, P);
      
      // get font size
      P := Pos(',', sFont);
      Size := StrToInt(Copy(sFont, 2, P - 2));
      Delete(sFont, 1, P);
      
      // get font style
      P := Pos(',', sFont);
      sStyle := '|' + Copy(sFont, 3, P - 4);
      Delete(sFont, 1, P);
      
      // get font color
      if bIncludeColor then
        Color := StringToColor(Copy(sFont, 3, Length(sFont) - 3));
      
      // convert str font style to
      // font style
      Style := [];
      
      if (Pos(csfsBold, sStyle) > 0) then
        Style := Style + [fsBold];
      
      if (Pos(csfsItalic, sStyle) > 0) then
        Style := Style + [fsItalic];
      
      if (Pos(csfsUnderline, sStyle) > 0) then
        Style := Style + [fsUnderline];
      
      if (Pos(csfsStrikeout, sStyle) > 0) then
        Style := Style + [fsStrikeOut];
    except
    end;
end;

//
// Output format:
//   "Aril", 9, [Bold|Italic], [clAqua]
//
function FontToString(Font: TFont; bIncludeColor: Boolean = True): string;
var
  sStyle: string;
begin
  with Font do
  begin
    // convert font style to string
    sStyle := '';
    
    if (fsBold in Style) then
      sStyle := sStyle + csfsBold;
    
    if (fsItalic in Style) then
      sStyle := sStyle + csfsItalic;
    
    if (fsUnderline in Style) then
      sStyle := sStyle + csfsUnderline;
    
    if (fsStrikeOut in Style) then
      sStyle := sStyle + csfsStrikeout;
    
    if ((Length(sStyle) > 0) and ('|' = sStyle[1])) then
      sStyle := Copy(sStyle, 2, Length(sStyle) - 1);
    
    Result := Format('"%s", %d, [%s]',[name, Size, sStyle]);
    if bIncludeColor then
      Result := Result + Format(', [%s]',[ColorToString(Color)]);
  end;
end;

end.

