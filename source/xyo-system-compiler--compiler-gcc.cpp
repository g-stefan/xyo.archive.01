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

#ifdef XYO_COMPILER_GCC

namespace XYO {
	namespace System {
		namespace Compiler {
			using namespace XYO::Cryptography;
			using namespace XYO::Multithreading;
			using namespace XYO::DataStructures;
			using namespace XYO::System;
			using namespace XYO::Encoding;

			String objFilename(
				const String &project,
				const String &fileName,
				const String &buildPath,
				int options) {
				options = filterOptions(options);

				String md5;
				if(options & CompilerOptions::Release) {
					md5 += "Release.";
				};
				if(options & CompilerOptions::Debug) {
					md5 += "Debug.";
				};
				if(options & CompilerOptions::CRTStatic) {
					md5 += "CRTStatic.";
				};
				if(options & CompilerOptions::CRTDynamic) {
					md5 += "CRTDynamic.";
				};
				if(options & CompilerOptions::StaticLibrary) {
					md5 += "StaticLibrary.";
				};
				if(options & CompilerOptions::DynamicLibrary) {
					md5 += "DynamicLibrary.";
				};
				md5 += project;
				md5 += ".";
				md5 += fileName;

				String retV = buildPath;
				retV << Shell::pathSeparator << Shell::getFileName(project) << "." << MD5::getHashString(md5) << ".";
				retV << Shell::getFileName(fileName) << ".o";

				return retV;
			};

			bool cppToObj(
				int options,
				String cppFile,
				String objFile,
				TDynamicArray<String> &cppDefine,
				TDynamicArray<String> &incPath,
				bool echoCmd) {
				String cmd;

				int k;
				options = filterOptions(options);
				if(!Shell::mkdirFilePath(objFile)) {
					return false;
				};

				cppFile = String::replace(cppFile, "\\", "/");
				objFile = String::replace(objFile, "\\", "/");
				String cxx = Shell::getEnv("CXX");
				if(cxx.length()==0) {
					cxx="gcc";
				};
				cmd = cxx + " -O1 -std=c++11 -std=gnu++11 -fpermissive";
				if(options & CompilerOptions::Release) {
					cmd += " -DXYO_COMPILE_RELEASE";
				};
				if(options & CompilerOptions::Debug) {
					cmd += " -g";
					cmd += " -DXYO_COMPILE_DEBUG";
				};
				if(options & CompilerOptions::CRTStatic) {
					cmd += " -DXYO_COMPILE_CRT_STATIC";
				};
				if(options & CompilerOptions::CRTDynamic) {
					cmd += " -DXYO_COMPILE_CRT_DYNAMIC";
				};
				if(options & CompilerOptions::StaticLibrary) {
					cmd += " -DXYO_COMPILE_STATIC_LIBRARY";
				};
				if(options & CompilerOptions::DynamicLibrary) {
					cmd += " -fpic";
#ifdef XYO_OS_UNIX
					cmd += " -rdynamic";
#endif
					if(options & CompilerOptions::DynamicLibraryXStatic) {
						cmd += " -DXYO_COMPILE_STATIC_LIBRARY";
					} else {
						cmd += " -DXYO_COMPILE_DYNAMIC_LIBRARY";
					};
				};
				for(k = 0; k < incPath.length(); ++k) {
					cmd << " -I\"" << String::replace(incPath[k], "\\", "/") << "\"";
				};
				for(k = 0; k < cppDefine.length(); ++k) {
					cmd << " -D\"" << cppDefine[k] << "\"";
				};
				cmd << " -c -o \"" << objFile << "\"";
				cmd << " \"" << cppFile << "\"";

				if(echoCmd) {
					printf("%s\n", cmd.value());
				};
				return (Shell::system(cmd) == 0);
			};

			bool makeObjToLib(
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
				bool force) {
				options = filterOptions(options);

				String cmd;
				int k;
				String content;
				bool toMakeObjToLib;
				String libNameOut;

				if(objFiles.isEmpty()) {
					return false;
				};

				if(!Shell::mkdirRecursivelyIfNotExists(binPath)) {
					return false;
				};
				if(!Shell::mkdirRecursivelyIfNotExists(libPath)) {
					return false;
				};
				if(!Shell::mkdirRecursivelyIfNotExists(buildPath)) {
					return false;
				};

				binPath = String::replace(binPath, "\\", "/");
				libPath = String::replace(libPath, "\\", "/");
				buildPath = String::replace(buildPath, "\\", "/");

				if(options & CompilerOptions::StaticLibrary) {
					libNameOut = libPath + "/" + libName + ".a";
					if(!force) {
						if(!Shell::isChanged(libNameOut, objFiles)) {
							return true;
						};
					};
					Shell::remove(libNameOut);
					for(k = 0; k < objFiles.length(); ++k) {
						cmd = "ar qcs";
						cmd << " \"" << libNameOut << "\"";
						cmd << " \"" << String::replace(objFiles[k], "\\", "/") << "\"";
						if(echoCmd) {
							printf("%s\n", cmd.value());
						};
						if(Shell::system(cmd) != 0) {
							Shell::remove(libNameOut);
							return false;
						};
					};
					return true;
				};

				if(options & CompilerOptions::DynamicLibrary) {
#ifdef XYO_OS_UNIX
					libNameOut = binPath << "/" << libName << ".so";
					if(!version.isEmpty()) {
						libNameOut << "." << version;
					};
#endif
#ifdef XYO_OS_WINDOWS
					libNameOut = binPath << "/" << libName;
					if(!version.isEmpty()) {
						libNameOut << "-" << version;
					};
					libNameOut << ".dll";
#endif
					if(!force) {
						if(!Shell::isChanged(libNameOut, objFiles)) {
							return true;
						};
					};

					content << "-shared -o \"" << libNameOut << "\" -Wl,-rpath='$ORIGIN'";
					if(!version.isEmpty()) {
#ifdef XYO_OS_UNIX
						content << ",-soname," << libName << ".so." << version;
#endif
#ifdef XYO_OS_WINDOWS
						content << ",-soname," << libName << "-" << version << ".dll";
#endif
					};
					for(k = 0; k < objFiles.length(); ++k) {
						content << " \"" << String::replace(objFiles[k], "\\", "/") << "\"";
					};
					for(k = 0; k < libDependencyPath.length(); ++k) {
#ifdef XYO_OS_UNIX
						content << " -L\"" << libDependencyPath[k] << "\"";
#endif
#ifdef XYO_OS_WINDOWS
						content << " -L\"" << String::replace(libDependencyPath[k], "\\", "/") << "\"";
#endif
					};
					for(k = 0; k < libDependency.length(); ++k) {
						if(String::endsWith(libDependency[k], ".static")) {
							if(libDependency[k][0] == ':') {
								content << " -l" << libDependency[k] << ".a";
								continue;
							};
							content << " -l" << String::replace(libDependency[k], "lib", "");
							continue;
						};
						if(libDependency[k][0] == ':') {
#ifdef XYO_OS_UNIX
							content << " -l" << libDependency[k] << ".so";
#endif
#ifdef XYO_OS_WINDOWS
							content << " -l" << libDependency[k] << ".dll";
#endif
							continue;
						};
						content << " -l" << String::replace(libDependency[k], "lib", "");
					};
					content << " -lstdc++";
					content << " -lpthread";
					content << " -lm";
#ifdef XYO_OS_UNIX
					content << " -ldl";
#endif
#ifdef XYO_OS_WINDOWS
					content << " -luser32 -lws2_32";
#endif

					Shell::filePutContents(buildPath + "/" + libName + ".o2so", content);
					String cxx = Shell::getEnv("CXX");
					if(cxx.length()==0) {
						cxx="gcc";
					};
					cmd = cxx + " @";
					cmd << buildPath + "/" + libName + ".o2so";
					if(echoCmd) {
						printf("%s\n", cmd.value());
					};
					if(Shell::system(cmd) == 0) {
#ifdef XYO_OS_UNIX
						return Shell::copy(libNameOut, libPath + "/" + libName + ".so");
#endif
#ifdef XYO_OS_WINDOWS
						return Shell::copy(libNameOut, libPath + "/" + libName + ".dll");
#endif
					};
					return false;
				};

				if(echoCmd) {
					printf("%s\n", cmd.value());
				};
				if(Shell::system(cmd) == 0) {
					return true;
				};
				return false;
			};

			bool makeObjToExe(
				String exeName,
				String binPath,
				String buildPath,
				int options,
				TDynamicArray<String> &objFiles,
				TDynamicArray<String> &libDependencyPath,
				TDynamicArray<String> &libDependency,
				bool echoCmd,
				bool force) {
				options = filterOptions(options);

				String cmd;
				int k;
				String content;
				String exeNameOut;

				if(objFiles.isEmpty()) {
					return false;
				};

				if(!Shell::mkdirRecursivelyIfNotExists(binPath)) {
					return false;
				};
				if(!Shell::mkdirRecursivelyIfNotExists(buildPath)) {
					return false;
				};

				binPath = String::replace(binPath, "\\", "/");
				buildPath = String::replace(buildPath, "\\", "/");

				exeNameOut = binPath << "/" << exeName;
#ifdef XYO_OS_WINDOWS
				if(!String::endsWith(exeNameOut, ".exe")) {
					exeNameOut << ".exe";
				};
#endif
				if(!force) {
					if(!Shell::isChanged(exeNameOut, objFiles)) {
						return true;
					};
				};

				content << "-o \"" << exeNameOut << "\" -Wl,-rpath='$ORIGIN'";
				for(k = 0; k < objFiles.length(); ++k) {
					content << " \"" << String::replace(objFiles[k], "\\", "/") << "\"";
				};
				for(k = 0; k < libDependencyPath.length(); ++k) {
#ifdef XYO_OS_UNIX
					content << " -L\"" << libDependencyPath[k] << "\"";
#endif
#ifdef XYO_OS_WINDOWS
					content << " -L\"" << String::replace(libDependencyPath[k], "\\", "/") << "\"";
#endif
				};
				for(k = 0; k < libDependency.length(); ++k) {
					if(String::endsWith(libDependency[k], ".static")) {
						if(libDependency[k][0] == ':') {
							content << " -l" << libDependency[k] << ".a";
							continue;
						};
						content << " -l" << String::replace(libDependency[k], "lib", "");
						continue;
					};
					if(libDependency[k][0] == ':') {
#ifdef XYO_OS_UNIX
						content << " -l" << libDependency[k] << ".so";
#endif
#ifdef XYO_OS_WINDOWS
						content << " -l" << libDependency[k] << ".dll";
#endif
						continue;
					};
					content << " -l" << String::replace(libDependency[k], "lib", "");
				};

#ifdef XYO_OS_WINDOWS
				if(options & CompilerOptions::CRTStatic) {
					content << " -static-libstdc++ -static-libgcc";
					content << " -Wl,-Bstatic -lstdc++ -lpthread -lm -Wl,-Bdynamic";
				} else {
					content << " -lstdc++";
					content << " -lpthread";
					content << " -lm";
				};
				content << " -luser32 -lws2_32";
#endif
#ifdef XYO_OS_UNIX
				content << " -lstdc++";
				content << " -lpthread";
				content << " -lm";
				content << " -ldl";
#endif
				Shell::filePutContents(buildPath + "/" + exeName + ".o2elf", content);
				String cxx = Shell::getEnv("CXX");
				if(cxx.length()==0) {
					cxx="gcc";
				};
				cmd = cxx + " @";
				cmd << buildPath + "/" + exeName + ".o2elf";

				if(echoCmd) {
					printf("%s\n", cmd.value());
				};
				if(Shell::system(cmd) == 0) {
					return true;
				};
				return false;
			};


			bool rcToRes(
				String rcFile,
				String resFile,
				TDynamicArray<String> &rcDefine,
				TDynamicArray<String> &incPath,
				bool echoCmd) {
#ifdef XYO_OS_UNIX
				return false;
#endif
#ifdef XYO_OS_WINDOWS
				String cmd;
				int k;
				if(!Shell::mkdirFilePath(resFile)) {
					return false;
				};

				rcFile = String::replace(rcFile, "\\", "/");
				resFile = String::replace(resFile, "\\", "/");
				cmd = "windres ";
				for(k = 0; k < incPath.length(); ++k) {
					cmd << " -I \"" << String::replace(incPath[k], "/", "\\") << "\"";
				};
				for(k = 0; k < rcDefine.length(); ++k) {
					cmd << " --define \"" << rcDefine[k] << "\"";
				};
				cmd << " -l 409 -J rc -O res";
				cmd << " -o \"" << resFile << "\"";
				cmd << " -i \"" << rcFile << "\"";

				if(echoCmd) {
					printf("%s\n", cmd.value());
				};
				return (Shell::system(cmd) == 0);
#endif
			};

			bool resToObj(
				String resFile,
				String objFile,
				bool echoCmd) {
#ifdef XYO_OS_UNIX
				return false;
#endif
#ifdef XYO_OS_WINDOWS
				String cmd;
				if(!Shell::mkdirFilePath(objFile)) {
					return false;
				};

				resFile = String::replace(resFile, "/", "\\");
				objFile = String::replace(objFile, "/", "\\");

				cmd = "windres -J res -O coff";

				cmd << " -o \"" << objFile << "\" -i \"" << resFile << "\"";

				if(echoCmd) {
					printf("%s\n", cmd.value());
				};
				return (Shell::system(cmd) == 0);
#endif
			};

			bool makeRcToObj(
				String rcFile,
				String objFile,
				TDynamicArray<String> &rcDefine,
				TDynamicArray<String> &incPath,
				bool echoCmd,
				bool force) {
#ifdef XYO_OS_UNIX
				return false;
#endif
#ifdef XYO_OS_WINDOWS
				bool toMake;

				String resFile = String::replace(objFile, ".o", ".res");
				toMake = false;
				if(!Shell::fileExists(resFile)) {
					toMake = true;
				} else {
					if(Shell::compareLastWriteTime(resFile, rcFile) < 0) {
						toMake = true;
					};
				};

				if(toMake || force) {
					if(!rcToRes(rcFile, resFile, rcDefine, incPath, echoCmd)) {
						return false;
					};
				};

				toMake = false;
				if(!Shell::fileExists(objFile)) {
					toMake = true;
				} else {
					if(Shell::compareLastWriteTime(objFile, resFile) < 0) {
						toMake = true;
					};
				};

				if(toMake || force) {
					if(!resToObj(resFile, objFile, echoCmd)) {
						return false;
					};
				};

				return true;
#endif
			}

			class CompilerWorkerBool:
				public Object {
				public:
					bool value;
			};

			TPointer<CompilerWorkerBool> compilerTransferWorkerBool(CompilerWorkerBool &value) {
				TPointer<CompilerWorkerBool> retV;
				retV.newMemory();
				retV->value = value.value;
				return retV;
			};

			class CompilerWorkerCppToObj:
				public Object {
				public:
					String cppFile;
					String objFile;
					int options;
					TDynamicArray<String> incPath;
					TDynamicArray<String> cppDefine;
					bool echoCmd;
			};

			TPointer<CompilerWorkerCppToObj> compilerTransferWorkerCppToObj(CompilerWorkerCppToObj &value) {
				TPointer<CompilerWorkerCppToObj> retV;
				retV.newMemory();
				retV->cppFile = value.cppFile.value();
				retV->objFile = value.objFile.value();
				retV->options = value.options;
				size_t k;
				TDynamicArray<String> *source;
				TDynamicArray<String> *target;

				source = &value.incPath;
				target = &retV->incPath;
				for(k = 0; k < source->length(); ++k) {
					(target->index(k)) = (source->index(k)).value();
				};

				source = &value.cppDefine;
				target = &retV->cppDefine;
				for(k = 0; k < source->length(); ++k) {
					(target->index(k)) = (source->index(k)).value();
				};

				retV->echoCmd = value.echoCmd;
				return retV;
			};

			TPointer<CompilerWorkerBool> compilerWorkerProcedureCppToObj(CompilerWorkerCppToObj *parameter, TAtomic<bool> &requestToTerminate) {
				TPointer<CompilerWorkerBool> retV;
				retV.newMemory();
				if(parameter) {
					retV->value = cppToObj(
							parameter->options,
							parameter->cppFile,
							parameter->objFile,
							parameter->cppDefine,
							parameter->incPath,
							parameter->echoCmd
						);
				};
				return retV;
			};

			bool makeCppToLib(
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
				bool force) {
				options = filterOptions(options);

				size_t k, m;
				TDynamicArray<String> objFiles;
				TPointer<CompilerWorkerCppToObj> parameter;
				TPointer<CompilerWorkerBool> retVCppToObj;
				WorkerQueue compileCppToObj;
				compileCppToObj.setNumberOfThreads(numThreads);
				String projectName = libName;
				bool toMakeCppToObj;

				if(options & CompilerOptions::DynamicLibrary) {
					projectName << ".so";
				};
				if(options & CompilerOptions::StaticLibrary) {
					projectName << ".a";
				};

				for(k = 0; k < cppFiles.length(); ++k) {
					objFiles[k] = objFilename(projectName, cppFiles[k], buildPath, options);
					toMakeCppToObj = false;
					if(Shell::isChanged(cppFiles[k], incFiles)) {
						Shell::touchIfExists(cppFiles[k]);
						toMakeCppToObj = true;
					};
					if(!Shell::fileExists(objFiles[k])) {
						toMakeCppToObj = true;
					} else {
						if(Shell::compareLastWriteTime(objFiles[k], cppFiles[k]) < 0) {
							toMakeCppToObj = true;
						};
					};
					if(!force) {
						if(!toMakeCppToObj) {
							continue;
						};
					};

					parameter.newMemory();
					parameter->cppFile = cppFiles[k];
					parameter->objFile = objFiles[k];
					parameter->options = options;
					for(m = 0; m < incPath.length(); ++m) {
						parameter->incPath[m] = incPath[m];
					};
					for(m = 0; m < cppDefine.length(); ++m) {
						parameter->cppDefine[m] = cppDefine[m];
					};
					parameter->echoCmd = echoCmd;
					TWorkerQueue<CompilerWorkerBool,
						     CompilerWorkerCppToObj,
						     compilerTransferWorkerBool,
						     compilerTransferWorkerCppToObj,
						     compilerWorkerProcedureCppToObj>::add(compileCppToObj, parameter);
				};

				if(!compileCppToObj.isEmpty()) {
					if(!compileCppToObj.process()) {
						return false;
					};
					for(k = 0; k < compileCppToObj.length(); ++k) {
						retVCppToObj = TStaticCast<CompilerWorkerBool *>(compileCppToObj.getReturnValue(k));
						if(retVCppToObj) {
							if(!retVCppToObj->value) {
								return false;
							};
							continue;
						};
						return false;
					};
				};

#ifdef XYO_OS_WINDOWS
				if(options & CompilerOptions::DynamicLibrary) {
					String resObj;
					for(k = 0; k < rcFiles.length(); ++k) {

						if(Shell::isChanged(rcFiles[k], incFiles)) {
							Shell::touchIfExists(rcFiles[k]);
						};

						resObj = objFilename(projectName, rcFiles[k], buildPath, options);

						if(!makeRcToObj(
								rcFiles[k],
								resObj,
								rcDefine,
								incPathRC,
								echoCmd,
								force)) {
							return false;
						};

						objFiles.push(resObj);
					};
				};
#endif

				return makeObjToLib(
						libName,
						binPath,
						libPath,
						buildPath,
						options,
						objFiles,
						defFile,
						libDependencyPath,
						libDependency,
						version,
						echoCmd,
						force);

			};

			bool makeCppToExe(
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
				bool force) {
				if(options & CompilerOptions::CRTStatic) {
					options |= CompilerOptions::StaticLibrary;
				};
				if(options & CompilerOptions::CRTDynamic) {
					options |= CompilerOptions::DynamicLibrary;
				};
				options = filterOptions(options);

				size_t k, m;
				TDynamicArray<String> objFiles;
				TPointer<CompilerWorkerCppToObj> parameter;
				TPointer<CompilerWorkerBool> retVCppToObj;
				WorkerQueue compileCppToObj;
				compileCppToObj.setNumberOfThreads(numThreads);
				String projectName = exeName;
				bool toMakeCppToObj;

				for(k = 0; k < cppFiles.length(); ++k) {
					objFiles[k] = objFilename(projectName, cppFiles[k], buildPath, options);
					toMakeCppToObj = false;
					if(Shell::isChanged(cppFiles[k], incFiles)) {
						Shell::touchIfExists(cppFiles[k]);
						toMakeCppToObj = true;
					};
					if(!Shell::fileExists(objFiles[k])) {
						toMakeCppToObj = true;
					} else {
						if(Shell::compareLastWriteTime(objFiles[k], cppFiles[k]) < 0) {
							toMakeCppToObj = true;
						};
					};

					if(!force) {
						if(!toMakeCppToObj) {
							continue;
						};
					};

					parameter.newMemory();
					parameter->cppFile = cppFiles[k];
					parameter->objFile = objFiles[k];
					parameter->options = options;
					for(m = 0; m < incPath.length(); ++m) {
						parameter->incPath[m] = incPath[m];
					};
					for(m = 0; m < cppDefine.length(); ++m) {
						parameter->cppDefine[m] = cppDefine[m];
					};
					parameter->echoCmd = echoCmd;
					TWorkerQueue<CompilerWorkerBool,
						     CompilerWorkerCppToObj,
						     compilerTransferWorkerBool,
						     compilerTransferWorkerCppToObj,
						     compilerWorkerProcedureCppToObj>::add(compileCppToObj, parameter);
				};

				if(!compileCppToObj.isEmpty()) {
					if(!compileCppToObj.process()) {
						return false;
					};
					for(k = 0; k < compileCppToObj.length(); ++k) {
						retVCppToObj = TStaticCast<CompilerWorkerBool *>(compileCppToObj.getReturnValue(k));
						if(retVCppToObj) {
							if(!retVCppToObj->value) {
								return false;
							};
							continue;
						};
						return false;
					};
				};

#ifdef XYO_OS_WINDOWS
				String resObj;
				for(k = 0; k < rcFiles.length(); ++k) {

					if(Shell::isChanged(rcFiles[k], incFiles)) {
						Shell::touchIfExists(rcFiles[k]);
					};

					resObj = objFilename(projectName, rcFiles[k], buildPath, options);

					if(!makeRcToObj(
							rcFiles[k],
							resObj,
							rcDefine,
							incPathRC,
							echoCmd,
							force)) {
						return false;
					};

					objFiles.push(resObj);
				};
#endif
				return makeObjToExe(
						exeName,
						binPath,
						buildPath,
						options,
						objFiles,
						libDependencyPath,
						libDependency,
						echoCmd,
						force);

			};

			bool cToObj(
				String cFile,
				String objFile,
				int options,
				TDynamicArray<String> &cDefine,
				TDynamicArray<String> &incPath,
				bool echoCmd) {
				String cmd;
				int k;
				options = filterOptions(options);
				if(!Shell::mkdirFilePath(objFile)) {
					return false;
				};

				cFile = String::replace(cFile, "\\", "/");
				objFile = String::replace(objFile, "\\", "/");
				String cc = Shell::getEnv("CC");
				if(cc.length()==0) {
					cc="gcc";
				};
				cmd = cc + " -O1";
				if(options & CompilerOptions::Release) {
					cmd += " -DXYO_COMPILE_RELEASE";
				};
				if(options & CompilerOptions::Debug) {
					cmd += " -g";
					cmd += " -DXYO_COMPILE_DEBUG";
				};
				if(options & CompilerOptions::CRTStatic) {
					cmd += " -DXYO_COMPILE_CRT_STATIC";
				};
				if(options & CompilerOptions::CRTDynamic) {
					cmd += " -DXYO_COMPILE_CRT_DYNAMIC";
				};
				if(options & CompilerOptions::StaticLibrary) {
					cmd += " -DXYO_COMPILE_STATIC_LIBRARY";
				};
				if(options & CompilerOptions::DynamicLibrary) {
					cmd += " -fpic -rdynamic";
					if(options & CompilerOptions::DynamicLibraryXStatic) {
						cmd += " -DXYO_COMPILE_STATIC_LIBRARY";
					} else {
						cmd += " -DXYO_COMPILE_DYNAMIC_LIBRARY";
					};
				};
				for(k = 0; k < incPath.length(); ++k) {
					cmd << " -I\"" << String::replace(incPath[k], "\\", "/") << "\"";
				};
				for(k = 0; k < cDefine.length(); ++k) {
					cmd << " -D\"" << cDefine[k] << "\"";
				};
				cmd << " -c -o \"" << objFile << "\"";
				cmd << " \"" << cFile << "\"";

				if(echoCmd) {
					printf("%s\n", cmd.value());
				};
				return (Shell::system(cmd) == 0);
			};

			TPointer<CompilerWorkerBool> compilerWorkerProcedureCToObj(CompilerWorkerCppToObj *parameter, TAtomic<bool> &requestToTerminate) {
				TPointer<CompilerWorkerBool> retV;
				retV.newMemory();
				if(parameter) {
					retV->value = cToObj(
							parameter->cppFile,
							parameter->objFile,
							parameter->options,
							parameter->cppDefine,
							parameter->incPath,
							parameter->echoCmd
						);
				};
				return retV;
			};

			bool makeCToLib(
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
				bool force) {
				options = filterOptions(options);

				size_t k, m;
				TDynamicArray<String> objFiles;
				TPointer<CompilerWorkerCppToObj> parameter;
				TPointer<CompilerWorkerBool> retVCToObj;
				WorkerQueue compileCToObj;
				compileCToObj.setNumberOfThreads(numThreads);
				String projectName = libName;
				bool toMakeCToObj;

				if(options & CompilerOptions::DynamicLibrary) {
					projectName << ".so";
				};
				if(options & CompilerOptions::StaticLibrary) {
					projectName << ".a";
				};

				for(k = 0; k < cFiles.length(); ++k) {
					objFiles[k] = objFilename(projectName, cFiles[k], buildPath, options);
					toMakeCToObj = false;
					if(Shell::isChanged(cFiles[k], incFiles)) {
						Shell::touchIfExists(cFiles[k]);
						toMakeCToObj = true;
					};
					if(!Shell::fileExists(objFiles[k])) {
						toMakeCToObj = true;
					} else {
						if(Shell::compareLastWriteTime(objFiles[k], cFiles[k]) < 0) {
							toMakeCToObj = true;
						};
					};

					if(!force) {
						if(!toMakeCToObj) {
							continue;
						};
					};

					parameter.newMemory();
					parameter->cppFile = cFiles[k];
					parameter->objFile = objFiles[k];
					parameter->options = options;
					for(m = 0; m < incPath.length(); ++m) {
						parameter->incPath[m] = incPath[m];
					};
					for(m = 0; m < cDefine.length(); ++m) {
						parameter->cppDefine[m] = cDefine[m];
					};
					parameter->echoCmd = echoCmd;
					TWorkerQueue<CompilerWorkerBool,
						     CompilerWorkerCppToObj,
						     compilerTransferWorkerBool,
						     compilerTransferWorkerCppToObj,
						     compilerWorkerProcedureCToObj>::add(compileCToObj, parameter);
				};

				if(!compileCToObj.isEmpty()) {
					if(!compileCToObj.process()) {
						return false;
					};
					for(k = 0; k < compileCToObj.length(); ++k) {
						retVCToObj = TStaticCast<CompilerWorkerBool *>(compileCToObj.getReturnValue(k));
						if(retVCToObj) {
							if(!retVCToObj->value) {
								return false;
							};
							continue;
						};
						return false;
					};
				};

#ifdef XYO_OS_WINDOWS
				if(options & CompilerOptions::DynamicLibrary) {
					String resObj;
					for(k = 0; k < rcFiles.length(); ++k) {

						if(Shell::isChanged(rcFiles[k], incFiles)) {
							Shell::touchIfExists(rcFiles[k]);
						};

						resObj = objFilename(projectName, rcFiles[k], buildPath, options);

						if(!makeRcToObj(
								rcFiles[k],
								resObj,
								rcDefine,
								incPathRC,
								echoCmd,
								force)) {
							return false;
						};

						objFiles.push(resObj);
					};
				};
#endif


				return makeObjToLib(
						libName,
						binPath,
						libPath,
						buildPath,
						options,
						objFiles,
						defFile,
						libDependencyPath,
						libDependency,
						version,
						echoCmd,
						force);

			};

			bool makeCToExe(
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
				bool force) {
				if(options & CompilerOptions::CRTStatic) {
					options |= CompilerOptions::StaticLibrary;
				};
				if(options & CompilerOptions::CRTDynamic) {
					options |= CompilerOptions::DynamicLibrary;
				};
				options = filterOptions(options);

				size_t k, m;
				TDynamicArray<String> objFiles;
				TPointer<CompilerWorkerCppToObj> parameter;
				TPointer<CompilerWorkerBool> retVCToObj;
				WorkerQueue compileCToObj;
				compileCToObj.setNumberOfThreads(numThreads);
				String projectName = exeName;
				bool toMakeCToObj;

				for(k = 0; k < cFiles.length(); ++k) {
					objFiles[k] = objFilename(projectName, cFiles[k], buildPath, options);
					toMakeCToObj = false;
					if(Shell::isChanged(cFiles[k], incFiles)) {
						Shell::touchIfExists(cFiles[k]);
						toMakeCToObj = true;
					};
					if(!Shell::fileExists(objFiles[k])) {
						toMakeCToObj = true;
					} else {
						if(Shell::compareLastWriteTime(objFiles[k], cFiles[k]) < 0) {
							toMakeCToObj = true;
						};
					};

					if(!force) {
						if(!toMakeCToObj) {
							continue;
						};
					};

					parameter.newMemory();
					parameter->cppFile = cFiles[k];
					parameter->objFile = objFiles[k];
					parameter->options = options;
					for(m = 0; m < incPath.length(); ++m) {
						parameter->incPath[m] = incPath[m];
					};
					for(m = 0; m < cDefine.length(); ++m) {
						parameter->cppDefine[m] = cDefine[m];
					};
					parameter->echoCmd = echoCmd;
					TWorkerQueue<CompilerWorkerBool,
						     CompilerWorkerCppToObj,
						     compilerTransferWorkerBool,
						     compilerTransferWorkerCppToObj,
						     compilerWorkerProcedureCToObj>::add(compileCToObj, parameter);
				};

				if(!compileCToObj.isEmpty()) {
					if(!compileCToObj.process()) {
						return false;
					};
					for(k = 0; k < compileCToObj.length(); ++k) {
						retVCToObj = TStaticCast<CompilerWorkerBool *>(compileCToObj.getReturnValue(k));
						if(retVCToObj) {
							if(!retVCToObj->value) {
								return false;
							};
							continue;
						};
						return false;
					};
				};
#ifdef XYO_OS_WINDOWS
				String resObj;
				for(k = 0; k < rcFiles.length(); ++k) {

					if(Shell::isChanged(rcFiles[k], incFiles)) {
						Shell::touchIfExists(rcFiles[k]);
					};

					resObj = objFilename(projectName, rcFiles[k], buildPath, options);

					if(!makeRcToObj(
							rcFiles[k],
							resObj,
							rcDefine,
							incPathRC,
							echoCmd,
							force)) {
						return false;
					};

					objFiles.push(resObj);
				};
#endif


				return makeObjToExe(
						exeName,
						binPath,
						buildPath,
						options,
						objFiles,
						libDependencyPath,
						libDependency,
						echoCmd,
						force);

			};

			bool getFileNameLib(const String &fileName, String &out) {
				if(String::endsWith(fileName, ".a")) {
					out = fileName;
					return true;
				};
				out = fileName;
				out += ".a";
				return true;
			};

			bool getFileNameDll(const String &fileName, String &out, const String &version) {
#ifdef XYO_OS_UNIX
				if(String::endsWith(fileName, ".so")) {
					out = fileName;
					return true;
				};
				out = fileName;
				out += ".so";
				if(!version.isEmpty()) {
					out += ".";
					out += version;
				};
				return true;
#endif
#ifdef XYO_OS_WINDOWS
				if(String::endsWith(fileName, ".dll")) {
					out = fileName;
					return true;
				};
				out = fileName;
				if(!version.isEmpty()) {
					out += "-";
					out += version;
				};
				out += ".dll";
				return true;
#endif
			};

			bool getFileNameExe(const String &fileName, String &out) {
#ifdef XYO_OS_UNIX
				out = fileName;
				return true;
#endif
#ifdef XYO_OS_WINDOWS
				if(String::endsWith(fileName, ".exe")) {
					out = fileName;
					return true;
				};
				out = fileName;
				out += ".exe";
				return true;
#endif
			};

			bool copyLib(const String &fileName, const String &file) {
				String fileNameLib;
				String fileLib;
				if(getFileNameLib(fileName, fileNameLib)) {
					if(getFileNameLib(file, fileLib)) {
						return Shell::copyFile(fileNameLib, fileLib);
					};
				};
				return false;
			};

			bool copyDll(const String &fileName, const String &file, const String &version, const String &fileVersion) {
				String fileNameDll;
				String fileDll;
				if(getFileNameDll(fileName, fileNameDll, version)) {
					if(getFileNameDll(file, fileDll, fileVersion)) {
						return Shell::copyFile(fileNameDll, fileDll);
					};
				};
				return false;
			};

			bool copyExe(const String &fileName, const String &file) {
				String fileNameExe;
				String fileExe;
				if(getFileNameExe(fileName, fileNameExe)) {
					if(getFileNameExe(file, fileExe)) {
						return Shell::copyFile(fileNameExe, fileExe);
					};
				};
				return false;
			};

			bool copyLibToFolder(const String &fileName, const String &folder) {
				String fileNameLib;
				if(getFileNameLib(fileName, fileNameLib)) {
					return Shell::copyFile(fileNameLib, folder + Shell::pathSeparator + Shell::getFileName(fileNameLib));
				};
				return false;
			};

			bool copyDllToFolder(const String &fileName, const String &folder, const String &version) {
				String fileNameDll;
				if(getFileNameDll(fileName, fileNameDll, version)) {
					return Shell::copyFile(fileNameDll, folder + Shell::pathSeparator + Shell::getFileName(fileNameDll));
				};
				return false;
			};

			bool copyExeToFolder(const String &fileName, const String &folder) {
				String fileNameExe;
				if(getFileNameExe(fileName, fileNameExe)) {
					return Shell::copyFile(fileNameExe, folder + Shell::pathSeparator + Shell::getFileName(fileNameExe));
				};
				return false;
			};

			bool copyDllToFolderWithLib(
				const String &fileNameLib, const String &folderLib,
				const String &fileNameDll, const String &folderBin,
				const String &version) {

				if(copyDllToFolder(fileNameLib, folderLib, "")) {
					if(copyDllToFolder(fileNameDll, folderBin, version)) {
						return true;
					};
				};

				return true;
			};

		};
	};
};

#endif
