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

#ifndef _OMEGA_FUNCTIONS_
#define _OMEGA_FUNCTIONS_
#include "OMEGA_types.h"

//----------------------------------------------------------------------------//
//-----------------------------  E N G I N E  --------------------------------//
//----------------------------------------------------------------------------//

// S T A R T
extern inline void OE_Init( BYTE zBits, BYTE stencilBits );

extern inline void OE_Init2( DWORD hwnd );

extern inline void OE_Quit(void);

// M A I N
extern inline void OE_RegProcedure(
                                    BYTE  PType,
                                    void* );

extern inline void OE_UnRegProcedure( BYTE PType );

extern inline POTimer Timer_Create(
                                    void*,
                                    int   Interval  = 1000,
                                    int   Precision = 1 );

extern inline void Timer_Free( POTimer& Timer );
extern inline void Timer_FreeAll();

// O P T I O N S
//FLAGS
extern inline void OE_Enable( int What );

extern inline void OE_Disable( int What );

//WINDOW
extern inline void OE_SetWndOnTop( bool Enable );

extern inline void OE_SetWndPosition( int X, int Y );

extern inline void OE_SetWndName( char* NewName );

extern inline void OE_ShowCursor( bool Show );

extern inline void OE_ResizeWindow( int Width, int Height );

//SCREEN
extern inline void OE_SetScreenOptions(
                                        int  Width,
                                        int  Height,
                                        int  BPP,
                                        int  Refresh,
                                        bool FullScreen,
                                        bool WaitVSync );

extern inline void OE_ChangeScreenOptions(
                                           int  Width,
                                           int  Height,
                                           int  BPP,
                                           int  Refresh,
                                           bool FullScreen,
                                           bool WaitVSync );

extern inline void OE_SetResolutionDependence(
                                               int NormalResX,
                                               int NormalResY );

extern inline void OE_SetVSync( bool WaitvSync );

//GET
extern inline POptions OE_GetOptions(void);

// A D D I T I O N A L
extern inline void OE_SetAdvancedOptions(
                                          bool UseLog,
                                          bool AppCanClose = true,
                                          bool HaltOnExit  = false );

extern inline int OE_GetFPS(void);

//----------------------------------------------------------------------------//
//----------------------------------  I N I  ---------------------------------//
//----------------------------------------------------------------------------//

extern inline void INI_LoadFromFile( char* FileName );

extern inline void INI_LoadFromMemory( PMemory Memory );

extern inline void INI_SaveToFile( char* FileName );

extern inline void INI_Add( char* Section, char* Key );

extern inline char* INI_ReadKeyStr( char* Section, char* Key );

extern inline int INI_ReadKeyInt( char* Section, char* Key );

extern inline bool INI_WriteKeyStr( char* Section, char* Key, char* Value );

extern inline bool INI_WriteKeyInt( char* Section, char* Key, int Value );

//----------------------------------------------------------------------------//
//-----------------------------  H T M L  L O G  -----------------------------//
//----------------------------------------------------------------------------//

extern inline void LOG_SetOptions( char* clrBODY,   //= "808080"
                                   char* clrTIME,   //= "yellowgreen"
                                   char* clrENGINE, //= "00ff00"
                                   char* clrAPP,    //= "blue"
                                   char* clrCONSOLE,//= "blue"
                                   char* clrMESS,   //= "black"
                                   char* clrWARNING,//= "orange"
                                   char* clrERROR,  //= "red"
                                   BYTE  sTIME    = 2,
                                   BYTE  sENGINE  = 3,
                                   BYTE  sAPP     = 4,
                                   BYTE  sCONSOLE = 4,
                                   BYTE  sMESS    = 3,
                                   BYTE  sWARNING = 4,
                                   BYTE  sERROR   = 4 );

extern inline void LOG_Init(
                             char* FileName,
                             bool  Create );

extern inline void LOG_AddMessage(
                                   BYTE MessageType,
                                   char* Text );

extern inline void LOG_AddLine(
                                int   Size,
                                char* Line );

//----------------------------------------------------------------------------//
//------------------------------  I N P U T  ---------------------------------//
//----------------------------------------------------------------------------//

// K E Y B O A R D
extern inline void Key_LoadLayout( char* Layout );

extern inline bool KeyEx_Down( BYTE KeyCode );

extern inline bool Key_Down( BYTE KeyCode );

extern inline bool Key_Press( BYTE KeyCode );

extern inline BYTE Key_LastDown(void);

extern inline BYTE Key_LastPress(void);

extern inline void Key_BeginReadText( char* StartText );

extern inline char* Key_EndReadText(void);

extern inline void Key_MaxReadText( int Count );

// M O U S E
extern inline int MouseEx_X(void);

extern inline int MouseEx_Y(void);

extern inline bool MouseEx_Down( BYTE Button );

extern inline int Mouse_X(void);

extern inline int Mouse_Y(void);

extern inline bool Mouse_Move(void);

extern inline void Mouse_Lock(void);

extern inline int Mouse_DeltaX(void);

extern inline int Mouse_DeltaY(void);

extern inline bool Mouse_Down( BYTE Button );

extern inline bool Mouse_Press( BYTE Button );

extern inline bool Mouse_Click( BYTE Button );

extern inline bool Mouse_DblClick( BYTE Button );

extern inline bool Mouse_WheelUp(void);

extern inline bool Mouse_WheelDown(void);

// J O Y P A D
extern inline bool Joy_Down(
                             int Joy,
                             int Button );

extern inline bool Joy_Press(
                              int Joy,
                              int Button );

extern inline bool Joy_AxePos(
                               int Joy,
                               int AxePos );

//----------------------------------------------------------------------------//
//----------------------------  T E X T U R E S  -----------------------------//
//----------------------------------------------------------------------------//

extern inline void Tex_Filter( PTexture& Texture, int Flags );

extern inline void Tex_SetAnisotropyLevel( int Level );

extern inline PTexture Tex_CreateZero( int Width, int Height, int Flags );

extern inline PTexture Tex_LoadFromFile(
                                         char* FileName,
                                         int   TransparentColor,
                                         int   Flags );

extern inline PTexture Tex_LoadFromMemory(
                                           PMemory Memory,
                                           int     FormatType,
                                           int     TransparentColor,
                                           int     Flags );

extern inline void Tex_Free( PTexture &Texture );
extern inline void Tex_FreeAll();

extern inline void Tex_LoadMaskFromFile( char* FileName );

extern inline void Tex_LoadMaskFromMemory( PMemory Memory );

extern inline void Tex_FreeMask(void);

extern inline void Tex_SetFramesSize(
                                      PTexture Texture,
                                      WORD     FrameWidth,
                                      WORD     FrameHeight );

//----------------------------------------------------------------------------//
//-----------------------  R E N D E R  T O  T E X T U R E  ------------------//
//----------------------------------------------------------------------------//

extern inline void Tex_BeginRenderIn( PTexture Texture, bool SaveOld = false, bool RealSize = false, bool Clear = true );

extern inline void Tex_EndRenderIn(void);

//----------------------------------------------------------------------------//
//----------------------------  C A M E R A  2 D  ----------------------------//
//----------------------------------------------------------------------------//

extern inline PCamera2D Cam2D_Create(void);

extern inline void Cam2D_Free( PCamera2D& YourCamera );
extern inline void Cam2D_FreeAll();

extern inline void Cam2D_Set( PCamera2D YourCamera );

//----------------------------------------------------------------------------//
//----------------------------------  F X  -----------------------------------//
//----------------------------------------------------------------------------//

extern inline void FX_SetColorMix( int Color );

extern inline void FX_SetBlendMode( int Mode );

extern inline void FX_SetScale( float ScaleX, float ScaleY );

extern inline void FX_SetVertexes(
                                   float X1, float Y1,
                                   float X2, float Y2,
                                   float X3, float Y3,
                                   float X4, float Y4 );

extern inline void FX_SetVCA(
                              int  C1, int  C2, int  C3, int  C4,
                              BYTE A1, BYTE A2, BYTE A3, BYTE A4);

// B L U R
extern inline void FX_Blur_SetTex( PTexture TexToRender );

extern inline void FX_Blur_SetParams( int Count, int MoveX, int MoveY );

extern inline void FX_Blur_Calc( void*,
                                 float Delta,
                                 BYTE  Alpha,
                                 int   BlendMode = FX_BLEND_NORMAL );

extern inline void FX_Blur_Draw( int Color, BYTE Alpha );

// "R A D I A L"  B L U R
extern inline void FX_RadBlur_SetTex( PTexture TexToRender );

extern inline void FX_RadBlur_SetParams( int Count, int MoveX, int MoveY );

extern inline void FX_RadBlur_Calc( void*,
                                    BYTE Alpha,
                                    int   BlendMode = FX_BLEND_NORMAL );

extern inline void FX_RadBlur_Draw( int Color, BYTE Alpha );

//----------------------------------------------------------------------------//
//------------------------------  T E X T  2 D  ------------------------------//
//----------------------------------------------------------------------------//

extern inline PFont2D Text_LoadFontFromFile( char* FontTexture, char* FontInfo, int TransparentColor = 0, int TexFlags = TEX_DEFAULT_2D );

extern inline PFont2D Text_LoadFontFromMemory( PMemory FontTexture, int FontTexType, PMemory FontInfo, int TransparentColor = 0, int TexFlags = TEX_DEFAULT_2D );

extern inline void Text_FreeFont( PFont2D &Font );
extern inline void Text_FreeFontAll();

extern inline void Text_Draw( PFont2D Font, float X, float Y, char* Text, float Scale = 1.0, float Step = 0, BYTE Alpha = 255, int Color = 0xFFFFFF );

extern inline float Text_GetWidth( PFont2D Font, char* Text, float Scale = 1.0, float Step = 0 );

//----------------------------------------------------------------------------//
//------------------------------  C O N S O L E  -----------------------------//
//----------------------------------------------------------------------------//

extern inline void Console_Active( bool Enable );

extern inline void Console_SetOptions( PFont2D Font, PTexture Texture = NULL, int Color = 0, BYTE Alpha = 155, int FontColor = 0xFFFFFF, BYTE FontAlpha = 255 );

extern inline void Console_ToLog( bool Connect );

extern inline void Console_Draw(void);

extern inline void Console_RegCommand( char* Command, void* );

extern inline void Console_RegVariable( char* VarName, int* Variable );

extern inline void Console_RegProcedure( char* ProcName, void* );

extern inline void Console_AddString( char* Str );

//----------------------------------------------------------------------------//
//-----------------------  P R I M I T I V E S  2 D  -------------------------//
//----------------------------------------------------------------------------//

extern inline void Pr2D_PixelSize( int Size );

extern inline void Pr2D_LineWidth( int Width );


extern inline void Pr2D_Pixel(
                               float X,
                               float Y,
                               int   Color,
                               BYTE  Alpha = 255 );

extern inline void Pr2D_Line(
                              float X1, float Y1,
                              float X2, float Y2,
                              int  Color,
                              BYTE Alpha = 255,
                              int Flags = PR_DEFAULT );

extern inline void Pr2D_TLine(
                               oePLine Line,
                               int 		 Color,
                               BYTE  	 Alpha = 255,
                               int 		 Flags = PR_DEFAULT );

extern inline void Pr2D_Rect(
                              float X,
                              float Y,
                              float Width,
                              float Height,
                              int  Color,
                              BYTE Alpha = 255,
                              int Flags = PR_DEFAULT );

extern inline void Pr2D_TRect(
                               oePRect Rectangle,
                               int     Color,
                               BYTE    Alpha = 255,
                               int     Flags = PR_DEFAULT );

extern inline void Pr2D_Triangle(
                                  float X1, float Y1,
                                  float X2, float Y2,
                                  float X3, float Y3,
                                  int  Color,
                                  BYTE Alpha = 255,
                                  int Flags = PR_DEFAULT );

extern inline void Pr2D_TTriangle(
                                   oePTriangle Triangle,
                                   int         Color,
                                   BYTE        Alpha = 255,
                                   int         Flags = PR_DEFAULT );

extern inline void Pr2D_Circle(
                                float cX,
                                float cY,
                                float Radius,
                                int  Color,
                                BYTE Alpha   = 255,
                                int Quality = 32,
                                int Flags   = PR_DEFAULT );

extern inline void Pr2D_TCircle(
                                 oePCircle Circle,
                                 int       Color,
                                 BYTE      Alpha   = 255,
                                 int       Quality = 32,
                                 int       Flags   = PR_DEFAULT );

extern inline void Pr2D_Ellipse(
                                 float cX,
                                 float cY,
                                 float xRadius,
                                 float yRadius,
                                 int  Color,
                                 BYTE Alpha   = 255,
                                 int Quality = 32,
                                 int Flags   = PR_DEFAULT );

//----------------------------------------------------------------------------//
//----------------------------  S P R I T E S  -------------------------------//
//----------------------------------------------------------------------------//

// S T A T I C
extern inline void SSprite_Draw(
                                 PTexture Tex,
                                 float    X,
                                 float    Y,
                                 float    Width,
                                 float    Height,
                                 BYTE     Alpha = 255,
                                 float    Angle = 0,
                                 int      Flags = FX_DEFAULT );

// A N I M A T E D
extern inline void ASprite_Draw(
                                 PTexture Tex,
                                 float    X,
                                 float    Y,
                                 float    Width,
                                 float    Height,
                                 int      FrameNow,
                                 BYTE     Alpha = 255,
                                 float    Angle = 0,
                                 int      Flags = FX_DEFAULT );

// C U T
extern inline void CSprite_Draw(
                                 PTexture Tex,
                                 float    X,
                                 float    Y,
                                 float    Width,
                                 float    Height,
                                 oePRect  CutRect,
                                 BYTE     Alpha = 255,
                                 float    Angle = 0,
                                 int      Flags = FX_DEFAULT );

//----------------------------------------------------------------------------//
//------------------------------  T I L E S  ---------------------------------//
//----------------------------------------------------------------------------//

// S T A T I C
extern inline void STile_Draw(
                               PTexture Tex,
                               float    X,
                               float    Y,
                               float    Width,
                               float    Height,
                               int      TilesX,
                               int      TilesY,
                               BYTE     Alpha = 255,
                               int      Flags = FX_DEFAULT );

// A N I M A T E D
extern inline void ATile_Draw(
                               PTexture Tex,
                               float    X,
                               float    Y,
                               float    Width,
                               float    Height,
                               int      TilesX,
                               int      TilesY,
                               int      FrameNow,
                               BYTE     Alpha = 255,
                               int      Flags = FX_DEFAULT);

//----------------------------------------------------------------------------//
//-----------------------------  S C I S S O R  ------------------------------//
//----------------------------------------------------------------------------//

extern inline void Scissor_Begin( int X, int Y, int Width, int Height );

extern inline void Scissor_End(void);

//----------------------------------------------------------------------------//
//------------------------------  S O U N D  ---------------------------------//
//----------------------------------------------------------------------------//

extern inline bool Snd_Init(void);

extern inline void Snd_Active( bool Active );

extern inline PSound Snd_LoadFromFile(
                                       char* FileName,
                                       int   BufferCount );

extern inline PSound Snd_LoadFromMemory(
                                         PMemory Memory,
                                         int     BufferCount );

extern inline void Snd_Free( PSound &Sound );
extern inline void Snd_FreeAll();

extern inline void Snd_SetBuffersCount(
                                        PSound Sound,
                                        int    Count );

extern inline int Snd_Play(
                            PSound Sound,
                            int    Pan       = 0,
                            int    Volume    = 0,
                            int    Frequency = 0,
                            bool   Loop      = false );

extern inline void Snd_PlayID(
                               PSound Sound,
                               int    ID,
                               int    Pan       = 0,
                               int    Volume    = 0,
                               int    Frequency = 0,
                               bool   Loop      = false );

extern inline void Snd_Stop( PSound Sound );

extern inline void Snd_StopID(
                               PSound Sound,
                               int    ID );

extern inline void Snd_StopAll(void);

extern inline void Snd_ChangeParam(
                                    PSound Sound,
                                    int    ID,
                                    int    Pan       = 0,
                                    int    Volume    = 0,
                                    int    Frequency = 0 );

//----------------------------------------------------------------------------//
//------------------------------  M E D I A  ---------------------------------//
//----------------------------------------------------------------------------//

extern inline void Media_Play( char* FileName, bool Loop );

extern inline void Media_Replay(void);

extern inline void Media_Pause(void);

extern inline void Media_Resume(void);

extern inline void Media_Stop(void);

extern inline void Media_SetVolume( int Volume );

extern inline double Media_GetLength(void);

extern inline void Media_SetPosition( double Position );

extern inline double Media_GetPosition(void);

extern inline void Media_SetWindowRect( int X, int Y, int Width, int Height );

//----------------------------------------------------------------------------//
//---------------------------  C O L L I S I O N  ----------------------------//
//----------------------------------------------------------------------------//

// P O I N T ' s
extern inline bool Col_PointInAABB( float X, float Y, PAABB2D AABB );

extern inline bool Col_PointInCircle( float X, float Y, PCircle2D Circ );

extern inline bool Col_PointInPolyLine( float X, float Y, PPolyLine2D PL );

// L I N E ' s
extern inline bool Col_Line( PLine2D A, PLine2D B );

extern inline bool Col_LineVsAABB( PLine2D A, PAABB2D AABB );

extern inline bool Col_LineVsCircle( PLine2D L, PCircle2D Circ );

extern inline bool Col_LineVsCircleXY( PLine2D L, PCircle2D Circ, int Precision );

extern inline bool Col_LineVsPolyLine( PLine2D A, PPolyLine2D B );

// P O L Y L I N E ' s
extern inline bool Col_PolyLine( PPolyLine2D A, PPolyLine2D B );

extern inline bool Col_PolyLineVsAABB( PPolyLine2D A, PAABB2D AABB );

extern inline bool Col_PolyLineVsCircle( PPolyLine2D A, PCircle2D Circ );

extern inline bool Col_PolyLineVsCircleXY( PPolyLine2D A, PCircle2D Circ, int Precision );

// A A B B ' s
extern inline bool Col_AABB( PAABB2D AABB1, PAABB2D AABB2 );

extern inline bool Col_AABBInAABB( PAABB2D AABB1, PAABB2D AABB2 );

extern inline bool Col_AABBInCircle( PAABB2D AABB1, PCircle2D Circ );

extern inline bool Col_AABBVsCircle( PAABB2D AABB1, PCircle2D Circ );

// C I R C L E ' s
extern inline bool Col_Circle( PCircle2D Circ1, PCircle2D Circ2 );

extern inline bool Col_CircleInCircle( PCircle2D Circ1, PCircle2D Circ2 );

extern inline bool Col_CircleInAABB( PCircle2D Circ1, PAABB2D AABB );

// E X T E N D E D  F U N C T I O N S
// G E T ' s
extern inline float ColEx_LastX(void);
extern inline float ColEx_LastY(void);

extern inline int ColEx_LastLineA(void);
extern inline int ColEx_LastLineB(void);

// T R A N S F O R M A T I O N ' s
extern inline void ColEx_PolyRotate( PPolyLine2D A, PPolyLine2D B, float Angle );

extern inline void ColEx_PolyScale( PPolyLine2D A, float ScaleX, float ScaleY );

extern inline void ColEx_PolyMove( PPolyLine2D A, PPolyLine2D B, float X, float Y );

extern inline void ColEx_PolyCenter( PPolyLine2D A );

extern inline void ColEx_PolyRect( PPolyLine2D A, PAABB2D Rect );

// L I N E ' s
extern inline void ColEx_CalcLineCross( PLine2D A, PLine2D B );

//----------------------------------------------------------------------------//
//----------------------------  F A S T  M A T H  ----------------------------//
//----------------------------------------------------------------------------//

extern inline float M_Cos( int Angle );

extern inline float M_Sin( int Angle );

extern inline float M_CosF( int Angle );

extern inline float M_SinF( int Angle );

extern inline int M_Round( float Value );

extern inline int M_Trunc( float Value );

extern inline float M_Distance( float X1, float Y1, float X2, float Y2 );

extern inline int M_FindAngle( int X1, int Y1, int X2, int Y2 );

//----------------------------------------------------------------------------//
//------------------------------  M E M O R Y  -------------------------------//
//----------------------------------------------------------------------------//

extern inline void Mem_Get( void* &p, int Size );

extern inline void Mem_Realloc( void* &p, int Size );

extern inline void Mem_Free( void* &p );

//----------------------------------------------------------------------------//
//-------------------------------  U T I L S  --------------------------------//
//----------------------------------------------------------------------------//

// H A R D W A R E
extern inline char* U_GetCPUName(void);
extern inline int U_GetTotalRAM(void);
extern inline bool U_Is3DAccelerator(void);

extern inline int U_GetMaxTexSize(void);
extern inline int U_GetMaxAnisotropy(void);

// A D D I T I O N A L  F O R  E N G I N E
extern inline void U_SnapShot(
                               char* Path,
                               char* FileName );

// C O N V E R Tint Num );
extern inline char* U_IntToStr( int Num );

extern inline int U_StrToInt( char* Str );

extern inline char* U_FloatToStr( float Num );

extern inline double U_GetTime( void );

//----------------------------------------------------------------------------//
//------------------------------  P L U G I N  -------------------------------//
//----------------------------------------------------------------------------//

extern inline void* P_GetParams( int What );

extern inline PTexture Tex_PostProcess( void* &pData, TTexture &Info, int TransparentColor );

#endif
