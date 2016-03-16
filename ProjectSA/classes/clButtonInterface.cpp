/*---------------------------------------------------------------------------
==== Класс "clButtonMainMenu" ====

---------------------------------------------------------------------------*/

//#define _CRT_SECURE_NO_WARNINGS

//---------------------------------------------------------------------------
#include "clButtonInterface.h"

//!!!!!!!!!!!!!!!!!!!!!! деструктор и конструкторы !!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
clButtonInterface::clButtonInterface()
{
	clButtonMainMenu::clButtonMainMenu();
	ptObject = new PTexture();
	//ptObject = (&)Tex_CreateZero(0, 0, PR_DEFAULT);
	chKey = new char[11];
	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!! SET-функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
void clButtonInterface::SetKey(char _chKey[11])
{
	strcpy(chKey, _chKey);
	return;
}
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!! GET-функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
char *clButtonInterface::GetKey()
{
	return chKey;
}
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!! Другие функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
void clButtonInterface::Draw()
{
	bFocus = false;
	
	if (!bEnabled)
		iAlpha = 100;
	else
		iAlpha = 255;
	
	//Рисуем рамку кнопки	
	Pr2D_Rect(fXpos, fYpos, fWidth, 1, _LightBLUE_, iAlpha, PR_FILL);
	Pr2D_Rect(fXpos+fWidth-1, fYpos, 1, fHeight, _LightBLUE_, iAlpha, PR_FILL);
	Pr2D_Rect(fXpos, fYpos+fHeight-1, fWidth, 1, _LightBLUE_, iAlpha, PR_FILL);
	Pr2D_Rect(fXpos, fYpos, 1, fHeight, _LightBLUE_, iAlpha, PR_FILL);
	//Стандартом рисуем прозрачную середину
	Pr2D_Rect(fXpos+3, fYpos+3, fWidth-6, fHeight-6, _LightBLUE_, 100, PR_FILL);
	
	//Рисуем центр не прозрачным, если курсор на кнопке	
	if (bEnabled)
	{		
		if (iX > fXpos && iX < fXpos+fWidth)
			if (iY > fYpos && iY < fYpos+fHeight)
			{
				Pr2D_Rect(fXpos + 3, fYpos + 3, fWidth - 6, fHeight - 6, _LightBLUE_, 200, PR_FILL);
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