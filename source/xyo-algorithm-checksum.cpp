//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-algorithm-checksum.hpp"

namespace XYO {
	namespace Algorithm {
		namespace Buffer8Core {

			uint16_t add(uint16_t x, uint16_t y) {
				uint32_t sum;
				sum=x;
				sum+=y;
				if(sum&0xFFFF0000) {
					++sum;
				};
				return ((uint16_t)(sum&0x0000FFFF));
			};

			uint16_t addX2(uint16_t x, uint8_t byteHigh, uint8_t byteLow) {
				uint16_t word;
				word=byteHigh;
				word<<=8;
				word|=byteLow;
				return add(x, word);
			};

			uint16_t complement(uint16_t x) {
				return (x^0xFFFF);
			};

			uint16_t unAdd(uint16_t x, uint16_t y) {
				uint16_t sum;
				sum=x;
				sum|=0x00010000;
				--sum;
				sum-=y;
				if(sum&0xFFFF0000) {
					++sum;
				};
				return ((uint16_t)(sum&0x0000FFFF));

			};
			uint16_t unAddX2(uint16_t x, uint8_t byteHigh, uint8_t byteLow) {
				uint16_t word;
				word=byteHigh;
				word<<=8;
				word|=byteLow;
				return unAdd(x, word);

			};

			uint16_t unComplement(uint16_t x) {
				return (x^0xFFFF);
			};

			uint16_t reAddX2(uint16_t x, uint8_t byteHigh, uint8_t byteLow) {
				uint16_t sum;
				sum=unComplement(x);
				sum=addX2(sum, byteHigh, byteLow);
				return complement(sum);
			};

			uint16_t unReAddX2(uint16_t x, uint8_t byteHigh, uint8_t byteLow) {
				uint16_t sum;
				sum=unComplement(x);
				sum=unAddX2(sum, byteHigh, byteLow);
				return complement(sum);
			};

		};
	};
};

