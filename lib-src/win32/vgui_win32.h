//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include"vfontdata.h"
#define WIN32_LEAN_AND_MEAN
#define OEMRESOURCE
#include<windows.h>

namespace vgui
{
class SurfacePlat
{
public:
	HWND    hwnd;
	HDC     hdc;
	HDC     hwndDC;
	HDC	  textureDC;
	HGLRC   hglrc;
	HRGN    clipRgn;
	HBITMAP bitmap;
	int     bitmapSize[2];
	int     restoreInfo[4];
	bool    isFullscreen;
	int     fullscreenInfo[3];
};

class BaseFontPlat
{
public:
	virtual ~BaseFontPlat() {}

	virtual bool equals(const char* name,int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol)=0;
	virtual void getCharRGBA(int ch,int rgbaX,int rgbaY,int rgbaWide,int rgbaTall,uchar* rgba)=0;
	virtual void getCharABCwide(int ch,int& a,int& b,int& c)=0;
	virtual int getTall()=0;
	virtual void drawSetTextFont(SurfacePlat* plat)=0;
};

class FontPlat : public BaseFontPlat
{
protected:
	HFONT m_hFont;
	HDC m_hDC;
	HBITMAP m_hDIB;
	TEXTMETRIC tm;
	enum { ABCWIDTHS_CACHE_SIZE = 256 };
	ABC m_ABCWidthsCache[ABCWIDTHS_CACHE_SIZE];

	int bufSize[2];
	uchar* buf;

	VFontData m_BitmapFont;
	bool m_bBitmapFont;

	char *m_szName;
	int m_iWide;
	int m_iTall;
	float m_flRotation;
	int m_iWeight;
	bool m_bItalic;
	bool m_bUnderline;
	bool m_bStrikeOut;
	bool m_bSymbol;

public:
	FontPlat(const char* name,int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol);
	~FontPlat();

	virtual bool equals(const char* name,int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol);
	virtual void getCharRGBA(int ch,int rgbaX,int rgbaY,int rgbaWide,int rgbaTall,uchar* rgba);
	virtual void getCharABCwide(int ch,int& a,int& b,int& c);
	virtual int getTall();
	virtual void drawSetTextFont(SurfacePlat* plat);
};

class FontPlat_Bitmap : public BaseFontPlat
{
private:
	VFontData m_FontData;
	char *m_pName;

public:
	static FontPlat_Bitmap* Create(const char* name, FileImageStream* pStream);

public:
	FontPlat_Bitmap();
	~FontPlat_Bitmap();

	virtual bool equals(const char* name,int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol);
	virtual void getCharRGBA(int ch,int rgbaX,int rgbaY,int rgbaWide,int rgbaTall,uchar* rgba);
	virtual void getCharABCwide(int ch,int& a,int& b,int& c);
	virtual int getTall();
	virtual void drawSetTextFont(SurfacePlat* plat);
};
}
