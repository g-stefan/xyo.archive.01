//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MULTITHREADING_THREAD_HPP
#define XYO_MULTITHREADING_THREAD_HPP

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

#ifdef XYO_SINGLE_THREAD

namespace XYO {
	namespace Multithreading {

		struct Thread {
			XYO_EXPORT static void sleep(int milliSeconds);
		};

	};
};

#endif

#ifdef XYO_MULTI_THREAD

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

#ifndef XYO_MULTITHREADING_TATOMIC_HPP
#include "xyo-multithreading-tatomic.hpp"
#endif

namespace XYO {
	namespace Multithreading {
		using namespace XYO::ManagedMemory;

		typedef void (*ThreadProcedure)(void *);

		class Thread_;

		class Thread : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(Thread);

			protected:

				class Thread_ *thread;

			public:

				XYO_EXPORT Thread();
				XYO_EXPORT ~Thread();
				XYO_EXPORT bool start(ThreadProcedure procedure, void *this_);
				XYO_EXPORT void join();
				XYO_EXPORT bool isRunning();
				XYO_EXPORT static void sleep(int milliSeconds);

				// ---

				XYO_EXPORT TPointer<Thread> onTimeout(int milliSeconds, ThreadProcedure procedure, void *this_);
				XYO_EXPORT TPointer<Thread> setInterval(TAtomic<bool> &clearInterval, int milliSeconds, ThreadProcedure procedure, void *this_);
				XYO_EXPORT TPointer<Thread> onFinish(Thread &thread, ThreadProcedure procedure, void *this_);
		};

	};
};

#endif

#endif
