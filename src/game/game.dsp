# Microsoft Developer Studio Project File - Name="game" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=game - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "game.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "game.mak" CFG="game - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "game - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "game - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/GoldSrc/game", ELEBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "game - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\temp\game\!release"
# PROP Intermediate_Dir "..\temp\game\!release"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
# ADD CPP /nologo /MD /W3 /O2 /I "./" /I "ents" /I "game" /I "global" /I "monsters" /I "../common" /I "../pm_shared" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /Fr /YX
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 msvcrt.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386 /nodefaultlib:"libc.lib" /def:".\game.def"
# SUBTRACT LINK32 /profile /map /debug /nodefaultlib
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
TargetDir=\Quake2\src_main\temp\game\!release
InputPath=\Quake2\src_main\temp\game\!release\game.dll
SOURCE="$(InputPath)"

"D:\Quake2\baseq2\game.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetDir)\game.dll "D:\Quake2\baseq2\game.dll"

# End Custom Build

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "game___Win32_Debug"
# PROP BASE Intermediate_Dir "game___Win32_Debug"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\temp\game\!debug"
# PROP Intermediate_Dir "..\temp\game\!debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MT /W3 /O2 /I "..\game" /I "..\common\engine" /I "..\common" /I "..\game\ents" /I "..\game\global" /I "..\game\weapons" /I "..\game\game" /I "..\game\monsters" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /ZI /Od /I "./" /I "ents" /I "game" /I "global" /I "monsters" /I "../common" /I "../pm_shared" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /FD /c
# SUBTRACT CPP /u /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /incremental:yes /machine:I386 /nodefaultlib:"libc" /def:".\game.def" /libpath:"..\common\libs"
# SUBTRACT BASE LINK32 /profile /map /debug
# ADD LINK32 msvcrtd.lib /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386 /nodefaultlib:"libc.lib" /def:".\game.def" /pdbtype:sept
# SUBTRACT LINK32 /profile /map
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
TargetDir=\Quake2\src_main\temp\game\!debug
InputPath=\Quake2\src_main\temp\game\!debug\game.dll
SOURCE="$(InputPath)"

"D:\Quake2\baseq2\game.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetDir)\game.dll "D:\Quake2\baseq2\game.dll"

# End Custom Build

!ENDIF 

# Begin Target

# Name "game - Win32 Release"
# Name "game - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def"
# Begin Source File

SOURCE=.\monster\berserker.c
# End Source File
# Begin Source File

SOURCE=.\monster\boss2.c
# End Source File
# Begin Source File

SOURCE=.\monster\boss3.c
# End Source File
# Begin Source File

SOURCE=.\monster\boss31.c
# End Source File
# Begin Source File

SOURCE=.\monster\boss32.c
# End Source File
# Begin Source File

SOURCE=.\monster\brain.c
# End Source File
# Begin Source File

SOURCE=.\monster\chick.c
# End Source File
# Begin Source File

SOURCE=.\player\client.c
# End Source File
# Begin Source File

SOURCE=..\common\shared\flash.c
# End Source File
# Begin Source File

SOURCE=.\monster\flipper.c
# End Source File
# Begin Source File

SOURCE=.\monster\float.c
# End Source File
# Begin Source File

SOURCE=.\monster\flyer.c
# End Source File
# Begin Source File

SOURCE=.\g_ai.c
# End Source File
# Begin Source File

SOURCE=.\g_chase.c
# End Source File
# Begin Source File

SOURCE=.\g_cmds.c
# End Source File
# Begin Source File

SOURCE=.\g_combat.c
# End Source File
# Begin Source File

SOURCE=.\g_func.c
# End Source File
# Begin Source File

SOURCE=.\g_items.c
# End Source File
# Begin Source File

SOURCE=.\g_main.c
# End Source File
# Begin Source File

SOURCE=.\g_misc.c
# End Source File
# Begin Source File

SOURCE=.\g_monster.c
# End Source File
# Begin Source File

SOURCE=.\g_phys.c
# End Source File
# Begin Source File

SOURCE=.\g_spawn.c
# End Source File
# Begin Source File

SOURCE=.\g_svcmds.c
# End Source File
# Begin Source File

SOURCE=.\g_target.c
# End Source File
# Begin Source File

SOURCE=.\g_trigger.c
# End Source File
# Begin Source File

SOURCE=.\g_turret.c
# End Source File
# Begin Source File

SOURCE=.\g_utils.c
# End Source File
# Begin Source File

SOURCE=.\g_weapon.c
# End Source File
# Begin Source File

SOURCE=.\monster\gladiator.c
# End Source File
# Begin Source File

SOURCE=.\monster\gunner.c
# End Source File
# Begin Source File

SOURCE=.\monster\hover.c
# End Source File
# Begin Source File

SOURCE=.\player\hud.c
# End Source File
# Begin Source File

SOURCE=.\monster\infantry.c
# End Source File
# Begin Source File

SOURCE=.\monster\insane.c
# End Source File
# Begin Source File

SOURCE=.\monster\medic.c
# End Source File
# Begin Source File

SOURCE=.\monster\move.c
# End Source File
# Begin Source File

SOURCE=.\monster\mutant.c
# End Source File
# Begin Source File

SOURCE=.\monster\parasite.c
# End Source File
# Begin Source File

SOURCE=..\common\shared\rand.c
# End Source File
# Begin Source File

SOURCE=.\savegame\savegame.c
# End Source File
# Begin Source File

SOURCE=..\common\shared\shared.c
# End Source File
# Begin Source File

SOURCE=.\monster\soldier.c
# End Source File
# Begin Source File

SOURCE=.\monster\supertank.c
# End Source File
# Begin Source File

SOURCE=.\monster\tank.c
# End Source File
# Begin Source File

SOURCE=.\player\trail.c
# End Source File
# Begin Source File

SOURCE=.\player\view.c
# End Source File
# Begin Source File

SOURCE=.\player\weapon.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp"
# Begin Source File

SOURCE=.\monster\berserker.h
# End Source File
# Begin Source File

SOURCE=.\monster\boss2.h
# End Source File
# Begin Source File

SOURCE=.\monster\boss31.h
# End Source File
# Begin Source File

SOURCE=.\monster\boss32.h
# End Source File
# Begin Source File

SOURCE=.\monster\brain.h
# End Source File
# Begin Source File

SOURCE=.\monster\chick.h
# End Source File
# Begin Source File

SOURCE=.\savegame\clientfields.h
# End Source File
# Begin Source File

SOURCE=.\savegame\fields.h
# End Source File
# Begin Source File

SOURCE=.\monster\flipper.h
# End Source File
# Begin Source File

SOURCE=.\monster\float.h
# End Source File
# Begin Source File

SOURCE=.\monster\flyer.h
# End Source File
# Begin Source File

SOURCE=.\game.h
# End Source File
# Begin Source File

SOURCE=.\savegame\gamefunc_decs.h
# End Source File
# Begin Source File

SOURCE=.\savegame\gamefunc_list.h
# End Source File
# Begin Source File

SOURCE=.\savegame\gamemmove_decs.h
# End Source File
# Begin Source File

SOURCE=.\savegame\gamemmove_list.h
# End Source File
# Begin Source File

SOURCE=.\monster\gladiator.h
# End Source File
# Begin Source File

SOURCE=.\monster\gunner.h
# End Source File
# Begin Source File

SOURCE=.\monster\hover.h
# End Source File
# Begin Source File

SOURCE=.\monster\infantry.h
# End Source File
# Begin Source File

SOURCE=.\monster\insane.h
# End Source File
# Begin Source File

SOURCE=.\savegame\levelfields.h
# End Source File
# Begin Source File

SOURCE=.\header\local.h
# End Source File
# Begin Source File

SOURCE=.\monster\medic.h
# End Source File
# Begin Source File

SOURCE=.\monster\mutant.h
# End Source File
# Begin Source File

SOURCE=.\monster\parasite.h
# End Source File
# Begin Source File

SOURCE=.\monster\player.h
# End Source File
# Begin Source File

SOURCE=.\monster\soldier.h
# End Source File
# Begin Source File

SOURCE=.\monster\supertank.h
# End Source File
# Begin Source File

SOURCE=.\monster\tank.h
# End Source File
# End Group
# End Target
# End Project
