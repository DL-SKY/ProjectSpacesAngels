//---------------------------------------------------------------------------
#ifndef clSpaceShipH
#define clSpaceShipH
//---------------------------------------------------------------------------
//#include <iostream>
//#include "..\\OMEGA_functions.h"
#include <vector>

#include "clObject.h"


//---------------------------------------------------------------------------
/*
//Структура
struct SpaceShipStruct
{
	int iTypeShip;				//Тип космического корабля (грузовой, истребитель и пр.)
	int iFaction;				//Текущая фракция
	char *chModelShip;			//Модель корабля
	
	//Реактор. Имеет количество "ячеек", которые можно распределять между системами корабля
	int iReactorCellMax;		//Реактор, ко-во ячеек максимум
	int iReactorCellCur;		//Реактор, ко-во ячеек текущее
	
	//Сигнатура
	float fSignature;			//Размер сигнатуры
	
	//Двигатель. Максимальная скорость. Маневренность.
	float fSpeedMax;			//Скорость максимальная
	float fSpeedCur;			//Скорость текущая
	float fManoeuvrability;		//Коэффициент маневренности
	
	//Грузовой отсек (м3).
	float fCargo;				//Вместимость м3 грузового отсека
	
	//Сенсоры. Максимальная дальность. Коэффициент скорости наведения (скорость наведения зависит от сигнатуры).
	float fSensorResolution;	//Мин. размер сигнатуры-цели для наведения без штрафов (скорость наведения = fSignature(цель) / fSensorResolution(сенсор))
	float fSensorRange;			//Дальность работы сенсоров
	
};
*/
//---------------------------------------------------------------------------
class clSpaceShip : virtual public clObject
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
	float floatmax;					//Максимальное значение разрешенного растояния в космосе (от центра)

	int iSPmax;						//Максимальное кол-во ShieldPoint
	int iSPcur;						//Текущее кол-во ShieldPoint
	int iAlphaShield;				//прозрачность текстуры щита
	char *chModelShip;				//Модель корабля
	char *chShip;					//Слово "Корабль"
	char *chHull;					//Слово "Корпус"
	char *chShield;					//Слово "Щиты"
	char *chSpeed;					//Слово "Скорость"
	//"set" функции-члены
	//"get" функции-члены   
	//другие функции-члены

/*открытые функции-члены и данные-члены
доступны везде*/
public:
	//деструктор и конструкторы
	virtual ~clSpaceShip() { /*delete chName;*/ };
	clSpaceShip();
	//данные-члены
	int iTypeShip;					//Тип космического корабля (грузовой, истребитель и пр.) Типоразмер
	int iFaction;					//Текущая фракция
	int iShipFaction;				//Фракция конструкторов корабля
	int iShipRace;					//Раса конструкторов корабля
	int iReactorCellBasic;			//Реактор, ко-во ячеек по умолчанию
	int iReactorCellMax;			//Реактор, ко-во ячеек максимум
	int iReactorCellCur;			//Реактор, ко-во ячеек текущее
	float fSignature;				//Размер сигнатуры
	float fSignatureBasic;			//Размер сигнатуры базовый
	float fSpeedCoeff;				//Множитель скорости корабля (макс скор = множитель * скор.модуля двигателя)
	float fSpeedMax;				//Скорость максимальная
	float fSpeedCur;				//Скорость текущая
	float fManoeuvrability;			//Коэффициент маневренности (скорость поворота)
	float fManoeuvrabilityBasic;	//Коэффициент (базовый) маневренности (скорость поворота)
	float fInertia;					//Коэффициент инерции (скорость изменения текущей скорости)
	float fInertiaBasic;			//Коэффициент (Базовый) инерции (скорость изменения текущей скорости)
	float fCargoBasic;				//Вместимость м3 грузового отсека корабля
	float fCargoCur;				//загруженность м3 грузового отсека текущее
	float fCargoMax;				//Вместимость м3 грузового отсека макс (с учетом модулей)
	float fSensorResolution;		//Мин. размер сигнатуры-цели для наведения без штрафов (скорость наведения = fSignature(цель) / fSensorResolution(сенсор))
	float fSensorRange;				//Дальность работы сенсоров
	bool bShieldEnabled;			//Активен ли щит
	float fSpeedTMP;				//Буфер скорости, к которому сртемится текущая скорость
	bool bSpeedUp;					//Маркер повышения скорости (колесо мыши вперед)
	bool bMoveLeft;					//Маркер движения влево
	bool bMoveRight;				//Маркер движения вправо
	bool bDriveForsage;				//Вкл/выкл режим форсажа
	int iForsageCoeff;				//множитель скорости при форсаже
	
	bool bActiveDriveTop;			//маркер активности верхнего маневрового двигателя
	bool bActiveDriveMain;			//маркер активности основного двигателя
	bool bActiveDriveLeft;			//маркер активности левого маневрового двигателя
	bool bActiveDriveRight;			//маркер активности правого маневрового двигателя
	bool bActiveDriveAngleToLeft;	//маркер активности маневровых двигателей для поворота налево
	bool bActiveDriveAngleToRight;	//маркер активности маневровых двигателей для поворота направо

	bool bThisPlayer;				//Маркер игрока
	bool bMapCoordTarget;			//Макркер включенного наведения на космический объект

	float fMapCoordTargetX;			//X-координата выбранного космообъекта
	float fMapCoordTargetY;			//Y-координата выбранного космообъекта

	bool bCollisionSun;				//Маркер пересечения с солнцем
	bool bCollisionPlanet;				//Маркер пересечения с планетой
	float fCollisionCoef;			//множитель действия гравитации небесных тел

	int iAlphaShip;					//Прозрачность текстуры корабля	
	int iColorDrive;				//Цвет шлейфа от двигателя
	
	oeCircle circleCircle;			//Структура окружности для коллизий
	/*struct oeCircle
	{
	float X;
	float Y;
	float Radius;
	};*/
	//oeRect rectRect;				//Структура прямоугольника для коллизий
	/*struct oeRect
	{ float X; float Y; float Width; float Height; };*/
	//int iAniN;					//Текущий кадр при анимации *наследуется
	//PTexture *ptObject;			//Указатель на текстуру корабля *наследуется
	PTexture *ptShield;				//Указатель на текстуру щита
	PTexture *ptDrvM;				//Указатель на текстуру основного двигателя
	PTexture *ptDrvT;				//Указатель на текстуру верхнего двигателя

	//"set" функции-члены	
	void SetSPmax(int _iSPmax);
	void SetSPcur(int _iSPcur);
	void SetModelShip(char _chModelShip[50]);
	void SetShip(char _chShip[25]);
	void SetSpeed(char _chSpeed[25]);
	void SetHull(char _chHull[25]);
	void SetShield(char _chShield[25]);
		
	//"get" функции-члены
	int GetSPmax();
	int GetSPcur();
	char *GetModelShip();
	char *GetShip();
	char *GetSpeed();
	char *GetHull();
	char *GetShield();
	
	//другие функции-члены	
	bool Collision(oeCircle _circleCircle);
	void CollisionSun(oeCircle _circleCircle);
	void CollisionPlanet(oeCircle _circleCircle);
	void ActivatedForsage();
	int ChangeSP(int _iSPdelta);
	float ChangeSpeed(float _fSpeedDelta);
	void MoveToLeft();
	void MoveToRight();
	void AngleToLeft();
	void AngleToRight();
	void DrawPoppupWindow(int _i);
	void Draw();
	void DrawName();
	void DrawDrive();
	void DrawMapCoordTarget();
	void Update();
};
//---------------------------------------------------------------------------
#endif