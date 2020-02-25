//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TPOINTERTYPE_HPP
#define XYO_MANAGEDMEMORY_TPOINTERTYPE_HPP

#ifndef XYO_MANAGEDMEMORY_TPOINTER_HPP
#include "xyo-managedmemory-tpointer.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TPOINTERX_HPP
#include "xyo-managedmemory-tpointerx.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		struct TPointerType {
			typedef T Type;
			typedef TPointer<T> Pointer;
			typedef TPointerX<T> PointerX;
		};

		template<typename T>
		struct TPointerType< TPointer<T> > {
			typedef T Type;
			typedef TPointer<T> Pointer;
			typedef TPointerX<T> PointerX;
		};

		template<typename T>
		struct TPointerType< TPointerX<T> > {
			typedef T Type;
			typedef TPointer<T> Pointer;
			typedef TPointerX<T> PointerX;
		};

	};
};

#endif
