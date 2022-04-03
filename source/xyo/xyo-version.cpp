//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-version.hpp"

namespace XYO {
	namespace Version {

		static const char *version_ = "6.1.0";
		static const char *build_ = "86";
		static const char *versionWithBuild_ = "6.1.0.86";
		static const char *datetime_ = "2022-04-04 01:15:52";

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
