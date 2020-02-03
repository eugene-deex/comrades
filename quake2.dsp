# Microsoft Developer Studio Project File - Name="quake2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=quake2 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "quake2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "quake2.mak" CFG="quake2 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "quake2 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "quake2 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "quake2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\temp\quake2\!release"
# PROP Intermediate_Dir ".\temp\quake2\!release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /Ob2 /I "./client\refresh" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /opt:nowin98
# ADD LINK32 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib winmm.lib .\client\refresh\SDL2.lib /nologo /subsystem:console /pdb:none /machine:I386 /out:".\temp\quake2\!release/yquake2.exe" /opt:nowin98
# Begin Custom Build
TargetDir=.\temp\quake2\!release
InputPath=.\temp\quake2\!release\yquake2.exe
SOURCE="$(InputPath)"

"D:\Quake2\yquake2.exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetDir)\yquake2.exe "D:\Quake2\yquake2.exe"

# End Custom Build

!ELSEIF  "$(CFG)" == "quake2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "quake2___Win32_Debug"
# PROP BASE Intermediate_Dir "quake2___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\temp\quake2\!debug"
# PROP Intermediate_Dir ".\temp\quake2\!debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /Ob0 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MLd /W3 /Gi /GX /ZI /Od /I "./client\refresh" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FAs /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 msvcrt.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /pdb:none /machine:I386 /nodefaultlib:"libcmt.lib" /out:"yquake2.exe" /opt:nowin98
# ADD LINK32 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib winmm.lib .\client\refresh\SDL2.lib /nologo /subsystem:console /pdb:none /debug /machine:I386 /out:".\temp\quake2\!debug/yquake2.exe" /opt:nowin98
# Begin Custom Build
TargetDir=.\temp\quake2\!debug
InputPath=.\temp\quake2\!debug\yquake2.exe
SOURCE="$(InputPath)"

"D:\Quake2\yquake2.exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetDir)\yquake2.exe "D:\Quake2\yquake2.exe"

# End Custom Build

!ENDIF 

# Begin Target

# Name "quake2 - Win32 Release"
# Name "quake2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\common\argproc.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_cin.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_console.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_download.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_effects.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_entities.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_input.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_inventory.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_keyboard.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_lights.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_main.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_network.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_parse.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_particles.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_prediction.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_screen.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_tempentities.c
# End Source File
# Begin Source File

SOURCE=.\client\cl_view.c
# End Source File
# Begin Source File

SOURCE=.\common\clientserver.c
# End Source File
# Begin Source File

SOURCE=.\common\cmdparser.c
# End Source File
# Begin Source File

SOURCE=.\common\collision.c
# End Source File
# Begin Source File

SOURCE=.\common\crc.c
# End Source File
# Begin Source File

SOURCE=.\common\cvar.c
# End Source File
# Begin Source File

SOURCE=.\common\filesystem.c
# End Source File
# Begin Source File

SOURCE=.\common\shared\flash.c
# End Source File
# Begin Source File

SOURCE=.\common\frame.c
# End Source File
# Begin Source File

SOURCE=.\client\vid\glimp_sdl.c
# End Source File
# Begin Source File

SOURCE=.\common\glob.c
# End Source File
# Begin Source File

SOURCE=.\backends\windows\shared\hunk.c
# End Source File
# Begin Source File

SOURCE=.\client\input\in_sdl.c
# End Source File
# Begin Source File

SOURCE=.\common\unzip\ioapi.c
# End Source File
# Begin Source File

SOURCE=.\common\md4.c
# End Source File
# Begin Source File

SOURCE=.\client\menu\menu.c
# End Source File
# Begin Source File

SOURCE=.\common\unzip\miniz.c
# End Source File
# Begin Source File

SOURCE=.\backends\generic\misc.c
# End Source File
# Begin Source File

SOURCE=.\common\movemsg.c
# End Source File
# Begin Source File

SOURCE=.\common\netchan.c
# End Source File
# Begin Source File

SOURCE=.\backends\windows\network.c
# End Source File
# Begin Source File

SOURCE=.\client\sound\ogg.c
# End Source File
# Begin Source File

SOURCE=.\client\sound\openal.c
# End Source File
# Begin Source File

SOURCE=.\common\pmove.c
# End Source File
# Begin Source File

SOURCE=.\backends\windows\q2.rc
# End Source File
# Begin Source File

SOURCE=.\client\sound\qal.c
# End Source File
# Begin Source File

SOURCE=.\client\menu\qmenu.c
# End Source File
# Begin Source File

SOURCE=.\common\shared\rand.c
# End Source File
# Begin Source File

SOURCE=.\common\shared\shared.c
# End Source File
# Begin Source File

SOURCE=.\client\sound\snd_sdl.c
# End Source File
# Begin Source File

SOURCE=.\client\sound\sound.c
# End Source File
# Begin Source File

SOURCE=.\server\sv_cmd.c
# End Source File
# Begin Source File

SOURCE=.\server\sv_conless.c
# End Source File
# Begin Source File

SOURCE=.\server\sv_entities.c
# End Source File
# Begin Source File

SOURCE=.\server\sv_game.c
# End Source File
# Begin Source File

SOURCE=.\server\sv_init.c
# End Source File
# Begin Source File

SOURCE=.\server\sv_main.c
# End Source File
# Begin Source File

SOURCE=.\server\sv_save.c
# End Source File
# Begin Source File

SOURCE=.\server\sv_send.c
# End Source File
# Begin Source File

SOURCE=.\server\sv_user.c
# End Source File
# Begin Source File

SOURCE=.\server\sv_world.c
# End Source File
# Begin Source File

SOURCE=.\backends\windows\sys_win.c
# End Source File
# Begin Source File

SOURCE=.\backends\windows\system.c
# End Source File
# Begin Source File

SOURCE=.\common\szone.c
# End Source File
# Begin Source File

SOURCE=.\common\unzip\unzip.c
# End Source File
# Begin Source File

SOURCE=.\client\vid\vid.c
# End Source File
# Begin Source File

SOURCE=.\client\menu\videomenu.c
# End Source File
# Begin Source File

SOURCE=.\client\sound\wave.c
# End Source File
# Begin Source File

SOURCE=.\common\zone.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\client\header\client.h
# End Source File
# Begin Source File

SOURCE=.\client\header\console.h
# End Source File
# Begin Source File

SOURCE=.\client\input\header\input.h
# End Source File
# Begin Source File

SOURCE=.\common\unzip\ioapi.h
# End Source File
# Begin Source File

SOURCE=.\client\header\keyboard.h
# End Source File
# Begin Source File

SOURCE=.\client\sound\header\local.h
# End Source File
# Begin Source File

SOURCE=.\common\unzip\miniz.h
# End Source File
# Begin Source File

SOURCE=.\common\unzip\minizconf.h
# End Source File
# Begin Source File

SOURCE=.\client\vid\icon\q2icon64.h
# End Source File
# Begin Source File

SOURCE=.\client\sound\header\qal.h
# End Source File
# Begin Source File

SOURCE=.\client\menu\header\qmenu.h
# End Source File
# Begin Source File

SOURCE=.\client\vid\header\ref.h
# End Source File
# Begin Source File

SOURCE=.\backends\windows\header\resource.h
# End Source File
# Begin Source File

SOURCE=.\client\header\screen.h
# End Source File
# Begin Source File

SOURCE=.\server\header\server.h
# End Source File
# Begin Source File

SOURCE=.\client\sound\header\sound.h
# End Source File
# Begin Source File

SOURCE=.\client\vid\header\stb_image_write.h
# End Source File
# Begin Source File

SOURCE=.\client\sound\header\stb_vorbis.h
# End Source File
# Begin Source File

SOURCE=.\common\unzip\unzip.h
# End Source File
# Begin Source File

SOURCE=.\client\vid\header\vid.h
# End Source File
# Begin Source File

SOURCE=.\client\sound\header\vorbis.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\backends\windows\q2.ico
# End Source File
# End Target
# End Project
