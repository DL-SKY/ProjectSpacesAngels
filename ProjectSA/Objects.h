//---------------------------------------------------------------------------
/* Project Microsoft Visual Studio Community 2013 */
//---------------------------------------------------------------------------

//Объекты
//Космический объект Стартового Меню
clObject *objMainMenuObject = new clObject();
clObject *objMainMenuPlanet = new clObject();
clBigStar *starMainMenuStar = new clBigStar();
//Кнопки Главного Меню
clButtonMainMenu *btnContGame = new clButtonMainMenu();
clButtonMainMenu *btnNewGame = new clButtonMainMenu();
clButtonMainMenu *btnLoadGame = new clButtonMainMenu();
clButtonMainMenu *btnConfig = new clButtonMainMenu();
clButtonMainMenu *btnAbout = new clButtonMainMenu();
clButtonMainMenu *btnExit = new clButtonMainMenu();
//Кнопки Карты
clButtonMainMenu *btnSystemMap = new clButtonMainMenu();
clButtonMainMenu *btnGalaxyMap = new clButtonMainMenu();
clButtonMainMenu *btnExitCancel = new clButtonMainMenu();
//Вектор звезд Стартового меню
vector<clSmallStar> vecSmallStars;
//Вектор моделей кораблей
vector<clSpaceShip> vecSpaceShips;
//Вектор звездных систем
vector<clStarSystem> vecStarSystems;
clStarSystem *ssysTempStarSys = new clStarSystem;
clStarSystem *ssysCurStarSys = new clStarSystem;
//Игра: космос
clSpaceShip *shpPlayer = new clSpaceShip();
clBigStar *star0 = new clBigStar();
clPlanet *plPlanet0 = new clPlanet();
const int iBICount = 10;							// Кол-во элементов в массиве кнопок интерфейса
clButtonInterface *btiButtonsInterface[iBICount];	// = new clButtonInterface();