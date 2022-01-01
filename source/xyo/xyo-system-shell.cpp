//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

#ifdef XYO_OS_WINDOWS
#       define WIN32_LEAN_AND_MEAN
#       include <windows.h>
#endif

#ifdef XYO_OS_UNIX
#       include <sys/types.h>
#       include <unistd.h>
#       include <sys/stat.h>
#       include <limits.h>
#endif

#include "xyo-system-shell.hpp"
#include "xyo-system-filetime.hpp"
#include "xyo-system-file.hpp"
#include "xyo-stream-streamx.hpp"
#include "xyo-datastructures-tdynamicarray.hpp"
#include "xyo-encoding-string.hpp"

namespace XYO {
	namespace System {
		namespace Shell {

			using namespace XYO::ManagedMemory;
			using namespace XYO::DataStructures;
			using namespace XYO::Stream;
			using namespace XYO::Encoding;

			String getFileName(const String &fileName) {
				String fileName_ = normalize(fileName);
				size_t index;
				if(String::indexOfFromEnd(fileName_, pathSeparator, 0, index)) {
					return String::substring(fileName, index + 1);
				};
				return fileName;
			};

			String getFileExtension(const String &fileName) {
				size_t index;
				if(String::indexOfFromEnd(fileName, ".", 0, index)) {
					return String::substring(fileName, index + 1);
				};
				return "";
			};

			String getFileBasename(const String &fileName) {
				size_t index;
				if(String::indexOfFromEnd(fileName, ".", 0, index)) {
					return String::substring(fileName, 0, index);
				};
				return fileName;
			};

			String getFilePath(const String &fileName) {
				String fileName_ = normalize(fileName);
				size_t index;
				if(String::indexOfFromEnd(fileName_, pathSeparator, 0, index)) {
					return String::substring(fileName, 0, index);
				};
				return "";
			};

			String getFilePathX(const String &fileName) {
				String fileName_ = normalize(fileName);
				size_t index;
				if(String::indexOfFromEnd(fileName_, pathSeparator, 0, index)) {
					return String::substring(fileName, 0, index + 1);
				};
				return "";
			};

			bool fileGetContents(const char *fileName, String &output) {
				File file;
				if (file.openRead(fileName)) {
					size_t size;

					file.seekFromEnd(0);
					size = file.seekTell();
					file.seekFromBegin(0);

					TPointer<StringReference> result(TMemory<StringReference>::newMemory());
					result->init(size);
					result->setLength(size);
					if (file.read(result->value(), size) == size) {
						file.close();
						(result->value())[size] = 0;
						output = result;
						return true;
					};
					result.deleteMemory();
					file.close();
				};
				return false;
			};

			bool filePutContents(const char *fileName, const String &value) {
				File file;
				if (file.openWrite(fileName)) {
					if (file.write(value.index(0), value.length()) == value.length()) {
						file.close();
						return true;
					};
					file.close();
				};
				return false;
			};

			bool filePutContentsAppend(const char *fileName, const String &value) {
				File file;
				if (file.openAppend(fileName)) {
					if (file.write(value.index(0), value.length()) == value.length()) {
						file.close();
						return true;
					};
					file.close();
				};
				return false;
			};

			bool isEmptyDir(const char *dirName) {
				String scan;
				bool found;
				ShellFind findX;

				found = false;
				scan = dirName;
				scan += pathSeparator;
				scan += "*";
				for(findX.find(scan); findX; findX.next()) {
					if(findX.isDirectory) {
						if(StringCore::isEqual(findX.name, "..")) {
							continue;
						};
						if(StringCore::isEqual(findX.name, ".")) {
							continue;
						};
						found = true;
						break;
					};
					found = true;
					break;
				};
				return !found;
			};

			bool removeEmptyDir(const char *dirName) {
				if(!isEmptyDir(dirName)) {
					return rmdir(dirName);
				};
				return false;
			};

			bool removeFile(const char *file) {
				if(fileExists(file)) {
					return remove(file);
				};
				return false;
			};

			bool removeFileAndDirectoryIfEmpty(const String &target) {
				if(!target.isEmpty()) {
					if(removeFile(target)) {
						String path = getFilePath(target);
						if(!path.isEmpty()) {
							return removeEmptyDir(path);
						};
					};
				};
				return false;
			};

			bool touchIfExists(const char *file) {
				if(fileExists(file)) {
					return touch(file);
				};
				return false;
			};

			bool isEnv(const char *name, const char *value) {
				char *v = getenv(name);
				if((v != nullptr) && (value != nullptr)) {
					if(StringCore::isEqual(v, value)) {
						return true;
					};
				};
				return false;
			};

			bool hasEnv(const char *name) {
				char *v = getenv(name);
				if(v != nullptr) {
					return true;
				};
				return false;
			};

			String getEnv(const char *name) {
				String retV;
				char *result_ = getenv(name);
				if(result_ != nullptr) {
					return result_;
				};
				return retV;
			};

			String getCwd() {
				TPointer<StringReference> retV(TMemory<StringReference>::newMemory());
				retV->init(4096);
				if (getcwd(retV->value(), 4096)) {
					retV->setLength(StringCore::length(retV->value()));
				};
				return retV;
			};

			bool realPath(const char *path, String &out) {
				TPointer<StringReference> retV(TMemory<StringReference>::newMemory());
				retV->init(4096);
				if (realpath(path, retV->value(), 4096)) {
					retV->setLength(StringCore::length(retV->value()));
					out = retV;
					return true;
				};
				return false;
			};

			bool fileGetContentsSkipLines(const String &fileName, String &output, int linesToSkip, size_t lineSize) {
				File file;
				String line;
				if (file.openRead(fileName)) {
					output = "";
					while(StreamX::readLn(file, line, lineSize)) {
						if(linesToSkip <= 0) {
							output << line;
							continue;
						};
						--linesToSkip;
					};
					file.close();
					return true;
				};
				return false;
			};

			bool fileGetContents(const char *fileName, Buffer &output) {
				File file;
				if (file.openRead(fileName)) {
					size_t size;

					file.seekFromEnd(0);
					size = file.seekTell();
					file.seekFromBegin(0);

					output.setSize(size);

					if (file.read(output.buffer, size) == size) {
						file.close();
						output.length = output.size;
						return true;
					};

					file.close();
				};
				return false;
			};

			bool filePutContents(const char *fileName, const Buffer &value) {
				File file;
				if (file.openWrite(fileName)) {
					if (file.write(value.buffer, value.length) == value.length) {
						file.close();
						return true;
					};
					file.close();
				};
				return false;
			};

			bool filePutContents(const char *fileName, const uint8_t *data, size_t dataSize) {
				File file;
				if (file.openWrite(fileName)) {
					if (file.write(data, dataSize) == dataSize) {
						file.close();
						return true;
					};
					file.close();
				};
				return false;
			};

			bool isAbsolutePath(const char *path) {
				String path_ = normalize(path);
				return (path_[0] == pathSeparator[0]);
			};

			String getExecutable() {
				String exeFile;
#ifdef XYO_OS_WINDOWS
				char strExe[4096];
				GetModuleFileName(nullptr, strExe, 4096);
#endif
#ifdef XYO_OS_UNIX
				char strExe[PATH_MAX];
				memset(strExe, 0, sizeof(strExe));
				if(readlink("/proc/self/exe", strExe, PATH_MAX) == -1) {
					strcpy(strExe, ".");
				};
#endif
				return normalize(strExe);
			};

			String getExecutablePath() {
				String pathMain;
				size_t idx;

#ifdef XYO_OS_WINDOWS
				char strExe[4096];
				GetModuleFileName(nullptr, strExe, 4096);
#endif
#ifdef XYO_OS_UNIX
				char strExe[PATH_MAX];
				memset(strExe, 0, sizeof(strExe));
				if(readlink("/proc/self/exe", strExe, PATH_MAX) == -1) {
					strcpy(strExe, ".");
				};
#endif
				pathMain = normalize(strExe);
				if (String::indexOfFromEnd(pathMain, pathSeparator, 0, idx)) {
					pathMain = String::substring(pathMain, 0, idx);
				} else {
					pathMain = ".";
				};

				if(pathMain == ".") {
					pathMain = getCwd();
				};

				return pathMain;
			};

			bool removeDirContentRecursively(const String &dirName) {
				TDynamicArray<String> dirList;
				TDynamicArray<String> fileList;
				size_t k, m;
				ShellFind scan;
				k = 0;
				m = 0;
				String findDir = dirName;
				findDir += pathSeparator;
				findDir += "*";
				if(scan.find(findDir)) {
					for(; scan; scan.next()) {
						if(scan.isDirectory) {
							if(StringCore::isEqual(scan.name, "..")) {
								continue;
							};
							if(StringCore::isEqual(scan.name, ".")) {
								continue;
							};

							dirList[k] = dirName;
							dirList[k] += pathSeparator;
							dirList[k] += scan.name;
							++k;

						} else {
							fileList[m] = dirName;
							fileList[m] += pathSeparator;
							fileList[m] += scan.name;
							++m;
						};
					};
				};
				//
				for(k = 0; k < dirList.length(); ++k) {
					if(!removeDirContentRecursively(dirList[k])) {
						return false;
					};
					if(!rmdir(dirList[k])) {
						return false;
					};
				};
				for(k = 0; k < fileList.length(); ++k) {
					if(!remove(fileList[k])) {
						return false;
					};
				};
				return true;
			};

			bool removeDirRecursively(const String &dirName) {
				if(!removeDirContentRecursively(dirName)) {
					return false;
				};
				return rmdir(dirName);
			};

			void getFileList(const String &fileName, TDynamicArray<String> &fileList) {
				size_t index;
				fileList.empty();

				String fileName_ = getFileName(fileName);
				if(String::indexOf(fileName_, "*", 0, index) || String::indexOf(fileName_, "?", 0, index)) {
					size_t m;
					ShellFind scan;

					m = 0;
					String dirName = getFilePathX(fileName);
					if(scan.find(fileName)) {
						for(; scan; scan.next()) {
							if(!scan.isDirectory) {
								fileList[m] = dirName;
								fileList[m] += scan.name;
								++m;
							};
						};
					};

					return;
				};

				if(fileExists(fileName)) {
					fileList[0] = fileName;
				};
			};

			void getDirList(const String &fileName, TDynamicArray<String> &dirList) {
				size_t index;
				dirList.empty();

				String fileName_ = getFileName(fileName);
				if(String::indexOf(fileName_, "*", 0, index) || String::indexOf(fileName_, "?", 0, index)) {
					size_t m;
					ShellFind scan;

					m = 0;
					String dirName = getFilePathX(fileName);
					if(scan.find(fileName)) {
						for(; scan; scan.next()) {
							if(scan.isDirectory) {

								if(StringCore::isEqual(scan.name, "..")) {
									continue;
								};
								if(StringCore::isEqual(scan.name, ".")) {
									continue;
								};

								dirList[m] = dirName;
								dirList[m] += scan.name;
								++m;
							};
						};
					};

					return;
				};

				if(directoryExists(fileName)) {
					dirList[0] = fileName;
				};
			};

			bool mkdirRecursively(const String &dirName) {
				String dirName_ = normalize(dirName);
				if(dirName_.isEmpty()) {
					return false;
				};
				TDynamicArray<String> dirList;
				size_t k = 0;
				size_t index = 0;
				while(index < dirName_.length()) {
					if(String::indexOf(dirName_, pathSeparator, index + 1, index)) {
						dirList[k] = String::substring(dirName_, 0, index);
						++k;
						continue;
					};
					dirList[k] = dirName_;
					++k;
					break;
				};
				for(k = 0; k < dirList.length(); ++k) {
					if(directoryExists(dirList[k])) {
						continue;
					};
					if(!mkdir(dirList[k])) {
						return false;
					};
				};
				return true;
			};

			bool removeEmptyDirRecursively(const String &dirName) {
				TDynamicArray<String> dirList;
				size_t k;
				ShellFind scan;
				k = 0;

				String findDir = dirName;
				findDir += pathSeparator;
				findDir += "*";
				bool hasFiles = false;
				if(scan.find(findDir)) {
					for(; scan; scan.next()) {
						if(scan.isDirectory) {
							if(StringCore::isEqual(scan.name, "..")) {
								continue;
							};
							if(StringCore::isEqual(scan.name, ".")) {
								continue;
							};

							dirList[k] = dirName;
							dirList[k] += pathSeparator;
							dirList[k] += scan.name;
							++k;

						};
						hasFiles = true;
					};
				};
				//
				for(k = 0; k < dirList.length(); ++k) {
					if(!removeEmptyDirRecursively(dirList[k])) {
						return false;
					};
				};
				if(hasFiles) {
					return false;
				};
				return rmdir(dirName);
			};

			bool copyDirRecursively(const String &source, const String &target) {
				TDynamicArray<String> dirList;
				TDynamicArray<String> fileList;
				size_t k, m;
				ShellFind scan;
				k = 0;
				m = 0;
				String findDir = source;
				findDir += pathSeparator;
				findDir += "*";
				if(scan.find(findDir)) {
					for(; scan; scan.next()) {
						if(scan.isDirectory) {
							if(StringCore::isEqual(scan.name, "..")) {
								continue;
							};
							if(StringCore::isEqual(scan.name, ".")) {
								continue;
							};

							dirList[k] = scan.name;
							++k;
						} else {
							fileList[m] = scan.name;
							++m;
						};
					};
				};
				//
				if(!mkdirRecursivelyIfNotExists(target)) {
					return false;
				};
				//
				for(k = 0; k < dirList.length(); ++k) {

					String path = target;
					path += pathSeparator;
					path += dirList[k];

					if(!mkdirRecursivelyIfNotExists(path)) {
						return false;
					};

					String pathSource;
					pathSource = source;
					pathSource += pathSeparator;
					pathSource += dirList[k];

					String pathTarget;
					pathTarget = target;
					pathTarget += pathSeparator;
					pathTarget += dirList[k];

					if(!copyDirRecursively(pathSource, pathTarget)) {
						return false;
					};
				};
				//
				for(k = 0; k < fileList.length(); ++k) {
					String fileSource;
					fileSource = source;
					fileSource += pathSeparator;
					fileSource += fileList[k];

					String fileTarget;
					fileTarget = target;
					fileTarget += pathSeparator;
					fileTarget += fileList[k];

					if(!copy(fileSource, fileTarget)) {
						return false;
					};

				};
				return true;
			};

			bool removeFileRecursively(const String &dirName, const String &fileName) {
				TDynamicArray<String> dirList;
				TDynamicArray<String> fileList;
				size_t k, m;
				ShellFind scan;
				k = 0;

				String findDir = dirName;
				findDir += pathSeparator;
				findDir += "*";
				if(scan.find(findDir)) {
					for(; scan; scan.next()) {
						if(scan.isDirectory) {
							if(StringCore::isEqual(scan.name, "..")) {
								continue;
							};
							if(StringCore::isEqual(scan.name, ".")) {
								continue;
							};
							dirList[k] = scan.name;
							++k;
						};
					};
				};
				//

				m = 0;
				String findFile = dirName;
				findFile += pathSeparator;
				findFile += fileName;
				if(scan.find(findFile)) {
					for(; scan; scan.next()) {
						if(scan.isDirectory) {
							continue;
						};
						fileList[m] = scan.name;
						++m;
					};
				};
				//
				for(k = 0; k < fileList.length(); ++k) {
					String file;
					file = dirName;
					file += pathSeparator;
					file += fileList[k];
					if(!remove(file)) {
						return false;
					};
				};
				//
				for(k = 0; k < dirList.length(); ++k) {
					String path;
					path = dirName;
					path += pathSeparator;
					path += dirList[k];
					if(!removeFileRecursively(path, fileName)) {
						return false;
					};
				};
				return true;
			};

			bool copyFilesToDirectory(const String &source, const String &target) {
				TDynamicArray<String> fileList;
				size_t k, m;
				ShellFind scan;

				m = 0;
				String findDir = source;
				String sourcePath = source;
				if(String::indexOf(source, "*", 0, k) || String::indexOf(source, "?", 0, k)) {
					sourcePath = getFilePath(source);
				} else {
					findDir += pathSeparator;
					findDir += "*";
				};
				if(scan.find(findDir)) {
					for(; scan; scan.next()) {
						if(!scan.isDirectory) {
							fileList[m] = scan.name;
							++m;
						};
					};
				};
				//
				if(!mkdirRecursively(target)) {
					return false;
				};
				for(k = 0; k < fileList.length(); ++k) {
					String fileSource;
					fileSource = sourcePath;
					fileSource += pathSeparator;
					fileSource += fileList[k];

					String fileTarget;
					fileTarget = target;
					fileTarget += pathSeparator;
					fileTarget += fileList[k];

					if(!copy(fileSource, fileTarget)) {
						return false;
					};
				};
				return true;
			};

			bool mkdirRecursivelyIfNotExists(const String &path) {
				if(fileExists(path)) {
					return false;
				};
				if(directoryExists(path)) {
					return true;
				};
				return mkdirRecursively(path);
			};

			bool mkdirFilePath(const String &fileName) {
				String path = getFilePath(fileName);
				if(!path.isEmpty()) {
					return mkdirRecursivelyIfNotExists(path);
				};
				return true;
			};

			bool copyFile(const String &source, const String &target) {
				if(!mkdirFilePath(target)) {
					return false;
				};
				return copy(source, target);
			};

			bool fileReplaceText(const String &fileInName, const String &fileOutName, TDynamicArray<TDynamicArray<String> > &textInOut, size_t maxLineSize) {
				File fileIn;
				File fileOut;
				String line;
				String lineFinal;
				size_t k;
				if(!mkdirFilePath(fileOutName)) {
					return false;
				};
				if(fileIn.openRead(fileInName)) {
					if(fileOut.openWrite(fileOutName)) {
						while(StreamX::readLn(fileIn, line, maxLineSize)) {
							lineFinal = line;
							for(k = 0; k < textInOut.length(); ++k) {
								lineFinal = String::replace(lineFinal, textInOut[k][0], textInOut[k][1]);
							};
							if(StreamX::write(fileOut, lineFinal) != lineFinal.length()) {
								return false;
							};
						};
						return true;
					};
				};
				return false;
			};

			bool isChanged(const String &target, TDynamicArray<String> &source) {
				int k;
				if(!fileExists(target)) {
					return true;
				};
				FileTime targetTime;
				FileTime sourceTime;
				targetTime.getLastWriteTime(target);
				for(k = 0; k < source.length(); ++k) {
					sourceTime.getLastWriteTime(source[k]);
					if(targetTime.compare(sourceTime) < 0) {
						return true;
					};
				};
				return false;
			};

			bool isChangedRecursive(const char *target, const char *source, const char *basePath) {
				int k;
				size_t index;
				TDynamicArray<String> fileList;
				String pathToSearch = source;
				String basePathX;
				String fileName;

				if(!fileExists(target)) {
					return true;
				};

				if(!(String::indexOf(pathToSearch, "*", 0, index) || String::indexOf(pathToSearch, "?", 0, index))) {
					pathToSearch += "/*";
				};

				if(basePath) {
					basePathX = basePath;
				} else {
					basePathX = getFilePathX(pathToSearch);
				};

				getFileList(pathToSearch, fileList);
				for(k = 0; k < fileList.length(); ++k) {
					if(compareLastWriteTime(target, fileList[k]) < 0) {
						return true;
					};
				};

				getDirList(pathToSearch, fileList);
				for(k = 0; k < fileList.length(); ++k) {
					if(isChangedRecursive(target, fileList[k], basePathX)) {
						return true;
					};
				};

				return false;
			};

			bool copyFileIfExists(const String &source, const String &target) {
				if(!fileExists(source)) {
					return true;
				};
				return copyFile(source, target);
			};

			void mainArgsFilter(char *cmdX) {
				char *result;
				char *scan;
				char *check;
				result = cmdX;
				scan = cmdX;
				while(*scan != '\0') {
					if(*scan == '\\') {
						check = scan + 1;
						while(*check != '\0') {
							if(*check == '\\') {
								++check;
								continue;
							};
							break;
						};
						if(*check == '"') {

							while(*scan != '\0') {
								if(*scan == '\\') {
									++scan;
									*result = *scan;
									++result;
									++scan;
									continue;
								};
								break;
							};
							continue;
						};
						while(*scan != '\0') {
							if(*scan == '\\') {
								*result = *scan;
								++result;
								++scan;
								continue;
							};
							break;
						};
						continue;
					};
					if(*scan == '"') {
						++scan;
						continue;
					};
					*result = *scan;
					++result;
					++scan;
				};
				*result = '\0';
			};

			void mainArgsParse(bool commit, const char *cmdLine, int &cmdN, char** &cmdS) {
				const char *cmdLineScan;
				const char *cmdLastLineScan;
				int cmdSize;

				// exe name is first
				cmdN = 1;

				cmdLineScan = cmdLine;
				// ignore first spaces
				while(*cmdLineScan != '\0') {
					if(*cmdLineScan == ' ' || *cmdLineScan == '\t' || *cmdLineScan == '\r' || *cmdLineScan == '\n') {
						while(*cmdLineScan == ' ' || *cmdLineScan == '\t' || *cmdLineScan == '\r' || *cmdLineScan == '\n') {
							++cmdLineScan;
							if(*cmdLineScan == '\0') {
								break;
							};
						};
						if(*cmdLineScan == '\0') {
							break;
						};
						continue;
					};
					break;
				};
				//
				cmdLastLineScan = cmdLineScan;
				cmdSize = 0;
				while(*cmdLineScan != '\0') {
					if(*cmdLineScan == ' ' || *cmdLineScan == '\t' || *cmdLineScan == '\r' || *cmdLineScan == '\n') {
						if(cmdSize > 0) {
							if(commit) {
								cmdS[cmdN] = new char[cmdSize + 1];
								memcpy(cmdS[cmdN], cmdLastLineScan, cmdSize);
								cmdS[cmdN][cmdSize] = '\0';
							};
							++cmdN;
						};
						while(*cmdLineScan == ' ' || *cmdLineScan == '\t' || *cmdLineScan == '\r' || *cmdLineScan == '\n') {
							++cmdLineScan;
							if(*cmdLineScan == '\0') {
								break;
							};
						};
						cmdLastLineScan = cmdLineScan;
						cmdSize = 0;
						if(*cmdLineScan == '\0') {
							break;
						};
						continue;
					};
					if(*cmdLineScan == '\\') {
						++cmdSize;
						++cmdLineScan;
						if(*cmdLineScan != '\0') {
							++cmdSize;
							++cmdLineScan;
						};
						continue;
					};
					if(*cmdLineScan == '\"') {
						if(cmdSize == 0) {
							cmdLastLineScan = cmdLineScan;
							++cmdSize;
							++cmdLineScan;
							while(*cmdLineScan != '\0') {
								if(*cmdLineScan == '\\') {
									++cmdSize;
									++cmdLineScan;
									if(*cmdLineScan != '\0') {
										++cmdSize;
										++cmdLineScan;
									};
									continue;
								};
								if(*cmdLineScan == '\"') {
									++cmdSize;
									++cmdLineScan;
									break;
								};
								++cmdSize;
								++cmdLineScan;
							};

							if(commit) {
								cmdS[cmdN] = new char[cmdSize + 1];
								memcpy(cmdS[cmdN], cmdLastLineScan, cmdSize);
								cmdS[cmdN][cmdSize] = '\0';
							};
							++cmdN;

							cmdLastLineScan = cmdLineScan;
							cmdSize = 0;
							continue;
						} else {
							++cmdSize;
							++cmdLineScan;
							while(*cmdLineScan != '\0') {
								if(*cmdLineScan == '\\') {
									++cmdSize;
									++cmdLineScan;
									if(*cmdLineScan != '\0') {
										++cmdSize;
										++cmdLineScan;
									};
									continue;
								};
								if(*cmdLineScan == '\"') {
									++cmdSize;
									++cmdLineScan;
									break;
								};
								++cmdSize;
								++cmdLineScan;
							};
							if(*cmdLineScan == '\0') {
								if(commit) {
									cmdS[cmdN] = new char[cmdSize + 1];
									memcpy(cmdS[cmdN], cmdLastLineScan, cmdSize);
									cmdS[cmdN][cmdSize] = '\0';
								};
								++cmdN;

								break;
							};
							continue;
						};
					};
					++cmdSize;
					++cmdLineScan;
					if(*cmdLineScan == '\0') {
						if(commit) {
							cmdS[cmdN] = new char[cmdSize + 1];
							memcpy(cmdS[cmdN], cmdLastLineScan, cmdSize);
							cmdS[cmdN][cmdSize] = '\0';
						};
						++cmdN;
						break;
					};
				};
			};

			void mainArgsDelete(int cmdN, char **cmdS) {
				int k;
				for(k = 0; k < cmdN; ++k) {
					delete[] cmdS[k];
				};
				delete[] cmdS;
			};

			void mainArgsSet(const char *exeName, const char *cmdLine, int &cmdN, char** &cmdS) {
				int cmdSize;
				int k;

				mainArgsParse(false, cmdLine, cmdN, cmdS);

				cmdS = new char *[cmdN];
				cmdSize = strlen(exeName);
				cmdS[0] = new char[cmdSize + 1];
				memcpy(cmdS[0], exeName, cmdSize);
				cmdS[0][cmdSize] = '\0';

				mainArgsParse(true, cmdLine, cmdN, cmdS);

				for(k = 0; k < cmdN; ++k) {
					mainArgsFilter(cmdS[k]);
				};

				if(strlen(cmdS[0]) == 0) {
					delete[] cmdS[0];
					--cmdN;
					memcpy(cmdS, cmdS + 1, cmdN * sizeof(char *));
					cmdS[cmdN] = nullptr;
					return;
				};

				if(cmdN > 1) {
					if(strlen(cmdS[0]) > 0) {
						if(strcmp(cmdS[0], cmdS[1]) == 0) {
							delete[] cmdS[0];
							--cmdN;
							memcpy(cmdS, cmdS + 1, cmdN * sizeof(char *));
							cmdS[cmdN] = nullptr;
						} else {
							char fullPath1[4096];
							char fullPath2[4096];
							if(realpath(cmdS[0], fullPath1, 4096)) {
								if(realpath(cmdS[1], fullPath2, 4096)) {
									if(StringCore::compareIgnoreCaseAscii(fullPath1, fullPath2) == 0) {
										delete[] cmdS[0];
										--cmdN;
										memcpy(cmdS, cmdS + 1, cmdN * sizeof(char *));
										cmdS[cmdN] = nullptr;
									};
								};
							};
						};
					};
				};
			};

			void mainArgsSet(const char *cmdLine, int &cmdN, char** &cmdS) {
				int k;

				mainArgsParse(false, cmdLine, cmdN, cmdS);

				cmdS = new char *[cmdN];
				cmdS[0] = nullptr;

				mainArgsParse(true, cmdLine, cmdN, cmdS);

				--cmdN;
				memcpy(cmdS, cmdS + 1, cmdN * sizeof(char *));
				cmdS[cmdN] = nullptr;

				for(k = 0; k < cmdN; ++k) {
					mainArgsFilter(cmdS[k]);
				};
			};

		};
	};
};

