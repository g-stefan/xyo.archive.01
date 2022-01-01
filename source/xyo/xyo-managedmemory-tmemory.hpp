//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#define XYO_MANAGEDMEMORY_TMEMORY_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#include "xyo-managedmemory-tmemorysystem.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIED_HPP
#include "xyo-managedmemory-tmemorypoolunified.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVE_HPP
#include "xyo-managedmemory-tmemorypoolactive.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYPROCESS_HPP
#include "xyo-managedmemory-tmemoryprocess.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYTHREAD_HPP
#include "xyo-managedmemory-tmemorythread.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOL_HPP
#include "xyo-managedmemory-tmemorypool.hpp"
#endif

#ifdef XYO_TMEMORYPOOL_SYSTEM

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		struct TMemory : TMemorySystem<T> {};

	};
};

#else

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		struct TMemory : TMemoryThread<T> {};

	};
};

#endif

#endif
