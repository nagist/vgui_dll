//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_BorderLayout.h>
#include<VGUI_LayoutInfo.h>
#include<VGUI_Panel.h>

using namespace vgui;

class BorderLayoutInfo : public LayoutInfo
{
public:
	BorderLayout::Alignment _alignment;
public:
	BorderLayoutInfo(BorderLayout::Alignment alignment)
	{
		_alignment=alignment;
	}
	virtual LayoutInfo* getThis()
	{
		return this;
	}
};

BorderLayout::BorderLayout(int inset) : Layout()
{
	_inset=inset;
}

LayoutInfo* BorderLayout::createLayoutInfo(Alignment alignment)
{
	return new BorderLayoutInfo(alignment);
}

void BorderLayout::performLayout(Panel* panel)
{
	int wide,tall;
	panel->getSize(wide,tall);

	int maxNorth=0;
	int maxSouth=0;
	int maxEast=0;
	int maxWest=0;

	int i;

	for(i=0;i<panel->getChildCount();i++)
	{
		BorderLayoutInfo* info=dynamic_cast<BorderLayoutInfo*>(panel->getChild(i)->getLayoutInfo());
		if(info!=null)
		{
			Panel* child=panel->getChild(i);

			switch(info->_alignment)
			{
				case a_north:
				{
					if(child->getTall()>maxNorth)
					{
						maxNorth=child->getTall();
					}
					break;
				}
				case a_south:
				{
					if(child->getTall()>maxSouth)
					{
						maxSouth=child->getTall();
					}
					break;
				}
				case a_west:
				{
					if(child->getWide()>maxWest)
					{
						maxWest=child->getWide();
					}
					break;
				}
				case a_east:
				{
					if(child->getTall()>maxEast) // getWide?
					{
						maxEast=child->getWide();
					}
					break;
				}
			}
		}
	}

	int x0=_inset+maxWest;
	int y0=_inset+maxNorth;
	int x1=wide-_inset-maxEast;
	int y1=tall-_inset-maxSouth;

	for(i=0;i<panel->getChildCount();i++)
	{
		BorderLayoutInfo* info=dynamic_cast<BorderLayoutInfo*>(panel->getChild(i)->getLayoutInfo());if(info==null){continue;}
		Alignment alignment=info->_alignment;

		Panel* child=panel->getChild(i);

		switch(alignment)
		{
			case a_north:
			{
				child->setBounds(0,0,wide,y0);
				break;
			}
			case a_south:
			{
				child->setBounds(0,y1,wide,tall-y1);
				break;
			}
			case a_west:
			{
				child->setBounds(0,y0,x0,y1-y0);
				break;
			}
			case a_east:
			{
				child->setBounds(x1,y0,wide-x1,y1-y0);
				break;
			}
			case a_center:
			{
				child->setBounds(x0,y0,x1-x0,y1-y0);
				break;
			}
		}
	}
}
