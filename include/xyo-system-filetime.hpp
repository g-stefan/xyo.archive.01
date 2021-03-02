//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_SYSTEM_FILETIME_HPP
#define XYO_SYSTEM_FILETIME_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TDYNAMICARRAY_HPP
#include "xyo-datastructures-tdynamicarray.hpp"
#endif

namespace XYO {
	namespace System {
		using namespace XYO::ManagedMemory;

		class FileTime_;

		class FileTime : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(FileTime);

			protected:

				FileTime_ *fileTime;

			public:

				XYO_EXPORT FileTime();
				XYO_EXPORT ~FileTime();

				XYO_EXPORT bool getCreationTime(const char *file);
				XYO_EXPORT bool getLastAccessTime(const char *file);
				XYO_EXPORT bool getLastWriteTime(const char *file);
				XYO_EXPORT int compare(FileTime &x);
				XYO_EXPORT bool isChanged(TDynamicArray<FileTime> &x);
		};

	};
};

#endif

