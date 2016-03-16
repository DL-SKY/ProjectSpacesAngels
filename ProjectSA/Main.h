//---------------------------------------------------------------------------
/* Project Microsoft Visual Studio Community 2013 */
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
int main();										//Точка входа
void BuildIncrement();							//Автоподсчет номера сборки
bool FileExists(const char *_chFileName);		//Проверка наличия файла
int ReadConfig();								//Загрузка настроек игры
int LoadLocalization();							//Загрузка файла локализации
int LoadFonts();								//Загрузка шрифтов
int LoadTextures();								//Загрузка текстур
void LoadShips();								//Загрузка кораблей из INI
void LoadSystems();								//Загрузка звездных систем из INI
void LoadStartMenuObject();						//Подготовка к построению Меню
void LoadGameSpaceObject();						//Подготовка к построению окна "Игра: космос"
void ErrorLog(int _iErr);						//Лог ошибки
void Loading(int _iLoad);						//Отрисовка экрана Загрузки

//Функции движка OMEGA Engine
void OMEGATimer01KeyboardMouse();				//Таймер №1, мышь и келавиатура
void OMEGATimer02Anumation();					//Таймер №2, анимация курсора и объектов
void OMEGATimer03UpdateObject();				//Таймер №3 Обновление объектов
void OMEGALoad();								//Экран загрузки
void OMEGAInit();								//
void OMEGADraw();								//
void OMEGAQuit();								//

//Консольные функции
void ConsoleArmageddon();						//Скорость Спутника в Меню = 20.0
void ConsoleVisibleInterface();					//Вкл/выкл работы сенсоров (отображение интерфейса)
void ConsoleFPS();								//Вкл/выкл FPS
void ConsoleHelp();								//Вывод списка команд
void ConsoleLayoutRus();						//Переключение в русскую расскладку
void ConsoleLayoutEng();						//Переключение в английскую расскладку

//Функции обновления картинки
void UpdateFrameSpace();						//Обновление картинки и данных в режиме полета в космосе

//Функции рисования
void PaintFrame(int _iX, int _iY,				//Рисуем рамку
				int _iWidth, int _iHeight,
				int _iThick, int _iColour,
				int _iAlpha);
void PaintStars();								//Рисуем звезды
void DrawFPS();									//Рисуем информацию о FPS
void DrawCursor();								//Рисуем курсор
void DrawInterfaceSpace();						//Рисуем Интерфейс в космосе
void DrawFrameDEFAULT();
void DrawFrameSTARTMENU();						//Стартовое меню
void DrawFrameABOUT();							//Окно "Об игре"
void DrawFrameCONFIG();							//Окно "Настройки"

void DrawFrameSPACE1();							//Игра: Режим в космосе для постобработки
void DrawFrameSPACE2();							//Игра: Режим в космосе без доп.эффектов
void DrawFrameSPACEMAP();						//Игра: Режим в космосе Карта

//Функции обработки событий манипуляторов
void MouseAndKeyboardZERO();					//Статус: начальная загрузка, OMEGAInit
void MouseAndKeyboardSTARTMENU();				//Первый экран после загрузки ресурсов, Стартовое меню
void MouseAndKeyboardABOUT();					//"Об игре"
void MouseAndKeyboardCONFIG();					//"Настройки"

void MouseAndKeyboardSPACE();					//Игра: Режим в космосе
void MouseAndKeyboardSPACEMAP();				//Игра: Режим в космосе - карта


void MouseAndKeyboardDEFAULT();					//По умолчанию (тестирование)







//---------------------------------------------------------------------------
#endif