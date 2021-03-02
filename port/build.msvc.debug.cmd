@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

echo -^> debug xyo

goto cmdXDefined
:cmdX
%*
if errorlevel 1 goto cmdXError
goto :eof
:cmdXError
echo "Error: debug"
exit 1
:cmdXDefined

if "%XYO_PLATFORM%" == "win64-msvc-2019" set DEFX= /DXYO_APPLICATION_64BIT /DXYO_PLATFORM=%XYO_PLATFORM%
if "%XYO_PLATFORM%" == "win32-msvc-2019" set DEFX= /DXYO_APPLICATION_32BIT /DXYO_PLATFORM=%XYO_PLATFORM%
if "%XYO_PLATFORM%" == "win64-msvc-2017" set DEFX= /DXYO_APPLICATION_64BIT /DXYO_PLATFORM=%XYO_PLATFORM%
if "%XYO_PLATFORM%" == "win32-msvc-2017" set DEFX= /DXYO_APPLICATION_32BIT /DXYO_PLATFORM=%XYO_PLATFORM%

if not exist bin\ mkdir bin
if not exist temp\ mkdir temp

set DEF=
set DEF= %DEF% /DXYO_OS_WINDOWS
set DEF= %DEF% /DXYO_COMPILER_MSVC
set DEF= %DEF% %DEFX%
set DEF= %DEF% /D_CRT_SECURE_NO_WARNINGS
set DEF= %DEF% /DXYO_MULTI_THREAD
rem set DEF= %DEF% /DXYO_SINGLE_THREAD
set DEF= %DEF% /DXYO_MEMORY_LEAK_DETECTOR_VLD
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_SYSTEM
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_ACTIVE_AS_UNIFIED
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_ACTIVE_LEVEL_IS_SYSTEM
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_UNIFIED_AS_SYSTEM
set DEF= %DEF% /DXYO_TMEMORYPOOL_CHECK
set DEF= %DEF% /DXYO_TMEMORYPOOL_CHECK_INFO
set DEF= %DEF% /DXYO_TMEMORYPOOL_CHECK_COUNT_INFO
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_CONSTRUCTOR_INFO
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_DESTRUCTOR_INFO
rem set DEF= %DEF% /DXYO_OBJECT_REFERENCE_COUNT_INFO

set INC=
set INC= %INC% /Iinclude
set INC= %INC% /Isource

set SRC=
set SRC=%SRC% util\xyo.config.cpp

call :cmdX cl /MT /O2 /Ox /Oy /GS- /GL /GA /EHsc- /GR- /TP %DEF% %INC% %SRC% /Fotemp\ /Fetemp/xyo.config.exe /link ws2_32.lib user32.lib
call :cmdX temp\xyo.config.exe

set DEF=
set DEF= %DEF% /D_CRT_SECURE_NO_WARNINGS
set DEF= %DEF% /DXYO_NO_VERSION
set DEF= %DEF% /DXYO_CC_NO_VERSION

set SRC=
set SRC=%SRC% util\xyo-cc\xyo-cc.cpp
set SRC=%SRC% util\xyo-cc\xyo-cc-copyright.cpp
set SRC=%SRC% util\xyo-cc\xyo-cc-license.cpp
set SRC=%SRC% source\xyo.amalgam.cpp

call :cmdX cl /MT /O2 /Ox /Oy /GS- /GL /GA /EHsc- /GR- /TP %DEF% %INC% %SRC% /Fotemp\ /Fetemp/xyo.cc.exe /link ws2_32.lib user32.lib

call :cmdX temp\xyo.cc --mode=debug @util/xyo.static.compile.info
call :cmdX temp\xyo.cc --mode=debug @util/xyo.dynamic.compile.info
call :cmdX temp\xyo.cc --mode=debug --exe xyo.test.01 @util/xyo.test.compile.info
call :cmdX temp\xyo.cc --mode=debug --exe xyo.test.02 @util/xyo.test.compile.info
call :cmdX temp\xyo.cc --mode=debug --exe xyo.test.03 @util/xyo.test.compile.info
call :cmdX temp\xyo.cc --mode=debug --exe xyo.test.04 @util/xyo.test.compile.info

call :cmdX temp\xyo.cc --mode=debug @util/xyo-cc.compile.info

