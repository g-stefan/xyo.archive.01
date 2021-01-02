//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MULTITHREADING_SYNCHRONIZE_HPP
#define XYO_MULTITHREADING_SYNCHRONIZE_HPP

#ifndef XYO_MULTITHREADING_CRITICALSECTION_HPP
#include "xyo-multithreading-criticalsection.hpp"
#endif

#ifdef XYO_MULTI_THREAD
namespace XYO {
	namespace Multithreading {

		template<typename T>
		class Synchronize {
			public:

				static inline T process(CriticalSection &criticalSection, const std::function<T ()> &fn) {
					T retV;
					criticalSection.enter();
					try {
						retV = fn();
					} catch(...) {
						criticalSection.leave();
						throw;
					}
					criticalSection.leave();
					return retV;
				};

		};

		template<>
		class Synchronize<void> {
			public:

				static inline void process(CriticalSection &criticalSection, const std::function<void ()> &fn) {
					criticalSection.enter();
					try {
						fn();
					} catch(...) {
						criticalSection.leave();
						throw;
					}
					criticalSection.leave();
				};

		};

	};
};
#endif

#ifdef XYO_SINGLE_THREAD
namespace XYO {
	namespace Multithreading {

		template<typename T>
		struct Synchronize {

			static inline T process(CriticalSection &, const std::function<T ()> &fn) {
				return fn();
			};

		};

		template<>
		struct Synchronize<void> {

			static inline void process(CriticalSection &, const std::function<void ()> &fn) {
				fn();
			};

		};

	};
};
#endif

#endif

