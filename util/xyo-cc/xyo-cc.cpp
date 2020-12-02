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

			void showVersion();
			void showUsage();
			void showLicense();

			int main(int cmdN, char *cmdS[]);
	};

	void Application::showVersion() {
		printf("xyo-cc - c++ compiler command driver\n");
#ifndef XYO_CC_NO_VERSION
		printf("version %s build %s [%s]\n", XYOCC::Version::version(), XYOCC::Version::build(), XYOCC::Version::datetime());
#endif
		printf("%s\n\n", XYOCC::Copyright::fullCopyright());
	};

	void Application::showLicense() {
		printf("%s", XYOCC::License::content());
	};

	void Application::showUsage() {
		showVersion();

		printf("%s",
			"options:\n"
			"    --version                      show version\n"
			"    --license                      show license\n"
			"    --usage                        this info\n"
			"    --bump-version                 increment version build number\n"
			"    --bump-version-build           increment version build number\n"
			"    --bump-version-patch           increment version patch number\n"
			"    --bump-version-minor           increment version minor number\n"
			"    --bump-version-major           increment version major number\n"
			"    --debug                        build debug version\n"
			"    --release                      build release version\n"
			"    --exe                          build executable (.exe)\n"
			"    --lib                          build library (.lib)\n"
			"    --dll                          build dynamic library (.dll)\n"
			"    --dll-x-static                 build dynamic library with static linking (.dll)\n"
			"    --crt-dynamic                  build using dynamic crt (default for dll)\n"
			"    --crt-static                   build using static crt (default for lib)\n"
			"    --source-is-separate           source code is separated in include and source folders\n"
			"    --include-path=path            folder where include files (.hpp/.h) are stored\n"
			"    --source-path=path             folder where source files (.cpp/.c) are stored\n"
			"    --use-path=path                folder where source files (.cpp/.c) are stored\n"
			"    --no-version                   do not bump version\n"
			"    --dll-no-version               generate dll without version number in name\n"
			"    --dll-with-version             generate dll with version number in name\n"
			"\n"
			"    --mode=[mode]                  compile using mode as reference:\n"
			"        [empty] or make            - build release or debug if XYO_COMPILE_DEBUG is defined in environment\n"
			"        release                    - build release\n"
			"        debug                      - build debug\n"
			"        version                    - bump version build\n"
			"        version-build              - bump version build\n"
			"        version-patch              - bump version patch\n"
			"        version-minor              - bump version minor\n"
			"        version-major              - bump version major\n"
			"        install                    - install to repository\n"
			"        install-release            - install to release repository\n"
			"        test                       - do nothing (return)\n"
			"        license-info               - show license dependency\n"
			"        archive                    - archive source, works only if --source-archive present, ignored otherwise\n"
			"        extract                    - extract source from archive, works only if --source-extract present, ignored otherwise\n"
			"\n"
			"    --no-install                   do not perform any install\n"
			"    --workspace-path=path          workspace path to use, default is current folder\n"
			"    --bin-path=path                location to bin folder, default to workspace/bin\n"
			"    --build-path=path              location to build folder, default to workspace/build\n"
			"    --lib-path=path                location to lib folder, default to workspace/lib\n"
			"    --threads=count                specify number of threads to use\n"
			"    --inc=path                     add path to include in search\n"
			"    --inc-repository=path          add path to include in search from repository/include/path\n"
			"    --def=value                    add value to definitions\n"
			"    --rc-inc=path                  add path to resource compiler include\n"
			"    --rc-def=value                 add value to resource compiler definitions\n"
			"    --use-lib-path=path            add path to library search\n"
			"    --use-lib=library              add library to linker\n"
			"    --use-lib-source=library       add library dependency, include path and lib path\n"
			"    --use-lib-include=library      add library include path and lib path\n"
			"    --use-project=project          add project to dependency\n"
			"    --version-file=file            use file for version info\n"
			"    --project-base=project         use project as base name\n"
			"    --def-file=file                use file for linker definitions (.dll)\n"
			"    --install-project=project      use project as name for install\n"
			"    --install-version-file=file    use file as version for project install\n"
			"    --install-dev                  install as dev (bin + include + lib)\n"
			"    --install-inc=path             use path for include install\n"
			"    --make                         build project using static crt runtime and default xyo library dependency\n"
			"    --no-lib                       do not generate library files (.lib), for use with dll\n"
			"    --no-inc                       do not install include folder, for use with dll\n"
			"    --write-dependency             generate a dependency file\n"
			"    --dependency-set=value         add value to dependency file\n"
			"    --dependency-license=value     add value to dependency license info\n"
			"    --license-info                 show license info\n"
			"    --lib-name=name                use name for static library\n"
			"    --src-h=file                   add file as h source\n"
			"    --src-c=file                   add file as c source\n"
			"    --src-hpp=file                 add file as hpp source\n"
			"    --src-cpp=file                 add file as cpp source\n"
			"    --src-rc=file                  add file as rc source\n"
			"    --no-default-source            don't search for source files\n"
			"    --platform=match option        if match platform activate next option\n"
			"    --not-platform=match option    if not match platform activate next option\n"
			"\n"
			"Options that require 7zr in your path\n"
			"\n"
			"    --source-archive               allow archive of source folder\n"
			"    --source-extract               allow extraction of source folder from archive\n"
			"    --source-is-archived           if source folder not found extract from archive\n"
			"    --source-has-archive           source-archive, source-extract and source-is-archived\n"
			"    --archive-release              archive install-release folder\n"
			"    --archive-release-sha512       archive install-release folder and append/update sha512 hash to csv\n"
			"\n"
			"    --install-file=src=dst         install custom file to repository\n"
			"    --sha512-file=file             generate sha512 of file, as csv line (sha512,file)\n"
		);
		printf("\n");
	};

	int Application::main(int cmdN, char *cmdS[]) {
		int i;
		String opt;
		size_t optIndex;
		String optValue;

		bool makeExecutable = false;
		bool makeLibrary = false;
		bool makeDynamicLibrary = false;
		bool isRelease = true;
		bool modeIsVersion = false;
		bool doInstall = false;
		bool doInstallRelease = false;
		bool doInstallDev = false;
		bool noLib = false;
		bool noInc = false;
		bool dllVersion = false;
		bool licenseInfo = false;
		bool noDefaultSource = false;
		bool sourceArchive = false;
		bool sourceExtract = false;
		bool sourceIsArchived = false;
		bool doSourceArchive = false;
		bool doSourceExtract = false;
		bool archiveRelease = false;
		bool archiveReleaseSHA512 = false;
		bool doBumpVersionBuild = false;
		bool doBumpVersionPatch = false;
		bool doBumpVersionMinor = false;
		bool doBumpVersionMajor = false;

		String workspacePath = Shell::getCwd();
		String projectName;
		String includePathX;
		String sourcePathX;
		String installProjectName;
		String installVersionFile;
		String installInc;
		String libName;

		String p7zipCompress="7zr a -mx9 -mmt4 -r- -sse -w. -y -t7z ";
		if(Compiler::matchPlatform("ubuntu*")) {
			p7zipCompress="7zr a -mx9 -mmt4 -r- -w. -y -t7z ";
		};
		if(Compiler::matchPlatform("mingw*")) {
			p7zipCompress="sh.exe -- 7zr a -mx9 -mmt4 -r- -w. -y -t7z ";
		};

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

		TDynamicArray<String> srcH;
		TDynamicArray<String> srcC;
		TDynamicArray<String> srcHpp;
		TDynamicArray<String> srcCpp;
		TDynamicArray<String> srcRc;

		TDynamicArray<String> repositoryPathDependency;
		TDynamicArray<String> repositoryPathDependencyLib;

		TDynamicArray<String> installFile;
		TDynamicArray<String> sha512File;

		int crtOption = CompilerOptions::CRTDynamic;
		int dllOption = CompilerOptions::None;
		String versionFile;
		String projectBase;

		String pathRepository = Shell::getEnv("XYO_PATH_REPOSITORY");
		if(pathRepository.isEmpty()) {
			pathRepository = "./repository";
		};

		// first is the main repository
		repositoryPathDependency.push(pathRepository);

		String pathRepositoryLibrary = Shell::getEnv("XYO_PATH_REPOSITORY_LIBRARY");
		if(pathRepositoryLibrary.length() > 0) {
			String::explode(";", pathRepositoryLibrary, repositoryPathDependency);
		};

		size_t w;
		for(w = 0; w < repositoryPathDependency.length(); ++w) {
			repositoryPathDependencyLib.push(repositoryPathDependency[w] + "/lib");
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
				if (opt == "version") {
					showVersion();
					return 0;
				};
				if (opt == "license") {
					showLicense();
					return 0;
				};
				if (opt == "usage") {
					showUsage();
					return 0;
				};
				if (opt == "bump-version") {
					doBumpVersionBuild = true;
					continue;
				};
				if (opt == "bump-version-build") {
					doBumpVersionBuild = true;
					continue;
				};
				if (opt == "bump-version-patch") {
					doBumpVersionPatch = true;
					continue;
				};
				if (opt == "bump-version-minor") {
					doBumpVersionMinor = true;
					continue;
				};
				if (opt == "bump-version-major") {
					doBumpVersionMajor = true;
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
					doBumpVersionBuild = false;
					doBumpVersionPatch = false;
					doBumpVersionMinor = false;
					doBumpVersionMajor = false;
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
					if(optValue.isEmpty()) {
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
						doBumpVersionBuild = true;
						modeIsVersion = true;
						continue;
					};
					if (optValue == "version-build") {
						doBumpVersionBuild = true;
						modeIsVersion = true;
						continue;
					};
					if (optValue == "version-patch") {
						doBumpVersionPatch = true;
						modeIsVersion = true;
						continue;
					};
					if (optValue == "version-minor") {
						doBumpVersionMinor = true;
						modeIsVersion = true;
						continue;
					};
					if (optValue == "version-major") {
						doBumpVersionMajor = true;
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
					if (optValue == "archive") {
						doSourceArchive=true;
						continue;
					};
					if (optValue == "extract") {
						doSourceExtract=true;
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
					if(workspacePath.isEmpty()) {
						printf("Error: workspace-path is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "bin-path") {
					binPath = optValue;
					if(binPath.isEmpty()) {
						printf("Error: bin-path is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "build-path") {
					buildPath = optValue;
					if(buildPath.isEmpty()) {
						printf("Error: build-path is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "lib-path") {
					libPath = optValue;
					if(libPath.isEmpty()) {
						printf("Error: lib-path is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "threads") {
					if(sscanf(optValue.value(), "%d", &numThreads)!=1) {
						numThreads=8;
					};
					continue;
				};
				if (opt == "inc") {
					if(optValue.isEmpty()) {
						printf("Error: inc path is empty\n");
						return 1;
					};
					incPath.push(optValue);
					continue;
				};
				if (opt == "inc-repository") {
					if(optValue.isEmpty()) {
						printf("Error: inc path is empty\n");
						return 1;
					};
					incPath.push(pathRepository + "/include/" + optValue);
					continue;
				};
				if (opt == "def") {
					if(optValue.isEmpty()) {
						printf("Error: def parameter is empty\n");
						return 1;
					};
					cppDefine.push(optValue);
					continue;
				};
				if (opt == "rc-inc") {
					if(optValue.isEmpty()) {
						printf("Error: rc-inc path is empty\n");
						return 1;
					};
					incPathRC.push(optValue);
					continue;
				};
				if (opt == "rc-def") {
					if(optValue.isEmpty()) {
						printf("Error: rc-def parameter is empty\n");
						return 1;
					};
					rcDefine.push(optValue);
					continue;
				};
				if (opt == "use-lib-path") {
					if(optValue.isEmpty()) {
						printf("Error: use-lib-path is empty\n");
						return 1;
					};
					libDependencyPath.push(optValue);
					continue;
				};
				if (opt == "use-lib") {
					if(optValue.isEmpty()) {
						printf("Error: use-lib is empty\n");
						return 1;
					};
					libDependency.push(optValue);
					if(String::endsWith(libDependency[libDependency.length() - 1], ".static")) {
						crtOption = CompilerOptions::CRTStatic;
					};
					INIFileX::insert(projectDependency, "project", "lib", optValue);
					continue;
				};
				if (opt == "use-lib-source") {
					if(optValue.isEmpty()) {
						printf("Error: use-lib-source is empty\n");
						return 1;
					};
					libDependency.push(Shell::getFileName(optValue));
					INIFileX::insert(projectDependency, "project", "lib", Shell::getFileName(optValue));
					if(String::endsWith(optValue, ".static")) {
						crtOption = CompilerOptions::CRTStatic;
						optValue = String::substring(optValue, 0, optValue.length() - strlen(".static"));
					};
					incPath.push(optValue + "/include");
					libDependencyPath.push(optValue + "/lib");
					continue;
				};
				if (opt == "use-lib-include") {
					if(optValue.isEmpty()) {
						printf("Error: use-lib-include is empty\n");
						return 1;
					};
					if(String::endsWith(optValue, ".static")) {
						crtOption = CompilerOptions::CRTStatic;
						optValue = String::substring(optValue, 0, optValue.length() - strlen(".static"));
					};
					incPath.push(optValue + "/include");
					libDependencyPath.push(optValue + "/lib");
					continue;
				};
				if (opt == "use-project") {
					if(optValue.isEmpty()) {
						printf("Error: use-project is empty\n");
						return 1;
					};
					INIFileX::insert(projectDependency, "project", "project", optValue);
					continue;
				};
				if (opt == "version-file") {
					versionFile = optValue;
					if(versionFile.isEmpty()) {
						printf("Error: version-file is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "project-base") {
					projectBase = optValue;
					if(projectBase.isEmpty()) {
						printf("Error: project-base is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "def-file") {
					defFile = optValue;
					if(defFile.isEmpty()) {
						printf("Error: def-file is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "install-project") {
					installProjectName = optValue;
					if(installProjectName.isEmpty()) {
						printf("Error: install-project is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "install-version-file") {
					installVersionFile = optValue;
					if(installVersionFile.isEmpty()) {
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
					if(installInc.isEmpty()) {
						printf("Error: install-inc is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "make") {
					doMake = true;
					cmdMake = optValue;
					libDependency.push(":xyo.static");
					crtOption = CompilerOptions::CRTStatic;
					incPath.push(pathRepository + "/include/xyo");
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
					if(optValue.isEmpty()) {
						printf("Error: dependency-set is empty\n");
						return 1;
					};
					String optKey;
					if(String::indexOf(optValue, "=", 0, optIndex)) {
						optKey = String::substring(optValue, 0, optIndex);
						optValue = String::substring(optValue, optIndex + 1);
					};
					if(optValue.isEmpty()) {
						printf("Error: dependency-set - key is empty\n");
						return 1;
					};
					if(optKey.isEmpty()) {
						printf("Error: dependency-set - value is empty\n");
						return 1;
					};
					INIFileX::insert(projectDependency, "project", optKey, optValue);
					continue;
				};
				if (opt == "dependency-license") {
					if(optValue.isEmpty()) {
						printf("Error: dependency-license is empty\n");
						return 1;
					};
					if(projectName.isEmpty()) {
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
				if (opt == "lib-name") {
					libName = optValue;
					if(libName.isEmpty()) {
						printf("Error: lib-name is empty\n");
						return 1;
					};
					continue;
				};
				if (opt == "src-h") {
					if(optValue.isEmpty()) {
						printf("Error: src-h file not provided\n");
						return 1;
					};
					srcH.push(optValue);
					continue;
				};
				if (opt == "src-c") {
					if(optValue.isEmpty()) {
						printf("Error: src-c file not provided\n");
						return 1;
					};
					srcC.push(optValue);
					continue;
				};
				if (opt == "src-hpp") {
					if(optValue.isEmpty()) {
						printf("Error: src-hpp file not provided\n");
						return 1;
					};
					srcHpp.push(optValue);
					continue;
				};
				if (opt == "src-cpp") {
					if(optValue.isEmpty()) {
						printf("Error: src-cpp file not provided\n");
						return 1;
					};
					srcCpp.push(optValue);
					continue;
				};
				if (opt == "src-rc") {
					if(optValue.isEmpty()) {
						printf("Error: src-rc file not provided\n");
						return 1;
					};
					srcRc.push(optValue);
					continue;
				};
				if (opt == "no-default-source") {
					noDefaultSource = true;
					continue;
				};
				if (opt == "platform") {
					if(optValue.isEmpty()) {
						printf("Error: platform to match in not provided\n");
						return 1;
					};
					if(!Compiler::matchPlatform(optValue)) {
						++i;
						continue;
					};
					continue;
				};
				if (opt == "not-platform") {
					if(optValue.isEmpty()) {
						printf("Error: platform to match in not provided\n");
						return 1;
					};
					if(Compiler::matchPlatform(optValue)) {
						++i;
						continue;
					};
					continue;
				};
				if (opt == "source-archive") {
					sourceArchive = true;
					continue;
				};
				if (opt == "source-extract") {
					sourceExtract = true;
					continue;
				};
				if (opt == "source-is-archived") {
					sourceIsArchived = true;
					continue;
				};
				if (opt == "source-has-archive") {
					sourceArchive = true;
					sourceExtract = true;
					sourceIsArchived = true;
					continue;
				};
				if (opt == "archive-release") {
					archiveRelease = true;
					continue;
				};
				if (opt == "archive-release-sha512") {
					archiveRelease = true;
					archiveReleaseSHA512 = true;
					continue;
				};
				if (opt == "install-file") {
					if(optValue.isEmpty()) {
						printf("Error: install-file not provided\n");
						return 1;
					};
					installFile.push(optValue);
				};
				if (opt == "sha512-file") {
					if(optValue.isEmpty()) {
						printf("Error: sha512-file not provided\n");
						return 1;
					};
					sha512File.push(optValue);
				};
				continue;
			};
			projectName = cmdLine[i];
		};

		// <hash>

		if(sha512File.length()) {
			CSVRow csvRow;
			String csvLine;
			int k;
			for(k=0; k<sha512File.length(); ++k) {
				csvRow.empty();
				if(!Util::fileHashSHA512(sha512File[k], csvRow[0])) {
					printf("Error: sha512-file on %s failed\n", sha512File[k].value());
					return 1;
				};
				csvRow[1]=sha512File[k];
				if(!CSVFileX::encode(csvLine, csvRow)) {
					printf("Error: csv encoding\n");
					return 1;
				};
				printf("%s", csvLine.value());
			};
			return 0;
		};

		// </hash>

		if(projectName.isEmpty()) {
			printf("Error: No project specified.\n");
			return 1;
		};

		if(projectBase.isEmpty()) {
			projectBase = projectName;
		};

		if(versionFile.isEmpty()) {
			if(sourcePathX.length() > 0) {
				versionFile = workspacePath + "/" + sourcePathX + "/" + projectBase + ".version.ini";
			} else {
				versionFile = workspacePath + "/" + projectBase + ".version.ini";
			};
		};

		String versionHash = Compiler::getVersionHash(versionFile, projectBase);
		INIFileX::insert(projectDependency, "project", "version", Compiler::getVersion(versionFile, projectBase));
		INIFileX::insert(projectDependency, "project", "version.hash", versionHash);

		String libVersion;
		if(dllVersion) {
			libVersion = Compiler::getVersion(versionFile, projectBase);
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

		// <archive>

		String projectNameWithVersion = projectName + "-" + Compiler::getVersion(versionFile, projectBase);

		if(doSourceArchive) {
			if(sourceArchive) {
				String originalPath = Shell::getCwd();
				Shell::chdir(workspacePath);

				if(!Shell::directoryExists("source")) {
					printf("Error: source not found\r\n");
					Shell::chdir(originalPath);
					return 1;
				};

				if(!Shell::rename("source", projectNameWithVersion)) {
					printf("Error: source directory in use\r\n");
					Shell::chdir(originalPath);
					return 1;
				};

				String archive = "archive/";
				archive << projectNameWithVersion << ".7z";
				if(Shell::fileExists(archive)) {
					if(!Shell::remove(archive)) {
						printf("Error: Unable to remove source archive\r\n");
						Shell::chdir(originalPath);
						return 1;
					};
				};
				if(Shell::system(p7zipCompress + archive + " " + projectNameWithVersion)) {
					printf("Error: Unable to compress source\r\n");
					Shell::chdir(originalPath);
					return 1;
				};
				if(!Shell::rename(projectNameWithVersion, "source")) {
					printf("Error: %s or source directory in use\r\n", projectNameWithVersion.value());
					Shell::chdir(originalPath);
					return 1;
				};
				Shell::chdir(originalPath);
				return 0;
			};
		};

		if(doSourceExtract) {
			if(sourceExtract) {
				String originalPath = Shell::getCwd();
				Shell::chdir(workspacePath);
				if(!Shell::removeDirRecursively("source")) {
					printf("Error: unable to remove source, directory in use\r\n");
					Shell::chdir(originalPath);
					return 1;
				};
				Shell::chdir(originalPath);
			};
		};

		if(sourceIsArchived) {
			String originalPath = Shell::getCwd();
			Shell::chdir(workspacePath);

			if(!Shell::directoryExists("source")) {
				if(Shell::system(String("7zr x -aoa ") + workspacePath + "/archive/" + projectNameWithVersion + ".7z")) {
					printf("Error: Unable to extract source archive: %s\r\n", projectNameWithVersion.value());
					Shell::chdir(originalPath);
					return 1;
				};
				if(!Shell::rename(projectNameWithVersion, "source")) {
					printf("Error: %s or source directory in use\r\n", projectNameWithVersion.value());
					Shell::chdir(originalPath);
					return 1;
				};
			};

			Shell::chdir(originalPath);
		};

		if(doSourceExtract) {
			if(sourceExtract) {
				return 0;
			};
		};

		if(sourceIsArchived) {
			return 0;
		};

		if(archiveRelease) {
			String originalPath = Shell::getCwd();
			String releaseName=Shell::getFileName(pathRelease);
			Shell::chdir(pathRelease+"/..");

			// bin

			if(Shell::directoryExists(releaseName)) {
				if(Shell::fileExists(releaseName+".7z")) {
					Shell::removeFile(releaseName+".7z");
				};
				Shell::system(p7zipCompress+releaseName+".7z "+releaseName);
				Shell::removeDirRecursively(releaseName);
				if(archiveReleaseSHA512) {
					CSVRow csvRow;
					String csvLine;
					String fileName=releaseName+".7z";
					String fileNameSHA512CSV=projectNameWithVersion+".sha512.csv";
					csvRow.empty();
					if(!Util::fileHashSHA512(fileName, csvRow[0])) {
						printf("Error: sha512-file on %s failed\n", fileName.value());
						return 1;
					};
					csvRow[1]=fileName;
					if(!CSVFileX::encode(csvLine, csvRow)) {
						printf("Error: csv encoding\n");
						return 1;
					};

					if(!Shell::fileExists(fileNameSHA512CSV)) {
						if(!Shell::filePutContentsAppend(fileNameSHA512CSV, csvLine+"\r\n")) {
							printf("Error: unable to write sha512 hash\n");
							return 1;
						};
					} else {
						CSVFile updateCSV;
						if(!CSVFileX::load(fileNameSHA512CSV, updateCSV)) {
							printf("Error: unable to load sha512 hash csv file\n");
							return 1;
						};
						bool found=false;
						for(i=0; i<updateCSV.length(); ++i) {
							if(updateCSV[i].length()>1) {
								if(updateCSV[i][1]==csvRow[1]) {
									updateCSV[i][0]=csvRow[0];
									found=true;
								};
							};
						};
						if(!found) {
							CSVRow &newRow=updateCSV.push();
							newRow[0]=csvRow[0];
							newRow[1]=csvRow[1];
						};
						if(!CSVFileX::save(fileNameSHA512CSV, updateCSV)) {
							printf("Error: unable to update sha512 hash csv file\n");
							return 1;
						};
					};
				};
			};

			// dev

			releaseName+="-dev";
			if(Shell::directoryExists(releaseName)) {
				if(Shell::fileExists(releaseName+".7z")) {
					Shell::removeFile(releaseName+".7z");
				};
				Shell::system(p7zipCompress+releaseName+".7z "+releaseName);
				Shell::removeDirRecursively(releaseName);
				if(archiveReleaseSHA512) {
					CSVRow csvRow;
					String csvLine;
					String fileName=releaseName+".7z";
					String fileNameSHA512CSV=projectNameWithVersion+".sha512.csv";
					csvRow.empty();
					if(!Util::fileHashSHA512(fileName, csvRow[0])) {
						printf("Error: sha512-file on %s failed\n", fileName.value());
						return 1;
					};
					csvRow[1]=fileName;
					if(!CSVFileX::encode(csvLine, csvRow)) {
						printf("Error: csv encoding\n");
						return 1;
					};

					if(!Shell::fileExists(fileNameSHA512CSV)) {
						if(!Shell::filePutContentsAppend(fileNameSHA512CSV, csvLine+"\r\n")) {
							printf("Error: unable to write sha512 hash\n");
							return 1;
						};
					} else {
						CSVFile updateCSV;
						if(!CSVFileX::load(fileNameSHA512CSV, updateCSV)) {
							printf("Error: unable to load sha512 hash csv file\n");
							return 1;
						};
						bool found=false;
						for(i=0; i<updateCSV.length(); ++i) {
							if(updateCSV[i].length()>1) {
								if(updateCSV[i][1]==csvRow[1]) {
									updateCSV[i][0]=csvRow[0];
									found=true;
									break;
								};
							};
						};
						if(!found) {
							CSVRow &newRow=updateCSV.push();
							newRow[0]=csvRow[0];
							newRow[1]=csvRow[1];
						};
						if(!CSVFileX::save(fileNameSHA512CSV, updateCSV)) {
							printf("Error: unable to update sha512 hash csv file\n");
							return 1;
						};
					};
				};
			};

			//

			Shell::chdir(originalPath);
			return 0;
		};

		// </archive>

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
			libDependency.push(String(":") + optValue);
			if(String::endsWith(optValue, ".static")) {
				crtOption = CompilerOptions::CRTStatic;
				optValue = String::substring(optValue, 0, optValue.length() - strlen(".static"));
			};
			for(w = 0; w < repositoryPathDependency.length(); ++w) {
				if(Shell::directoryExists(repositoryPathDependency[w] + "/include/" + optValue)) {
					incPath.push(repositoryPathDependency[w] + "/include/" + optValue);
					break;
				};
			};
		};

		dependecyList.empty();
		INIFileX::getValues(dependency, projectName, "lib", dependecyList);
		for(k = 0; k < dependecyList.length(); ++k) {
			optValue = dependecyList[k];
			libDependency.push(optValue);
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
					incPath.push(repositoryPathDependency[w] + "/include/" + optValue);
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
					incPathRC.push(repositoryPathDependency[w] + "/include/" + optValue);
					break;
				};
			};
		};

		dependecyList.empty();
		INIFileX::getValues(dependency, projectName, "define", dependecyList);
		for(k = 0; k < dependecyList.length(); ++k) {
			optValue = dependecyList[k];
			if(optValue.length() > 0) {
				cppDefine.push(optValue);
			};
		};

		dependecyList.empty();
		INIFileX::getValues(dependency, projectName, "rc.define", dependecyList);
		for(k = 0; k < dependecyList.length(); ++k) {
			optValue = dependecyList[k];
			if(optValue.length() > 0) {
				rcDefine.push(optValue);
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

		if(doBumpVersionBuild) {
			if(!Compiler::bumpVersionBuild(
					versionFile,
					projectBase,
					sourcePath,
					includePath)) {
				printf("Error: version update fail\n");
				return 1;
			};
			return 0;
		};

		if(doBumpVersionPatch) {
			if(!Compiler::bumpVersionPatch(
					versionFile,
					projectBase,
					sourcePath,
					includePath)) {
				printf("Error: version update fail\n");
				return 1;
			};
			return 0;
		};

		if(doBumpVersionMinor) {
			if(!Compiler::bumpVersionMinor(
					versionFile,
					projectBase,
					sourcePath,
					includePath)) {
				printf("Error: version update fail\n");
				return 1;
			};
			return 0;
		};

		if(doBumpVersionMajor) {
			if(!Compiler::bumpVersionMajor(
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

		if(!noDefaultSource) {

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
				hFilesIn.push(hFilesExtra[k]);
			};
			for(k = 0; k < cSourceExtra.length(); ++k) {
				cSourceIn.push(cSourceExtra[k]);
			};
			for(k = 0; k < hppFilesExtra.length(); ++k) {
				hppFilesIn.push(hppFilesExtra[k]);
			};
			for(k = 0; k < cppSourceExtra.length(); ++k) {
				cppSourceIn.push(cppSourceExtra[k]);
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
					hFiles.push(hFilesIn[k]);
					continue;
				};
				hFiles.push(hFilesIn[k]);
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
					hFiles.push(cSourceIn[k]);
					continue;
				};
				cSource.push(cSourceIn[k]);
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
					hppFiles.push(hppFilesIn[k]);
					continue;
				};
				hppFiles.push(hppFilesIn[k]);
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
					hppFiles.push(cppSourceIn[k]);
					continue;
				};
				cppSource.push(cppSourceIn[k]);
			};

		};

		TDynamicArray<String> srcScan;
		size_t l;

		for(k = 0; k < srcH.length(); ++k) {
			Shell::getFileList(srcH[k], srcScan);
			for(l = 0; l < srcScan.length(); ++l) {
				hFiles.push(srcScan[l]);
			};
		};

		for(k = 0; k < srcC.length(); ++k) {
			Shell::getFileList(srcC[k], srcScan);
			for(l = 0; l < srcScan.length(); ++l) {
				cSource.push(srcScan[l]);
			};
		};

		for(k = 0; k < srcHpp.length(); ++k) {
			Shell::getFileList(srcHpp[k], srcScan);
			for(l = 0; l < srcScan.length(); ++l) {
				hppFiles.push(srcScan[l]);
			};
		};

		for(k = 0; k < srcCpp.length(); ++k) {
			Shell::getFileList(srcCpp[k], srcScan);
			for(l = 0; l < srcScan.length(); ++l) {
				cppSource.push(srcScan[l]);
			};
		};

		for(k = 0; k < srcRc.length(); ++k) {
			Shell::getFileList(srcRc[k], srcScan);
			for(l = 0; l < srcScan.length(); ++l) {
				rcFiles.push(srcScan[l]);
			};
		};

		//

		incPath.push(includePath);
		if(includePath != sourcePath) {
			incPath.push(sourcePath);
		};

		incPathRC.push(includePath);
		if(includePath != sourcePath) {
			incPathRC.push(sourcePath);
		};

		String defInternal = String::toUpperCaseAscii(projectBase) + "_INTERNAL";
		defInternal = String::replace(defInternal, "-", "_");
		defInternal = String::replace(defInternal, ".", "_");
		cppDefine.push(defInternal);
		if(String::beginWith(projectBase, "lib")) {
			cppDefine[cppDefine.length() - 1] = String::substring(cppDefine[cppDefine.length() - 1], 3);
		};

		libDependencyPath.push(libPath);

		// last is repository
		for(w = 0; w < repositoryPathDependency.length(); ++w) {
			incPath.push(repositoryPathDependency[w] + "/include");
			libDependencyPath.push(repositoryPathDependency[w] + "/lib");
			incPathRC.push(repositoryPathDependency[w] + "/include");
		};

		if(doInstallRelease) {
			doInstall = true;
			pathInstall = pathRelease;
			pathInstall += "-dev";
		};

		if(makeLibrary) {
			if((cSource.isEmpty()) && (cppSource.isEmpty())) {
				printf("Error: no c/cpp source for library %s\n", projectName.value());
				return 1;
			};
			if(cSource.length() > 0) {
				if(!Compiler::makeCToLib(
						libName.length()?libName:projectName + ".static",
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
						libName.length()?libName:projectName + ".static",
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
					if(includePath != workspacePath) {
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
		};

		if(makeDynamicLibrary) {
			if((cSource.isEmpty()) && (cppSource.isEmpty())) {
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
					if(includePath != workspacePath) {
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
		};

		if(makeExecutable) {
			if((cSource.isEmpty()) && (cppSource.isEmpty())) {
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
			if(doInstall && ((!doInstallRelease) || doInstallDev)) {
				if(!Compiler::copyExeToFolder(binPath + "/" + projectName, pathInstall + "/bin")) {
					printf("Error: copy exe %s to folder %s\n", (binPath + "/" + projectName).value(), (pathInstall + "/bin").value());
					return 1;
				};
			};
		};

		if(doInstall) {
			if(installFile.length()) {
				String srcFile;
				String dstFile;
				size_t scanIndex;

				for(k=0; k<installFile.length(); ++k) {
					if(String::indexOf(installFile[k], "=", 0, scanIndex)) {
						srcFile = String::substring(installFile[k], 0, scanIndex);
						if(srcFile.length()==0) {
							printf("Error: install-file src is empty\n");
							return 1;
						};
						dstFile = String::substring(installFile[k], scanIndex + 1);
						if(dstFile.length()==0) {
							printf("Error: install-file dst is empty\n");
							return 1;
						};
						srcFile = workspacePath + "/" + srcFile;
						dstFile = pathInstall  + "/" + dstFile;
						if(!Shell::copyFile(srcFile, dstFile)) {
							printf("Error: copy %s to %s\n", srcFile.value(), dstFile.value());
							return 1;
						};
					} else {
						printf("Error: install-file empty\n");
						return 1;
					};
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
