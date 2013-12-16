unit xdarray;

interface

uses SysUtils, Windows, Dialogs, Math;

// A: 動態陣列變數 elSize: 元素所佔位元組 Index: 欲刪除的元素索引
// Count: 欲刪除的元素數目
procedure DynArrayDelete(var A; elSize: Longint; index, Count: Integer);
procedure DynArrayInsert(var A; elSize: Longint; index, Count: Integer);

procedure DynArrayCopy(var ADst; const ASrc; elSize: Longint; IndexDst, IndexSrc, Count: Integer);
procedure DynArrayAppend(var ADst; const ASrc; elSize: Longint; IndexSrc, Count: Integer);

implementation

procedure DynArraySetZero(var A);
var
  P: PLongint;
begin
  P := PLongint(A);
  Dec(P);
  P^ := 0;
  Dec(P);
  P^ := 0;
end;

procedure DynArrayDelete(var A; elSize: Longint; index, Count: Integer);
var
  len, MaxDelete: Integer; 
  P             : PLongint;
begin
  P := PLongint(A);
  if P = nil then Exit;
  
  len := PLongint(PChar(P) - 4)^;
  
  if index >= len then Exit;
  
  MaxDelete := len - index;
  Count := Min(Count, MaxDelete);
  
  if Count = 0 then Exit; // nothing to delete
  
  Dec(len, Count);
  MoveMemory(PChar(P) + index * elSize, PChar(P) + (index + Count) * elSize, (len - index) * elSize);
  
  Dec(P);
  Dec(P);
  ReallocMem(P, len * elSize + Sizeof(Longint) * 2);
  Inc(P);
  P^ := len; // new length
  Inc(P);
  
  PLongint(A) := P;
end;

procedure DynArrayInsert(var A; elSize: Longint; index, Count: Integer);
const
  PNull: Pointer = nil;
var
  len, I: Integer; 
  P     : PLongint;
begin
  P := PLongint(A);
  if P <> nil then
  begin
    len := PLongint(PChar(P) - 4)^;
    if (index > len) or (Count = 0) then Exit; // nothing to insert
    
    Dec(P);
    Dec(P);
  end else len := 0;
  
  ReallocMem(P, (len + Count) * elSize + Sizeof(Longint) * 2); // 先 realloc
  Inc(P);
  P^ := len + Count;
  Inc(P);
  
  MoveMemory(PChar(P) + (index + Count) * elSize, PChar(P) + index * elSize, (len - index) * elSize); // 往後挪
  for I := index to index + Count - 1 do
    System.Move(PNull, PChar(Integer(P) + I * elSize)^, elSize);
  
  PLongint(A) := P;
end;

procedure DynArrayCopy(var ADst; const ASrc; elSize: Longint; IndexDst, IndexSrc, Count: Integer);
var
  PDst, PSrc    : PLongint;
  LenDst, LenSrc: Integer; 
begin
  PDst := PLongint(ADst);
  PSrc := PLongint(ASrc);
  if (PSrc = nil) then Exit;
  
  if PDst <> nil then
    LenDst := PLongint(PChar(PDst) - 4)^
     else LenDst := 0;
  
  LenSrc := PLongint(PChar(PSrc) - 4)^;
  
  Count := Min(LenSrc - IndexSrc, Count); // src array 不足時, 減少 count
  
  if IndexDst + Count - 1 > LenDst then // dst array 空間不足
  begin
    DynArrayInsert(ADst, elSize, IndexDst, (IndexDst + Count) - LenDst); // 補足, 內容不管, 待會就蓋掉了
    PDst := PLongint(ADst);
  end;
  
  MoveMemory(PChar(PDst) + IndexDst * elSize, PChar(PSrc) + IndexSrc * elSize, Count * elSize); // 複製
end;

procedure DynArrayAppend(var ADst; const ASrc; elSize: Longint; IndexSrc, Count: Integer);
var
  P: PLongint;
begin
  P := PLongint(ADst);
  if (P = nil) then Exit;
  
  DynArrayCopy(ADst, ASrc, elSize, PLongint(PChar(P) - 4)^, IndexSrc, Count);
end;

end.

