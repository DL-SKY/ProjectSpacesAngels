//---------------------------------------------------------------------------
#ifndef clStarSystemH
#define clStarSystemH
//---------------------------------------------------------------------------
//#include <iostream>
//#include "..\\OMEGA_functions.h"
#include <vector>

#include "clPlanet.h"
#include "clBigStar.h"
#include "clButtonMainMenu.h"

class clStarSystem
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
	int iCol;				//Текущая колонка для списка объектов на карте справа
	char *chName;			//Символьное название
	//"set" функции-члены
	//"get" функции-члены   
	//другие функции-члены

/*открытые функции-члены и данные-члены
доступны везде*/
public:
	//деструктор и конструкторы
	int X, Y;									//Координаты мыши
	virtual ~clStarSystem();
	clStarSystem();
	//данные-члены	
	int iIDSystem;								//Идентификатор
	float fZoomForMap;
	float fZoomTex;
	float fScreenWidth;							//Ширина игрового экрана
	float fScreenHeight;						//Высота игрового экрана
	vector<clBigStar> vecBigStars;				//Вектор звезд	
	vector<clPlanet> vecPlanets;				//Вектор планет
	vector<clButtonMainMenu> vecButtons;		//Вектор кнопок
	//"set" функции-члены	
	void SetName(char _chName[25]);
	void SetXY(int _X, int _Y);					//Задать координаты мыши
	//"get" функции-члены
	char *GetName();
	//другие функции-члены	
	void InitializeButtons();					//Инициализация кнопок
	void Update();
	void DrawMap();								//Отрисовка системы на карте

};
//---------------------------------------------------------------------------
#endif