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
