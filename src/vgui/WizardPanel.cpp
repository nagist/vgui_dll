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
#include<VGUI_WizardPanel.h>
#include<VGUI_ActionSignal.h>
#include<VGUI_App.h>

using namespace vgui;

namespace
{
class FooBackHandler : public ActionSignal
{
private:
	WizardPanel* _wizardPanel;
public:
	FooBackHandler(WizardPanel* wizardPanel)
	{
		_wizardPanel=wizardPanel;
	}
public:
	virtual void actionPerformed(Panel* panel)
	{
		_wizardPanel->doBack();
	}
};

class FooNextHandler : public ActionSignal
{
private:
	WizardPanel* _wizardPanel;
public:
	FooNextHandler(WizardPanel* wizardPanel)
	{
		_wizardPanel=wizardPanel;
	}
public:
	virtual void actionPerformed(Panel* panel)
	{
		_wizardPanel->doNext();
	}
};

void fooGetText(const char* src,char* dst,int dstLen)
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
}

void WizardPanel::WizardPage::init()
{
	_backWizardPage=null;
	_nextWizardPage=null;
	_backButtonEnabled=false;
	_nextButtonEnabled=false;
	_finishedButtonEnabled=false;
	_cancelButtonEnabled=true;
	_backButtonText=null;
	_nextButtonText=null;
	_finishedButtonText=null;
	_cancelButtonText=null;
	_wantedFocus=null;
	_title=null;
	_backButtonVisible=true;
	_nextButtonVisible=true;
	_finishedButtonVisible=true;
	_cancelButtonVisible=true;

	setTitle("Untitled");
	setBackButtonText("<< Back");
	setNextButtonText("Next >>");
	setFinishedButtonText("Finished");
	setCancelButtonText("Cancel");
}

WizardPanel::WizardPage::WizardPage() : Panel(0,0,64,64)
{
	init();
}

WizardPanel::WizardPage::WizardPage(int wide,int tall) : Panel(0,0,wide,tall)
{
	init();
}

void WizardPanel::WizardPage::setBackWizardPage(WizardPage* backWizardPage)
{
	_backWizardPage=backWizardPage;
	setBackButtonEnabled(backWizardPage!=null);
}

void WizardPanel::WizardPage::setNextWizardPage(WizardPage* nextWizardPage)
{
	_nextWizardPage=nextWizardPage;
	setNextButtonEnabled(nextWizardPage!=null);
}

WizardPanel::WizardPage* WizardPanel::WizardPage::getBackWizardPage()
{
	return _backWizardPage;
}

WizardPanel::WizardPage* WizardPanel::WizardPage::getNextWizardPage()
{
	return _nextWizardPage;
}

bool WizardPanel::WizardPage::isBackButtonEnabled()
{
	return _backButtonEnabled;
}

bool WizardPanel::WizardPage::isNextButtonEnabled()
{
	return _nextButtonEnabled;
}

bool WizardPanel::WizardPage::isFinishedButtonEnabled()
{
	return _finishedButtonEnabled;
}

bool WizardPanel::WizardPage::isCancelButtonEnabled()
{
	return _cancelButtonEnabled;
}

void WizardPanel::WizardPage::setBackButtonEnabled(bool state)
{
	_backButtonEnabled=state;
}

void WizardPanel::WizardPage::setNextButtonEnabled(bool state)
{
	_nextButtonEnabled=state;
}

void WizardPanel::WizardPage::setFinishedButtonEnabled(bool state)
{
	_finishedButtonEnabled=state;
}

void WizardPanel::WizardPage::setCancelButtonEnabled(bool state)
{
	_cancelButtonEnabled=state;
}

bool WizardPanel::WizardPage::isBackButtonVisible()
{
	return _backButtonVisible;
}

bool WizardPanel::WizardPage::isNextButtonVisible()
{
	return _nextButtonVisible;
}

bool WizardPanel::WizardPage::isFinishedButtonVisible()
{
	return _finishedButtonVisible;
}

bool WizardPanel::WizardPage::isCancelButtonVisible()
{
	return _cancelButtonVisible;
}

void WizardPanel::WizardPage::setBackButtonVisible(bool state)
{
	_backButtonVisible=state;
}

void WizardPanel::WizardPage::setNextButtonVisible(bool state)
{
	_nextButtonVisible=state;
}

void WizardPanel::WizardPage::setFinishedButtonVisible(bool state)
{
	_finishedButtonVisible=state;
}

void WizardPanel::WizardPage::setCancelButtonVisible(bool state)
{
	_cancelButtonVisible=state;
}

void WizardPanel::WizardPage::getBackButtonText(char* text,int textLen)
{
	fooGetText(_backButtonText,text,textLen);
}

void WizardPanel::WizardPage::getNextButtonText(char* text,int textLen)
{
	fooGetText(_nextButtonText,text,textLen);
}

void WizardPanel::WizardPage::getFinishedButtonText(char* text,int textLen)
{
	fooGetText(_finishedButtonText,text,textLen);
}

void WizardPanel::WizardPage::getCancelButtonText(char* text,int textLen)
{
	fooGetText(_cancelButtonText,text,textLen);
}

void WizardPanel::WizardPage::setBackButtonText(const char* text)
{
	delete[] _backButtonText;
	_backButtonText=vgui_strdup(text);
}

void WizardPanel::WizardPage::setNextButtonText(const char* text)
{
	delete[] _nextButtonText;
	_nextButtonText=vgui_strdup(text);
}

void WizardPanel::WizardPage::setFinishedButtonText(const char* text)
{
	delete[] _finishedButtonText;
	_finishedButtonText=vgui_strdup(text);
}

void WizardPanel::WizardPage::setCancelButtonText(const char* text)
{
	delete[] _cancelButtonText;
	_cancelButtonText=vgui_strdup(text);
}

void WizardPanel::WizardPage::addSwitchingToBackPageSignal(ActionSignal* s)
{
	_switchingToBackPageSignalDar.putElement(s);
}

void WizardPanel::WizardPage::addSwitchingToNextPageSignal(ActionSignal* s)
{
	_switchingToNextPageSignalDar.putElement(s);
}

void WizardPanel::WizardPage::fireSwitchingToBackPageSignals()
{
	for(int i=0;i<_switchingToBackPageSignalDar.getCount();i++)
	{
		_switchingToBackPageSignalDar[i]->actionPerformed(this);
	}
}

void WizardPanel::WizardPage::fireSwitchingToNextPageSignals()
{
	for(int i=0;i<_switchingToBackPageSignalDar.getCount();i++)
	{
		_switchingToBackPageSignalDar[i]->actionPerformed(this);
	}
}

void WizardPanel::WizardPage::setTitle(const char* title)
{
	delete[] _title;
	_title=vgui_strdup(title);
}

void WizardPanel::WizardPage::getTitle(char* buf,int bufLen)
{
	vgui_strcpy(buf,bufLen,_title);
}

void WizardPanel::WizardPage::setWantedFocus(Panel* panel)
{
	_wantedFocus=panel;
}

Panel* WizardPanel::WizardPage::getWantedFocus()
{
	return _wantedFocus;
}

WizardPanel::WizardPanel(int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	_currentWizardPage=null;

	_backButton=new Button("back",20,100);
	_backButton->setParent(this);
	_backButton->addActionSignal(new FooBackHandler(this));

	_nextButton=new Button("next",80,100);
	_nextButton->setParent(this);
	_nextButton->addActionSignal(new FooNextHandler(this));

	_nextButton=new Button("finished",120,100);
	_nextButton->setParent(this);

	_nextButton=new Button("cancel",180,100);
	_nextButton->setParent(this);
}

void WizardPanel::performLayout()
{
	int wide,tall;
	getPaintSize(wide,tall);

	_backButton->setVisible(false);
	_nextButton->setVisible(false);
	_finishedButton->setVisible(false);
	_cancelButton->setVisible(false);

	if(_currentWizardPage!=null)
	{
		int bTall=_backButton->getTall();
		_currentWizardPage->setBounds(2,2,wide-4,tall-bTall-8);

		char buf[256];
		int gap=2;
		int x=wide-(gap*2);
		int y=tall-bTall-gap;

		_currentWizardPage->getCancelButtonText(buf,sizeof(buf));
		_cancelButton->setText(buf);
		_cancelButton->setEnabled(_currentWizardPage->isCancelButtonEnabled());
		_cancelButton->setVisible(_currentWizardPage->isCancelButtonVisible());
		_cancelButton->setPos(x-_cancelButton->getWide(),y);
		if(_currentWizardPage->isCancelButtonVisible())
		{
			x-=_cancelButton->getWide()+(gap*2);
		}

		_currentWizardPage->getFinishedButtonText(buf,sizeof(buf));
		_finishedButton->setText(buf);
		_finishedButton->setEnabled(_currentWizardPage->isFinishedButtonEnabled());
		_finishedButton->setVisible(_currentWizardPage->isFinishedButtonVisible());
		_finishedButton->setPos(x-_finishedButton->getWide(),y);
		if(_currentWizardPage->isFinishedButtonVisible())
		{
			x-=_finishedButton->getWide()+(gap*2);
		}

		_currentWizardPage->getNextButtonText(buf,sizeof(buf));
		_nextButton->setText(buf);
		_nextButton->setEnabled(_currentWizardPage->isNextButtonEnabled());
		_nextButton->setVisible(_currentWizardPage->isNextButtonVisible());
		_nextButton->setPos(x-_nextButton->getWide(),y);
		if(_currentWizardPage->isNextButtonVisible())
		{
			x-=_nextButton->getWide()+(gap*2);
		}

		_currentWizardPage->getBackButtonText(buf,sizeof(buf));
		_backButton->setText(buf);
		_backButton->setEnabled(_currentWizardPage->isBackButtonEnabled());
		_backButton->setVisible(_currentWizardPage->isBackButtonVisible());
		_backButton->setPos(x-_backButton->getWide(),y);
		if(_currentWizardPage->isBackButtonVisible())
		{
			x-=_backButton->getWide()+(gap*2);
		}
	}
}

void WizardPanel::setCurrentWizardPage(WizardPage* currentWizardPage)
{
	if(_currentWizardPage!=null)
	{
		removeChild(_currentWizardPage);
	}
	_currentWizardPage=currentWizardPage;

	if(_currentWizardPage!=null)
	{
		_currentWizardPage->setParent(this);
		getApp()->requestFocus(_currentWizardPage->getWantedFocus());
	}

	firePageChangedActionSignal();
	invalidateLayout(false);
}

void WizardPanel::addFinishedActionSignal(ActionSignal* s)
{
	_finishedButton->addActionSignal(s);
}

void WizardPanel::addCancelledActionSignal(ActionSignal* s)
{
	_cancelButton->addActionSignal(s);
}

void WizardPanel::addPageChangedActionSignal(ActionSignal* s)
{
	_pageChangedActionSignalDar.putElement(s);
}

void WizardPanel::fireFinishedActionSignal()
{
	_finishedButton->fireActionSignal();
}

void WizardPanel::fireCancelledActionSignal()
{
	_cancelButton->fireActionSignal();
}

void WizardPanel::firePageChangedActionSignal()
{
	for(int i=0;i<_pageChangedActionSignalDar.getCount();i++)
	{
		_pageChangedActionSignalDar[i]->actionPerformed(this);
	}
}

void WizardPanel::doBack()
{
	if(_currentWizardPage!=null)
	{
		_currentWizardPage->fireSwitchingToBackPageSignals();
		setCurrentWizardPage(_currentWizardPage->getBackWizardPage());
	}
}

void WizardPanel::doNext()
{
	if(_currentWizardPage!=null)
	{
		_currentWizardPage->fireSwitchingToNextPageSignals();
		setCurrentWizardPage(_currentWizardPage->getNextWizardPage());
	}
}

void WizardPanel::getCurrentWizardPageTitle(char* buf,int bufLen)
{
	_currentWizardPage->getTitle(buf,bufLen);
}

WizardPanel::WizardPage* WizardPanel::getCurrentWizardPage()
{
	return _currentWizardPage;
}
