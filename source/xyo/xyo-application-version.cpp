//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-application-version.hpp"

namespace XYO {
	namespace Application {
		namespace Version {
			using namespace XYO::DataStructures;

			bool getVersion(const char *version, int &major, int &minor, int &patch, int &build) {
				return (sscanf(version, "%d.%d.%d.%d", &major, &minor, &patch, &build) == 4);
			};

			String setVersion(int major, int minor, int patch, int build) {
				String retV;
				char buffer[32];
				sprintf(buffer, "%d", major);
				retV += buffer;
				retV += ".";
				sprintf(buffer, "%d", minor);
				retV += buffer;
				retV += ".";
				sprintf(buffer, "%d", patch);
				retV += buffer;
				retV += ".";
				sprintf(buffer, "%d", build);
				retV += buffer;
				return retV;
			};

			bool compare(const char *versionA, const char *versionB, int &result, int type) {
				int majorA, majorB;
				int minorA, minorB;
				int patchA, patchB;
				int buildA, buildB;

				majorA = 0;
				majorB = 0;
				minorA = 0;
				minorB = 0;
				patchA = 0;
				patchB = 0;
				buildA = 0;
				buildB = 0;

				if(!getVersion(versionA, majorA, minorA, patchA, buildA)) {
					return false;
				};
				if(!getVersion(versionB, majorB, minorB, patchB, buildB)) {
					return false;
				};

				if(type & CompareMajor) {

					if(majorA < majorB) {
						result = -1;
						return true;
					};

					if(majorA > majorB) {
						result = 1;
						return true;
					};

				};

				if(type & CompareMinor) {

					if(minorA < minorB) {
						result = -1;
						return true;
					};

					if(minorA > minorB) {
						result = 1;
						return true;
					};

				};

				if(type & ComparePatch) {

					if(patchA < patchB) {
						result = -1;
						return true;
					};

					if(patchA > patchB) {
						result = 1;
						return true;
					};

				};

				if(type & CompareBuild) {

					if(buildA < buildB) {
						result = -1;
						return true;
					};

					if(buildA > buildB) {
						result = 1;
						return true;
					};

				};

				result = 0;
				return true;
			};

		};
	};
};

