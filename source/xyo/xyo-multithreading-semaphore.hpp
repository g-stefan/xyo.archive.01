//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MULTITHREADING_SEMAPHORE_HPP
#define XYO_MULTITHREADING_SEMAPHORE_HPP

#ifndef XYO_MULTITHREADING_TATOMIC_HPP
#include "xyo-multithreading-tatomic.hpp"
#endif

#ifdef XYO_MULTI_THREAD

namespace XYO {
	namespace Multithreading {

		class Semaphore {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(Semaphore);

			protected:

				TAtomic<bool> state;

			public:

				XYO_EXPORT Semaphore();

				XYO_EXPORT void wait();
				XYO_EXPORT void notify();
				XYO_EXPORT bool peek() const;
				XYO_EXPORT void reset();
		};

	};
};

#endif

#endif

