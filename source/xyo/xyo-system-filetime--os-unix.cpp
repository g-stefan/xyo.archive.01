//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

#ifdef XYO_OS_UNIX

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "xyo-system-filetime.hpp"

namespace XYO {
	namespace System {
		using namespace XYO::ManagedMemory;

		class FileTime_ {
			public:
				struct timespec value;
		};

		FileTime::FileTime() {
			fileTime = nullptr;
		};

		FileTime::~FileTime() {
			if(fileTime) {
				delete fileTime;
			};
		};

		bool FileTime::getCreationTime(const char *file) {
			struct stat attrib;
			if(stat(file, &attrib)) {
				if(fileTime) {
					delete fileTime;
					fileTime = nullptr;
				};
				return false;
			};
			if(!fileTime) {
				fileTime = new FileTime_();
			};
			memcpy(&fileTime->value, &attrib.st_ctim, sizeof(struct timespec));
			return true;
		};

		bool FileTime::getLastAccessTime(const char *file) {
			struct stat attrib;
			if(stat(file, &attrib)) {
				if(fileTime) {
					delete fileTime;
					fileTime = nullptr;
				};
				return false;
			};
			if(!fileTime) {
				fileTime = new FileTime_();
			};
			memcpy(&fileTime->value, &attrib.st_atim, sizeof(struct timespec));
			return true;
		};

		bool FileTime::getLastWriteTime(const char *file) {
			struct stat attrib;
			if(stat(file, &attrib)) {
				if(fileTime) {
					delete fileTime;
					fileTime = nullptr;
				};
				return false;
			};
			if(!fileTime) {
				fileTime = new FileTime_();
			};
			memcpy(&fileTime->value, &attrib.st_mtim, sizeof(struct timespec));
			return true;
		};

		int FileTime::compare(FileTime &x) {
			if(!fileTime) {
				if(!x.fileTime) {
					return 0;
				} else {
					return -1;
				};
			} else {
				if(!x.fileTime) {
					return 1;
				};
			};
			if(fileTime->value.tv_sec == x.fileTime->value.tv_sec) {
				return (int) (fileTime->value.tv_nsec - x.fileTime->value.tv_nsec);
			};
			return (int) (fileTime->value.tv_sec - x.fileTime->value.tv_sec);
		};

		uint64_t FileTime::toUnixTime() {
			if(!fileTime) {
				return (uint64_t)0;
			};			
			return (uint64_t)fileTime->value.tv_sec;
		};

		void FileTime::fromUnixTime(uint64_t t) {
			if(!fileTime) {
				fileTime = new FileTime_();
			};
			fileTime->value.tv_sec = t;
			fileTime->value.tv_nsec = 0;
		};

	};
};


#endif
