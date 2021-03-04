//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_TSTRINGCORE_X_STRING_X_CHAR_HPP
#define XYO_DATASTRUCTURES_TSTRINGCORE_X_STRING_X_CHAR_HPP

#ifndef XYO_DATASTRUCTURES_TSTRINGCORE_HPP
#include "xyo-datastructures-tstringcore.hpp"
#endif

namespace XYO {
	namespace DataStructures {

		template<>
		inline size_t TStringCore<char>::length(const char *x) {
			return strlen(x);
		};

		template<>
		inline void TStringCore<char>::copy(char *x, const char *y) {
			strcpy(x, y);
		};

		template<>
		inline void TStringCore<char>::copyN(char *x, const char *y, size_t yLn) {
			strncpy(x, y, yLn);
		};

		template<>
		inline int TStringCore<char>::compare(const char *x, const char *y) {
			return strcmp(x, y);
		};

		template<>
		inline int TStringCore<char>::compareN(const char *x, const char *y, size_t ln) {
			return strncmp(x, y, ln);
		};

		template<>
		inline void TStringCore<char>::concatenate(char *x, const char *y) {
			strcat(x, y);
		};

		template<>
		inline void TStringCore<char>::concatenateN(char *x, const char *y, size_t yLn) {
			strncat(x, y, yLn);
		};

	};
};

#endif


