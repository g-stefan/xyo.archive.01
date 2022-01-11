//
// XYO CC
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_CC_COMPILER_HPP
#define XYO_CC_COMPILER_HPP

namespace XYOCC {
	using namespace XYO;

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

		int filterOptions(int options);

		String objFilename(
			const String &project,
			const String &fileName,
			const String &tmpPath,
			int options);

		bool cppToObj(
			int options,
			String cppFile,
			String objFile,
			TDynamicArray<String> &cppDefine,
			TDynamicArray<String> &incPath,
			bool echoCmd);

		bool makeObjToLib(
			String libName,
			String binPath,
			String libPath,
			String tmpPath,
			int options,
			TDynamicArray<String> &objFiles,
			String defFile,
			TDynamicArray<String> &libDependencyPath,
			TDynamicArray<String> &libDependency,
			String version,
			bool echoCmd,
			bool force = false);

		bool makeObjToExe(
			String exeName,
			String binPath,
			String tmpPath,
			int options,
			TDynamicArray<String> &objFiles,
			TDynamicArray<String> &libDependencyPath,
			TDynamicArray<String> &libDependency,
			bool echoCmd,
			bool force = false);

		bool rcToRes(
			String rcFile,
			String resFile,
			TDynamicArray<String> &rcDefine,
			TDynamicArray<String> &incPath,
			bool echoCmd);

		bool resToObj(
			String resFile,
			String objFile,
			bool echoCmd);

		bool makeRcToObj(
			String rcFile,
			String objFile,
			TDynamicArray<String> &rcDefine,
			TDynamicArray<String> &incPath,
			bool echoCmd,
			bool force = false);

		bool makeCppToLib(
			String libName,
			String binPath,
			String libPath,
			String tmpPath,
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

		bool makeCppToExe(
			String exeName,
			String binPath,
			String tmpPath,
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

		bool versionBuildBump(
			String versionIni,
			String projectName);

		bool versionPatchBump(
			String versionIni,
			String projectName);

		bool versionMinorBump(
			String versionIni,
			String projectName);

		bool versionMajorBump(
			String versionIni,
			String projectName);

		bool versionProcessTemplate(
			String versionIni,
			String projectName,
			String templateIn,
			String fileOut,
			size_t maxLineSize = 16384);

		bool versionSetVersion(
			String versionIni,
			String projectName,
			String version);

		bool versionProcess(
			String versionFile,
			String projectName,
			String sourcePath,
			String includePath,
			size_t maxLineSize = 16384);

		bool bumpVersionBuild(
			String versionFile,
			String projectName,
			String sourcePath,
			String includePath,
			size_t maxLineSize = 16384);

		bool bumpVersionPatch(
			String versionFile,
			String projectName,
			String sourcePath,
			String includePath,
			size_t maxLineSize = 16384);

		bool bumpVersionMinor(
			String versionFile,
			String projectName,
			String sourcePath,
			String includePath,
			size_t maxLineSize = 16384);

		bool bumpVersionMajor(
			String versionFile,
			String projectName,
			String sourcePath,
			String includePath,
			size_t maxLineSize = 16384);

		String getVersionHash(
			String versionFile,
			String projectName);

		String getVersion(
			String versionFile,
			String projectName);

		bool cToObj(
			String cppFile,
			String objFile,
			int options,
			TDynamicArray<String> &cDefine,
			TDynamicArray<String> &incPath,
			bool echoCmd);

		bool makeCToLib(
			String libName,
			String binPath,
			String libPath,
			String tmpPath,
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

		bool makeCToExe(
			String exeName,
			String binPath,
			String tmpPath,
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

		bool getFileNameLib(const String &fileName, String &out);
		bool getFileNameDll(const String &fileName, String &out, const String &version);
		bool getFileNameExe(const String &fileName, String &out);
		bool copyLib(const String &fileName, const String &file);
		bool copyDll(const String &fileName, const String &file, const String &version, const String &fileVersion);
		bool copyExe(const String &fileName, const String &file);
		bool copyLibToFolder(const String &fileName, const String &folder);
		bool copyDllToFolder(const String &fileName, const String &folder, const String &version);
		bool copyExeToFolder(const String &fileName, const String &folder);

		bool copyDllToFolderWithLib(
			const String &fileNameLib, const String &folderLib,
			const String &fileNameDll, const String &folderBin,
			const String &version);

		bool matchPlatform(const String &platform);
		String getPlatform();

		bool loadDependency(
			INIFile &dependencyInfo,
			const String &projectName,
			const String &localDependencyPath,
			TDynamicArray<String> &repositoryDependencyPath,
			bool isLoaded);

		bool saveDependency(
			INIFile &dependencyInfo,
			const String &projectName,
			const String &dependencyPath);

		bool joinDependency(
			INIFile &dependencyInfo,
			const String &projectName,
			INIFile &dependencyInfoSource,
			const String &projectNameSource);

		bool getDependency(
			INIFile &dependencyInfo,
			const String &projectName,
			const String &localDependencyPath,
			TDynamicArray<String> &repositoryDependencyPath,
			bool isLoaded);

		bool checkDependencyVersion(
			INIFile &projectDependency,
			const String &projectName,
			const String &localDependencyPath,
			TDynamicArray<String> &repositoryDependencyPath,
			bool &forceMake);

		bool copyDependency(
			const String &projectName,
			const String &localDependencyPath,
			TDynamicArray<String> &repositoryDependencyPath);

		String getPathRepository();

		String getPathRelease(
			const String &projectName,
			const String &versionFile,
			bool isRelease);

		String getPathReleaseVersion(
			const String &projectName,
			const String &releaseVersion,
			bool isRelease);

		bool loadVersionDependency(
			const String &versionFile,
			const String &projectName,
			TRedBlackTree<String, String> &versionDependency);

		bool checkVersionDependencyRecursive(
			TRedBlackTree<String, bool> &versionDependencyInfo,
			TRedBlackTree<String, String> &versionDependency,
			TDynamicArray<String> &repositoryDependencyPath);

		bool checkVersionDependency(
			TRedBlackTree<String, String> &versionDependency,
			TDynamicArray<String> &repositoryDependencyPath);

		bool setVersionDependency(
			TRedBlackTree<String, String> &versionDependency,
			TDynamicArray<String> &repositoryDependencyPath);

		bool saveVersionDependency(
			const String &versionFile,
			const String &projectName,
			TRedBlackTree<String, String> &versionDependency);

		bool updateVersionDependency(
			const String &versionFile,
			const String &projectName,
			TDynamicArray<String> &repositoryDependencyPath);

		bool versionMinorBumpIfVersionDependencyMismatch(
			const String &versionFile,
			const String &projectName,
			TDynamicArray<String> &repositoryDependencyPath);
	};

};

#endif

