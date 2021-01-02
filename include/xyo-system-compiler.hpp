//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_SYSTEM_COMPILER_HPP
#define XYO_SYSTEM_COMPILER_HPP

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TDYNAMICARRAY_HPP
#include "xyo-datastructures-tdynamicarray.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_INI_HPP
#include "xyo-datastructures-ini.hpp"
#endif

namespace XYO {
	namespace System {
		using namespace XYO::DataStructures;
		using namespace XYO::Encoding;

		namespace CompilerOptions {
			enum {
				None = 0,
				Release = 1,
				Debug = 2,
				CRTDynamic = 4,
				CRTStatic = 8,
				StaticLibrary = 16,
				DynamicLibrary = 32,
				DynamicLibraryXStatic = 64
			};
		};

		namespace Compiler {

			XYO_EXPORT int filterOptions(int options);

			XYO_EXPORT String objFilename(
				const String &project,
				const String &fileName,
				const String &buildPath,
				int options);

			XYO_EXPORT bool cppToObj(
				int options,
				String cppFile,
				String objFile,
				TDynamicArray<String> &cppDefine,
				TDynamicArray<String> &incPath,
				bool echoCmd);

			XYO_EXPORT bool makeObjToLib(
				String libName,
				String binPath,
				String libPath,
				String buildPath,
				int options,
				TDynamicArray<String> &objFiles,
				String defFile,
				TDynamicArray<String> &libDependencyPath,
				TDynamicArray<String> &libDependency,
				String version,
				bool echoCmd,
				bool force = false);

			XYO_EXPORT bool makeObjToExe(
				String exeName,
				String binPath,
				String buildPath,
				int options,
				TDynamicArray<String> &objFiles,
				TDynamicArray<String> &libDependencyPath,
				TDynamicArray<String> &libDependency,
				bool echoCmd,
				bool force = false);

			XYO_EXPORT bool rcToRes(
				String rcFile,
				String resFile,
				TDynamicArray<String> &rcDefine,
				TDynamicArray<String> &incPath,
				bool echoCmd);

			XYO_EXPORT bool resToObj(
				String resFile,
				String objFile,
				bool echoCmd);

			XYO_EXPORT bool makeRcToObj(
				String rcFile,
				String objFile,
				TDynamicArray<String> &rcDefine,
				TDynamicArray<String> &incPath,
				bool echoCmd,
				bool force = false);

			XYO_EXPORT bool makeCppToLib(
				String libName,
				String binPath,
				String libPath,
				String buildPath,
				int options,
				TDynamicArray<String> &cppDefine,
				TDynamicArray<String> &incPath,
				TDynamicArray<String> &incFiles,
				TDynamicArray<String> &cppFiles,
				TDynamicArray<String> &rcDefine,
				TDynamicArray<String> &incPathRC,
				TDynamicArray<String> &rcFiles,
				String defFile,
				TDynamicArray<String> &libDependencyPath,
				TDynamicArray<String> &libDependency,
				String version,
				int numThreads,
				bool echoCmd,
				bool force = false);

			XYO_EXPORT bool makeCppToExe(
				String exeName,
				String binPath,
				String buildPath,
				int options,
				TDynamicArray<String> &cppDefine,
				TDynamicArray<String> &incPath,
				TDynamicArray<String> &incFiles,
				TDynamicArray<String> &cppFiles,
				TDynamicArray<String> &rcDefine,
				TDynamicArray<String> &incPathRC,
				TDynamicArray<String> &rcFiles,
				TDynamicArray<String> &libDependencyPath,
				TDynamicArray<String> &libDependency,
				int numThreads,
				bool echoCmd,
				bool force = false);

			XYO_EXPORT bool versionBuildBump(
				String versionIni,
				String projectName);

			XYO_EXPORT bool versionPatchBump(
				String versionIni,
				String projectName);

			XYO_EXPORT bool versionMinorBump(
				String versionIni,
				String projectName);

			XYO_EXPORT bool versionMajorBump(
				String versionIni,
				String projectName);

			XYO_EXPORT bool versionProcessTemplate(
				String versionIni,
				String projectName,
				String templateIn,
				String fileOut,
				size_t maxLineSize = 16384);

			XYO_EXPORT bool versionSetVersion(
				String versionIni,
				String projectName,
				String version);

			XYO_EXPORT bool bumpVersionBuild(
				String versionFile,
				String projectName,
				String sourcePath,
				String includePath,
				size_t maxLineSize = 16384);

			XYO_EXPORT bool bumpVersionPatch(
				String versionFile,
				String projectName,
				String sourcePath,
				String includePath,
				size_t maxLineSize = 16384);

			XYO_EXPORT bool bumpVersionMinor(
				String versionFile,
				String projectName,
				String sourcePath,
				String includePath,
				size_t maxLineSize = 16384);

			XYO_EXPORT bool bumpVersionMajor(
				String versionFile,
				String projectName,
				String sourcePath,
				String includePath,
				size_t maxLineSize = 16384);

			XYO_EXPORT String getVersionHash(
				String versionFile,
				String projectName);

			XYO_EXPORT String getVersion(
				String versionFile,
				String projectName);

			XYO_EXPORT bool cToObj(
				String cppFile,
				String objFile,
				int options,
				TDynamicArray<String> &cDefine,
				TDynamicArray<String> &incPath,
				bool echoCmd);

			XYO_EXPORT bool makeCToLib(
				String libName,
				String binPath,
				String libPath,
				String buildPath,
				int options,
				TDynamicArray<String> &cDefine,
				TDynamicArray<String> &incPath,
				TDynamicArray<String> &incFiles,
				TDynamicArray<String> &cFiles,
				TDynamicArray<String> &rcDefine,
				TDynamicArray<String> &incPathRC,
				TDynamicArray<String> &rcFiles,
				String defFile,
				TDynamicArray<String> &libDependencyPath,
				TDynamicArray<String> &libDependency,
				String version,
				int numThreads,
				bool echoCmd,
				bool force = false);

			XYO_EXPORT bool makeCToExe(
				String exeName,
				String binPath,
				String buildPath,
				int options,
				TDynamicArray<String> &cDefine,
				TDynamicArray<String> &incPath,
				TDynamicArray<String> &incFiles,
				TDynamicArray<String> &cFiles,
				TDynamicArray<String> &rcDefine,
				TDynamicArray<String> &incPathRC,
				TDynamicArray<String> &rcFiles,
				TDynamicArray<String> &libDependencyPath,
				TDynamicArray<String> &libDependency,
				int numThreads,
				bool echoCmd,
				bool force = false);

			XYO_EXPORT bool getFileNameLib(const String &fileName, String &out);
			XYO_EXPORT bool getFileNameDll(const String &fileName, String &out, const String &version);
			XYO_EXPORT bool getFileNameExe(const String &fileName, String &out);
			XYO_EXPORT bool copyLib(const String &fileName, const String &file);
			XYO_EXPORT bool copyDll(const String &fileName, const String &file, const String &version, const String &fileVersion);
			XYO_EXPORT bool copyExe(const String &fileName, const String &file);
			XYO_EXPORT bool copyLibToFolder(const String &fileName, const String &folder);
			XYO_EXPORT bool copyDllToFolder(const String &fileName, const String &folder, const String &version);
			XYO_EXPORT bool copyExeToFolder(const String &fileName, const String &folder);

			XYO_EXPORT bool copyDllToFolderWithLib(
				const String &fileNameLib, const String &folderLib,
				const String &fileNameDll, const String &folderBin,
				const String &version);

			XYO_EXPORT bool matchPlatform(const String &platform);
			XYO_EXPORT String getPlatform();

			XYO_EXPORT bool loadDependency(
				INIFile &dependencyInfo,
				const String &projectName,
				const String &localDependencyPath,
				TDynamicArray<String> &repositoryDependencyPath,
				bool isLoaded);

			XYO_EXPORT bool saveDependency(
				INIFile &dependencyInfo,
				const String &projectName,
				const String &dependencyPath);

			XYO_EXPORT bool joinDependency(
				INIFile &dependencyInfo,
				const String &projectName,
				INIFile &dependencyInfoSource,
				const String &projectNameSource);

			XYO_EXPORT bool getDependency(
				INIFile &dependencyInfo,
				const String &projectName,
				const String &localDependencyPath,
				TDynamicArray<String> &repositoryDependencyPath,
				bool isLoaded);

			XYO_EXPORT bool checkDependencyVersion(
				INIFile &projectDependency,
				const String &projectName,
				const String &localDependencyPath,
				TDynamicArray<String> &repositoryDependencyPath,
				bool &forceMake);

			XYO_EXPORT bool copyDependency(
				const String &projectName,
				const String &localDependencyPath,
				TDynamicArray<String> &repositoryDependencyPath);

			XYO_EXPORT String getPathRepository();

			XYO_EXPORT String getPathRelease(
				const String &projectName,
				const String &versionFile,
				bool isRelease);

			XYO_EXPORT String getPathReleaseVersion(
				const String &projectName,
				const String &releaseVersion,
				bool isRelease);
		};

	};
};

#endif

