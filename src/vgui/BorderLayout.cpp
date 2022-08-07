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
