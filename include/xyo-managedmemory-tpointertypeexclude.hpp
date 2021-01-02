//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TPOINTERTYPEEXCLUDE_HPP
#define XYO_MANAGEDMEMORY_TPOINTERTYPEEXCLUDE_HPP

#ifndef XYO_MANAGEDMEMORY_TPOINTER_HPP
#include "xyo-managedmemory-tpointer.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TPOINTERX_HPP
#include "xyo-managedmemory-tpointerx.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		struct TPointerTypeExclude {

			template<typename U> struct TUnknownType;
			template<typename U> struct TUnknownPointer;
			template<typename U> struct TUnknownPointerX;

			typedef TUnknownType<T> Type;
			typedef TUnknownPointer<T> Pointer;
			typedef TUnknownPointerX<T> PointerX;

		};

		template<typename T>
		struct TPointerTypeExclude< TPointer<T> > {

			template<typename U> struct TUnknownPointer;

			typedef T Type;
			typedef TUnknownPointer<T> Pointer;
			typedef TPointerX<T> PointerX;
		};

		template<typename T>
		struct TPointerTypeExclude< TPointerX<T> > {

			template<typename U> struct TUnknownPointerX;

			typedef T Type;
			typedef TPointer<T> Pointer;
			typedef TUnknownPointerX<T> PointerX;
		};

	};
};

#endif
