#!/bin/sh
# Public domain
# http://unlicense.org/
# Created by Grigore Stefan <g_stefan@yahoo.com>

ACTION=$1
if [ "$ACTION" = "" ]; then
	ACTION=make
fi

echo "-> $ACTION xyo"

cmdX(){
	if ! "$@" ; then
		echo "Error: $ACTION"
		exit 1
	fi
}

[ -d bin ] || mkdir -p bin
[ -d build ] || mkdir -p build

XYO_PLATFORM="unknown"
XYO_APPLICATION="XYO_APPLICATION_64BIT"
XYO_OS="XYO_OS_UNIX"
CC_LIB=""
if [ "$(expr substr $(uname -s) 1 5)" = "Linux" ]; then
	RELEASE=`cat /etc/lsb-release | grep DISTRIB_RELEASE| cut -d "=" -f 2`
	XYO_PLATFORM="ubuntu-$RELEASE"
elif [ "$(expr substr $(uname -s) 1 10)" = "MSYS_NT" ]; then
	XYO_PLATFORM="msys"
elif [ "$(expr substr $(uname -s) 1 10)" = "MINGW32_NT" ]; then
	XYO_PLATFORM="mingw32"
	XYO_OS="XYO_OS_WINDOWS"
	XYO_APPLICATION="XYO_APPLICATION_32BIT"
elif [ "$(expr substr $(uname -s) 1 10)" = "MINGW64_NT" ]; then
	XYO_PLATFORM="mingw64"
	XYO_OS="XYO_OS_WINDOWS"
	CC_LIB="-luser32 -lws2_32"
fi

DEF=""
DEF="$DEF -D$XYO_OS"
DEF="$DEF -DXYO_COMPILER_GCC"
DEF="$DEF -DXYO_APPLICATION_64BIT"
DEF="$DEF -DXYO_PLATFORM=$XYO_PLATFORM"
DEF="$DEF -DXYO_MULTI_THREAD"

INC=""
INC="$INC -Iinclude"
INC="$INC -Isource"

SRC=""
SRC="$SRC util/xyo.config.cpp"

cmdX gcc -o build/xyo.config -O1 -std=c++11 -std=gnu++11 $DEF $INC $SRC -lstdc++ -lpthread -lm
cmdX ./build/xyo.config

DEF=""
DEF="$DEF -DXYO_NO_VERSION"
DEF="$DEF -DXYO_CC_NO_VERSION"

SRC=""
SRC="$SRC util/xyo-cc/xyo-cc.cpp"
SRC="$SRC util/xyo-cc/xyo-cc-copyright.cpp"
SRC="$SRC util/xyo-cc/xyo-cc-license.cpp"
SRC="$SRC source/xyo.amalgam.cpp"

cmdX gcc -o build/xyo.cc -O1 -std=c++11 -std=gnu++11 $DEF $INC $SRC -lstdc++ -lpthread -lm $CC_LIB
cmdX build/xyo.cc --mode=$ACTION @util/xyo.static.compile.info
cmdX build/xyo.cc --mode=$ACTION @util/xyo.dynamic.compile.info
cmdX build/xyo.cc --mode=$ACTION --exe xyo.test.01 @util/xyo.test.compile.info
cmdX build/xyo.cc --mode=$ACTION --exe xyo.test.02 @util/xyo.test.compile.info
cmdX build/xyo.cc --mode=$ACTION --exe xyo.test.03 @util/xyo.test.compile.info
cmdX build/xyo.cc --mode=$ACTION --exe xyo.test.04 @util/xyo.test.compile.info

cmdX build/xyo.cc --mode=$ACTION @util/xyo-cc.compile.info

