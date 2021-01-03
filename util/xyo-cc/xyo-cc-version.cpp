//
// XYO CC
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-cc-version.hpp"

namespace XYOCC {
	namespace Version {

		static const char *version_ = "1.8.0";
		static const char *build_ = "27";
		static const char *versionWithBuild_ = "1.8.0.27";
		static const char *datetime_ = "2021-01-03 02:30:47";

		const char *version() {
			return version_;
		};
		const char *build() {
			return build_;
		};
		const char *versionWithBuild() {
			return versionWithBuild_;
		};
		const char *datetime() {
			return datetime_;
		};

	};
};

