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

#include<VGUI_Image.h>
#include<VGUI_Panel.h>

using namespace vgui;

Image::Image()
{
	_panel=null;
	setPos(0,0);
	setSize(0,0);
	setColor(Color(255,255,255,0));
}

void Image::setPos(int x,int y)
{
	_pos[0]=x;
	_pos[1]=y;
}

void Image::getPos(int& x,int& y)
{
	x=_pos[0];
	y=_pos[1];
}

void Image::getSize(int& wide,int& tall)
{
	wide=_size[0];
	tall=_size[1];
}

void Image::setColor(Color color)
{
	_color=color;
}

void Image::getColor(Color& color)
{
	color=_color;
}

void Image::setSize(int wide,int tall)
{
	_size[0]=wide;
	_size[1]=tall;
}

void Image::drawSetColor(Scheme::SchemeColor sc)
{
	_panel->drawSetColor(sc);
}

void Image::drawSetColor(int r,int g,int b,int a)
{
	_panel->drawSetColor(r,g,b,a);
}

void Image::drawFilledRect(int x0,int y0,int x1,int y1)
{
	x0+=_pos[0];
	y0+=_pos[1];
	x1+=_pos[0];
	y1+=_pos[1];
	_panel->drawFilledRect(x0,y0,x1,y1);
}

void Image::drawOutlinedRect(int x0,int y0,int x1,int y1)
{
	x0+=_pos[0];
	y0+=_pos[1];
	x1+=_pos[0];
	y1+=_pos[1];
	_panel->drawOutlinedRect(x0,y0,x1,y1);
}

void Image::drawSetTextFont(Scheme::SchemeFont sf)
{
	_panel->drawSetTextFont(sf);
}

void Image::drawSetTextFont(Font* font)
{
	_panel->drawSetTextFont(font);
}

void Image::drawSetTextColor(Scheme::SchemeColor sc)
{
	_panel->drawSetTextColor(sc);
}

void Image::drawSetTextColor(int r,int g,int b,int a)
{
	_panel->drawSetTextColor(r,g,b,a);
}

void Image::drawSetTextPos(int x,int y)
{
	x+=_pos[0];
	y+=_pos[1];
	_panel->drawSetTextPos(x,y);
}

void Image::drawPrintText(const char* str,int strlen)
{
	_panel->drawPrintText(str,strlen);
}

void Image::drawPrintText(int x,int y,const char* str,int strlen)
{
	x+=_pos[0];
	y+=_pos[1];
	_panel->drawPrintText(x,y,str,strlen);
}

void Image::drawPrintChar(char ch)
{
	_panel->drawPrintChar(ch);
}

void Image::drawPrintChar(int x,int y,char ch)
{
	x+=_pos[0];
	y+=_pos[1];
	_panel->drawPrintChar(x,y,ch);
}

void Image::drawSetTextureRGBA(int id,const char* rgba,int wide,int tall)
{
	_panel->drawSetTextureRGBA(id,rgba,wide,tall);
}

void Image::drawSetTexture(int id)
{
	_panel->drawSetTexture(id);
}

void Image::drawTexturedRect(int x0,int y0,int x1,int y1)
{
	_panel->drawTexturedRect(x0,y0,x1,y1);
}

void Image::paint(Panel* panel)
{
}

void Image::doPaint(Panel* panel)
{
	_panel=panel;
	paint(panel);
	_panel=null;
}
