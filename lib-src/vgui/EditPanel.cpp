//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_EditPanel.h"

using namespace vgui;

EditPanel::EditPanel(int x,int y,int wide,int tall)
{
}

void EditPanel::doCursorUp()
{
}

void EditPanel::doCursorDown()
{
}

void EditPanel::doCursorLeft()
{
}

void EditPanel::doCursorRight()
{
}

void EditPanel::doCursorToStartOfLine()
{
}

void EditPanel::doCursorToEndOfLine()
{
}

void EditPanel::doCursorInsertChar(char ch)
{
}

void EditPanel::doCursorBackspace()
{
}

void EditPanel::doCursorNewLine()
{
}

void EditPanel::doCursorDelete()
{
}

void EditPanel::doCursorPrintf(char* format,...)
{
}

int EditPanel::getLineCount()
{
	return 0;
}

int EditPanel::getVisibleLineCount()
{
	return 0;
}

void EditPanel::setCursorBlink(bool state)
{
}

void EditPanel::setFont(Font* font)
{
}

void EditPanel::getText(int lineIndex, int offset,char* buf,int bufLen)
{
}

void EditPanel::getCursorBlink(bool& blink,int& nextBlinkTime)
{
}

void EditPanel::paintBackground()
{
}

void EditPanel::paint()
{
}

void EditPanel::addLine()
{
}

Dar<char>* EditPanel::getLine(int lineIndex)
{
	return null;
}

void EditPanel::setChar(Dar<char>* lineDar,int x,char ch,char fill)
{
}

void EditPanel::setChar(Dar<char>* lineDar,int x,char ch)
{
}

void EditPanel::shiftLineLeft(Dar<char>* lineDar,int x,int count)
{
}

void EditPanel::shiftLineRight(Dar<char>* lineDar,int x,int count)
{
}

int EditPanel::spatialCharOffsetBetweenTwoLines(Dar<char>* srcDar,Dar<char>* dstDar,int x)
{
	return 0;
}
