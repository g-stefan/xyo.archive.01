//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_ALGORITHM_BUFFER8CORE_HPP
#define XYO_ALGORITHM_BUFFER8CORE_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

namespace XYO {
	namespace Algorithm {
		namespace Buffer8Core {

			XYO_EXPORT void xorOperation(uint8_t *inOut, size_t inOutLn, const uint8_t *key, size_t keyLn);
			XYO_EXPORT void xorAvalancheEncode(uint8_t *data, size_t dataLn);
			XYO_EXPORT void xorAvalancheDecode(uint8_t *data, size_t dataLn);

		};
	};
};

#endif
