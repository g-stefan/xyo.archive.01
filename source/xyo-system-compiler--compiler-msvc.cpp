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

#ifdef XYO_COMPILER_MSVC

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

				retV << Shell::getFileName(fileName) << ".obj";

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
				String content;

				int k;
				options = filterOptions(options);
				if(!Shell::mkdirFilePath(objFile)) {
					return false;
				};

				cppFile = String::replace(cppFile, "/", "\\");
				objFile = String::replace(objFile, "/", "\\");

				String cxx = Shell::getEnv("CXX");
				if(cxx.length()==0) {
					cxx="cl.exe";
				};

				cmd = cxx;
				content = " /nologo";

				if(options & CompilerOptions::Release) {
					content += " /DXYO_COMPILE_RELEASE";
					if(options & CompilerOptions::CRTDynamic) {
						content += " /MD";
						content += " /DXYO_COMPILE_CRT_DYNAMIC";
					};
					if(options & CompilerOptions::CRTStatic) {
						content += " /MT";
						content += " /DXYO_COMPILE_CRT_STATIC";
					};
					content += " /O2 /Oi /Oy /Gy /Gd /EHsc /GR /TP /c";
				};
				if(options & CompilerOptions::Debug) {
					content += " /DXYO_COMPILE_DEBUG";
					if(options & CompilerOptions::CRTDynamic) {
						content += " /MDd";
						content += " /DXYO_COMPILE_CRT_DYNAMIC";
					};
					if(options & CompilerOptions::CRTStatic) {
						content += " /MTd";
						content += " /DXYO_COMPILE_CRT_STATIC";
					};
					content += " /Zi /EHsc /GR /TP /c";
				};
				if(options & CompilerOptions::StaticLibrary) {
					content += " /DXYO_COMPILE_STATIC_LIBRARY";
				};
				if(options & CompilerOptions::DynamicLibrary) {
					if(options & CompilerOptions::DynamicLibraryXStatic) {
						content += " /DXYO_COMPILE_STATIC_LIBRARY";
					} else {
						content += " /DXYO_COMPILE_DYNAMIC_LIBRARY";
					};
				};

				for(k = 0; k < incPath.length(); ++k) {
					content << " /I\"" << String::replace(incPath[k], "/", "\\") << "\"";
				};
				for(k = 0; k < cppDefine.length(); ++k) {
					content << " /D\"" << cppDefine[k] << "\"";
				};
				if(options & CompilerOptions::Debug) {
					content << " /Fd\"" << String::replace(objFile, ".obj", ".pdb") << "\"";
				};
#ifdef XYO_APPLICATION_32BIT
				content << " /arch:SSE2";
#endif
				content << " /Fo\"" << objFile << "\"";
				content << " \"" << cppFile << "\"";

				String cmdFile = String::replace(objFile, ".cpp.obj", ".cpp2obj");
				Shell::filePutContents(cmdFile, content);
				cmd << " @" << cmdFile;

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


				binPath = String::replace(binPath, "/", "\\");
				libPath = String::replace(libPath, "/", "\\");
				buildPath = String::replace(buildPath, "/", "\\");

				if(options & CompilerOptions::StaticLibrary) {
					libNameOut = libPath << "\\" << libName << ".lib";
					if(!force) {
						if(!Shell::isChanged(libNameOut, objFiles)) {
							return true;
						};
					};

#ifdef XYO_APPLICATION_64BIT
					content << "/NOLOGO /OUT:\"" << libNameOut << "\" /MACHINE:X64";
#endif
#ifdef XYO_APPLICATION_32BIT
					content << "/NOLOGO /OUT:\"" << libNameOut << "\" /MACHINE:X86";
#endif

					for(k = 0; k < objFiles.length(); ++k) {
						content << " \"" << String::replace(objFiles[k], "/", "\\") << "\"";
					};

					Shell::filePutContents(buildPath + "\\" + libName + ".obj2lib", content);
					cmd = "lib.exe @";
					cmd << buildPath + "\\" + libName + ".obj2lib";

				};

				if(options & CompilerOptions::DynamicLibrary) {
					libNameOut = binPath << "\\" << libName;
					if(!version.isEmpty()) {
						libNameOut << "-" << version;
					};
					libNameOut << ".dll";
					if(!force) {
						if(!Shell::isChanged(libNameOut, objFiles)) {
							return true;
						};
					};

#ifdef XYO_APPLICATION_64BIT
					content << "/NOLOGO /OUT:\"" << libNameOut << "\" /MACHINE:X64";
					content << " /ENTRY:_DllMainCRTStartup";
#endif
#ifdef XYO_APPLICATION_32BIT
					content << "/NOLOGO /OUT:\"" << libNameOut << "\" /MACHINE:X86";
					content << " /ENTRY:_DllMainCRTStartup@12";
#endif
					content << " /DLL /INCREMENTAL:NO /OPT:REF /OPT:ICF";
					if(options & CompilerOptions::Release) {
						content << " /RELEASE";
						if(options & CompilerOptions::CRTDynamic) {
							content += " /nodefaultlib:libcmt /defaultlib:msvcrt";
						};
						if(options & CompilerOptions::CRTStatic) {
							content += " /nodefaultlib:msvcrt /defaultlib:libcmt";
						};
					};
					if(options & CompilerOptions::Debug) {
						content << " /DEBUG";
						if(options & CompilerOptions::CRTDynamic) {
							content += " /nodefaultlib:libcmtd /defaultlib:msvcrtd";
						};
						if(options & CompilerOptions::CRTStatic) {
							content += " /nodefaultlib:msvcrtd /defaultlib:libcmtd";
						};
					};
					if(!defFile.isEmpty()) {
						content << " /DEF:\"" << defFile << "\"";
					};
					content << " /implib:\"" << libPath << "\\" << libName << ".lib\"";
					for(k = 0; k < objFiles.length(); ++k) {
						content << " \"" << String::replace(objFiles[k], "/", "\\") << "\"";
					};
					for(k = 0; k < libDependencyPath.length(); ++k) {
						content << " /LIBPATH:\"" << libDependencyPath[k] << "\"";
					};
					for(k = 0; k < libDependency.length(); ++k) {
						if(libDependency[k][0] == ':') {
							content << " " << String::substring(libDependency[k], 1) << ".lib";
							continue;
						};
						content << " " << libDependency[k] << ".lib";
					};

					content << " user32.lib";
					content << " gdi32.lib";
					content << " ws2_32.lib";
					content << " ole32.lib";
					content << " wininet.lib";
					content << " advapi32.lib";
					content << " ole32.lib";
					content << " oleaut32.lib";
					content << " shell32.lib";
					content << " iphlpapi.lib";

					Shell::filePutContents(buildPath + "\\" + libName + ".obj2dll", content);
					cmd = "link.exe @";
					cmd << buildPath + "\\" + libName + ".obj2dll";

				};
				if(echoCmd) {
					printf("%s\n", cmd.value());
				};
				return (Shell::system(cmd) == 0);
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

				binPath = String::replace(binPath, "/", "\\");
				buildPath = String::replace(buildPath, "/", "\\");

				exeNameOut = binPath << "\\" << exeName << ".exe";
				if(!force) {
					if(!Shell::isChanged(exeNameOut, objFiles)) {
						return true;
					};
				};

#ifdef XYO_APPLICATION_64BIT
				content << "/NOLOGO /OUT:\"" << exeNameOut << "\" /MACHINE:X64";
#endif
#ifdef XYO_APPLICATION_32BIT
				content << "/NOLOGO /OUT:\"" << exeNameOut << "\" /MACHINE:X86";
#endif
				content << " /INCREMENTAL:NO /OPT:REF /OPT:ICF";
				if(options & CompilerOptions::Release) {
					content << " /RELEASE";
					if(options & CompilerOptions::CRTDynamic) {
						content += " /nodefaultlib:libcmt /defaultlib:msvcrt";
					};
					if(options & CompilerOptions::CRTStatic) {
						content += " /nodefaultlib:msvcrt /defaultlib:libcmt";
					};
				};
				if(options & CompilerOptions::Debug) {
					content << " /DEBUG";
					if(options & CompilerOptions::CRTDynamic) {
						content += " /nodefaultlib:libcmtd /defaultlib:msvcrtd";
					};
					if(options & CompilerOptions::CRTStatic) {
						content += " /nodefaultlib:msvcrtd /defaultlib:libcmtd";
					};
				};
				for(k = 0; k < objFiles.length(); ++k) {
					content << " \"" << String::replace(objFiles[k], "/", "\\") << "\"";
				};
				for(k = 0; k < libDependencyPath.length(); ++k) {
					content << " /LIBPATH:\"" << libDependencyPath[k] << "\"";
				};
				for(k = 0; k < libDependency.length(); ++k) {
					if(libDependency[k][0] == ':') {
						content << " " << String::substring(libDependency[k], 1) << ".lib";
						continue;
					};
					content << " " << libDependency[k] << ".lib";
				};

				content << " user32.lib";
				content << " gdi32.lib";
				content << " ws2_32.lib";
				content << " ole32.lib";
				content << " wininet.lib";
				content << " advapi32.lib";
				content << " ole32.lib";
				content << " oleaut32.lib";
				content << " shell32.lib";
				content << " iphlpapi.lib";

				Shell::filePutContents(buildPath + "\\" + exeName + ".obj2exe", content);
				cmd = "link.exe @";
				cmd << buildPath + "\\" + exeName + ".obj2exe";

				if(echoCmd) {
					printf("%s\n", cmd.value());
				};
				return (Shell::system(cmd) == 0);
			};

			bool rcToRes(
				String rcFile,
				String resFile,
				TDynamicArray<String> &rcDefine,
				TDynamicArray<String> &incPath,
				bool echoCmd) {
				String cmd;
				int k;
				if(!Shell::mkdirFilePath(resFile)) {
					return false;
				};

				rcFile = String::replace(rcFile, "/", "\\");
				resFile = String::replace(resFile, "/", "\\");
				cmd = "rc.exe /nologo";
				for(k = 0; k < incPath.length(); ++k) {
					cmd << " /i \"" << String::replace(incPath[k], "/", "\\") << "\"";
				};
				for(k = 0; k < rcDefine.length(); ++k) {
					cmd << " /d \"" << rcDefine[k] << "\"";
				};
				cmd << " /l 409 /z \"MS Sans Serif,Helv/MS Shell Dlg\" /r /fo \"" << resFile << "\"";
				cmd << " \"" << rcFile << "\"";

				if(echoCmd) {
					printf("%s\n", cmd.value());
				};
				return (Shell::system(cmd) == 0);
			};

			bool resToObj(
				String resFile,
				String objFile,
				bool echoCmd) {
				String cmd;
				if(!Shell::mkdirFilePath(objFile)) {
					return false;
				};

				resFile = String::replace(resFile, "/", "\\");
				objFile = String::replace(objFile, "/", "\\");

				cmd = "cvtres.exe /NOLOGO";

#ifdef XYO_APPLICATION_64BIT
				cmd << " /MACHINE:X64";
#endif
#ifdef XYO_APPLICATION_32BIT
				cmd << " /MACHINE:X86";
#endif
				cmd << " /OUT:\"" << objFile << "\" \"" << resFile << "\"";

				if(echoCmd) {
					printf("%s\n", cmd.value());
				};
				return (Shell::system(cmd) == 0);
			};

			bool makeRcToObj(
				String rcFile,
				String objFile,
				TDynamicArray<String> &rcDefine,
				TDynamicArray<String> &incPath,
				bool echoCmd,
				bool force) {
				bool toMake;

				String resFile = String::replace(objFile, ".obj", ".res");
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
			};

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
					projectName << ".dll";
				};
				if(options & CompilerOptions::StaticLibrary) {
					projectName << ".lib";
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

				projectName << ".exe";

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
				String content;

				int k;
				options = filterOptions(options);
				if(!Shell::mkdirFilePath(objFile)) {
					return false;
				};

				cFile = String::replace(cFile, "/", "\\");
				objFile = String::replace(objFile, "/", "\\");

				String cc = Shell::getEnv("CC");
				if(cc.length()==0) {
					cc="cl.exe";
				};

				cmd = cc;
				content = " /nologo";

				if(options & CompilerOptions::Release) {
					content += " /DXYO_COMPILE_RELEASE";
					if(options & CompilerOptions::CRTDynamic) {
						content += " /MD";
						content += " /DXYO_COMPILE_CRT_DYNAMIC";
					};
					if(options & CompilerOptions::CRTStatic) {
						content += " /MT";
						content += " /DXYO_COMPILE_CRT_STATIC";
					};
					content += " /O2 /Oi /Oy /Gy /Gd /EHsc /GR /TC /c";
				};
				if(options & CompilerOptions::Debug) {
					content += " /DXYO_COMPILE_DEBUG";
					if(options & CompilerOptions::CRTDynamic) {
						content += " /MDd";
						content += " /DXYO_COMPILE_CRT_DYNAMIC";
					};
					if(options & CompilerOptions::CRTStatic) {
						content += " /MTd";
						content += " /DXYO_COMPILE_CRT_STATIC";
					};
					content += " /Zi /EHsc /GR /TC /c";
				};
				if(options & CompilerOptions::StaticLibrary) {
					content += " /DXYO_COMPILE_STATIC_LIBRARY";
				};
				if(options & CompilerOptions::DynamicLibrary) {
					if(options & CompilerOptions::DynamicLibraryXStatic) {
						content += " /DXYO_COMPILE_STATIC_LIBRARY";
					} else {
						content += " /DXYO_COMPILE_DYNAMIC_LIBRARY";
					};
				};

				for(k = 0; k < incPath.length(); ++k) {
					content << " /I\"" << String::replace(incPath[k], "/", "\\") << "\"";
				};
				for(k = 0; k < cDefine.length(); ++k) {
					content << " /D\"" << cDefine[k] << "\"";
				};
				if(options & CompilerOptions::Debug) {
					content << " /Fd\"" << String::replace(objFile, ".obj", ".pdb") << "\"";
				};
#ifdef XYO_APPLICATION_32BIT
				content << " /arch:SSE2";
#endif
				content << " /Fo\"" << objFile << "\"";
				content << " \"" << cFile << "\"";

				String cmdFile = String::replace(objFile, ".c.obj", ".c2obj");
				Shell::filePutContents(cmdFile, content);
				cmd << " @" << cmdFile;

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
					projectName << ".dll";
				};
				if(options & CompilerOptions::StaticLibrary) {
					projectName << ".lib";
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

				projectName << ".exe";

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
				if(String::endsWith(fileName, ".lib")) {
					out = fileName;
					return true;
				};
				out = fileName;
				out += ".lib";
				return true;

			};

			bool getFileNameDll(const String &fileName, String &out, const String &version) {
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

			};

			bool getFileNameExe(const String &fileName, String &out) {
				if(String::endsWith(fileName, ".exe")) {
					out = fileName;
					return true;
				};
				out = fileName;
				out += ".exe";
				return true;
			};

			bool copyLib(const String &fileName, const String &file) {
				String fileNameLib;
				String fileLib;
				if(getFileNameLib(fileName, fileNameLib)) {
					if(getFileNameLib(file, fileLib)) {
						if(Shell::copyFile(fileNameLib, fileLib)) {
							String fileNameExp = Shell::getFileBasename(fileNameLib) + ".exp";
							if(Shell::fileExists(fileNameExp)) {
								String fileExp = Shell::getFileBasename(fileLib) + ".exp";
								if(!Shell::copyFile(fileNameExp, fileExp)) {
									return false;
								};
							};
							return true;
						};
					};
				};
				return false;
			};

			bool copyDll(const String &fileName, const String &file, const String &version, const String &fileVersion) {
				String fileNameDll;
				String fileDll;
				if(getFileNameDll(fileName, fileNameDll, version)) {
					if(getFileNameDll(file, fileDll, fileVersion)) {
						if(Shell::copyFile(fileNameDll, fileDll)) {
							String fileNamePdb = Shell::getFileBasename(fileNameDll) + ".pdb";
							if(Shell::fileExists(fileNamePdb)) {
								String filePdb = Shell::getFileBasename(fileDll) + ".pdb";
								if(!Shell::copyFile(fileNamePdb, filePdb)) {
									return false;
								};
							};
							return true;
						};
					};
				};
				return false;
			};

			bool copyExe(const String &fileName, const String &file) {
				String fileNameExe;
				String fileExe;
				if(getFileNameExe(fileName, fileNameExe)) {
					if(getFileNameExe(file, fileExe)) {
						if(Shell::copyFile(fileNameExe, fileExe)) {
							String fileNamePdb = Shell::getFileBasename(fileNameExe) + ".pdb";
							if(Shell::fileExists(fileNamePdb)) {
								String filePdb = Shell::getFileBasename(fileExe) + ".pdb";
								if(!Shell::copyFile(fileNamePdb, filePdb)) {
									return false;
								};
							};
							return true;
						};
					};
				};
				return false;
			};

			bool copyLibToFolder(const String &fileName, const String &folder) {
				String fileNameLib;
				if(getFileNameLib(fileName, fileNameLib)) {
					if(Shell::copyFile(fileNameLib, folder + Shell::pathSeparator + Shell::getFileName(fileNameLib))) {
						String fileNameExp = Shell::getFileBasename(fileNameLib) + ".exp";
						if(Shell::fileExists(fileNameExp)) {
							if(!Shell::copyFile(fileNameExp, folder + Shell::pathSeparator + Shell::getFileName(fileNameExp))) {
								return false;
							};
						};
						return true;
					};
				};
				return false;
			};

			bool copyDllToFolder(const String &fileName, const String &folder, const String &version) {
				String fileNameDll;
				if(getFileNameDll(fileName, fileNameDll, version)) {
					if(Shell::copyFile(fileNameDll, folder + Shell::pathSeparator + Shell::getFileName(fileNameDll))) {
						String fileNamePdb = Shell::getFileBasename(fileNameDll) + ".pdb";
						if(Shell::fileExists(fileNamePdb)) {
							if(!Shell::copyFile(fileNamePdb, folder + Shell::pathSeparator + Shell::getFileName(fileNamePdb))) {
								return false;
							};
						};
						return true;
					};
				};
				return false;
			};

			bool copyExeToFolder(const String &fileName, const String &folder) {
				String fileNameExe;
				if(getFileNameExe(fileName, fileNameExe)) {
					if(Shell::copyFile(fileNameExe, folder + Shell::pathSeparator + Shell::getFileName(fileNameExe))) {
						String fileNamePdb = Shell::getFileBasename(fileNameExe) + ".pdb";
						if(Shell::fileExists(fileNamePdb)) {
							if(!Shell::copyFile(fileNamePdb, folder + Shell::pathSeparator + Shell::getFileName(fileNamePdb))) {
								return false;
							};
						};
						return true;
					};
				};
				return false;
			};

			bool copyDllToFolderWithLib(
				const String &fileNameLib, const String &folderLib,
				const String &fileNameDll, const String &folderBin,
				const String &version) {

				if(copyLibToFolder(fileNameLib, folderLib)) {
					if(copyDllToFolder(fileNameDll, folderBin, version)) {
						return true;
					};
				};

				return false;
			};

		};
	};
};

#endif
