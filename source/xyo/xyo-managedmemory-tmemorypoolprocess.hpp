//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLPROCESS_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPOOLPROCESS_HPP

#ifdef XYO_TMEMORYPOOL_SYSTEM

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#include "xyo-managedmemory-tmemorysystem.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		struct TMemoryPoolProcess : TMemorySystem<T> {};

	};
};

#else

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDPROCESS_HPP
#include "xyo-managedmemory-tmemorypoolunifiedprocess.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		struct TMemoryPoolProcess : TMemoryPoolUnifiedProcess<T> {};

	};
};

#endif

#endif
