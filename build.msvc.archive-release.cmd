@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

echo -^> archive-release xyo

set XYO_PATH_RELEASE=release

call build.msvc.cmd make
call build.msvc.cmd sign
call build.msvc.cmd install
call build.msvc.cmd install-release

if not exist release\ goto :eof

set PROJECT=xyo
SETLOCAL ENABLEDELAYEDEXPANSION
FOR /F "tokens=* USEBACKQ" %%F IN (`xyo-version --no-bump --get "--version-file=source/%PROJECT%.version.ini" %PROJECT%`) DO (
	SET VERSION=%%F
)

rem --- bin

set PROJECT_RELEASE=%PROJECT%-%VERSION%-%XYO_PLATFORM%
if not exist release\%PROJECT_RELEASE% goto :eof

pushd release
if exist %PROJECT_RELEASE%.7z del /Q /F %PROJECT_RELEASE%.7z
7zr a -mx9 -mmt4 -r- -sse -w. -y -t7z %PROJECT_RELEASE%.7z %PROJECT_RELEASE%
rmdir /Q /S %PROJECT_RELEASE%
popd

rem --- dev

set PROJECT_RELEASE=%PROJECT%-%VERSION%-%XYO_PLATFORM%-dev
if not exist release\%PROJECT_RELEASE% goto :eof

pushd release
if exist %PROJECT_RELEASE%.7z del /Q /F %PROJECT_RELEASE%.7z
7zr a -mx9 -mmt4 -r- -sse -w. -y -t7z %PROJECT_RELEASE%.7z %PROJECT_RELEASE%
rmdir /Q /S %PROJECT_RELEASE%
popd
