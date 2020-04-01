@echo off

set MSDEV=BuildConsole
set CONFIG=/ShowTime /ShowAgent /nologo /cfg=
set MSDEV=msdev
set CONFIG=/make 
set build_type=release
set BUILD_ERROR=
call vcvars32

%MSDEV% game/game.dsp %CONFIG%"game - Win32 Release" %build_target%
if errorlevel 1 set BUILD_ERROR=1

%MSDEV% .\quake2.dsp %CONFIG%"quake2 - Win32 Release" %build_target%
if errorlevel 1 set BUILD_ERROR=1

%MSDEV% client\refresh\ref_gl1.dsp %CONFIG%"ref_gl1 - Win32 Release" %build_target%
if errorlevel 1 set BUILD_ERROR=1

%MSDEV% client\refresh\ref_gl3.dsp %CONFIG%"ref_gl3 - Win32 Release" %build_target%
if errorlevel 1 set BUILD_ERROR=1

%MSDEV% client\refresh\ref_soft.dsp %CONFIG%"ref_soft - Win32 Release" %build_target%
if errorlevel 1 set BUILD_ERROR=1

if "%BUILD_ERROR%"=="" goto build_ok

echo *********************
echo *********************
echo *** Build Errors! ***
echo *********************
echo *********************
echo press any key to exit
echo *********************
pause>nul
goto done


@rem
@rem Successful build
@rem
:build_ok

echo
echo 	     Build succeeded!
echo
:done