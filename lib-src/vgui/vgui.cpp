//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<assert.h>
#if defined( OSX )
#include<malloc/malloc.h>
#else
#include<malloc.h>
#endif
#include<string.h>
#include<stdio.h>
#include<stdarg.h>
#include<VGUI.h>

static void*(*staticMalloc)(size_t size)=malloc;
static void(*staticFree)(void* memblock)=free;

void *operator new(size_t size)
{
	return staticMalloc(size);
}

void operator delete(void* memblock)
{
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

void vgui_setMalloc(void *(*theMalloc)(size_t size))
{
	if(theMalloc==null)
	{
		theMalloc=malloc;
	}

	staticMalloc=theMalloc;
}

void vgui_setFree(void (*theFree)(void* memblock))
{
	if(theFree==null)
	{
		theFree=free;
	}

	staticFree=theFree;
}

namespace vgui
{
void vgui_strcpy(char* dst,int dstLen,const char* src)
{
	assert(dst!=null);
	assert(dstLen>=0);
	assert(src!=null);

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
	assert(src!=null);

	int len=strlen(src)+1;
	char* dst=new char[len];
	memcpy(dst,src,len-1);
	dst[len-1]=0;
	return dst;
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
