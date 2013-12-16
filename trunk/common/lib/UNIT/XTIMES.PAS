unit xTimes;

interface

uses Windows, Messages, SysUtils, Forms, Controls;

function TimeT_To_DateTime(TimeT: Longint): TDateTime;

function TimeToSecond(const H, M, S: Integer): Integer;
procedure SecondToTime(const secs: Integer; var H, M, S: Word);
function SecondToTimeStr(secs: Integer): string;

implementation

function TimeT_To_DateTime(TimeT: Longint): TDateTime;
var
  ts: TTimeStamp;
begin
  Dec(TimeT, 3600 * 8);    // still unprecise
  ts.Time := (TimeT mod 86400) * 1000;
  ts.Date := TimeT div 86400 + 719163;
  Result := TimeStampToDateTime(ts);
end;

function TimeToSecond(const H, M, S: Integer): Integer;
begin
  Result := H * 3600 + M * 60 + S;
end;

procedure SecondToTime(const secs: Integer; var H, M, S: Word);
begin
  H := secs div 3600;
  M := (secs mod 3600) div 60;
  S := secs mod 60;
end;

function SecondToTimeStr(secs: Integer): string;
var
  H, M, S: Word;
begin
 Secondtotime(secs, h, m, s);

 result := '';
 if h <> 0 then Result := result + format('%-.2d ¤p®É ', [h]);
 if m <> 0 then Result := result + format('%-.2d ¤À ', [m]);
 if s <> 0 then Result := result + format('%-.2d ¬í ', [s]);
end;

end.
