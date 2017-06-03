//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<string.h>
#include<VGUI_MiniApp.h>

using namespace vgui;

MiniApp::MiniApp()
{
	_name=null;
}

void MiniApp::getName(char* buf,int bufLen)
{
	if(buf==null)
	{
		return;
	}

	int len=strlen(_name)+1;
	if(len>bufLen)
	{
		len=bufLen;
	}

	memcpy(buf,_name,len-1);
	buf[len-1]=0;
}

void MiniApp::setName(const char* name)
{
	_name=strdup(_name);
}
