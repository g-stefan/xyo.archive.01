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

#define XYO_CC_VERSION_ABCD                3,3,0,78
#define XYO_CC_VERSION_STR                 "3.3.0"
#define XYO_CC_VERSION_STR_BUILD           "78"
#define XYO_CC_VERSION_STR_DATETIME        "2022-01-01 21:19:32"

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

