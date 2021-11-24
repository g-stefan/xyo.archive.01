@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

echo - %BUILD_PROJECT% ^> release

goto cmdXDefined
:cmdX
%*
if errorlevel 1 goto cmdXError
goto :eof
:cmdXError
echo "Error: release"
exit 1
:cmdXDefined

set XYO_PATH_RELEASE_ORIGINAL=%XYO_PATH_RELEASE%
set XYO_PATH_RELEASE=release

if exist temp\xyo.cc temp\xyo.cc %BUILD_PROJECT% --has-archived-release --version-file=version.ini
if errorlevel 1 exit 0
call :cmdX call build\msvc.cmd make
call :cmdX call build\msvc.cmd sign
call :cmdX call build\msvc.cmd install
call :cmdX call build\msvc.cmd install-release
call :cmdX temp\xyo.cc %BUILD_PROJECT% --archive-release-sha512 --version-file=version.ini
set XYO_PATH_RELEASE=%XYO_PATH_RELEASE_ORIGINAL%
call :cmdX temp\xyo.cc %BUILD_PROJECT% --copy-local-archived-release --version-file=version.ini
