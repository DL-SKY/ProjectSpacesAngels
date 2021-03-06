﻿/*---------------------------------------------------------------------------
==== Класс "clBigStar" ====

---------------------------------------------------------------------------*/

//#define _CRT_SECURE_NO_WARNINGS

//---------------------------------------------------------------------------
#include "clBigStar.h"

//!!!!!!!!!!!!!!!!!!!!!! деструктор и конструкторы !!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!! SET-функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!! GET-функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!! Другие функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
bool clBigStar::CollisionPlayer(oeCircle _circleCircle)
{
	//if (Col_AABBInCircle(&_circleCircle, &circleCircle))
	//if (Col_Circle(&_circleCircle, &circleCircle))
	if (Col_Circle(&circleCircle, &_circleCircle))
		bCollisionPlayer = true;
	/*if (Col_CircleInCircle(&_circleCircle, &circleCircle))
		bCollisionPlayer = true;*/

	else
		bCollisionPlayer = false;


	return bCollisionPlayer;
}
//---------------------------------------------------------------------------
void clBigStar::DrawPoppupWindow(int _i)
{
	//Ширина и высота контекстного окна
	/*int itmpWidth = 150;
	int itmpHeight = 200;

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
	Pr2D_Rect(iX - itmpWidth + 3, iY - itmpHeight + 4, itmpWidth - 8, itmpHeight - 8, _LightBLUE_, 150, PR_FILL);*/

	return;
}
//---------------------------------------------------------------------------
void clBigStar::SSpriteDraw(float X, float Y, float Width, float Height, int Alpha, float Angle, int Flags)
{
	SSprite_Draw(*(ptObject), X, Y, Width, Height, Alpha, Angle, Flags);
	SSprite_Draw(*(ptObject), X - Width / 2 * 0.5, Y - Height / 2 * 0.5, Width + Width*0.5, Height + Height*0.5, 100, Angle * 2, Flags);
		
	return;
}
//---------------------------------------------------------------------------
void clBigStar::Draw()
{
	//Фокус
	bFocus = false;
	if (iX > fXpos * fZoom && iX < (fXpos + fWidth) * fZoom)
		if (iY > fYpos * fZoom && iY < (fYpos + fHeight) * fZoom)
			bFocus = true;

	//Градиент солнечной короны
	Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 1.1) * fZoom, iColour, iAlpha, 32, PR_FILL);
	Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 1.2) * fZoom, iColour, iAlpha, 32, PR_FILL);
	Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 1.3) * fZoom, iColour, iAlpha, 32, PR_FILL);
	Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 1.4) * fZoom, iColour, iAlpha, 32, PR_FILL);
	Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 1.5) * fZoom, iColour, iAlpha, 32, PR_FILL);
	Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 1.6) * fZoom, iColour, iAlpha, 32, PR_FILL);
	Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 1.7) * fZoom, iColour, iAlpha, 32, PR_FILL);
	Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 1.8) * fZoom, iColour, iAlpha, 32, PR_FILL);
	Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 1.9) * fZoom, iColour, iAlpha, 32, PR_FILL);
	Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 2.0) * fZoom, iColour, iAlpha, 32, PR_FILL);
	Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 2.1) * fZoom, iColour, iAlpha, 32, PR_FILL);

	//Рисуем звезду: корона
	ASprite_Draw(*(ptObject), (fXpos - fWidth / 2 * 0.1) * fZoom, (fYpos - fWidth / 2 * 0.1) * fZoom, (fWidth + fWidth * 0.1) * fZoom, (fHeight + fWidth * 0.1) * fZoom, iAniN, 100, fAngle * 2.0, FX_DEFAULT);
	//Название
	if (bViewInterface)
	{
		DrawName();
	}
	//Рисуем звезду: космический объект
	ASprite_Draw(*(ptObject), fXpos * fZoom, fYpos * fZoom, fWidth * fZoom, fHeight * fZoom, iAniN, 255, fAngle, FX_DEFAULT);

	//Рамка
	/*if (bCollisionPlayer && bViewInterface)
	{
		Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 2.1) * fZoom + 1, _LightBLUE_, 200, 32, PR_DEFAULT);
		Pr2D_Circle((fXpos + fWidth / 2) * fZoom, (fYpos + fWidth / 2) * fZoom, (fWidth / 2 * 2.1) * fZoom + 2, _LightBLUE_, 200, 32, PR_DEFAULT);
	}*/	

	//Контекстное окно если курсор на объекте
	if (bViewInterface && bFocus)
	{
		DrawPoppupWindow(0);
	}

	return;
}
//---------------------------------------------------------------------------
void clBigStar::DrawName()
{
	//Пишем название звезды
	float fWidthName;
	fWidthName = Text_GetWidth(*(fntFont), chName, 1, 0);

	/*Pr2D_Rect(	(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 1,
				(int)((fYpos - fWidth / 2 * 0.1) * fZoom - 15) + 1,
				fWidthName + 1,
				14,
				_LightBLUE_, 200, PR_FILL);*/

	//void Pr2D_Line( float X1, float Y1, float X2, float Y2, int Color, BYTE Alpha = 255, int Flags = PR_DEFAULT ); 
	Pr2D_Line(	(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 5,
				(int)((fYpos - fWidth / 2 * 0.1) * fZoom) + 1,
				(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) + fWidthName + 2,
				(int)((fYpos - fWidth / 2 * 0.1) * fZoom) + 1,
				_LightBLUE_,
				255,
				PR_DEFAULT	);
	Pr2D_Line(	(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 5,
				(int)((fYpos - fWidth / 2 * 0.1) * fZoom) + 2,
				(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) + fWidthName + 2,
				(int)((fYpos - fWidth / 2 * 0.1) * fZoom) + 2,
				_LightBLUE_,
				255,
				PR_DEFAULT);
	Pr2D_Circle((int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 5,
				(int)((fYpos - fWidth / 2 * 0.1) * fZoom) + 1,
				4, _LightBLUE_, 255, 32, PR_FILL);
	Pr2D_Line(	(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 5,
				(int)((fYpos - fWidth / 2 * 0.1) * fZoom) + 1,
				(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 5,
				(int)((fYpos - fWidth / 2 * 0.1) * fZoom) - 14,
				_LightBLUE_,
				255,
				PR_DEFAULT);
	Pr2D_Line(	(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 4,
				(int)((fYpos - fWidth / 2 * 0.1) * fZoom) + 1,
				(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 4,
				(int)((fYpos - fWidth / 2 * 0.1) * fZoom) - 14,
				_LightBLUE_,
				255,
				PR_DEFAULT);
	//Линия до центра Звезды
	Pr2D_Line(	(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 5,
				(int)((fYpos - fWidth / 2 * 0.1) * fZoom) + 1,
				(int)((fXpos + fWidth / 2) * fZoom),
				(int)((fYpos + fHeight / 2) * fZoom),
				_LightBLUE_,
				255,
				PR_DEFAULT);
	Pr2D_Line(	(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2) - 4,
				(int)((fYpos - fWidth / 2 * 0.1) * fZoom) + 1,
				(int)((fXpos + fWidth / 2) * fZoom) - 1,
				(int)((fYpos + fHeight / 2) * fZoom),
				_LightBLUE_,
				255,
				PR_DEFAULT);



	Text_Draw(*(fntFont),						// Наш идентификатор шрифта
		(int)((fXpos + fWidth / 2) * fZoom - (int)fWidthName / 2),	// Координаты
		(int)((fYpos - fWidth / 2 * 0.1) * fZoom - 15),			// Координаты
		chName,								// Сам текст
		1.0,								// Коэффициент увеличения
		0,									// Дополнительное растояние между символами
		255,								// Альфа
		_WHITE_);							// цвет

	return;
}
//---------------------------------------------------------------------------
void clBigStar::Update()
{
	/*if (bAlphaUp)
	{
		if (iAlpha > 20)
			bAlphaUp = false;
		else
			iAlpha++;
	}
	else
	{		
		if (iAlpha < 10)
			bAlphaUp = true;
		else
			iAlpha--;
	}*/
	
	//Поворот звезды
	fAngle += 0.05;
	AngleValidation();

	//Обновляем данные структуры для коллизий
	/*circleCircle.cX = (fXposGlob + fWidth / 2) / fPositionCoef;
	circleCircle.cY = (fYposGlob + fWidth / 2) / fPositionCoef;
	circleCircle.Radius = (fWidth / 2) / fPositionCoef;*/
	
	circleCircle.cX = fXposGlob + (fWidth / 2.0 / fPositionCoef);
	circleCircle.cY = fYposGlob + (fHeight / 2.0 / fPositionCoef);
	//2.1 - коэффициент радиуса действия притяжения Солнца
	circleCircle.Radius = /*коэфф*/2.1/*коэфф*/ * (fWidth / 2.0 / fPositionCoef);
	
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------