//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TPOINTERX_X_TCOMPARATOR_HPP
#define XYO_MANAGEDMEMORY_TPOINTERX_X_TCOMPARATOR_HPP

#ifndef XYO_MANAGEDMEMORY_TPOINTERX_HPP
#include "xyo-managedmemory-tpointerx.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TCOMPARATOR_HPP
#include "xyo-datastructures-tcomparator.hpp"
#endif

namespace XYO {
	namespace DataStructures {

		template<typename T_>
		struct TComparator<ManagedMemory::TPointerX<T_> > {
			typedef ManagedMemory::TPointerX<T_> T;

			static inline bool isEqual(const T &x, const T &y) {
				return TComparator<T_>::isEqual(*x, *y);
			};

			static inline bool isNotEqual(const T &x, const T &y) {
				return TComparator<T_>::isNotEqual(*x, *y);
			};

			static inline bool isLess(const T &x, const T &y) {
				return TComparator<T_>::isLess(*x, *y);
			};

			static inline bool isGreater(const T &x, const T &y) {
				return TComparator<T_>::isGreater(*x, *y);
			};

			static inline bool isLessOrEqual(const T &x, const T &y) {
				return TComparator<T_>::isLessOrEqual(*x, *y);
			};

			static inline bool isGreaterOrEqual(const T &x, const T &y) {
				return TComparator<T_>::isGreaterOrEqual(*x, *y);
			};

			static inline int compare(const T &x, const T &y) {
				return TComparator<T_>::compare(*x, *y);
			};
		};


	};
};

#endif

