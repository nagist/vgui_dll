//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "VGUI.h"

static void*(*staticMalloc)(size_t size)=malloc;
static void(*staticFree)(void* memblock)=free;

void *operator new(size_t size)
{
	return staticMalloc(size);
}

void operator delete(void* memblock)
{
	if (!memblock)
		return;

	staticFree(memblock);
}

void *operator new [] (size_t size)
{
	return staticMalloc(size);
}

void operator delete [] (void *pMem)
{
	staticFree(pMem);
}

void vgui_setMalloc(void *(*theMalloc)(size_t size) )
{
	if(!theMalloc)
	{
		theMalloc=malloc;
	}
	staticMalloc=theMalloc;
}

void vgui_setFree(void (*theFree)(void* memblock))
{
	if(!theFree)
	{
		theFree=free;
	}
	staticFree=theFree;
}

namespace vgui
{
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
	char    buf[2048];
	va_list argList;

	va_start(argList,format);
	int ret=vsprintf(buf,format,argList);
	va_end(argList);

	printf("%s",buf);
	return ret;
}
}
