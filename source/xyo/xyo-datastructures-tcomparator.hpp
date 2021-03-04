//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_TCOMPARATOR_HPP
#define XYO_DATASTRUCTURES_TCOMPARATOR_HPP

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

namespace XYO {
	namespace DataStructures {

		template<typename T>
		struct TComparator {

			static inline bool isEqual(const T &x, const T &y) {
				return x == y;
			};

			static inline bool isNotEqual(const T &x, const T &y) {
				return x != y;
			};

			static inline bool isLess(const T &x, const T &y) {
				return x < y;
			};

			static inline bool isGreater(const T &x, const T &y) {
				return x > y;
			};

			static inline bool isLessOrEqual(const T &x, const T &y) {
				return x <= y;
			};

			static inline bool isGreaterOrEqual(const T &x, const T &y) {
				return x >= y;
			};

			static inline int compare(const T &x, const T &y) {
				if(x < y) {
					return -1;
				};
				if(x == y) {
					return 0;
				};
				return 1;
			};

		};

	};
};

#ifndef XYO_DATASTRUCTURES_TCOMPARATOR_X_STRING_X_CHAR_HPP
#include "xyo-datastructures-tcomparator-x-string-x-char.hpp"
#endif

#endif
