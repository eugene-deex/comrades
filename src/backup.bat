@echo off
color 4F
echo 			 XashXT Group 2006 (C)
echo 			Prepare source for backup
echo.

if exist backup.log del /f /q backup.log
if not exist C:\Quake2\!backup/ mkdir C:\Quake2\!backup\
echo 			     Prepare OK!
echo 		     Please wait: backup in progress
C:\Progra~1\WinRar\rar a -agMMMYYYY-DD C:\Quake2\!backup\.rar -dh -m5 -rr10p @backup.lst >>backup.log
if errorlevel 1 goto error
if errorlevel 0 goto ok
:ok
cls
echo 		    Source was sucessfully backuped
echo 		     and stored in folder "backup"
echo 		      Press any key for exit. :-)
if exist backup.log del /f /q backup.log
exit
:error
echo 		    ******************************
echo 		    ***********Error!*************
echo 		    ******************************
echo 		    **See backup.log for details**
echo 		    ******************************
echo 		    ******************************
echo.
echo 		      press any key for exit :-(
pause>nul
exit
