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

#include "xyo-system-processor.hpp"

namespace XYO {
	namespace System {
		namespace Processor {

			int32_t getCount() {
				return GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);
			};

		};
	};
};

#endif
