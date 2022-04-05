//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_VERSION_HPP
#define XYO_VERSION_HPP

#define XYO_VERSION_ABCD 6,1,0,88
#define XYO_VERSION_STR "6.1.0"
#define XYO_VERSION_STR_BUILD "88"
#define XYO_VERSION_STR_DATETIME "2022-04-04 01:44:46"

#ifndef XYO_RC

#	ifndef XYO__EXPORT_HPP
#		include "xyo--export.hpp"
#	endif

namespace XYO {
	namespace Version {
		XYO_EXPORT const char *version();
		XYO_EXPORT const char *build();
		XYO_EXPORT const char *versionWithBuild();
		XYO_EXPORT const char *datetime();
	};
};

#endif
#endif
