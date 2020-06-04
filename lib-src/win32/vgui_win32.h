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
