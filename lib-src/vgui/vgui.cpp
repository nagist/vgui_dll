//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include <string.h>
#include "VGUI.h"

namespace vgui
{
void vgui_setMalloc(void *(*malloc)(size_t size) )
{
}

void vgui_setFree(void (*free)(void* memblock))
{
}

void vgui_strcpy(char* dst,int dstLen,const char* src)
{
	int srcLen=strlen(src)+1;
	if(srcLen>dstLen)
	{
		srcLen=dstLen;
	}

	memcpy(dst,src,srcLen-1);
	dst[srcLen-1]=0;
}

char* vgui_strdup(const char* src)
{
	return strdup(src);
}

int vgui_printf(const char* format,...)
{
	return 0;
}

int vgui_dprintf(const char* format,...)
{
	return 0;
}

int vgui_dprintf2(const char* format,...)
{
	return 0;
}
}
