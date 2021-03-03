@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

echo -^> release xyo

goto cmdXDefined
:cmdX
%*
if errorlevel 1 goto cmdXError
goto :eof
:cmdXError
echo "Error: release"
exit 1
:cmdXDefined

set XYO_PATH_RELEASE=release

call :cmdX call build\build.msvc.cmd make
call :cmdX call build\build.msvc.cmd sign
call :cmdX call build\build.msvc.cmd install
call :cmdX call build\build.msvc.cmd install-release
call :cmdX temp\xyo.cc xyo --archive-release-sha512 --version-file=source/xyo.version.ini
