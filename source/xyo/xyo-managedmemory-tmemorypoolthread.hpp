//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLTHREAD_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPOOLTHREAD_HPP

#ifdef XYO_TMEMORYPOOL_SYSTEM

#	ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#		include "xyo-managedmemory-tmemorysystem.hpp"
#	endif

namespace XYO {
	namespace ManagedMemory {

		template <typename T>
		struct TMemoryPoolThread : TMemorySystem<T> {};

	};
};

#else

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDTHREAD_HPP
#		include "xyo-managedmemory-tmemorypoolunifiedthread.hpp"
#	endif

namespace XYO {
	namespace ManagedMemory {

		template <typename T>
		struct TMemoryPoolThread : TMemoryPoolUnifiedThread<T> {};

	};
};

#endif

#endif
