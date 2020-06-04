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
#include"vgui_osx.h"

using namespace vgui;

static int staticFontId=100;
static Dar<BaseFontPlat*> staticFontPlatDar;

struct metrictweaks_t {
	const char *name;
	int tall;
	float ascent;
	float descent;
	float leading;
};
metrictweaks_t g_FontMetricTweaks[] =
{
	{ "Helvetica", 0, 1.0, 1.0, 1.05 },
	{ "Helvetica Bold", 0, 1.0, 1.0, 1.0 },
};

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
	
	m_ASTFont = 0;

	CFStringRef nameStr = CFStringCreateWithCString( kCFAllocatorDefault, name, kCFStringEncodingUTF8 );
	if ( nameStr != NULL )
	{
		m_ASTFont = ATSFontFindFromPostScriptName( nameStr, kNilOptions );
		CFRelease( nameStr );
	}

	if ( m_ASTFont == 0 )
	{	
		nameStr = CFStringCreateWithCString( kCFAllocatorDefault, name, kCFStringEncodingUTF8 );
		if ( nameStr != NULL )
		{
			m_ASTFont = ATSFontFindFromName( nameStr, kNilOptions );
			CFRelease( nameStr );
		}
	}
	
	ATSFontMetrics metrics;
	if ( ATSUCreateStyle( &m_ATSUStyle ) != noErr || ATSFontGetHorizontalMetrics( m_ASTFont, kATSOptionFlagsDefault, &metrics ) != noErr )
	{
		m_szName[0] = 0;
		return;
	}
	
	int tallAdd = 0;
	float ascentScale = 1.0;
	float descentScale = 1.0;
	float leadingScale = 1.0;

	for ( int i = 0 ; i < 2 ; i++ )
	{
		if ( !strcasecmp( name, g_FontMetricTweaks[i].name ) )
		{
			tallAdd = g_FontMetricTweaks[i].tall;
			ascentScale = g_FontMetricTweaks[i].ascent;
			descentScale = g_FontMetricTweaks[i].descent;
			leadingScale = g_FontMetricTweaks[i].leading;
			break;
		}
	}
	
	Fixed fontSize = FloatToFixed( (m_iTall + tallAdd) / (metrics.ascent - metrics.descent) + metrics.leading );
	Boolean isItalic = italic;
	Boolean isBoldface = false;
	Boolean isUnderline = ( m_bUnderlined != false );
	UInt32 useAntialias = ( m_bAntiAliased != false ) ? kATSStyleNoAntiAliasing : kATSStyleApplyAntiAliasing;
	
	ATSUAttributeTag attribTags[] = { kATSUFontTag, kATSUSizeTag, kATSUQDItalicTag, kATSUQDBoldfaceTag, kATSUStyleRenderingOptionsTag, kATSUQDUnderlineTag };
	ATSUAttributeValuePtr attribValues[] = { &m_ASTFont, &fontSize, &isItalic, &isBoldface, &useAntialias, &isUnderline };
	ByteCount attribSizes[] = { sizeof(ATSFontRef), sizeof(Fixed), sizeof(Boolean), sizeof(Boolean), sizeof(UInt32), sizeof(Boolean) };

	if ( ATSUSetAttributes( m_ATSUStyle, 6, attribTags, attribSizes, attribValues ) != noErr )
	{
		m_szName[0] = 0;
		return;
	}
	
	m_iAscent = ceilf( (m_iTall + tallAdd) * ( metrics.ascent / ( (metrics.ascent - metrics.descent) + metrics.leading) ) * ascentScale );
	m_iHeight = ceilf( (m_iTall + tallAdd) * ( ( (metrics.ascent * ascentScale) - (metrics.descent * descentScale) ) + (metrics.leading * leadingScale) ) + m_iDropShadowOffset + m_iOutlineSize * 2 );
	m_iMaxCharWidth = (m_iTall * metrics.maxAdvanceWidth) + 0.5;
	
	int bytesPerRow = m_iMaxCharWidth * 4;
	int bitmapSize = bytesPerRow * m_iHeight;
	m_pBitmapData = new unsigned char[bitmapSize];
	memset( m_pBitmapData, 0, bitmapSize );

	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	m_CGContext = CGBitmapContextCreate( m_pBitmapData, m_iMaxCharWidth, m_iHeight, 8, bytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast );
	CGColorSpaceRelease( colorSpace );
	
	ATSURGBAlphaColor color = { 1.0, 1.0, 1.0, 1.0 };
	ATSUAttributeTag colorTag = kATSURGBAlphaColorTag;
	ByteCount colorSize = sizeof(ATSURGBAlphaColor);
	ATSUAttributeValuePtr colorValue = &color;

	if ( ATSUSetAttributes( m_ATSUStyle, 1, &colorTag, &colorSize, &colorValue ) != noErr )
	{
		m_szName[0] = 0;
		return;
	}
}

FontPlat::~FontPlat()
{
	if ( m_CGContext != NULL )
	{
		CGContextRelease( m_CGContext );
	}

	if ( m_pBitmapData != NULL )
	{
		delete[] m_pBitmapData;
	}
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
	if ( m_CGContext == NULL )
	{
		return;
	}
	
	const UniChar text[2] = { ch, 0 };
	UniCharCount runLengths = 1;
	ATSUTextLayout textLayout;
	if ( ATSUCreateTextLayoutWithTextPtr( text, 0, 1, 1, 1, &runLengths, &m_ATSUStyle, &textLayout ) != noErr )
	{
		return;
	}
	
	ATSUAttributeTag layoutAttribTags[] = { kATSUCGContextTag };
	ByteCount layoutAttribSizes[] = { sizeof(CGContextRef) };
	ATSUAttributeValuePtr layoutAttribValues[] = { &m_CGContext };
	
	if ( ATSUSetLayoutControls( textLayout, 1, layoutAttribTags, layoutAttribSizes, layoutAttribValues ) != noErr )
	{
		return;
	}
	
	Rect textImageRect;
	if ( ATSUMeasureTextImage( textLayout, -1, -1, 0, 0, &textImageRect ) != noErr )
	{
		return;
	}
	
	CGRect rect = { 0, 0, m_iHeight, m_iMaxCharWidth };
	CGContextClearRect( m_CGContext, rect );
	CGContextFlush( m_CGContext );
	
	if ( ATSUDrawText( textLayout, 0, 1, Long2Fix( 0 ), Long2Fix( m_iHeight - m_iAscent ) ) != noErr )
	{
		return;
	}	
	
	unsigned char *data = (unsigned char *)CGBitmapContextGetData( m_CGContext );
	for ( int i = 0; i < m_iHeight; i++ )
	{
		memcpy( &rgba[rgbaWide * 4 * (i + rgbaY) + rgbaX * 4], &data[m_iMaxCharWidth * i * 4], m_iMaxCharWidth * 4 );
		if ( i > rgbaTall )
		{
			break;
		}
	}
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
	
	const UniChar text[2] = { ch, 0 };
	UniCharCount runLengths = 1;
	ATSUTextLayout textLayout;
	if ( ATSUCreateTextLayoutWithTextPtr( text, 0, 2, 2, 1, &runLengths, &m_ATSUStyle, &textLayout ) != noErr )
	{
		return;
	}
	
	ATSUTextMeasurement lineWidth = IntToFixed(2000);
	Fract lineFlushFactor = 0;
	
	ATSUAttributeTag layoutAttribTags[] = { kATSULineWidthTag, kATSULineFlushFactorTag };
	ByteCount layoutAttribSizes[] = { sizeof(ATSUTextMeasurement), sizeof(Fract) };
	ATSUAttributeValuePtr layoutAttribValues[] = { &lineWidth, &lineFlushFactor };
	
	if ( ATSUSetLayoutControls( textLayout, 2, layoutAttribTags, layoutAttribSizes, layoutAttribValues ) != noErr )
	{
		return;
	}
	
	ATSLayoutRecord *layoutPtr;
	ItemCount count;
	
	if ( ATSUDirectGetLayoutDataArrayPtrFromTextLayout( textLayout, 0, kATSUDirectDataLayoutRecordATSLayoutRecordCurrent, (void **)&layoutPtr, &count ) != noErr )
	{
		return;
	}
	
	ATSGlyphScreenMetrics glyphScreenMetrics;
	if ( ATSUGlyphGetScreenMetrics( m_ATSUStyle, 4, &layoutPtr->glyphID, sizeof(ATSLayoutRecord), false, false, &glyphScreenMetrics ) != noErr )
	{
		return;
	}
	
	finder.abc.a = glyphScreenMetrics.sideBearing.x - m_iBlur - m_iOutlineSize;
	finder.abc.b = glyphScreenMetrics.deviceAdvance.x + ((m_iBlur + m_iOutlineSize) * 2) + m_iDropShadowOffset;
	finder.abc.c = glyphScreenMetrics.otherSideBearing.x - m_iBlur - m_iDropShadowOffset - m_iOutlineSize;
	
	if ( finder.abc.a + finder.abc.b == -finder.abc.c )
	{
		if ( finder.abc.b == -finder.abc.c )
		{
			finder.abc.c = 0;
		}
		else
		{
			if ( finder.abc.a + finder.abc.b != 0 )
			{
				finder.abc.c = 0;
			}
			
			finder.abc.a = 0;
		}
	}
	
	if ( ch == ' ' && !strstr( m_szName, "Helvetica" ) && !strstr( m_szName, "Verdana" ) )
	{
		if ( m_iHeight < 21 )
		{
			if ( m_iHeight > 10 )
			{
				finder.abc.b -= 3;
			}
			
			finder.abc.b -= 1;
		}
	}
	
	m_ExtendedABCWidthsCache.Insert(finder);
	
	a = finder.abc.a;
	b = finder.abc.b;
	c = finder.abc.c;
	
	if ( a < 0 )
	{
		a = 0;
	}
	
	ATSUDirectReleaseLayoutDataArrayPtr( NULL, kATSUDirectDataLayoutRecordATSLayoutRecordCurrent, (void **)&layoutPtr );
	ATSUDisposeTextLayout( textLayout );
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
