//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_ALGORITHM_CHECKSUM_HPP
#define XYO_ALGORITHM_CHECKSUM_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

namespace XYO {
	namespace Algorithm {
		namespace Checksum {

			XYO_EXPORT uint16_t add(uint16_t x, uint16_t y);
			XYO_EXPORT uint16_t addX2(uint16_t x, uint8_t byteHigh, uint8_t byteLow);
			XYO_EXPORT uint16_t complement(uint16_t x);
			XYO_EXPORT uint16_t unAdd(uint16_t x, uint16_t y);
			XYO_EXPORT uint16_t unAddX2(uint16_t x, uint8_t byteHigh, uint8_t byteLow);
			XYO_EXPORT uint16_t unComplement(uint16_t x);
			XYO_EXPORT uint16_t reAddX2(uint16_t x, uint8_t byteHigh, uint8_t byteLow);
			XYO_EXPORT uint16_t unReAddX2(uint16_t x, uint8_t byteHigh, uint8_t byteLow);

		};
	};
};

#endif
