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

#include<VGUI_Font.h>
#include<VGUI_Dar.h>
#include"Font.h"

using namespace vgui;

static int staticFontId=100;
static Dar<BaseFontPlat*> staticFontPlatDar;

FontPlat::FontPlat(const char* name,int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol)
{
	m_szName = strdup(name);
	m_iTall = tall;
	m_iWide = wide;
	m_flRotation = rotation;
	m_iWeight = weight;
	m_bItalic = italic;
	m_bUnderline = underline;
	m_bStrikeOut = strikeout;
	m_bSymbol = symbol;

	int charset = symbol ? SYMBOL_CHARSET : ANSI_CHARSET;
	m_hFont = ::CreateFontA(tall, wide, (int)(rotation*10), (int)(rotation*10), 
									weight, 
									italic, 
									underline, 
									strikeout, 
									charset, 
									OUT_DEFAULT_PRECIS, 
									CLIP_DEFAULT_PRECIS, 
									DEFAULT_QUALITY, 
									DEFAULT_PITCH, 
									m_szName);

	m_hDC = ::CreateCompatibleDC(NULL);

	// set as the active font
	::SelectObject(m_hDC, m_hFont);
	::SetTextAlign(m_hDC, TA_LEFT | TA_TOP | TA_UPDATECP);

	// get info about the font
	GetTextMetrics(m_hDC, &tm);

	// code for rendering to a bitmap
	bufSize[0] = tm.tmMaxCharWidth;
	bufSize[1] = tm.tmHeight + tm.tmAscent + tm.tmDescent;

	::BITMAPINFOHEADER header;
	memset(&header, 0, sizeof(header));
	header.biSize = sizeof(header);
	header.biWidth = bufSize[0];
	header.biHeight = -bufSize[1];
	header.biPlanes = 1;
	header.biBitCount = 32;
	header.biCompression = BI_RGB;

	m_hDIB = ::CreateDIBSection(m_hDC, (BITMAPINFO*)&header, DIB_RGB_COLORS, (void**)(&buf), NULL, 0);
	::SelectObject(m_hDC, m_hDIB);

	// get char spacing
	// a is space before character (can be negative)
	// b is the width of the character
	// c is the space after the character
	memset(m_ABCWidthsCache, 0, sizeof(m_ABCWidthsCache));
	if (!::GetCharABCWidthsA(m_hDC, 0, ABCWIDTHS_CACHE_SIZE - 1, m_ABCWidthsCache))
	{
		// since that failed, it must be fixed width, zero everything so a and c will be zeros, then
		// fill b with the value from TEXTMETRIC
		for (int i = 0; i < ABCWIDTHS_CACHE_SIZE; i++)
		{
			m_ABCWidthsCache[i].abcB = (char)tm.tmAveCharWidth;
		}
	}
}

FontPlat::~FontPlat()
{
}

bool FontPlat::equals(const char* name,int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol)
{
	if (!stricmp(name, m_szName) 
		&& m_iTall == tall
		&& m_iWide == wide
		&& m_flRotation == rotation
		&& m_iWeight == weight
		&& m_bItalic == italic
		&& m_bUnderline == underline
		&& m_bStrikeOut == strikeout
		&& m_bSymbol == symbol)
		return true;

	return false;
}

void FontPlat::getCharRGBA(int ch,int rgbaX,int rgbaY,int rgbaWide,int rgbaTall,uchar* rgba)
{
	// set us up to render into our dib
	::SelectObject(m_hDC, m_hFont);

	// use render-to-bitmap to get our font texture
	::SetBkColor(m_hDC, RGB(0, 0, 0));
	::SetTextColor(m_hDC, RGB(255, 255, 255));
	::SetBkMode(m_hDC, OPAQUE);
	::MoveToEx(m_hDC, -m_ABCWidthsCache[ch].abcA, 0, NULL);

	// render the character
	char wch = (char)ch;
	::ExtTextOutA(m_hDC, 0, 0, 0, NULL, &wch, 1, NULL);
	::SetBkMode(m_hDC, TRANSPARENT);

	int wide = m_ABCWidthsCache[ch].abcB;
	if (wide > bufSize[0])
	{
		wide = bufSize[0];
	}
	int tall = tm.tmHeight;
	if (tall > bufSize[1])
	{
		tall = bufSize[1];
	}

	// iterate through copying the generated dib into the texture
	for (int j = 0; j < tall; j++)
	{
		for (int i = 0; i < wide; i++)
		{
			int x = rgbaX + i;
			int y = rgbaY + j;
			if ((x < rgbaWide) && (y < rgbaTall))
			{
				unsigned char *src = &buf[(j*bufSize[0]+i)*4];

				float r = (src[0]) / 255.0f;
				float g = (src[1]) / 255.0f;
				float b = (src[2]) / 255.0f;

				// Don't want anything drawn for tab characters.
				if (ch == '\t')
				{
					r = g = b = 0;
				}

				unsigned char *dst = &rgba[(y*rgbaWide+x)*4];
				dst[0] = (unsigned char)(r * 255.0f);
				dst[1] = (unsigned char)(g * 255.0f);
				dst[2] = (unsigned char)(b * 255.0f);
				dst[3] = (unsigned char)((r * 0.34f + g * 0.55f + b * 0.11f) * 255.0f);
			}
		}
	}
}

void FontPlat::getCharABCwide(int ch,int& a,int& b,int& c)
{
	a = m_ABCWidthsCache[ch].abcA;
	b = m_ABCWidthsCache[ch].abcB;
	c = m_ABCWidthsCache[ch].abcC;

	if (a < 0)
	{
		a = 0;
	}
}

int FontPlat::getTall()
{
	return tm.tmHeight;
}

void FontPlat::drawSetTextFont(SurfacePlat* plat)
{
	::SelectObject(plat->hdc, m_hFont);
}

FontPlat_Bitmap::FontPlat_Bitmap()
{
	m_pName=null;
}

FontPlat_Bitmap::~FontPlat_Bitmap()
{
}

FontPlat_Bitmap* FontPlat_Bitmap::Create(const char* name, FileImageStream* pStream)
{
	FontPlat_Bitmap* pBitmap=new FontPlat_Bitmap();
	if(pBitmap==null)
	{
		return null;
	}

	if(!LoadVFontDataFrom32BitTGA(pStream,&pBitmap->m_FontData))
	{
		delete pBitmap;
		return null;
	}

	pBitmap->m_pName=new char[strlen(name)+1];
	if(pBitmap->m_pName==null)
	{
		delete pBitmap;
		return null;
	}

	strcpy(pBitmap->m_pName,name);
	return pBitmap;
}

bool FontPlat_Bitmap::equals(const char* name,int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol)
{
	return false;
}

void FontPlat_Bitmap::getCharRGBA(int ch,int rgbaX,int rgbaY,int rgbaWide,int rgbaTall,uchar* rgba)
{
	uchar* pSrcPos;
	uchar* pOutPos;
	int x,y,outX,outY;

	if(ch<0)
		ch=0;
	else if(ch>=256)
		ch=256;

	for(y=0;y<m_FontData.m_BitmapCharHeight;y++)
	{
		pSrcPos=&m_FontData.m_pBitmap[m_FontData.m_BitmapCharWidth*(ch+y*256)];
		for(x=0;x<m_FontData.m_BitmapCharWidth;x++)
		{
			outX=rgbaX+x;
			outY=rgbaY+y;
			if ((outX<rgbaWide)&&(outY<rgbaTall))
			{
				pOutPos=&rgba[(outY*rgbaWide+outX)*4];
				if(pSrcPos[x]!=0)
				{
					pOutPos[0]=pOutPos[1]=pOutPos[2]=pOutPos[3]=255;
				}
				else
				{
					pOutPos[0]=pOutPos[1]=pOutPos[2]=pOutPos[3]=0;
				}
			}
		}
	}
}

void FontPlat_Bitmap::getCharABCwide(int ch,int& a,int& b,int& c)
{
	if(ch<0)
		ch=0;
	else if(ch>255)
		ch=255;

	a=c=0;
	b=m_FontData.m_CharWidths[ch]+1;
}

int FontPlat_Bitmap::getTall()
{
	return m_FontData.m_BitmapCharHeight;
}

void FontPlat_Bitmap::drawSetTextFont(SurfacePlat* plat)
{
}

Font::Font(const char* name,int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol)
{
	init(name,null,0,wide,tall,rotation,weight,italic,underline,strikeout,symbol);
}

Font::Font(const char* name,void *pFileData,int fileDataLen, int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol)
{
	init(name,pFileData,fileDataLen,wide,tall,rotation,weight,italic,underline,strikeout,symbol);
}

void Font::init(const char* name,void *pFileData,int fileDataLen, int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol)
{
	FontPlat_Bitmap*pBitmapFont=null;

	_name=strdup(name);
	_id=-1;

	if(pFileData!=null)
	{
		FileImageStream_Memory memStream(pFileData,fileDataLen);
		pBitmapFont=FontPlat_Bitmap::Create(name,&memStream);
		if(pBitmapFont!=null)
		{
			_plat=pBitmapFont;
			staticFontPlatDar.addElement(_plat);
			_id=staticFontId++;
		}
	}
	else
	{
		_plat=null;
		for(int i=0;i<staticFontPlatDar.getCount();i++)
		{
			if(staticFontPlatDar[i]->equals(name,tall,wide,rotation,weight,italic,underline,strikeout,symbol))
			{
				_plat=staticFontPlatDar[i];
				break;
			}
		}
		if(_plat==null)
		{
			_plat=new FontPlat(name,tall,wide,rotation,weight,italic,underline,strikeout,symbol);
			staticFontPlatDar.addElement(_plat);
			_id=staticFontId++;
		}
	}
}

void Font::getCharRGBA(int ch,int rgbaX,int rgbaY,int rgbaWide,int rgbaTall,uchar* rgba)
{
	_plat->getCharRGBA(ch,rgbaX,rgbaY,rgbaWide,rgbaTall,rgba);
}

void Font::getCharABCwide(int ch,int& a,int& b,int& c)
{
	_plat->getCharABCwide(ch,a,b,c);
}

int Font::getTall()
{
	return _plat->getTall();
}

namespace vgui
{
void Font_Reset()
{
	staticFontPlatDar.removeAll();
}
}
