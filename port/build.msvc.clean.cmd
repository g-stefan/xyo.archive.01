@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

echo -^> clean xyo

if exist bin\ rmdir /Q /S bin
if exist temp\ rmdir /Q /S temp
if exist lib\ rmdir /Q /S lib
