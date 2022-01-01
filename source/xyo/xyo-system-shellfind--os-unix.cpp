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

#ifdef XYO_OS_UNIX

#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <spawn.h>
#include <sys/wait.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cstdio>

#include "xyo-system-shellfind.hpp"
#include "xyo-encoding-string.hpp"

#define DT_DIR__ 0x04

namespace XYO {
	namespace System {
		using namespace XYO::DataStructures;
		using namespace XYO::Encoding;

		struct SShellFind_ {
			struct dirent *finddata;
			DIR *hfind;

			String match_;
		};

		ShellFind::ShellFind() {
			isFile = false;
			isDirectory = false;
			isReadOnly = false;
			isValid_ = false;

			shellFind_ = new SShellFind_();

			shellFind_->hfind = nullptr;
			shellFind_->finddata = nullptr;
		};

		ShellFind::~ShellFind() {
			close();
			delete shellFind_;
		};

		bool ShellFind::next() {

			shellFind_->finddata = readdir(shellFind_->hfind);
			if (shellFind_->finddata == nullptr) {
				close();
				return false;
			} else {

				while (!String::matchAscii(shellFind_->finddata->d_name, shellFind_->match_.value())) {
					shellFind_->finddata = readdir(shellFind_->hfind);
					if (shellFind_->finddata != nullptr) {
					} else {
						close();
						return false;
					};
				};


				isValid_ = true;
				name = shellFind_->finddata->d_name;
				isDirectory = (shellFind_->finddata->d_type == DT_DIR__);
				isFile = !isDirectory;

				struct stat attrib;
				stat(shellFind_->finddata->d_name, &attrib);

				isReadOnly = (attrib.st_mode & (S_IWUSR == 0));
				return true;
			};


			close();
			return false;
		};

		void ShellFind::close() {
			if (shellFind_->hfind != nullptr) {
				closedir(shellFind_->hfind);
				shellFind_->hfind = nullptr;
			};
			isValid_ = false;
		};

		bool ShellFind::find(const char *name__) {
			String name_;
			String path_;
			size_t pos;

			if (StringCore::indexOfFromEnd(name__, "/", pos)) {
				path_ = String::substring(name__, 0, pos);
				name_ = String::substring(name__, pos + 1);
			} else {
				path_ = ".";
				name_ = name__;
			};

			shellFind_->match_ = name_;
			shellFind_->hfind = opendir(path_);
			if (shellFind_->hfind != nullptr) {
				shellFind_->finddata = readdir(shellFind_->hfind);
				if (shellFind_->finddata == nullptr) {
					return false;
				} else {
					while (!String::matchAscii(shellFind_->finddata->d_name, shellFind_->match_)) {
						shellFind_->finddata = readdir(shellFind_->hfind);
						if (shellFind_->finddata == nullptr) {
							return false;
						};
					};

					isValid_ = true;
					name = shellFind_->finddata->d_name;
					isDirectory = (shellFind_->finddata->d_type == DT_DIR__);
					isFile = !isDirectory;

					struct stat attrib;
					stat(shellFind_->finddata->d_name, &attrib);

					isReadOnly = (attrib.st_mode & (S_IWUSR == 0));
					return true;
				};
			};
			return false;
		};

	};
};


#endif

