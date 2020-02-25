//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MULTITHREADING_CRITICALSECTION_HPP
#define XYO_MULTITHREADING_CRITICALSECTION_HPP

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

#ifdef XYO_MULTI_THREAD
namespace XYO {
	namespace Multithreading {

		class CriticalSection_;

		class CriticalSection {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(CriticalSection);

			protected:

				CriticalSection_ *criticalSection;

			public:

				static const bool isCriticalSection = true;

				XYO_EXPORT CriticalSection();
#ifdef XYO_OS_UNIX
				XYO_EXPORT ~CriticalSection() noexcept(false);
#else
				XYO_EXPORT ~CriticalSection();
#endif

				XYO_EXPORT void enter();
				XYO_EXPORT void leave();
		};

	};
};
#endif

#ifdef XYO_SINGLE_THREAD
namespace XYO {
	namespace Multithreading {

		class CriticalSection {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(CriticalSection);

			public:

				static const bool isCriticalSection = false;

				CriticalSection() = default ;

				inline void enter() {
				};

				inline void leave() {
				};
		};

	};
};
#endif

#endif

