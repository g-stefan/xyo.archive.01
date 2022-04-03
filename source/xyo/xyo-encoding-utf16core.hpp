//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_ENCODING_UTF15CORE_HPP
#define XYO_ENCODING_UTF15CORE_HPP

#ifndef XYO__DEPENDENCY_HPP
#	include "xyo--dependency.hpp"
#endif

namespace XYO {
	namespace Encoding {

		typedef uint16_t utf16;

		namespace Utf16Core {

			inline size_t elementSize(const utf16 x) {
				if ((x & 0xFC00) == 0xD800) {
					return 2;
				};
				if ((x & 0xFC00) == 0xDC00) {
					return 0;
				};
				if (x == 0xFFFF) {
					return 0;
				};
				return 1;
			};

			inline bool elementIsValid(const utf16 *x) {
				size_t sz;
				sz = elementSize(*x);
				if (sz == 0) {
					return false;
				}
				if (sz == 1) {
					return true;
				}
				++x;
				if ((*x & 0xFC00) == 0xDC00) {
					return true;
				}
				return false;
			};

		};

	};
};

#endif
