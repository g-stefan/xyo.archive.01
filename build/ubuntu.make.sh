#!/bin/sh
# Public domain
# http://unlicense.org/
# Created by Grigore Stefan <g_stefan@yahoo.com>

ACTION=$1
if [ "$ACTION" = "" ]; then
	ACTION=make
fi

echo "- $BUILD_PROJECT > $ACTION"

cmdX(){
	if ! "$@" ; then
		echo "Error: $ACTION"
		exit 1
	fi
}

[ -d output ] || mkdir -p output
[ -d temp ] || mkdir -p temp

XYO_APPLICATION="XYO_APPLICATION_64BIT"
XYO_OS="XYO_OS_UNIX"
CC_LIB=""
if [ "$(expr substr $(uname -s) 1 10)" = "MINGW32_NT" ]; then
	XYO_OS="XYO_OS_MINGW"
	XYO_APPLICATION="XYO_APPLICATION_32BIT"
	CC_LIB="-luser32 -lws2_32"
elif [ "$(expr substr $(uname -s) 1 10)" = "MINGW64_NT" ]; then
	XYO_OS="XYO_OS_MINGW"
	CC_LIB="-luser32 -lws2_32"
fi

DEF=""
DEF="$DEF -D$XYO_OS"
DEF="$DEF -DXYO_COMPILER_GCC"
DEF="$DEF -DXYO_APPLICATION_64BIT"
DEF="$DEF -DXYO_PLATFORM=$XYO_PLATFORM"
DEF="$DEF -DXYO_MULTI_THREAD"

INC=""
INC="$INC -Isource/xyo"

SRC=""
SRC="$SRC build/source/xyo.config.cpp"

if [ "$CXX" = "" ]; then
	CXX=gcc
	export CXX=$CXX
fi

cmdX $CXX -o temp/xyo.config -O1 -std=c++11 -std=gnu++11 $DEF $INC $SRC -lstdc++ -lpthread -lm
cmdX ./temp/xyo.config

DEF=""
DEF="$DEF -DXYO_NO_VERSION"
DEF="$DEF -DXYO_CC_NO_VERSION"

SRC=""
SRC="$SRC source/xyo-cc/xyo-cc.cpp"
SRC="$SRC source/xyo-cc/xyo-cc-copyright.cpp"
SRC="$SRC source/xyo-cc/xyo-cc-license.cpp"
SRC="$SRC source/xyo-cc/xyo-cc-compiler.cpp"
SRC="$SRC source/xyo-cc/xyo-cc-compiler--compiler-gcc.cpp"
SRC="$SRC source/xyo-cc/xyo-cc-compiler--compiler-msvc.cpp"
SRC="$SRC source/xyo/xyo.amalgam.cpp"

cmdX $CXX -o temp/xyo.cc -O1 -std=c++11 -std=gnu++11 $DEF $INC $SRC -lstdc++ -lpthread -lm $CC_LIB
cmdX temp/xyo.cc --mode=$ACTION @build/source/xyo.static.compile
cmdX temp/xyo.cc --mode=$ACTION @build/source/xyo.dynamic.compile
cmdX temp/xyo.cc --mode=$ACTION --exe xyo.test.01 @build/source/xyo.test.compile
cmdX temp/xyo.cc --mode=$ACTION --exe xyo.test.02 @build/source/xyo.test.compile
cmdX temp/xyo.cc --mode=$ACTION --exe xyo.test.03 @build/source/xyo.test.compile
cmdX temp/xyo.cc --mode=$ACTION --exe xyo.test.04 @build/source/xyo.test.compile
cmdX temp/xyo.cc --mode=$ACTION @build/source/xyo-cc.compile
cmdX temp/xyo.cc --mode=$ACTION @build/source/xyo-cc.library.compile
