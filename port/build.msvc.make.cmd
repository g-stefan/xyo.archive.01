@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

set ACTION=%1
if "%1" == "" set ACTION=make

echo -^> %ACTION% xyo

goto cmdXDefined
:cmdX
%*
if errorlevel 1 goto cmdXError
goto :eof
:cmdXError
echo "Error: %ACTION%"
exit 1
:cmdXDefined

if "%XYO_PLATFORM%" == "win64-msvc-2019" set DEFX= /DXYO_APPLICATION_64BIT /DXYO_PLATFORM=%XYO_PLATFORM%
if "%XYO_PLATFORM%" == "win32-msvc-2019" set DEFX= /DXYO_APPLICATION_32BIT /DXYO_PLATFORM=%XYO_PLATFORM%
if "%XYO_PLATFORM%" == "win64-msvc-2017" set DEFX= /DXYO_APPLICATION_64BIT /DXYO_PLATFORM=%XYO_PLATFORM%
if "%XYO_PLATFORM%" == "win32-msvc-2017" set DEFX= /DXYO_APPLICATION_32BIT /DXYO_PLATFORM=%XYO_PLATFORM%

if not exist bin\ mkdir bin
if not exist build\ mkdir build

set DEF=
set DEF= %DEF% /DXYO_OS_WINDOWS
set DEF= %DEF% /DXYO_COMPILER_MSVC
set DEF= %DEF% %DEFX%
set DEF= %DEF% /D_CRT_SECURE_NO_WARNINGS
set DEF= %DEF% /DXYO_MULTI_THREAD

if not "%XYO_COMPILE_DEBUG%" == "1" goto :ReleaseX

set DEF= %DEF% /DXYO_MEMORY_LEAK_DETECTOR_VLD
set DEF= %DEF% /DXYO_TMEMORYPOOL_CHECK
set DEF= %DEF% /DXYO_TMEMORYPOOL_CHECK_INFO
set DEF= %DEF% /DXYO_TMEMORYPOOL_CHECK_COUNT_INFO

:ReleaseX

set INC=
set INC= %INC% /Iinclude
set INC= %INC% /Isource

set SRC=
set SRC=%SRC% util\xyo.config.cpp

call :cmdX cl /MT /O2 /Ox /Oy /GS- /GL /GA /EHsc- /GR- /TP %DEF% %INC% %SRC% /Fobuild\ /Febuild/xyo.config.exe
call :cmdX build\xyo.config.exe

set DEF=
set DEF= %DEF% /D_CRT_SECURE_NO_WARNINGS
set DEF= %DEF% /DXYO_NO_VERSION
set DEF= %DEF% /DXYO_CC_NO_VERSION

set SRC=
set SRC=%SRC% util\xyo-cc\xyo-cc.cpp
set SRC=%SRC% util\xyo-cc\xyo-cc-copyright.cpp
set SRC=%SRC% util\xyo-cc\xyo-cc-license.cpp
set SRC=%SRC% source\xyo.amalgam.cpp

call :cmdX cl /MT /O2 /Ox /Oy /GS- /GL /GA /EHsc- /GR- /TP %DEF% %INC% %SRC% /Fobuild\ /Febuild/xyo.cc.exe
call :cmdX build\xyo.cc --mode=%ACTION% @util/xyo.static.compile
call :cmdX build\xyo.cc --mode=%ACTION% @util/xyo.dynamic.compile
call :cmdX build\xyo.cc --mode=%ACTION% --exe xyo.test.01 @util/xyo.test.compile
call :cmdX build\xyo.cc --mode=%ACTION% --exe xyo.test.02 @util/xyo.test.compile
call :cmdX build\xyo.cc --mode=%ACTION% --exe xyo.test.03 @util/xyo.test.compile
call :cmdX build\xyo.cc --mode=%ACTION% --exe xyo.test.04 @util/xyo.test.compile
call :cmdX build\xyo.cc --mode=%ACTION% @util/xyo-cc.compile
