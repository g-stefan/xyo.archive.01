//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_ENCODING_THEX_HPP
#define XYO_ENCODING_THEX_HPP

#ifndef XYO__DEPENDENCY_HPP
#	include "xyo--dependency.hpp"
#endif

namespace XYO {
	namespace Encoding {

		template <typename T>
		struct THex {
				static inline T encodeUppercase(const typename std::make_unsigned<T>::type x) {
					if (x < 10) {
						return ('0' | x);
					};
					return 'A' + (x - 10);
				};

				static inline T encodeLowercase(const typename std::make_unsigned<T>::type x) {
					if (x < 10) {
						return ('0' | x);
					};
					return 'a' + (x - 10);
				};

				static inline typename std::make_unsigned<T>::type decode(const T x) {
					if (x >= '0' && x <= '9') {
						return (x & 0x0F);
					};
					if (x >= 'A' && x <= 'F') {
						return x - 'A' + 10;
					};
					if (x >= 'a' && x <= 'f') {
						return x - 'a' + 10;
					};
					return 0;
				};
		};

	};
};

#endif
