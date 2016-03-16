/*
Использование в Main.CPP:

	#include "classes\\clObject.cpp
	clObject *objOne = new clObject();
	void OMEGAInit()
	{
		objOne->SetWidth(100);
		objOne->SetHeight(100);
		objOne->SetXY(100, 100);
		objOne->ptObject = &ptLoad00;
	}
	void OMEGADraw()
	{
		objOne->iAniN = N;
		objOne->Draw();
	}
*/

//---------------------------------------------------------------------------
#ifndef clObjectH
#define clObjectH
//---------------------------------------------------------------------------
//типоразмеры
#define _XS_ int(1)		//оч.мал.
#define _S_ int(2)		//мал.
#define _M_ int(3)		//сред.
#define _L_ int(4)		//бол.
#define _XL_ int(5)		//оч.бол.
//---------------------------------------------------------------------------

#include <iostream>
#include <math.h>
#include <time.h>
//#include "..\\OMEGA_code.cpp"
#include "..\\OMEGA_functions.h"

class clObject
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
	unsigned int iID;	//Идентификатор
	char *chName;		//Символьное название
	int iHPmax;			//Максимальное кол-во HP
	int iHPcur;			//Текущее кол-во HP
	float fSpeed;		//Скорость
	float fHeight;		//Высота
	float fWidth;		//Ширина
	float fGravity;		//"Гравитация", коэф. изменения движения fMove***	
	bool bHPchange;		//Признак возможности изменения HP (true = изм.возможно)
	bool bInteractive;	//Признак интерактивности (true = интерактивный, с объектом возможны действия)	
	float fFreezingPoint;//Температура замерзания
	float fBoilingPoint;//Температура горения/кипения
	int iX;				//X-координату курсора мыши
	int iY;				//Y-координату курсора мыши
	
	//"set" функции-члены
	//"get" функции-члены
	//другие функции-члены

/*открытые функции-члены и данные-члены
доступны везде*/
public:
	//деструктор и конструкторы
	virtual ~clObject() { /*delete chName;*/ };
	clObject();
	clObject(unsigned int _iID);
	
	//данные-члены
	float fPositionCoef;//Коэффициент изменения позиции относительно отображения на экране
	bool bFocus;		//Фокус на объекте
	bool bCollision;	//Коллизия (перекрытие др. объектом)
	bool bViewInterface;//Признак видимости интерфейса (целый ли дисплей)
	float fXpos;		//X-координата на экране
	float fYpos;		//Y-координата на экране
	float fXposGlob;	//X-координата в пространстве
	float fYposGlob;	//Y-координата в пространстве
	float fZoom;		//Коэффициент увеличения
			// *fMove*** - коэффициент перемещения по координатам на следующей отрисовке
			// * при обновлении (Update) коэф. могут поменяться (н-р, из-за гравитации fGravity)
	//float fMoveUp;		//Движение вверх*
	float fMoveDown;	//Движение вниз*, перемещение по оси Y
	//float fMoveLeft;	//Движение влево*
	float fMoveRight;	//Движение вправо*, перемещение по оси X
	float fTemp;		//Текущая температура объекта
	float fAngle;		//Угол поворота
	int iAniN;			//Текущий кадр при анимации
	int iAniRand;		//Модификатор случайности анимации
	PTexture *ptObject;	//Указатель на текстуру
	PFont2D *fntFont;
	
	//"set" функции-члены
	void SetID(unsigned int _iID);
	void SetName(char _chName[25]);
	void SetHPMax(int _iHPmax);
	void SetHPcur(int _iHPcur);
	void SetSpeed(float _fSpeed);
	void SetHeight(float _fHeight);
	void SetWidth(float _fWidth);
	void SetGravity(float _fGravity);
	void SetHPchange(bool _bHPchange);
	void SetInteractive(bool _bInteractive);
	void SetFreezingPoint(float _fFreezingPoint);
	void SetBoilingPoint(float _fBoilingPoint);
	
	//"get" функции-члены
	unsigned int GetID();
	char *GetName();
	int GetHPMax();
	int GetHPcur();
	float GetSpeed();
	float GetHeight();
	float GetWidth();
	float GetGravity();
	bool GetHPchange();
	bool GetInteractive();
	float GetFreezingPoint();
	float GetBoilingPoint();
	
	//другие функции-члены	
	void SetXY(float _fXpos, float _fYpos);
	void SetXYGlob(float _fXposGlob, float _fYposGlob);
	void SetXYcursor(int _iX, int _iY);
	int ChangeHP(int _iHPdelta);
	void AngleValidation();
	void AngleToLeft();
	void AngleToRight();
	void Update();
	void Draw();
};
//---------------------------------------------------------------------------
#endif