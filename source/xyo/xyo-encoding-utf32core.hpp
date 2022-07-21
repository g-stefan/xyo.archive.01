//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_ENCODING_UTF32CORE_HPP
#define XYO_ENCODING_UTF32CORE_HPP

#ifndef XYO__DEPENDENCY_HPP
#	include "xyo--dependency.hpp"
#endif

namespace XYO {
	namespace Encoding {

		typedef uint32_t utf32;

		namespace UTF32Core {

			inline bool elementIsValid(const utf32 x) {
				if (x <= 0x0000D7FFUL) {
					return true;
				};
				if ((x >= 0x0000D800UL) && (x < 0x0000E000UL)) {
					return false;
				};
				if (x == 0x0000FFFFUL) {
					return false;
				};
				if (x >= 0x00110000UL) {
					return false;
				};
				return true;
			};

			inline size_t elementSize(const utf32 x) {
				return static_cast<size_t>(elementIsValid(x));
			};

		};

	};
};

#endif
