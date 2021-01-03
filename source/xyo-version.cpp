//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-version.hpp"

namespace XYO {
	namespace Version {

		static const char *version_ = "3.4.0";
		static const char *build_ = "27";
		static const char *versionWithBuild_ = "3.4.0.27";
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
