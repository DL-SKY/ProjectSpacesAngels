//---------------------------------------------------------------------------
#ifndef clButtonMainMenuH
#define clButtonMainMenuH
//---------------------------------------------------------------------------
//#include <iostream>
//#include "..\\OMEGA_functions.h"
#include "clObject.h"

class clButtonMainMenu : virtual public clObject
{
/*закрытые функции-члены и данные-члены
недоступны за пределами класса*/
private:
	//данные-члены
	//"set" функции-члены
	//"get" функции-члены
	//другие функции-члены

/*защищенные функции-члены и данные-члены
доступны в производном классе*/
protected:
	//данные-члены
	//"set" функции-члены
	//"get" функции-члены   
	//другие функции-члены

/*открытые функции-члены и данные-члены
доступны везде*/
public:
	//деструктор и конструкторы
	virtual ~clButtonMainMenu() { /*delete chName;*/ };
	clButtonMainMenu() { clObject::clObject(); bEnabled = true; iAlpha = 255;};
	//данные-члены	
	int iAlpha;
	bool bEnabled;
	PFont2D *fntFont;
	//"set" функции-члены		
	//"get" функции-члены
	//другие функции-члены	
	void Draw();
};
//---------------------------------------------------------------------------
#endif