//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_VERSION_HPP
#define XYO_VERSION_HPP

#define XYO_VERSION_ABCD                1,0,0,2
#define XYO_VERSION_STR                 "1.0.0"
#define XYO_VERSION_STR_BUILD           "2"
#define XYO_VERSION_STR_DATETIME        "2020-02-24 03:06:43"

#ifndef XYO_RC

#ifndef XYO__EXPORT_HPP
#include "xyo--export.hpp"
#endif

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

