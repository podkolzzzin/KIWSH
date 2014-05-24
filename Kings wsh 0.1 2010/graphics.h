/*
 *   Simple graphics library
 */
#ifdef DLLCOMPILE
#define TYPEDLL __declspec(dllexport)
#else
#define TYPEDLL __declspec(dllimport)
#pragma comment (lib, "GraphicsLibrary.lib")
#endif


#define sgRGB(r,g,b) ((unsigned long)(((unsigned char)(r)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(b))<<16)))
#define SgRGB	sgRGB




// brush styles for SgSelectBrush
enum {
	BRUSH_SOLID=-1,
	BRUSH_CROSS=HS_CROSS,
	BRUSH_DIAGCROSS=HS_DIAGCROSS,
	BRUSH_HORIZONTAL = HS_HORIZONTAL,
	BRUSH_VERTICAL=HS_VERTICAL,
	BRUSH_BDIAGONAL = HS_BDIAGONAL,
	BRUSH_FDIAGONAL = HS_FDIAGONAL
};
enum {
	PEN_SOLID = PS_SOLID,
	PEN_DOT = PS_DOT,
	PEN_DASH = PS_DASH,
	PEN_DASHDOT = PS_DASHDOT,
	PEN_DASHDOTDOT = PS_DASHDOTDOT
};

// modes for SgSetBkMode
#define		BK_OPAQUE				1
#define		BK_TRANSPARENT			2


/*
	TODO: define all virtual key codes
*/


TYPEDLL bool SgCreate( unsigned int width, unsigned int height, const char *title=0 );

TYPEDLL void SgDestroy();

TYPEDLL bool SgIsActive();

TYPEDLL void SgFlipPages();

TYPEDLL void SgPause( int msec );

TYPEDLL void SgClearScreen( unsigned long color );

TYPEDLL void SgSetBkMode( int mode, unsigned long color );

TYPEDLL void SgSelectPen( int width, unsigned long color );

TYPEDLL void SgSelectBrush( int style, unsigned long color );

TYPEDLL void SgSetPixel( int x, int y, unsigned long color );

TYPEDLL void SgMoveTo( int x, int y );

TYPEDLL void SgLineTo( int x, int y );

TYPEDLL void SgLine( int x1, int y1, int x2, int y2 );

TYPEDLL void SgRectangle( int x1, int y1, int x2, int y2 );

TYPEDLL void SgCircle( int x, int y, int radius );

TYPEDLL void SgEllipse( int x, int y, int radius1, int radius2 );

TYPEDLL bool SgIsKeyDown(int key);

TYPEDLL bool SgIsKeyPressed(int key);

TYPEDLL bool SgGetCursorPos( int& rx, int& ry );

TYPEDLL int SgLoadImage( const char *name );

TYPEDLL void SgSetImageColorKey( int handle, unsigned long color );

TYPEDLL void SgResetImageColorKey( int handle );

TYPEDLL void SgDrawImage( int handle, int x, int y );

TYPEDLL void SgDrawImageArea( int handle, int xDest, int yDest, int xSrc, int ySrc, int widthSrc, int heightSrc );

TYPEDLL void SgDrawImageFile( const char *name, int x, int y );

TYPEDLL bool SgGetImageSizes( int handle, int& width, int& height );
TYPEDLL void SgSelectFont(int Height,int Width,int clr,char*face="Tahoma",bool IsItalic=false,bool IsUnderLine=false,bool IsStrike=false,int Orientation=0);
TYPEDLL void SgDrawText(int x,int y,const char*pstr,...);