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

#include<VGUI_App.h>
#include<VGUI_SurfaceBase.h>
#include"vgui_linux.h"
#include<sys/time.h>

using namespace vgui;

void App::platTick()
{
}

void App::setCursorPos(int x,int y)
{
}

void App::getCursorPos(int& x,int& y)
{
	_surfaceBaseDar[0]->GetMousePos(x,y);
}

void App::internalSetMouseArena(int x0,int y0,int x1,int y1,bool enabled)
{
}

long App::getTimeMillis()
{
	struct timeval tp;
	static int secbase = 0;

	gettimeofday(&tp, NULL);

	if (!secbase)
	{
		secbase = tp.tv_sec;
		return tp.tv_usec / 1000000.0;
	}

	return (tp.tv_sec - secbase) * 1000 + tp.tv_usec / 1000.0;
}

void App::setClipboardText(const char* text,int textLen)
{
}

int App::getClipboardTextCount()
{
	return 0;
}

int App::getClipboardText(int offset,char* buf,int bufLen)
{
	return 0;
}

bool App::setRegistryString(const char* key,const char* value)
{
	return false;
}

bool App::getRegistryString(const char* key,char* value,int valueLen)
{
	return false;
}

bool App::setRegistryInteger(const char* key,int value)
{
	return false;
}

bool App::getRegistryInteger(const char* key,int& value)
{
	return false;
}

App* App::getInstance()
{
	return _instance;
}
