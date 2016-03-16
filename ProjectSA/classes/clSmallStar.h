//---------------------------------------------------------------------------
#ifndef clSmallStarH
#define clSmallStarH
//---------------------------------------------------------------------------
//#include <iostream>
//#include "..\\OMEGA_functions.h"
#include "clObject.h"

class clSmallStar : virtual public clObject
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
	virtual ~clSmallStar() { /*delete chName;*/ };
	clSmallStar() { clObject::clObject(); iColour = _ColdBLUE_; iAlpha = 0; bAlphaUp = true; };
	//данные-члены
	int iColour;
	int iAlpha;
	bool bAlphaUp;
	//"set" функции-члены		
	//"get" функции-члены
	//другие функции-члены	
	void Draw();
	void Update();
};
//---------------------------------------------------------------------------
#endif