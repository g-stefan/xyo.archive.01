//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-algorithm-buffer8core.hpp"

namespace XYO {
	namespace Algorithm {
		namespace Buffer8Core {

			void xorOperation(uint8_t *inOut, size_t inOutLn, const uint8_t *key, size_t keyLn) {
				while ((inOutLn > 0) && (keyLn > 0)) {
					*inOut ^= *key;
					--inOutLn;
					--keyLn;
					++inOut;
					++key;
				};
			};

			void xorAvalancheEncode(uint8_t *data, size_t dataLn) {
				if (dataLn == 0) {
					return;
				};
				while (dataLn > 0) {
					if (dataLn - 1 > 0) {
						*(data + 1) ^= *data;
					};
					--dataLn;
					++data;
				};
			};

			void xorAvalancheDecode(uint8_t *data, size_t dataLn) {
				if (dataLn == 0) {
					return;
				};
				uint8_t last_ = *data;
				uint8_t next_;
				while (dataLn > 0) {
					if (dataLn - 1 > 0) {
						next_ = *(data + 1);
						*(data + 1) ^= last_;
						last_ = next_;
					};
					--dataLn;
					++data;
				};
			};

		};
	};
};
