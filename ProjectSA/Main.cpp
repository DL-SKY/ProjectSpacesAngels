//---------------------------------------------------------------------------
/* Project Microsoft Visual Studio Community 2013 */
//---------------------------------------------------------------------------

/*===========================================================================
==== рабочее название Project Spase Angels ====
Игровой проект на движке OMEGA.
===========================================================================*/

#define _CRT_SECURE_NO_WARNINGS

//---------------------------------------------------------------------------
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <io.h>
#include <math.h>
#include <vector>
#include <time.h>


#include "OMEGA_code.cpp"
#include "OMEGA_functions.h"

using namespace std;

//Ресурсы
#include "resource.h"

#include "Typedef.h"
//Файл глобальных переменных конфигурации

//подключаем классы
#include "classes\\clObject.cpp"
#include "classes\\clButtonMainMenu.cpp"
#include "classes\\clButtonInterface.cpp"
#include "classes\\clSmallStar.cpp"
#include "classes\\clBigStar.cpp"
#include "classes\\clPlanet.cpp"
#include "classes\\clSpaceShip.cpp"
#include "classes\\clStarSystem.cpp"

//Заголовочный файл основного модуля
#include "Main.h"
//Файл констант
#include "Config.h"
//Файл указания файлов шрифтов
#include "Fonts.h"
//Файл глобальных переменных движка OMEGA (таймеры, шрифты, текстуры)
#include "OEngine.h"
//Файл объявления звуковых идентификаторов
#include "Sound.h"
//Файл объектов в игре (объявление экземпляров классов)
#include "Objects.h"

//---------------------------------------------------------------------------

//===========================================================================
//Глобальные перменные:

//Статус сборки
const float fStatus = _WORK_;

//Версия
const char *chVersion = "v.0.0.05 \"Ранний Рябчик\"";

//Текущее состояние (режим) отображения на экране
int iGameStatus = _ZERO_;

//Версии игры (издания) и дополнения

//===========================================================================

//---------------------------------------------------------------------------
int main()
{
	//Функция инкрементирования номера сборки
	BuildIncrement();
	//Загружаем библиотеку
	//русский язык
	if (!FileExists("OMEGA.DLL"))
	{
		ErrorLog(0);
		return 0;
	}
		LoadOMEGA("OMEGA.dll");

	//Загрузка настроек
	if (ReadConfig() == 0)
		return 0;

	//---------------
	
	//===============
	// Работа с движком OMEGA Engine
	//===============
	// Создаем таймеры
	//PTimer Timer_Create( void* OnTimer, int Interval = 1000, int Precision = 1 );
	//Обработка мыши и клвавиатуры
	MyTimer01key = Timer_Create((void*)OMEGATimer01KeyboardMouse, 10, 0);
	//анимация курсора, анимация объектов
	MyTimer02ani = Timer_Create((void*)OMEGATimer02Anumation, 200, 0);
	//обновление объектов
	MyTimer03upd = Timer_Create((void*)OMEGATimer03UpdateObject, 50, 0);

	// Назначаем "системные" процедуры
	OE_RegProcedure(SYS_LOAD, (void*)OMEGALoad);
	OE_RegProcedure(SYS_INIT, (void*)OMEGAInit);
	OE_RegProcedure(SYS_DRAW, (void*)OMEGADraw);
	OE_RegProcedure(SYS_QUIT, (void*)OMEGAQuit);

	//Задаем настройки окна	 
	/*if (iAnisotropy > U_GetMaxAnisotropy())
		iAnisotropy = U_GetMaxAnisotropy();*/
	if (iWidth > GetSystemMetrics(SM_CXSCREEN))
		iWidth = GetSystemMetrics(SM_CXSCREEN);
	if (iHeight > GetSystemMetrics(SM_CYSCREEN))
		iHeight = GetSystemMetrics(SM_CYSCREEN);

	//Фильтрация
	//Tex_SetAnisotropyLevel(iAnisotropy);
	//Настройки окна
	//void OE_SetScreenOptions( int Width, int Heigth, int BPP, int Refresh, bool FullScreen, bool WaitVSync );
	OE_SetScreenOptions(iWidth, iHeight, iBPP, iRefresh, bFullScreen, bVSync);
	//Функция OE_SetWndPosition перемещает окно в позицию X, Y.
	//void OE_SetWndPosition( int X, int Y ); 
	if (!bFullScreen)
		OE_SetWndPosition(0, 0);

	//Функция меняет OE_SetWndName заголовок окна на NewName.
	//void OE_SetWndName( char* NewName );
	switch (iLanguage)
	{
	case 643:	//русский	
		OE_SetWndName("Звездные Ангелы");;
		break;

	default:
		OE_SetWndName("The Star's Angels");;
		break;
	}
	//В зависимости от значения параметра Show, системный курсор мыши будет показан или отключен.
	//void OE_ShowCursor( bool Show );
	OE_ShowCursor(true);
			
	//Запускаем движок
	OE_Init();
	//===============

	return 1;
}
//---------------------------------------------------------------------------
void BuildIncrement()
{
	int iBuild;
	bool bResult;
		
	iBuild = 0;
	//проверяем наличие файла chFileBuildNumber
	bResult = FileExists(chFileBuildNumber);
	
	//Если файл существует, то читаем из него значение сборки
	if (bResult)
	{
		ifstream ifstreamBuild;
		ifstreamBuild.open(chFileBuildNumber);
		ifstreamBuild >> iBuild;
		ifstreamBuild.close();
	}
	else
	{
		ErrorLog(0);
		return;
	}

	//Увеличиваем значение сборки
	iBuild++;

	//Записываем новое значение
	ofstream ofstreamBuild;
	ofstreamBuild.open(chFileBuildNumber);
	ofstreamBuild << iBuild << endl << fStatus;
	ofstreamBuild.close();
	
	return;
}
//---------------------------------------------------------------------------
bool FileExists(const char *_chFileName) 
{
	//Проверяем наличие файла
	bool bResult;
	bResult = _access(_chFileName, 0) != -1;	
	return bResult;
}
//---------------------------------------------------------------------------
int ReadConfig()
{
	//На случай доработки создадим переменную-результат
	int iResult = 1;
	//Загружаем INI средствами движка OMEGA
	if (!FileExists(chFileConfig))
	{	
		iResult = 0;
		ErrorLog(0);
		return iResult;
	}
	INI_LoadFromFile((char*)chFileConfig);
	//--------------
	//Читаем настройки и присваиваем их значение переменным
	bConsole = INI_ReadKeyInt("Main", "Console");
	bFullScreen = INI_ReadKeyInt("Main", "FullScreen");
	iWidth = INI_ReadKeyInt("Main", "Width");
	iHeight = INI_ReadKeyInt("Main", "Height");
	bVSync = INI_ReadKeyInt("Main", "VSync");
	//iAnisotropy = INI_ReadKeyInt("Main", "Anisotropy");
	bSoundOn = INI_ReadKeyInt("Main", "SoundOn");
	iVolume = INI_ReadKeyInt("Main", "Volume");
	iLanguage = INI_ReadKeyInt("Main", "Language");

	if (fStatus != _RELEASE_)
		bConsole = true;

	//--------------
	return iResult;
}
//---------------------------------------------------------------------------
int LoadLocalization()
{
	char *chLocalization = new char(255);
	int iTMP = 0;

	switch (iLanguage)
	{
		case 643:	//русский	
			chLocalization = "..\\loc\\643\\localization.txt";
			break;

		default:
			chLocalization = "..\\loc\\840\\localization.txt";
			break;
	}

	//проверка существования файла локализации
	if (!FileExists(chLocalization))
	{
		ErrorLog(0);
		return 0;
	}

	ifstream ifstreamLoc;
	ifstreamLoc.open(chLocalization);
	//--------------------------------
	/*ifstreamLoc.getline(chTest1, 255);
	ifstreamLoc.getline(chTest2, 255);
	ifstreamLoc.getline(chLocal[1], 255);*/
	while (!ifstreamLoc.eof())
	{
		ifstreamLoc.getline(chLocal[iTMP], 255);
		iTMP++;
	}		
	//--------------------------------
	ifstreamLoc.close();

	//Локализация кораблей
	iTMP = 0;
	switch (iLanguage)
	{
	case 643:	//русский	
		chLocalization = "..\\loc\\643\\spaceships.txt";
		break;

	default:
		chLocalization = "..\\loc\\840\\spaceships.txt";
		break;
	}
	//проверка существования файла локализации
	if (!FileExists(chLocalization))
	{
		ErrorLog(0);
		return 0;
	}
	ifstreamLoc.open(chLocalization);
	//--------------------------------
	while (!ifstreamLoc.eof())
	{
		ifstreamLoc.getline(chLocalShip[iTMP], 255);
		iTMP++;
	}
	//--------------------------------
	ifstreamLoc.close();

	return 1;
}
//---------------------------------------------------------------------------
int LoadFonts()
{
	if (!FileExists(chFontFPS))
	{
		ErrorLog(0);
		return 0;
	}
	if (!FileExists(chFontFPSInfo))
	{
		ErrorLog(0);
		return 0;
	}

	if (!FileExists(chFontConsole))
	{
		ErrorLog(0);
		return 0;
	}
	if (!FileExists(chFontConsoleInfo))
	{
		ErrorLog(0);
		return 0;
	}

	/*if (!FileExists(chFontMain))
	{
		ErrorLog(0);
		return 0;
	}
	if (!FileExists(chFontMainInfo))
	{
		ErrorLog(0);
		return 0;
	}*/
	//-----------------------------------------------
	// Загружаем шрифт FPS
	FontFPS = Text_LoadFontFromFile((char*)chFontFPS,						// Где текстура шрифта
									(char*)chFontFPSInfo,					// Где параметры шрифта
									_BLACK_,								// Цвет прозрачности: -1 = указан в Font.tga
									TEX_DEFAULT_2D | TEX_FILTER_NEAREST);	// Для ауентичности не будем использовать фильтрацию
	// Загружаем шрифт консоли
	FontConsole = Text_LoadFontFromFile((char*)chFontConsole,				// Где текстура шрифта
									(char*)chFontConsoleInfo,				// Где параметры шрифта
									_BLACK_,								// Цвет прозрачности: -1 = указан в Font.tga
									TEX_DEFAULT_2D | TEX_FILTER_NEAREST);	// Для ауентичности не будем использовать фильтрацию
	// Загружаем основной шрифт
	FontMain = Text_LoadFontFromFile((char*)chFontMain,					// Где текстура шрифта
									(char*)chFontMainInfo,					// Где параметры шрифта
									_BLACK_,								// Цвет прозрачности: -1 = указан в Font.tga
									TEX_DEFAULT_2D | TEX_FILTER_NEAREST);	// Для ауентичности не будем использовать фильтрацию
	
	//-----------------------------------------------
	return 1;
}
//---------------------------------------------------------------------------
int LoadTextures()
{
	// Загружаем текстуры курсора
	// Прозрацный цвет в BMP в формате - BGR
	//PTexture Tex_LoadFromFile(char* FileName, int TransparentColor, int Flags = TEX_DEFAULT_2D);
	//ptCursorDefault = Tex_LoadFromFile(MAKEINTRESOURCE(IDB_BITMAP1), -1, TEX_DEFAULT_2D);
	//========================================================================
	//текстуры курсора
	//========================================================================
	if (!FileExists("..\\img\\cursors\\cursorDefault.bmp"))
	{
		ErrorLog(0);
		return 0;
	}
	ptCursorDefault = Tex_LoadFromFile("..\\img\\cursors\\cursorDefault.bmp", _TranspGREEN_, TEX_DEFAULT_2D);
	
	if (!FileExists("..\\img\\cursors\\cursorDefault.bmp"))
	{
		ErrorLog(0);
		return 0;
	}
	ptCursorDefaultA = Tex_LoadFromFile("..\\img\\cursors\\cursorDefaultA.bmp", _TranspGREEN_, TEX_DEFAULT_2D);
	Tex_SetFramesSize(ptCursorDefaultA, 32, 32);

	//========================================================================
	//текстуры 
	//========================================================================
	//BLUR
	ptBlurTex = Tex_CreateZero(512, 512, TEX_DEFAULT_2D);	// Создаем пустую текстуру среднего
															// качества для blur-эффектов
															// Сделаю замечания - разрешение по
															// горизонтале и вертикали не должно
															// превышать разрешение экрана и должно
															// быть кратно двум!!!
	// Назначаем текстуру
	FX_RadBlur_SetTex(ptBlurTex);


	//Спутник из Главного Меню
	if (!FileExists("..\\img\\objects\\MainMenuSputnik.bmp"))
	{
		ErrorLog(0);
		return 0;
	}
	ptMainMenuObject = Tex_LoadFromFile("..\\img\\objects\\MainMenuSputnik.bmp", _TranspGREEN_, TEX_DEFAULT_2D);
	Tex_SetFramesSize(ptMainMenuObject, 128, 128);
	//Планета главного меню
	if (!FileExists("..\\img\\objects\\PlanetDefault600.bmp"))
	{
		ErrorLog(0);
		return 0;
	}
	ptMainMenuPlanet = Tex_LoadFromFile("..\\img\\objects\\PlanetDefault600.bmp", _TranspGREEN_, TEX_DEFAULT_2D);
	Tex_SetFramesSize(ptMainMenuPlanet, 600, 600);
	//звезда главного меню
	if (!FileExists("..\\img\\objects\\Sun00.bmp"))
	{
		ErrorLog(0);
		return 0;
	}
	ptMainMenuStar = Tex_LoadFromFile("..\\img\\objects\\Sun00.bmp", _TranspGREEN_, TEX_DEFAULT_2D);
	Tex_SetFramesSize(ptMainMenuStar, 400, 400);
	//Название игры в Главном меню
	if (!FileExists("..\\img\\objects\\TitleForMainMenu.bmp"))
	{
		ErrorLog(0);
		return 0;
	}
	ptMainMenuTitle = Tex_LoadFromFile("..\\img\\objects\\TitleForMainMenu.bmp", _TranspGREEN_, TEX_DEFAULT_2D);

	//Интерфейс
	if (!FileExists("..\\img\\interface\\display.bmp"))
	{
		ErrorLog(0);
		return 0;
	}
	ptInterfaceDisplay = Tex_LoadFromFile("..\\img\\interface\\display.bmp", _TranspGREEN_, TEX_DEFAULT_2D);


	//Корабли
	LoadShips();
	///-------------------------------------------------------------------------------------------
	//One
	if (!FileExists("..\\img\\spaceships\\one.bmp"))
	{
		ErrorLog(0);
		return 0;
	}
	ptShipOne = Tex_LoadFromFile("..\\img\\spaceships\\one.bmp", _TranspGREEN_, TEX_DEFAULT_2D);
	Tex_SetFramesSize(ptShipOne, 150, 150);
	//Щиты
	if (!FileExists("..\\img\\spaceships\\one_m.bmp"))
	{
		ErrorLog(0);
		return 0;
	}
	Tex_LoadMaskFromFile("..\\img\\spaceships\\one_m.bmp");
	if (!FileExists("..\\img\\spaceships\\Shield.bmp"))
	{
		ErrorLog(0);
		return 0;
	}
	ptShipShield = Tex_LoadFromFile("..\\img\\spaceships\\Shield.bmp", _TranspGREEN_, TEX_USEMASK| TEX_DEFAULT_2D);
	Tex_SetFramesSize(ptShipShield, 150, 150);
	Tex_FreeMask();
	//двигатели
	if (!FileExists("..\\img\\spaceships\\one_drvm.bmp"))
	{
		ErrorLog(0);
		return 0;
	}
	ptShipOneDrvM = Tex_LoadFromFile("..\\img\\spaceships\\one_drvm.bmp", _TranspGREEN_, TEX_DEFAULT_2D);
	Tex_SetFramesSize(ptShipOneDrvM, 150, 150);

	if (!FileExists("..\\img\\spaceships\\one_drvt.bmp"))
	{
		ErrorLog(0);
		return 0;
	}
	ptShipOneDrvT = Tex_LoadFromFile("..\\img\\spaceships\\one_drvt.bmp", _TranspGREEN_, TEX_DEFAULT_2D);
	Tex_SetFramesSize(ptShipOneDrvT, 150, 150);
	///-------------------------------------------------------------------------------------------

	//Солнце
	if (!FileExists("..\\img\\objects\\sun00.bmp"))
	{
		ErrorLog(0);
		return 0;
	}
	ptBigSun00 = Tex_LoadFromFile("..\\img\\objects\\sun00.bmp", _TranspGREEN_, TEX_DEFAULT_2D);
	Tex_SetFramesSize(ptBigSun00, 400, 400);

	return 1;
}
//---------------------------------------------------------------------------
//Загрузка кораблей из INI
void LoadShips()
{
	//объявляем вспомогательные переменные
	char *chIniShipPath = new char[250];
	PTexture ptTMP;
	clSpaceShip *shpTMP = new clSpaceShip();
	int i = 0;

	WIN32_FIND_DATA wdata;							// структура для поиска файлов.    
	HANDLE hdr = FindFirstFileA("..\\ini\\spaceships\\*", &wdata);  //начало поиска        
	while (FindNextFile(hdr, &wdata))										// цикл поиска    
	{
		//if (i > 0)    desktop.ini
		if (wdata.cFileName[0] != '.')	//исключаем ошибку, связанную с файлом ".."
		{
			//формируем путь к INI-файлу корабля
			sprintf(chIniShipPath, "..\\ini\\spaceships\\%s", wdata.cFileName);
			//загружаем INI-файл корабля в память
			INI_LoadFromFile((char*)chIniShipPath);

			//заносим текстуру в вектор
			vecPTexShip.push_back(ptTMP);

			//заносим корабль в вектор
			shpTMP = new clSpaceShip();
			vecSpaceShips.push_back(*shpTMP);

			//тест-------------------------------------------
			INI_WriteKeyStr("Test", "Test", wdata.cFileName);
			INI_WriteKeyInt("Test", "Test2", i);
			INI_SaveToFile(chIniShipPath);
			//-----------------------------------------------
		}
		//считаем количество итераций
		i++;
	}
	//закрытие дескриптора поиска
	FindClose(hdr); 
	

//One
/*if (!FileExists("..\\img\\spaceships\\one.bmp"))
{
ErrorLog(0);
return 0;
}
ptShipOne = Tex_LoadFromFile("..\\img\\spaceships\\one.bmp", _TranspGREEN_, TEX_DEFAULT_2D);
Tex_SetFramesSize(ptShipOne, 150, 150);
//Щиты
if (!FileExists("..\\img\\spaceships\\one_m.bmp"))
{
ErrorLog(0);
return 0;
}
Tex_LoadMaskFromFile("..\\img\\spaceships\\one_m.bmp");
if (!FileExists("..\\img\\spaceships\\Shield.bmp"))
{
ErrorLog(0);
return 0;
}
ptShipShield = Tex_LoadFromFile("..\\img\\spaceships\\Shield.bmp", _TranspGREEN_, TEX_USEMASK| TEX_DEFAULT_2D);
Tex_SetFramesSize(ptShipShield, 150, 150);
Tex_FreeMask();
//двигатели
if (!FileExists("..\\img\\spaceships\\one_drvm.bmp"))
{
ErrorLog(0);
return 0;
}
ptShipOneDrvM = Tex_LoadFromFile("..\\img\\spaceships\\one_drvm.bmp", _TranspGREEN_, TEX_DEFAULT_2D);
Tex_SetFramesSize(ptShipOneDrvM, 150, 150);

if (!FileExists("..\\img\\spaceships\\one_drvt.bmp"))
{
ErrorLog(0);
return 0;
}
ptShipOneDrvT = Tex_LoadFromFile("..\\img\\spaceships\\one_drvt.bmp", _TranspGREEN_, TEX_DEFAULT_2D);
Tex_SetFramesSize(ptShipOneDrvT, 150, 150);*/

	return;
}
//---------------------------------------------------------------------------
//Загрузка звездных систем из INI
void LoadSystems()
{

	return;
}
//---------------------------------------------------------------------------
void LoadStartMenuObject()
{
	//Музыка
	if (!FileExists("..\\snd\\Main menu\\The Descent.wav"))
	{
		ErrorLog(0);
		OE_Quit();
	}
	//PSound Snd_LoadFromFile( char* FileName, int BufferCount ); 
	sndStartMenuTheme = Snd_LoadFromFile("..\\snd\\Main menu\\The Descent.wav", 1);
	// Зацикленно воспроизводим, 0 - по умолчанию
	iIDStartMenuTheme = Snd_Play(	sndStartMenuTheme,	// Идентификатор звука
									0,					// Значение Pan
									VOLUME(iVolume),	// "Громксоть"
									0,					// Частота проигрывания
									true);				// Зацикленно ли играть
	
	//Подготавливаем Космический Объект Главного меню
	objMainMenuObject->SetWidth(128);
	objMainMenuObject->SetHeight(128);
	objMainMenuObject->SetXYGlob(iWidth / 2, iHeight / 2);
	objMainMenuObject->SetXY(iWidth / 2, iHeight / 2);
	objMainMenuObject->SetGravity(0.0);				//GRAVITY
	objMainMenuObject->SetSpeed(1.0);				//SPEED
	objMainMenuObject->ptObject = &ptMainMenuObject;//TEXTURE
	objMainMenuObject->SetInteractive(true);

	objMainMenuPlanet->SetWidth(150);
	objMainMenuPlanet->SetHeight(150);
	objMainMenuPlanet->SetXYGlob(100, 50);
	objMainMenuPlanet->SetXY(100, 50);
	objMainMenuPlanet->ptObject = &ptMainMenuPlanet;//TEXTURE
	//objMainMenuPlanet->SetXYcursor(X, Y);

	starMainMenuStar->SetName("Звезда STARTMENU");
	starMainMenuStar->bViewInterface = false;
	starMainMenuStar->fPositionCoef = 1;
	starMainMenuStar->fZoom = 1;
	starMainMenuStar->ptObject = &ptMainMenuStar;
	starMainMenuStar->fntFont = &FontConsole;
	starMainMenuStar->iColour = _RED_;
	starMainMenuStar->SetWidth(600);
	starMainMenuStar->SetHeight(600);
	starMainMenuStar->SetXYGlob(iWidth - 250, iHeight - 400);
	starMainMenuStar->SetXY(iWidth - 250, iHeight - 400);
	
	//Кнопки
	//1 Приодолжить игру
	btnContGame->bEnabled = false;
	btnContGame->SetWidth(250);
	btnContGame->SetHeight(36);
	btnContGame->SetXY(17, iHeight / 2);
	btnContGame->SetName(chLocal[21]);//////////////////////
	btnContGame->fntFont = &FontConsole;
	//2 Новая игра
	btnNewGame->SetWidth(250);
	btnNewGame->SetHeight(36);
	btnNewGame->SetXY(17, btnContGame->fYpos + btnContGame->GetHeight() + 5);
	btnNewGame->SetName(chLocal[22]);///////////////////////
	btnNewGame->fntFont = &FontConsole;
	//3 Загрузить
	btnLoadGame->bEnabled = false;
	btnLoadGame->SetWidth(250);
	btnLoadGame->SetHeight(36);
	btnLoadGame->SetXY(17, btnNewGame->fYpos + btnNewGame->GetHeight() + 5);
	btnLoadGame->SetName(chLocal[23]);///////////////////////
	btnLoadGame->fntFont = &FontConsole;
	//4 Настройка
	btnConfig->bEnabled = false;
	btnConfig->SetWidth(250);
	btnConfig->SetHeight(36);
	btnConfig->SetXY(17, btnLoadGame->fYpos + btnLoadGame->GetHeight() + 5);
	btnConfig->SetName(chLocal[2]);///////////////////////
	btnConfig->fntFont = &FontConsole;
	//5 Авторы
	btnAbout->bEnabled = false;
	btnAbout->SetWidth(250);
	btnAbout->SetHeight(36);
	btnAbout->SetXY(17, btnConfig->fYpos + btnConfig->GetHeight() + 5);
	btnAbout->SetName(chLocal[25]);///////////////////////
	btnAbout->fntFont = &FontConsole;
	//6 Выход
	btnExit->SetWidth(250);
	btnExit->SetHeight(36);
	btnExit->SetXY(17, btnAbout->fYpos + btnAbout->GetHeight() + 5);
	btnExit->SetName(chLocal[6]);///////////////////////
	btnExit->fntFont = &FontConsole;

	//Звезды на фон
	/*clSmallStar *clSS = new clSmallStar();
	clSS->SetXY(250, 250);
	clSS->SetWidth(5);
	clSS->SetSpeed(5);
	vecSmallStars.push_back(*clSS);

	clSS->SetXY(300, 300);
	clSS->SetWidth(10);
	clSS->SetSpeed(2);
	vecSmallStars.push_back(*clSS);*/

	//Глобальные переменные
	fGameZoom = 1.0;
	iIDCurStarSystem = 0;

	srand( time(NULL) );
	int iColSmallStar = (rand() % ((int)iHeight / 6)) + ((int)iHeight / 16) + 10;
	for (int i = 0; i < iColSmallStar; i++)
	{
		clSmallStar *clSS = new clSmallStar();
		clSS->SetXYGlob(rand() % (int)iWidth / fGameZoom, rand() % (int)iHeight / fGameZoom);
		clSS->SetXY(clSS->fXposGlob, clSS->fYposGlob);
		clSS->SetWidth(rand() % 5 + 1);
		clSS->SetSpeed(rand() % 20 + 1);
		clSS->fZoom = fGameZoom;

		vecSmallStars.push_back(*clSS);
	}

	return;
}
//---------------------------------------------------------------------------
//Подготовка к построению окна "Игра: космос"
void LoadGameSpaceObject()
{
	//Корабль игрока
	shpPlayer->SetName("Я-Так-Назвал-Корабль");
	shpPlayer->SetModelShip("model Корабль Игрока");
	shpPlayer->bThisPlayer = true;
	shpPlayer->SetShip(chLocal[26]);
	shpPlayer->SetSpeed(chLocal[27]);
	shpPlayer->SetHull(chLocal[28]);
	shpPlayer->SetShield(chLocal[29]);
	shpPlayer->iTypeShip = _S_;
	shpPlayer->fntFont = &FontConsole;
	shpPlayer->fPositionCoef = fPositionCoef;
	shpPlayer->fZoom = fGameZoom;
	shpPlayer->ptObject = &ptShipOne;
	shpPlayer->ptShield = &ptShipShield;
	shpPlayer->ptDrvM = &ptShipOneDrvM;
	shpPlayer->ptDrvT = &ptShipOneDrvT;
	shpPlayer->SetWidth(150);
	shpPlayer->SetHeight(150);
	shpPlayer->fSpeedMax = 100;
	//shpPlayer->fSpeedMax = FLT_MAX;
	//shpPlayer->SetXYGlob(0.0, 0.0);
	//shpPlayer->SetXYGlob(0.0 - shpPlayer->GetWidth() / 2, 0.0 - shpPlayer->GetHeight() / 2);
	shpPlayer->SetXYGlob(0.0 - shpPlayer->GetWidth() / 2 / fPositionCoef, 0.0 - shpPlayer->GetHeight() / 2 / fPositionCoef);
	//shpPlayer->SetXY(iWidth / 2 - shpPlayer->GetWidth() / 2, iHeight / 2 - shpPlayer->GetHeight() / 2);
	shpPlayer->fManoeuvrability = 0.1;
	shpPlayer->fInertia = 0.25;
	//shpPlayer->ChangeSP(-55);
	//shpOne->fAngle = -90.0; "правильный угол по умолчанию" -90 добавлен в конструктор класса корабля.
	shpPlayer->bShieldEnabled = true;
	//shpPlayer->iColorDrive = _LightBLUE_;
	//-------------
	shpPlayer->bMapCoordTarget = false;
	shpPlayer->fMapCoordTargetX = 35 + (600/ 2 / fPositionCoef);
	shpPlayer->fMapCoordTargetY = - 10 + (600/ 2 / fPositionCoef);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//Сделать через цикл, когда будет реализован файл звездных систем
	
	//P.S. Дистанция видимых объектов - в пределах 2500 от центра
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//объекты
	star0 = new clBigStar();
	star0->SetName("Звезда 0");
	star0->fPositionCoef = fPositionCoef;
	star0->fZoom = fGameZoom;
	star0->ptObject = &ptBigSun00;
	star0->fntFont = &FontConsole;	
	star0->iColour = _RED_;
	star0->SetWidth(800);
	star0->SetHeight(800);
	//star0->SetXYGlob(0.0 - star0->GetWidth() / 2, 0.0 - star0->GetHeight() / 2);
	//star0->SetXYGlob(0.0, 0.0);
	star0->SetXYGlob(0.0 - star0->GetWidth() / 2 / fPositionCoef, 0.0 - star0->GetHeight() / 2 / fPositionCoef);

	plPlanet0 = new clPlanet();
	plPlanet0->SetName("Планета 0");
	plPlanet0->fPositionCoef = fPositionCoef;
	plPlanet0->fZoom = fGameZoom;
	plPlanet0->ptObject = &ptMainMenuPlanet;
	plPlanet0->fntFont = &FontConsole;
	plPlanet0->iColour = _ColdBLUE_;
	plPlanet0->SetWidth(600);
	plPlanet0->SetHeight(600);
	plPlanet0->SetXYGlob(0, -2500);

	ssysTempStarSys->SetName("Система TEST");
	ssysTempStarSys->vecBigStars.push_back(*star0);
	ssysTempStarSys->vecPlanets.push_back(*plPlanet0);
	ssysTempStarSys->iIDSystem = 1;
	ssysTempStarSys->fScreenWidth = iWidth;
	ssysTempStarSys->fScreenHeight = iHeight;
	//!!!
	//Удалить после добавления цикла
	plPlanet0 = new clPlanet();
	plPlanet0->SetName("Планета 1");
	plPlanet0->fPositionCoef = fPositionCoef;
	plPlanet0->fZoom = fGameZoom;
	plPlanet0->ptObject = &ptMainMenuPlanet;
	plPlanet0->fntFont = &FontConsole;
	plPlanet0->iColour = _ColdBLUE_;
	plPlanet0->SetWidth(300);
	plPlanet0->SetHeight(300);
	plPlanet0->SetXYGlob(155, 597);
	ssysTempStarSys->vecPlanets.push_back(*plPlanet0);

	plPlanet0 = new clPlanet();
	plPlanet0->SetName("Планета 2");
	plPlanet0->fPositionCoef = fPositionCoef;
	plPlanet0->fZoom = fGameZoom;
	plPlanet0->ptObject = &ptMainMenuPlanet;
	plPlanet0->fntFont = &FontConsole;
	plPlanet0->iColour = _ColdBLUE_;
	plPlanet0->SetWidth(1000);
	plPlanet0->SetHeight(1000);
	plPlanet0->SetXYGlob(-2140, 279);
	ssysTempStarSys->vecPlanets.push_back(*plPlanet0);

	plPlanet0 = new clPlanet();
	plPlanet0->SetName("Планета 3");
	plPlanet0->fPositionCoef = fPositionCoef;
	plPlanet0->fZoom = fGameZoom;
	plPlanet0->ptObject = &ptMainMenuPlanet;
	plPlanet0->fntFont = &FontConsole;
	plPlanet0->iColour = _ColdBLUE_;
	plPlanet0->SetWidth(500);
	plPlanet0->SetHeight(500);
	plPlanet0->SetXYGlob(2400, 1870);
	ssysTempStarSys->vecPlanets.push_back(*plPlanet0);

	plPlanet0 = new clPlanet();
	plPlanet0->SetName("Планета 4");
	plPlanet0->fPositionCoef = fPositionCoef;
	plPlanet0->fZoom = fGameZoom;
	plPlanet0->ptObject = &ptMainMenuPlanet;
	plPlanet0->fntFont = &FontConsole;
	plPlanet0->iColour = _ColdBLUE_;
	plPlanet0->SetWidth(700);
	plPlanet0->SetHeight(700);
	plPlanet0->SetXYGlob(-200.5, -1500);
	ssysTempStarSys->vecPlanets.push_back(*plPlanet0);
	//vecStarSystems.push_back(*ssysTempStarSys);
	//!!!
	ssysTempStarSys->InitializeButtons();
	vecStarSystems.push_back(*ssysTempStarSys);
	iIDCurStarSystem = 1;

	//Загружаем данные в Текущую Звездную Систему
	vector<clStarSystem>::iterator i1 = vecStarSystems.begin();
	while (i1 != vecStarSystems.end())
	{
		if (iIDCurStarSystem == i1->iIDSystem)
		{
			ssysCurStarSys->SetName(ssysTempStarSys->GetName());
			ssysCurStarSys->fScreenHeight = i1->fScreenHeight;
			ssysCurStarSys->fScreenWidth = i1->fScreenWidth;
			ssysCurStarSys->iIDSystem = i1->iIDSystem;
			ssysCurStarSys->vecBigStars = i1->vecBigStars;
			ssysCurStarSys->vecPlanets = i1->vecPlanets;
			ssysCurStarSys->vecButtons = i1->vecButtons;
			ssysCurStarSys->InitializeButtons();
		
			break;
		}
		++i1;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	//Кнопки для карты
	//1 Система
	btnSystemMap->bEnabled = true;
	btnSystemMap->SetWidth(150);
	btnSystemMap->SetHeight(36);
	btnSystemMap->SetXY(iWidth * 0.1 - 4, iHeight * 0.1 - 43);
	btnSystemMap->SetName(chLocal[30]);//////////////////////
	btnSystemMap->fntFont = &FontConsole;
	//2 Галактика
	btnGalaxyMap->bEnabled = true;
	btnGalaxyMap->SetWidth(150);
	btnGalaxyMap->SetHeight(36);
	btnGalaxyMap->SetXY(btnSystemMap->fXpos + 5 + 150, btnSystemMap->fYpos);
	btnGalaxyMap->SetName(chLocal[31]);//////////////////////
	btnGalaxyMap->fntFont = &FontConsole;
	//3 Закрыть
	btnExitCancel->bEnabled = true;
	btnExitCancel->SetWidth(150);
	btnExitCancel->SetHeight(36);
	btnExitCancel->SetXY(btnGalaxyMap->fXpos + 5 + 150, btnGalaxyMap->fYpos);
	btnExitCancel->SetName(chLocal[32]);//Закрыть
	btnExitCancel->fntFont = &FontConsole;


	//Кнопки интерфейса в космосе
	biTestBI->bEnabled = true;
	biTestBI->SetWidth(36);
	biTestBI->SetHeight(36);
	biTestBI->SetXY(12, iHeight - 52);
	biTestBI->SetName("Кнопка 1");//
	biTestBI->SetKey("1");
	biTestBI->fntFont = &FontConsole;

	//ФОН
	//обновляем вектор звезд
	vector<clSmallStar>::iterator i = vecSmallStars.begin();
	while (i != vecSmallStars.end())
	{
		i->fXposGlob -= iWidth / 2;
		i->fYposGlob -= iHeight / 2;
		++i;
	}
	
	return;
}
//---------------------------------------------------------------------------
void ErrorLog(int _iErr)
{
	if (_iErr == 0)
		return;

	return;
}
//---------------------------------------------------------------------------
void Loading(int _iLoad)
{
	switch (_iLoad)
	{
		//Начальная загрузка в момент выполнения OMEGAInit
		case 0:			
			//Только статичное изображение
			ASprite_Draw(ptLoad00, (iWidth - 128) / 2, (iHeight - 128) / 2, 128, 128, N, 255, 0, FX_DEFAULT);
			break;
		case 1:
			break;
	}
	

	return;
}
//---------------------------------------------------------------------------
//===========================================================================
//===========================================================================
//Таймер №1, мониторинг мыши и клавиатуры
void OMEGATimer01KeyboardMouse()
{
	//Постоянные действия (на все игровые статусы)
	// Cursor: Мониторим координаты курсора
	if (Mouse_Move())
	{
		SetCursor(NULL);	//Убираем курсор ОС
		X = Mouse_X();
		Y = Mouse_Y();

		if (X < 0)	X = 0;
		if (Y < 0)	Y = 0;
	}

	// Keyboard F12: Делаем скриншот
	if (Key_Press(K_F12))
	{
		if (!FileExists(chPathScreen))
		{
			ErrorLog(0);
			return;
		}
		else
			U_SnapShot((char*)chPathScreen, (char*)chFileScreen);
	}

	//Выбор события на основании игрового статуса (iGameStatus)
	switch (iGameStatus)
	{
		//Статус: начальная загрузка, OMEGAInit
		case _ZERO_:
			MouseAndKeyboardZERO();
			break;
		//Первый экран после загрузки ресурсов, Стартовое меню
		case _STARTMENU_:
			MouseAndKeyboardSTARTMENU();
			break;
		//Оено об игре
		case _ABOUT_:
			MouseAndKeyboardABOUT();
			break;
		//Окно настроек
		case _CONFIG_:
			MouseAndKeyboardCONFIG();
			break;
		//Окно "Новая игра"
		case _NEWGAME_:
			//DrawFrameCONFIG();
			break;
		//
		case _ZERO5_:
			//DrawFrameCONFIG();
			break;
		//
		case _ZERO6_:
			//DrawFrameCONFIG();
			break;
		//Окно "Загрузить"
		case _LOADGAME_:
		//DrawFrameCONFIG();
			break;
		//
		case _ZERO8_:
			//DrawFrameCONFIG();
			break;
		//Игра: Режим в космосе
		case _GAMESPACE_:
			MouseAndKeyboardSPACE();
			break;
			//Игра: Режим в космосе - КАРТА
		case _GAMESPACEMAP_:
			MouseAndKeyboardSPACEMAP();
			break;


		//По умолчанию (тестирование)
		default:
			MouseAndKeyboardDEFAULT();
			break;
	}
	
	return;
}
//---------------------------------------------------------------------------
//Таймер №2 Анимация курсора
void OMEGATimer02Anumation()
{
	// Инкрементируем текущий кадр спрайта...
	N++;
	if (N > 120)
		N = 1;

	return;
}
//---------------------------------------------------------------------------
//Таймер №3 Обновление объектов
void OMEGATimer03UpdateObject()
{
	//Инициализация итератора вектора "маленьких звезд" Главного Меню
	vector<clSmallStar>::iterator i = vecSmallStars.begin();

	switch (iGameStatus)
	{
		//Статус: начальная загрузка, OMEGAInit
		case _ZERO_:
			break;
		//Первый экран после загрузки ресурсов, Стартовое меню
		case _STARTMENU_:
			//ФИКС: исчезновение спутника
			/*if (objMainMenuObject->fXposGlob > iWidth)
				objMainMenuObject->fXposGlob = iWidth;
			if (objMainMenuObject->fXposGlob < 0)
				objMainMenuObject->fXposGlob = 0;
			if (objMainMenuObject->fYposGlob > iHeight)
				objMainMenuObject->fYposGlob = iHeight;
			if (objMainMenuObject->fYposGlob < 0)
				objMainMenuObject->fYposGlob = 0;*/
			//КонецФИКС			

			objMainMenuObject->iAniN = N;
			objMainMenuPlanet->iAniN = N;
			starMainMenuStar->iAniN = N;
			objMainMenuObject->Update();
			starMainMenuStar->Update();

			if (objMainMenuObject->GetSpeed() < 20.0)
				objMainMenuPlanet->fAngle += 0.02;
			else
				objMainMenuPlanet->fAngle += 0.8;

			if (objMainMenuPlanet->fAngle > 360.0)
				objMainMenuPlanet->fAngle = 0.0;

			btnContGame->SetXYcursor(X, Y);
			btnNewGame->SetXYcursor(X, Y);
			btnLoadGame->SetXYcursor(X, Y);
			btnConfig->SetXYcursor(X, Y);
			btnAbout->SetXYcursor(X, Y);
			btnExit->SetXYcursor(X, Y);

			//обновление вектора звезд
			while (i != vecSmallStars.end())
			{
				i->Update();
				/*if (i->alpha <= 0.05f)
					i = vecSmallStars.erase(i);
				else*/
				++i;
			}
			break;
		//Об игре
		case _ABOUT_:
			break;
		//Окно настроек
		case _CONFIG_:
			break;
		//Окно "Новая игра"
		case _NEWGAME_:
			//DrawFrameCONFIG();
			break;
		//
		case _ZERO5_:
			//DrawFrameCONFIG();
			break;
		//
		case _ZERO6_:
			//DrawFrameCONFIG();
			break;
		//Окно "Загрузить"
		case _LOADGAME_:
			//DrawFrameCONFIG();
			break;
		//
		case _ZERO8_:
			//DrawFrameCONFIG();
			break;
		//Игра: Режим в космосе
		case _GAMESPACE_:
			UpdateFrameSpace();
			break;
		//Игра: Режим в космосе - карта
		case _GAMESPACEMAP_:
			UpdateFrameSpace();
			ssysCurStarSys->SetXY(X, Y);
			ssysCurStarSys->Update();
			btnSystemMap->SetXYcursor(X, Y);
			btnGalaxyMap->SetXYcursor(X, Y);
			btnExitCancel->SetXYcursor(X, Y);
			break;

		//По умолчанию (тестирование)
		default:
			//objOne->Update();
			break;
	}	

	return;
}
//---------------------------------------------------------------------------
//Экран загрузки (действия, пока идет загрузка ресурсов в OMEGAInit)
void OMEGALoad()
{
	iGameStatus = _ZERO_;

	if (!FileExists("..\\img\\loading\\loading0.bmp"))
	{
		ErrorLog(0);
		OE_Quit();
	}
	ptLoad00 = Tex_LoadFromFile("..\\img\\loading\\loading0.bmp", _TranspGREEN_, TEX_DEFAULT_2D);
	Tex_SetFramesSize(ptLoad00, 128, 128);

	//Экран загрузки
	Loading(0);
	
	return;
}
//---------------------------------------------------------------------------
//
void OMEGAInit()
{
	// Инициализируем звуковую подсистему
	Snd_Init();		
	//Вкл/выкл звук
	Snd_Active(bSoundOn);

	//Загружаем файл локализации
	if (LoadLocalization() == 0)
		OE_Quit();
	//Загружаем шрифты
	if (LoadFonts() == 0)
		OE_Quit();
	//Загружаем текстуры
	if (LoadTextures() == 0)
		OE_Quit();

	//Консоль
	if (bConsole)
	{
		Console_SetOptions(	FontConsole,    // Задаем шрифт
							NULL,			// Если значение null, то будет фон цвета...
							0,				// указанного тут
							155,			// Альфа консоли
							_WHITE_,		// Цвет шрифта
							255);			// Альфа шрифта
		Console_Active(true);
	}
	//Console_AddString("###########################");
	//Console_AddString("# Simple console application v.1.0 #");
	//Console_AddString("###########################");
	// Регистрируем консольные команды
	Console_RegCommand("?", (void*)ConsoleHelp);
	Console_RegCommand("help", (void*)ConsoleHelp);
	Console_RegCommand("помощь", (void*)ConsoleHelp);
	//--------------------------------------------
	Console_RegCommand("armageddon", (void*)ConsoleArmageddon);
	Console_RegCommand("армагеддон", (void*)ConsoleArmageddon);
	Console_RegCommand("interface", (void*)ConsoleVisibleInterface);
	Console_RegCommand("интерфейс", (void*)ConsoleVisibleInterface);
	//--------------------------------------------
	Console_RegCommand("quit", (void*)OE_Quit);
	Console_RegCommand("выход", (void*)OE_Quit);
	Console_RegCommand("fps", (void*)ConsoleFPS);
	Console_RegCommand("фпс", (void*)ConsoleFPS);
	Console_RegCommand("russian", (void*)ConsoleLayoutRus);
	Console_RegCommand("rus", (void*)ConsoleLayoutRus);
	Console_RegCommand("английский", (void*)ConsoleLayoutEng);
	Console_RegCommand("англ", (void*)ConsoleLayoutEng);
	
	//------------------------------------------------
	//Пример использования класса clObject
	/*
	objOne->SetWidth(100);
	objOne->SetHeight(100);
	objOne->SetXY(100, 100);
	objOne->SetGravity(0.0);		//GRAVITY
	objOne->SetSpeed(1.5);			//SPEED
	objOne->ptObject = &ptLoad00;	//TEXTURE
	*/
	//------------------------------------------------

	//После завершения инициализации переменной игрового статуса
	//присваиваем значение 1: "Первый экран после загрузки ресурсов, Стартовое меню"
	iGameStatus = _STARTMENU_;
	LoadStartMenuObject();

	//Пауза
	if (fStatus != _RELEASE_)
	{
		Sleep(1000);
	}	
	/*
	if (fStatus != _RELEASE_)
		iGameStatus += -50;
	*/


	return;
}
//---------------------------------------------------------------------------
//
void OMEGADraw()
{
	//Выбор FRAME для рисования на основании Игрового статуса iGameStatus
	switch (iGameStatus)
	{
		//Статус: начальная загрузка, OMEGAInit
		case _ZERO_:
			break;
		//Первый экран после загрузки ресурсов, Стартовое меню
		case _STARTMENU_:
			DrawFrameSTARTMENU();
			break;
		//Окно "Об игре"
		case _ABOUT_:
			DrawFrameABOUT();
			break;
		//Окно настроек
		case _CONFIG_:
			DrawFrameCONFIG();
			break;
		//Окно "Новая игра"
		case _NEWGAME_:
			//DrawFrameCONFIG();
			break;
		//
		case _ZERO5_:
			//DrawFrameCONFIG();
			break;
		//
		case _ZERO6_:
			//DrawFrameCONFIG();
			break;
		//Окно "Загрузить"
		case _LOADGAME_:
			//DrawFrameCONFIG();
			break;
		//
		case _ZERO8_:
			//DrawFrameCONFIG();
			break;
		//Игра: Режим в космосе
		case _GAMESPACE_:
			DrawFrameSPACE1();
			//эффект BLUR если включен форсаж
			if (shpPlayer->bDriveForsage)
			{
				FX_SetBlendMode(FX_BLEND_ADD);
				FX_RadBlur_Draw(_ColdBLUE_, 255);
				FX_SetBlendMode(FX_BLEND_NORMAL);
			}
			DrawFrameSPACE2();
			break;
		//Игра: Режим в космосе - карта
		case _GAMESPACEMAP_:
			//Сначала рисуем основную картинку...................................
			DrawFrameSPACE1();
			if (shpPlayer->bDriveForsage)
			{
				FX_SetBlendMode(FX_BLEND_ADD);
				FX_RadBlur_Draw(_ColdBLUE_, 255);
				FX_SetBlendMode(FX_BLEND_NORMAL);
			}
			DrawFrameSPACE2();

			//...и потом рисуем карту
			DrawFrameSPACEMAP();
			break;

		//По умолчанию (тестирование)
		default:
			DrawFrameDEFAULT();
			break;
	}


	//Рисуем информацию по FPS в последнюю очередь (что бы рисовалось сверху)
	if (bShowFPS)
		DrawFPS();	

	//Рисуем курсор и консоль в самую последнюю очередь
	DrawCursor();
	Console_Draw();
	
	return;
}
//---------------------------------------------------------------------------
//
void OMEGAQuit()
{
	vecSmallStars.clear();
	return;
}
//===========================================================================
//---------------------------------------------------------------------------
//Увеличение скорости Спутника в Главном меню
void ConsoleArmageddon()
{
	switch (iGameStatus)
	{
		//Статус: начальная загрузка, OMEGAInit
	case _ZERO_:
		break;
		//Первый экран после загрузки ресурсов, Стартовое меню
	case _STARTMENU_:
		if (objMainMenuObject->GetSpeed() < 20.0)
		{
			vector<clSmallStar>::iterator i = vecSmallStars.begin();
			while (i != vecSmallStars.end())
			{
				i->iColour = _RED_;
				++i;
			}
			objMainMenuObject->SetSpeed(20.0);
		}
		else
		{
			vector<clSmallStar>::iterator i = vecSmallStars.begin();
			while (i != vecSmallStars.end())
			{
				i->iColour = _ColdBLUE_;
				++i;
			}
			objMainMenuObject->SetSpeed(0.8);
		}


		break;
	}




	
	return;
}
//---------------------------------------------------------------------------
//Вкл/выкл работы сенсоров (отображение интерфейса)
void ConsoleVisibleInterface()
{
	bViewInterface = !bViewInterface;

	return;
}
//---------------------------------------------------------------------------
//Вкл/выкл FPS
void ConsoleFPS()
{
	bShowFPS = !bShowFPS;
	return;
}
//---------------------------------------------------------------------------
//Список команд
void ConsoleHelp()
{
	Console_AddString("###########################");
	Console_AddString("# Simple console application v.1.0 #");
	Console_AddString("###########################");
	
	if (iLanguage = _RUS_)
	{
		Console_AddString("выход/quit - закрыть игру");
		Console_AddString("фпс/fps - вкл/выкл отображения FPS");
	}


	return;
}
//---------------------------------------------------------------------------
//Переключение в русскую расскладку
void ConsoleLayoutRus()
{
	Key_LoadLayout(K_LAYOUT_RUS);

	return;
}
//---------------------------------------------------------------------------
//Переключение в английскую расскладку
void ConsoleLayoutEng()
{
	Key_LoadLayout(K_LAYOUT_ENG);

	return;
}
//---------------------------------------------------------------------------
//===========================================================================
//---------------------------------------------------------------------------
//Обновление картинки и данных в режиме полета в космосе
void UpdateFrameSpace()
{
	vector<clSmallStar>::iterator i = vecSmallStars.begin();

	//Блюр-эффект
	//iCountBlur++;
	if (iGameStatus == _GAMESPACE_)
	{
		FX_RadBlur_SetParams(10, 7, 7);
		FX_RadBlur_Calc((void*)DrawFrameSPACE1, 25);
	}

	//Обновляем данные корабля, применяем ЗУМ
	shpPlayer->fZoom = fGameZoom;
	shpPlayer->iAniN = N;
	shpPlayer->bViewInterface = bViewInterface;
	shpPlayer->Update();
	shpPlayer->SetXYcursor(X, Y);
	//shpPlayer->CollisionSun(star0->circleCircle);
	//shpPlayer->CollisionPlanet(plPlanet0->circleCircle);
	//Если игровой статус отличается от Игра в космосе, то отключаем отображение всплыв. подсказок на объектах
	if (iGameStatus != _GAMESPACE_)
		shpPlayer->SetXYcursor(0, 0);

	/*star0->fZoom = fGameZoom;
	star0->iAniN = N;
	star0->bViewInterface = bViewInterface;
	star0->Update();
	star0->SetXYcursor(X, Y);*/
	//Вектор больших звезд в Системе
	vector<clBigStar>::iterator iBS = ssysCurStarSys->vecBigStars.begin();
	while (iBS != ssysCurStarSys->vecBigStars.end())
	{
		shpPlayer->CollisionSun(iBS->circleCircle);

		iBS->fZoom = fGameZoom;
		iBS->iAniN = N;
		iBS->bViewInterface = bViewInterface;
		iBS->Update();
		iBS->SetXYcursor(X, Y);

		//Если игровой статус отличается от Игра в космосе, то отключаем отображение всплыв. подсказок на объектах
		if (iGameStatus != _GAMESPACE_)
			iBS->SetXYcursor(0, 0);

		++iBS;
	}

	/*plPlanet0->fZoom = fGameZoom;
	plPlanet0->iAniN = N;
	plPlanet0->bViewInterface = bViewInterface;
	plPlanet0->Update();
	plPlanet0->SetXYcursor(X, Y);*/
	//Вектор планет в Системе
	vector<clPlanet>::iterator iPL = ssysCurStarSys->vecPlanets.begin();
	while (iPL != ssysCurStarSys->vecPlanets.end())
	{
		shpPlayer->CollisionPlanet(iPL->circleCircle);

		iPL->fZoom = fGameZoom;
		iPL->iAniN = N;
		iPL->bViewInterface = bViewInterface;
		iPL->Update();
		iPL->SetXYcursor(X, Y);

		//Если игровой статус отличается от Игра в космосе, то отключаем отображение всплыв. подсказок на объектах
		if (iGameStatus != _GAMESPACE_)
			iPL->SetXYcursor(0, 0);

		++iPL;
	}

	//Обновляем кнопки интерфейса
	biTestBI->SetXYcursor(X, Y);

	//обновление вектора звезд
	while (i != vecSmallStars.end())
	{
		i->Update();
		++i;
	}

	return;
}
//---------------------------------------------------------------------------
//===========================================================================
//---------------------------------------------------------------------------
//Рисуем рамку
void PaintFrame(int _iX, int _iY, int _iWidth, int _iHeight, int _iThick, int _iColour, int _iAlpha)
{
	//_iX--;
	//_iY--;
	_iThick--;
	//верх
	Pr2D_Rect(_iX, _iY, _iWidth, _iThick, _iColour, _iAlpha, PR_FILL);
	//право
	Pr2D_Rect(_iX + _iWidth - _iThick, _iY, _iThick, _iHeight, _iColour, _iAlpha, PR_FILL);
	//низ
	Pr2D_Rect(_iX, _iY + _iHeight - _iThick, _iWidth, _iThick, _iColour, _iAlpha, PR_FILL);
	//лево
	Pr2D_Rect(_iX, _iY, _iThick, _iHeight, _iColour, _iAlpha, PR_FILL);

	return;
}
//---------------------------------------------------------------------------
//Функция рисования звезд
void PaintStars()
{

	return;
}
//---------------------------------------------------------------------------
//Рисуем информацию о FPS
void DrawFPS()
{
	//Отрисовка FPS
	char chFPS[250];
	float fWidthFPS;
	sprintf_s(chFPS, "FPS:%d", OE_GetFPS());
	fWidthFPS = Text_GetWidth(FontFPS, chFPS, 1, 0);

	//Рисуем рамку для ФПС
	//void Pr2D_Line( float X1, float Y1, float X2, float Y2, int Color, BYTE Alpha = 255, int Flags = PR_DEFAULT );
	Pr2D_Line(0, 15, 10, 25, _LightBLUE_, 255, PR_FILL);
	Pr2D_Line(0, 16, 10, 26, _LightBLUE_, 255, PR_FILL);
	//Pr2D_Line(5, 22, 10, 27, _LightBLUE_, 255, PR_FILL);
	//void Pr2D_Rect( float X, float Y, float Width, float Height, int Color, BYTE Alpha = 255, int Flags = PR_DEFAULT ); 
	Pr2D_Rect(10, 16, fWidthFPS + 6, 18, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(12, 18, fWidthFPS + 2, 14, _SpaceMainMenu_, 255, PR_FILL);

	//Рисуем поверх рамки значение ФПС
	//void Text_Draw( PFont2D Font, float X, float Y, char* Text, float Scale = 1.0, float Step = 0, BYTE Alpha = 255, int Color = 0xFFFFFF );
	Text_Draw(FontFPS,			// Наш идентификатор шрифта
			14, 19,				// Координаты
			chFPS,				// Сам текст
			1.0,				// Коэффициент увеличения
			0,					// Дополнительное растояние между символами
			255,				// Альфа
			_WHITE_);			// цвет

	//Отрисовка справочной информации, если не "РЕЛИЗ-ВЕРСИЯ"
	if (fStatus != _RELEASE_)
	{
		MEMORYSTATUS memStatus;
		GlobalMemoryStatus(&memStatus);

		switch (iGameStatus)
		{
		case _GAMESPACE_:
		case _GAMESPACEMAP_:
			sprintf_s(chFPS, "fStatus:%4.1f\niGameStatus:%d\nN(ani):%d\nVolume:%d\n---------------\nZOOM:%4.2f\nPlayerX:%f\nPlayerY:%f\nScreenX:%d\nScreenY:%d\nAngle:%6.2f\nSpeed:%6.2f\n---------------\nFullScreen:%d\nResolution(cur):%d-%d\n---------------",
				fStatus, iGameStatus, N, iVolume,
				fGameZoom, shpPlayer->fXposGlob, shpPlayer->fYposGlob, X, Y, shpPlayer->fAngle, shpPlayer->fSpeedCur,
				bFullScreen, iWidth, iHeight);
			Text_Draw(FontFPS, 14, 42, chFPS, 1, 0, 255, _WHITE_);
			break;
		default:
			sprintf_s(chFPS, "fStatus:%4.1f\niGameStatus:%d\nN(ani):%d\nVolume:%d\n---------------\nFullScreen:%d\nResolution(cur):%d-%d\n---------------\nRAM:%d\nResolution(max):%d-%d\nTexSize(max):%d\n---------------",
				fStatus, iGameStatus, N, iVolume,
				bFullScreen, iWidth, iHeight,
				memStatus.dwTotalPageFile / (1024 * 1024), GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
				U_GetMaxTexSize());
			Text_Draw(FontFPS, 14, 42, chFPS, 1, 0, 255, _WHITE_);
			/*
			//Тест отображения загруженных строк из файла локализации
			Text_Draw(FontFPS, 3, 250, chTest1, 1, 0, 255, _WHITE_);
			Text_Draw(FontFPS, 3, 265, chTest2, 1, 0, 255, _WHITE_);
			*/
			break;
		}
		
	}

	return;
}
//---------------------------------------------------------------------------
void DrawCursor()
{
	//SetCursor(NULL);
	//Рисуем курсор
	//void SSprite_Draw( PTexture Tex, float X, float Y, float Width, float Height, int Alpha = 255, float Angle = 0, int Flags = FX_DEFAULT );

	//SSprite_Draw(ptCursorDefault, X, Y, 32, 32, 255, 0, FX_DEFAULT);		//статический курсор
	//ASprite_Draw(ptCursorDefaultA, X, Y, 32, 32, N, 255, 0, FX_DEFAULT);	//анимированный курсор

	//Выбор курсора на основании игрового статуса (iGameStatus)
	switch (iGameStatus)
	{
		//Статус: начальная загрузка, OMEGAInit
	case _ZERO_:
		break;
		//Первый экран после загрузки ресурсов, Стартовое меню
	case _STARTMENU_:
		ASprite_Draw(ptCursorDefaultA, X, Y, 32, 32, N, 255, 0, FX_DEFAULT);	//анимированный курсор
		break;


		//По умолчанию (тестирование)
	default:
		ASprite_Draw(ptCursorDefaultA, X, Y, 32, 32, N, 255, 0, FX_DEFAULT);	//анимированный курсор
		break;
	}

	return;
}
//---------------------------------------------------------------------------
void DrawInterfaceSpace()
{
	int x, y;
	char chTMPCoord[250];

	//Мини-карта
	//void PaintFrame(int _iX, int _iY, int _iWidth, int _iHeight, int _iThick, int _iColour, int _iAlpha);
	PaintFrame(iWidth - 261, iHeight - 211, 250, 200, 2, _LightBLUE_, 255);
	Pr2D_Rect(iWidth - 25, iHeight - 211, 25, 1, _LightBLUE_, 255, PR_FILL);
	if (bViewInterface)
	{
		//прозрачный фон
		Pr2D_Rect(iWidth - 258, iHeight - 208, 244, 194, _LightBLUE_, 200, PR_FILL);
		//Сетка дисплея
		SSprite_Draw(ptInterfaceDisplay, iWidth - 258, iHeight - 208, 245, 195, 200, 0, FX_DEFAULT);

		//==================================================================
		//          Перебор объектов для отрисовки мини-карты
		//==================================================================

		//Звезды
		vector<clBigStar>::iterator iBS = ssysCurStarSys->vecBigStars.begin();
		while (iBS != ssysCurStarSys->vecBigStars.end())
		{
			x = (iWidth - 258 + 244 / 2) + (iBS->fXposGlob - shpPlayer->fXposGlob) + 5;
			y = (iHeight - 208 + 194 / 2) + (iBS->fYposGlob - shpPlayer->fYposGlob) + 5;
			if (iWidth - 258 < x && x < iWidth - 258 + 244)
				if (iHeight - 208 < y && y < iHeight - 208 + 194)
				{
					Pr2D_Circle(x, y, 10, _ColdBLUE_, 255, 32, PR_DEFAULT);
					Pr2D_Circle(x, y, 4, _ColdBLUE_, 255, 32, PR_DEFAULT);
				}

			++iBS;
		}

		//Планеты
		vector<clPlanet>::iterator iPL = ssysCurStarSys->vecPlanets.begin();
		while (iPL != ssysCurStarSys->vecPlanets.end())
		{
			x = (iWidth - 258 + 244 / 2) + (iPL->fXposGlob - shpPlayer->fXposGlob) + 4;
			y = (iHeight - 208 + 194 / 2) + (iPL->fYposGlob - shpPlayer->fYposGlob) + 4;
			if (iWidth - 258 < x && x < iWidth - 258 + 244)
				if (iHeight - 208 < y && y < iHeight - 208 + 194)
				{
					Pr2D_Circle(x, y, 8, _ColdBLUE_, 255, 32, PR_DEFAULT);
				}

			++iPL;
		}

		//==================================================================
		//==================================================================

		//Корабль игрока
		Pr2D_Circle(iWidth - 258 + 244 / 2, iHeight - 208 + 194 / 2, 5, _ColdBLUE_, 255, 32, PR_FILL);
	}
	else
	{
		//Сетка дисплея мерцает (АЛЬФА) если нет отображения интерфейса
		SSprite_Draw(ptInterfaceDisplay, iWidth - 258, iHeight - 208, 245, 195, N * 25, 0, FX_DEFAULT);
		//Рисуем круг точки маршрута/цели
		Pr2D_Circle(iWidth - 122, iHeight - 227, 3, _WHITE_, N * 25, 32, PR_FILL);
		Pr2D_Circle(iWidth - 122, iHeight - 227, 11, _WHITE_, N * 25, 32, PR_DEFAULT);
		Pr2D_Circle(iWidth - 122, iHeight - 227, 12, _WHITE_, N * 25, 32, PR_DEFAULT);
		Pr2D_Circle(iWidth - 122, iHeight - 227, 13, _WHITE_, N * 25, 32, PR_DEFAULT);
		//расстояние до цели
		Text_Draw(FontConsole,					// Наш идентификатор шрифта
			iWidth - 105,					// Координаты X
			iHeight - 234,					// Координаты Y
			"0000.00",						// текст
			1.0,							// Коэффициент увеличения
			0,								// Дополнительное растояние между символами
			N * 25,							// Альфа
			_WHITE_);						//Цвет
		//координаты игрока
		sprintf_s(chTMPCoord, "X:%0.2f\nY:%0.2f", shpPlayer->fXposGlob, shpPlayer->fYposGlob);
		Text_Draw(FontConsole,					// Наш идентификатор шрифта
				iWidth - 256,					// Координаты X
				iHeight - 242,					// Координаты Y
				chTMPCoord,						// текст
				1.0,							// Коэффициент увеличения
				0,								// Дополнительное растояние между символами
				N * 25,							// Альфа
				_WHITE_);						//Цвет
	}

	//Координаты
	//Линии
	Pr2D_Rect(iWidth - 261, iHeight - 241, 1, 30, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(iWidth - 12, iHeight - 241, 1, 30, _LightBLUE_, 255, PR_FILL);
	//прозрачный фон
	Pr2D_Rect(iWidth - 258, iHeight - 240, 244, 27, _LightBLUE_, 150, PR_FILL);
	//Текст
	sprintf_s(chTMPCoord, "X:%0.2f\nY:%0.2f", shpPlayer->fXposGlob, shpPlayer->fYposGlob);
	if (bViewInterface)
	{
		Text_Draw(FontConsole,					// Наш идентификатор шрифта
				iWidth - 256,					// Координаты X
				iHeight - 242,					// Координаты Y
				chTMPCoord,						// текст
				1.0,							// Коэффициент увеличения
				0,								// Дополнительное растояние между символами
				255,							// Альфа
				_WHITE_);						//Цвет
	}
	//Дистанция до цели
	if (bViewInterface)
		if (shpPlayer->bMapCoordTarget)
		{
			//Рисуем круг точки маршрута/цели
			Pr2D_Circle(iWidth - 122, iHeight - 227, 3, _WHITE_, 255, 32, PR_FILL);
			Pr2D_Circle(iWidth - 122, iHeight - 227, 11, _WHITE_, 200, 32, PR_DEFAULT);
			Pr2D_Circle(iWidth - 122, iHeight - 227, 12, _WHITE_, 200, 32, PR_DEFAULT);
			Pr2D_Circle(iWidth - 122, iHeight - 227, 13, _WHITE_, 200, 32, PR_DEFAULT);

			//Дистанция
			sprintf_s(chTMPCoord, "%0.2f", M_Distance(	shpPlayer->fXposGlob,
													shpPlayer->fYposGlob,
													shpPlayer->fMapCoordTargetX,
													shpPlayer->fMapCoordTargetY));
			Text_Draw(FontConsole,					// Наш идентификатор шрифта
					iWidth - 105,					// Координаты X
					iHeight - 234,					// Координаты Y
					chTMPCoord,						// текст
					1.0,							// Коэффициент увеличения
					0,								// Дополнительное растояние между символами
					255,							// Альфа
					_WHITE_);						//Цвет
		}

	//Правый верхний дисплей
	PaintFrame(iWidth - 261, 16, 250, 125, 2, _LightBLUE_, 255);
	Pr2D_Rect(iWidth - 25, 140, 25, 1, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(iWidth - 258, 19, 244, 119, _LightBLUE_, 150, PR_FILL);
	//правая вертикальная линия
	Pr2D_Line(iWidth - 11, 25, iWidth - 11, iHeight - 25, _LightBLUE_, 255, PR_FILL);
	Pr2D_Line(iWidth - 10, 25, iWidth - 10, iHeight - 25, _LightBLUE_, 255, PR_FILL);

	//Скорость

	//Броня и щит

	//Модули
	//Рисуем линию в лев.ниж. углу
	Pr2D_Line(0, iHeight - 1, 10, iHeight - 11, _LightBLUE_, 255, PR_FILL);
	Pr2D_Line(0, iHeight, 11, iHeight - 11, _LightBLUE_, 255, PR_FILL);
	//Нижняя горизонтальная линия до радара	
	Pr2D_Line(11, iHeight - 12, iWidth - 5 - 261, iHeight - 12, _LightBLUE_, 255, PR_FILL);
	Pr2D_Line(10, iHeight - 11, iWidth - 5 - 261, iHeight - 11, _LightBLUE_, 255, PR_FILL);
	//Кнопка интерфейса
	biTestBI->Draw();

	return;
}
//---------------------------------------------------------------------------
//Статус: по умолчанию (тестирование)
void DrawFrameDEFAULT()
{
	//Пример использования класса clObject
	//objOne->iAniN = N;
	//objOne->Draw();

	//тестирование экрана загрузки
	Loading(0);

	return;
}
//---------------------------------------------------------------------------
//Стартовое меню
void DrawFrameSTARTMENU()
{	
	float fLineHeight = 0.0;
	fLineHeight = iHeight - (btnContGame->GetHeight() / 2 + btnContGame->fYpos + 6);

	//Рисуем космос
	Pr2D_Rect(0, 0, iWidth, iHeight, _SpaceMainMenu_, 255, PR_FILL);
	//Рисуем звезды
	vector<clSmallStar>::iterator i = vecSmallStars.begin();
	while (i != vecSmallStars.end())
	{
		i->Draw();
		++i;
	}

	//Рисуем линии к кнопкам
	Pr2D_Line(0, iHeight-1, 10, iHeight-11, _LightBLUE_, 255, PR_FILL);
	Pr2D_Line(0, iHeight, 10, iHeight-10, _LightBLUE_, 255, PR_FILL);
	Pr2D_Line(11, iHeight - 10, 11, iHeight - fLineHeight, _LightBLUE_, 255, PR_FILL);
	Pr2D_Line(12, iHeight - 11, 12, iHeight - fLineHeight, _LightBLUE_, 255, PR_FILL);
	//1 Продолжить игру
	Pr2D_Line(12, iHeight - fLineHeight, 17, iHeight - fLineHeight - 5, _LightBLUE_, 255, PR_FILL);
	Pr2D_Line(11, iHeight - fLineHeight, 17, iHeight - fLineHeight - 6, _LightBLUE_, 255, PR_FILL);
	//2 Новая игра
	Pr2D_Line(12, iHeight - fLineHeight + (btnContGame->GetHeight() + 5)*1, 17, iHeight - fLineHeight - 5 + (btnContGame->GetHeight() + 5)*1, _LightBLUE_, 255, PR_FILL);
	Pr2D_Line(11, iHeight - fLineHeight + (btnContGame->GetHeight() + 5)*1, 17, iHeight - fLineHeight - 6 + (btnContGame->GetHeight() + 5)*1, _LightBLUE_, 255, PR_FILL);
	//3 Загрузить игру
	Pr2D_Line(12, iHeight - fLineHeight + (btnContGame->GetHeight() + 5) * 2, 17, iHeight - fLineHeight - 5 + (btnContGame->GetHeight() + 5) * 2, _LightBLUE_, 255, PR_FILL);
	Pr2D_Line(11, iHeight - fLineHeight + (btnContGame->GetHeight() + 5) * 2, 17, iHeight - fLineHeight - 6 + (btnContGame->GetHeight() + 5) * 2, _LightBLUE_, 255, PR_FILL);
	//4 Настройки
	Pr2D_Line(12, iHeight - fLineHeight + (btnContGame->GetHeight() + 5) * 3, 17, iHeight - fLineHeight - 5 + (btnContGame->GetHeight() + 5) * 3, _LightBLUE_, 255, PR_FILL);
	Pr2D_Line(11, iHeight - fLineHeight + (btnContGame->GetHeight() + 5) * 3, 17, iHeight - fLineHeight - 6 + (btnContGame->GetHeight() + 5) * 3, _LightBLUE_, 255, PR_FILL);
	//5 Авторы
	Pr2D_Line(12, iHeight - fLineHeight + (btnContGame->GetHeight() + 5) * 4, 17, iHeight - fLineHeight - 5 + (btnContGame->GetHeight() + 5) * 4, _LightBLUE_, 255, PR_FILL);
	Pr2D_Line(11, iHeight - fLineHeight + (btnContGame->GetHeight() + 5) * 4, 17, iHeight - fLineHeight - 6 + (btnContGame->GetHeight() + 5) * 4, _LightBLUE_, 255, PR_FILL);
	//6 Выход
	Pr2D_Line(12, iHeight - fLineHeight + (btnContGame->GetHeight() + 5) * 5, 17, iHeight - fLineHeight - 5 + (btnContGame->GetHeight() + 5) * 5, _LightBLUE_, 255, PR_FILL);
	Pr2D_Line(11, iHeight - fLineHeight + (btnContGame->GetHeight() + 5) * 5, 17, iHeight - fLineHeight - 6 + (btnContGame->GetHeight() + 5) * 5, _LightBLUE_, 255, PR_FILL);

	//Рисуем объект-планету
	objMainMenuPlanet->Draw();
	//Рисуем объект-звезду
	starMainMenuStar->Draw();
	//Рисуем объект - Спутник
	objMainMenuObject->Draw();	
	//Рисуем кнопки
	btnContGame->Draw();
	btnNewGame->Draw();
	btnLoadGame->Draw();
	btnConfig->Draw();
	btnAbout->Draw();
	btnExit->Draw();

	//Рисуем название игры
	SSprite_Draw(ptMainMenuTitle, 15, btnContGame->fYpos - 40, 472, 37, 255, 0, FX_DEFAULT);

	//Рисуем рамку
	//void Pr2D_Rect( float X, float Y, float Width, float Height, int Color, BYTE Alpha = 255, int Flags = PR_DEFAULT ); 
	Pr2D_Rect(0, 0, iWidth, 10, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(iWidth-6, 0, iWidth, iHeight, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(0, iHeight-6, iWidth, iHeight, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(0, 0, 4, iHeight, _LightBLUE_, 255, PR_FILL);	
	
	//Рисуем номер версии в самом конце
	//void Text_Draw( PFont2D Font, float X, float Y, char* Text, float Scale = 1.0, float Step = 0, BYTE Alpha = 255, int Color = 0xFFFFFF );
	Text_Draw(FontConsole,				// Наш идентификатор шрифта
			18, iHeight-25,				// Координаты
			(char *)chVersion,			// Сам текст
			1.0,						// Коэффициент увеличения
			0,							// Дополнительное растояние между символами
			255,						// Альфа
			_WHITE_);					// цвет

	return;
}
//---------------------------------------------------------------------------
//"Об игре"
void DrawFrameABOUT()
{
	//отображаем фоном Главное (Стартовое) Меню
	DrawFrameSTARTMENU();
	//перекрытие
	Pr2D_Rect(0, 0, iWidth, iHeight, _SpaceMainMenu_, 255, PR_FILL);
	//Рисуем рамку
	//void Pr2D_Rect( float X, float Y, float Width, float Height, int Color, BYTE Alpha = 255, int Flags = PR_DEFAULT ); 
	Pr2D_Rect(0, 0, iWidth, 10, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(iWidth - 6, 0, iWidth, iHeight, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(0, iHeight - 6, iWidth, iHeight, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(0, 0, 4, iHeight, _LightBLUE_, 255, PR_FILL);

	return;
}
//---------------------------------------------------------------------------
//"Настройки"
void DrawFrameCONFIG()
{
	//отображаем фоном Главное (Стартовое) Меню
	DrawFrameSTARTMENU();
	//перекрытие
	Pr2D_Rect(0, 0, iWidth, iHeight, _SpaceMainMenu_, 255, PR_FILL);
	//Центральная область
	Pr2D_Rect(iWidth / 6, iHeight / 6, iWidth / 6 * 4, iHeight / 6 * 4, _LightBLUE_, 150, PR_FILL);
	//Рисуем рамку Игрового окна, толщина 10*5*5*5пикселей
	//void Pr2D_Rect( float X, float Y, float Width, float Height, int Color, BYTE Alpha = 255, int Flags = PR_DEFAULT ); 
	Pr2D_Rect(0, 0, iWidth, 10, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(iWidth - 6, 0, iWidth, iHeight, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(0, iHeight - 6, iWidth, iHeight, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(0, 0, 4, iHeight, _LightBLUE_, 255, PR_FILL);
	//рисуем рамку окна настроек
	PaintFrame(iWidth / 6 - 6, iHeight / 6 - 6, iWidth / 6 * 4 + 12, iHeight / 6 * 4 + 12, 5, _LightBLUE_, 255);

	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//Игра: Режим в космосе
void DrawFrameSPACE1()
{
	//преобразуем систему координат пространства для текущего экрана с учетом масштаба
	shpPlayer->fXpos = (iWidth / 2) / fGameZoom - (shpPlayer->GetWidth() / 2);
	shpPlayer->fYpos = (iHeight / 2) / fGameZoom - (shpPlayer->GetHeight() / 2);
	//shpPlayer->fXpos = (iWidth / 2) / fGameZoom - (shpPlayer->GetWidth() / 2);
	//shpPlayer->fYpos = (iHeight / 2) / fGameZoom - (shpPlayer->GetHeight() / 2);
	//shpPlayer->fXpos *= fPositionCoef;
	//shpPlayer->fYpos *= fPositionCoef;

	//Рисуем космос
	Pr2D_Rect(0, 0, iWidth, iHeight, _SpaceMainMenu_, 255, PR_FILL);
	
	//Рисуем звезды======================================================================================
	vector<clSmallStar>::iterator i = vecSmallStars.begin();
	while (i != vecSmallStars.end())
	{
		/*i->fXpos = i->fXposGlob + (shpPlayer->fXpos - shpPlayer->fXposGlob);
		i->fYpos = i->fYposGlob + (shpPlayer->fYpos - shpPlayer->fYposGlob);*/
		//i->fXpos *= fPositionCoef;
		//i->fYpos *= fPositionCoef;
		i->Draw();
		++i;
	}
	
	//Звезда
	/*star0->fXpos = (star0->fXposGlob + (shpPlayer->fXpos / fPositionCoef - shpPlayer->fXposGlob)) * fPositionCoef;
	star0->fYpos = (star0->fYposGlob + (shpPlayer->fYpos / fPositionCoef - shpPlayer->fYposGlob)) * fPositionCoef;
	star0->Draw();*/

	/*plPlanet0->fXpos = (plPlanet0->fXposGlob + (shpPlayer->fXpos / fPositionCoef - shpPlayer->fXposGlob)) * fPositionCoef;
	plPlanet0->fYpos = (plPlanet0->fYposGlob + (shpPlayer->fYpos / fPositionCoef - shpPlayer->fYposGlob)) * fPositionCoef;
	plPlanet0->Draw();*/

	//Рисуем объекты Системы
	//Вектор больших звезд в Системе
	vector<clBigStar>::iterator iBS = ssysCurStarSys->vecBigStars.begin();
	while (iBS != ssysCurStarSys->vecBigStars.end())
	{
		iBS->fXpos = (iBS->fXposGlob + (shpPlayer->fXpos / fPositionCoef - shpPlayer->fXposGlob)) * fPositionCoef;
		iBS->fYpos = (iBS->fYposGlob + (shpPlayer->fYpos / fPositionCoef - shpPlayer->fYposGlob)) * fPositionCoef;
		iBS->Draw();

		++iBS;
	}
	
	//Вектор планет в Системе
	vector<clPlanet>::iterator iPL = ssysCurStarSys->vecPlanets.begin();
	while (iPL != ssysCurStarSys->vecPlanets.end())
	{
		iPL->fXpos = (iPL->fXposGlob + (shpPlayer->fXpos / fPositionCoef - shpPlayer->fXposGlob)) * fPositionCoef;
		iPL->fYpos = (iPL->fYposGlob + (shpPlayer->fYpos / fPositionCoef - shpPlayer->fYposGlob)) * fPositionCoef;
		iPL->Draw();

		++iPL;
	}


	//рисуем корабль игрока
	shpPlayer->Draw();

	//Рисуем эффекты форсажа
	if (shpPlayer->bDriveForsage)
	{
		//Сделать: расстянувшиеся в линии звезды, как в StarWars
	}

	return;
}
//---------------------------------------------------------------------------
//Игра: Режим в космосе без эффектов (н-р /БЛЮР)
void DrawFrameSPACE2()
{
	//Рисуем рамку Игрового окна, толщина 10*5*5*5пикселей
	//void Pr2D_Rect( float X, float Y, float Width, float Height, int Color, BYTE Alpha = 255, int Flags = PR_DEFAULT ); 
	Pr2D_Rect(0, 0, iWidth, 10, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(iWidth - 5, 0, iWidth, iHeight, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(0, iHeight - 5, iWidth, iHeight, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(0, 0, 4, iHeight, _LightBLUE_, 255, PR_FILL);

	//Интерфейс
	DrawInterfaceSpace();
	return;
}
//---------------------------------------------------------------------------
//Игра: Режим в космосе - Карта
void DrawFrameSPACEMAP()
{
	//Затеняем фон
	Pr2D_Rect(0, 0, iWidth, iHeight, _BLACK_, 200, PR_FILL);

	//Рисуем рамку Игрового окна, толщина 10*5*5*5пикселей
	Pr2D_Rect(0, 0, iWidth, 10, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(iWidth - 5, 0, iWidth, iHeight, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(0, iHeight - 5, iWidth, iHeight, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(0, 0, 4, iHeight, _LightBLUE_, 255, PR_FILL);

	//Рисуем вертикальную линию
	Pr2D_Rect((float)iWidth * 0.1 - 8, 0, 1, (float)iHeight * 0.9 + 4, _LightBLUE_, 255, PR_FILL);
	//Рисуем рамку
	Pr2D_Rect((float)iWidth * 0.1 - 4, (float)iHeight * 0.1 - 4, (float)iHeight * 0.8 + 8, 1, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect((float)iWidth * 0.1 + (float)iHeight * 0.8 + 3, (float)iHeight * 0.1 - 4, 1, (float)iHeight * 0.8 + 7, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect((float)iWidth * 0.1 - 4, (float)iHeight * 0.9 + 3, (float)iHeight * 0.8 + 8, 1, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect((float)iWidth * 0.1 - 4, (float)iHeight * 0.1 - 4, 1, (float)iHeight * 0.8 + 7, _LightBLUE_, 255, PR_FILL);

	//Рисуем область для карты (минус 10% с каждой стороны Экрана, учитываем, что должен быть квадрат)
	Pr2D_Rect((float)iWidth * 0.1, (float)iHeight * 0.1, (float)iHeight * 0.8, (float)iHeight * 0.8, _LightBLUE_, 150, PR_FILL);
	//Рисуем область для доп.информации 
	Pr2D_Rect(	(float)iWidth * 0.1 + (float)iHeight * 0.8 + 7, (float)iHeight * 0.1,
				(float)iWidth * 0.2, (float)iHeight * 0.8, _LightBLUE_, 150, PR_FILL);

	//Рисуем линии пересечения до корабля игрока
	float fXCentre, fYCentre;
	fXCentre = (float)iWidth* 0.1 + (float)iHeight * 0.4;
	fYCentre = (float)iHeight * 0.1 + (float)iHeight * 0.4;

	float fMapCoordTargetX, fMapCoordTargetY;
	fMapCoordTargetX = fXCentre + shpPlayer->fXposGlob * ssysCurStarSys->fZoomForMap;
	fMapCoordTargetY = fYCentre + shpPlayer->fYposGlob * ssysCurStarSys->fZoomForMap;

	Pr2D_Line(	(float)iWidth * 0.1, fMapCoordTargetY,
				(float)iWidth * 0.1 + (float)iHeight * 0.8, fMapCoordTargetY, _LightBLUE_, 200, PR_DEFAULT);
	Pr2D_Line(	fMapCoordTargetX, (float)iHeight * 0.1,
				fMapCoordTargetX, (float)iHeight * 0.1 + (float)iHeight * 0.8, _LightBLUE_, 200, PR_DEFAULT);

	//Рисуем карту
	ssysCurStarSys->DrawMap();

	//Рисуем корабль главного героя
	if (
		(float)iWidth * 0.1 + (float)iHeight * 0.4 + shpPlayer->fXposGlob * ssysCurStarSys->fZoomForMap > (float)iWidth * 0.1
		&&
		(float)iWidth * 0.1 + (float)iHeight * 0.4 + shpPlayer->fXposGlob * ssysCurStarSys->fZoomForMap < (float)iWidth * 0.1 + (float)iHeight * 0.8
		)
	if (
		(float)iHeight * 0.1 + (float)iHeight * 0.4 + shpPlayer->fYposGlob * ssysCurStarSys->fZoomForMap > (float)iHeight * 0.1
		&&
		(float)iHeight * 0.1 + (float)iHeight * 0.4 + shpPlayer->fYposGlob * ssysCurStarSys->fZoomForMap < (float)iHeight * 0.1 + (float)iHeight * 0.8
		)
	{
		Pr2D_Circle((float)iWidth * 0.1 + (float)iHeight * 0.4 + shpPlayer->fXposGlob * ssysCurStarSys->fZoomForMap,
					(float)iHeight * 0.1 + (float)iHeight * 0.4 + shpPlayer->fYposGlob * ssysCurStarSys->fZoomForMap,
					10, _LightBLUE_, 255, 4, PR_FILL);
		Pr2D_Circle((float)iWidth * 0.1 + (float)iHeight * 0.4 + shpPlayer->fXposGlob * ssysCurStarSys->fZoomForMap,
					(float)iHeight * 0.1 + (float)iHeight * 0.4 + shpPlayer->fYposGlob * ssysCurStarSys->fZoomForMap,
					8, _WHITE_, 255, 4, PR_FILL);
		Pr2D_Circle((float)iWidth * 0.1 + (float)iHeight * 0.4 + shpPlayer->fXposGlob * ssysCurStarSys->fZoomForMap,
					(float)iHeight * 0.1 + (float)iHeight * 0.4 + shpPlayer->fYposGlob * ssysCurStarSys->fZoomForMap,
					4, _LightBLUE_, 255, 4, PR_FILL);
		/*Text_Draw(		*(shpPlayer->fntFont),
						(int)((float)iWidth * 0.1 + (float)iHeight * 0.4 + shpPlayer->fXposGlob * ssysCurStarSys->fZoomForMap -
						Text_GetWidth(*(shpPlayer->fntFont), shpPlayer->GetName(), 1, 0) / 2),
						(int)((float)iHeight * 0.1 + (float)iHeight * 0.4 + shpPlayer->fYposGlob * ssysCurStarSys->fZoomForMap - 22),
						shpPlayer->GetName(), 1.0, 0, 255, _WHITE_);*/
	}
	
	//Рисуем символ корабля справа под названием Системы и указываем координаты
	Pr2D_Circle((float)iWidth * 0.1 + (float)iHeight * 0.8 + 22,
				(float)iHeight * 0.1 + 51,
				10, _LightBLUE_, 255, 4, PR_FILL);
	Pr2D_Circle((float)iWidth * 0.1 + (float)iHeight * 0.8 + 22,
				(float)iHeight * 0.1 + 51,
				8, _WHITE_, 255, 4, PR_FILL);
	Pr2D_Circle((float)iWidth * 0.1 + (float)iHeight * 0.8 + 22,
				(float)iHeight * 0.1 + 51,
				4, _LightBLUE_, 255, 4, PR_FILL);
	//Название корабля
	Text_Draw(	FontConsole,
				(int)((float)iWidth * 0.1 + (float)iHeight * 0.8 + 12),
				(int)((float)iHeight * 0.1 + 26),
				shpPlayer->GetName(), 1.0, 0, 255, _WHITE_);
	//Координаты
	char chtmpText[50];
	sprintf_s(chtmpText, "X:%0.2f Y:%0.2f", shpPlayer->fXposGlob, shpPlayer->fYposGlob);
	Text_Draw(	FontConsole,					// Наш идентификатор шрифта
				(int)((float)iWidth * 0.1 + (float)iHeight * 0.8 + 40),// Координаты
				(int)((float)iHeight * 0.1 + 46),// Координаты
				chtmpText,						// Сам текст
				1.0,							// Коэффициент увеличения
				0,								// Дополнительное растояние между символами
				255,							// Альфа
				_WHITE_);						// цвет	

	//Рисуем метку цели на карте
	if (shpPlayer->bMapCoordTarget)
	{
		float fXCentre, fYCentre;
		fXCentre = (float)iWidth* 0.1 + (float)iHeight * 0.4;
		fYCentre = (float)iHeight * 0.1 + (float)iHeight * 0.4;

		//float fMapCoordTargetX, fMapCoordTargetY;
		fMapCoordTargetX = fXCentre + shpPlayer->fMapCoordTargetX * ssysCurStarSys->fZoomForMap;
		fMapCoordTargetY = fYCentre + shpPlayer->fMapCoordTargetY * ssysCurStarSys->fZoomForMap;

		//Рисуем линии пересечения точки маршрута/цели
		//void Pr2D_Line(float X1, float Y1, float X2, float Y2, int Color, BYTE Alpha = 255, int Flags = PR_DEFAULT);
		//Pr2D_Rect((float)iWidth * 0.1, (float)iHeight * 0.1, (float)iHeight * 0.8, (float)iHeight * 0.8, _LightBLUE_, 150, PR_FILL);
		Pr2D_Line(	(float)iWidth * 0.1, fMapCoordTargetY,
					(float)iWidth * 0.1 + (float)iHeight * 0.8, fMapCoordTargetY, _WHITE_, 100, PR_DEFAULT);
		Pr2D_Line(	fMapCoordTargetX, (float)iHeight * 0.1,
					fMapCoordTargetX, (float)iHeight * 0.1 + (float)iHeight * 0.8, _WHITE_, 100, PR_DEFAULT);

		//Рисуем круг точки маршрута/цели
		Pr2D_Circle(fMapCoordTargetX, fMapCoordTargetY, 3, _WHITE_, 255, 32, PR_FILL);
		Pr2D_Circle(fMapCoordTargetX, fMapCoordTargetY, 15, _WHITE_, 200, 32, PR_DEFAULT);
		Pr2D_Circle(fMapCoordTargetX, fMapCoordTargetY, 14, _WHITE_, 200, 32, PR_DEFAULT);
		Pr2D_Circle(fMapCoordTargetX, fMapCoordTargetY, 13, _WHITE_, 200, 32, PR_DEFAULT);
	}
		
	//Рисуем Кнопки
	btnSystemMap->bEnabled = true;
	btnGalaxyMap->bEnabled = true;
	btnExitCancel->bEnabled = true;

	btnSystemMap->Draw();
	btnGalaxyMap->Draw();
	btnExitCancel->Draw();

	//Курсор: рисуем координаты над указателем
	if (
		X > (float)iWidth * 0.1
		&&
		X < (float)iWidth * 0.1 + (float)iHeight * 0.8
		)
		if (
			Y >(float)iHeight * 0.1
			&&
			Y < (float)iHeight * 0.1 + (float)iHeight * 0.8
			)
		{
			char chtmpText[50];
			sprintf_s(chtmpText, "X:%0.2f Y:%0.2f", (float)(-1 * ((fXCentre - (float)X) / ssysCurStarSys->fZoomForMap)),
							(float)(-1 * ((fYCentre - (float)Y) / ssysCurStarSys->fZoomForMap)));

			Text_Draw(	FontConsole,					// Наш идентификатор шрифта
						(int)(X),					// Координаты
						(int)(Y - 16),					// Координаты
						chtmpText,					// Сам текст
						1.0,						// Коэффициент увеличения
						0,							// Дополнительное растояние между символами
						255,						// Альфа
						_WHITE_);					// цвет			
		}

	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//===========================================================================
//---------------------------------------------------------------------------
//Статус: начальная загрузка, OMEGAInit
void MouseAndKeyboardZERO()
{
	//Рисуем рамку Игрового окна, толщина 10*5*5*5пикселей
	//void Pr2D_Rect( float X, float Y, float Width, float Height, int Color, BYTE Alpha = 255, int Flags = PR_DEFAULT ); 
	Pr2D_Rect(0, 0, iWidth, 10, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(iWidth - 5, 0, iWidth, iHeight, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(0, iHeight - 5, iWidth, iHeight, _LightBLUE_, 255, PR_FILL);
	Pr2D_Rect(0, 0, 4, iHeight, _LightBLUE_, 255, PR_FILL);

	//Интерфейс
	DrawInterfaceSpace();

	return;
}
//---------------------------------------------------------------------------
//Первый экран после загрузки ресурсов, Стартовое меню
void MouseAndKeyboardSTARTMENU()
{
	//ФИКС: резкий поворот на 180 градусов при сближении с курсором центра Спутника
	if (M_Distance(X, Y,
		objMainMenuObject->fXposGlob + objMainMenuObject->GetWidth() / 2,
		objMainMenuObject->fYposGlob + objMainMenuObject->GetHeight() / 2)
		< 10)
		objMainMenuObject->SetInteractive(false);
	else
		objMainMenuObject->SetInteractive(true);
	//КонецФИКС

	//всегда задаем перемещение Спутника к курсору
	//objMainMenuObject->fMoveRight = (X+1 - (objMainMenuObject->fXposGlob + objMainMenuObject->GetWidth() / 2)) / 100;
	//objMainMenuObject->fMoveDown = (Y+1 - (objMainMenuObject->fYposGlob + objMainMenuObject->GetHeight() / 2)) / 100;
	//устанавливаем угол наклона текстуры	
	if (objMainMenuObject->GetInteractive())
	{
		objMainMenuObject->fAngle = M_FindAngle(X, Y, (objMainMenuObject->fXposGlob + objMainMenuObject->GetWidth() / 2),
			(objMainMenuObject->fYposGlob + objMainMenuObject->GetHeight() / 2)) + 90;
		objMainMenuObject->SetXY(objMainMenuObject->fXposGlob, objMainMenuObject->fYposGlob);
	}

	// Esc: По нажатию Escape завершаем работу
	if (Key_Press(K_ESCAPE))
	{
		//OE_Quit();
	}

	// Mouse: нажатие кнопки
	if (Mouse_Press(M_LBUTTON))
	{
		//Щелчок по кнопке "Новая игра"
		if (btnNewGame->bFocus)
		{
			//Готовим объекты
			LoadGameSpaceObject();
			//Останавливаем фоновую музыку Стартового Меню
			Snd_Stop(sndStartMenuTheme);
			//Меняем статус
			//*****Пока что на режим Игра:Космос
			iGameStatus = _GAMESPACE_;
		}
		else

		//Щелчок по кнопке "Настройки"
		if (btnConfig->bFocus)
			iGameStatus = _CONFIG_;
		else
		//Щелчок по кнопке "Об игре"
		if (btnAbout->bFocus)
			iGameStatus = _ABOUT_;
		else
		//Щелчок по кнопке "Выход"
		if (btnExit->bFocus)
			OE_Quit();
				
	}
	
	return;
}
//---------------------------------------------------------------------------
void MouseAndKeyboardABOUT()
{
	// Esc: По нажатию Escape выходим в главное меню
	if (Key_Press(K_ESCAPE))
	{
		iGameStatus = _STARTMENU_;
	}

	// Mouse: нажатие кнопки
	if (Mouse_Press(M_LBUTTON))
	{
		iGameStatus = _STARTMENU_;
	}

	return;
}
//---------------------------------------------------------------------------
void MouseAndKeyboardCONFIG()
{
	// Esc: По нажатию Escape выходим в главное меню
	if (Key_Press(K_ESCAPE))
	{
		iGameStatus = _STARTMENU_;
	}

	// Mouse: нажатие кнопки
	if (Mouse_Press(M_LBUTTON))
	{
		iGameStatus = _STARTMENU_;
	}

	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//Игра: Режим в космосе
void MouseAndKeyboardSPACE()
{
	//Открыть окно карты
	if (Key_Press(K_M))
	{
		iGameStatus = _GAMESPACEMAP_;
	}

	//Форсаж
	if (Key_Press(K_TAB))
	{
		shpPlayer->ActivatedForsage();
	}

	//Смещение влево/вправо
	if (Key_Down(K_A))
	{
		shpPlayer->MoveToLeft();
	}
	if (Key_Down(K_D))
	{ 
		shpPlayer->MoveToRight();
	}

	//Поворот корабля (рысканье)
	if (Key_Down(K_Q))//if (Key_Down(K_A))
	{
		shpPlayer->AngleToLeft();
		//shpPlayer->fAngle -= 1*shpPlayer->fManoeuvrability;
	}
	if (Key_Down(K_E))//if (Key_Down(K_D))
	{
		shpPlayer->AngleToRight();
		//shpPlayer->fAngle += 1*shpPlayer->fManoeuvrability;
	}

	//Скорость (движение вперед/назад)
	if (Mouse_WheelUp())
	{
		shpPlayer->ChangeSpeed(+5);
		/*if ((shpPlayer->fSpeedTMP) <= shpPlayer->fSpeedMax - 5)
		shpPlayer->fSpeedTMP += 5;*/
	}
	if (Mouse_WheelDown())
	{
		shpPlayer->ChangeSpeed(-5);
		/*if (shpPlayer->fSpeedTMP >= -(shpPlayer->fSpeedMax * 0.15) + 5)
		shpPlayer->fSpeedTMP -= 5;*/
	}
	if (Key_Press(K_SPACE))
	{
		//останавливаем корабль
		shpPlayer->ChangeSpeed(0);
	}
	if (Key_Press(K_W))
	{
		//Полный вперед!
		shpPlayer->ChangeSpeed(100);
	}

	//Масштаб
	if (Key_Press(K_ADD))
	{
		if (fGameZoom == 4.0)
			fGameZoom = 5.0;
		if (fGameZoom == 3.0)
			fGameZoom = 4.0;
		if (fGameZoom == 2.5)
			fGameZoom = 3.0;
		if (fGameZoom == 2.0)
			fGameZoom = 2.5;
		if (fGameZoom == 1.5)
			fGameZoom = 2.0;
		if (fGameZoom == 1.0)
			fGameZoom = 1.5;
		if (fGameZoom == 0.75)
			fGameZoom = 1.0;
		if (fGameZoom == 0.5)
			fGameZoom = 0.75;
		/*if (fGameZoom < 0.5)
			fGameZoom = 0.5;*/
		if (fGameZoom == 0.25)
			fGameZoom = 0.5;
		if (fGameZoom < 0.25)
			fGameZoom = 0.25;
	}	
	if (Key_Press(K_SUBTRACT))
	{
		if (fGameZoom <= 0.25)
			fGameZoom = 0.1;
		if (fGameZoom == 0.5)
			fGameZoom = 0.25;
		/*if (fGameZoom <= 0.5)
			fGameZoom = 0.2;*/
		if (fGameZoom == 0.75)
			fGameZoom = 0.5;
		if (fGameZoom == 1.0)
			fGameZoom = 0.75;
		if (fGameZoom == 1.5)
			fGameZoom = 1.0;
		if (fGameZoom == 2.0)
			fGameZoom = 1.5;
		if (fGameZoom == 2.5)
			fGameZoom = 2.0;
		if (fGameZoom == 3.0)
			fGameZoom = 2.5;
		if (fGameZoom == 4.0)
			fGameZoom = 3.0;
		if (fGameZoom == 5.0)
			fGameZoom = 4.0;
	}	
	
	//Возврат в Главное Меню
	if (Key_Press(K_ESCAPE))
	{
		LoadStartMenuObject();
		iGameStatus = _STARTMENU_;
	}

	return;
}
//---------------------------------------------------------------------------
//Игра: Режим в космосе - карта
void MouseAndKeyboardSPACEMAP()
{
	// Mouse: нажатие кнопки
	//Убираем метку до цели
	if (Mouse_Down(M_RBUTTON))
	{
		shpPlayer->bMapCoordTarget = false;
	}

	//Нажатие на кнопку справа - выбор космообъекта
	if (Mouse_Down(M_LBUTTON))
	{
		vector<clButtonMainMenu>::iterator iBt = ssysCurStarSys->vecButtons.begin();
		while (iBt != ssysCurStarSys->vecButtons.end())
		{
			if (iBt->bFocus)
			{
				//Ставим точку маршрута "привязанному" кнопке объекту
				shpPlayer->bMapCoordTarget = true;
				shpPlayer->fMapCoordTargetX = iBt->fXposGlob;
				shpPlayer->fMapCoordTargetY = iBt->fYposGlob;
			}
			++iBt;
		}
	}

	//Нажатие на кнопки сверху карты (Система, Галактика, Закрыть)
	if (Mouse_Down(M_LBUTTON))
	{
		//Кнопка "Закрыть"
		if (btnExitCancel->bFocus)
		{
			iGameStatus = _GAMESPACE_;
		}
	}
		
	//Ставим метку до цели на карте
	if (Mouse_Down(M_LBUTTON))
	//Движение мыши в зоне квадрата карты
	if (
		X > (float)iWidth * 0.1
		&&
		X < (float)iWidth * 0.1 + (float)iHeight * 0.8
		)
		if (
			Y > (float)iHeight * 0.1
			&&
			Y < (float)iHeight * 0.1 + (float)iHeight * 0.8
			)
		{
			float fXCentre, fYCentre;
			fXCentre = (float)iWidth* 0.1 + (float)iHeight * 0.4;
			fYCentre = (float)iHeight * 0.1 + (float)iHeight * 0.4;

			//Выбор точки маршрута
			shpPlayer->bMapCoordTarget = true;
			shpPlayer->fMapCoordTargetX = -1 * ((fXCentre - (float)X) / ssysCurStarSys->fZoomForMap);
			shpPlayer->fMapCoordTargetY = -1 * ((fYCentre - (float)Y) / ssysCurStarSys->fZoomForMap);
		}




	//Закрыть окно карты
	if (Key_Press(K_ESCAPE) || Key_Press(K_M))
	{
		iGameStatus = _GAMESPACE_;
	}

	return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//По умолчанию (тестирование)
void MouseAndKeyboardDEFAULT()
{
	// Mouse: нажатие кнопки
	if (Mouse_Down(M_LBUTTON))
	{
		/*
		objOne->SetInteractive(true);
		objOne->fMoveRight = (X - (objOne->fXpos + objOne->GetWidth() / 2)) / 100;
		objOne->fMoveDown = (Y - (objOne->fYpos + objOne->GetHeight() / 2)) / 100;
		*/
	}

	// ~: Открываем консоль (тильда - 0xc0)
	if (Key_Press(0xc0))
	{
		Console_Active(1);
	}

	// Esc: По нажатию Escape завершаем работу
	if (Key_Press(K_ESCAPE))
	{
		OE_Quit();
	}

	// 
	if (Key_Down(K_W))
	{
		//objOne->fMoveDown = -1;
	}
	// 
	if (Key_Down(K_D))
	{
		//objOne->fMoveRight = 1;
	}
	if (Key_Down(K_S))
	{
		//objOne->fMoveDown = 1;
	}
	// 
	if (Key_Down(K_A))
	{
		//objOne->fMoveRight = -1;
	}

	return;
}
//---------------------------------------------------------------------------
//===========================================================================
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

