//
// XYO CC
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_CC_VERSION_HPP
#define XYO_CC_VERSION_HPP

#define XYO_CC_VERSION_ABCD                1,2,0,6
#define XYO_CC_VERSION_STR                 "1.2.0"
#define XYO_CC_VERSION_STR_BUILD           "6"
#define XYO_CC_VERSION_STR_DATETIME        "2020-08-19 11:59:55"

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

