//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO__CONFIG_HPP
#define XYO__CONFIG_HPP

// -- Operating System
#define XYO_OS_WINDOWS
//#define XYO_OS_UNIX
//#define XYO_OS_MINGW

// -- Compiler
#define XYO_COMPILER_MSVC
//#define XYO_COMPILER_GCC

// -- Platform
#define XYO_PLATFORM "win32-msvc-2019"

// -- Application
//#define XYO_APPLICATION_64BIT
#define XYO_APPLICATION_32BIT

// -- Thread support
//#define XYO_SINGLE_THREAD
#define XYO_MULTI_THREAD

// -- Compile
//#define XYO_COMPILE_RELEASE
//#define XYO_COMPILE_DEBUG
//#define XYO_COMPILE_CRT_STATIC
//#define XYO_COMPILE_CRT_DYNAMIC
//#define XYO_COMPILE_STATIC_LIBRARY
//#define XYO_COMPILE_DYNAMIC_LIBRARY

// -- Debug
//#define XYO_MEMORY_LEAK_DETECTOR_VLD
//#define XYO_TMEMORYPOOL_SYSTEM
//#define XYO_TMEMORYPOOL_ACTIVE_AS_UNIFIED
//#define XYO_TMEMORYPOOL_ACTIVE_LEVEL_IS_SYSTEM
//#define XYO_TMEMORYPOOL_UNIFIED_AS_SYSTEM
//#define XYO_TMEMORYPOOL_CHECK
//#define XYO_TMEMORYPOOL_CHECK_INFO
//#define XYO_TMEMORYPOOL_CHECK_COUNT_INFO
//#define XYO_TMEMORYPOOL_CONSTRUCTOR_INFO
//#define XYO_TMEMORYPOOL_DESTRUCTOR_INFO
//#define XYO_OBJECT_REFERENCE_COUNT_INFO

#endif
