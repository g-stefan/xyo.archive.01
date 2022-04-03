//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVE_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVE_HPP

#ifdef XYO_TMEMORYPOOL_SYSTEM

#	ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#		include "xyo-managedmemory-tmemorysystem.hpp"
#	endif

namespace XYO {
	namespace ManagedMemory {

		template <typename T>
		struct TMemoryPoolActive : TMemorySystem<T> {};

	};
};

#elif defined(XYO_TMEMORYPOOL_ACTIVE_AS_UNIFIED)

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIED_HPP
#		include "xyo-managedmemory-tmemorypoolunified.hpp"
#	endif

namespace XYO {
	namespace ManagedMemory {

		template <typename T>
		struct TMemoryPoolActive : TMemoryPoolUnified<T> {};

	};
};

#else

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVEPROCESS_HPP
#		include "xyo-managedmemory-tmemorypoolactiveprocess.hpp"
#	endif

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVETHREAD_HPP
#		include "xyo-managedmemory-tmemorypoolactivethread.hpp"
#	endif

namespace XYO {
	namespace ManagedMemory {

		template <typename T>
		struct TMemoryPoolActive : TMemoryPoolActiveThread<T> {};

	};
};

#endif

#endif
