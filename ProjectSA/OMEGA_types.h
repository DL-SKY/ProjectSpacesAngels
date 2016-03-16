////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////                                                                        ////
////     01010101   010        010   0101010101   0101010101      0110      ////
////    01      01  01010    10101   01           01             01  10     ////
////   01        01 01 010  101 01   01           01             01  10     ////
////   01        01 01  010010  01   0101010101   01            01    10    ////
////    01      01  01    00    01   01           01    0101    01010110    ////
////     01    01   01          01   01           01      01   01      10   ////
////   0101    0101 01          01   0101010101   0101010101   01      10   ////
////                                                                        ////
////                                                                        ////
////   0101010101   010     01   0101010101   01   010     01   0101010101  ////
////   01           010     01   01           01   010     01   01          ////
////   01           01 01   01   01           01   01 01   01   01          ////
////   0101010101   01  01  01   01           01   01  01  01   0101010101  ////
////   01           01   01 01   01    0101   01   01   01 01   01          ////
////   01           01    0101   01      01   01   01    0101   01          ////
////   0101010101   01     001   0101010101   01   01     011   0101010101  ////
////                                                                        ////
////   Версия    : 1.14                                                     ////
////   Дата      : 13.11.07                                                 ////
////   eСтраничка: http://www.isada.mirgames.ru/omega.php                   ////
////                                                                        ////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////                                                                        ////
////  АВТОР: Andru 'aka' КЕМКА АНДРЕЙ                                       ////
////  Mail: dr.andru@gmail.com                                              ////
////  Site: http://isada.mirgames.ru                                        ////
////                                                                        ////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////                                                                        ////
////             Л И Ц Е Н З И О Н Н О Е  С О Г Л А Ш Е Н И Е :             ////
////                                                                        ////
////    Всё лицензионное соглашение приведено в соответствующих файлах      ////
////  и в справке к движку. Там же указаны все авторские права.             ////
////                                                             (С)2007    ////
////                                                                        ////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef _OMEGA_types_
#define _OMEGA_types_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#endif

#include <windows.h>

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;

struct TMemory
{
  void* Ptr;
  DWORD Size;
};
typedef TMemory *PMemory;

//----------------------------------------------------------------------------//
//-----------------------------  E N G I N E  --------------------------------//
//----------------------------------------------------------------------------//

// S T A R T
typedef void ( APIENTRY * OE_Init_ )( BYTE zBits, BYTE stencilBits );

typedef void ( APIENTRY * OE_Init2_ )( DWORD hwnd );

typedef void ( APIENTRY * OE_Quit_ )(void);

// M A I N
#define SYS_DRAW            0x0
#define SYS_INIT            0x1
#define SYS_QUIT            0x2
#define SYS_LOAD            0x3
#define SYS_WNDPROC_BEFORE  0x4
#define SYS_WNDPROC_AFTER   0x5
#define SYS_CONSOLE_MESSAGE 0x6

typedef void ( APIENTRY * OE_RegProcedure_ )(
                                              BYTE  PType,
                                              void* );

typedef void ( APIENTRY * OE_UnRegProcedure_ )( BYTE PType );

struct TOTimer
{
	bool   Active;
  DWORD  Interval;
  double LastTime;
  int    Precision;
  void*  OnTimer;
  DWORD  Reserved;
};
typedef TOTimer *POTimer;

typedef POTimer ( APIENTRY * Timer_Create_ )(
                                             void*,
                                             int   Interval,
                                             int   Precision );

typedef void ( APIENTRY * Timer_Free_ )( POTimer& Timer );
typedef void ( APIENTRY * Timer_FreeAll_ )(void);

// O P T I O N S
//FLAGS
#define FLAG_COLOR_BUFFER_CLEAR 0x000001
#define FLAG_CROP_UNVISIBLE_OBJ 0x000002
#define FLAG_RESOLUTION_CORRECT 0x000004
#define FLAG_SHOW_WARNINGS      0x000008
#define FLAG_SHOW_ERRORS        0x000010
#define FLAG_PAUSE              0x000020
#define FLAG_AUTO_PAUSE         0x000040

typedef void ( APIENTRY * OE_Enable_ )( int What );

typedef void ( APIENTRY * OE_Disable_ )( int What );

//WINDOW
typedef void ( APIENTRY * OE_SetWndOnTop_ )( bool Enable );

typedef void ( APIENTRY * OE_SetWndPosition_ )( int X, int Y );

typedef void ( APIENTRY * OE_SetWndName_ )( char* NewName );

typedef void ( APIENTRY * OE_ShowCursor_ )( bool Show );

typedef void ( APIENTRY * OE_ResizeWindow_ )( int Width, int Height );

//SCREEN
typedef void ( APIENTRY * OE_SetScreenOptions_ )(
                                                  int  Width,
                                                  int  Height,
                                                  int  BPP,
                                                  int  Refresh,
                                                  bool FullScreen,
                                                  bool WaitVSync );

typedef void ( APIENTRY * OE_ChangeScreenOptions_ )(
                                                     int  Width,
                                                     int  Height,
                                                     int  BPP,
                                                     int  Refresh,
                                                     bool FullScreen,
                                                     bool WaitVSync );

typedef void ( APIENTRY * OE_SetResolutionDependence_ )(
                                                         int NormalResX,
                                                         int NormalResY );

typedef void ( APIENTRY * OE_SetVSync_ )( bool WaitVSync );

//GET
struct TOptions
{
  bool app_FullScreen;
  int  wnd_X;
  int  wnd_Y;
  int  wnd_Width;
  int  wnd_Height;
  int  scr_Width;
  int  scr_Height;
  int  scr_BPP;
  BYTE scr_Refresh;
  bool scr_VSync;
  bool Reserved;
};
typedef TOptions *POptions;

typedef POptions ( APIENTRY * OE_GetOptions_ )(void);

// A D D I T I O N A L
typedef void ( APIENTRY * OE_SetAdvancedOptions_ )(
                                                    bool UseLog,
                                                    bool AppCanClose,
                                                    bool HaltOnExit );

typedef int ( APIENTRY * OE_GetFPS_ )(void);

//----------------------------------------------------------------------------//
//----------------------------------  I N I  ---------------------------------//
//----------------------------------------------------------------------------//

typedef void ( APIENTRY * INI_LoadFromFile_ )( char* FileName );

typedef void ( APIENTRY * INI_LoadFromMemory_ )( PMemory Memory );

typedef void ( APIENTRY * INI_SaveToFile_ )( char* FileName );

typedef void ( APIENTRY * INI_Add_ )( char* Section, char* Key );

typedef char* ( APIENTRY * INI_ReadKeyStr_ )( char* Section, char* Key );

typedef int ( APIENTRY * INI_ReadKeyInt_ )( char* Section, char* Key );

typedef bool ( APIENTRY * INI_WriteKeyStr_ )( char* Section, char* Key, char* Value );

typedef bool ( APIENTRY * INI_WriteKeyInt_ )( char* Section, char* Key, int Value );

//----------------------------------------------------------------------------//
//-----------------------------  H T M L  L O G  -----------------------------//
//----------------------------------------------------------------------------//

#define LOGT_ERROR   0x0
#define LOGT_WARNING 0x1
#define LOGT_APP     0x2
#define LOGT_CONSOLE 0x3

typedef void ( APIENTRY * LOG_SetOptions_ )(
                                             char* clrBODY,
                                             char* clrTIME,
                                             char* clrENGINE,
                                             char* clrAPP,
                                             char* clrCONSOLE,
                                             char* clrMESS,
                                             char* clrWARNING,
                                             char* clrERROR,
                                             BYTE  sTIME,
                                             BYTE  sENGINE,
                                             BYTE  sAPP,
                                             BYTE  sCONSOLE,
                                             BYTE  sMESS,
                                             BYTE  sWARNING,
                                             BYTE  sERROR );

typedef void ( APIENTRY * LOG_Init_ )(
                                       char* FileName,
                                       bool  Create );

typedef void ( APIENTRY * LOG_AddMessage_ )(
                                             BYTE  MessageType,
                                             char* Text );

typedef void ( APIENTRY * Console_RegVariable_ )(
                                                  char* VarName,
                                                  int*  Variable );

typedef void ( APIENTRY * Console_RegProcedure_ )(
                                                   char* ProcName,
                                                   void* );

typedef void ( APIENTRY * LOG_AddLine_ )(
                                          int   Size,
                                          char* Color );

//----------------------------------------------------------------------------//
//------------------------------  I N P U T  ---------------------------------//
//----------------------------------------------------------------------------//

// K E Y B O A R D
#define K_LAYOUT_ENG "00000409"
#define K_LAYOUT_RUS "00000419"

#define K_BACKSPACE 0x8
#define K_TAB       0x9
#define K_ENTER     0xd
#define K_SHIFT     0x10
#define K_CONTROL   0x11
#define K_ALT       0x12
#define K_ESCAPE    0x1b
#define K_SPACE     0x20
#define K_PAGEUP    0x21
#define K_PAGEDOWN  0x22
#define K_END       0x23
#define K_HOME      0x24
#define K_SNAPSHOT  0x2C
#define K_INSERT    0x2D
#define K_DELETE    0x2E
#define K_LEFT      0x25
#define K_UP        0x26
#define K_RIGHT     0x27
#define K_DOWN      0x28
#define K_0         0x30
#define K_1         0x31
#define K_2         0x32
#define K_3         0x33
#define K_4         0x34
#define K_5         0x35
#define K_6         0x36
#define K_7         0x37
#define K_8         0x38
#define K_9         0x39
#define K_NUMPAD0   0x60
#define K_NUMPAD1   0x61
#define K_NUMPAD2   0x62
#define K_NUMPAD3   0x63
#define K_NUMPAD4   0x64
#define K_NUMPAD5   0x65
#define K_NUMPAD6   0x66
#define K_NUMPAD7   0x67
#define K_NUMPAD8   0x68
#define K_NUMPAD9   0x69
#define K_MULTIPLY  0x6A
#define K_ADD       0x6B
#define K_SEPARATOR 0x6C
#define K_SUBTRACT  0x6D
#define K_DECIMAL   0x6E
#define K_DIVIDE    0x6F
#define K_A         0x41
#define K_B         0x42
#define K_C         0x43
#define K_D         0x44
#define K_E         0x45
#define K_F         0x46
#define K_G         0x47
#define K_H         0x48
#define K_I         0x49
#define K_J         0x4a
#define K_K         0x4b
#define K_L         0x4c
#define K_M         0x4d
#define K_N         0x4e
#define K_O         0x4f
#define K_P         0x50
#define K_Q         0x51
#define K_R         0x52
#define K_S         0x53
#define K_T         0x54
#define K_U         0x55
#define K_V         0x56
#define K_W         0x57
#define K_X         0x58
#define K_Y         0x59
#define K_Z         0x5a
#define K_F1        0x70
#define K_F2        0x71
#define K_F3        0x72
#define K_F4        0x73
#define K_F5        0x74
#define K_F6        0x75
#define K_F7        0x76
#define K_F8        0x77
#define K_F9        0x78
#define K_F10       0x79
#define K_F11       0x7a
#define K_F12       0x7b


typedef void ( APIENTRY * Key_LoadLayout_ )( char* Layout );

typedef bool ( APIENTRY * KeyEx_Down_ )( BYTE KeyCode );

typedef bool ( APIENTRY * Key_Down_ )( BYTE KeyCode );

typedef bool ( APIENTRY * Key_Press_ )( BYTE KeyCode );

typedef BYTE ( APIENTRY * Key_LastDown_ )(void);

typedef BYTE ( APIENTRY * Key_LastPress_ )(void);

typedef void ( APIENTRY * Key_BeginReadText_ )( char* StartText );

typedef char* ( APIENTRY * Key_EndReadText_ )(void);

typedef void ( APIENTRY * Key_MaxReadText_ )( int Count );

// M O U S E
#define M_RBUTTON 0x0
#define M_LBUTTON 0x1
#define M_MBUTTON 0x2

typedef int ( APIENTRY * MouseEx_X_ )(void);

typedef int ( APIENTRY * MouseEx_Y_ )(void);

typedef bool ( APIENTRY * MouseEx_Down_ )( BYTE Button );

typedef int ( APIENTRY * Mouse_X_ )(void);

typedef int ( APIENTRY * Mouse_Y_ )(void);

typedef bool ( APIENTRY * Mouse_Move_ )(void);

typedef void ( APIENTRY * Mouse_Lock_ )(void);

typedef int ( APIENTRY * Mouse_DeltaX_ )(void);

typedef int ( APIENTRY * Mouse_DeltaY_ )(void);

typedef bool ( APIENTRY * Mouse_Down_ )( BYTE Button );

typedef bool ( APIENTRY * Mouse_Press_ )( BYTE Button );

typedef bool ( APIENTRY * Mouse_Click_ )( BYTE Button );

typedef bool ( APIENTRY * Mouse_DblClick_ )( BYTE Button );

typedef bool ( APIENTRY * Mouse_WheelUp_ )(void);

typedef bool ( APIENTRY * Mouse_WheelDown_ )(void);

// J O Y P A D
#define JOY_0      0x000000

#define JOY_XLEFT  0x000001
#define JOY_XRIGHT 0x000002
#define JOY_YUP    0x000003
#define JOY_YDOWN  0x000004

#define JOY_BTN01  0x00000001
#define JOY_BTN02  0x00000002
#define JOY_BTN03  0x00000004
#define JOY_BTN04  0x00000008
#define JOY_BTN05  0x00000010
#define JOY_BTN06  0x00000020
#define JOY_BTN07  0x00000040
#define JOY_BTN08  0x00000080
#define JOY_BTN09  0x00000100
#define JOY_BTN10  0x00000200
#define JOY_BTN11  0x00000400
#define JOY_BTN12  0x00000800
#define JOY_BTN13  0x00001000
#define JOY_BTN14  0x00002000
#define JOY_BTN15  0x00004000
#define JOY_BTN16  0x00008000
#define JOY_BTN17  0x00010000
#define JOY_BTN18  0x00020000
#define JOY_BTN19  0x00040000
#define JOY_BTN20  0x00080000
#define JOY_BTN21  0x00100000
#define JOY_BTN22  0x00200000
#define JOY_BTN23  0x00400000
#define JOY_BTN24  0x00800000
#define JOY_BTN25  0x01000000
#define JOY_BTN26  0x02000000
#define JOY_BTN27  0x04000000
#define JOY_BTN28  0x08000000
#define JOY_BTN29  0x10000000
#define JOY_BTN30  0x20000000
#define JOY_BTN31  0x40000000
#define JOY_BTN32  0x80000000

typedef bool ( APIENTRY * Joy_Down_ )(
                                       int Joy,
                                       int Button );

typedef bool ( APIENTRY * Joy_Press_ )(
                                        int Joy,
                                        int Button );

typedef bool ( APIENTRY * Joy_AxePos_ )(
                                         int Joy,
                                         int Button );

//----------------------------------------------------------------------------//
//----------------------------  T E X T U R E S  -----------------------------//
//----------------------------------------------------------------------------//
struct TTexture
{
  DWORD ID;
  int   Width;
  int   Height;
  float U;
  float V;
  int   Flags;
  WORD  FramesX;
  WORD  FramesY;
  DWORD Reserved;
};
typedef TTexture *PTexture;

#define TEXTYPE_BJGWI 0x000000 // BMP, JPG, GIF, WMF, ICO
#define TEXTYPE_TGA   0x000001 // TGA

#define TEX_MIPMAP            0x000001
#define TEX_CLAMP             0x000002
#define TEX_REPEAT            0x001000
#define TEX_COMPRESS          0x000004

// Special
#define TEX_OMEGA_TO_2X2      0x000008

// Effects
#define TEX_GRAYSCALE         0x000010
#define TEX_INVERT            0x000020
#define TEX_USEMASK           0x000040

// Filtering
#define TEX_FILTER_NEAREST    0x000080
#define TEX_FILTER_LINEAR     0x000100
#define TEX_FILTER_BILINEAR   0x000200
#define TEX_FILTER_TRILINEAR  0x000400
#define TEX_FILTER_ANISOTROPY 0x000800

// Quality
#define TEX_QUALITY_LOW 	    0x400000
#define TEX_QUALITY_MEDIUM    0x800000

#define TEX_DEFAULT_2D        TEX_OMEGA_TO_2X2 | TEX_FILTER_LINEAR | TEX_CLAMP
#define TEX_DEFAULT_3D        TEX_MIPMAP | TEX_FILTER_TRILINEAR | TEX_CLAMP

typedef void ( APIENTRY * Tex_Filter_ )( PTexture& Texture, int Flags );

typedef void ( APIENTRY * Tex_SetAnisotropyLevel_ )( int Level );

typedef PTexture ( APIENTRY * Tex_CreateZero_ )(
                                                 int Width,
                                                 int Height,
                                                 int Flags );

typedef PTexture ( APIENTRY * Tex_LoadFromFile_ )(
                                                   char* FileName,
                                                   int   TransparentColor,
                                                   int   Flags );

typedef PTexture ( APIENTRY * Tex_LoadFromMemory_ )(
                                                     PMemory Memory,
                                                     int     FormatType,
                                                     int     TransparentColor,
                                                     int     Flags );

typedef void ( APIENTRY * Tex_Free_ )( PTexture &Texture );
typedef void ( APIENTRY * Tex_FreeAll_ )(void);

typedef void ( APIENTRY * Tex_LoadMaskFromFile_ )( char* FileName );

typedef void ( APIENTRY * Tex_LoadMaskFromMemory_ )( PMemory Memory );

typedef void ( APIENTRY * Tex_FreeMask_ )(void);

typedef void ( APIENTRY * Tex_SetFramesSize_ )(
                                       			    PTexture Texture,
                                       					WORD     FrameWidth,
                                       					WORD     FrameHeight );

//----------------------------------------------------------------------------//
//-----------------------  R E N D E R  T O  T E X T U R E  ------------------//
//----------------------------------------------------------------------------//

typedef void ( APIENTRY * Tex_BeginRenderIn_ )(
                                                PTexture Texture,
                                                bool     SaveOld,
                                                bool     RealSize,
                                                bool     Clear );

typedef void ( APIENTRY * Tex_EndRenderIn_ )(void);

//----------------------------------------------------------------------------//
//----------------------------  C A M E R A  2 D  ----------------------------//
//----------------------------------------------------------------------------//

struct TCamera2D
{
  float X;
  float Y;
  bool  Active;
  DWORD Reserved;
};
typedef TCamera2D *PCamera2D;


typedef PCamera2D ( APIENTRY * Cam2D_Create_ )(void);

typedef void ( APIENTRY * Cam2D_Free_ )( PCamera2D& YourCamera );
typedef void ( APIENTRY * Cam2D_FreeAll_ )(void);

typedef void ( APIENTRY * Cam2D_Set_ )( PCamera2D YourCamera );

//----------------------------------------------------------------------------//
//----------------------------------  F X  -----------------------------------//
//----------------------------------------------------------------------------//

#define FX_BLEND    0x000001
#define FX_FLIPX    0x000002
#define FX_FLIPY    0x000004
#define FX_COLORMIX 0x000008
#define FX_SCALE    0x000010
#define FX_VCHANGE  0x000020
#define FX_VCA      0x000040

#define FX_BLEND_NORMAL 0x000000
#define FX_BLEND_ADD    0x000001
#define FX_BLEND_MULT   0x000002
#define FX_BLEND_BLACK  0x000003
#define FX_BLEND_WHITE  0x000004
#define FX_BLEND_MASK   0x000005


#define FX_DEFAULT  FX_BLEND

typedef void ( APIENTRY * FX_SetColorMix_ )( int Color );

typedef void ( APIENTRY * FX_SetBlendMode_ )( int Mode );

typedef void ( APIENTRY * FX_SetScale_ )(
                                          float ScaleX,
                                          float ScaleY );

typedef void ( APIENTRY * FX_SetVertexes_ )(
                                             float X1, float Y1,
                                             float X2, float Y2,
                                             float X3, float Y3,
                                             float X4, float Y4 );

typedef void ( APIENTRY * FX_SetVCA_ )(
                                        int  C1, int  C2, int  C3, int  C4,
                                        BYTE A1, BYTE A2, BYTE A3, BYTE A4 );

// B L U R
typedef void ( APIENTRY * FX_Blur_SetTex_ )( PTexture TexToRender );

typedef void ( APIENTRY * FX_Blur_SetParams_ )( int Count, int MoveX, int MoveY );

typedef void ( APIENTRY * FX_Blur_Calc_ )( void*,
                                           float Delta,
                                           BYTE  Alpha,
                                           int   BlendMode );

typedef void ( APIENTRY * FX_Blur_Draw_ )( int Color, BYTE Alpha );

// "R A D I A L"  B L U R
typedef void ( APIENTRY * FX_RadBlur_SetTex_ )( PTexture TexToRender );

typedef void ( APIENTRY * FX_RadBlur_SetParams_ )( int Count, int MoveX, int MoveY );

typedef void ( APIENTRY * FX_RadBlur_Calc_ )( void*,
                                              BYTE  Alpha,
                                              int   BlendMode );

typedef void ( APIENTRY * FX_RadBlur_Draw_ )( int Color, BYTE Alpha );

//----------------------------------------------------------------------------//
//------------------------------  T E X T  2 D  ------------------------------//
//----------------------------------------------------------------------------//

struct TSymbol
{
  WORD X;
  WORD Y;
  BYTE Width;
};

struct TFont2D
{
  BYTE     Height;
  TSymbol  Sizes[ 256 ];
  PTexture Texture;
  DWORD    Reserved;
};
typedef TFont2D* PFont2D;


typedef PFont2D ( APIENTRY * Text_LoadFontFromFile_ )(
                                                       char* FontTexture,
                                                       char* FontInfo,
                                                       int   TransparentColor,
                                                       int   TexFlags );

typedef PFont2D ( APIENTRY * Text_LoadFontFromMemory_ )(
                                                         PMemory FontTexture,
                                                         int     FontTexType,
                                                         PMemory FontInfo,
                                                         int     TransparentColor,
                                                         int     TexFlags );

typedef void ( APIENTRY * Text_FreeFont_ )( PFont2D &Font );
typedef void ( APIENTRY * Text_FreeFontAll_ )(void);

typedef PFont2D ( APIENTRY * Text_Draw_ )(
                                           PFont2D Font,
                                           float X, float Y,
                                           char* Text,
                                           float Scale,
                                           float Step,
                                           BYTE  Alpha,
                                           int   Color );

typedef float ( APIENTRY * Text_GetWidth_ )(
                                             PFont2D Font,
                                             char*   Text,
                                             float   Scale,
                                             float   Step );

//----------------------------------------------------------------------------//
//------------------------------  C O N S O L E  -----------------------------//
//----------------------------------------------------------------------------//

typedef void ( APIENTRY * Console_Active_ )( bool Enable );

typedef void ( APIENTRY * Console_SetOptions_ )(
                                                 PFont2D  Font,
                                                 PTexture Texture,
                                                 int      Color,
                                                 BYTE     Alpha,
                                                 int      FontColor,
                                                 BYTE     FontAlpha );

typedef void ( APIENTRY * Console_ToLog_ )( bool Connect );

typedef void ( APIENTRY * Console_Draw_ )(void);

typedef void ( APIENTRY * Console_RegCommand_ )(
                                                 char* Command,
                                                 void* );

typedef void ( APIENTRY * Console_AddString_ )( char* Str );

//----------------------------------------------------------------------------//
//-----------------------  P R I M I T I V E S  2 D  -------------------------//
//----------------------------------------------------------------------------//

#define PR_FILL    0x000001
#define PR_SMOOTH  0x000002

#define PR_DEFAULT 0x0

struct oePoint
{
  float X;
  float Y;
};
typedef oePoint* oePPoint;

struct oeLine
{
  float x0;
  float y0;
  float x1;
  float y1;
};
typedef oeLine* oePLine;

struct oeRect
{
  float X;
  float Y;
  float Width;
  float Height;
};
typedef oeRect *oePRect;

struct oeTriangle
{
  float X1; float Y1;
  float X2; float Y2;
  float X3; float Y3;
};
typedef oeTriangle *oePTriangle;

struct oeCircle
{
  float cX;
  float cY;
  float Radius;
};
typedef oeCircle *oePCircle;

typedef void ( APIENTRY * Pr2D_PixelSize_ )( int Size );

typedef void ( APIENTRY * Pr2D_LineWidth_ )( int Width );


typedef void ( APIENTRY * Pr2D_Pixel_ )(
                                         float  X,
                                         float  Y,
                                         int  Color,
                                         BYTE Alpha );

typedef void ( APIENTRY * Pr2D_Line_ )(
                                        float X1, float Y1,
                                        float X2, float Y2,
                                        int  Color,
                                        BYTE Alpha,
                                        int Flags );

typedef void ( APIENTRY * Pr2D_TLine_ )(
                                         oePLine Line,
                                         int     Color,
                                         BYTE    Alpha,
                                         int     Flags );

typedef void ( APIENTRY * Pr2D_Rect_ )(
                                        float X,
                                        float Y,
                                        float Width,
                                        float Height,
                                        int  Color,
                                        BYTE Alpha,
                                        int  Flags );

typedef void ( APIENTRY * Pr2D_TRect_ )(
                                         oePRect Rectangle,
                                         int     Color,
                                         BYTE    Alpha,
                                         int     Flags );

typedef void ( APIENTRY * Pr2D_Triangle_ )(
                                            float X1, float Y1,
                                            float X2, float Y2,
                                            float X3, float Y3,
                                            int  Color,
                                            BYTE Alpha,
                                            int  Flags );

typedef void ( APIENTRY * Pr2D_TTriangle_ )(
                                            oePTriangle Triangle,
                                            int         Color,
                                            BYTE        Alpha,
                                            int         Flags );

typedef void ( APIENTRY * Pr2D_Circle_ )(
                                          float cX,
                                          float cY,
                                          float Radius,
                                          int  Color,
                                          BYTE Alpha,
                                          int  Quality,
                                          int  Flags );

typedef void ( APIENTRY * Pr2D_TCircle_ )(
                                          oePCircle Circle,
                                          int       Color,
                                          BYTE      Alpha,
                                          int       Quality,
                                          int       Flags );

typedef void ( APIENTRY * Pr2D_Ellipse_ )(
                                           float cX,
                                           float cY,
                                           float xRadius,
                                           float yRadius,
                                           int  Color,
                                           BYTE Alpha,
                                           int  Quality,
                                           int  Flags );

//----------------------------------------------------------------------------//
//----------------------------  S P R I T E S  -------------------------------//
//----------------------------------------------------------------------------//

// S T A T I C
typedef void ( APIENTRY * SSprite_Draw_ )(
                                           PTexture Tex,
                                           float    X,
                                           float    Y,
                                           float    Width,
                                           float    Height,
                                           BYTE     Alpha,
                                           float    Angle,
                                           int      Flags );

// A N I M A T E D
typedef void ( APIENTRY * ASprite_Draw_ )(
                                           PTexture Tex,
                                           float    X,
                                           float    Y,
                                           float    Width,
                                           float    Height,
                                           int      FrameNow,
                                           BYTE     Alpha,
                                           float    Angle,
                                           int      Flags );

// C U T
typedef void ( APIENTRY * CSprite_Draw_ )(
                                           PTexture Tex,
                                           float    X,
                                           float    Y,
                                           float    Width,
                                           float    Height,
                                           oePRect  CutRect,
                                           BYTE     Alpha,
                                           float    Angle,
                                           int      Flags );

//----------------------------------------------------------------------------//
//------------------------------  T I L E S  ---------------------------------//
//----------------------------------------------------------------------------//

// S T A T I C
typedef void ( APIENTRY * STile_Draw_ )(
                                         PTexture Tex,
                                         float    X,
                                         float    Y,
                                         float    Width,
                                         float    Height,
                                         int      TilesX,
                                         int      TilesY,
                                         BYTE     Alpha,
                                         int      Flags );

// A N I M A T E D
typedef void ( APIENTRY * ATile_Draw_ )(
                                         PTexture Tex,
                                         float    X,
                                         float    Y,
                                         float    Width,
                                         float    Height,
                                         int      TilesX,
                                         int      TilesY,
                                         int      FrameNow,
                                         BYTE     Alpha,
                                         int      Flags );

//----------------------------------------------------------------------------//
//-----------------------------  S C I S S O R  ------------------------------//
//----------------------------------------------------------------------------//

typedef void ( APIENTRY * Scissor_Begin_ )( int X, int Y, int Width, int Height );

typedef void ( APIENTRY * Scissor_End_ )(void);

//----------------------------------------------------------------------------//
//------------------------------  S O U N D  ---------------------------------//
//----------------------------------------------------------------------------//

typedef void* PSound;

typedef bool ( APIENTRY * Snd_Init_)(void);

typedef void ( APIENTRY * Snd_Active_)( bool Active );

typedef PSound ( APIENTRY * Snd_LoadFromFile_ )(
                                                 char* FileName,
                                                 int   BufferCount );

typedef PSound ( APIENTRY * Snd_LoadFromMemory_ )(
                                                   PMemory Memory,
                                                   int     BufferCount );

typedef bool ( APIENTRY * Snd_Free_)( PSound Sound );
typedef bool ( APIENTRY * Snd_FreeAll_)(void);

typedef void ( APIENTRY * Snd_SetBuffersCount_)(
                                                 PSound Sound,
                                                 int    Count );

// Нормализация громкости к размерности 0..100
#define VOLUME(value) (int)(-100 * ( 100 - value ) )

typedef int ( APIENTRY * Snd_Play_)(
                                     PSound Sound,
                                     int    Pan,
                                     int    Volume,
                                     int    Frequency,
                                     bool   Loop );

typedef void ( APIENTRY * Snd_PlayID_)(
                                        PSound Sound,
                                        int    ID,
                                        int    Pan,
                                        int    Volume,
                                        int    Frequency,
                                        bool   Loop );

typedef void ( APIENTRY * Snd_Stop_)( PSound Sound );

typedef void ( APIENTRY * Snd_StopID_)(
                                        PSound Sound,
                                        int    ID );

typedef void ( APIENTRY * Snd_StopAll_)(void);

typedef void ( APIENTRY * Snd_ChangeParam_)(
                                             PSound Sound,
                                             int    ID,
                                             int    Pan,
                                             int    Volume,
                                             int    Frequency );

//----------------------------------------------------------------------------//
//------------------------------  M E D I A  ---------------------------------//
//----------------------------------------------------------------------------//

typedef void ( APIENTRY * Media_Play_ )( char* FileName, bool Loop );

typedef void ( APIENTRY * Media_Replay_ )(void);

typedef void ( APIENTRY * Media_Pause_ )(void);

typedef void ( APIENTRY * Media_Resume_ )(void);

typedef void ( APIENTRY * Media_Stop_ )(void);

typedef void ( APIENTRY * Media_SetVolume_ )( int Volume );

typedef double ( APIENTRY * Media_GetLength_ )(void);

typedef void ( APIENTRY * Media_SetPosition_ )( double Position );

typedef double ( APIENTRY * Media_GetPosition_ )(void);

typedef void ( APIENTRY * Media_SetWindowRect_ )( int X, int Y, int Width, int Height );

//----------------------------------------------------------------------------//
//---------------------------  C O L L I S I O N  ----------------------------//
//----------------------------------------------------------------------------//

typedef oePoint  TPoint2D;
typedef oePPoint PPoint2D;

typedef oeLine  TLine2D;
typedef oePLine PLine2D;

struct TPolyLine2D
{
  DWORD     Count;
  float     cX;
  float     cY;
  PPoint2D  Points;
};
typedef TPolyLine2D* PPolyLine2D;

typedef oeRect  TAABB2D;
typedef oePRect PAABB2D;

typedef oeCircle  TCircle2D;
typedef oePCircle PCircle2D;

// P O I N T ' s
typedef bool ( APIENTRY * Col_PointInAABB_)(
                                             float X, float Y, PAABB2D AABB );

typedef bool ( APIENTRY * Col_PointInCircle_)(
                                              float X, float Y, PCircle2D Circ );

typedef bool ( APIENTRY * Col_PointInPolyLine_)(
                                                 float X, float Y, PPolyLine2D PL );

// L I N E ' s
typedef bool ( APIENTRY * Col_Line_)(
                                      PLine2D A, PLine2D B );

typedef bool ( APIENTRY * Col_LineVsAABB_)(
                                            PLine2D A, PAABB2D AABB );

typedef bool ( APIENTRY * Col_LineVsCircle_)(
                                              PLine2D L, PCircle2D Circ );
                                              
typedef bool ( APIENTRY * Col_LineVsCircleXY_)(
                                                PLine2D L, PCircle2D Circ, int Precision );

typedef bool ( APIENTRY * Col_LineVsPolyLine_)(
                                                PLine2D A, PPolyLine2D B );

// P O L Y L I N E ' s
typedef bool ( APIENTRY * Col_PolyLine_)(
                                          PPolyLine2D A, PPolyLine2D B );

typedef bool ( APIENTRY * Col_PolyLineVsAABB_)(
                                                PPolyLine2D A, PAABB2D AABB );

typedef bool ( APIENTRY * Col_PolyLineVsCircle_)(
                                                  PPolyLine2D A, PCircle2D Circ );
                                                  
typedef bool ( APIENTRY * Col_PolyLineVsCircleXY_)(
                                                    PPolyLine2D A, PCircle2D Circ, int Precision );

// A A B B ' s
typedef bool ( APIENTRY * Col_AABB_)(
                                      PAABB2D AABB1, PAABB2D AABB2 );

typedef bool ( APIENTRY * Col_AABBInAABB_)(
                                            PAABB2D AABB1, PAABB2D AABB2 );

typedef bool ( APIENTRY * Col_AABBInCircle_)(
                                              PAABB2D AABB1, PCircle2D Circ );

typedef bool ( APIENTRY * Col_AABBVsCircle_)(
                                              PAABB2D AABB1, PCircle2D Circ );

// C I R C L E ' s
typedef bool ( APIENTRY * Col_Circle_)(
                                        PCircle2D Circ1, PCircle2D Circ2 );

typedef bool ( APIENTRY * Col_CircleInCircle_)(
                                                PCircle2D Circ1, PCircle2D Circ2 );

typedef bool ( APIENTRY * Col_CircleInAABB_)(
                                              PCircle2D Circ1, PAABB2D AABB );

// E X T E N D E D  F U N C T I O N S
// G E T ' s
typedef float ( APIENTRY * ColEx_LastX_)(void);
typedef float ( APIENTRY * ColEx_LastY_)(void);

typedef int ( APIENTRY * ColEx_LastLineA_)(void);
typedef int ( APIENTRY * ColEx_LastLineB_)(void);

// T R A N S F O R M A T I O N ' s
typedef void ( APIENTRY * ColEx_PolyRotate_)(
                                              PPolyLine2D A, PPolyLine2D B,
                                              float Angle );

typedef void ( APIENTRY * ColEx_PolyScale_)(
                                             PPolyLine2D A,
                                             float ScaleX, float ScaleY );

typedef void ( APIENTRY * ColEx_PolyMove_)(
                                            PPolyLine2D A, PPolyLine2D B,
                                            float X, float Y );

typedef void ( APIENTRY * ColEx_PolyCenter_)(
                                              PPolyLine2D A );

typedef void ( APIENTRY * ColEx_PolyRect_)(
                                            PPolyLine2D A,
                                            PAABB2D     Rect );

// L I N E ' s
typedef void ( APIENTRY * ColEx_CalcLineCross_)(
                                                 PLine2D A, PLine2D B );

//----------------------------------------------------------------------------//
//----------------------------  F A S T  M A T H  ----------------------------//
//----------------------------------------------------------------------------//

typedef float ( APIENTRY * M_Cos_ )( int Angle );

typedef float ( APIENTRY * M_Sin_ )( int Angle );

typedef float ( APIENTRY * M_CosF_ )( int Angle );

typedef float ( APIENTRY * M_SinF_ )( int Angle );

typedef int ( APIENTRY * M_Round_ )( float Value );

typedef int ( APIENTRY * M_Trunc_ )( float Value);

typedef float ( APIENTRY * M_Distance_ )( float X1, float Y1, float X2, float Y2 );

typedef int ( APIENTRY * M_FindAngle_ )( int X1, int Y1, int X2, int Y2 );

//----------------------------------------------------------------------------//
//------------------------------  M E M O R Y  -------------------------------//
//----------------------------------------------------------------------------//

typedef void ( APIENTRY * Mem_Get_ )( void* &p, int Size );

typedef void ( APIENTRY * Mem_Realloc_ )( void* &p, int Size );

typedef void ( APIENTRY * Mem_Free_ )( void* &p );

//----------------------------------------------------------------------------//
//-------------------------------  U T I L S  --------------------------------//
//----------------------------------------------------------------------------//

// H A R D W A R E
typedef char* ( APIENTRY * U_GetCPUName_ )(void);
typedef int ( APIENTRY * U_GetTotalRAM_ )(void);
typedef bool ( APIENTRY * U_Is3DAccelerator_ )(void);

typedef int ( APIENTRY * U_GetMaxTexSize_ )(void);
typedef int ( APIENTRY * U_GetMaxAnisotropy_ )(void);

// A D D I T I O N A L  F O R  E N G I N E
typedef void ( APIENTRY * U_SnapShot_ )(
                                        char* Path,
                                        char* FileName );

// C O N V E R T
typedef char* ( APIENTRY * U_IntToStr_ )( int Num );

typedef int ( APIENTRY * U_StrToInt_ )( char* Str );

typedef char* ( APIENTRY * U_FloatToStr_ )( float Num );

typedef double ( APIENTRY * U_GetTime_ )( void );


//----------------------------------------------------------------------------//
//------------------------------  P L U G I N  -------------------------------//
//----------------------------------------------------------------------------//

#define gENGINE_HWND    0x000000; //Тип: DWORD*, Дескриптор окна
#define gENGINE_DC      0x000001; //Тип: DWORD*, Контекст окна
#define gENGINE_GLRC    0x000002; //Тип: DWORD*, OpenGL контекст окна
#define gENGINE_LOG     0x000008; //Тип: bool*, Ведется ли лог движком
#define gENGINE_FLAGS   0x000010; //Тип: int*, Включенные на данный момент флаги

#define gOGL_WIDTH      0x000003; //Тип: int*, Ширина области для вывода изображения
#define gOGL_HEIGHT     0x000004; //Тип: int*, Высота области для выводы изображения
#define gOGL_EXTENSIONS 0x000009; //Тип: char*, Расширения OpenGL

#define gCURRENT_CAM2D  0x000005; //Тип: PCamera2D*, Указатель на текущую камеру

#define gCONSOLE_ACTIVE 0x000011; //Тип: bool*, Активна ли сейчас консоль

#define gSCREEN_SCALEX  0x000006; //Тип: float*, Коэфициент масштабирования по X
#define gSCREEN_SCALEY  0x000007; //Тип: float*, Коэфициент масштабирования по Y

typedef void* ( APIENTRY * P_GetParams_ )( int What );

typedef PTexture ( APIENTRY * Tex_PostProcess_ )( void* &pData, TTexture &Info, int TransparentColor );

#endif
