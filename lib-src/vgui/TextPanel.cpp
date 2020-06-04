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

#include<VGUI_TextPanel.h>
#include<VGUI_TextImage.h>

using namespace vgui;

TextPanel::TextPanel(const char* text,int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	_textImage=new TextImage(text);
	_textImage->setSize(wide,tall);
}

void TextPanel::setText(const char* text)
{
	_textImage->setText(text);
}

void TextPanel::setFont(vgui::Scheme::SchemeFont schemeFont)
{
	_textImage->setFont(schemeFont);
}

void TextPanel::setFont(vgui::Font* font)
{
	_textImage->setFont(font);
}

void TextPanel::paint()
{
	_textImage->doPaint(this);
}

void TextPanel::setSize(int wide,int tall)
{
	Panel::setSize(wide,tall);
	getPaintSize(wide,tall);
	_textImage->setSize(wide,tall);
}

void TextPanel::setFgColor(int r,int g,int b,int a)
{
	Panel::setFgColor(r,g,b,a);
	_textImage->setColor(Color(r,g,b,a));
}

void TextPanel::setFgColor(Scheme::SchemeColor sc)
{
	Panel::setFgColor(sc);
	_textImage->setColor(Color(sc));
}

TextImage* TextPanel::getTextImage()
{
	return _textImage;
}
