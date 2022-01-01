//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-multithreading-thread.hpp"
#include "xyo-multithreading-semaphore.hpp"

#ifdef XYO_MULTI_THREAD

namespace XYO {
	namespace Multithreading {

		//
		// Simple Semaphore
		// Master/Slave mode
		// No Condition variable
		//

		Semaphore::Semaphore() {
			state.set(false);
		};

		void Semaphore::wait() {
			while(!state.get()) {
				Thread::sleep(1);
			};
			state.set(false);
		};

		void Semaphore::notify() {
			state.set(true);
		};

		bool Semaphore::peek() const {
			return state.get();
		};

		void Semaphore::reset() {
			state.set(false);
		};

	};
};

#endif

