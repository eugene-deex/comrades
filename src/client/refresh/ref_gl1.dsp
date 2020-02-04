# Microsoft Developer Studio Project File - Name="ref_gl1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ref_gl1 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ref_gl1.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ref_gl1.mak" CFG="ref_gl1 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ref_gl1 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ref_gl1 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ref_gl1 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\temp\ref_gl1\!release"
# PROP Intermediate_Dir "..\..\temp\ref_gl1\!release"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir "."
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /Ob2 /I "./" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 user32.lib gdi32.lib ./SDL2.lib opengl32.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386
# SUBTRACT LINK32 /debug
# Begin Custom Build
TargetDir=\Quake2\src_main\temp\ref_gl1\!release
InputPath=\Quake2\src_main\temp\ref_gl1\!release\ref_gl1.dll
SOURCE="$(InputPath)"

"D:\Quake2\ref_gl1.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetDir)\ref_gl1.dll "D:\Quake2\ref_gl1.dll"

# End Custom Build

!ELSEIF  "$(CFG)" == "ref_gl1 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\temp\ref_gl1\!debug"
# PROP Intermediate_Dir "..\..\temp\ref_gl1\!debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir "."
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /Gi /GX /ZI /Od /I "./" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FAs /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 user32.lib gdi32.lib ./SDL2.lib opengl32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /profile /incremental:no /map
# Begin Custom Build
TargetDir=\Quake2\src_main\temp\ref_gl1\!debug
InputPath=\Quake2\src_main\temp\ref_gl1\!debug\ref_gl1.dll
SOURCE="$(InputPath)"

"D:\Quake2\ref_gl1.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetDir)\ref_gl1.dll "D:\Quake2\ref_gl1.dll"

# End Custom Build

!ENDIF 

# Begin Target

# Name "ref_gl1 - Win32 Release"
# Name "ref_gl1 - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\gl1\header\local.h
# End Source File
# Begin Source File

SOURCE=.\gl1\header\model.h
# End Source File
# Begin Source File

SOURCE=.\gl1\header\qgl.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\gl1\gl1_draw.c
# End Source File
# Begin Source File

SOURCE=.\gl1\gl1_image.c
# End Source File
# Begin Source File

SOURCE=.\gl1\gl1_light.c
# End Source File
# Begin Source File

SOURCE=.\gl1\gl1_lightmap.c
# End Source File
# Begin Source File

SOURCE=.\gl1\gl1_main.c
# End Source File
# Begin Source File

SOURCE=.\gl1\gl1_md2.c
# End Source File
# Begin Source File

SOURCE=.\gl1\gl1_mesh.c
# End Source File
# Begin Source File

SOURCE=.\gl1\gl1_misc.c
# End Source File
# Begin Source File

SOURCE=.\gl1\gl1_model.c
# End Source File
# Begin Source File

SOURCE=.\gl1\gl1_scrap.c
# End Source File
# Begin Source File

SOURCE=.\gl1\gl1_sdl.c
# End Source File
# Begin Source File

SOURCE=.\gl1\gl1_sp2.c
# End Source File
# Begin Source File

SOURCE=.\gl1\gl1_surf.c
# End Source File
# Begin Source File

SOURCE=.\gl1\gl1_warp.c
# End Source File
# Begin Source File

SOURCE=..\..\backends\windows\shared\hunk.c
# End Source File
# Begin Source File

SOURCE=..\..\common\md4.c
# End Source File
# Begin Source File

SOURCE=.\files\pcx.c
# End Source File
# Begin Source File

SOURCE=.\files\pvs.c
# End Source File
# Begin Source File

SOURCE=.\gl1\qgl.c
# End Source File
# Begin Source File

SOURCE=..\..\common\shared\shared.c
# End Source File
# Begin Source File

SOURCE=.\files\stb.c
# End Source File
# Begin Source File

SOURCE=.\files\wal.c
# End Source File
# End Group
# End Target
# End Project
