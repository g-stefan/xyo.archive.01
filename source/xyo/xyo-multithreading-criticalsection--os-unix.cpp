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

#ifdef XYO_OS_UNIX

#	include <pthread.h>
#	include <unistd.h>

#	include "xyo-multithreading-criticalsection.hpp"

#	ifdef XYO_MULTI_THREAD

namespace XYO {
	namespace Multithreading {

		class CriticalSection_ {
			public:
				pthread_mutex_t section;
		};

		CriticalSection::CriticalSection() {
			criticalSection = new CriticalSection_();
			if (pthread_mutex_init(&criticalSection->section, nullptr)) {
				throw std::runtime_error("pthread_mutex_init");
			};
		};

		CriticalSection::~CriticalSection() noexcept(false) {
			if (pthread_mutex_destroy(&criticalSection->section)) {
				throw std::runtime_error("pthread_mutex_destroy");
			};
			delete criticalSection;
		};

		void CriticalSection::enter() {
			if (pthread_mutex_lock(&criticalSection->section)) {
				throw std::runtime_error("pthread_mutex_lock");
			};
		};

		void CriticalSection::leave() {
			if (pthread_mutex_unlock(&criticalSection->section)) {
				throw std::runtime_error("pthread_mutex_unlock");
			};
		};

	};

};

#	endif

#endif
