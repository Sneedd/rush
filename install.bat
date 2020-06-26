@echo off
set targetdir=E:\Libraries\rush
set sourcedir=.

echo Installiert die neuen include und lib Dateien ...
xcopy %sourcedir%\include\*.*  %targetdir%\include\*.* /Y /S /Q
xcopy %sourcedir%\bin\Library\*.*  %targetdir%\lib\*.* /Y /S /Q

echo.
echo.
rem pause

@echo on


