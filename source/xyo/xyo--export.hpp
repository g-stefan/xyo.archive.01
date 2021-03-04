//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO__EXPORT_HPP
#define XYO__EXPORT_HPP

#ifndef XYO__CONFIG_HPP
#include "xyo--config.hpp"
#endif

#ifdef XYO_COMPILE_DYNAMIC_LIBRARY
#   ifndef XYO_LIBRARY_EXPORT
#       ifdef XYO_COMPILER_MSVC
#           define XYO_LIBRARY_EXPORT __declspec(dllexport)
#       endif
#       ifdef XYO_COMPILER_GCC
#           define XYO_LIBRARY_EXPORT
#       endif
#   endif
#   ifndef XYO_LIBRARY_IMPORT
#       ifdef XYO_COMPILER_MSVC
#           define XYO_LIBRARY_IMPORT __declspec(dllimport)
#       endif
#       ifdef XYO_COMPILER_GCC
#           define XYO_LIBRARY_IMPORT
#       endif
#   endif
#else
#   ifndef XYO_LIBRARY_EXPORT
#       define XYO_LIBRARY_EXPORT
#   endif
#   ifndef XYO_LIBRARY_IMPORT
#       define XYO_LIBRARY_IMPORT
#   endif
#endif

#ifdef  XYO_INTERNAL
#   define XYO_EXPORT XYO_LIBRARY_EXPORT
#else
#   define XYO_EXPORT XYO_LIBRARY_IMPORT
#endif

#endif
