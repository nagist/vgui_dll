//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include"vfontdata.h"
#include"utlrbtree.h"

namespace vgui
{
class SurfacePlat
{
public:
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
	virtual int getWide()=0;
	virtual void drawSetTextFont(SurfacePlat* plat)=0;
};

class FontPlat : public BaseFontPlat
{
protected:
	int bufSize[2];
	uchar* buf;

	VFontData m_BitmapFont;
	bool m_bBitmapFont;

	char m_szName[32];
	int m_iTall;
	int m_iWeight;
	int m_iFlags;
	bool m_bAntiAliased;
	bool m_bRotary;
	bool m_bAdditive;
	int m_iDropShadowOffset;
	bool m_bUnderlined;
	int m_iOutlineSize;

	int m_iHeight;
	int m_iMaxCharWidth;
	int m_iAscent;

	// abc widths
	struct abc_t
	{
		short b;
		char a;
		char c;
	};

	// On PC we cache char widths on demand when actually requested to minimize our use of the kernels 
	// paged pool (GDI may cache information about glyphs we have requested and take up lots of paged pool)
	struct abc_cache_t
	{
		wchar_t wch;
		abc_t abc;
	};
	CUtlRBTree<abc_cache_t, unsigned short> m_ExtendedABCWidthsCache;
	static bool ExtendedABCWidthsCacheLessFunc(const abc_cache_t &lhs, const abc_cache_t &rhs);

	int m_iScanLines;
	int m_iBlur;
	float *m_pGaussianDistribution;

	struct font_name_entry
	{
		char *m_OSSpecificName;
		unsigned char m_cbOSSpecificName;
		char *m_pchFriendlyName;
	};

	static bool ms_bSetFriendlyNameCacheLessFunc;
	static CUtlRBTree<font_name_entry, int> m_FriendlyNameCache;

	static bool FontLessFunc( const font_name_entry &lhs, const font_name_entry &rhs );
	static void CreateFontList() { }

public:
	FontPlat(const char* name,int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol);
	~FontPlat();

	virtual bool equals(const char* name,int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol);
	virtual void getCharRGBA(int ch,int rgbaX,int rgbaY,int rgbaWide,int rgbaTall,uchar* rgba);
	virtual void getCharABCwide(int ch,int& a,int& b,int& c);
	virtual int getTall();
	virtual int getWide();
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
	virtual int getWide();
	virtual void drawSetTextFont(SurfacePlat* plat);
};
}
