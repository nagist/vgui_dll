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

#include<assert.h>
#include<stdio.h>
#include<VGUI_Surface.h>
#include<VGUI_Cursor.h>
#include<VGUI_KeyCode.h>
#include<VGUI_Panel.h>
#include<VGUI_App.h>
#include<VGUI_ImagePanel.h>
#include<VGUI_Bitmap.h>
#include<VGUI_Font.h>
#include"Font.h"

using namespace vgui;

class Texture
{
public:
	int     _id;
	int     _wide;
	int     _tall;
	void   *_dib;
};

#define MAXTEXTURECOUNT 128
static int      staticTextureCount = 0;
static Texture  staticTexture[MAXTEXTURECOUNT];
static Texture *staticTextureCurrent = NULL;

static Texture *staticGetTextureById(int id)
{
	if(staticTextureCurrent!=null)
	{
		if(staticTextureCurrent->_id==id)
		{
			return staticTextureCurrent;
		}
	}
	
	for(int i=0;i<staticTextureCount;i++)
	{
		if(staticTexture[i]._id==id)
		{
			return &staticTexture[i];
		}
	}
	return null;
}

bool Surface::createPlat()
{
	return true;
}

bool Surface::recreateContext()
{
	int wide,tall;
	getPanel()->getSize(wide,tall);

	return true;
}

void Surface::applyChanges()
{
}

void Surface::swapBuffers()
{
}

void Surface::drawSetColor(int r,int g,int b,int a)
{
}

void Surface::drawFilledRect(int x0,int y0,int x1,int y1)
{
}

void Surface::drawOutlinedRect(int x0,int y0,int x1,int y1)
{
	// draw an outline of a rectangle using 4 filledRect
	drawFilledRect(x0,y0,x1,y0+1);     // top
	drawFilledRect(x0,y1-1,x1,y1);	   // bottom
	drawFilledRect(x0,y0+1,x0+1,y1-1); // left
	drawFilledRect(x1-1,y0+1,x1,y1-1); // right
}

void Surface::drawSetTextColor(int r,int g,int b,int a)
{
}

void Surface::drawPrintText(const char* text,int textLen)
{
}

int Surface::createNewTextureID(void)
{
	//!! hack, arbitrary base
	static int staticBindIndex = 2700;
	return staticBindIndex++;
}

void Surface::drawSetTextureRGBA(int id,const char* rgba,int wide,int tall)
{
	Texture *texture = staticGetTextureById(id);
	if (!texture)
	{
		if (staticTextureCount >= MAXTEXTURECOUNT)
			return;

		// allocate a new texture
		texture = &staticTexture[staticTextureCount++];
		texture->_id = id;
	}
}

void Surface::drawSetTexture(int id)
{
	staticTextureCurrent = staticGetTextureById(id);
}

void Surface::drawTexturedRect(int x0,int y0,int x1,int y1)
{
}

void Surface::pushMakeCurrent(Panel* panel,bool useInsets)
{
	int inset[4];

	//!! need to make the inset part of Panel
	panel->getInset(inset[0],inset[1],inset[2],inset[3]);

	if(!useInsets)
	{
		inset[0]=0;
		inset[1]=0;
		inset[2]=0;
		inset[3]=0;
	}

	int absThis[4];
	getPanel()->getAbsExtents(absThis[0],absThis[1],absThis[2],absThis[3]);

	int absPanel[4];
	panel->getAbsExtents(absPanel[0],absPanel[1],absPanel[2],absPanel[3]);

	int clipRect[4];
	panel->getClipRect(clipRect[0],clipRect[1],clipRect[2],clipRect[3]);
}

void Surface::popMakeCurrent(Panel* panel)
{
}

void Surface::enableMouseCapture(bool state)
{
}

void Surface::setCursor(Cursor* cursor)
{
	_currentCursor = cursor;

	if (cursor != null)
	{
		_emulatedCursor->setImage(cursor->getBitmap());

		switch (cursor->getDefaultCursor())
		{
			case Cursor::dc_none:
			case Cursor::dc_arrow:
			case Cursor::dc_ibeam:
			case Cursor::dc_hourglass:
			case Cursor::dc_crosshair:
			case Cursor::dc_up:
			case Cursor::dc_sizenwse:
			case Cursor::dc_sizenesw:
			case Cursor::dc_sizewe:
			case Cursor::dc_sizens:
			case Cursor::dc_sizeall:
			case Cursor::dc_no:
			case Cursor::dc_hand:
			{
				break;
			}
			case Cursor::dc_user:
			{
				break;
			}
		}
	}
	else
	{
		_emulatedCursor->setImage(null);
	}
}

void Surface::invalidate(Panel *panel)
{
}

void Surface::drawSetTextFont(Font* font)
{
	if (!font)
	{
		return;
	}

	font->getPlat()->drawSetTextFont(_plat);
}

void Surface::setTitle(const char* title)
{
}

bool Surface::hasFocus()
{
	return true;
}

int Surface::getModeInfoCount()
{
	resetModeInfo();
	addModeInfo(640,480,16);
	addModeInfo(800,600,16);
	return SurfaceBase::getModeInfoCount();
}

bool Surface::setFullscreenMode(int wide,int tall,int bpp)
{
	if (_plat->isFullscreen && _plat->fullscreenInfo[0] == wide && _plat->fullscreenInfo[1] == tall && _plat->fullscreenInfo[2] == bpp)
	{
		return true;
	}

	if (_modeInfoDar.getCount() == 0)
	{
		getModeInfoCount();
	}

	return false;
}

void Surface::setWindowedMode()
{
}

void Surface::drawSetTextPos(int x,int y)
{
}

void Surface::setAsTopMost(bool state)
{
}

bool Surface::isWithin(int x,int y)
{
	return false;
}
