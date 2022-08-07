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

#include<stdio.h>
#include<VGUI_SurfaceBase.h>
#include<VGUI_ImagePanel.h>
#include<VGUI_App.h>
#include<VGUI_Cursor.h>

using namespace vgui;

SurfaceBase::SurfaceBase(Panel* embeddedPanel)
{
	_embeddedPanel=embeddedPanel;
	_needsSwap=true;
	_emulatedCursor=new ImagePanel(null);
	_emulatedCursor->setVisible(false);
	_currentCursor=null;
	_embeddedPanel->setSurfaceBaseTraverse(this);
	getApp()->surfaceBaseCreated(this);
	_emulatedCursor->setParent(getPanel());
}

SurfaceBase::~SurfaceBase()
{
	getApp()->surfaceBaseDeleted(this);
}

Panel* SurfaceBase::getPanel()
{
	return _embeddedPanel;
}

void SurfaceBase::requestSwap()
{
	_needsSwap=true;
}

void SurfaceBase::resetModeInfo()
{
	_modeInfoDar.removeAll();
}

int SurfaceBase::getModeInfoCount()
{
	return _modeInfoDar.getCount();
}

bool SurfaceBase::getModeInfo(int index,int& wide,int& tall,int& bpp)
{
	if((index<0)||(index>=_modeInfoDar.getCount()))
	{
		return false;
	}

	sscanf(_modeInfoDar[index],"%dx%dx%d",&wide,&tall,&bpp);
	return true;
}

void SurfaceBase::addModeInfo(int wide,int tall,int bpp)
{
	char buf[256];
	sprintf(buf,"%dx%dx%d",wide,tall,bpp);
	_modeInfoDar.putElement(vgui_strdup(buf));
}

App* SurfaceBase::getApp()
{
	return App::getInstance();
}

void SurfaceBase::setEmulatedCursorVisible(bool state)
{
	_emulatedCursor->setVisible(state);
}

void SurfaceBase::setEmulatedCursorPos(int x,int y)
{
	getPanel()->removeChild(_emulatedCursor);
	getPanel()->addChild(_emulatedCursor);
	getPanel()->screenToLocal(x,y);

	if((_currentCursor!=null)&&(!_emulatedCursor->isVisible()))
	{
		int hx,hy;
		_currentCursor->getHotspot(hx,hy);
		x-=hx;
		y-=hy;
	}

	_emulatedCursor->setPos(x,y);
}
