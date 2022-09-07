# Microsoft Developer Studio Project File - Name="ReportCreator" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ReportCreator - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ReportCreator.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ReportCreator.mak" CFG="ReportCreator - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ReportCreator - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ReportCreator - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ReportCreator - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Z<none>
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41d /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ReportCreator - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41d /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ReportCreator - Win32 Release"
# Name "ReportCreator - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "ReportEditor"

# PROP Default_Filter ""
# Begin Group "DiagramEditor"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramClipboardHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramClipboardHandler.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramEditor.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramEntity.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramEntityContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramEntityContainer.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramLine.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramLine.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramMenu.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramPropertyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\DiagramPropertyDlg.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\GroupFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\GroupFactory.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\Tokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\Tokenizer.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\UndoItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\DiagramEditor\UndoItem.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReportEditor\ColorStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ColorStatic.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\Column.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\Column.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ColumnContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ColumnContainer.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ColumnDialog.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ColumnDialog.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ExListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ExListBox.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\PicturePreview.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\PicturePreview.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportBoxProperties.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportBoxProperties.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportControlFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportControlFactory.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEditor.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEllipseProperties.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEllipseProperties.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityBox.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityEllipse.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityEllipse.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityField.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityField.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityGrid.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityLabel.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityLabel.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityLine.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityLine.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityPicture.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntityPicture.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntitySettings.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportEntitySettings.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportFieldProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportFieldProperties.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportGridProperties.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportGridProperties.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportLabelProperties.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportLabelProperties.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportLineProperties.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportLineProperties.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportPictureProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\ReportPictureProperties.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\StringHelpers.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\StringHelpers.h
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\UnitConversion.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEditor\UnitConversion.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CornerBox.cpp
# End Source File
# Begin Source File

SOURCE=.\EditorSettingsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\HorzRuler.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportCreator.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportCreator.rc
# End Source File
# Begin Source File

SOURCE=.\ReportCreatorDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportCreatorView.cpp
# End Source File
# Begin Source File

SOURCE=.\RulerMeasurementsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdGrfx.cpp
# End Source File
# Begin Source File

SOURCE=.\VertRuler.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CornerBox.h
# End Source File
# Begin Source File

SOURCE=.\EditorSettingsDialog.h
# End Source File
# Begin Source File

SOURCE=.\HorzRuler.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ReportCreator.h
# End Source File
# Begin Source File

SOURCE=.\ReportCreatorDoc.h
# End Source File
# Begin Source File

SOURCE=.\ReportCreatorView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RulerMeasurementsDialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StdGrfx.h
# End Source File
# Begin Source File

SOURCE=.\VertRuler.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ReportCreator.ico
# End Source File
# Begin Source File

SOURCE=.\res\ReportCreator.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ReportCreatorDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
