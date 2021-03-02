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

#ifdef XYO_OS_WINDOWS

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "xyo-system-filetime.hpp"

namespace XYO {
	namespace System {
		using namespace XYO::ManagedMemory;

		class FileTime_ {
			public:
				FILETIME value;
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
			HANDLE hFile;
			hFile = CreateFile(file, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
			if (hFile == INVALID_HANDLE_VALUE) {
				if(fileTime) {
					delete fileTime;
					fileTime = nullptr;
				};
				return false;
			};
			if(!fileTime) {
				fileTime = new FileTime_();
			};
			if(!GetFileTime(hFile, &fileTime->value, nullptr, nullptr)){
				delete fileTime;
				fileTime = nullptr;
				return false;
			};
			CloseHandle(hFile);
			return true;
		};

		bool FileTime::getLastAccessTime(const char *file) {
			HANDLE hFile;
			hFile = CreateFile(file, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
			if (hFile == INVALID_HANDLE_VALUE) {
				if(fileTime) {
					delete fileTime;
					fileTime = nullptr;
				};
				return false;
			};
			if(!fileTime) {
				fileTime = new FileTime_();
			};
			if(!GetFileTime(hFile, nullptr, &fileTime->value, nullptr)){
				delete fileTime;
				fileTime = nullptr;
				return false;
			};
			CloseHandle(hFile);
			return true;
		};

		bool FileTime::getLastWriteTime(const char *file) {
			HANDLE hFile;
			hFile = CreateFile(file, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
			if (hFile == INVALID_HANDLE_VALUE) {
				if(fileTime) {
					delete fileTime;
					fileTime = nullptr;
				};				
				return false;
			};
			if(!fileTime) {
				fileTime = new FileTime_();
			};
			if(!GetFileTime(hFile, nullptr, nullptr, &fileTime->value)){
				delete fileTime;
				fileTime = nullptr;				
				return false;
			};		
			CloseHandle(hFile);			
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
			return (int) CompareFileTime(&fileTime->value, &x.fileTime->value);
		};


	};
};

#endif
