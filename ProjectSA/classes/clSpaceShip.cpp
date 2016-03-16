/*---------------------------------------------------------------------------
==== Класс "clSpaceShip" ====

---------------------------------------------------------------------------*/

//#define _CRT_SECURE_NO_WARNINGS

//---------------------------------------------------------------------------
#include "clSpaceShip.h"

//!!!!!!!!!!!!!!!!!!!!!! деструктор и конструкторы !!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
clSpaceShip::clSpaceShip()
{
	clObject::clObject();
	SetName("SpaceShip");
	fPositionCoef = 100.0;
	bHPchange = true;
	bInteractive = true;
	fAngle = -90.0;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	floatmax = 1000000;
	iForsageCoeff = 20;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	iTypeShip = 0;					
	iFaction = 0;
	iShipFaction = 0;				//Фракция конструкторов корабля
	iShipRace = 0;					//Раса конструкторов корабля
	chModelShip = new char[50];	
	SetModelShip("model SpaceShip");
	chShip = new char[25];
	chSpeed = new char[25];
	chHull = new char[25];
	chShield = new char[25];
	iReactorCellBasic = 5;
	iReactorCellMax = 5;			
	iReactorCellCur = 5;			
	fSignature = 5.0;		
	fSpeedCoeff = 1.0;
	fSpeedMax = 100.0;				
	fSpeedCur = 0.0;
	fSpeedTMP = 0.5;
	fManoeuvrability = 1.0;			
	fCargoBasic = 50.0;					
	fSensorResolution = 5.0;		
	fSensorRange = 100.0;				
	bShieldEnabled = true;
	fSpeedTMP = 0.0;
	bSpeedUp = false;
	bMoveLeft = false;
	bMoveRight = false;
	bDriveForsage = false;
	
	bActiveDriveTop = false;
	bActiveDriveMain = false;
	bActiveDriveLeft = false;
	bActiveDriveRight = false;
	bActiveDriveAngleToLeft = false;
	bActiveDriveAngleToRight = false;

	bCollisionSun = false;
	bCollisionPlanet = false;
	fCollisionCoef = 1.0;

	bThisPlayer = false;
	bMapCoordTarget = false;
	fMapCoordTargetX = 0.0;
	fMapCoordTargetY = 0.0;
	
	iSPmax = 100;
	iSPcur = 100;
	iAlphaShield = 255;
	iAlphaShip = 255;

	iColorDrive = _LightBLUE_;

	circleCircle.cX = fXpos + (fWidth / 2 / fPositionCoef);
	circleCircle.cY = fYpos + (fHeight / 2 / fPositionCoef);
	circleCircle.Radius = fWidth/ 2.0 / fPositionCoef;

	ChangeSP(0);
	
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!! SET-функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
void clSpaceShip::SetSPmax(int _iSPmax)
{
	iSPmax = _iSPmax;
	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::SetSPcur(int _iSPcur)
{
	iSPcur = _iSPcur;
	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::SetModelShip(char _chModelShip[50])
{
	strcpy(chModelShip, _chModelShip);
	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::SetShip(char _chShip[25])
{
	strcpy(chShip, _chShip);
	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::SetSpeed(char _chSpeed[25])
{
	strcpy(chSpeed, _chSpeed);
	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::SetHull(char _chHull[25])
{
	strcpy(chHull, _chHull);
	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::SetShield(char _chShield[25])
{
	strcpy(chShield, _chShield);
	return;
}
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!! GET-функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
int clSpaceShip::GetSPmax()
{
	return iSPmax;
}
//---------------------------------------------------------------------------
int clSpaceShip::GetSPcur()
{
	return iSPcur;
}
//---------------------------------------------------------------------------
char *clSpaceShip::GetModelShip()
{
	return chModelShip;
}
//---------------------------------------------------------------------------
char *clSpaceShip::GetShip()
{
	return chShip;
}
//---------------------------------------------------------------------------
char *clSpaceShip::GetSpeed()
{
	return chSpeed;
}
//---------------------------------------------------------------------------
char *clSpaceShip::GetHull()
{
	return chHull;
}
//---------------------------------------------------------------------------
char *clSpaceShip::GetShield()
{
	return chShield;
}
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!! Другие функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
bool clSpaceShip::Collision(oeCircle _circleCircle)
{
	return Col_Circle(&circleCircle, &_circleCircle);
}
//---------------------------------------------------------------------------
void clSpaceShip::CollisionSun(oeCircle _circleCircle)
{
	bCollisionSun = Collision(_circleCircle);
	if (bCollisionSun)
		fCollisionCoef = 0.25;
	else if (!bCollisionPlanet)
		fCollisionCoef = 1.0;

	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::CollisionPlanet(oeCircle _circleCircle)
{
	bCollisionPlanet = Collision(_circleCircle);
	if (bCollisionPlanet)
		fCollisionCoef = 0.5;
	else if (!bCollisionSun)
		fCollisionCoef = 1.0;

	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::ActivatedForsage()
{
	//Если форсаж вкл, то функция отключает форсаж и нормализует скорость
	if (bDriveForsage)
	{
		fSpeedCur = fSpeedMax * 2.0;
		bSpeedUp = false;
		fSpeedTMP = fSpeedMax;
	}

	bDriveForsage = !bDriveForsage;

	if (fSpeedCur < fSpeedMax * 0.99)
	{
		bDriveForsage = false;
	}

	return;
}
//---------------------------------------------------------------------------
int clSpaceShip::ChangeSP(int _iSPdelta)
{
	//Если броня (HP) может уменьшаться, то и щит (SP) тоже может
	if (bHPchange)
	{
		iSPcur -= _iSPdelta;
	}
	//Обновляем данные прозрачности щита
	//Вычисляем текущий процент щита
	int iTMPShield = iSPcur / (iSPmax / 100);
	//iAlphaShield = (float)255 * (float)iTMPShield * (float)0.01;
	iAlphaShield = (float)220 * (float)iTMPShield * (float)0.01; 		//первое число - максимальная Альфа для щита
	
	return iSPcur;
}
//---------------------------------------------------------------------------
float clSpaceShip::ChangeSpeed(float _fSpeedDelta)
{
	if (_fSpeedDelta == 100)
	{
		bSpeedUp = true;
		fSpeedTMP = fSpeedMax;
		return fSpeedTMP;
	}
	
	_fSpeedDelta = fSpeedMax / 100 * _fSpeedDelta;

	if (_fSpeedDelta > 0)
	{
		bSpeedUp = true;
		if ((fSpeedTMP) <= fSpeedMax - _fSpeedDelta)
			fSpeedTMP += _fSpeedDelta;
	}
	else if (_fSpeedDelta < 0)
	{
		bSpeedUp = false;
		if (fSpeedTMP >= -(fSpeedMax * 0.15) - _fSpeedDelta)
			fSpeedTMP += _fSpeedDelta;
	}
	else if (_fSpeedDelta == 0)
	{
		if (bDriveForsage)
			fSpeedCur = fSpeedMax * 2.0;
		bDriveForsage = false;
		bSpeedUp = false;
		fSpeedTMP = _fSpeedDelta;
	}

	return fSpeedTMP;
}
//---------------------------------------------------------------------------
void clSpaceShip::MoveToLeft()
{
	bMoveLeft = true;
	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::MoveToRight()
{
	bMoveRight = true;
	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::AngleToLeft()
{
	fAngle -= 1.0 * fManoeuvrability * fCollisionCoef;
	bActiveDriveAngleToLeft = true;

	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::AngleToRight()
{
	fAngle += 1.0 * fManoeuvrability * fCollisionCoef;
	bActiveDriveAngleToRight = true;

	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::DrawPoppupWindow(int _i)
{	
	char chtmpText[250];
	switch (iTypeShip)
	{
	case _XS_:
		sprintf_s(chtmpText, "|XS| %s", chModelShip);
		break;
	case _S_:
		sprintf_s(chtmpText, "|S| %s", chModelShip);
		break;
	case _M_:
		sprintf_s(chtmpText, "|M| %s", chModelShip);
		break;
	case _L_:
		sprintf_s(chtmpText, "|L| %s", chModelShip);
		break;
	case _XL_:
		sprintf_s(chtmpText, "|XL| %s", chModelShip);
		break;
	default:
		sprintf_s(chtmpText, "|N/A| %s", chModelShip);
		break;
	}
	int itmpInt = 60;
	float fWidthName;
	fWidthName = Text_GetWidth(*(fntFont), chtmpText, 1, 0);
	
	//Сравниваем длину Модели корабля и его Названия
	if ( fWidthName < Text_GetWidth(*(fntFont), chName, 1, 0) )
		fWidthName = Text_GetWidth(*(fntFont), chName, 1, 0) - itmpInt + 10; //+10 - это для кавычек

	//Ширина и высота контекстного окна
	int itmpWidth = itmpInt + fWidthName + 12;
	int itmpHeight = 150;

	//Изменение точек начала отрисовки окна в зависимости от расположения к верхнему лев. углу
	if (iX - itmpWidth < 0)
		iX += itmpWidth;
	if (iY - itmpHeight < 0)
		iY += itmpHeight;

	//Рисуем рамочку и центральный прозрачный фон
	Pr2D_Rect(iX - itmpWidth, iY - itmpHeight, itmpWidth, itmpHeight, _LightBLUE_, 255, PR_DEFAULT);	
	Pr2D_Rect(iX - itmpWidth + 1, iY - itmpHeight + 1, itmpWidth - 2, itmpHeight - 2, _LightBLUE_, 255, PR_DEFAULT);
	Pr2D_Pixel(iX - itmpWidth - 1, iY - itmpHeight, _LightBLUE_, 255);	//исправление пустой клетки
	Pr2D_Pixel(iX - itmpWidth, iY - itmpHeight + 1, _LightBLUE_, 255);	//исправл. пустой клетки

	Pr2D_Rect(iX - itmpWidth + 3, iY - itmpHeight + 4, itmpWidth - 8, itmpHeight - 8, _LightBLUE_, 200, PR_FILL);

	//Формируем заголовки
	//sprintf_s(	chtmpText, "корабль: %s\nкорпус: %d/%d\nщиты: %d/%d", chName, iHPcur, iHPmax, iSPcur, iSPmax);
	sprintf_s(chtmpText, "%s:\n%s:\n%s:\n%s:\n", chShip, chHull, chShield, chSpeed);

	//Заголовки
	Text_Draw(	*(fntFont),							// Наш идентификатор шрифта
				iX - itmpWidth + 3 + 2,				// Координаты
				iY - itmpHeight + 4 + 16,			// Координаты
				chtmpText,							// Сам текст
				1.0,								// Коэффициент увеличения
				0,									// Дополнительное растояние между символами
				255,								// Альфа
				_WHITE_);							// цвет

	//Название корабля
	sprintf_s(chtmpText, "\"%s\"", chName);
	Text_Draw(	*(fntFont),							// Наш идентификатор шрифта
				iX - itmpWidth + 3 + 2,				// Координаты
				iY - itmpHeight + 4,				// Координаты
				chtmpText,							// Сам текст
				1.0,								// Коэффициент увеличения
				0,									// Дополнительное растояние между символами
				255,								// Альфа
				_WHITE_);							// цвет

	//Текст:
	switch (iTypeShip)
	{
	case _XS_:
		sprintf_s(chtmpText, "|XS| %s", chModelShip);
		break;
	case _S_:
		sprintf_s(chtmpText, "|S| %s", chModelShip);
		break;
	case _M_:
		sprintf_s(chtmpText, "|M| %s", chModelShip);
		break;
	case _L_:
		sprintf_s(chtmpText, "|L| %s", chModelShip);
		break;
	case _XL_:
		sprintf_s(chtmpText, "|XL| %s", chModelShip);
		break;
	default:
		sprintf_s(chtmpText, "|N/A| %s", chModelShip);
		break;
	}	
	Text_Draw(*(fntFont),
		iX - itmpWidth + 3 + 2 + itmpInt,
		iY - itmpHeight + 4 + 16,
		chtmpText, 1.0, 0, 255, _WHITE_);

	sprintf_s(	chtmpText, "%d/%d", iHPcur, iHPmax);
	Text_Draw(*(fntFont),
		iX - itmpWidth + 3 + 2 + itmpInt,
		iY - itmpHeight + 4 + 16 + 16,
		chtmpText, 1.0, 0, 255, _RED_);

	sprintf_s(	chtmpText, "%d/%d", iSPcur, iSPmax);
	Text_Draw(*(fntFont),
		iX - itmpWidth + 3 + 2 + itmpInt,
		iY - itmpHeight + 4 + 32 + 16,
		chtmpText, 1.0, 0, 255, _ShieldBLUE_);

	sprintf_s(chtmpText, "%0.2f/%0.2f", /*(int)*/fSpeedCur*fCollisionCoef, /*(int)*/fSpeedMax);
	Text_Draw(*(fntFont),
		iX - itmpWidth + 3 + 2 + itmpInt,
		iY - itmpHeight + 4 + 48 + 16,
		chtmpText, 1.0, 0, 255, _WHITE_);


	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::Draw()
{	
	//Фокус
	bFocus = false;
	if (iX > fXpos * fZoom && iX < (fXpos + fWidth) * fZoom)
		if (iY > fYpos * fZoom && iY < (fYpos + fHeight) * fZoom)
			bFocus = true;

	//Название
	if (bViewInterface)
	{
		DrawName();

		//Рисуем окружность при маленьком масштабе
		if (fZoom < 0.4 && bViewInterface)
		{
			Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 0.9) * fZoom + 1, _LightBLUE_, 255, 32, PR_DEFAULT);
			Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 0.9) * fZoom + 2, _LightBLUE_, 255, 32, PR_DEFAULT);
		}

	}

	//Рисуем работающий двигатель
	DrawDrive();

	//Рисуем корпус корабля
	ASprite_Draw(*(ptObject), fXpos*fZoom, fYpos*fZoom, fWidth*fZoom, fHeight*fZoom, iAniN, iAlphaShip, fAngle, FX_DEFAULT);
	//Рисуем щит, если он активен
	if (bShieldEnabled)
		ASprite_Draw(*(ptShield), fXpos*fZoom, fYpos*fZoom, fWidth*fZoom, fHeight*fZoom, iAniN, iAlphaShield, fAngle, FX_DEFAULT);

	//Рисуем путь до цели
	if (bViewInterface)
		DrawMapCoordTarget();

	//Контекстное окно если курсор на объекте
	if (bViewInterface && bFocus)
	{
		DrawPoppupWindow(0);
	}

	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::DrawName()
{
	//Пишем название корабля
	char chtmpText[250];

	switch (iTypeShip)
	{
	case _XS_:
		sprintf_s(chtmpText, "|XS| %s", chModelShip);
		break;
	case _S_:
		sprintf_s(chtmpText, "|S| %s", chModelShip);
		break;
	case _M_:
		sprintf_s(chtmpText, "|M| %s", chModelShip);
		break;
	case _L_:
		sprintf_s(chtmpText, "|L| %s", chModelShip);
		break;
	case _XL_:
		sprintf_s(chtmpText, "|XL| %s", chModelShip);
		break;
	default:
		sprintf_s(chtmpText, "|N/A| %s", chModelShip);
		break;
	}
	
	float fWidthName;
	fWidthName = Text_GetWidth(*(fntFont), chtmpText, 1, 0);
	int iInt = 30;			//пространство между надписью корабля и кораблем

	//void Pr2D_Line( float X1, float Y1, float X2, float Y2, int Color, BYTE Alpha = 255, int Flags = PR_DEFAULT ); 
	Pr2D_Line((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 5,
		(int)(fYpos * fZoom) + 1 - iInt,
		(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) + fWidthName + 2,
		(int)(fYpos * fZoom) + 1 - iInt,
		_LightBLUE_,
		255,
		PR_DEFAULT);
	Pr2D_Line((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 5,
		(int)(fYpos * fZoom) + 2 - iInt,
		(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) + fWidthName + 2,
		(int)(fYpos * fZoom) + 2 - iInt,
		_LightBLUE_,
		255,
		PR_DEFAULT);
	Pr2D_Circle((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 5,
		(int)(fYpos * fZoom) + 1 - iInt,
		4, _LightBLUE_, 255, 32, PR_FILL);
	Pr2D_Line((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 5,
		(int)(fYpos * fZoom) + 31 - iInt,
		(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 5,
		(int)(fYpos * fZoom) - 14 - iInt,
		_LightBLUE_,
		255,
		PR_DEFAULT);
	Pr2D_Line((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 4,
		(int)(fYpos * fZoom) + 31 - iInt,
		(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 4,
		(int)(fYpos * fZoom) - 14 - iInt,
		_LightBLUE_,
		255,
		PR_DEFAULT);
	//Линия до центра корабля
	Pr2D_Line((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 4,
		(int)(fYpos * fZoom) + 31 - iInt,
		(int)((fXpos + fWidth / 2) * fZoom),
		(int)((fYpos + fHeight / 2) * fZoom),
		_LightBLUE_,
		255,
		PR_DEFAULT);
	Pr2D_Line((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 5,
		(int)(fYpos * fZoom) + 31 - iInt,
		(int)((fXpos + fWidth / 2) * fZoom) - 1,
		(int)((fYpos + fHeight / 2) * fZoom),
		_LightBLUE_,
		255,
		PR_DEFAULT);
	
	//Название
	Text_Draw(*(fntFont),					// Наш идентификатор шрифта
		(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2),	// Координаты
		(int)(fYpos * fZoom - 15) - iInt,	// Координаты
		chtmpText,							// Сам текст
		//U_IntToStr(fSpeedCur),
		1.0,								// Коэффициент увеличения
		0,									// Дополнительное растояние между символами
		255,								// Альфа
		_WHITE_);							// цвет

	//Скорость
	sprintf_s(chtmpText, "%0.2f", fSpeedCur*fCollisionCoef);
	Text_Draw(*(fntFont),					// Наш идентификатор шрифта
		(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 10 - Text_GetWidth(*(fntFont), chtmpText, 1, 0),	// Координаты
		(int)(fYpos * fZoom - 15) - iInt,	// Координаты
		chtmpText,				// Скорость в текст
		1.0,								// Коэффициент увеличения
		0,									// Дополнительное растояние между символами
		255,								// Альфа
		_WHITE_);							// цвет
	
	//HP
	//Фон
	Pr2D_Rect((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2),
		(int)(fYpos * fZoom) + 7 - iInt,
		101,
		5,
		_LightBLUE_,
		255,
		PR_FILL);
	//Черный сегмент
	Pr2D_Rect((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) + 1,
		(int)(fYpos * fZoom) + 8 - iInt,
		99,
		3,
		_BLACK_,
		255,
		PR_FILL);
	//Красный сегмент
	Pr2D_Rect((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) + 1,
		(int)(fYpos * fZoom) + 8 - iInt,
		((iHPcur * 100) / (iHPmax)) - 1,
		3,
		_RED_,
		255,
		PR_FILL);

	//SP
	//Фон
	Pr2D_Rect((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2),
		(int)(fYpos * fZoom) + 17 - iInt,
		101,
		5,
		_LightBLUE_,
		255,
		PR_FILL);
	//Черный сегмент
	Pr2D_Rect((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) + 1,
		(int)(fYpos * fZoom) + 18 - iInt,
		99,
		3,
		_BLACK_,
		255,
		PR_FILL);
	//Синий сегмент
	Pr2D_Rect((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) + 1,
		(int)(fYpos * fZoom) + 18 - iInt,
		((iSPcur * 100) / (iSPmax)) - 1,
		3,
		_ShieldBLUE_,
		255,
		PR_FILL);




	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::DrawDrive()
{
	//Pr2D_Rect(float X, float Y, float Width, float Height, int Color, BYTE Alpha = 255, int Flags = PR_FILL);
	//Pr2D_Circle(float cX, float cY, float Radius, int Color, BYTE Alpha = 255, int Quality = 32, int Flags = PR_DEFAULT);
	if (fSpeedCur > 0.01)
		ASprite_Draw(*(ptDrvM), fXpos*fZoom, fYpos*fZoom, fWidth*fZoom, fHeight*fZoom, iAniN, 200, fAngle, FX_DEFAULT);
	if (fSpeedCur < -0.01)
		ASprite_Draw(*(ptDrvT), fXpos*fZoom, fYpos*fZoom, fWidth*fZoom, fHeight*fZoom, iAniN, 200, fAngle, FX_DEFAULT);

	if (bActiveDriveMain)
		ASprite_Draw(*(ptDrvM), fXpos*fZoom, fYpos*fZoom, fWidth*fZoom, fHeight*fZoom, iAniN, 200, fAngle, FX_DEFAULT);
	if (bActiveDriveTop)
		ASprite_Draw(*(ptDrvT), fXpos*fZoom, fYpos*fZoom, fWidth*fZoom, fHeight*fZoom, iAniN, 200, fAngle, FX_DEFAULT);

	if (bDriveForsage)
	{
		ASprite_Draw(*(ptDrvM), fXpos*fZoom, fYpos*fZoom, fWidth*fZoom, fHeight*fZoom, iAniN, 200, fAngle, FX_DEFAULT);
	}

	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::DrawMapCoordTarget()
{
	if (!bMapCoordTarget)
		return;

	//Линия до цели
	Pr2D_Line(	(fXpos + fWidth/2) * fZoom,
				(fYpos + fHeight/2) * fZoom, 
				(fMapCoordTargetX + (fXpos/fPositionCoef - fXposGlob)) * fPositionCoef * fZoom,
				(fMapCoordTargetY + (fYpos/fPositionCoef - fYposGlob)) * fPositionCoef * fZoom,
				_LightBLUE_, 255, PR_DEFAULT);

	//метка на цели
	Pr2D_Circle((fMapCoordTargetX + (fXpos / fPositionCoef - fXposGlob)) * fPositionCoef * fZoom,
				(fMapCoordTargetY + (fYpos / fPositionCoef - fYposGlob)) * fPositionCoef * fZoom,
				5, _LightBLUE_, 255, 32, PR_FILL);

	Pr2D_Circle((fMapCoordTargetX + (fXpos / fPositionCoef - fXposGlob)) * fPositionCoef * fZoom,
				(fMapCoordTargetY + (fYpos / fPositionCoef - fYposGlob)) * fPositionCoef * fZoom, 
				150*fZoom, _LightBLUE_, 255, 32, PR_DEFAULT);
	Pr2D_Circle((fMapCoordTargetX + (fXpos / fPositionCoef - fXposGlob)) * fPositionCoef * fZoom,
				(fMapCoordTargetY + (fYpos / fPositionCoef - fYposGlob)) * fPositionCoef * fZoom,
				149 * fZoom, _LightBLUE_, 255, 32, PR_DEFAULT);
	Pr2D_Circle((fMapCoordTargetX + (fXpos / fPositionCoef - fXposGlob)) * fPositionCoef * fZoom,
				(fMapCoordTargetY + (fYpos / fPositionCoef - fYposGlob)) * fPositionCoef * fZoom, 
				148 * fZoom, _LightBLUE_, 255, 32, PR_DEFAULT);

	//метка на корабле игрока
	Pr2D_Circle((fXpos + fWidth / 2) * fZoom,
				(fYpos + fHeight / 2) * fZoom,
				5, _LightBLUE_, 255, 32, PR_FILL);


	//star0->fXpos = (star0->fXposGlob + (shpPlayer->fXpos / fPositionCoef - shpPlayer->fXposGlob)) * fPositionCoef;
	//star0->fYpos = (star0->fYposGlob + (shpPlayer->fYpos / fPositionCoef - shpPlayer->fYposGlob)) * fPositionCoef;

	return;
}
//---------------------------------------------------------------------------
void clSpaceShip::Update()
{
	//Проверяем угол поворота на корректность (-360; 360)
	AngleValidation();

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//Проверяем расстояние на переполнение FLOAT
	if (fXposGlob < -floatmax || fXposGlob > floatmax || fYposGlob < -floatmax || fYposGlob > floatmax)
	{
		bActiveDriveMain = false;
		bActiveDriveTop = false;

		bDriveForsage = false;

		fSpeedTMP = 0;
		fSpeedCur = 0;

		return;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//Меняем скорость	
	if (bSpeedUp)
	{
		bActiveDriveMain = true;
		bActiveDriveTop = false;

		if (fSpeedTMP > 0)
		{
			fSpeedCur += fSpeedTMP * fInertia / 10;
		}
		if (fSpeedTMP < 0)
		{
			fSpeedCur -= fSpeedTMP * fInertia / 10;
		}
		if (fSpeedTMP == 0)
		{
			fSpeedCur -= fSpeedCur * fInertia / 10;
		}
		
		if (fSpeedCur > fSpeedTMP && fSpeedTMP != 0)
		{
			fSpeedCur = fSpeedTMP;
		}

		if (fSpeedCur > -0.01 && fSpeedCur < 0.01 && fSpeedTMP == 0)
			bActiveDriveMain = false;
	}
	if (!bSpeedUp)
	{
		bActiveDriveMain = false;
		bActiveDriveTop = true;

		if (fSpeedTMP > 0)
		{
			fSpeedCur -= fSpeedTMP * fInertia / 10;
		}
		if (fSpeedTMP < 0)
		{
			fSpeedCur += fSpeedTMP * fInertia / 10;
		}
		if (fSpeedTMP == 0)
		{
			fSpeedCur -= fSpeedCur * fInertia / 10;
		}
				
		if (fSpeedCur < fSpeedTMP && fSpeedTMP != 0)
		{
			fSpeedCur = fSpeedTMP;
		}
		if (fSpeedCur < fSpeedTMP)
		{
			bActiveDriveMain = true;
		}
		if (fSpeedCur == fSpeedTMP && fSpeedTMP > 0)
		{
			bActiveDriveTop = false;
		}
		if (fSpeedCur == fSpeedTMP && fSpeedTMP == 0)
		{
			bActiveDriveMain = false;
		}

		if (fSpeedCur > -0.01 && fSpeedCur < 0.01 && fSpeedTMP == 0)
			bActiveDriveTop = false;
		
		if (bDriveForsage)
			bActiveDriveTop = false;
	}
	if (fSpeedCur > -0.01 && fSpeedCur < 0.01 && fSpeedTMP == 0)
	{
		bActiveDriveMain = false;
		bActiveDriveTop = false;
	}

	//Форсаж
	if (bDriveForsage)
		fSpeedCur = fSpeedMax * iForsageCoeff;

	//Передвижение ("15" - коэффициент деления скорости корабля для каждого "обновления")
	fXposGlob = fXposGlob - M_Cos(fAngle + 180) * (fSpeedCur / 15 / fPositionCoef) * fCollisionCoef;
	fYposGlob = fYposGlob - M_Sin(fAngle + 180) * (fSpeedCur / 15 / fPositionCoef) * fCollisionCoef;

	//Передвижение вбок
	if (bMoveLeft)
	{
		fXposGlob = fXposGlob - M_Cos((int)fAngle + 90) * (fSpeedMax * 0.15 / 15 / fPositionCoef) * fCollisionCoef;
		fYposGlob = fYposGlob - M_Sin((int)fAngle + 90) * (fSpeedMax * 0.15 / 15 / fPositionCoef) * fCollisionCoef;

		bActiveDriveMain = true;
		bActiveDriveTop = true;
		bMoveLeft = false;
	}
	if (bMoveRight)
	{
		fXposGlob = fXposGlob - M_Cos((int)fAngle + 270) * (fSpeedMax * 0.15 / 15 / fPositionCoef) * fCollisionCoef;
		fYposGlob = fYposGlob - M_Sin((int)fAngle + 270) * (fSpeedMax * 0.15 / 15 / fPositionCoef) * fCollisionCoef;

		bActiveDriveMain = true;
		bActiveDriveTop = true;
		bMoveRight = false;
	}

	//анимация маневровых двигателей при поворотах/рыскании
	if (bActiveDriveAngleToLeft || bActiveDriveAngleToRight)
	{
		bActiveDriveMain = true;
		bActiveDriveTop = true;

		bActiveDriveAngleToLeft = false;
		bActiveDriveAngleToRight = false;
	}

	//Обновляем информацио о достижении цели MapCoordTarget
	if (bMapCoordTarget)
	{
		DrawMapCoordTarget();

		if (M_Distance(fXposGlob + (fWidth / 2 / fPositionCoef), fYposGlob + (fHeight / 2 / fPositionCoef), fMapCoordTargetX, fMapCoordTargetY) < 200 / fPositionCoef)
		{
			bMapCoordTarget = false;

			//ChangeHP(35);
		}
	}
	
	//Обновляем данные структуры для коллизий
	circleCircle.cX = fXposGlob + (fWidth / 2 / fPositionCoef);
	circleCircle.cY = fYposGlob + (fHeight / 2 / fPositionCoef);
	circleCircle.Radius = fWidth / 2.0 / fPositionCoef;

	iAniN += iAniRand;

	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------