//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_SYSTEM_SHELL_HPP
#define XYO_SYSTEM_SHELL_HPP

#ifndef XYO_ENCODING_STRING_HPP
#	include "xyo-encoding-string.hpp"
#endif

#ifndef XYO_SYSTEM_SHELLFIND_HPP
#	include "xyo-system-shellfind.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_BUFFER_HPP
#	include "xyo-datastructures-buffer.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TDYNAMICARRAY_HPP
#	include "xyo-datastructures-tdynamicarray.hpp"
#endif

namespace XYO {
	namespace System {
		namespace Shell {
			using namespace XYO::DataStructures;
			using namespace XYO::Encoding;

			typedef uint32_t ProcessId;

			XYO_EXPORT bool chdir(const char *path);
			XYO_EXPORT bool rmdir(const char *path);
			XYO_EXPORT bool mkdir(const char *path);
			XYO_EXPORT bool getcwd(char *buffer, size_t bufferSize);
			XYO_EXPORT bool copy(const char *source, const char *destination);
			XYO_EXPORT bool rename(const char *source, const char *destination);
			XYO_EXPORT bool remove(const char *file);
			XYO_EXPORT int compareLastWriteTime(const char *fileA, const char *fileB);
			XYO_EXPORT int system(const char *cmd);
			XYO_EXPORT bool touch(const char *file);
			XYO_EXPORT bool fileExists(const char *file);
			XYO_EXPORT bool directoryExists(const char *directory);
			XYO_EXPORT char *getenv(const char *name);
			XYO_EXPORT bool setenv(const char *name, const char *value);
			XYO_EXPORT bool realpath(const char *fileNameIn, char *fileNameOut, long int fileNameOutSize);

			XYO_EXPORT uint32_t execute(const char *cmd);
			XYO_EXPORT uint32_t executeHidden(const char *cmd);
			XYO_EXPORT ProcessId executeNoWait(const char *cmd);
			XYO_EXPORT ProcessId executeHiddenNoWait(const char *cmd);
			XYO_EXPORT bool isProcessTerminated(const ProcessId processId);
			XYO_EXPORT bool terminateProcess(const ProcessId processId, const uint32_t waitMilliseconds_);
			XYO_EXPORT uint32_t executeWriteOutputToFile(const char *cmd, const char *out);
			XYO_EXPORT extern const char *pathSeparator;
			XYO_EXPORT extern const char *envPathSeparator;

			XYO_EXPORT String normalize(const String &fileOrDirName);

			// ---

			XYO_EXPORT String getFileName(const String &fileName);
			XYO_EXPORT String getFileExtension(const String &fileName);
			XYO_EXPORT String getFileBasename(const String &fileName);
			XYO_EXPORT String getFilePath(const String &fileName);
			XYO_EXPORT String getFilePathX(const String &fileName);
			XYO_EXPORT bool isEmptyDir(const char *dirName);
			XYO_EXPORT bool removeEmptyDir(const char *dirName);
			XYO_EXPORT bool removeFile(const char *file);
			XYO_EXPORT bool removeFileAndDirectoryIfEmpty(const String &target);
			XYO_EXPORT bool touchIfExists(const char *file);
			XYO_EXPORT bool isEnv(const char *name, const char *value);
			XYO_EXPORT bool hasEnv(const char *name);
			XYO_EXPORT bool fileGetContents(const char *fileName, String &output);
			XYO_EXPORT bool filePutContents(const char *fileName, const String &value);
			XYO_EXPORT bool filePutContentsAppend(const char *fileName, const String &value);
			XYO_EXPORT bool fileGetContents(const char *fileName, Buffer &output);
			XYO_EXPORT bool filePutContents(const char *fileName, const Buffer &value);
			XYO_EXPORT bool filePutContents(const char *fileName, const uint8_t *data, size_t dataSize);
			XYO_EXPORT String getEnv(const char *name);
			XYO_EXPORT String getCwd();
			XYO_EXPORT bool realPath(const char *path, String &out);
			XYO_EXPORT bool fileGetContentsSkipLines(const String &fileName, String &output, int linesToSkip, size_t lineSize);
			XYO_EXPORT bool isAbsolutePath(const char *path);
			XYO_EXPORT String getExecutable();
			XYO_EXPORT String getExecutablePath();
			XYO_EXPORT bool removeDirContentRecursively(const String &dirName);
			XYO_EXPORT bool removeDirRecursively(const String &dirName);
			XYO_EXPORT void getFileList(const String &fileName, TDynamicArray<String> &fileList);
			XYO_EXPORT void getDirList(const String &fileName, TDynamicArray<String> &dirList);
			XYO_EXPORT bool mkdirRecursively(const String &dirName);
			XYO_EXPORT bool removeEmptyDirRecursively(const String &dirName);
			XYO_EXPORT bool copyDirRecursively(const String &source, const String &target);
			XYO_EXPORT bool moveDirRecursively(const String &source, const String &target, bool overwrite);
			XYO_EXPORT bool removeFileRecursively(const String &dirName, const String &fileName);
			XYO_EXPORT bool copyFilesToDirectory(const String &source, const String &target);
			XYO_EXPORT bool mkdirRecursivelyIfNotExists(const String &path);
			XYO_EXPORT bool mkdirFilePath(const String &fileName);
			XYO_EXPORT bool copyFile(const String &source, const String &target);
			XYO_EXPORT bool fileReplaceText(const String &fileInName, const String &fileOutName, TDynamicArray<TDynamicArray<String>> &textInOut, size_t maxLineSize);
			XYO_EXPORT bool isChanged(const String &target, TDynamicArray<String> &source);
			XYO_EXPORT bool isChangedRecursive(const char *target, const char *source, const char *basePath = nullptr);
			//
			XYO_EXPORT bool copyFileIfExists(const String &source, const String &target);
			//
			XYO_EXPORT void mainArgsFilter(char *cmdX);
			XYO_EXPORT void mainArgsParse(bool commit, const char *cmdLine, int &cmdN, char **&cmdS);
			XYO_EXPORT void mainArgsDelete(int cmdN, char **cmdS);
			XYO_EXPORT void mainArgsSet(const char *exeName, const char *cmdLine, int &cmdN, char **&cmdS);
			XYO_EXPORT void mainArgsSet(const char *cmdLine, int &cmdN, char **&cmdS);

		};
	};
};

#endif
