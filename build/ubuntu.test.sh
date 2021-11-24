#!/bin/sh
# Public domain
# http://unlicense.org/
# Created by Grigore Stefan <g_stefan@yahoo.com>

echo "- $BUILD_PROJECT > test"

cmdX(){
	echo "-> $@"
	if ! "$@" ; then
		echo "Error: $@"
		exit 1
	fi
}

cd output/bin

cmdX ./xyo.test.01
cmdX ./xyo.test.02
cmdX ./xyo.test.03
cmdX ./xyo.test.04

cd ../..
