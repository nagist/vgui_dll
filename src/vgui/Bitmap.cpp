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

#include<VGUI_Bitmap.h>
#include<VGUI_Panel.h>
#include<VGUI_SurfaceBase.h>

using namespace vgui;

Bitmap::Bitmap() : Image()
{
	_rgba=null;
	_id=0;
	_uploaded=false;
}

void Bitmap::setSize(int wide,int tall)
{
	Image::setSize(wide,tall);

	if(_rgba!=null)
	{
		delete[] _rgba;
	}

	_rgba=new uchar[wide*tall*4];
}

void Bitmap::setRGBA(int x,int y,uchar r,uchar g,uchar b,uchar a)
{
	if(_rgba==null)
	{
		return;
	}

	int wide,tall;
	getSize(wide,tall);

	if ((x>=0)&&(x<wide)&&(y>=0)&&(y<tall))
	{
		_rgba[((y*wide)+x)*4]=r;
		_rgba[((y*wide)+x)*4+1]=g;
		_rgba[((y*wide)+x)*4+2]=b;
		_rgba[((y*wide)+x)*4+3]=a;
	}
}

void Bitmap::paint(Panel* panel)
{
	if(_rgba==null)
	{
		return;
	}

	int wide,tall;
	getSize(wide,tall);

	if(_id==0)
	{
		if(panel->getSurfaceBase()==null)
		{
			return;
		}

		_id=panel->getSurfaceBase()->createNewTextureID();
	}

	if(!_uploaded)
	{
		drawSetTextureRGBA(_id,(const char*)_rgba,wide,tall);
		_uploaded=true;
	}
	
	Color color;
	getColor(color);

	int r,g,b,a;
	color.getColor(r,g,b,a);
	drawSetTexture(_id);
	drawSetColor(r,g,b,a);

	int x,y;
	getPos(x,y);
	drawTexturedRect(x,y,x+wide,y+tall);
}
