//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_TablePanel.h"
#include "VGUI_HeaderPanel.h"
#include "VGUI_ChangeSignal.h"
#include "VGUI_InputSignal.h"
#include "VGUI_RepaintSignal.h"

using namespace vgui;

namespace vgui
{
class FooVGuiTablePanelHandler : public ChangeSignal, public InputSignal, public RepaintSignal
{
public:
	FooVGuiTablePanelHandler(TablePanel* table)
	{
		_table=table;
	}
	void valueChanged(Panel* panel)
	{
		HeaderPanel* header=null;
		if(panel)
			header=dynamic_cast<HeaderPanel*>(panel);

		int cols=_table->getColumnCount();

		for(int i=0;i<header->getSectionCount();i++)
		{
			if(i>=cols)
				break;

			int x0,x1;
			header->getSectionExtents(i,x0,x1);
			_table->setColumnExtents(i,x0,x1);
		}
	}
	void cursorMoved(int x,int y,Panel* panel)
	{
	}
	void cursorEntered(Panel* panel)
	{
	}
	void cursorExited(Panel* panel)
	{
	}
	void mousePressed(MouseCode code,Panel* panel)
	{
		_table->privateMousePressed(code,panel);
	}
	void mouseDoublePressed(MouseCode code,Panel* panel)
	{
		_table->privateMouseDoublePressed(code,panel);
	}
	void mouseReleased(MouseCode code,Panel* panel)
	{
	}
	void mouseWheeled(int delta,Panel* panel)
	{
	}
	void keyPressed(KeyCode code,Panel* panel)
	{
	}
	void keyTyped(KeyCode code,Panel* panel)
	{
		_table->privateKeyTyped(code,panel);
	}
	void keyReleased(KeyCode code,Panel* panel)
	{
	}
	void keyFocusTicked(Panel* panel)
	{
	}
	void panelRepainted(Panel* panel)
	{
		_table->repaint();
	}
private:
	TablePanel* _table;
};
}

TablePanel::TablePanel(int x,int y,int wide,int tall,int columnCount) : Panel(x,y,wide,tall)
{
	setGridSize(2,2);
	setGridVisible(false,false);
	setColumnCount(columnCount);
	setFgColor(Color(Scheme::sc_black));

	_selectedCell[0]=-1;
	_selectedCell[1]=-1;
	_fakeInputPanel=new Panel();
	_columnSelectionEnabled=false;
	_rowSelectionEnabled=true;
	_cellSelectionEnabled=true;
	_mouseOverCell[0]=0;
	_mouseOverCell[1]=0;
	_editableCell[0]=-1;
	_editableCell[1]=-1;
	_editableCellPanel=null;
	_virtualSize[0]=wide;
	_virtualSize[1]=tall;
	_cellEditingEnabled=true;

	addInputSignal(new FooVGuiTablePanelHandler(this));
}

void TablePanel::setCellEditingEnabled(bool state)
{
	_cellEditingEnabled=state;
}

void TablePanel::setColumnCount(int columnCount)
{
	_columnDar.ensureCapacity(columnCount);
	_columnDar.setCount(columnCount);
}

void TablePanel::setGridVisible(bool horizontal,bool vertical)
{
	_gridVisible[0]=horizontal;
	_gridVisible[1]=horizontal; // vertical?
}

void TablePanel::setGridSize(int gridWide,int gridTall)
{
	_gridWide=gridWide;
	_gridTall=gridTall;
}

int TablePanel::getColumnCount()
{
	return _columnDar.getCount();
}

void TablePanel::setColumnExtents(int column,int x0,int x1)
{
	_columnDar.setElementAt(x1+(x0<<12),column);
	repaint();
}

void TablePanel::setSelectedCell(int column,int row)
{
	if(_selectedCell[0]!=column||_selectedCell[1]!=row)
	{
		repaint();
		stopCellEditing();
	}
	_selectedCell[0]=column;
	_selectedCell[1]=row;
}

void TablePanel::getSelectedCell(int& column,int& row)
{
	column=_selectedCell[0];
	row=_selectedCell[1];
}

void TablePanel::setHeaderPanel(HeaderPanel* header)
{
	header->addChangeSignal(new FooVGuiTablePanelHandler(this));
	header->fireChangeSignal();
	repaint();
}

void TablePanel::setColumnSelectionEnabled(bool state)
{
	_columnSelectionEnabled=state;
	repaint();
}

void TablePanel::setRowSelectionEnabled(bool state)
{
	_rowSelectionEnabled=state;
	repaint();
}

void TablePanel::setCellSectionEnabled(bool state)
{
	_cellSelectionEnabled=state;
	repaint();
}

void TablePanel::setEditableCell(int column,int row)
{
	if(_editableCell[0]!=column||_editableCell[1]!=row)
	{
		stopCellEditing();
		_editableCellPanel=startCellEditing(column,row);
		if(_editableCellPanel)
			_editableCellPanel->setParent(this);
	}
	_editableCell[0]=column;
	_editableCell[1]=row;
}

void TablePanel::stopCellEditing()
{
	if(_editableCellPanel)
	{
		_editableCellPanel->setParent(null);
		_editableCellPanel=null;
		_editableCell[0]=-1;
		_editableCell[1]=-1;
	}
}

void TablePanel::getVirtualSize(int& wide,int& tall)
{
	wide=_virtualSize[0];
	tall=_virtualSize[1];
}

void TablePanel::paint()
{
	int x0gap=(_gridWide/2)-1;
	int x1gap=_gridWide-x0gap;

	int i,wide,tall,maxX;
	getPaintSize(wide,tall);

	Color fgColor;
	getFgColor(fgColor);

	int r,g,b,a;
	fgColor.getColor(r,g,b,a);

	if(_gridVisible[1])
	{
		maxX=0;
		for(i=0;i<_columnDar.getCount();i++)
		{
			maxX=(_columnDar[i]&0xFFF);
			drawSetColor(r,g,b,a);

			int x0=maxX+x0gap;
			int x1=maxX-x1gap;
			drawFilledRect(x1,0,x0,tall);
		}
	}
	else
	{
		maxX=wide;
	}

	if(_gridVisible[0])
	{
		int y0=0;
		for(int j=0;j<getRowCount();j++)
		{
			drawSetColor(r,g,b,a);
			drawFilledRect(0,y0,maxX,y0+_gridTall);
			y0+=_gridTall+getCellTall(j);
		}
	}

	_virtualSize[0]=0;
	_virtualSize[1]=0;

	for(i=0;i<_columnDar.getCount();i++)
	{
		int x0=(_columnDar[i]>>12)&0xFFF;
		int x1=(_columnDar[i])&0xFFF;

		x0+=x0gap;
		x1-=x1gap;

		if(x1>_virtualSize[0])
		{
			_virtualSize[0]=x1;
		}

		int y0=_gridTall;
		for(int j=0;j<getRowCount();j++)
		{
			bool columnSelected=false;
			if(_columnSelectionEnabled&&(_selectedCell[0]==i))
			{
				columnSelected=true;
			}

			bool rowSelected=false;
			if(_rowSelectionEnabled&&(_selectedCell[1]==j))
			{
				rowSelected=true;
			}

			bool cellSelected=false;
			if(_cellSelectionEnabled&&(_selectedCell[0]==i)&&(_selectedCell[1]==j))
			{
				cellSelected=true;
			}

			if(_editableCell[0]==i&&_editableCell[1]==j)
			{
				if(_editableCellPanel)
				{
					_editableCellPanel->setBounds(x0,y0,x1-x0,getCellTall(j));
					_editableCellPanel->repaint();
					_editableCellPanel->solveTraverse();
				}
			}
			else
			{
				Panel* panel=getCellRenderer(i,j,columnSelected,rowSelected,cellSelected);
				if(panel)
				{
					panel->setParent(this);
					panel->setBounds(x0,y0,x1-x0,getCellTall(j));
					panel->repaint();
					panel->solveTraverse();
					panel->paintTraverse();
					panel->setParent(null);
				}
			}
			y0+=_gridTall+getCellTall(j);
			if(y0>_virtualSize[1])
			{
				_virtualSize[1]=x1;
			}
		}
	}
}

Panel* TablePanel::isWithinTraverse(int x,int y)
{
	Panel* panel=Panel::isWithinTraverse(x,y);
	if(panel!=this)
	{
		return panel;
	}

	int x0gap=(_gridWide/2)-1;
	int x1gap=_gridWide-x0gap;

	for(int i=0;i<_columnDar.getCount();i++)
	{
		int x0=(_columnDar[i]>>12)&0xFFF;
		int x1=(_columnDar[i])&0xFFF;

		x0+=x0gap;
		x1-=x1gap;

		int y0=_gridTall;
		for(int j=0;j<getRowCount();j++)
		{
			_fakeInputPanel->setParent(this);
			_fakeInputPanel->setBounds(x0,y0,x1-x0,getCellTall(j));
			_fakeInputPanel->solveTraverse();
			panel=_fakeInputPanel->isWithinTraverse(x,y);
			_fakeInputPanel->setParent(null);
			if(panel==_fakeInputPanel)
			{
				_mouseOverCell[0]=i;
				_mouseOverCell[1]=j;
				return this;
			}
			y0+=_gridTall+getCellTall(j);
		}
	}

	return this;
}

void TablePanel::privateMousePressed(MouseCode code,Panel* panel)
{
	if(!_cellEditingEnabled)
	{
		return;
	}

	setSelectedCell(_mouseOverCell[0],_mouseOverCell[1]);
	requestFocus();
}

void TablePanel::privateMouseDoublePressed(MouseCode code,Panel* panel)
{
	if(!_cellEditingEnabled)
	{
		return;
	}

	setSelectedCell(_mouseOverCell[0],_mouseOverCell[1]);

	int column,row;
	getSelectedCell(column,row);
	setEditableCell(_mouseOverCell[0],_mouseOverCell[1]);
}

void TablePanel::privateKeyTyped(KeyCode code,Panel* panel)
{
	if(!_cellEditingEnabled)
	{
		return;
	}

	int column,row;
	getSelectedCell(column,row);

	switch(code)
	{
	case KEY_UP:
		{
			row--;
			if(row<0)
			{
				row=0;
			}
			setSelectedCell(column,row);
			break;
		}
	case KEY_DOWN:
		{
			setSelectedCell(column,row+1);
			break;
		}
	case KEY_LEFT:
		{
			column--;
			if(column<0)
			{
				column=0;
			}
			setSelectedCell(column,row);
			break;
		}
	case KEY_RIGHT:
		{
			setSelectedCell(column+1,row);
			break;
		}
	case KEY_ENTER:
		{
			setEditableCell(column,row);
			break;
		}
	}
}
