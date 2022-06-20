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

FontPlat::FontPlat(const char* name,int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol) : m_ExtendedABCWidthsCache(256, 0, &ExtendedABCWidthsCacheLessFunc)
{
	m_bBitmapFont = false;

	strncpy( m_szName, name, sizeof( m_szName ));
	m_iTall = tall;
	m_iWeight = weight;
	m_iFlags = 0;
	m_bAntiAliased = false;
	m_bUnderlined = underline;
	m_iDropShadowOffset = 0;
	m_iOutlineSize = 0;
	m_iBlur = 0;
	m_iScanLines = 0;
	m_bRotary = false;
	m_bAdditive = false;

	// TODO
}

FontPlat::~FontPlat()
{
}

bool FontPlat::ExtendedABCWidthsCacheLessFunc(const abc_cache_t &lhs, const abc_cache_t &rhs)
{
	return lhs.wch < rhs.wch;
}

bool FontPlat::equals(const char* name,int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol)
{
	if (!stricmp(name, m_szName) 
		&& m_iTall == tall
		&& m_iWeight == weight
		&& m_bUnderlined == underline)
		return true;

	return false;
}

void FontPlat::getCharRGBA(int ch,int rgbaX,int rgbaY,int rgbaWide,int rgbaTall,uchar* rgba)
{
	// TODO
}

void FontPlat::getCharABCwide(int ch,int& a,int& b,int& c)
{
	// look for it in the cache
	abc_cache_t finder = { (wchar_t)ch };

	unsigned short i = m_ExtendedABCWidthsCache.Find(finder);
	if (m_ExtendedABCWidthsCache.IsValidIndex(i))
	{
		a = m_ExtendedABCWidthsCache[i].abc.a;
		b = m_ExtendedABCWidthsCache[i].abc.b;
		c = m_ExtendedABCWidthsCache[i].abc.c;
		return;
	}

	// TODO
}

int FontPlat::getTall()
{
	return m_iHeight;
}

int FontPlat::getWide()
{
	return m_iMaxCharWidth;
}

void FontPlat::drawSetTextFont(SurfacePlat* plat)
{
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

int FontPlat_Bitmap::getWide()
{
	return m_FontData.m_BitmapCharWidth;
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

int Font::getWide()
{
	return _plat->getWide();
}

namespace vgui
{
void Font_Reset()
{
	staticFontPlatDar.removeAll();
}
}
