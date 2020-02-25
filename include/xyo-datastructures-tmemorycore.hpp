//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_TMEMORYCORE_HPP
#define XYO_DATASTRUCTURES_TMEMORYCORE_HPP

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

namespace XYO {
	namespace DataStructures {

		template<typename T>
		struct TMemoryCore {

			static inline void copyN(T *x, const T *y, size_t ln) {

				while(ln != 0) {

					*x = *y;

					++x;
					++y;
					--ln;

				};

			};

			static inline int compareN(T *x, const T *y, size_t ln) {

				while((ln != 0) && (*x == *y)) {
					++x;
					++y;
					--ln;
				};

				if(ln == 0) {
					return 0;
				};

				if( (*x - *y) < 0 ) {
					return -1;
				};

				return 1;
			};

			static inline void setN(T *x, const T y, size_t ln) {

				while(ln != 0) {

					*x=y;

					++x;
					--ln;
				};

			};

		};

	};
};

#ifndef XYO_DATASTRUCTURES_TMEMORYCORE_X_CHAR_HPP
#include "xyo-datastructures-tmemorycore-x-char.hpp"
#endif

#endif
