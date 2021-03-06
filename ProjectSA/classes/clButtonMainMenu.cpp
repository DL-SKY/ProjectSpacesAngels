﻿/*---------------------------------------------------------------------------
==== Класс "clButtonMainMenu" ====

---------------------------------------------------------------------------*/

//#define _CRT_SECURE_NO_WARNINGS

//---------------------------------------------------------------------------
#include "clButtonMainMenu.h"

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
void clButtonMainMenu::Draw()
{
	bFocus = false;
	
	if (!bEnabled)
		iAlpha = 100;
	else
		iAlpha = 255;
	
	//Рисуем рамку кнопки	
	Pr2D_Rect(fXpos, fYpos, fWidth, 3, _LightBLUE_, iAlpha, PR_FILL);
	Pr2D_Rect(fXpos+fWidth-3, fYpos, 3, fHeight, _LightBLUE_, iAlpha, PR_FILL);
	Pr2D_Rect(fXpos, fYpos+fHeight-3, fWidth, 3, _LightBLUE_, iAlpha, PR_FILL);
	Pr2D_Rect(fXpos, fYpos, 3, fHeight, _LightBLUE_, iAlpha, PR_FILL);
	//Стандартом рисуем прозрачную середину
	Pr2D_Rect(fXpos+5, fYpos+5, fWidth-10, fHeight-10, _LightBLUE_, 100, PR_FILL);
	
	//Рисуем центр не прозрачным, если курсор на кнопке	
	if (bEnabled)
	{		
		if (iX > fXpos && iX < fXpos+fWidth)
			if (iY > fYpos && iY < fYpos+fHeight)
			{
				Pr2D_Rect(fXpos+5, fYpos+5, fWidth-10, fHeight-10, _LightBLUE_, 255, PR_FILL);
				bFocus = true;
			}
	}
	
	//Пишем название кнопки
	float fWidthName;
	fWidthName = Text_GetWidth(*(fntFont), chName, 1, 0);
	Text_Draw(*(fntFont),						// Наш идентификатор шрифта
			(int)fXpos + (int)fWidth/2 - (int)fWidthName/2,	// Координаты
			(int)fYpos+10,						// Координаты
			chName,								// Сам текст
			1.0,								// Коэффициент увеличения
			0,									// Дополнительное растояние между символами
			iAlpha,								// Альфа
			_WHITE_);							// цвет
	
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------