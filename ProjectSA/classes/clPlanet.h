//---------------------------------------------------------------------------
#ifndef clPlanetH
#define clPlanetH
//---------------------------------------------------------------------------
//#include <iostream>
//#include "..\\OMEGA_functions.h"
#include "clObject.h"

class clPlanet : virtual public clObject
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
	virtual ~clPlanet() { /*delete chName;*/ };
	clPlanet() { clObject::clObject(); SetName("Star"); iColour = _ColdBLUE_; iAlpha = 20; bAlphaUp = true; bCollisionPlayer = false; };
	//данные-члены
	int iColour;
	int iAlpha;
	bool bAlphaUp;
	bool bCollisionPlayer;
	oeCircle circleCircle;
	/*struct oeCircle
	{
		float X;
		float Y;
		float Radius;
	};*/


	//"set" функции-члены		
	//"get" функции-члены
	//другие функции-члены	
	bool CollisionPlayer(oeCircle _circleCircle);
	void DrawPoppupWindow(int _i);
	void SSpriteDraw(float X, float Y, float Width, float Height, int Alpha, float Angle, int Flags);
	void Draw();
	void DrawName();
	void Update();
};
//---------------------------------------------------------------------------
#endif