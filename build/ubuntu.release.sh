#!/bin/sh
# Public domain
# http://unlicense.org/
# Created by Grigore Stefan <g_stefan@yahoo.com>

echo "- $BUILD_PROJECT > release"

cmdX(){
	if ! "$@" ; then
		echo "Error: release"
		exit 1
	fi
}

export XYO_PATH_RELEASE_ORIGINAL=$XYO_PATH_RELEASE
export XYO_PATH_RELEASE=release

if [ -f "./temp/xyo.cc" ]; then
	if ! ./temp/xyo.cc $BUILD_PROJECT --has-archived-release --version-file=version.ini; then
		exit 0
	fi
fi
cmdX /bin/sh ./build/ubuntu.sh make
cmdX /bin/sh ./build/ubuntu.sh install
cmdX /bin/sh ./build/ubuntu.sh install-release
cmdX ./temp/xyo.cc $BUILD_PROJECT --archive-release-sha512 --version-file=version.ini
export XYO_PATH_RELEASE=$XYO_PATH_RELEASE_ORIGINAL
cmdX ./temp/xyo.cc $BUILD_PROJECT --copy-local-archived-release --version-file=version.ini
