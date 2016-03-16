//---------------------------------------------------------------------------
/* Project Microsoft Visual Studio Community 2013 */
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifndef TypedefH
#define TypedefH
//---------------------------------------------------------------------------
//���� ������ �������
#define _WORK_ float(0.0)
#define _ALPHA_ float(0.1)
#define _BETA_ float(0.5)
#define _PRERELEASE_ float(0.9)
#define _RELEASE_ float(1.0)

//���� ��������� (������) ����������� �� ������
#define _ZERO_ int(0)			//��������� �����, �������� ��������
#define _STARTMENU_ int(1)		//������ ����� ����� �������� ��������, "��������� ����"
#define _ABOUT_ int(2)			//���� "�� ����"
#define _CONFIG_ int(3)			//���� "���������"
#define _NEWGAME_ int(4)		//���� "����� ����"
#define _ZERO5_ int(5)			//
#define _ZERO6_ int(6)			//
#define _LOADGAME_ int(7)		//���� "���������"
#define _ZERO8_ int(8)			//
#define _GAMESPACE_ int(9)		//����: ����� � �������
#define _GAMESPACEMAP_ int(10)	//����: ����� � ������� - �����

//�����������
//��� ������: https://ru.wikipedia.org/wiki/%D0%9E%D0%B1%D1%89%D0%B5%D1%80%D0%BE%D1%81%D1%81%D0%B8%D0%B9%D1%81%D0%BA%D0%B8%D0%B9_%D0%BA%D0%BB%D0%B0%D1%81%D1%81%D0%B8%D1%84%D0%B8%D0%BA%D0%B0%D1%82%D0%BE%D1%80_%D1%81%D1%82%D1%80%D0%B0%D0%BD_%D0%BC%D0%B8%D1%80%D0%B0
#define _RUS_ int(643)
#define _USA_ int(840)
#define _FRA_ int(250)
#define _DEU_ int(276)

//�����
//���� � BMP � ������� - BGR   
#define _RED_ 0x0000FF
#define _BLUE_ 0xFF0000
#define _BLACK_ 0x000000
#define _WHITE_ 0xFFFFFF
#define _TranspGREEN_ 0x00FF4C
#define _LightBLUE_ 0xFF9B00
#define _ColdBLUE_ 0xFFEBCC
#define _ShieldBLUE_ 0xFFF000
#define _SpaceMainMenu_ 0x331F00
//---------------------------------------------------------------------------
#endif


/*
%c - ������
%s - ������ ��������
%d, i - ����� ���������� �� ������
%o - ����� ������������
%u - ����� ���������� ��� �����
%x, X - ����� �����������������
%f - ������� ����� � ������������� �������
%e, E - ������� ����� � ������� �������
%g, G - ������� ����� � ������� ��� ������������� �������
%p - ��������� (� ����������������� ����)

#include <stdio.h>

int main( void )
{
char  buffer[200], s[] = "computer", c = 'l';
int   i = 35, j;
float fp = 1.7320534f;

// Format and print various data:
j  = sprintf_s( buffer, 200,     "   String:    %s\n", s );
j += sprintf_s( buffer + j, 200 - j, "   Character: %c\n", c );
j += sprintf_s( buffer + j, 200 - j, "   Integer:   %d\n", i );
j += sprintf_s( buffer + j, 200 - j, "   Real:      %f\n", fp );

printf_s( "Output:\n%s\ncharacter count = %d\n", buffer, j );
}
*/

