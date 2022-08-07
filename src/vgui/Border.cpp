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

#include<VGUI_Border.h>

using namespace vgui;

Border::Border() : Image()
{
	_inset[0]=0;
	_inset[1]=0;
	_inset[2]=0;
	_inset[3]=0;
	_panel=null;
}

Border::Border(int left,int top,int right,int bottom) : Image()
{
	_inset[0]=0;
	_inset[1]=0;
	_inset[2]=0;
	_inset[3]=0;
	_panel=null;
	setInset(left,top,right,bottom);
}

void Border::setInset(int left,int top,int right,int bottom)
{
	_inset[0]=left;
	_inset[1]=top;
	_inset[2]=right;
	_inset[3]=bottom;
}

void Border::getInset(int& left,int& top,int& right,int& bottom)
{
	left=_inset[0];
	top=_inset[1];
	right=_inset[2];
	bottom=_inset[3];
}

void Border::drawFilledRect(int x0,int y0,int x1,int y1)
{
	Image::drawFilledRect(x0-_inset[0],y0-_inset[1],x1-_inset[0],y1-_inset[1]);
}

void Border::drawOutlinedRect(int x0,int y0,int x1,int y1)
{
	Image::drawOutlinedRect(x0-_inset[0],y0-_inset[1],x1-_inset[0],y1-_inset[1]);
}

void Border::drawSetTextPos(int x,int y)
{
	Image::drawSetTextPos(x-_inset[0],y-_inset[1]);
}

void Border::drawPrintText(int x,int y,const char* str,int strlen)
{
	Image::drawPrintText(x-_inset[0],y-_inset[1],str,strlen);
}

void Border::drawPrintChar(int x,int y,char ch)
{
	Image::drawPrintChar(x-_inset[0],y-_inset[1],ch);
}
