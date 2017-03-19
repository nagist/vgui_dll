//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include <string.h>
#include <stdio.h>
#include "VGUI.h"
#include "VGUI_String.h"

using namespace vgui;

String::String()
{
	_text="";
}

String::String(const char* text)
{
	int count=getCount(text);
	_text=new char[count+1];
	memcpy(_text,text,count);
	_text[count]=0;
}

String::String(const String& src)
{
	_text=src._text;
}

String::~String()
{
	_text=null;
}

int String::getCount(const char* text)
{
	int count=0;
	while(text[count])
		count++;
	return count;
}

int String::getCount()
{
	return getCount(_text);
}

String String::operator+(String text)
{
	int c1=getCount();
	int c2=text.getCount();

	String* newString=new String();
	newString->_text=new char[c1+c2+1];
	memcpy(newString->_text,_text,c1);
	memcpy(newString->_text+c1,text._text,c1);
	newString->_text[c1+c2]=0;

	return String(*newString);
}

String String::operator+(const char* text)
{
	int c1=getCount();
	int c2=getCount(text);

	String* newString=new String();
	newString->_text=new char[c1+c2+1];
	memcpy(newString->_text,_text,c1);
	memcpy(newString->_text+c1,text,c1);
	newString->_text[c1+c2]=0;

	return String(*newString);
}

bool String::operator==(String text)
{
	const char* p1=_text;
	const char* p2=text._text;
	while(1)
	{
		if(*p1!=*p2)
			return false;
		if(!*p1)
			break;
		p1++;
		p2++;
	}
	return true;
}

bool String::operator==(const char* text)
{
	const char* p1=_text;
	const char* p2=text;
	while(1)
	{
		if(*p1!=*p2)
			return false;
		if(!*p1)
			break;
		p1++;
		p2++;
	}
	return true;
}

char String::operator[](int index)
{
	return _text[index];
}

const char* String::getChars()
{
	return _text;
}

void String::test()
{
#ifdef _WIN32
	printf("{\n");
	String aa("aa");
	printf("aa [%s]\n",aa);
	String bb("bb");
	printf("bb [%s]\n",bb);
	String cc("cc");
	printf("cc [%s]\n",cc);
	String dd("dd");
	printf("dd [%s]\n",dd);
	String aacc=aa+cc;
	printf("aacc [%s]\n",aacc);
	String aabb("aa");
	printf("}\n");
#endif
}
