//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_POINTERX_HPP
#define XYO_MANAGEDMEMORY_POINTERX_HPP

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		struct PointerX {
			PointerX *back;
			PointerX *next;
			class Object *link;
			void *object;
		};

	};
};

#endif
