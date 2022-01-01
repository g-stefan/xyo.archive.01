//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_APPLICATION_VERSION_HPP
#define XYO_APPLICATION_VERSION_HPP

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace Application {
		namespace Version {
			using namespace XYO::DataStructures;
			using namespace XYO::Encoding;

			XYO_EXPORT bool getVersion(const char *version, int &major, int &minor, int &patch, int &build);
			XYO_EXPORT String setVersion(int major, int minor, int patch, int build);

			enum {
				CompareMajor = 1,
				CompareMinor = 2,
				ComparePatch = 4,
				CompareBuild = 8,
				CompareMajorMinor = 3,
				CompareMajorMinorPatch = 7,
				CompareAll = 15
			};

			XYO_EXPORT bool compare(const char *versionA, const char *versionB, int &result, int type = CompareMajorMinorPatch);

		};
	};
};

#endif
