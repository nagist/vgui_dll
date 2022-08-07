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

#include<VGUI_Color.h>
#include<VGUI_App.h>

using namespace vgui;

void Color::init()
{
	_color[0]=0;
	_color[1]=0;
	_color[2]=0;
	_color[3]=0;
	_schemeColor=Scheme::sc_user;
}

Color::Color()
{
	init();
}

Color::Color(int r,int g,int b,int a)
{
	init();
	setColor(r,g,b,a);
}

Color::Color(Scheme::SchemeColor sc)
{
	init();
	setColor(sc);
}

void Color::setColor(int r,int g,int b,int a)
{
	_color[0]=r;
	_color[1]=g;
	_color[2]=b;
	_color[3]=a;
	_schemeColor=Scheme::sc_user;
}

void Color::setColor(Scheme::SchemeColor sc)
{
	_schemeColor=sc;
}

void Color::getColor(int& r,int& g,int& b,int& a)
{
	if(_schemeColor==Scheme::sc_user)
	{
		r=_color[0];
		g=_color[1];
		b=_color[2];
		a=_color[3];
	}
	else
	{
		App::getInstance()->getScheme()->getColor(_schemeColor,r,g,b,a);
	}
}

void Color::getColor(Scheme::SchemeColor& sc)
{
	sc=_schemeColor;
}

int Color::operator[](int index)
{
	int co[4];
	getColor(co[0],co[1],co[2],co[3]);
	return co[index];
}
