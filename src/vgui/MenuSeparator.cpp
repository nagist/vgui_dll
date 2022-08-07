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

#include<VGUI_MenuSeparator.h>

using namespace vgui;

MenuSeparator::MenuSeparator(const char* text) : Label(text)
{
	setFont(Scheme::sf_primary3);
}

void MenuSeparator::paintBackground()
{
	int wide,tall;
	getPaintSize(wide,tall);

	drawSetColor(Scheme::sc_secondary3);
	drawFilledRect(0,0,wide,tall);

	int textWide,textTall;
	int gap=2;
	int tgap=2;

	getTextSize(textWide,textTall);

	if(textWide>0)
	{
		textWide+=(gap*2);
	}

	int wide2=(textWide/2);
	int tall2=(textTall/2)-(tgap/2);
	int x0=(wide/2)-wide2;
	int x1=(wide/2)+wide2;

	drawSetColor(Scheme::sc_secondary1);
	drawFilledRect(gap,tall2,x0,tall2+(tgap/2));
	drawFilledRect(x1,tall2,wide-gap,tall2+(tgap/2));

	drawSetColor(Scheme::sc_white);
	drawFilledRect(gap,tall2+(tgap/2),x0,tall2+tgap);
	drawFilledRect(x1,tall2+(tgap/2),wide-gap,tall2+tgap);
}
