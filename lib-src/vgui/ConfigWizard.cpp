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

#include<VGUI_ConfigWizard.h>
#include<VGUI_TreeFolder.h>
#include<VGUI_LineBorder.h>
#include<VGUI_LoweredBorder.h>
#include<VGUI_Button.h>

using namespace vgui;

ConfigWizard::ConfigWizard(int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	setBorder(new LineBorder());

	_treeFolder=new TreeFolder("DonkeyFoo");
	_treeFolder->setParent(this);
	_treeFolder->setBorder(new LoweredBorder());

	_client=new Panel(80,30,64,64);
	_client->setParent(this);
	_treeFolder->setBorder(new LineBorder());

	_okButton=new Button("Ok",80,80,60,20);
	_okButton->setParent(this);

	_cancelButton=new Button("Cancel",120,80);
	_cancelButton->setParent(this);

	_applyButton=new Button("Apply",160,80);
	_applyButton->setParent(this);

	_helpButton=new Button("Help",200,80);
	_helpButton->setParent(this);
}

Panel* ConfigWizard::getClient()
{
	return _client;
}

TreeFolder* ConfigWizard::getFolder()
{
	return _treeFolder;
}

void ConfigWizard::setSize(int wide,int tall)
{
	setSize(wide,tall);
	getPaintSize(wide,tall);

	_treeFolder->setBounds(10,10,160,tall-60);
	_client->setBounds(180,10,wide-190,tall-60);
	_helpButton->setPos(wide-80,tall-25);
	_applyButton->setPos(wide-150,tall-25);
	_cancelButton->setPos(wide-220,tall-25);
	_okButton->setPos(wide-290,tall-25);
}
