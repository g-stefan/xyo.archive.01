//
// XYO CC
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_CC_VERSION_HPP
#define XYO_CC_VERSION_HPP

#define XYO_CC_VERSION_ABCD                3,2,0,73
#define XYO_CC_VERSION_STR                 "3.2.0"
#define XYO_CC_VERSION_STR_BUILD           "73"
#define XYO_CC_VERSION_STR_DATETIME        "2021-11-15 16:51:47"

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

