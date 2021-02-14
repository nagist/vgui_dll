
#
# vgui_dll Makefile for x86 Linux
#
#

DLLNAME=vgui

CC=gcc

SRCDIR=../../../../..
VGUIDIR=../../..
VGUISRCDIR=$(VGUIDIR)/lib-src
VGUIINCDIR=$(VGUIDIR)/include
PUBLICDIR=$(SRCDIR)/public

OBJDIR=./obj
BINDIR=./bin

BASE_CFLAGS=-DNDEBUG -D_LINUX -DLINUX -Dstricmp=strcasecmp -D_vsnprintf=vsnprintf

CFLAGS=$(BASE_CFLAGS) -w -O1

ifneq ($(64BIT), 1)
    CFLAGS += -m32
endif

INCLUDEDIRS=-I. -I$(VGUIINCDIR) -I$(PUBLICDIR)

LDFLAGS=-Wl,--no-undefined

SHLIBEXT=so
SHLIBCFLAGS=-fPIC
SHLIBLDFLAGS=-shared

DO_CC=$(CC) $(CFLAGS) $(SHLIBCFLAGS) $(INCLUDEDIRS) -o $@ -c $<

#############################################################################
# SETUP AND BUILD
#############################################################################

$(OBJDIR)/%.o: $(VGUISRCDIR)/%.cpp
	$(DO_CC)

OBJ = \
	$(OBJDIR)/vgui/App.o \
	$(OBJDIR)/vgui/Bitmap.o \
	$(OBJDIR)/vgui/BitmapTGA.o \
	$(OBJDIR)/vgui/Border.o \
	$(OBJDIR)/vgui/BorderLayout.o \
	$(OBJDIR)/vgui/BorderPair.o \
	$(OBJDIR)/vgui/BuildGroup.o \
	$(OBJDIR)/vgui/Button.o \
	$(OBJDIR)/vgui/ButtonGroup.o \
	$(OBJDIR)/vgui/CheckButton.o \
	$(OBJDIR)/vgui/Color.o \
	$(OBJDIR)/vgui/ConfigWizard.o \
	$(OBJDIR)/vgui/Cursor.o \
	$(OBJDIR)/vgui/DataInputStream.o \
	$(OBJDIR)/vgui/Desktop.o \
	$(OBJDIR)/vgui/DesktopIcon.o \
	$(OBJDIR)/vgui/EditPanel.o \
	$(OBJDIR)/vgui/EtchedBorder.o \
	$(OBJDIR)/vgui/FileInputStream.o \
	$(OBJDIR)/vgui/FlowLayout.o \
	$(OBJDIR)/vgui/FocusNavGroup.o \
	$(OBJDIR)/vgui/Font.o \
	$(OBJDIR)/vgui/Frame.o \
	$(OBJDIR)/vgui/GridLayout.o \
	$(OBJDIR)/vgui/HeaderPanel.o \
	$(OBJDIR)/vgui/Image.o \
	$(OBJDIR)/vgui/ImagePanel.o \
	$(OBJDIR)/vgui/IntLabel.o \
	$(OBJDIR)/vgui/Label.o \
	$(OBJDIR)/vgui/Layout.o \
	$(OBJDIR)/vgui/LineBorder.o \
	$(OBJDIR)/vgui/ListPanel.o \
	$(OBJDIR)/vgui/LoweredBorder.o \
	$(OBJDIR)/vgui/Menu.o \
	$(OBJDIR)/vgui/MenuItem.o \
	$(OBJDIR)/vgui/MenuSeparator.o \
	$(OBJDIR)/vgui/MessageBox.o \
	$(OBJDIR)/vgui/MiniApp.o \
	$(OBJDIR)/vgui/Panel.o \
	$(OBJDIR)/vgui/PopupMenu.o \
	$(OBJDIR)/vgui/ProgressBar.o \
	$(OBJDIR)/vgui/RadioButton.o \
	$(OBJDIR)/vgui/RaisedBorder.o \
	$(OBJDIR)/vgui/Scheme.o \
	$(OBJDIR)/vgui/ScrollBar.o \
	$(OBJDIR)/vgui/ScrollPanel.o \
	$(OBJDIR)/vgui/Slider.o \
	$(OBJDIR)/vgui/StackLayout.o \
	$(OBJDIR)/vgui/String.o \
	$(OBJDIR)/vgui/Surface.o \
	$(OBJDIR)/vgui/SurfaceBase.o \
	$(OBJDIR)/vgui/TablePanel.o \
	$(OBJDIR)/vgui/TabPanel.o \
	$(OBJDIR)/vgui/TaskBar.o \
	$(OBJDIR)/vgui/TextEntry.o \
	$(OBJDIR)/vgui/TextGrid.o \
	$(OBJDIR)/vgui/TextImage.o \
	$(OBJDIR)/vgui/TextPanel.o \
	$(OBJDIR)/vgui/ToggleButton.o \
	$(OBJDIR)/vgui/TreeFolder.o \
	$(OBJDIR)/vgui/vgui.o \
	$(OBJDIR)/vgui/WizardPanel.o \
	$(OBJDIR)/linux/App.o \
	$(OBJDIR)/linux/Cursor.o \
	$(OBJDIR)/linux/fileimage.o \
	$(OBJDIR)/linux/Font.o \
	$(OBJDIR)/linux/Surface.o \
	$(OBJDIR)/linux/vfontdata.o \
	$(OBJDIR)/linux/vgui.o

$(BINDIR)/$(DLLNAME).$(SHLIBEXT) : neat $(OBJ)
	$(CXX) $(CFLAGS) $(SHLIBLDFLAGS) $(LDFLAGS) -o $@ $(OBJ)

neat:
	-mkdir -p $(OBJDIR)
	-mkdir -p $(OBJDIR)/vgui
	-mkdir -p $(OBJDIR)/linux
	-mkdir -p $(BINDIR)
clean:
	-rm -rf $(OBJDIR)
	-rm -rf $(BINDIR)

