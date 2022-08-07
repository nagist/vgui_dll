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
#include<zmouse.h>

using namespace vgui;

class Texture
{
public:
	int     _id;
	HBITMAP _bitmap;
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

static KeyCode s_pVirtualKeyToKeyCode[256];
static HICON staticDefaultCursor[20];
static HICON staticCurrentCursor = NULL;
static WNDCLASS staticWndclass = { NULL };
static ATOM staticWndclassAtom = 0;

// these functions defined below
static LRESULT CALLBACK staticProc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);

bool Surface::createPlat()
{
	//load up all default cursors, this gets called everytime a Surface is created, but
	//who cares
	staticDefaultCursor[Cursor::dc_none]     =null;
	staticDefaultCursor[Cursor::dc_arrow]    =(HICON)LoadCursor(null,(LPCTSTR)OCR_NORMAL);
	staticDefaultCursor[Cursor::dc_ibeam]    =(HICON)LoadCursor(null,(LPCTSTR)OCR_IBEAM);
	staticDefaultCursor[Cursor::dc_hourglass]=(HICON)LoadCursor(null,(LPCTSTR)OCR_WAIT);
	staticDefaultCursor[Cursor::dc_crosshair]=(HICON)LoadCursor(null,(LPCTSTR)OCR_CROSS);
	staticDefaultCursor[Cursor::dc_up]       =(HICON)LoadCursor(null,(LPCTSTR)OCR_UP);
	staticDefaultCursor[Cursor::dc_sizenwse] =(HICON)LoadCursor(null,(LPCTSTR)OCR_SIZENWSE);
	staticDefaultCursor[Cursor::dc_sizenesw] =(HICON)LoadCursor(null,(LPCTSTR)OCR_SIZENESW);
	staticDefaultCursor[Cursor::dc_sizewe]   =(HICON)LoadCursor(null,(LPCTSTR)OCR_SIZEWE);
	staticDefaultCursor[Cursor::dc_sizens]   =(HICON)LoadCursor(null,(LPCTSTR)OCR_SIZENS);
	staticDefaultCursor[Cursor::dc_sizeall]  =(HICON)LoadCursor(null,(LPCTSTR)OCR_SIZEALL);
	staticDefaultCursor[Cursor::dc_no]       =(HICON)LoadCursor(null,(LPCTSTR)OCR_NO);
	staticDefaultCursor[Cursor::dc_hand]     =(HICON)LoadCursor(null,(LPCTSTR)32649);

	s_pVirtualKeyToKeyCode['0']			=vgui::KEY_0;
	s_pVirtualKeyToKeyCode['1']			=vgui::KEY_1;
	s_pVirtualKeyToKeyCode['2']			=vgui::KEY_2;
	s_pVirtualKeyToKeyCode['3']			=vgui::KEY_3;
	s_pVirtualKeyToKeyCode['4']			=vgui::KEY_4;
	s_pVirtualKeyToKeyCode['5']			=vgui::KEY_5;
	s_pVirtualKeyToKeyCode['6']			=vgui::KEY_6;
	s_pVirtualKeyToKeyCode['7']			=vgui::KEY_7;
	s_pVirtualKeyToKeyCode['8']			=vgui::KEY_8;
	s_pVirtualKeyToKeyCode['9']			=vgui::KEY_9;
	s_pVirtualKeyToKeyCode['A']			=vgui::KEY_A;
	s_pVirtualKeyToKeyCode['B']			=vgui::KEY_B;
	s_pVirtualKeyToKeyCode['C']			=vgui::KEY_C;
	s_pVirtualKeyToKeyCode['D']			=vgui::KEY_D;
	s_pVirtualKeyToKeyCode['E']			=vgui::KEY_E;
	s_pVirtualKeyToKeyCode['F']			=vgui::KEY_F;
	s_pVirtualKeyToKeyCode['G']			=vgui::KEY_G;
	s_pVirtualKeyToKeyCode['H']			=vgui::KEY_H;
	s_pVirtualKeyToKeyCode['I']			=vgui::KEY_I;
	s_pVirtualKeyToKeyCode['J']			=vgui::KEY_J;
	s_pVirtualKeyToKeyCode['K']			=vgui::KEY_K;
	s_pVirtualKeyToKeyCode['L']			=vgui::KEY_L;
	s_pVirtualKeyToKeyCode['M']			=vgui::KEY_M;
	s_pVirtualKeyToKeyCode['N']			=vgui::KEY_N;
	s_pVirtualKeyToKeyCode['O']			=vgui::KEY_O;
	s_pVirtualKeyToKeyCode['P']			=vgui::KEY_P;
	s_pVirtualKeyToKeyCode['Q']			=vgui::KEY_Q;
	s_pVirtualKeyToKeyCode['R']			=vgui::KEY_R;
	s_pVirtualKeyToKeyCode['S']			=vgui::KEY_S;
	s_pVirtualKeyToKeyCode['T']			=vgui::KEY_T;
	s_pVirtualKeyToKeyCode['U']			=vgui::KEY_U;
	s_pVirtualKeyToKeyCode['V']			=vgui::KEY_V;
	s_pVirtualKeyToKeyCode['W']			=vgui::KEY_W;
	s_pVirtualKeyToKeyCode['X']			=vgui::KEY_X;
	s_pVirtualKeyToKeyCode['Y']			=vgui::KEY_Y;
	s_pVirtualKeyToKeyCode['Z']			=vgui::KEY_Z;
	s_pVirtualKeyToKeyCode[VK_NUMPAD0]	=vgui::KEY_PAD_0;
	s_pVirtualKeyToKeyCode[VK_NUMPAD1]	=vgui::KEY_PAD_1;
	s_pVirtualKeyToKeyCode[VK_NUMPAD2]	=vgui::KEY_PAD_2;
	s_pVirtualKeyToKeyCode[VK_NUMPAD3]	=vgui::KEY_PAD_3;
	s_pVirtualKeyToKeyCode[VK_NUMPAD4]	=vgui::KEY_PAD_4;
	s_pVirtualKeyToKeyCode[VK_NUMPAD5]	=vgui::KEY_PAD_5;
	s_pVirtualKeyToKeyCode[VK_NUMPAD6]	=vgui::KEY_PAD_6;
	s_pVirtualKeyToKeyCode[VK_NUMPAD7]	=vgui::KEY_PAD_7;
	s_pVirtualKeyToKeyCode[VK_NUMPAD8]	=vgui::KEY_PAD_8;
	s_pVirtualKeyToKeyCode[VK_NUMPAD9]	=vgui::KEY_PAD_9;
	s_pVirtualKeyToKeyCode[VK_DIVIDE]	=vgui::KEY_PAD_DIVIDE;
	s_pVirtualKeyToKeyCode[VK_MULTIPLY]	=vgui::KEY_PAD_MULTIPLY;
	s_pVirtualKeyToKeyCode[VK_SUBTRACT]	=vgui::KEY_PAD_MINUS;
	s_pVirtualKeyToKeyCode[VK_ADD]		=vgui::KEY_PAD_PLUS;
	s_pVirtualKeyToKeyCode[VK_DECIMAL]	=vgui::KEY_PAD_DECIMAL;
	s_pVirtualKeyToKeyCode[0xdb]		=vgui::KEY_LBRACKET;
	s_pVirtualKeyToKeyCode[0xdd]		=KEY_RBRACKET;
	s_pVirtualKeyToKeyCode[0xba]		=KEY_SEMICOLON;
	s_pVirtualKeyToKeyCode[0xde]		=KEY_APOSTROPHE;
	s_pVirtualKeyToKeyCode[0xc0]		=KEY_BACKQUOTE;
	s_pVirtualKeyToKeyCode[0xbc]		=KEY_COMMA;
	s_pVirtualKeyToKeyCode[0xbe]		=KEY_PERIOD;
	s_pVirtualKeyToKeyCode[0xbf]		=KEY_SLASH;
	s_pVirtualKeyToKeyCode[0xdc]		=KEY_BACKSLASH;
	s_pVirtualKeyToKeyCode[0xbd]		=KEY_MINUS;
	s_pVirtualKeyToKeyCode[0xbb]		=KEY_EQUAL;
	s_pVirtualKeyToKeyCode[VK_RETURN]	=vgui::KEY_ENTER;
	s_pVirtualKeyToKeyCode[VK_SPACE]	=vgui::KEY_SPACE;
	s_pVirtualKeyToKeyCode[VK_BACK]		=vgui::KEY_BACKSPACE;
	s_pVirtualKeyToKeyCode[VK_TAB]		=vgui::KEY_TAB;
	s_pVirtualKeyToKeyCode[VK_CAPITAL]	=vgui::KEY_CAPSLOCK;
	s_pVirtualKeyToKeyCode[VK_NUMLOCK]	=vgui::KEY_NUMLOCK;
	s_pVirtualKeyToKeyCode[VK_ESCAPE]	=vgui::KEY_ESCAPE;
	s_pVirtualKeyToKeyCode[VK_SCROLL]	=vgui::KEY_SCROLLLOCK;
	s_pVirtualKeyToKeyCode[VK_INSERT]	=vgui::KEY_INSERT;
	s_pVirtualKeyToKeyCode[VK_DELETE]	=vgui::KEY_DELETE;
	s_pVirtualKeyToKeyCode[VK_HOME]		=vgui::KEY_HOME;
	s_pVirtualKeyToKeyCode[VK_END]		=vgui::KEY_END;
	s_pVirtualKeyToKeyCode[VK_PRIOR]	=vgui::KEY_PAGEUP;
	s_pVirtualKeyToKeyCode[VK_NEXT]		=vgui::KEY_PAGEDOWN;
	s_pVirtualKeyToKeyCode[VK_PAUSE]	=KEY_BREAK;
	s_pVirtualKeyToKeyCode[VK_SHIFT]	=KEY_RSHIFT;
	s_pVirtualKeyToKeyCode[VK_MENU]		=KEY_RALT;
	s_pVirtualKeyToKeyCode[VK_CONTROL]	=KEY_RCONTROL;
	s_pVirtualKeyToKeyCode[VK_LWIN]		=KEY_LWIN;
	s_pVirtualKeyToKeyCode[VK_RWIN]		=KEY_RWIN;
	s_pVirtualKeyToKeyCode[VK_APPS]		=KEY_APP;
	s_pVirtualKeyToKeyCode[VK_UP]		=KEY_UP;
	s_pVirtualKeyToKeyCode[VK_LEFT]		=KEY_LEFT;
	s_pVirtualKeyToKeyCode[VK_DOWN]		=KEY_DOWN;
	s_pVirtualKeyToKeyCode[VK_RIGHT]	=KEY_RIGHT;	
	s_pVirtualKeyToKeyCode[VK_F1]		=KEY_F1;
	s_pVirtualKeyToKeyCode[VK_F2]		=KEY_F2;
	s_pVirtualKeyToKeyCode[VK_F3]		=KEY_F3;
	s_pVirtualKeyToKeyCode[VK_F4]		=KEY_F4;
	s_pVirtualKeyToKeyCode[VK_F5]		=KEY_F5;
	s_pVirtualKeyToKeyCode[VK_F6]		=KEY_F6;
	s_pVirtualKeyToKeyCode[VK_F7]		=KEY_F7;
	s_pVirtualKeyToKeyCode[VK_F8]		=KEY_F8;
	s_pVirtualKeyToKeyCode[VK_F9]		=KEY_F9;
	s_pVirtualKeyToKeyCode[VK_F10]		=KEY_F10;
	s_pVirtualKeyToKeyCode[VK_F11]		=KEY_F11;
	s_pVirtualKeyToKeyCode[VK_F12]		=KEY_F12;

	// make and register a very simple Window Class
	memset( &staticWndclass,0,sizeof(staticWndclass) );
	staticWndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	staticWndclass.lpfnWndProc = staticProc;
	staticWndclass.hInstance = GetModuleHandle(NULL);
	staticWndclass.lpszClassName = "Surface";
	staticWndclassAtom = ::RegisterClass( &staticWndclass );

	int x,y,wide,tall;
	getPanel()->getBounds(x,y,wide,tall);

	//create the window and initialize platform specific data
	//window is initial a popup and not visible
	//when applyChanges is called the window will be shown unless
	//it setVisible(false) is called
	SurfacePlat *plat = new SurfacePlat();
	plat->hwnd = CreateWindowEx(0, "Surface", "", WS_POPUP, x, y, wide, tall, NULL, NULL, GetModuleHandle(NULL), NULL);
	plat->clipRgn = CreateRectRgn(0,0,64,64);
	plat->hdc = CreateCompatibleDC(NULL);
	plat->hwndDC = GetDC(_plat->hwnd);
	plat->bitmap = null;
	plat->bitmapSize[0] = 0;
	plat->bitmapSize[1] = 0;
	plat->isFullscreen = false;

	::SetBkMode(plat->hdc, TRANSPARENT);
	::SetWindowLong(plat->hwnd, GWL_USERDATA, (LONG)this);
	::SetTextAlign(plat->hdc, TA_LEFT | TA_TOP | TA_UPDATECP);

	return true;
}

LRESULT CALLBACK staticProc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
	LRESULT ret = TRUE;

	Surface *surface = (Surface *)GetWindowLong(hwnd, GWL_USERDATA);

	switch (msg)
	{
		case WM_SETFOCUS:
		{
			surface->getPanel()->requestFocus();
			break;
		}
		case WM_SETCURSOR:
		{		
			SetCursor(staticCurrentCursor);
			break;
		}
		case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = (short)LOWORD(lparam);
			pt.y = (short)HIWORD(lparam);
			surface->getApp()->internalCursorMoved(pt.x, pt.y, surface);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			surface->getApp()->internalMousePressed(MOUSE_LEFT, surface);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			surface->getApp()->internalMousePressed(MOUSE_RIGHT, surface);
			break;
		}
		case WM_MBUTTONDOWN:
		{
			surface->getApp()->internalMousePressed(MOUSE_MIDDLE, surface);
			break;
		}
		case WM_LBUTTONDBLCLK:
		{
			surface->getApp()->internalMouseDoublePressed(MOUSE_LEFT, surface);
			break;
		}
		case WM_RBUTTONDBLCLK:
		{
			surface->getApp()->internalMouseDoublePressed(MOUSE_RIGHT, surface);
			break;
		}
		case WM_MBUTTONDBLCLK:
		{
			surface->getApp()->internalMouseDoublePressed(MOUSE_MIDDLE, surface);
			break;
		}
		case WM_LBUTTONUP:
		{
			surface->getApp()->internalMouseReleased(MOUSE_LEFT, surface);
			break;
		}
		case WM_RBUTTONUP:
		{
			surface->getApp()->internalMouseReleased(MOUSE_RIGHT, surface);
			break;
		}
		case WM_MBUTTONUP:
		{
			surface->getApp()->internalMouseReleased(MOUSE_MIDDLE, surface);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			surface->getApp()->internalMouseWheeled(((short)HIWORD(wparam))/WHEEL_DELTA, surface);
			break;
		}
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			int code = wparam;
			if (!(lparam & (1<<30)))
			{
				surface->getApp()->internalKeyPressed(s_pVirtualKeyToKeyCode[code], surface);
			}
			surface->getApp()->internalKeyTyped(s_pVirtualKeyToKeyCode[code], surface);
			break;
		}
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			int code=wparam;
			surface->getApp()->internalKeyReleased(s_pVirtualKeyToKeyCode[code], surface);
			break;
		}
		case WM_ERASEBKGND:
		{
			//since the vgui invalidate call does not erase the background
			//this will only be called when windows itselfs wants a repaint.
			//this is the desired behavior because this call will for the
			//surface and all its children to end up being repainted, which
			//is what you want when windows wants you to repaint the surface,
			//but not what you want when say a control wants to be painted
			//Panel::repaint will always invalidate the surface so it will
			//get a WM_PAINT, but that does not necessarily mean you want
			//the whole surface painted
			//simply this means.. this call only happens when windows wants the repaint
			//and WM_PAINT gets called just after this to do the real painting

			surface->getPanel()->repaint();
			break;
		}
		case WM_PAINT:
		{
			//surface was by repainted vgui or by windows itself, do the repainting all repainting 
			//will goes through here and nowhere else

			PAINTSTRUCT ps;
			HDC hDC=::BeginPaint(hwnd,&ps);
			surface->getPanel()->solveTraverse();
			surface->getPanel()->paintTraverse();
			::EndPaint(hwnd,&ps);

			//clear the update rectangle so it does not get another repaint
			::ValidateRect(hwnd, NULL);	

			break;
		}
	}
	return DefWindowProc(hwnd,msg,wparam,lparam);
}

bool Surface::recreateContext()
{
	int wide,tall;
	getPanel()->getSize(wide,tall);

	// rebuild bitmap only if necessary
	// simple scheme to prevent excessive allocations by allocating only when
	// bigger. It also adds in 100 extra for subsequent sizings
	// it will also realloc if the size is 200 smaller to shrink memory usage
	if ((wide > _plat->bitmapSize[0]) 
		|| (tall > _plat->bitmapSize[1])
		|| (wide < (_plat->bitmapSize[0] - 200)) 
		|| (tall < (_plat->bitmapSize[1] - 200)))
	{
		if (_plat->bitmap != null)
		{
			::DeleteObject(_plat->bitmap);
		}

		_plat->hwndDC = GetDC(_plat->hwnd);

		_plat->bitmap = ::CreateCompatibleBitmap(_plat->hwndDC, wide + 100, tall + 100);
		_plat->bitmapSize[0] = wide + 100;
		_plat->bitmapSize[1] = tall + 100;

		::SelectObject(_plat->hdc, _plat->bitmap);
		_plat->textureDC = ::CreateCompatibleDC(_plat->hdc);
	}

	return true;
}

void Surface::applyChanges()
{
	RECT rect;
	int x, y, wide, tall, sx, sy, swide, stall;

	// get how big the win32 window
	::GetWindowRect(_plat->hwnd, &rect);
	sx = rect.left;
	sy = rect.top;
	swide = rect.right-rect.left;
	stall = rect.bottom-rect.top;

	// how big is the embedded Panel
	getPanel()->getBounds(x, y, wide, tall);

	// if they are not the same, then adjust the win32 window so it is
	if ((x != sx) || (y != sy) || (wide != swide) || (tall != stall))
	{
		::SetWindowPos(_plat->hwnd, null, x, y, wide, tall, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
	}

	// check to see if the win32 window is visible
	if (::GetWindowLong(_plat->hwnd, GWL_STYLE) & WS_VISIBLE)
	{
		//check to see if embedded Panel is not visible, if so then hide the win32 window
		if (getPanel()->isVisible())
		{
			::ShowWindow(_plat->hwnd, SW_HIDE);
		}
	}
	else // win32 window is hidden
	{
		//check to see if embedded Panel is visible, if so then show the win32 window
		if (getPanel()->isVisible())
		{
			::ShowWindow(_plat->hwnd, SW_SHOWNA);
		}
	}

	//if the win32 window changed size and is visible, then the context needs to be recreated
	if (((wide != swide) || (tall != stall)) && getPanel()->isVisible())
	{
		recreateContext();
	}
}

void Surface::swapBuffers()
{
	int wide,tall;
	getPanel()->getSize(wide,tall);

	// reset origin and clipping then blit
	::SetRectRgn(_plat->clipRgn, 0, 0, wide, tall);
	::SelectObject(_plat->hdc, _plat->clipRgn);
	::SetViewportOrgEx(_plat->hdc, 0, 0, NULL);
	::BitBlt(_plat->hwndDC, 0, 0, wide, tall, _plat->hdc, 0, 0, SRCCOPY);
}

void Surface::drawSetColor(int r,int g,int b,int a)
{
	SetBkColor(_plat->hdc,RGB(r,g,b));
}

void Surface::drawFilledRect(int x0,int y0,int x1,int y1)
{
	// trick to draw filled rectangles using current background color
	RECT rect = { x0, y0, x1, y1};
	BOOL res = ExtTextOut(_plat->hdc, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
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
	SetTextColor(_plat->hdc,RGB(r,g,b));
}

void Surface::drawPrintText(const char* text,int textLen)
{
	assert(text);
	if (!text)
		return;

	if (textLen < 1)
		return;

	ExtTextOut(_plat->hdc, 0, 0, 0, NULL, text, textLen, NULL);
}

int Surface::createNewTextureID(void)
{
	//!! hack, arbitrary base
	static int staticBindIndex = 2700;
	return staticBindIndex++;
}

HBITMAP staticCreateBitmapHandle(int wide, int tall, HDC hdc, int bpp, void **dib)
{
	BITMAPINFOHEADER bitmapInfoHeader;
	memset(&bitmapInfoHeader, 0, sizeof(bitmapInfoHeader));
	bitmapInfoHeader.biSize = sizeof(bitmapInfoHeader);
	bitmapInfoHeader.biWidth = wide;
	bitmapInfoHeader.biHeight = -tall;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = bpp;
	bitmapInfoHeader.biCompression = BI_RGB;

	return ::CreateDIBSection(hdc, (BITMAPINFO*)&bitmapInfoHeader, DIB_RGB_COLORS, dib, null, 0);
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

	if (texture->_bitmap)
	{
		::DeleteObject(texture->_bitmap);
	}

	{
		// no texture or forced  load the new texture
		texture->_wide = wide;
		texture->_tall = tall;
		texture->_bitmap = staticCreateBitmapHandle(texture->_wide, 
			texture->_tall,	_plat->hdc, 32, &texture->_dib );

		// copy over the texture data
		memcpy(texture->_dib,rgba,wide*tall*4);

	}
}

void Surface::drawSetTexture(int id)
{
	staticTextureCurrent = staticGetTextureById(id);
}

void Surface::drawTexturedRect(int x0,int y0,int x1,int y1)
{
	if (staticTextureCurrent == null)
	{
		return;
	}

	if (_plat->textureDC == null)
	{
		return;
	}

	HBITMAP bitmap = staticTextureCurrent->_bitmap;
	int wide = staticTextureCurrent->_wide;
	int tall = staticTextureCurrent->_tall;

	::SelectObject(_plat->textureDC, bitmap);
	::StretchBlt(_plat->hdc,x0,y0,x1-x0,y1-y0,_plat->textureDC,0,0,wide,tall,SRCCOPY);
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

	if ( getPanel() == panel )
	{
		// this panel has it's own window, so use screen space
		::SetViewportOrgEx(_plat->hdc,0+inset[0],0+inset[1],null);
	}
	else
	{
		// child window, so set win32 up so all subsequent drawing calls are done in local space
		::SetViewportOrgEx(_plat->hdc,(absPanel[0]+inset[0])-absThis[0],(absPanel[1]+inset[1])-absThis[1],null);
	}

	// setup clipping
	// get and translate clipRect into surface space, then factor in inset
	int x0 = clipRect[0] - absThis[0];
	int y0 = clipRect[1] - absThis[1];
	int x1 = clipRect[2] - absThis[0];
	int y1 = clipRect[3] - absThis[1];

	//set the rect and select to make it current
	::SetRectRgn(_plat->clipRgn,x0,y0,x1,y1);
	::SelectObject(_plat->hdc, _plat->clipRgn);
}

void Surface::popMakeCurrent(Panel* panel)
{
}

void Surface::enableMouseCapture(bool state)
{
	if (state)
	{
		HWND wnd = ::SetCapture(_plat->hwnd);
	}
	else
	{
		::ReleaseCapture();
	}
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
				staticCurrentCursor = staticDefaultCursor[cursor->getDefaultCursor()];
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
		staticCurrentCursor = NULL;
		_emulatedCursor->setImage(null);
	}

	::SetCursor(staticCurrentCursor);
}

void Surface::invalidate(Panel *panel)
{
	InvalidateRect(_plat->hwnd, NULL, false);
}

void Surface::drawSetTextFont(Font* font)
{
	assert(font);
	if (!font)
	{
		return;
	}

	font->getPlat()->drawSetTextFont(_plat);
}

void Surface::setTitle(const char* title)
{
	SetWindowTextA(_plat->hwnd, title);
}

bool Surface::hasFocus()
{
	return GetFocus() == _plat->hwnd;
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
	for (int i = 0; i < _modeInfoDar.getCount(); i++)
	{
		int modewide, modetall, modebpp;
		sscanf(_modeInfoDar[i], "%dx%dx%d", &modewide, &modetall, &modebpp);
		if (wide == modewide && tall == modetall && bpp == modebpp)
		{
			DEVMODE dm;
			memset(&dm, 0, sizeof(dm));

			dm.dmSize		= sizeof(dm);
			dm.dmPelsWidth  = wide;
			dm.dmPelsHeight = tall;
			dm.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
			dm.dmBitsPerPel = bpp;

			if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL)
			{
				if (!_plat->isFullscreen)
				{
					getPanel()->getBounds(_plat->restoreInfo[0], _plat->restoreInfo[1], _plat->restoreInfo[2], _plat->restoreInfo[3]);
					SetWindowPos(_plat->hwnd,HWND_TOPMOST,-1,-1,-1,-1,SWP_NOMOVE|SWP_NOSIZE);
				}
				getPanel()->setBounds(0,0,wide,tall);
				applyChanges();
				_plat->isFullscreen = true;
				_plat->fullscreenInfo[0] = wide;
				_plat->fullscreenInfo[1] = tall;
				_plat->fullscreenInfo[2] = bpp;
				getPanel()->repaint();
				return true;
			}
		}
	}

	return false;
}

void Surface::setWindowedMode()
{
	if (_plat->isFullscreen)
	{
		getPanel()->setBounds(_plat->restoreInfo[0], _plat->restoreInfo[1], _plat->restoreInfo[2], _plat->restoreInfo[3]);
		ChangeDisplaySettings(NULL, 0);
		applyChanges();
		_plat->isFullscreen = false;
		getPanel()->repaint();
	}
}

void Surface::drawSetTextPos(int x,int y)
{
	MoveToEx(_plat->hdc,x,y,null);	
}

void Surface::setAsTopMost(bool state)
{
	if (state)
		SetWindowPos(_plat->hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	else
		SetWindowPos(_plat->hwnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
}

bool Surface::isWithin(int x,int y)
{
	POINT pnt={x,y};
	return _plat->hwnd == WindowFromPoint(pnt);
}
