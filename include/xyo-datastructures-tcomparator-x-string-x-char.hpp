//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_TCOMPARATOR_X_STRING_X_CHAR_HPP
#define XYO_DATASTRUCTURES_TCOMPARATOR_X_STRING_X_CHAR_HPP

#ifndef XYO_DATASTRUCTURES_TCOMPARATOR_HPP
#include "xyo-datastructures-tcomparator.hpp"
#endif

namespace XYO {
	namespace DataStructures {

		template<>
		struct TComparator<const char *> {

			static inline bool isEqual(const char *x, const char *y) {
				return (strcmp(x, y) == 0);
			};

			static inline bool isNotEqual(const char *x, const char *y) {
				return (strcmp(x, y) != 0);
			};

			static inline bool isLess(const char *x, const char *y) {
				return (strcmp(x, y) < 0);
			};

			static inline bool isGreater(const char *x, const char *y) {
				return (strcmp(x, y) > 0);
			};

			static inline bool isLessOrEqual(const char *x, const char *y) {
				return (strcmp(x, y) <= 0);
			};

			static inline bool isGreaterOrEqual(const char *x, const char *y) {
				return (strcmp(x, y) >= 0);
			};

			static inline int compare(const char *x, const char *y) {
				return strcmp(x, y);
			};

		};

		template<>
		struct TComparator<char *> : TComparator<const char *> {
		};

	};
};

#endif

