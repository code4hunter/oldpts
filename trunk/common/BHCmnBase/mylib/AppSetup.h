//---------------------------------------------------------------------------
//    Name:       AppSetup
//    Function:   ∂¡–¥≈‰÷√Œƒº˛
//    Author:     codehunter
//---------------------------------------------------------------------------

#ifndef AppSetupH
#define AppSetupH
//---------------------------------------------------------------------------
#include <inifiles.hpp>

class TAppSetup
{
private:
protected:
    AnsiString FFileName;
  TIniFile *FIniFile;
  void virtual __fastcall ReadIni(void);
  void virtual __fastcall WriteIni(void);

public:
  void __fastcall ReadFromFile(const AnsiString PathName="");
  void __fastcall SaveToFile(const AnsiString PathName="");
  __fastcall TAppSetup(const AnsiString PathName);
  virtual __fastcall ~TAppSetup(void);
  
  __property AnsiString FileName  = { read=FFileName, write=FFileName };

};
#endif
 