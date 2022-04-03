//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_ENCODING_UTF8CORE_HPP
#define XYO_ENCODING_UTF8CORE_HPP

#ifndef XYO__DEPENDENCY_HPP
#	include "xyo--dependency.hpp"
#endif

namespace XYO {
	namespace Encoding {

		typedef char utf8;

		namespace Utf8Core {

			inline size_t elementSize(const utf8 x) {
				if ((x & 0x80) == 0x00) {
					return 1;
				};
				if ((x & 0xE0) == 0xC0) {
					return 2;
				};
				if ((x & 0xF0) == 0xE0) {
					return 3;
				};
				if ((x & 0xF8) == 0xF0) {
					return 4;
				};
				if ((x & 0xFC) == 0xF8) {
					return 5;
				};
				if ((x & 0xFE) == 0xFC) {
					return 6;
				};
				return 0;
			};

			inline bool elementIsValid(const utf8 *x) {
				size_t sz;
				sz = elementSize(*x);
				if (sz == 0) {
					return false;
				};
				++x;
				--sz;
				while (sz) {
					if ((*x & 0xC0) != 0x80) {
						return false;
					};
					++x;
					--sz;
				};
				return true;
			};

			inline bool check(const utf8 x) {
				return ((x & 0xC0) == 0x80);
			};

			inline bool elementIsEqual(const utf8 *x, const utf8 *y) {
				size_t sz;
				sz = elementSize(*x);
				if (sz != elementSize(*y)) {
					return false;
				};
				return (memcmp(x, y, sz) == 0);
			};

		};

	};
};

#endif
