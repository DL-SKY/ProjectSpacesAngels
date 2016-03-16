//---------------------------------------------------------------------------
/* Project Microsoft Visual Studio Community 2013 */
//---------------------------------------------------------------------------

//Файл настроек
const char *chFileConfig = "..\\ini\\config.ini";
//Временный файл номера сборки
const char *chFileBuildNumber = "..\\tmp\\BuildVersion.txt";
//Скриншот:
const char *chPathScreen = "..\\screenshots";
const char *chFileScreen = "scr";

//Координаты мыши
int X = 0;
int Y = 0;

//Текущая звездная система
int iIDCurStarSystem;

//Масштаб
float fGameZoom = 1.0;
float fPositionCoef = 100.0;

// Текущий кадр спрайта
unsigned int N = 1;

// Количество проходов blur
int iCountBlur = 10; 

//Настройки+локализация
bool bFullScreen = false;
int iWidth = 800;
int iHeight = 600;
bool bVSync = 1;
//int iAnisotropy = 4;
bool bSoundOn = true;
int iVolume = 100;
int iLanguage = _RUS_;
bool bShowFPS = true;
int iBPP = 32;				//Бит на пиксель
int iRefresh = 0;			//Частота обновления (Гц): 0-автоопределение Герц движком, 1-настройка Windows
bool bConsole = false;
bool bViewInterface = true;	//Переменная отрисовки интерфейса если исправен дисплей коробля или навигационная система и пр.

//Локализация
//char *chTest1 = new char(255);
//char *chTest2 = new char(255);
char chLocal[255][255];
char chLocalShip[255][255];

//Имя игрока
char *chPlayerName = new char[50];

