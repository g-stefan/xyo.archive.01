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
#include <sys/sysinfo.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "xyo-system-processor.hpp"

namespace XYO {
	namespace System {
	namespace Processor {

		int32_t getCount(){
			return sysconf (_SC_NPROCESSORS_ONLN);
		};

	};
	};
};


#endif
