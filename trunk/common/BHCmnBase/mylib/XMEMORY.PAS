unit xMemory;

interface

uses Windows, SysUtils;

function IsMemAddressReadable(P: Pointer; Size: DWORD = 4): Boolean;
function IsMemAddressWritable(P: Pointer; Size: DWORD = 4): Boolean;

procedure TryReadMemAddress(P: Pointer; Size: DWORD = 4);
procedure TryWriteMemAddress(P: Pointer; Size: DWORD = 4);

function MapGlobalData(const MapName: string; Size: Integer; var Ptr: Pointer): THandle;
procedure ReleaseGlobalData(Handle: THandle; var Ptr: Pointer);

function IsGlobalDataExistent(const MapName: string): Boolean;

implementation

function IsMemAddressReadable(P: Pointer; Size: DWORD = 4): Boolean;
begin
  Result := not IsBadReadPtr(P, Size);
end;

procedure TryReadMemAddress(P: Pointer; Size: DWORD = 4);
begin
  if not IsMemAddressReadable(P, Size) then
    raise EAccessViolation.CreateFmt('Can''t read address %p',[P]);
end;

function IsMemAddressWritable(P: Pointer; Size: DWORD = 4): Boolean;
begin
  Result := not IsBadWritePtr(P, Size);
end;

procedure TryWriteMemAddress(P: Pointer; Size: DWORD = 4);
begin
  if not IsMemAddressWritable(P, Size) then
    raise EAccessViolation.CreateFmt('Can''t write address %p',[P]);
end;

function MapGlobalData(const MapName: string; Size: Integer; var Ptr: Pointer): THandle;
begin
  Result := CreateFileMapping($FFFFFFFF, nil, PAGE_READWRITE, 0, Size, PChar(MapName));
  
  if Result = 0 then
    if GetLastError = ERROR_ALREADY_EXISTS then
    begin
      Result := OpenFileMapping(FILE_MAP_ALL_ACCESS, False, PChar(MapName));
      if Result = 0 then Exit;
    end else Exit;
  
  Ptr := MapViewOfFile(Result, FILE_MAP_ALL_ACCESS, 0, 0, 0);
  if Ptr = nil then
  begin
    CloseHandle(Result);
    Result := 0;
  end;
end;

procedure ReleaseGlobalData(Handle: THandle; var Ptr: Pointer);
begin
  if Assigned(Ptr) then
  begin
    UnmapViewOfFile(Ptr);
    Ptr := nil;
  end;
  
  if Handle <> 0 then
  begin
    CloseHandle(Handle);
    Handle := 0;
  end;
end;

function IsGlobalDataExistent(const MapName: string): Boolean;
var
  hMap: THandle;
begin
  hMap := OpenFileMapping(FILE_MAP_ALL_ACCESS, False, PChar(MapName));
  Result := hMap <> 0;
  if Result then CloseHandle(hMap);
end;

end.

