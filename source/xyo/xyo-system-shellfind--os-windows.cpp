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

#include <direct.h>
#include <io.h>
#include <sys/stat.h>

#include "xyo-system-shellfind.hpp"
#include "xyo-encoding-string.hpp"

namespace XYO {
	namespace System {
		using namespace XYO::DataStructures;
		using namespace XYO::Encoding;

		struct SShellFind_ {
			struct _finddata_t finddata;
			intptr_t hfind;
		};

		ShellFind::ShellFind() {
			isFile = false;
			isDirectory = false;
			isReadOnly = false;
			isValid_ = false;

			shellFind_ = new SShellFind_();
			shellFind_->hfind = -1;
			memset(&shellFind_->finddata, 0, sizeof (struct _finddata_t));
		};

		ShellFind::~ShellFind() {
			close();
			delete shellFind_;
		};

		bool ShellFind::next() {
			if(isValid_) {
				if (_findnext(shellFind_->hfind, &shellFind_->finddata) == 0) {
					name = shellFind_->finddata.name;
					isDirectory = (shellFind_->finddata.attrib & _A_SUBDIR) == _A_SUBDIR;
					isFile = !isDirectory;
					isReadOnly = (shellFind_->finddata.attrib & _A_RDONLY) == _A_RDONLY;
					return true;
				};
				close();
			};
			return false;
		};

		void ShellFind::close() {
			if (shellFind_->hfind != -1) {
				_findclose(shellFind_->hfind);
				shellFind_->hfind = -1L;
			};
			isValid_ = false;
		};

		bool ShellFind::find(const char *name_) {
			shellFind_->hfind = _findfirst(name_, &shellFind_->finddata);
			if (shellFind_->hfind != -1L) {
				isValid_ = true;
				name = shellFind_->finddata.name;
				isDirectory = (shellFind_->finddata.attrib & _A_SUBDIR) == _A_SUBDIR;
				isFile = !isDirectory;
				isReadOnly = (shellFind_->finddata.attrib & _A_RDONLY) == _A_RDONLY;
				return true;
			};
			return false;
		};
	};
};

#endif

