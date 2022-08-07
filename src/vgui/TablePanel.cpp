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

#include<VGUI_TablePanel.h>
#include<VGUI_HeaderPanel.h>
#include<VGUI_ChangeSignal.h>
#include<VGUI_InputSignal.h>
#include<VGUI_RepaintSignal.h>

using namespace vgui;

namespace vgui
{
class FooVGuiTablePanelHandler : public ChangeSignal, public InputSignal, public RepaintSignal
{
private:
	TablePanel* _table;
public:
	FooVGuiTablePanelHandler(TablePanel* table)
	{
		_table=table;
	}
public:
	virtual void valueChanged(Panel* panel)
	{
		HeaderPanel* header=dynamic_cast<HeaderPanel*>(panel);

		int cols=_table->getColumnCount();

		for(int i=0;i<header->getSectionCount()&&(i<cols);i++)
		{
			int x0,x1;
			header->getSectionExtents(i,x0,x1);
			_table->setColumnExtents(i,x0,x1);
		}
	}
	virtual void cursorMoved(int x,int y,Panel* panel)
	{
	}
	virtual void cursorEntered(Panel* panel)
	{
	}
	virtual void cursorExited(Panel* panel)
	{
	}
	virtual void mousePressed(MouseCode code,Panel* panel)
	{
		_table->privateMousePressed(code,panel);
	}
	virtual void mouseDoublePressed(MouseCode code,Panel* panel)
	{
		_table->privateMouseDoublePressed(code,panel);
	}
	virtual void mouseReleased(MouseCode code,Panel* panel)
	{
	}
	virtual void mouseWheeled(int delta,Panel* panel)
	{
	}
	virtual void keyPressed(KeyCode code,Panel* panel)
	{
	}
	virtual void keyTyped(KeyCode code,Panel* panel)
	{
		_table->privateKeyTyped(code,panel);
	}
	virtual void keyReleased(KeyCode code,Panel* panel)
	{
	}
	virtual void keyFocusTicked(Panel* panel)
	{
	}
	virtual void panelRepainted(Panel* panel)
	{
		_table->repaint();
	}
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

void TablePanel::setGridSize(int wide,int tall)
{
	_gridWide=wide;
	_gridTall=tall;
}

void TablePanel::setGridVisible(bool horizontal,bool vertical)
{
	_gridVisible[0]=horizontal;
	_gridVisible[1]=horizontal; // vertical?
}

void TablePanel::setColumnCount(int columnCount)
{
	_columnDar.ensureCapacity(columnCount);
	_columnDar.setCount(columnCount);
}

int TablePanel::getColumnCount()
{
	return _columnDar.getCount();
}

void TablePanel::setColumnExtents(int column,int x0,int x1)
{
	_columnDar.setElementAt((x0<<12)+x1,column);
	repaint();
}

void TablePanel::setSelectedCell(int column,int row)
{
	if((_selectedCell[0]!=column)||(_selectedCell[1]!=row))
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
	if((_editableCell[0]!=column)||(_editableCell[1]!=row))
	{
		stopCellEditing();
		_editableCellPanel=startCellEditing(column,row);
		if(_editableCellPanel!=null)
		{
			_editableCellPanel->setParent(this);
		}
	}
	_editableCell[0]=column;
	_editableCell[1]=row;
}

void TablePanel::stopCellEditing()
{
	if(_editableCellPanel!=null)
	{
		_editableCellPanel->setParent(null);
		_editableCellPanel=null;
		_editableCell[0]=-1;
		_editableCell[1]=-1;
	}
}

void TablePanel::setHeaderPanel(HeaderPanel* header)
{
	header->addChangeSignal(new FooVGuiTablePanelHandler(this));
	header->fireChangeSignal();
	repaint();
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
			row++;
			setSelectedCell(column,row);
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
			column++;
			setSelectedCell(column,row);
			break;
		}
		case KEY_ENTER:
		{
			setEditableCell(column,row);
			break;
		}
	}
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
			int x0=maxX+x0gap;
			int x1=maxX-x1gap;
			drawSetColor(r,g,b,a);
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

			if((_editableCell[0]==i)&&(_editableCell[1]==j))
			{
				if(_editableCellPanel!=null)
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

void TablePanel::getVirtualSize(int& wide,int& tall)
{
	wide=_virtualSize[0];
	tall=_virtualSize[1];
}
