//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO__DEPENDENCY_HPP
#define XYO__DEPENDENCY_HPP

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <typeinfo>
#include <utility>
#include <stdexcept>
#include <new>
#include <atomic>
#include <functional>
#include <type_traits>

#ifndef XYO__CONFIG_HPP
#include "xyo--config.hpp"
#endif

#ifndef XYO__EXPORT_HPP
#include "xyo--export.hpp"
#endif

// -- Defaults

#ifndef XYO_MULTI_THREAD
#       ifndef XYO_SINGLE_THREAD
#               define XYO_MULTI_THREAD
#       endif
#endif

#ifndef XYO_APPLICATION_64BIT
#       ifndef XYO_APPLICATION_32BIT
#               define XYO_APPLICATION_64BIT
#       endif
#endif

// -- Checking

#ifndef XYO_COMPILER_MSVC
#       ifndef XYO_COMPILER_GCC
#               error "XYO_COMPILER_MSVC or XYO_COMPILER_GCC must be defined"
#       endif
#endif

#ifndef XYO_OS_WINDOWS
#       ifndef XYO_OS_UNIX
#               ifndef XYO_OS_MINGW
#                       error "XYO_OS_WINDOWS or XYO_OS_UNIX or XYO_OS_MINGW must be defined"
#               endif
#       endif
#endif

#ifndef XYO_MULTI_THREAD
#       ifndef XYO_SINGLE_THREAD
#               error "XYO_MULTI_THREAD or XYO_SINGLE_THREAD must be defined"
#       endif
#endif

#ifndef XYO_APPLICATION_64BIT
#       ifndef XYO_APPLICATION_32BIT
#               error "XYO_APPLICATION_64BIT or XYO_APPLICATION_32BIT must be defined"
#       endif
#endif

//

#ifdef XYO_OS_WINDOWS
#       ifdef XYO_MEMORY_LEAK_DETECTOR_VLD
#               ifndef WIN32_LEAN_AND_MEAN
#                       define WIN32_LEAN_AND_MEAN
#               endif
#               include <windows.h>
#               include "vld.h"
#       endif
#endif

//

#ifdef XYO_MULTI_THREAD
#       ifdef XYO_COMPILER_MSVC
#               define XYO_THREAD_LOCAL __declspec(thread)
#       endif
#       ifdef XYO_COMPILER_GCC
#               define XYO_THREAD_LOCAL __thread
#       endif
#else
#       define XYO_THREAD_LOCAL
#endif

//

#ifdef XYO_APPLICATION_64BIT
#       define XYO_FORMAT_UINT32T "%u"
#       define XYO_FORMAT_SIZET_HEX "%16lX"
#       ifdef XYO_COMPILER_GCC
#               define XYO_FORMAT_SIZET "%lu"
#       else
#               define XYO_FORMAT_SIZET "%llu"
#       endif
#else
#       define XYO_FORMAT_UINT32T "%lu"
#       define XYO_FORMAT_SIZET_HEX "%08X"
#       define XYO_FORMAT_SIZET "%lu"
#endif

//

#define XYO_DISALLOW_COPY_ASSIGN_MOVE(T) \
	private:\
	T(const T&) = delete;\
	T(T&&) = delete;\
	T& operator =(const T&) = delete;\
	T& operator =(T&&) = delete

#define XYO_INTERFACE(T) \
	protected:\
	T() = default;\
	~T() = default;\
	XYO_DISALLOW_COPY_ASSIGN_MOVE(T)

#endif
