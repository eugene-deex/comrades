# Microsoft Developer Studio Project File - Name="ref_soft" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ref_soft - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ref_soft.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ref_soft.mak" CFG="ref_soft - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ref_soft - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ref_soft - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ref_soft - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\temp\ref_soft\!release"
# PROP Intermediate_Dir "..\..\temp\ref_soft\!release"
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
# ADD LINK32 user32.lib gdi32.lib ./SDL2.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386
# SUBTRACT LINK32 /debug
# Begin Custom Build
TargetDir=\q2src\temp\ref_soft\!release
InputPath=\q2src\temp\ref_soft\!release\ref_soft.dll
SOURCE="$(InputPath)"

"C:\Quake2\ref_soft.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetDir)\ref_soft.dll "C:\Quake2\ref_soft.dll"

# End Custom Build

!ELSEIF  "$(CFG)" == "ref_soft - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\temp\ref_soft\!debug"
# PROP Intermediate_Dir "..\..\temp\ref_soft\!debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir "."
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /Gi /GX /ZI /Od /I "./" /D "YQ2OSTYPE Windows" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FAs /FR /FD /c
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
# ADD LINK32 user32.lib gdi32.lib ./SDL2.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /profile /incremental:no /map
# Begin Custom Build
TargetDir=\q2src\temp\ref_soft\!debug
InputPath=\q2src\temp\ref_soft\!debug\ref_soft.dll
SOURCE="$(InputPath)"

"C:\Quake2\ref_soft.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetDir)\ref_soft.dll "C:\Quake2\ref_soft.dll"

# End Custom Build

!ENDIF 

# Begin Target

# Name "ref_soft - Win32 Release"
# Name "ref_soft - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
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

SOURCE=..\..\common\shared\shared.c
# End Source File
# Begin Source File

SOURCE=.\files\stb.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_aclip.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_alias.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_bsp.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_draw.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_edge.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_image.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_light.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_main.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_misc.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_model.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_part.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_poly.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_polyset.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_rast.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_scan.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_sprite.c
# End Source File
# Begin Source File

SOURCE=.\soft\sw_surf.c
# End Source File
# Begin Source File

SOURCE=.\files\wal.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\soft\header\local.h
# End Source File
# Begin Source File

SOURCE=.\soft\header\model.h
# End Source File
# Begin Source File

SOURCE=.\files\stb_image.h
# End Source File
# Begin Source File

SOURCE=.\files\stb_image_resize.h
# End Source File
# End Group
# End Target
# End Project
