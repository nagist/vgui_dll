
#
# vgui_dll Makefile for x86 Linux
#
#

DLLNAME=vgui

CXX?=g++

SRCDIR=../../../../..
VGUIDIR=../../..
VGUISRCDIR=$(VGUIDIR)/src
VGUIINCDIR=$(VGUIDIR)/include
UTLSRCDIR=$(VGUIDIR)/miniutl
UTLINCDIR=$(UTLSRCDIR)
PUBLICDIR=$(SRCDIR)/public

OBJDIR=./obj
LIBDIR=$(VGUIDIR)/lib

BASE_CFLAGS=-DNDEBUG -Dstricmp=strcasecmp -D_vsnprintf=vsnprintf

CFLAGS=$(BASE_CFLAGS) -w -O1

ifneq ($(64BIT), 1)
	CFLAGS += -m32
endif

SYS = $(shell $(CXX) -dumpmachine)
ifneq (, $(findstring darwin, $(SYS)))
PLATFORM=apple
SHLIBEXT=dylib
else
PLATFORM=posix
SHLIBEXT=so
endif

PLATFORMINCDIR=$(VGUISRCDIR)/platform/$(PLATFORM)
POSIXINCDIR=$(VGUISRCDIR)/platform/posix

SHLIBCFLAGS=-fPIC
SHLIBLDFLAGS=-shared

INCLUDEDIRS=-I. -I$(VGUIINCDIR) -I$(PUBLICDIR) -I$(UTLINCDIR) -I$(PLATFORMINCDIR) -I$(POSIXINCDIR)

LDFLAGS=-Wl,--no-undefined

DO_CXX=$(CXX) $(CFLAGS) $(SHLIBCFLAGS) $(INCLUDEDIRS) -o $@ -c $<

#############################################################################
# SETUP AND BUILD
#############################################################################

$(OBJDIR)/%.o: $(VGUISRCDIR)/%.cpp
	$(DO_CXX)

$(OBJDIR)/%.o: $(UTLSRCDIR)/utlmemory.cpp
	$(DO_CXX)

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
	$(OBJDIR)/platform/posix/App.o \
	$(OBJDIR)/platform/posix/Cursor.o \
	$(OBJDIR)/platform/posix/fileimage.o \
	$(OBJDIR)/platform/$(PLATFORM)/Font.o \
	$(OBJDIR)/platform/posix/Surface.o \
	$(OBJDIR)/platform/posix/vfontdata.o \
	$(OBJDIR)/platform/posix/vgui.o \
	$(OBJDIR)/miniutl/utlmemory.o

$(LIBDIR)/$(DLLNAME).$(SHLIBEXT) : neat $(OBJ)
	$(CXX) $(CFLAGS) $(SHLIBLDFLAGS) $(LDFLAGS) -o $@ $(OBJ)

neat:
	-mkdir -p $(OBJDIR)
	-mkdir -p $(OBJDIR)/vgui
	-mkdir -p $(OBJDIR)/miniutl
	-mkdir -p $(OBJDIR)/platform/posix
	-mkdir -p $(OBJDIR)/platform/$(PLATFORM)
	-mkdir -p $(LIBDIR)
clean:
	-rm -rf $(OBJDIR)
	-rm -f $(LIBDIR)/$(DLLNAME).$(SHLIBEXT)

