//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-system-compiler.hpp"
#include "xyo-system-shell.hpp"
#include "xyo-system-datetime.hpp"
#include "xyo-cryptography-md5.hpp"
#include "xyo-multithreading-workerqueue.hpp"
#include "xyo-datastructures-ini.hpp"
#include "xyo-encoding-string.hpp"

namespace XYO {
	namespace System {
		namespace Compiler {
			using namespace XYO::Cryptography;
			using namespace XYO::Multithreading;
			using namespace XYO::DataStructures;
			using namespace XYO::System;
			using namespace XYO::Encoding;

			int filterOptions(int options) {
				int retV = 0;
				if(options & CompilerOptions::Debug) {
					retV |= CompilerOptions::Debug;
				} else {
					retV |= CompilerOptions::Release;
				};
				if(options & CompilerOptions::CRTStatic) {
					retV |= CompilerOptions::CRTStatic;
				} else {
					retV |= CompilerOptions::CRTDynamic;
				};
				if(options & CompilerOptions::StaticLibrary) {
					retV |= CompilerOptions::StaticLibrary;
				} else {
					retV |= CompilerOptions::DynamicLibrary;
				};
				if(options & CompilerOptions::DynamicLibraryXStatic) {
					retV &= ~CompilerOptions::CRTDynamic;
					retV &= ~CompilerOptions::StaticLibrary;
					retV |= CompilerOptions::DynamicLibraryXStatic;
					retV |= CompilerOptions::DynamicLibrary;
					retV |= CompilerOptions::CRTStatic;
				};
				return retV;
			};

			bool versionBuildBump(
				String versionIni,
				String projectName) {
				INIFile versionInfo;
				String value;
				int versionBuild;
				char buf[32];
				DateTime now;
				if(INIFileX::load(versionIni, versionInfo)) {
					if(!INIFileX::get(versionInfo, projectName, "build", value)) {
						value = "0";
					};
					sscanf(value.value(), "%d", &versionBuild);
					++versionBuild;
					sprintf(buf, "%d", versionBuild);
					if(!INIFileX::set(versionInfo, projectName, "build", buf)) {
						return false;
					};
					sprintf(buf, "%04d-%02d-%02d", now.getYear(), now.getMonth(), now.getDay());
					if(!INIFileX::set(versionInfo, projectName, "date", buf)) {
						return false;
					};
					sprintf(buf, "%02d:%02d:%02d", now.getHour(), now.getMinute(), now.getSecond());
					if(!INIFileX::set(versionInfo, projectName, "time", buf)) {
						return false;
					};
					return INIFileX::save(versionIni, versionInfo);
				};
				return false;
			};

			bool versionProcessTemplate(
				String versionIni,
				String projectName,
				String templateIn,
				String fileOut,
				size_t maxLineSize) {
				INIFile versionInfo;
				TDynamicArray<TDynamicArray<String> > replace;
				String value;
				String datetime;
				char buf[64];
				DateTime now;
				replace[0][0] = "$VERSION_ABCD";
				replace[1][0] = "$VERSION_VERSION";
				replace[2][0] = "$VERSION_BUILD";
				replace[3][0] = "$VERSION_DATETIME";
				replace[0][1] = "0,0,0,0";
				replace[1][1] = "0.0.0";
				replace[2][1] = "0";

				int a, b, c, d;

				a = 0;
				b = 0;
				c = 0;
				d = 0;

				sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
					now.getYear(), now.getMonth(), now.getDay(),
					now.getHour(), now.getMinute(), now.getSecond());
				replace[3][1] = buf;

				if(INIFileX::load(versionIni, versionInfo)) {
					if(INIFileX::get(versionInfo, projectName, "version", value)) {
						replace[1][1] = value;
						sscanf(value.value(), "%d.%d.%d", &a, &b, &c);
					};
					if(INIFileX::get(versionInfo, projectName, "build", value)) {
						replace[2][1] = value;
						sscanf(value.value(), "%d", &d);
					};

					sprintf(buf, "%d,%d,%d,%d", a, b, c, d);
					replace[0][1] = buf;

					if(!INIFileX::get(versionInfo, projectName, "date", value)) {
						sprintf(buf, "%04d-%02d-%02d",
							now.getYear(), now.getMonth(), now.getDay());
						value = buf;
					};
					datetime = value;
					datetime += " ";
					if(!INIFileX::get(versionInfo, projectName, "time", value)) {
						sprintf(buf, "%02d:%02d:%02d",
							now.getHour(), now.getMinute(), now.getSecond());
						value = buf;
					};
					datetime += value;
					replace[3][1] = datetime;
					return Shell::fileReplaceText(
							templateIn,
							fileOut,
							replace,
							maxLineSize);
				};
				return false;
			};

			bool versionSetVersion(
				String versionIni,
				String projectName,
				String version) {
				INIFile versionInfo;
				char buf[32];
				DateTime now;
				if(INIFileX::load(versionIni, versionInfo)) {
					if(!INIFileX::set(versionInfo, projectName, "version", version)) {
						return false;
					};
					sprintf(buf, "%04d-%02d-%02d", now.getYear(), now.getMonth(), now.getDay());
					if(!INIFileX::set(versionInfo, projectName, "date", buf)) {
						return false;
					};
					sprintf(buf, "%02d:%02d:%02d", now.getHour(), now.getMinute(), now.getSecond());
					if(!INIFileX::set(versionInfo, projectName, "time", buf)) {
						return false;
					};
					return INIFileX::save(versionIni, versionInfo);
				};
				versionInfo.empty();
				if(!INIFileX::set(versionInfo, projectName, "version", version)) {
					return false;
				};
				if(!INIFileX::set(versionInfo, projectName, "build", "0")) {
					return false;
				};
				sprintf(buf, "%04d-%02d-%02d", now.getYear(), now.getMonth(), now.getDay());
				if(!INIFileX::set(versionInfo, projectName, "date", buf)) {
					return false;
				};
				sprintf(buf, "%02d:%02d:%02d", now.getHour(), now.getMinute(), now.getSecond());
				if(!INIFileX::set(versionInfo, projectName, "time", buf)) {
					return false;
				};
				return INIFileX::save(versionIni, versionInfo);
			};

			bool bumpVersion(
				String versionFile,
				String projectName,
				String sourcePath,
				String includePath,
				size_t maxLineSize) {
				if(!versionBuildBump(versionFile, projectName)) {
					if(!versionSetVersion(versionFile, projectName, "0.0.0")) {
						return false;
					};
				};
				if(!versionProcessTemplate(versionFile,
						projectName,
						sourcePath + "/" + projectName + "-version.template.hpp",
						includePath + "/" + projectName + "-version.hpp",
						maxLineSize)) {
					return false;
				};
				if(!versionProcessTemplate(versionFile,
						projectName,
						sourcePath + "/" + projectName + "-version.template.cpp",
						sourcePath + "/" + projectName + "-version.cpp",
						maxLineSize)) {
					return false;
				};
				return true;
			};

			String getVersionHash(
				String versionFile,
				String projectName) {
				INIFile versionInfo;
				String value;
				String hash;
				DateTime now;
				char buf[32];
				if(INIFileX::load(versionFile, versionInfo)) {
					if(!INIFileX::get(versionInfo, projectName, "version", value)) {
						value = "0.0.0";
					};
					hash = value;
					if(!INIFileX::get(versionInfo, projectName, "build", value)) {
						value = "0";
					};
					hash << "." << value;
					if(!INIFileX::get(versionInfo, projectName, "date", value)) {
						sprintf(buf, "%04d-%02d-%02d", now.getYear(), now.getMonth(), now.getDay());
						value = buf;
					};
					hash << "." << value;
					if(!INIFileX::get(versionInfo, projectName, "time", value)) {
						sprintf(buf, "%02d:%02d:%02d", now.getHour(), now.getMinute(), now.getSecond());
						value = buf;
					};
					hash << "." << value;
					return MD5::getHashString(hash);
				};
				hash = "0.0.0.0";
				sprintf(buf, "%04d-%02d-%02d", now.getYear(), now.getMonth(), now.getDay());
				hash << "." << buf;
				sprintf(buf, "%02d:%02d:%02d", now.getHour(), now.getMinute(), now.getSecond());
				hash << "." << buf;
				return MD5::getHashString(hash);
			};

			String getVersion(
				String versionFile,
				String projectName) {
				INIFile versionInfo;
				String value;
				if(INIFileX::load(versionFile, versionInfo)) {
					if(!INIFileX::get(versionInfo, projectName, "version", value)) {
						value = "0.0.0";
					};
					return value;
				};
				return "0.0.0";
			};

			bool matchPlatform(const String &platform) {

#ifdef XYO_PLATFORM_DEF
#define XYO_PLATFORM_STR_B(X) #X
#define XYO_PLATFORM_STR_A(X) XYO_PLATFORM_STR_B(X)
#define XYO_PLATFORM XYO_PLATFORM_STR_A(XYO_PLATFORM_DEF)
#endif

#ifdef XYO_PLATFORM
				return String::matchAscii(XYO_PLATFORM, platform);
#else
				return false;
#endif

			};

			String getPlatform() {
#ifdef XYO_PLATFORM
				return XYO_PLATFORM;
#else
				return "unknown";
#endif
			};

			bool loadDependency(
				INIFile &dependencyInfo,
				const String &projectName,
				const String &localDependencyPath,
				TDynamicArray<String> &repositoryDependencyPath,
				bool isLoaded) {
				if((INIFileX::hasSection(dependencyInfo, projectName)) && (!isLoaded)) {
					return true;
				};
				INIFile projectDependency;
				if(isLoaded) {
					if(!INIFileX::joinSection(projectDependency, projectName, dependencyInfo, projectName)) {
						return false;
					};
				} else {
					String fileName;
					fileName = localDependencyPath;
					fileName << "/" << projectName << ".dependency.ini";
					if(!INIFileX::load(fileName, projectDependency)) {
						projectDependency.empty();
						size_t k;
						for(k = 0; k < repositoryDependencyPath.length(); ++k) {
							fileName = repositoryDependencyPath[k];
							fileName << "/" << projectName << ".dependency.ini";
							if(INIFileX::load(fileName, projectDependency)) {
								break;
							};
						};
						if(k == repositoryDependencyPath.length()) {
							return true;
						};
					};
					if(!INIFileX::joinSection(dependencyInfo, projectName, projectDependency, projectName)) {
						return false;
					};
				};
				size_t items = INIFileX::count(projectDependency, projectName, "project");
				size_t k;
				String nextDependency;
				for(k = 0; k < items; ++k) {
					if(!INIFileX::get(projectDependency, projectName, "project", nextDependency, k)) {
						return false;
					};
					if(!loadDependency(dependencyInfo, nextDependency, localDependencyPath, repositoryDependencyPath, false)) {
						return false;
					};
				};
				return true;
			};

			bool saveDependency(
				INIFile &dependencyInfo,
				const String &projectName,
				const String &dependencyPath) {
				String fileName = dependencyPath;
				fileName << "/" << projectName << ".dependency.ini";
				INIFile projectDependency;
				INIFileX::joinSection(projectDependency, projectName, dependencyInfo, projectName);
				return INIFileX::save(fileName, projectDependency);
			};

			bool joinDependency(
				INIFile &dependencyInfo,
				const String &projectName,
				INIFile &dependencyInfoSource,
				const String &projectNameSource) {
				if(INIFileX::hasKeyWithValue(dependencyInfo, projectName, "project.loaded", projectNameSource)) {
					return true;
				};
				size_t items;
				items = INIFileX::count(dependencyInfo, projectName, "project.loaded");
				INIFileX::set(dependencyInfo, projectName, "project.loaded", projectNameSource, items);
				INIFileX::joinSection(dependencyInfo, projectName, dependencyInfoSource, projectNameSource);
				items = INIFileX::count(dependencyInfoSource, projectNameSource, "project");
				size_t k;
				String nextDependency;
				for(k = 0; k < items; ++k) {
					if(!INIFileX::get(dependencyInfoSource, projectNameSource, "project", nextDependency, k)) {
						return false;
					};
					if(!joinDependency(dependencyInfo, projectName, dependencyInfoSource, nextDependency)) {
						return false;
					};
				};
				return true;
			};

			bool getDependency(
				INIFile &dependencyInfo,
				const String &projectName,
				const String &localDependencyPath,
				TDynamicArray<String> &repositoryDependencyPath,
				bool isLoaded) {
				INIFile dependency;
				INIFile dependencyScan;
				if(isLoaded) {
					if(!INIFileX::joinSection(dependency, projectName, dependencyInfo, projectName)) {
						return false;
					};
				};
				if(!loadDependency(dependency, projectName, localDependencyPath, repositoryDependencyPath, isLoaded)) {
					return false;
				};
				if(!joinDependency(
						dependencyScan,
						projectName,
						dependency,
						projectName)) {
					return false;
				};
				for(;;) {
					if(!INIFileX::removeKey(dependencyScan, projectName, "project.loaded", 0)) {
						break;
					};
				};
				size_t index;
				if(!INIFileX::sectionIndex(dependencyScan, projectName, index)) {
					return false;
				};
				for(++index; index < dependencyScan.length(); ++index) {
					if(dependencyScan[index].type == INILineType::Value) {
						if(!INIFileX::hasKeyWithValue(dependencyInfo, projectName, dependencyScan[index].key, dependencyScan[index].value)) {
							INIFileX::insert(dependencyInfo, projectName, dependencyScan[index].key, dependencyScan[index].value);
						};
					};
				};
				return true;
			};

			bool checkDependencyVersion(
				INIFile &projectDependency,
				const String &projectName,
				const String &localDependencyPath,
				TDynamicArray<String> &repositoryDependencyPath,
				bool &forceMake) {
				INIFile localDependency;
				INIFile localDependencyScan;
				if(!INIFileX::joinSection(localDependency, projectName, projectDependency, projectName)) {
					return false;
				};
				if(!loadDependency(localDependency, projectName, localDependencyPath, repositoryDependencyPath, true)) {
					return false;
				};
				if(!INIFileX::joinSection(localDependencyScan, projectName, projectDependency, projectName)) {
					return false;
				};
				if(!getDependency(localDependencyScan, projectName, localDependencyPath, repositoryDependencyPath, true)) {
					return false;
				};
				forceMake = false;
				INIFile repositoryDependency;
				size_t items;
				items = INIFileX::count(localDependencyScan, projectName, "project");
				size_t k, m;
				String project;
				String version;
				for(k = 0; k < items; ++k) {
					if(!INIFileX::get(localDependencyScan, projectName, "project", project, k)) {
						return false;
					};
					if(!Shell::fileExists(localDependencyPath + "/" + project + ".dependency.ini")) {
						for(m = 0; m < repositoryDependencyPath.length(); ++m) {
							if(Shell::fileExists(repositoryDependencyPath[m] + "/" + project + ".dependency.ini")) {
								if(!Shell::copyFile(repositoryDependencyPath[m] + "/" + project + ".dependency.ini",
										localDependencyPath + "/" + project + ".dependency.ini")) {
									return false;
								};
							};
						};
					};
					for(m = 0; m < repositoryDependencyPath.length(); ++m) {
						repositoryDependency.empty();
						if(INIFileX::load(repositoryDependencyPath[m] + "/" + project + ".dependency.ini", repositoryDependency)) {
							String versionA;
							String versionB;
							if(!INIFileX::get(localDependency, project, "version.hash", versionA, 0)) {
								return false;
							};
							if(!INIFileX::get(repositoryDependency, project, "version.hash", versionB, 0)) {
								return false;
							};
							if(versionA != versionB) {
								forceMake = true;
							};
							break;
						};
					};
				};
				return true;
			};

			bool copyDependency(
				const String &projectName,
				const String &localDependencyPath,
				TDynamicArray<String> &repositoryDependencyPath) {
				INIFile localDependency;
				INIFile repositoryDependency;
				if(!getDependency(localDependency, projectName, localDependencyPath, repositoryDependencyPath, false)) {
					return false;
				};
				size_t items;
				items = INIFileX::count(localDependency, projectName, "project");
				size_t k, m;
				String project;
				for(k = 0; k < items; ++k) {
					if(!INIFileX::get(localDependency, projectName, "project", project, k)) {
						return false;
					};
					for(m = 0; m < repositoryDependencyPath.length(); ++m) {
						if(Shell::fileExists(repositoryDependencyPath[m] + "/" + project + ".dependency.ini")) {
							if(!Shell::copyFile(repositoryDependencyPath[m] + "/" + project + ".dependency.ini",
									localDependencyPath + "/" + project + ".dependency.ini")) {
								return false;
							};
						};
					};
				};
				return true;
			};

			String getPathRepository() {
				String pathRepository = Shell::getEnv("XYO_PATH_REPOSITORY");
				if(pathRepository.length() == 0) {
					pathRepository = "./repository";
				};
				return pathRepository;
			};

			String getPathRelease(
				const String &projectName,
				const String &versionFile,
				bool isRelease) {
				String pathRelease = Shell::getEnv("XYO_PATH_RELEASE");
				if(pathRelease.length() == 0) {
					pathRelease = "./release";
				};
				String releaseVersion = getVersion(versionFile, projectName);
				pathRelease += "/";
				pathRelease += projectName;
				pathRelease += "-";
				pathRelease += releaseVersion;
				String releasePlatform = getPlatform();
				pathRelease += "-";
				pathRelease += releasePlatform;
				if(!isRelease) {
					pathRelease += "-";
					pathRelease += "debug";
				};
				return pathRelease;
			};

			String getPathReleaseVersion(
				const String &projectName,
				const String &releaseVersion,
				bool isRelease) {
				String pathRelease = Shell::getEnv("XYO_PATH_RELEASE");
				if(pathRelease.length() == 0) {
					pathRelease = "./release";
				};
				pathRelease += "/";
				pathRelease += projectName;
				pathRelease += "-";
				pathRelease += releaseVersion;
				String releasePlatform = getPlatform();
				pathRelease += "-";
				pathRelease += releasePlatform;
				if(!isRelease) {
					pathRelease += "-";
					pathRelease += "debug";
				};
				return pathRelease;
			};

		};
	};
};


