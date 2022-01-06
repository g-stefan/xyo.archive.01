@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

set ACTION=%1
if "%1" == "" set ACTION=make

echo - %BUILD_PROJECT% ^> %1

goto cmdXDefined
:cmdX
cmd.exe /C "%*"
if errorlevel 1 goto cmdXError
goto :eof
:cmdXError
echo "Error: %ACTION%"
exit 1
:cmdXDefined

if "%XYO_PLATFORM%" == "win64-msvc-2022" set DEFX= /DXYO_APPLICATION_64BIT /DXYO_PLATFORM=%XYO_PLATFORM%
if "%XYO_PLATFORM%" == "win32-msvc-2022" set DEFX= /DXYO_APPLICATION_32BIT /DXYO_PLATFORM=%XYO_PLATFORM%
if "%XYO_PLATFORM%" == "win64-msvc-2019" set DEFX= /DXYO_APPLICATION_64BIT /DXYO_PLATFORM=%XYO_PLATFORM%
if "%XYO_PLATFORM%" == "win32-msvc-2019" set DEFX= /DXYO_APPLICATION_32BIT /DXYO_PLATFORM=%XYO_PLATFORM%
if "%XYO_PLATFORM%" == "win64-msvc-2017" set DEFX= /DXYO_APPLICATION_64BIT /DXYO_PLATFORM=%XYO_PLATFORM%
if "%XYO_PLATFORM%" == "win32-msvc-2017" set DEFX= /DXYO_APPLICATION_32BIT /DXYO_PLATFORM=%XYO_PLATFORM%

if not exist output\ mkdir output
if not exist temp\ mkdir temp

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
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_NEW_MEMORY_INFO
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_DELETE_MEMORY_INFO
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_CONSTRUCTOR_INFO
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_DESTRUCTOR_INFO
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_SYSTEM
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_ACTIVE_AS_UNIFIED
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_ACTIVE_LEVEL_IS_SYSTEM
rem set DEF= %DEF% /DXYO_TMEMORYPOOL_UNIFIED_AS_SYSTEM
rem set DEF= %DEF% /DXYO_OBJECT_REFERENCE_COUNT_INFO

:ReleaseX

set INC=
set INC= %INC% /Isource\xyo

set SRC=
set SRC=%SRC% build\source\xyo.config.cpp

if "%CXX%" == "" set CXX=cl

call :cmdX %CXX% /MT /O2 /Ox /Oy /GS- /GL /GA /EHsc- /GR- /TP %DEF% %INC% %SRC% /Fotemp\ /Fetemp/xyo.config.exe
call :cmdX temp\xyo.config.exe

set DEF=
set DEF= %DEF% /D_CRT_SECURE_NO_WARNINGS
set DEF= %DEF% /DXYO_NO_VERSION
set DEF= %DEF% /DXYO_CC_NO_VERSION

set SRC=
set SRC=%SRC% source\xyo-cc\xyo-cc.cpp
set SRC=%SRC% source\xyo-cc\xyo-cc-copyright.cpp
set SRC=%SRC% source\xyo-cc\xyo-cc-license.cpp
set SRC=%SRC% source\xyo\xyo.amalgam.cpp

call :cmdX %CXX% /MT /O2 /Ox /Oy /GS- /GL /GA /EHsc- /GR- /TP %DEF% %INC% %SRC% /Fotemp\ /Fetemp/xyo.cc.exe
call :cmdX temp\xyo.cc --mode=%ACTION% @build/source/xyo.static.compile
call :cmdX temp\xyo.cc --mode=%ACTION% @build/source/xyo.dynamic.compile
call :cmdX temp\xyo.cc --mode=%ACTION% --exe xyo.test.01 @build/source/xyo.test.compile
call :cmdX temp\xyo.cc --mode=%ACTION% --exe xyo.test.02 @build/source/xyo.test.compile
call :cmdX temp\xyo.cc --mode=%ACTION% --exe xyo.test.03 @build/source/xyo.test.compile
call :cmdX temp\xyo.cc --mode=%ACTION% --exe xyo.test.04 @build/source/xyo.test.compile
call :cmdX temp\xyo.cc --mode=%ACTION% @build/source/xyo-cc.compile
call :cmdX temp\xyo.cc --mode=%ACTION% @build/source/xyo-cc.library.compile
