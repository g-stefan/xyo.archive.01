//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_TMEMORYCORE_X_CHAR_HPP
#define XYO_DATASTRUCTURES_TMEMORYCORE_X_CHAR_HPP

#ifndef XYO_DATASTRUCTURES_TMEMORYCORE_HPP
#include "xyo-datastructures-tmemorycore.hpp"
#endif

namespace XYO {
	namespace DataStructures {

		template<>
		struct TMemoryCore<char> {

			static inline void copyN(char *x, const char *y, size_t ln) {
				memcpy(x, y, ln);
			};

			static inline int compareN(char *x, const char *y, size_t ln) {
				return memcmp(x, y, ln);
			};

			static inline void setN(char *x, const char y, size_t ln) {
				memset(x, y, ln);
			};

		};

	};
};

#endif
