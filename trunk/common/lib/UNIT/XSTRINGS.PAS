unit xStrings;

interface

uses SysUtils, Classes, Windows, FileCtrl, Dialogs;

const
  DEFAULT_DELIMITERS = [' ', #9, #10, #13];
  
function GetToken(const S: string; index: Integer; bTrail: Boolean = False; Delimiters: TSysCharSet = DEFAULT_DELIMITERS): string;
function CountWords(S: string; Delimiters: TSysCharSet = DEFAULT_DELIMITERS): Integer;
function BracketString(const S: string): string;

procedure TruncateCRLF(var S: string);
function IsContainingCRLF(const S: string): Boolean;

function ReplaceString(var S: string; const Token, NewToken: string; bCaseSensitive: Boolean): Boolean;
procedure Simple_ReplaceString(var S: string; const Substr: string; index, Count: Integer);

function UnquoteString(const S: string): string;
function FirstToken(var S: string; const Delimiter: string; Remove: Boolean): string;
function AddTimeStamp(const S: string): string;

function PartialIndexOf(SL: TStrings; S: string; StartIndex: Integer; bForward: Boolean): Integer;
function CompositeStrings(SL: TStrings; const Delimiter: string): string;

function SafeLoadStrings(SL: TStrings; const Filename: string): Boolean;
procedure SafeSaveStrings(SL: TStrings; const Filename: string);

procedure RemoveDuplicates(SL: TStrings);
function ParseRPLNo(var Msg: string): Integer;

function RPos(const C: Char; const S: string): Integer;
function AnsiIPos(const Substr, S: string): Integer;
function MatchString(S, SubS: string; Options: TFindOptions): Integer;

implementation

function GetToken(const S: string; index: Integer; bTrail: Boolean = False; Delimiters: TSysCharSet = DEFAULT_DELIMITERS): string;
var
  I, W, head, tail: Integer;
  bInWord         : Boolean;
begin
  I := 1;
  W := 0;
  bInWord := False;
  head := 1;
  tail := Length(S);
  while (I <= Length(S)) and (W <= index) do
  begin
    if S[I] in Delimiters then
    begin
      if (W = index) and bInWord then tail := I - 1;
      bInWord := False;
    end else
    begin
      if not bInWord then
      begin
        bInWord := True;
        Inc(W);
        if W = index then head := I;
      end;
    end;
    
    Inc(I);
  end;
  
  if bTrail then tail := Length(S);
  if W >= index then Result := Copy(S, head, tail - head + 1)
  else Result := '';
end;

function CountWords(S: string; Delimiters: TSysCharSet = DEFAULT_DELIMITERS): Integer;
var
  bInWord: Boolean;
  I      : Integer;
begin
  Result := 0;
  I := 1;
  bInWord := False;
  while I <= Length(S) do
  begin
    if S[I] in Delimiters then bInWord := False
    else
    begin
      if not bInWord then
      begin
        bInWord := True;
        Inc(Result);
      end;
    end;
    
    Inc(I);
  end;
end;

function IsContainingCRLF(const S: string): Boolean;
var
  len: Integer;
begin
  len := Length(S);
  Result := (len >= 2) and (S[len - 1] = #13) and (S[len] = #10);
end;

procedure TruncateCRLF(var S: string);
var
  I: Integer;
begin
  I := 1;
  while I <= Length(S) do
    if (S[I] = #13) or (S[I] = #10) then Delete(S, I, 1)
    else Inc(I);
end;

function ReplaceString(var S: string; const Token, NewToken: string; bCaseSensitive: Boolean): Boolean;
var
  I         : Integer;
  sFirstPart: string; 
begin
  if bCaseSensitive then
    I := AnsiPos(Token, S)
  else
    I := AnsiPos(AnsiUpperCase(Token), AnsiUpperCase(S));
  
  if I <> 0 then
  begin
    sFirstPart := Copy(S, 1, I - 1) + NewToken; // Á×§KµL½a»¼°j
    S := Copy(S, I + Length(Token), Maxint);
  end;
  
  Result := I <> 0;
  if Result then
  begin
    ReplaceString(S, Token, NewToken, bCaseSensitive);
    S := sFirstPart + S;
  end;
end;

procedure Simple_ReplaceString(var S: string; const Substr: string; index, Count: Integer);
begin
  S := Format('%s%s%s',[Copy(S, 1, index - 1), Substr, Copy(S, index + Count, Maxint)]);
end;

function BracketString(const S: string): string;
begin
  Result := S;
  if (Result = '') or (Result[1] <> '[') then Result := '[' + Result;
  if Result[Length(Result)] <> ']' then Result := Result + ']';
end;

function UnquoteString(const S: string): string;
begin
  if S = '' then Exit;
  
  Result := S;
  
  if Result[1] = '"' then Delete(Result, 1, 1);
  if Result = '' then Exit;
  
  if Result[Length(Result)] = '"' then Delete(Result, Length(Result), 1);
end;

function FirstToken(var S: string; const Delimiter: string; Remove: Boolean): string;
var
  I: Integer;
begin
  I := Pos(Delimiter, S);
  if I <> 0 then
  begin
    Result := Copy(S, 1, I - 1);
    if Remove then S := Trim(Copy(S, I + 1, Maxint));
  end else
  begin
    Result := S;
    if Remove then S := '';
  end;
end;

function CompositeStrings(SL: TStrings; const Delimiter: string): string;
var
  I: Integer;
begin
  Result := '';
  
  with SL do
  begin
    for I := 0 to Count - 2 do
      Result := Result + Strings[I] + Delimiter;
    if Count > 0 then
      Result := Result + Strings[Count - 1];
  end;
end;

function AddTimeStamp(const S: string): string;
begin
  if S = '' then
    Result := DateTimeToStr(Now)
  else if S[Length(S)] = #10 then
    Result := Copy(S, 1, Length(S) - 2) + ' at ' + DateTimeToStr(Now) + #13#10
  else
    Result := S + ' at ' + DateTimeToStr(Now);
end;

function SafeLoadStrings(SL: TStrings; const Filename: string): Boolean;
begin
  Result := False;
  repeat
    try
      if not FileExists(Filename) then Exit;
      SL.LoadFromFile(Filename);
      Result := True;
      Break;
    except
      Sleep(500);
    end;
  until False;
end;

procedure SafeSaveStrings(SL: TStrings; const Filename: string);
begin
  ForceDirectories(ExtractFilePath(Filename));
  repeat
    try
      SL.SaveToFile(Filename);
      Break;
    except
      Sleep(500);
    end;
  until False;
end;

function PartialIndexOf(SL: TStrings; S: string; StartIndex: Integer; bForward: Boolean): Integer;
begin
  with SL do
  begin
    if bForward then
    begin
      for Result := StartIndex to Count - 1 do
        if AnsiCompareText(S, Copy(Strings[Result], 1, Length(S))) = 0 then Exit;
    end else
    begin
      for Result := StartIndex downto 0 do
        if AnsiCompareText(S, Copy(Strings[Result], 1, Length(S))) = 0 then Exit;
    end;
  end;
  
  Result := -1;
end;

// duplicated string must be adjacent ..
procedure RemoveDuplicates(SL: TStrings);
var
  I: Integer;
begin
  with SL do
  begin
    I := 1;
    while I < Count do
      if CompareText(Strings[I], Strings[I - 1]) = 0 then
        Delete(I)
      else
        Inc(I);
  end;
end;

function ParseRPLNo(var Msg: string): Integer;
var
  S: string;
begin
  S := GetToken(Msg, 1, False);
  Result := StrToIntDef(S, 0);
  Msg := GetToken(Msg, 2, True);
end;

function RPos(const C: Char; const S: string): Integer;
var
  I: Integer;
begin
  Result := 0;
  I := Length(S);
  repeat
    if S[I] = C then
    begin
      Result := I;
      Exit;
    end;
    dec(I);
  until I < 1;
end;

function AnsiIPos(const Substr, S: string): Integer;
begin
  Result := AnsiPos(AnsiLowerCase(Substr), AnsiLowerCase(S));
end;

function MatchString(S, SubS: string; Options: TFindOptions): Integer;
const
  Delimiters = [#0..#47, #58..#64, #123..#255];
var
  EndI: Integer;
begin
  if not (frMatchCase in Options) then
  begin
    S := AnsiUpperCase(S);
    SubS := AnsiUpperCase(SubS);
  end;

  if frWholeWord in Options then
  begin
    Result := 1;
    EndI := Length(SubS);
    while EndI <= Length(S) do
    begin
      if ((Result = 1) or (S[Result - 1] in Delimiters)) and ((EndI = Length(S)) or (S[EndI + 1] in Delimiters)) and
        (AnsiCompareStr(Copy(S, Result, Length(SubS)), SubS) = 0) then Break;
      Inc(Result);
      Inc(EndI);
    end;
    Result := EndI;
    if Result > Length(S) then Result := 0;
  end else Result := AnsiPos(SubS, S);
end;

end.

