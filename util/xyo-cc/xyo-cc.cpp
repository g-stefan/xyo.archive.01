//
// XYO CC
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo.hpp"
#include "xyo-cc-copyright.hpp"
#include "xyo-cc-license.hpp"

#ifndef XYO_CC_NO_VERSION
#include "xyo-cc-version.hpp"
#endif

namespace Main {

	using namespace XYO;

	class Application :
		public virtual IMain {
			XYO_DISALLOW_COPY_ASSIGN_MOVE(Application);
		public:

			inline Application() {};

			void showUsage();
			void showLicense();

			int main(int cmdN, char *cmdS[]);
	};

	void Application::showUsage() {
		printf("xyo-cc - c++ compiler command driver\n");
#ifndef XYO_CC_NO_VERSION
		printf("version %s build %s [%s]\n", XYOCC::Version::version(), XYOCC::Version::build(), XYOCC::Version::datetime());
#endif
		printf("%s\n\n", XYOCC::Copyright::fullCopyright());

		printf("%s",
			"options:\n"
			"    --license           show license\n"
		);
		printf("\n");
	};

	void Application::showLicense() {
		printf("%s", XYOCC::License::content());
	};

	int Application::main(int cmdN, char *cmdS[]) {
		int i;
		String opt;
		size_t optIndex;
		String optValue;

		bool makeExecutable = false;
		bool makeLibrary = false;
		bool makeDynamicLibrary = false;
		bool doBumpVersion = false;
		bool isRelease = true;
		bool modeIsVersion = false;
		bool doInstall = false;
		bool doInstallRelease = false;
		bool doInstallDev = false;
		bool noLib = false;
		bool noInc = false;
		bool dllVersion = false;
		bool licenseInfo = false;

		String workspacePath = Shell::getCwd();
		String projectName;
		String includePathX;
		String sourcePathX;
		String installProjectName;
		String installVersionFile;
		String installInc;

		int numThreads = 8;
		String binPath = workspacePath + "/bin";
		String buildPath = workspacePath + "/build";
		String libPath = workspacePath + "/lib";

		TDynamicArray<String> incPath;
		TDynamicArray<String> cppDefine;
		String defFile;
		TDynamicArray<String> libDependencyPath;
		TDynamicArray<String> libDependency;
		TDynamicArray<String> rcDefine;
		TDynamicArray<String> incPathRC;

		TDynamicArray<String> repositoryPathDependency;
		TDynamicArray<String> repositoryPathDependencyLib;

		int crtOption = CompilerOptions::CRTDynamic;
		int dllOption = CompilerOptions::None;
		String versionFile;
		String projectBase;

		String pathRepository = Shell::getEnv("XYO_PATH_REPOSITORY");
		if(pathRepository.length() == 0) {
			pathRepository = "../repository";
		};

		// first is the main repository
		repositoryPathDependency[repositoryPathDependency.length()] = pathRepository;

		String pathRepositoryLibrary = Shell::getEnv("XYO_PATH_REPOSITORY_LIBRARY");
		if(pathRepositoryLibrary.length() > 0) {
			String::explode(";", pathRepositoryLibrary, repositoryPathDependency);
		};

		size_t w;
		for(w = 0; w < repositoryPathDependency.length(); ++w) {
			repositoryPathDependencyLib[repositoryPathDependencyLib.length()] = repositoryPathDependency[w] + "/lib";
		};

		bool doMake = false;
		String cmdMake;

		bool doWriteDependency = false;

		INIFile projectDependency;
		INIFile projectDependencyStatic;

		if(cmdN < 2) {
			showUsage();
			return 0;
		};

		if(Shell::hasEnv("XYO_COMPILE_DEBUG")) {
			isRelease = false;
		};
		String::explode(" ", Shell::getEnv("XYO_COMPILE_DEFINE"), cppDefine);

		TDynamicArray<String> cmdLine;
		String content;
		int cmdNX;
		char **cmdSX;
		int m;

		for (i = 1; i < cmdN; ++i) {
			if (StringCore::beginWith(cmdS[i], "@")) {
				if(Shell::fileGetContents(&cmdS[i][1], content)) {
					Shell::mainArgsSet(content, cmdNX, cmdSX);
					for(m = 0; m < cmdNX; ++m) {
						cmdLine.push(cmdSX[m]);
					};
					Shell::mainArgsDelete(cmdNX, cmdSX);
					continue;
				};
				printf("Error: file not found - %s\n", &cmdS[i][1]);
				return 1;
			};
			cmdLine.push(cmdS[i]);
		};

		for (i = 0; i < cmdLine.length(); ++i) {
			if (StringCore::beginWith(cmdLine[i], "--")) {
				opt = cmdLine[i].index(2);
				optValue = "";
				if(String::indexOf(opt, "=", 0, optIndex)) {
					optValue = String::substring(opt, optIndex + 1);
					opt = String::substring(opt, 0, optIndex);
				};
				if (opt == "usage") {
					showUsage();
					return 0;
				};
				if (opt == "license") {
					showLicense();
					return 0;
				};
				if (opt == "bump-version") {
					doBumpVersion = true;
					continue;
				};
				if (opt == "debug") {
					isRelease = false;
					continue;
				};
				if (opt == "release") {
					isRelease = true;
					continue;
				};
				if (opt == "exe") {
					makeExecutable = true;
					continue;
				};
				if (opt == "lib") {
					makeLibrary = true;
					crtOption = CompilerOptions::CRTStatic;
					continue;
				};
				if (opt == "dll") {
					makeDynamicLibrary = true;
					crtOption = CompilerOptions::CRTDynamic;
					continue;
				};
				if (opt == "dll-x-static") {
					makeDynamicLibrary = true;
					crtOption = CompilerOptions::CRTStatic;
					dllOption = CompilerOptions::DynamicLibraryXStatic;
					continue;
				};
				if (opt == "crt-dynamic") {
					crtOption = CompilerOptions::CRTDynamic;
					continue;
				};
				if (opt == "crt-static") {
					crtOption = CompilerOptions::CRTStatic;
					continue;
				};
				if (opt == "source-is-separate") {
					includePathX = "include";
					sourcePathX = "source";
					continue;
				};
				if (opt == "include-path") {
					includePathX = optValue;
					continue;
				};
				if (opt == "source-path") {
					sourcePathX = optValue;
					continue;
				};
				if (opt == "use-path") {
					includePathX = optValue;
					sourcePathX = optValue;
					continue;
				};
				if (opt == "no-version") {
					doBumpVersion = false;
					continue;
				};
				if (opt == "dll-no-version") {
					dllVersion = false;
					continue;
				};
				if (opt == "dll-with-version") {
					dllVersion = true;
					continue;
				};
				if (opt == "mode") {
					if(optValue.length() == 0) {
						isRelease = true;
						if(Shell::hasEnv("XYO_COMPILE_DEBUG")) {
							isRelease = false;
						};
						continue;
					};
					if (optValue == "make") {
						isRelease = true;
						if(Shell::hasEnv("XYO_COMPILE_DEBUG")) {
							isRelease = false;
						};
						continue;
					};
					if (optValue == "release") {
						isRelease = true;
						continue;
					};
					if (optValue == "debug") {
						isRelease = false;
						continue;
					};
					if (optValue == "version") {
						doBumpVersion = true;
						modeIsVersion = true;
						continue;
					};
					if (optValue == "install") {
						isRelease = true;
						doInstall = true;
						if(Shell::hasEnv("XYO_COMPILE_DEBUG")) {
							isRelease = false;
						};
						continue;
					};
					if (optValue == "install-release") {
						isRelease = true;
						doInstallRelease = true;
						if(Shell::hasEnv("XYO_COMPILE_DEBUG")) {
							isRelease = false;
						};
						continue;
					};
					if (optValue == "test") {
						// test mode, nothing to do
						return 0;
					};
					if (optValue == "license-info") {
						licenseInfo=true;
						continue;
					};
					printf("Error: unknown mode %s\n", optValue.value());
					return 1;
				};
				if (opt == "no-install") {
					doInstall = false;
					doInstallRelease = false;
					continue;
				};
				if (opt == "workspace-path") {
					workspacePath = optValue;
					if(workspacePath.length() == 0) {
						printf("Error: workspace-path is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "bin-path") {
					binPath = optValue;
					if(binPath.length() == 0) {
						printf("Error: bin-path is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "build-path") {
					buildPath = optValue;
					if(buildPath.length() == 0) {
						printf("Error: build-path is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "lib-path") {
					libPath = optValue;
					if(libPath.length() == 0) {
						printf("Error: lib-path is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "threads") {
					sscanf(optValue.value(), "%d", &numThreads);
					continue;
				};
				if (opt == "inc") {
					incPath[incPath.length()] = optValue;
					if(incPath[incPath.length() - 1].length() == 0) {
						printf("Error: inc path is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "inc-repository") {
					incPath[incPath.length()] = pathRepository + "/include/" + optValue;
					if(incPath[incPath.length() - 1].length() == 0) {
						printf("Error: inc path is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "def") {
					cppDefine[cppDefine.length()] = optValue;
					if(cppDefine[cppDefine.length() - 1].length() == 0) {
						printf("Error: def parameter is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "rc-inc") {
					incPathRC[incPathRC.length()] = optValue;
					if(incPathRC[incPathRC.length() - 1].length() == 0) {
						printf("Error: rc-inc path is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "rc-def") {
					rcDefine[rcDefine.length()] = optValue;
					if(rcDefine[rcDefine.length() - 1].length() == 0) {
						printf("Error: rc-def parameter is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "use-lib-path") {
					libDependencyPath[libDependencyPath.length()] = optValue;
					if(libDependencyPath[libDependencyPath.length() - 1].length() == 0) {
						printf("Error: use-lib-path is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "use-lib") {
					libDependency[libDependency.length()] = optValue;
					if(libDependency[libDependency.length() - 1].length() == 0) {
						printf("Error: use-lib is empty\n");
						return 1;
					};
					if(String::endsWith(libDependency[libDependency.length() - 1], ".static")) {
						crtOption = CompilerOptions::CRTStatic;
					};
					INIFileX::insert(projectDependency, "project", "lib", optValue);
					continue;
				};
				if (opt == "use-lib-source") {
					if(optValue.length() == 0) {
						printf("Error: use-lib-source is empty\n");
						return 1;
					};
					libDependency[libDependency.length()] = Shell::getFileName(optValue);
					INIFileX::insert(projectDependency, "project", "lib", Shell::getFileName(optValue));
					if(String::endsWith(optValue, ".static")) {
						crtOption = CompilerOptions::CRTStatic;
						optValue = String::substring(optValue, 0, optValue.length() - strlen(".static"));
					};
					incPath[incPath.length()] = optValue + "/include";
					libDependencyPath[libDependencyPath.length()] = optValue + "/lib";
					continue;
				};
				if (opt == "use-lib-include") {
					if(optValue.length() == 0) {
						printf("Error: use-lib-include is empty\n");
						return 1;
					};
					if(String::endsWith(optValue, ".static")) {
						crtOption = CompilerOptions::CRTStatic;
						optValue = String::substring(optValue, 0, optValue.length() - strlen(".static"));
					};
					incPath[incPath.length()] = optValue + "/include";
					libDependencyPath[libDependencyPath.length()] = optValue + "/lib";
					continue;
				};
				if (opt == "use-project") {
					if(optValue.length() == 0) {
						printf("Error: use-project is empty\n");
						return 1;
					};
					INIFileX::insert(projectDependency, "project", "project", optValue);
					continue;
				};
				if (opt == "version-file") {
					versionFile = optValue;
					if(versionFile.length() == 0) {
						printf("Error: version-file is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "project-base") {
					projectBase = optValue;
					if(projectBase.length() == 0) {
						printf("Error: project-base is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "def-file") {
					defFile = optValue;
					if(defFile.length() == 0) {
						printf("Error: def-file is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "install-project") {
					installProjectName = optValue;
					if(installProjectName.length() == 0) {
						printf("Error: install-project is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "install-version-file") {
					installVersionFile = optValue;
					if(installVersionFile.length() == 0) {
						printf("Error: install-version-file is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "install-dev") {
					doInstallDev = true;
					continue;
				};
				if (opt == "install-inc") {
					installInc = optValue;
					if(installInc.length() == 0) {
						printf("Error: install-inc is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "make") {
					doMake = true;
					cmdMake = optValue;
					libDependency[libDependency.length()] = ":xyo.static";
					crtOption = CompilerOptions::CRTStatic;
					incPath[incPath.length()] = pathRepository + "/include/xyo";
					continue;
				};
				if (opt == "no-lib") {
					noLib = true;
					continue;
				};
				if (opt == "no-inc") {
					noInc = true;
					continue;
				};
				if (opt == "write-dependency") {
					doWriteDependency = true;
					continue;
				};
				if (opt == "dependency-set") {
					if(optValue.length() == 0) {
						printf("Error: dependency-set is empty\n");
						return 1;
					};
					String optKey;
					if(String::indexOf(optValue, "=", 0, optIndex)) {
						optKey = String::substring(optValue, 0, optIndex);
						optValue = String::substring(optValue, optIndex + 1);
					};
					if(optValue.length() == 0) {
						printf("Error: dependency-set - key is empty\n");
						return 1;
					};
					if(optKey.length() == 0) {
						printf("Error: dependency-set - value is empty\n");
						return 1;
					};
					INIFileX::insert(projectDependency, "project", optKey, optValue);
					continue;
				};
				if (opt == "dependency-license") {
					if(optValue.length() == 0) {
						printf("Error: dependency-license is empty\n");
						return 1;
					};
					if(projectName.length() == 0) {
						printf("Error: project name not specified\n");
						return 1;
					};
					INIFileX::insert(projectDependency, "project", "license", projectName + ":" + optValue);
					continue;
				};
				if (opt == "license-info") {
					licenseInfo=true;
					continue;
				};
				continue;
			};
			projectName = cmdLine[i];
		};

		if(projectName.length() == 0) {
			printf("Error: No project specified.\n");
			return 1;
		};

		if(projectBase.length() == 0) {
			projectBase = projectName;
		};

		if(versionFile.length() == 0) {
			if(sourcePathX.length() > 0) {
				versionFile = workspacePath + "/" + sourcePathX + "/" + projectBase + ".version.ini";
			} else {
				versionFile = workspacePath + "/" + projectBase + ".version.ini";
			};
		};

		String versionHash = Compiler::getVersionHash(versionFile, projectBase);
		INIFileX::insert(projectDependency, "project", "version.hash", versionHash);

		String libVersion;
		if(dllVersion) {
			libVersion = Compiler::getVersion(versionFile, projectBase);
		};

		// <dependency>

		bool forceMake = false;

		if(!INIFileX::renameSection(projectDependency, "project", projectName)) {
			printf("Error: internal dependency #1\n");
			return 1;
		};

		if(!INIFileX::joinSection(projectDependencyStatic, projectName + ".static", projectDependency, projectName)) {
			printf("Error: internal dependency #2\n");
			return 1;
		};

		if(doWriteDependency) {
			if(makeLibrary || makeDynamicLibrary) {
				Shell::mkdirRecursivelyIfNotExists(buildPath);
				Shell::mkdirRecursivelyIfNotExists(libPath);
				if(!INIFileX::save(buildPath + "/" + projectName + ".dependency.ini", projectDependency)) {
					printf("Error: write dependency %s\n", (buildPath + "/" + projectName + ".dependency.ini").value());
					return 1;
				};
				if(!INIFileX::save(libPath + "/" + projectName + ".dependency.ini", projectDependency)) {
					printf("Error: write dependency %s\n", (libPath + "/" + projectName + ".dependency.ini").value());
					return 1;
				};
			};
			return 0;
		};

		if(!Compiler::checkDependencyVersion(
				projectDependency,
				projectName,
				buildPath,
				repositoryPathDependencyLib,
				forceMake)) {
			printf("Error: check dependecy version\n");
			return 1;
		};

		if(forceMake) {
			if(!INIFileX::save(buildPath + "/" + projectName + ".dependency.ini", projectDependency)) {
				printf("Error: write dependency %s\n", (buildPath + "/" + projectName + ".dependency.ini").value());
				return 1;
			};
		};

		INIFile dependency;

		if(!INIFileX::joinSection(dependency, projectName, projectDependency, projectName)) {
			printf("Error: internal dependency #3\n");
			return 1;
		};

		if(!Compiler::getDependency(dependency, projectName, buildPath, repositoryPathDependencyLib, true)) {
			printf("Error: get dependency %s\n", (buildPath + "/" + projectName + ".dependency.ini").value());
			return 1;
		};

		TDynamicArray<String> dependecyList;
		size_t k;

		if(licenseInfo) {
			TRedBlackTreeOne<String> licenseList;
			TRedBlackTreeOne<String>::Node *scan;
			dependecyList.empty();
			INIFileX::getValues(dependency, projectName, "license", dependecyList);
			for(k = 0; k < dependecyList.length(); ++k) {
				licenseList.set(dependecyList[k]);
			};
			for(scan=licenseList.begin(); scan; scan=scan->successor()) {
				printf("%s\n", scan->key.value());
			};
			return 0;
		};

		dependecyList.empty();
		INIFileX::getValues(dependency, projectName, "project", dependecyList);
		for(k = 0; k < dependecyList.length(); ++k) {
			optValue = dependecyList[k];
			libDependency[libDependency.length()] = String(":") + optValue;
			if(String::endsWith(optValue, ".static")) {
				crtOption = CompilerOptions::CRTStatic;
				optValue = String::substring(optValue, 0, optValue.length() - strlen(".static"));
			};
			for(w = 0; w < repositoryPathDependency.length(); ++w) {
				if(Shell::directoryExists(repositoryPathDependency[w] + "/include/" + optValue)) {
					incPath[incPath.length()] = repositoryPathDependency[w] + "/include/" + optValue;
					break;
				};
			};
		};

		dependecyList.empty();
		INIFileX::getValues(dependency, projectName, "lib", dependecyList);
		for(k = 0; k < dependecyList.length(); ++k) {
			optValue = dependecyList[k];
			libDependency[libDependency.length()] = optValue;
			if(String::endsWith(optValue, ".static")) {
				crtOption = CompilerOptions::CRTStatic;
			};
		};

		dependecyList.empty();
		INIFileX::getValues(dependency, projectName, "inc", dependecyList);
		for(k = 0; k < dependecyList.length(); ++k) {
			optValue = dependecyList[k];
			for(w = 0; w < repositoryPathDependency.length(); ++w) {
				if(Shell::directoryExists(repositoryPathDependency[w] + "/include/" + optValue)) {
					incPath[incPath.length()] = repositoryPathDependency[w] + "/include/" + optValue;
					break;
				};
			};
		};

		dependecyList.empty();
		INIFileX::getValues(dependency, projectName, "rc.inc", dependecyList);
		for(k = 0; k < dependecyList.length(); ++k) {
			optValue = dependecyList[k];
			for(w = 0; w < repositoryPathDependency.length(); ++w) {
				if(Shell::directoryExists(repositoryPathDependency[w] + "/include/" + optValue)) {
					incPathRC[incPathRC.length()] = repositoryPathDependency[w] + "/include/" + optValue;
					break;
				};
			};
		};

		dependecyList.empty();
		INIFileX::getValues(dependency, projectName, "define", dependecyList);
		for(k = 0; k < dependecyList.length(); ++k) {
			optValue = dependecyList[k];
			if(optValue.length() > 0) {
				cppDefine[cppDefine.length()] = optValue;
			};
		};

		dependecyList.empty();
		INIFileX::getValues(dependency, projectName, "rc.define", dependecyList);
		for(k = 0; k < dependecyList.length(); ++k) {
			optValue = dependecyList[k];
			if(optValue.length() > 0) {
				rcDefine[rcDefine.length()] = optValue;
			};
		};

		// </dependency>

		String includePath;
		String sourcePath;

		includePath = workspacePath;
		if(includePathX.length() > 0) {
			includePath << "/" << includePathX;
		};

		sourcePath = workspacePath;
		if(sourcePathX.length() > 0) {
			sourcePath << "/" << sourcePathX;
		};

		if(doBumpVersion) {
			if(!Compiler::bumpVersion(
					versionFile,
					projectBase,
					sourcePath,
					includePath)) {
				printf("Error: version update fail\n");
				return 1;
			};
			return 0;
		};

		if(modeIsVersion) {
			return 0;
		};

		TDynamicArray<String> cSourceIn;
		TDynamicArray<String> hFilesIn;
		TDynamicArray<String> cppSourceIn;
		TDynamicArray<String> hppFilesIn;

		TDynamicArray<String> cSource;
		TDynamicArray<String> hFiles;
		TDynamicArray<String> cppSource;
		TDynamicArray<String> hppFiles;
		TDynamicArray<String> rcFiles;

		Shell::getFileList(includePath + "/" + projectBase + "*.h", hFilesIn);
		Shell::getFileList(sourcePath + "/" + projectBase + "*.c", cSourceIn);
		Shell::getFileList(includePath + "/" + projectBase + "*.hpp", hppFilesIn);
		Shell::getFileList(sourcePath + "/" + projectBase + "*.cpp", cppSourceIn);
		Shell::getFileList(sourcePath + "/" + projectBase + "*.rc", rcFiles);

		TDynamicArray<String> cSourceExtra;
		TDynamicArray<String> hFilesExtra;
		TDynamicArray<String> cppSourceExtra;
		TDynamicArray<String> hppFilesExtra;

		if(String::beginWith(projectName, "lib")) {
			String projectBaseX = String::substring(projectBase, 3);
			Shell::getFileList(includePath + "/" + projectBaseX + "*.h", hFilesExtra);
			Shell::getFileList(sourcePath + "/" + projectBaseX + "*.c", cSourceExtra);
			Shell::getFileList(includePath + "/" + projectBaseX + "*.hpp", hppFilesExtra);
			Shell::getFileList(sourcePath + "/" + projectBaseX + "*.cpp", cppSourceExtra);
		};

		// add extra

		for(k = 0; k < hFilesExtra.length(); ++k) {
			hFilesIn[hFilesIn.length()] = hFilesExtra[k];
		};
		for(k = 0; k < cSourceExtra.length(); ++k) {
			cSourceIn[cSourceIn.length()] = cSourceExtra[k];
		};
		for(k = 0; k < hppFilesExtra.length(); ++k) {
			hppFilesIn[hppFilesIn.length()] = hppFilesExtra[k];
		};
		for(k = 0; k < cppSourceExtra.length(); ++k) {
			cppSourceIn[cppSourceIn.length()] = cppSourceExtra[k];
		};

		// remove template/amalgam/source

		for(k = 0; k < hFilesIn.length(); ++k) {
			if(String::endsWith(hFilesIn[k], ".amalgam.h")) {
				continue;
			};
			if(String::endsWith(hFilesIn[k], ".template.h")) {
				continue;
			};
			// .source.h - internal header source
			if(String::endsWith(hFilesIn[k], ".source.h")) {
				hFiles[hFiles.length()] = hFilesIn[k];
				continue;
			};
			hFiles[hFiles.length()] = hFilesIn[k];
		};

		for(k = 0; k < cSourceIn.length(); ++k) {
			if(String::endsWith(cSourceIn[k], ".amalgam.c")) {
				continue;
			};
			if(String::endsWith(cSourceIn[k], ".template.c")) {
				continue;
			};
			// .source.c - internal source code, force build on change
			if(String::endsWith(cSourceIn[k], ".source.c")) {
				hFiles[hFiles.length()] = cSourceIn[k];
				continue;
			};
			cSource[cSource.length()] = cSourceIn[k];
		};

		for(k = 0; k < hppFilesIn.length(); ++k) {
			if(String::endsWith(hppFilesIn[k], ".amalgam.hpp")) {
				continue;
			};
			if(String::endsWith(hppFilesIn[k], ".template.hpp")) {
				continue;
			};
			// .source.hpp - internal header source
			if(String::endsWith(hppFilesIn[k], ".source.hpp")) {
				hppFiles[hppFiles.length()] = hppFilesIn[k];
				continue;
			};
			hppFiles[hppFiles.length()] = hppFilesIn[k];
		};

		for(k = 0; k < cppSourceIn.length(); ++k) {
			if(String::endsWith(cppSourceIn[k], ".amalgam.cpp")) {
				continue;
			};
			if(String::endsWith(cppSourceIn[k], ".template.cpp")) {
				continue;
			};
			// .source.cpp - internal source code, force build on change
			if(String::endsWith(cppSourceIn[k], ".source.cpp")) {
				hppFiles[hppFiles.length()] = cppSourceIn[k];
				continue;
			};
			cppSource[cppSource.length()] = cppSourceIn[k];
		};

		incPath[incPath.length()] = includePath;
		if(includePath != sourcePath) {
			incPath[incPath.length()] = sourcePath;
		};

		incPathRC[incPathRC.length()] = includePath;
		if(includePath != sourcePath) {
			incPathRC[incPathRC.length()] = sourcePath;
		};

		String defInternal = String::toUpperCaseAscii(projectBase) + "_INTERNAL";
		defInternal = String::replace(defInternal, "-", "_");
		defInternal = String::replace(defInternal, ".", "_");
		cppDefine[cppDefine.length()] = defInternal;
		if(String::beginWith(projectBase, "lib")) {
			cppDefine[cppDefine.length() - 1] = String::substring(cppDefine[cppDefine.length() - 1], 3);
		};

		libDependencyPath[libDependencyPath.length()] = libPath;

		// last is repository
		for(w = 0; w < repositoryPathDependency.length(); ++w) {
			incPath[incPath.length()] = repositoryPathDependency[w] + "/include";
			libDependencyPath[libDependencyPath.length()] = repositoryPathDependency[w] + "/lib";
			incPathRC[incPathRC.length()] = repositoryPathDependency[w] + "/include";
		};

		String pathInstall = pathRepository;
		String pathRelease;

		if(installVersionFile.length()==0) {
			installVersionFile=versionFile;
		};

		if(installProjectName.length()==0) {
			pathRelease = Compiler::getPathRelease(projectBase, installVersionFile, isRelease);
		} else {
			pathRelease = Compiler::getPathRelease(installProjectName, installVersionFile, isRelease);
		};

		if(doInstallRelease) {
			doInstall = true;
			pathInstall = pathRelease;
			pathInstall += "-dev";
		};

		if(makeLibrary) {
			if((cSource.length() == 0) && (cppSource.length() == 0)) {
				printf("Error: no c/cpp source for library %s\n", projectName.value());
				return 1;
			};
			if(cSource.length() > 0) {
				if(!Compiler::makeCToLib(
						projectName + ".static",
						binPath,
						libPath,
						buildPath,
						(isRelease ? CompilerOptions::Release : CompilerOptions::Debug) | crtOption | CompilerOptions::StaticLibrary,
						cppDefine,
						incPath,
						hFiles,
						cSource,
						rcDefine,
						incPathRC,
						rcFiles,
						defFile,
						libDependencyPath,
						libDependency,
						libVersion,
						numThreads,
						true,
						forceMake)) {
					printf("Error: building library %s\n", projectName.value());
					return 1;
				};
				if(!INIFileX::save(buildPath + "/" + projectName + ".static.dependency.ini", projectDependencyStatic)) {
					printf("Error: write dependency %s\n", (buildPath + "/" + projectName + ".static.dependency.ini").value());
					return 1;
				};
				if(!INIFileX::save(libPath + "/" + projectName + ".static.dependency.ini", projectDependencyStatic)) {
					printf("Error: write dependency %s\n", (libPath + "/" + projectName + ".static.dependency.ini").value());
					return 1;
				};
			};
			if(cppSource.length() > 0) {
				if(!Compiler::makeCppToLib(
						projectName + ".static",
						binPath,
						libPath,
						buildPath,
						(isRelease ? CompilerOptions::Release : CompilerOptions::Debug) | crtOption | CompilerOptions::StaticLibrary,
						cppDefine,
						incPath,
						hppFiles,
						cppSource,
						rcDefine,
						incPathRC,
						rcFiles,
						defFile,
						libDependencyPath,
						libDependency,
						libVersion,
						numThreads,
						true,
						forceMake)) {
					printf("Error: building library %s\n", projectName.value());
					return 1;
				};
				if(!INIFileX::save(buildPath + "/" + projectName + ".static.dependency.ini", projectDependencyStatic)) {
					printf("Error: write dependency %s\n", (buildPath + "/" + projectName + ".static.dependency.ini").value());
					return 1;
				};
				if(!INIFileX::save(libPath + "/" + projectName + ".static.dependency.ini", projectDependencyStatic)) {
					printf("Error: write dependency %s\n", (libPath + "/" + projectName + ".static.dependency.ini").value());
					return 1;
				};
			};
			if(doInstall) {
				if(!Compiler::copyLibToFolder(libPath + "/" + projectName + ".static", pathInstall + "/lib")) {
					printf("Error: copy file %s to %s\n", (libPath + "/" + projectName + ".static").value(), (pathInstall + "/lib").value());
					return 1;
				};
				if(!Shell::copyFileIfExists(libPath + "/" + projectName + ".static.dependency.ini",
						pathInstall + "/lib/" + projectName + ".static.dependency.ini")) {
					printf("Error: copy file %s to %s\n", (libPath + "/" + projectName + ".static.dependency.ini").value(),
						(pathInstall + "/lib/" + projectName + ".static.dependency.ini").value());
					return 1;
				};
				if(!noInc) {
					if(installInc.length()>0) {
						if(!Shell::copyDirRecursively(includePath, pathInstall + "/include/" + installInc)) {
							printf("Error: copy directory %s to %s\n", (includePath).value(), (pathInstall + "/include/" + installInc).value());
							return 1;
						};
					} else {
						if(!Shell::copyDirRecursively(includePath, pathInstall + "/include/" + projectName)) {
							printf("Error: copy directory %s to %s\n", (includePath).value(), (pathInstall + "/include/" + projectName).value());
							return 1;
						};
					};
				};
			};
		};

		if(makeDynamicLibrary) {
			if((cSource.length() == 0) && (cppSource.length() == 0)) {
				printf("Error: no c/cpp source for dynamic library %s\n", projectName.value());
				return 1;
			};
			if(cSource.length() > 0) {
				if(!Compiler::makeCToLib(
						projectName,
						binPath,
						libPath,
						buildPath,
						(isRelease ? CompilerOptions::Release : CompilerOptions::Debug) | crtOption | CompilerOptions::DynamicLibrary | dllOption,
						cppDefine,
						incPath,
						hFiles,
						cSource,
						rcDefine,
						incPathRC,
						rcFiles,
						defFile,
						libDependencyPath,
						libDependency,
						libVersion,
						numThreads,
						true,
						forceMake)) {
					printf("Error: building dynamic library %s\n", projectName.value());
					return 1;
				};
				if(!INIFileX::save(buildPath + "/" + projectName + ".dependency.ini", projectDependency)) {
					printf("Error: write dependency %s\n", (buildPath + "/" + projectName + ".dependency.ini").value());
					return 1;
				};
				if(!INIFileX::save(libPath + "/" + projectName + ".dependency.ini", projectDependency)) {
					printf("Error: write dependency %s\n", (libPath + "/" + projectName + ".dependency.ini").value());
					return 1;
				};
			};

			if(cppSource.length() > 0) {
				if(!Compiler::makeCppToLib(
						projectName,
						binPath,
						libPath,
						buildPath,
						(isRelease ? CompilerOptions::Release : CompilerOptions::Debug) | crtOption | CompilerOptions::DynamicLibrary | dllOption,
						cppDefine,
						incPath,
						hppFiles,
						cppSource,
						rcDefine,
						incPathRC,
						rcFiles,
						defFile,
						libDependencyPath,
						libDependency,
						libVersion,
						numThreads,
						true,
						forceMake)) {
					printf("Error: building dynamic library %s\n", projectName.value());
					return 1;
				};
				if(!INIFileX::save(buildPath + "/" + projectName + ".dependency.ini", projectDependency)) {
					printf("Error: write dependency %s\n", (buildPath + "/" + projectName + ".dependency.ini").value());
					return 1;
				};
				if(!INIFileX::save(libPath + "/" + projectName + ".dependency.ini", projectDependency)) {
					printf("Error: write dependency %s\n", (libPath + "/" + projectName + ".dependency.ini").value());
					return 1;
				};
			};
			if(doInstallRelease) {
				if(!Compiler::copyDllToFolder(binPath + "/" + projectName, pathRelease, libVersion)) {
					printf("Error: copy dll %s to folder %s\n", (binPath + "/" + projectName).value(), (pathRelease).value());
					return 1;
				};
			};
			if(doInstall) {
				if(noLib) {
					if(!Compiler::copyDllToFolder(binPath + "/" + projectName, pathInstall + "/bin", libVersion)) {
						printf("Error: copy dll %s to folder %s\n", (binPath + "/" + projectName).value(), (pathInstall + "/bin").value());
						return 1;
					};
				} else {
					if(!Compiler::copyDllToFolderWithLib(
							libPath + "/" + projectName, pathInstall + "/lib",
							binPath + "/" + projectName, pathInstall + "/bin",
							libVersion)) {
						printf("Error: copy dll %s to folder %s with lib\n", (binPath + "/" + projectName).value(), (pathInstall + "/bin").value());
						return 1;
					};
				};
				if(!Shell::copyFileIfExists(libPath + "/" + projectName + ".dependency.ini",
						pathInstall + "/lib/" + projectName + ".dependency.ini")) {
					printf("Error: copy file %s to %s\n", (libPath + "/" + projectName + ".dependency.ini").value(),
						(pathInstall + "/lib/" + projectName + ".dependency.ini").value());
					return 1;
				};
				if(!noLib) {
					if(installInc.length()>0) {
						if(!Shell::copyDirRecursively(includePath, pathInstall + "/include/" + installInc)) {
							printf("Error: copy directory %s to %s\n", (includePath).value(), (pathInstall + "/include/" + installInc).value());
							return 1;
						};
					} else {
						if(!Shell::copyDirRecursively(includePath, pathInstall + "/include/" + projectName)) {
							printf("Error: copy directory %s to %s\n", (includePath).value(), (pathInstall + "/include/" + projectName).value());
							return 1;
						};
					};
				};
			};
		};

		if(makeExecutable) {
			if((cSource.length() == 0) && (cppSource.length() == 0)) {
				printf("Error: no c/cpp source for executable %s\n", projectName.value());
				return 1;
			};
			if(cSource.length() > 0) {
				if(!Compiler::makeCToExe(
						projectName,
						doMake ? buildPath : binPath,
						buildPath,
						(isRelease ? CompilerOptions::Release : CompilerOptions::Debug) | crtOption,
						cppDefine,
						incPath,
						hFiles,
						cSource,
						rcDefine,
						incPathRC,
						rcFiles,
						libDependencyPath,
						libDependency,
						numThreads,
						true,
						forceMake)) {
					printf("Error: building executable %s\n", projectName.value());
					return 1;
				};
			};

			if(cppSource.length() > 0) {
				if(!Compiler::makeCppToExe(
						projectName,
						doMake ? buildPath : binPath,
						buildPath,
						(isRelease ? CompilerOptions::Release : CompilerOptions::Debug) | crtOption,
						cppDefine,
						incPath,
						hppFiles,
						cppSource,
						rcDefine,
						incPathRC,
						rcFiles,
						libDependencyPath,
						libDependency,
						numThreads,
						true,
						forceMake)) {
					printf("Error: building executable %s\n", projectName.value());
					return 1;
				};
			};
			if(doInstallRelease) {
				if(!Compiler::copyExeToFolder(binPath + "/" + projectName, pathRelease)) {
					printf("Error: copy exe %s to folder %s\n", (binPath + "/" + projectName).value(), (pathRelease).value());
					return 1;
				};
			};
			if((doInstall && (!doInstallRelease)) || doInstallDev) {
				if(!Compiler::copyExeToFolder(binPath + "/" + projectName, pathInstall + "/bin")) {
					printf("Error: copy exe %s to folder %s\n", (binPath + "/" + projectName).value(), (pathInstall + "/bin").value());
					return 1;
				};
			};
		};

		if(forceMake) {
			if(!Compiler::copyDependency(
					projectName,
					buildPath,
					repositoryPathDependencyLib)) {
				printf("Error: copy dependecy\n");
				return 1;
			};
		};

		if(doMake) {
			String cmd;
			if(!Compiler::getFileNameExe(buildPath + "/" + projectName, cmd)) {
				printf("Error: get filename exe %s\n", (buildPath + "/" + projectName).value());
				return 1;
			};
			cmd << " " << cmdMake;
			return Shell::execute(cmd);
		};

		return 0;
	};

};

XYO_APPLICATION_MAIN_STD(Main::Application);
