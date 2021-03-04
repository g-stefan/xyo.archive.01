@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

echo -^> test xyo

goto cmdXDefined
:cmdX
echo %*
%*
if errorlevel 1 goto cmdXError
goto :eof
:cmdXError
echo "Error: test"
exit 1
:cmdXDefined

pushd output\bin

call :cmdX xyo.test.01.exe
call :cmdX xyo.test.02.exe
call :cmdX xyo.test.03.exe
call :cmdX xyo.test.04.exe

popd
