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

#define XYO_CC_VERSION_ABCD                2,0,0,38
#define XYO_CC_VERSION_STR                 "2.0.0"
#define XYO_CC_VERSION_STR_BUILD           "38"
#define XYO_CC_VERSION_STR_DATETIME        "2021-03-04 02:42:21"

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

