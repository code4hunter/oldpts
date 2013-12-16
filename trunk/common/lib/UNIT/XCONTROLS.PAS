unit xControls;

interface

uses Windows, Messages, SysUtils, Forms, Classes, Controls, ComCtrls;

procedure EnableControl(AControl: TControl; Enable: Boolean);
procedure EnableChildControls(AControl: TControl; Enable: Boolean);
procedure EnableClassControl(AControl: TControl; Enable: Boolean; ControlClass: TControlClass);

procedure SelectPageIndex(const PC: TPageControl; const iIndex: Integer; const Animated: Boolean);
procedure MakeSureTabVisible(const PC: TPageControl);

procedure LoadTreeViewFromTextFile(Nodes: TTreeNodes; Filename: string);
procedure SaveTreeViewToTextFile(Nodes: TTreeNodes; Filename: string);

implementation

uses xStrings;


procedure EnableControl(AControl: TControl; Enable: Boolean);
var
  I: Integer;
begin
  AControl.Enabled := Enable;
  if AControl is TWinControl then
    with TWinControl(AControl) do
    begin
      for I := 0 to ControlCount - 1 do
        EnableControl(Controls[I], Enable);
    end;
end;

procedure EnableChildControls(AControl: TControl; Enable: Boolean);
var
  I: Integer;
begin
  if AControl is TWinControl then
    with TWinControl(AControl) do
    begin
      for I := 0 to ControlCount - 1 do
        EnableControl(Controls[I], Enable);
    end;
end;

procedure EnableClassControl(AControl: TControl; Enable: Boolean; ControlClass: TControlClass);
var
  I: Integer;
begin
  if (AControl is ControlClass) then AControl.Enabled := Enable;
  
  if AControl is TWinControl then
    with TWinControl(AControl) do
    begin
      for I := 0 to ControlCount - 1 do
        EnableClassControl(Controls[I], Enable, ControlClass);
    end;
end;

procedure SelectPageIndex(const PC: TPageControl; const iIndex: Integer; const Animated: Boolean);
var
  oIndex, I: Integer;
begin
  with PC do
  begin
    oIndex := ActivePage.pageindex;
    if Animated then
    begin
      while (ActivePage.pageindex <> iIndex) do
      begin
        SelectNextPage(iIndex > oIndex);
        if ActivePage.pageindex = oIndex then Break;
      end;
      // if not ActivePage.TabVisible then ActivePage := Pages[oIndex];
    end
    else
    begin
      for I := 0 to PageCount - 1 do
        if Pages[I].pageindex = iIndex then
        begin
          if Pages[I].TabVisible then ActivePage := Pages[I] else ActivePage := Pages[oIndex];
          Exit;
        end;
    end;
  end;
end;

procedure MakeSureTabVisible(const PC: TPageControl);
begin
  while not PC.ActivePage.TabVisible do PC.SelectNextPage(True);
end;

procedure LoadTreeViewFromTextFile(Nodes: TTreeNodes; Filename: string);
var
  F: TextFile;
  
  function ProcessNode(Node: TTreeNode; LevelNo: Integer): TTreeNode;
  var
    S : string; 
    No: Integer;
  begin
    Result := Node;
    repeat
      readln(F, S);
      No := ParseRPLNo(S);
      if No > LevelNo then // 下一層
      begin
        Node := ProcessNode(Nodes.addchild(Node, S), No);
      end else if No < LevelNo then // 上一層
      begin
        Result := Nodes.Add(Node.Parent, S);
        Exit;
      end else // 同一層
        Node := Nodes.Add(Node, S);
      
    until EOF(F);
  end;
  
begin
  Assignfile(F, Filename);
  reset(F);
  
  ProcessNode(nil, 1);
  
  CloseFile(F);
end;

procedure SaveTreeViewToTextFile(Nodes: TTreeNodes; Filename: string);
var
  F: TextFile;
  
  procedure ProcessNode(Node: TTreeNode; Depth: Integer);
  begin
    while Node <> nil do
    begin
      Writeln(F, IntToStr(Depth) + ' ' + Node.Text);
      
      if Node.HasChildren then
        ProcessNode(Node.GetFirstChild, Depth + 1);
      
      Node := Node.getNextSibling;
    end;
  end;
  
begin
  Assignfile(F, Filename);
  rewrite(F);
  
  ProcessNode(Nodes.GetFirstNode, 1);
  
  CloseFile(F);
end;

end.

