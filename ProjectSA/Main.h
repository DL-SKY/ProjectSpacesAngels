//---------------------------------------------------------------------------
/* Project Microsoft Visual Studio Community 2013 */
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
int main();										//����� �����
void BuildIncrement();							//����������� ������ ������
bool FileExists(const char *_chFileName);		//�������� ������� �����
int ReadConfig();								//�������� �������� ����
int LoadLocalization();							//�������� ����� �����������
int LoadFonts();								//�������� �������
int LoadTextures();								//�������� �������
void LoadShips();								//�������� �������� �� INI
void LoadSystems();								//�������� �������� ������ �� INI
void LoadStartMenuObject();						//���������� � ���������� ����
void LoadGameSpaceObject();						//���������� � ���������� ���� "����: ������"
void ErrorLog(int _iErr);						//��� ������
void Loading(int _iLoad);						//��������� ������ ��������

//������� ������ OMEGA Engine
void OMEGATimer01KeyboardMouse();				//������ �1, ���� � �����������
void OMEGATimer02Anumation();					//������ �2, �������� ������� � ��������
void OMEGATimer03UpdateObject();				//������ �3 ���������� ��������
void OMEGALoad();								//����� ��������
void OMEGAInit();								//
void OMEGADraw();								//
void OMEGAQuit();								//

//���������� �������
void ConsoleArmageddon();						//�������� �������� � ���� = 20.0
void ConsoleVisibleInterface();					//���/���� ������ �������� (����������� ����������)
void ConsoleFPS();								//���/���� FPS
void ConsoleHelp();								//����� ������ ������
void ConsoleLayoutRus();						//������������ � ������� ����������
void ConsoleLayoutEng();						//������������ � ���������� ����������

//������� ���������� ��������
void UpdateFrameSpace();						//���������� �������� � ������ � ������ ������ � �������

//������� ���������
void PaintFrame(int _iX, int _iY,				//������ �����
				int _iWidth, int _iHeight,
				int _iThick, int _iColour,
				int _iAlpha);
void PaintStars();								//������ ������
void DrawFPS();									//������ ���������� � FPS
void DrawCursor();								//������ ������
void DrawInterfaceSpace();						//������ ��������� � �������
void DrawFrameDEFAULT();
void DrawFrameSTARTMENU();						//��������� ����
void DrawFrameABOUT();							//���� "�� ����"
void DrawFrameCONFIG();							//���� "���������"

void DrawFrameSPACE1();							//����: ����� � ������� ��� �������������
void DrawFrameSPACE2();							//����: ����� � ������� ��� ���.��������
void DrawFrameSPACEMAP();						//����: ����� � ������� �����

//������� ��������� ������� �������������
void MouseAndKeyboardZERO();					//������: ��������� ��������, OMEGAInit
void MouseAndKeyboardSTARTMENU();				//������ ����� ����� �������� ��������, ��������� ����
void MouseAndKeyboardABOUT();					//"�� ����"
void MouseAndKeyboardCONFIG();					//"���������"

void MouseAndKeyboardSPACE();					//����: ����� � �������
void MouseAndKeyboardSPACEMAP();				//����: ����� � ������� - �����


void MouseAndKeyboardDEFAULT();					//�� ��������� (������������)







//---------------------------------------------------------------------------
#endif