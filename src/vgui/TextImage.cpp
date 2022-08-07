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

#include<VGUI_TextImage.h>
#include<VGUI_App.h>
#include<VGUI_Scheme.h>
#include<VGUI_Font.h>

using namespace vgui;

void TextImage::init(int textBufferLen,const char* text)
{
	_text=null;
	_font=null;
	_textBufferLen=0;
	_schemeFont=Scheme::sf_primary1;
	int wide,tall;
	setText(textBufferLen,text);
	getTextSize(wide,tall);
	setSize(wide,tall);
}

TextImage::TextImage(int textBufferLen,const char* text) : Image()
{
	init(textBufferLen,text);
}

TextImage::TextImage(const char* text) : Image()
{
	init(strlen(text)+1,text);
}

void TextImage::setText(int textBufferLen,const char* text)
{
	if(textBufferLen>_textBufferLen)
	{
		delete[] _text;
		_textBufferLen=textBufferLen;
		_text=new char[textBufferLen];
		if(_text==null)
		{
			_textBufferLen=0;
		}
	}
	if(_text!=null)
	{
		vgui_strcpy(_text,_textBufferLen,text);
	}

	int wide,tall;
	getTextSize(wide,tall);
	Image::setSize(wide,tall);
}

void TextImage::setText(const char* text)
{
	setText(strlen(text)+1,text);
}

void TextImage::setFont(vgui::Scheme::SchemeFont schemeFont)
{
	_schemeFont=schemeFont;
}

void TextImage::setFont(vgui::Font* font)
{
	_font=font;
}

Font* TextImage::getFont()
{
	if(_font==null)
	{
		return App::getInstance()->getScheme()->getFont(_schemeFont);
	}
	return _font;
}

void TextImage::setSize(int wide,int tall)
{
	Image::setSize(wide,tall);
}

void TextImage::paint(Panel* panel)
{
	int wide,tall;
	getSize(wide,tall);

	if(_text==null)
	{
		return;
	}

	Color color;
	getColor(color);

	int r,g,b,a;
	color.getColor(r,g,b,a);
	drawSetTextColor(r,g,b,a);

	Font* font=getFont();
	drawSetTextFont(font);

	int yAdd=font->getTall();
	int x=0,y=0;

	for(int i=0;;i++)
	{
		int ch=_text[i];

		int a,b,c;

		font->getCharABCwide(ch,a,b,c);
		int len=a+b+c;

		if(ch==0)
		{
			break;
		}
		else
		if(ch=='\r')
		{
		}		
		else
		if(ch=='\n')
		{
			x=0;
			y+=yAdd;
		}
		else
		if(ch==' ')
		{
			char nextch;
			nextch = _text[i+1];

			font->getCharABCwide(' ',a,b,c);

			if ( !(nextch==0) && !(nextch=='\n') && !(nextch=='\r') )
			{
				x+=a+b+c;
				if(x>wide)
				{
					x=0;
					y+=yAdd;
				}
			}
		}
		else
		{
			int ctr;
			for(ctr=1;;ctr++)
			{
				ch=_text[i+ctr];
				if( (ch==0) || (ch=='\n') || (ch=='\r') || (ch==' ') )
				{
					break;
				}
				else
				{
					int a,b,c;
					font->getCharABCwide(ch,a,b,c);
					len+=a+b+c;
				}
			}

			if((x+len)>wide)
			{
				x=0;
				y+=yAdd;
			}

			for(int j=0;j<ctr;j++)
			{
				ch=_text[i+j];
				font->getCharABCwide(ch,a,b,c);
				drawPrintChar(x,y,ch);
				x+=a+b+c;
			}
			
			i+=ctr-1;
		}
	}
}

void TextImage::getTextSizeWrapped(int& wideo,int& tallo)
{
	wideo=0;
	tallo=0;

	if(_text==null)
	{
		return;
	}

	int wide,tall;
	getSize(wide,tall);

	Font* font=getFont();

	int yAdd=font->getTall();
	int x=0,y=0;

	for(int i=0;;i++)
	{
		int ch=_text[i];

		int a,b,c;

		font->getCharABCwide(ch,a,b,c);
		int len=a+b+c;

		if(ch==0)
		{
			break;
		}
		else
		if(ch=='\r')
		{
		}		
		else
		if(ch=='\n')
		{
			x=0;
			y+=yAdd;
		}
		else
		if(ch==' ')
		{
			char nextch;
			nextch = _text[i+1];

			font->getCharABCwide(' ',a,b,c);

			if ( !(nextch==0) && !(nextch=='\n') && !(nextch=='\r') )
			{
				x+=a+b+c;
				if(x>wide)
				{
					x=0;
					y+=yAdd;
				}
			}
		}
		else
		{
			int ctr;
			for(ctr=1;;ctr++)
			{
				ch=_text[i+ctr];
				if( (ch==0) || (ch=='\n') || (ch=='\r') || (ch==' ') )
				{
					break;
				}
				else
				{
					int a,b,c;
					font->getCharABCwide(ch,a,b,c);
					len+=a+b+c;
				}
			}

			if((x+len)>wide)
			{
				x=0;
				y+=yAdd;
			}

			for(int j=0;j<ctr;j++)
			{
				ch=_text[i+j];
				font->getCharABCwide(ch,a,b,c);

				if((x+a+b+c)>wideo)
				{
					wideo=x+a+b+c;
				}
				if((y+yAdd)>tallo)
				{
					tallo=y+yAdd;
				}

				x+=a+b+c;
			}
			
			i+=ctr-1;
		}
	}
}

void TextImage::getTextSize(int& wide,int& tall)
{
	wide=0;
	tall=0;

	if(_text==null)
	{
		return;
	}

	Font* font=getFont();

	if(font==null)
	{
		return;
	}

	font->getTextSize(_text,wide,tall);
}
