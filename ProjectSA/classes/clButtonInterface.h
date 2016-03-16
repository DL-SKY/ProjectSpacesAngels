//---------------------------------------------------------------------------
#ifndef clButtonInterfaceH
#define clButtonInterfaceH
//---------------------------------------------------------------------------
//#include <iostream>
//#include "..\\OMEGA_functions.h"
#include "clButtonMainMenu.h"

class clButtonInterface : virtual public clButtonMainMenu
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
	char *chKey;
	//int iAlpha;
	//"set" функции-члены
	//"get" функции-члены   
	//другие функции-члены

/*открытые функции-члены и данные-члены
доступны везде*/
public:
	//деструктор и конструкторы
	virtual ~clButtonInterface() { /*delete chName;*/ };
	clButtonInterface();
	//данные-члены	
	//bool bEnabled;
	//PFont2D *fntFont;
	//"set" функции-члены
	void SetKey(char _chKey[11]);
	//"get" функции-члены
	char *GetKey();
	//другие функции-члены	
	void Draw();
};
//---------------------------------------------------------------------------
#endif