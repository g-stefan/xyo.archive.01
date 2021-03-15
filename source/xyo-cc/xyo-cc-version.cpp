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

		static const char *version_ = "3.0.0";
		static const char *build_ = "48";
		static const char *versionWithBuild_ = "3.0.0.48";
		static const char *datetime_ = "2021-03-15 12:30:20";

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

