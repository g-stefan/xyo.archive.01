//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO__DEPENDENCY_HPP
#	include "xyo--dependency.hpp"
#endif

#ifdef XYO_OS_WINDOWS

#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>

#	include "xyo-multithreading-criticalsection.hpp"

#	ifdef XYO_MULTI_THREAD

namespace XYO {
	namespace Multithreading {

		class CriticalSection_ {
			public:
				CRITICAL_SECTION section;
		};

		CriticalSection::CriticalSection() {
			criticalSection = new CriticalSection_();
			InitializeCriticalSection(&criticalSection->section);
		};

		CriticalSection::~CriticalSection() {
			DeleteCriticalSection(&criticalSection->section);
			delete criticalSection;
		};

		void CriticalSection::enter() {
			EnterCriticalSection(&criticalSection->section);
		};

		void CriticalSection::leave() {
			LeaveCriticalSection(&criticalSection->section);
		};

	};
};

#	endif

#endif
