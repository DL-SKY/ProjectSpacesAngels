/*---------------------------------------------------------------------------
==== Класс "clStarSystem" ====

---------------------------------------------------------------------------*/

//#define _CRT_SECURE_NO_WARNINGS

//---------------------------------------------------------------------------
#include "clStarSystem.h"

//!!!!!!!!!!!!!!!!!!!!!! деструктор и конструкторы !!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
clStarSystem::~clStarSystem()
{

	return;
}
//---------------------------------------------------------------------------
clStarSystem::clStarSystem()
{
	/*for (int i = 0; i < iColSmallStar; i++)
	{
	clSmallStar *clSS = new clSmallStar();
	clSS->SetXYGlob(rand() % (int)iWidth / fGameZoom, rand() % (int)iHeight / fGameZoom);
	clSS->SetXY(clSS->fXposGlob, clSS->fYposGlob);
	clSS->SetWidth(rand() % 5 + 1);
	clSS->SetSpeed(rand() % 20 + 1);
	clSS->fZoom = fGameZoom;

	vecSmallStars.push_back(*clSS);
	}

	//обновляем вектор звезд
	vector<clSmallStar>::iterator i = vecSmallStars.begin();
	while (i != vecSmallStars.end())
	{
		i->fXposGlob -= iWidth / 2;
		i->fYposGlob -= iHeight / 2;
		++i;
	}*/

	iCol = 0;
	chName = new char[25];
	fZoomForMap = 0.1;
	fZoomTex = 0.04;

	X = 0; Y = 0;
	iIDSystem = 0;
	fScreenWidth = 0.0;	
	fScreenHeight = 0.0;

	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!! SET-функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
void clStarSystem::SetName(char _chName[25])
{
	strcpy(chName, _chName);
	return;
}
//---------------------------------------------------------------------------
void clStarSystem::SetXY(int _X, int _Y)
{
	X = _X;
	Y = _Y;
	return;
}
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!!! GET-функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
char *clStarSystem::GetName()
{
	return chName;
}
//---------------------------------------------------------------------------
//!!!!!!!!!!!!!!!!!!!!!!! Другие функции-члены !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//---------------------------------------------------------------------------
void clStarSystem::InitializeButtons()
{
	clButtonMainMenu *btnTMP;	//временная кнопка для создания вектора кнопок

	iCol = 3; //1 - название системы, 2 - координаты коробля игрока
	vecButtons.clear();

	//Звезды
	vector<clBigStar>::iterator iBS = vecBigStars.begin();
	while (iBS != vecBigStars.end())
	{
		btnTMP = new clButtonMainMenu();
		btnTMP->bEnabled = true;
		btnTMP->SetWidth(fScreenWidth * 0.2 - 4);
		btnTMP->SetHeight(30);
		//координаты кнопки
		btnTMP->SetXY(fScreenWidth * 0.1 + fScreenHeight * 0.8 + 9, (btnTMP->GetHeight() + 5)* (iCol - 1) + fScreenHeight * 0.1 + 2);
		//координаты объекта
		btnTMP->SetXYGlob(iBS->fXposGlob + iBS->GetWidth()/2/iBS->fPositionCoef, iBS->fYposGlob + iBS->GetHeight()/2/iBS->fPositionCoef);
		btnTMP->SetName(iBS->GetName());
		btnTMP->fntFont = vecBigStars[0].fntFont;		
		
		vecButtons.push_back(*btnTMP);

		++iCol;
		++iBS;
	}

	//Планеты
	vector<clPlanet>::iterator iPl = vecPlanets.begin();
	while (iPl != vecPlanets.end())
	{
		btnTMP = new clButtonMainMenu();
		btnTMP->bEnabled = true;
		btnTMP->SetWidth(fScreenWidth * 0.2 - 4);
		btnTMP->SetHeight(30);
		//координаты кнопки
		btnTMP->SetXY(fScreenWidth * 0.1 + fScreenHeight * 0.8 + 9, (btnTMP->GetHeight() + 5) * (iCol - 1) + fScreenHeight * 0.1 + 2);
		//координаты объекта
		btnTMP->SetXYGlob(iPl->fXposGlob + iPl->GetWidth()/2/iPl->fPositionCoef, iPl->fYposGlob + iPl->GetHeight()/2/iPl->fPositionCoef);
		btnTMP->SetName(iPl->GetName());
		btnTMP->fntFont = vecBigStars[0].fntFont;

		vecButtons.push_back(*btnTMP);
		
		++iCol;
		++iPl;
	}

	return;
}
//---------------------------------------------------------------------------
void clStarSystem::Update()
{
	//Передаем кнопкам координаты
	vector<clButtonMainMenu>::iterator iBt = vecButtons.begin();
	while (iBt != vecButtons.end())
	{
		iBt->SetXYcursor(X, Y);
		++iBt;
	}

	return;
}
//---------------------------------------------------------------------------
//Отрисовка системы на карте
void clStarSystem::DrawMap()
{
	float fXCentre, fYCentre;
	fXCentre = fScreenWidth * 0.1 + fScreenHeight * 0.4;
	fYCentre = fScreenHeight * 0.1 + fScreenHeight * 0.4;

	//Выводим название сектора
	//Слева
	Pr2D_Rect(	fScreenWidth * 0.1 + 2, fScreenHeight * 0.1 + 2, 
				Text_GetWidth(*(vecBigStars[0].fntFont), chName, 1, 0) + 3, 15, _LightBLUE_, 255, PR_FILL);
	Text_Draw(	*(vecBigStars[0].fntFont),
				(int)(fScreenWidth * 0.1 + 4),
				(int)(fScreenHeight * 0.1 + 2),
				chName, 1.0, 0, 255, _WHITE_);
	//Справа
	Pr2D_Rect(	fScreenWidth * 0.1 + fScreenHeight * 0.8 + 9, fScreenHeight * 0.1 + 2,
				fScreenWidth * 0.2 - 4, 15, _LightBLUE_, 255, PR_FILL);
	Text_Draw(	*(vecBigStars[0].fntFont),
				(int)(fScreenWidth * 0.1 + fScreenHeight * 0.8 + 12),
				(int)(fScreenHeight * 0.1 + 2),
				chName, 1.0, 0, 255, _WHITE_);

	//Рисуем область для карты (минус 10% с каждой стороны Экрана, учитываем, что должен быть квадрат)
	//Pr2D_Rect(fScreenWidth * 0.1, fScreenHeight * 0.1, fScreenHeight * 0.8, fScreenHeight * 0.8, _WHITE_, 150, PR_FILL);
	//Рисуем область для доп.информации 
	//Pr2D_Rect(fScreenWidth * 0.1 + fScreenHeight * 0.8 + 7, fScreenHeight * 0.1, fScreenWidth * 0.2, fScreenHeight * 0.8, _WHITE_, 150, PR_FILL);

	//Звезды
	vector<clBigStar>::iterator iBS = vecBigStars.begin();
	while (iBS != vecBigStars.end())
	{
		float X, Y;
		X = fXCentre + iBS->fXposGlob * fZoomForMap - iBS->GetWidth()*fZoomTex / 2;
		Y = fYCentre + iBS->fYposGlob * fZoomForMap - iBS->GetHeight()*fZoomTex / 2;

		//Рисуем звезду
		iBS->SSpriteDraw(	X, Y,
							iBS->GetWidth()*fZoomTex, iBS->GetHeight()*fZoomTex, 200, iBS->fAngle, FX_DEFAULT);

		float fWidthName;
		fWidthName = Text_GetWidth(*(iBS->fntFont), iBS->GetName(), 1, 0);

		//Пишем название
		Text_Draw(	*(iBS->fntFont),
					(int)(X + iBS->GetWidth()*fZoomTex / 2 - fWidthName / 2),
					(int)(Y - 20),
					iBS->GetName(), 1.0, 0, 255, _WHITE_);
	
		++iBS;
	}

	//Планеты
	vector<clPlanet>::iterator iPl = vecPlanets.begin();
	while (iPl != vecPlanets.end())
	{
		float X, Y;
		X = fXCentre + iPl->fXposGlob * fZoomForMap - iPl->GetWidth()*fZoomTex / 2;
		Y = fYCentre + iPl->fYposGlob * fZoomForMap - iPl->GetHeight()*fZoomTex / 2;

		//Рисуем плантету
		iPl->SSpriteDraw(	X, Y,
							iPl->GetWidth()*fZoomTex, iPl->GetHeight()*fZoomTex, 200, iPl->fAngle, FX_DEFAULT);

		float fWidthName;
		fWidthName = Text_GetWidth(*(iPl->fntFont), iPl->GetName(), 1, 0);

		//Пишем название
		Text_Draw(*(iPl->fntFont),
			(int)(X + iPl->GetWidth()*fZoomTex / 2 - fWidthName / 2),
			(int)(Y - 20),
			iPl->GetName(), 1.0, 0, 255, _WHITE_);

		++iPl;
	}

	//Рисуем кнопки
	vector<clButtonMainMenu>::iterator iBt = vecButtons.begin();
	while (iBt != vecButtons.end())
	{
		iBt->Draw();
		++iBt;
	}

	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------