# Microsoft Developer Studio Project File - Name="vgui_dll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=vgui_dll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vgui_dll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vgui_dll.mak" CFG="vgui_dll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vgui_dll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vgui_dll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vgui_dll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VGUI_DLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /Zi /O2 /I "..\..\..\include" /I "..\..\..\..\public" /I "..\..\..\..\common" /I "." /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /map /debug /machine:I386 /out:"Release/vgui.dll"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "vgui_dll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VGUI_DLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /W3 /Gm /GR /ZI /Od /I "..\..\..\include" /I "..\..\..\..\public" /I "..\..\..\..\common" /I "." /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"LIBCMTD" /out:"Debug/vgui.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "vgui_dll - Win32 Release"
# Name "vgui_dll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "win32"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\src\win32\App.cpp"

!IF  "$(CFG)" == "vgui_dll - Win32 Release"

# PROP Intermediate_Dir "Release\win32"

!ELSEIF  "$(CFG)" == "vgui_dll - Win32 Debug"

# PROP Intermediate_Dir "Debug\win32"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\posix\Cursor.cpp"

!IF  "$(CFG)" == "vgui_dll - Win32 Release"

# PROP Intermediate_Dir "Release\win32"

!ELSEIF  "$(CFG)" == "vgui_dll - Win32 Debug"

# PROP Intermediate_Dir "Debug\win32"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\posix\fileimage.cpp"

!IF  "$(CFG)" == "vgui_dll - Win32 Release"

# PROP Intermediate_Dir "Release\win32"

!ELSEIF  "$(CFG)" == "vgui_dll - Win32 Debug"

# PROP Intermediate_Dir "Debug\win32"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\posix\fileimage.h"

!IF  "$(CFG)" == "vgui_dll - Win32 Release"

# PROP Intermediate_Dir "Release\win32"

!ELSEIF  "$(CFG)" == "vgui_dll - Win32 Debug"

# PROP Intermediate_Dir "Debug\win32"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\win32\Font.cpp"

!IF  "$(CFG)" == "vgui_dll - Win32 Release"

# PROP Intermediate_Dir "Release\win32"

!ELSEIF  "$(CFG)" == "vgui_dll - Win32 Debug"

# PROP Intermediate_Dir "Debug\win32"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\win32\Surface.cpp"

!IF  "$(CFG)" == "vgui_dll - Win32 Release"

# PROP Intermediate_Dir "Release\win32"

!ELSEIF  "$(CFG)" == "vgui_dll - Win32 Debug"

# PROP Intermediate_Dir "Debug\win32"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\posix\vfontdata.cpp"

!IF  "$(CFG)" == "vgui_dll - Win32 Release"

# PROP Intermediate_Dir "Release\win32"

!ELSEIF  "$(CFG)" == "vgui_dll - Win32 Debug"

# PROP Intermediate_Dir "Debug\win32"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\posix\vfontdata.h"

!IF  "$(CFG)" == "vgui_dll - Win32 Release"

# PROP Intermediate_Dir "Release\win32"

!ELSEIF  "$(CFG)" == "vgui_dll - Win32 Debug"

# PROP Intermediate_Dir "Debug\win32"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\posix\vgui.cpp"

!IF  "$(CFG)" == "vgui_dll - Win32 Release"

# PROP Intermediate_Dir "Release\win32"

!ELSEIF  "$(CFG)" == "vgui_dll - Win32 Debug"

# PROP Intermediate_Dir "Debug\win32"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\lib-src\win32\vgui_win32.h"

!IF  "$(CFG)" == "vgui_dll - Win32 Release"

# PROP Intermediate_Dir "Release\win32"

!ELSEIF  "$(CFG)" == "vgui_dll - Win32 Debug"

# PROP Intermediate_Dir "Debug\win32"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE="..\..\..\src\vgui\App.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Bitmap.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\BitmapTGA.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Border.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\BorderLayout.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\BorderPair.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\BuildGroup.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Button.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\ButtonGroup.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\CheckButton.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Color.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\ConfigWizard.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Cursor.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\DataInputStream.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Desktop.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\DesktopIcon.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\EditPanel.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\EtchedBorder.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\FileInputStream.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\FlowLayout.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\FocusNavGroup.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Font.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Frame.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\GridLayout.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\HeaderPanel.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Image.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\ImagePanel.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\IntLabel.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Label.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Layout.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\LineBorder.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\ListPanel.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\LoweredBorder.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Menu.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\MenuItem.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\MenuSeparator.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\MessageBox.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\MiniApp.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Panel.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\PopupMenu.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\ProgressBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\RadioButton.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\RaisedBorder.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Scheme.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\ScrollBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\ScrollPanel.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Slider.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\StackLayout.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\String.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\Surface.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\SurfaceBase.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\TablePanel.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\TabPanel.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\TaskBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\TextEntry.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\TextGrid.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\TextImage.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\TextPanel.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\ToggleButton.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\TreeFolder.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\vgui.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\vgui\WizardPanel.cpp"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\include\VGUI.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_ActionSignal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_App.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Bitmap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_BitmapTGA.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Border.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_BorderLayout.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_BorderPair.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_BuildGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Button.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_ButtonController.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_ButtonGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_ChangeSignal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_CheckButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Color.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_ComboKey.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_ConfigWizard.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Cursor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Dar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_DataInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Desktop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_DesktopIcon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_EditPanel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_EtchedBorder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_FileInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_FlowLayout.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_FocusChangeSignal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_FocusNavGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Font.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Frame.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_FrameSignal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_GridLayout.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_HeaderPanel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_ImagePanel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_InputSignal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_InputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_IntChangeSignal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_IntLabel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_KeyCode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Label.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Layout.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_LayoutInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_LineBorder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_ListPanel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_LoweredBorder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Menu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_MenuItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_MenuSeparator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_MessageBox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_MiniApp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_MouseCode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Panel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Point.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_PopupMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_ProgressBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_RadioButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_RaisedBorder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_RepaintSignal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Scheme.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_ScrollBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_ScrollPanel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Slider.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_StackLayout.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_String.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_Surface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_SurfaceBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_SurfaceGL.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_TablePanel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_TabPanel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_TaskBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_TextEntry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_TextGrid.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_TextImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_TextPanel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_TickSignal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_ToggleButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_TreeFolder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\VGUI_WizardPanel.h
# End Source File
# End Group
# End Target
# End Project
