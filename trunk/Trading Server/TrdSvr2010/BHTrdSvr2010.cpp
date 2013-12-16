//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UFrmMain.cpp", FrmMain);
USEFORM("UnitAbout.cpp", AboutBox);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{

		#ifdef USECOM
			if( CoInitialize(NULL) != S_OK  )
				Application->MessageBox("CoInitialize(NULL)Ê§°Ü£¡","Trade Server",IDOK);
			else
				Application->Title = "Trade Server Apartment";
		#elif defined USECOMT
			CoUninitialize();
			int ret = CoInitializeEx(NULL,0) ;
			if ( ret!= S_OK )
				Application->MessageBox(L"CoInitialize(NULL,0)Ê§°Ü£¡",L"Trade Server",IDOK);
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


















