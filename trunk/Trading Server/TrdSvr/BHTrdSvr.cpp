//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitAbout.cpp", AboutBox);
USEFORM("UFrmMain.cpp", FrmMain);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		#ifdef USECOM
			if( CoInitialize(NULL) != S_OK  )
				Application->MessageBoxA("CoInitialize(NULL)Ê§°Ü£¡","Trade Server",IDOK);
			else
				Application->Title = "Trade Server Apartment";
		#elif defined USECOMT
			if ( CoInitializeEx(NULL,0) != S_OK )
				Application->MessageBoxA("CoInitialize(NULL,0)Ê§°Ü£¡","Trade Server",IDOK);
			else
				Application->Title = "Trade Server MTH";
		#else
    	Application->Title = "Trade Server";
		#endif

		Application->Initialize();
		Application->CreateForm(__classid(TFrmMain), &FrmMain);
		SetApplicationMainFormOnTaskBar(Application, true);
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
	#ifdef USECOM
	CoUninitialize();
	#elif defined USECOMT
	CoUninitialize();
	#endif
  return 0;
}
//---------------------------------------------------------------------------


















