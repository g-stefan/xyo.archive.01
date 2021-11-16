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

if [ -f "./temp/xyo.cc" ]; then
	if ! ./temp/xyo.cc xyo --has-archived-release --version-file=version.ini; then
		exit 0
	fi
fi
cmdX /bin/sh ./build/ubuntu.sh make
cmdX /bin/sh ./build/ubuntu.sh install
cmdX /bin/sh ./build/ubuntu.sh install-release
cmdX ./temp/xyo.cc xyo --archive-release-sha512 --version-file=version.ini
