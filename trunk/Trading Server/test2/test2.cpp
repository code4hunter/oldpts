//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//#include <objbase.h>
//---------------------------------------------------------------------------
USEFORM("uMain.cpp", frmMain);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     //CoInitializeEx(NULL,0);

     Application->Initialize();
     Application->Title = "Test Trade";
     Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  catch (...)
  {
     try
     {
       throw Exception("");
     }
     catch (Exception &exception)
     {
       Application->ShowException(&exception);
     }
  }
  return 0;
}
//---------------------------------------------------------------------------
