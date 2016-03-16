/*---------------------------------------------------------------------------
==== Класс "clObject" ====
Класс объектов. Базовый класс в игре.
Включает HP объекта, признаки интерактивности, скорость,
коэффициент гравитации, дельты (изменения) положения и т.д.
---------------------------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS

//---------------------------------------------------------------------------
#include "clObject.h"

//!!!!!!!!!!!!!!!!!!!!!! деструктор и конструкторы !!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
clObject::clObject()
{
	iID = 0;
	chName = new char[25];
	iHPmax = 100;
	iHPcur = 100;
	fSpeed = 0.0;
	fHeight = 0.0;
	fWidth = 0.0;
	fGravity = 0.0;
	bHPchange = false;
	bInteractive = false;
	bViewInterface = true;
	fFreezingPoint = -50;
	fBoilingPoint = 250;
	fPositionCoef = 1.0;
	bFocus = false; 
	bCollision = false;
	fXpos = 0.0;
	fYpos = 0.0;
	fXposGlob = 0.0;
	fYposGlob = 0.0;
	fZoom = 1.0;
	//fMoveUp = 0.0;
	fMoveDown = 0.0;
	//fMoveLeft = 0.0;
	fMoveRight = 0.0;
	fTemp = 20.0;
	fAngle = 0.0;
	iAniN = 1;
	
	//задаем случайный первый кадр анимации, что бы объекты анимироваись по-разному
	iAniRand = rand() % 5 + 1;
	
	return;
}
//---------------------------------------------------------------------------
clObject::clObject(unsigned int _iID)
{
	clObject();
	iID = _iID;
	return;
}
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!! SET-функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
void clObject::SetID(unsigned int _iID)
{
	iID = _iID;
	return;
}
//---------------------------------------------------------------------------
void clObject::SetName(char _chName[25])
{
	strcpy(chName, _chName);
	return;
}
//---------------------------------------------------------------------------
void clObject::SetHPMax(int _iHPmax)
{
	iHPmax = _iHPmax;
	return;
}
//---------------------------------------------------------------------------
void clObject::SetHPcur(int _iHPcur)
{
	iHPcur = _iHPcur;
	return;
}
//---------------------------------------------------------------------------
void clObject::SetSpeed(float _fSpeed)
{
	fSpeed = _fSpeed;
	return;
}
//---------------------------------------------------------------------------
void clObject::SetHeight(float _fHeight)
{
	fHeight = _fHeight;
	return;
}
//---------------------------------------------------------------------------
void clObject::SetWidth(float _fWidth)
{
	fWidth = _fWidth;
	return;
}
//---------------------------------------------------------------------------
void clObject::SetGravity(float _fGravity)
{
	fGravity = _fGravity;
	return;
}
//---------------------------------------------------------------------------
void clObject::SetHPchange(bool _bHPchange)
{
	bHPchange = _bHPchange;
	return;
}
//---------------------------------------------------------------------------
void clObject::SetInteractive(bool _bInteractive)
{
	bInteractive = _bInteractive;
	return;
}
//---------------------------------------------------------------------------
void clObject::SetFreezingPoint(float _fFreezingPoint)
{
	fFreezingPoint = _fFreezingPoint;
	return;
}
//---------------------------------------------------------------------------
void clObject::SetBoilingPoint(float _fBoilingPoint)
{
	fBoilingPoint = _fBoilingPoint;
	return;
}
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!! GET-функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
unsigned int clObject::GetID()
{
	return iID;
}
//---------------------------------------------------------------------------
char *clObject::GetName()
{
	return chName;
}
//---------------------------------------------------------------------------
int clObject::GetHPMax()
{
	return iHPmax;
}
//---------------------------------------------------------------------------
int clObject::GetHPcur()
{
	return iHPcur;
}
//---------------------------------------------------------------------------
float clObject::GetSpeed()
{
	return fSpeed;
}
//---------------------------------------------------------------------------
float clObject::GetHeight()
{
	return fHeight;
}
//---------------------------------------------------------------------------
float clObject::GetWidth()
{
	return fWidth;
}
//---------------------------------------------------------------------------
float clObject::GetGravity()
{
	return fGravity;
}
//---------------------------------------------------------------------------
bool clObject::GetHPchange()
{
	return bHPchange;
}
//---------------------------------------------------------------------------
bool clObject::GetInteractive()
{
	return bInteractive;
}
//---------------------------------------------------------------------------
float clObject::GetFreezingPoint()
{
	return fFreezingPoint;
}
//---------------------------------------------------------------------------
float clObject::GetBoilingPoint()
{
	return fBoilingPoint;
}
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!! Другие функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
void clObject::SetXY(float _fXpos, float _fYpos)
{
	fXpos = _fXpos;
	fYpos = _fYpos;
	return;
}
//---------------------------------------------------------------------------
void clObject::SetXYGlob(float _fXposGlob, float _fYposGlob)
{
	fXposGlob = _fXposGlob;
	fYposGlob = _fYposGlob;

	return;
}
//---------------------------------------------------------------------------
void clObject::SetXYcursor(int _iX, int _iY)
{
	iX = _iX;
	iY = _iY;
	return;
}
//---------------------------------------------------------------------------
int clObject::ChangeHP(int _iHPdelta)
{
	if (bHPchange)
	{
		iHPcur -= _iHPdelta;
	}
	return iHPcur;
}
//---------------------------------------------------------------------------
void clObject::AngleValidation()
{
	if (fAngle >= 360)
		fAngle = 0;
	if (fAngle <= -360)
		fAngle = 0;

	return;
}
//---------------------------------------------------------------------------
void clObject::Update()
{
	//AngleValidation();

	if (bInteractive)
	{
		/*fXposGlob += fSpeed*fMoveRight;
		fYposGlob += fSpeed*fMoveDown;
		fMoveDown = 0;
		fMoveRight = 0;*/		

		//Передвижение
		fXposGlob = fXposGlob - M_Cos(fAngle + 90) * (fSpeed / fPositionCoef);
		fYposGlob = fYposGlob - M_Sin(fAngle + 90) * (fSpeed / fPositionCoef);

		//fMoveDown += fGravity;
	}
	iAniN += iAniRand;
	
	

	return;
}
//---------------------------------------------------------------------------
void clObject::Draw()
{
	/*
	void ASprite_Draw( PTexture Tex, float X, float Y, float Width, float Height, int FrameNow, int Alpha = 255, float Angle = 0, int Flags = FX_DEFAULT ); 
	*/
	ASprite_Draw(*(ptObject), fXpos * fZoom, fYpos * fZoom, fWidth * fZoom, fHeight * fZoom, iAniN, 255, fAngle, FX_DEFAULT);

	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------