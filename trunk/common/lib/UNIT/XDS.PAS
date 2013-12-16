unit xDS;

{$R-}

interface

uses SysUtils, Classes;

const
  DEFAULT_HASHTABLE_SLOTNUM = 513;

type
  ExDataStructure = Exception;

  TxLinkedList = class
  private
    FRootPtr: Pointer;
    FNode_Size: Integer;
  protected
  public
    constructor Create(ANode_Size: Integer);
    destructor Destroy; override;
  end;

  TxHashTable = class
  private
    FTablePtr: Pointer;
    FSlot_Num, FSlot_Size: Integer;
  protected
    procedure RecreateTable; virtual;
    function HashFunc(Slot_No: Integer): Longint; virtual;
  public
    constructor Create(ASlot_Size: Integer; ASlot_Num: Integer = DEFAULT_HASHTABLE_SLOTNUM);
    destructor Destroy; override;
  end;

implementation

constructor TxLinkedList.Create(ASlot_Size: Integer; ASlot_Num: Integer = DEFAULT_HASHTABLE_SLOTNUM);
begin
  inherited Create;

  FSlot_Num := ASlot_Num;
  FSlot_Size := ASlot_Size;

  RecreateTable;
end;

destructor TxLinkedList.Destroy;
begin

  inherited Destroy;
end;

// TxHashTable

constructor TxHashTable.Create(ANode_Size: Integer);
begin
  inherited Create;

  FNode_Size := ANode_Size;

end;

destructor TxHashTable.Destroy;
begin

  inherited Destroy;
end;


procedure TxHashTable.RecreateTable;
begin
  if Assigned(FTablePtr) then
    FreeMem(FTablePtr);
  
  if FSlot_Num = 0 then
    raise ExDataStructure.Create('Slot num can''t be zero');
  
  if FSlot_Size = 0 then
    raise ExDataStructure.Create('Slot size can''t be zero');
  
  FTablePtr := AllocMem(FSlot_Num * FSlot_Size);
end;

function TxHashTable.HashFunc(Slot_No: Integer): Longint;
type
  PByte = ^Byte;
var
  P: PByte;
  I: Integer;
begin
  P := PByte(Integer(FTablePtr) + Slot_No * FSlot_Size);

  Result := 0;
  for I := 1 to FSlot_Size do
    Inc(Result, P^);
end;

end.

