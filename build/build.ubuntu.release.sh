#!/bin/sh
# Public domain
# http://unlicense.org/
# Created by Grigore Stefan <g_stefan@yahoo.com>

echo "-> release xyo"

cmdX(){
	if ! "$@" ; then
		echo "Error: release"
		exit 1
	fi
}

export XYO_PATH_RELEASE=release

cmdX /bin/sh ./build/build.ubuntu.sh make
cmdX /bin/sh ./build/build.ubuntu.sh install
cmdX /bin/sh ./build/build.ubuntu.sh install-release
cmdX ./temp/xyo.cc xyo --archive-release-sha512 --version-file=source/xyo.version.ini