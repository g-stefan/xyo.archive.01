//
// XYO CC
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_CC_VERSION_HPP
#define XYO_CC_VERSION_HPP

#define XYO_CC_VERSION_ABCD 3,5,0,101
#define XYO_CC_VERSION_STR "3.5.0"
#define XYO_CC_VERSION_STR_BUILD "101"
#define XYO_CC_VERSION_STR_DATETIME "2022-06-23 14:48:15"

#ifndef XYO_RC

namespace XYOCC {
	namespace Version {
		const char *version();
		const char *build();
		const char *versionWithBuild();
		const char *datetime();
	};
};

#endif
#endif
