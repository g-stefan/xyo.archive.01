@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

if "%1" == "" goto ProcessSystemPlatform
if not exist ".\build\%1.cmd" goto ProcessSystemPlatform
call ".\build\%1.cmd" %2
goto :eof

:ProcessSystemPlatform
call ".\build\platform.select.cmd"
if "%XYO_PLATFORM%" == "" goto Info
if not exist ".\build\%XYO_PLATFORM%.cmd" goto Info
call ".\build\%XYO_PLATFORM%.cmd" %1
goto :eof

:Info
echo build [platform] [mode]
