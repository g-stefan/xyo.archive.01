//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TSINGLETON_HPP
#define XYO_MANAGEDMEMORY_TSINGLETON_HPP

#ifndef XYO_MANAGEDMEMORY_TSINGLETONPROCESS_HPP
#	include "xyo-managedmemory-tsingletonprocess.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TSINGLETONTHREAD_HPP
#	include "xyo-managedmemory-tsingletonthread.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template <typename T>
		struct TSingleton : TSingletonThread<T> {};

	};
};

#endif
