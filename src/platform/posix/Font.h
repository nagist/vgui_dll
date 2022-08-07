/*
 * BSD 3-Clause License
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
