//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_CRYPTOGRAPHY_SHA512_HPP
#define XYO_CRYPTOGRAPHY_SHA512_HPP

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace Cryptography {
		using namespace XYO::Encoding;

		class SHA512 : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(SHA512);
			protected:
				XYO_EXPORT static const uint64_t k_[];

				uint64_t h0, h1, h2, h3, h4, h5, h6, h7;

				uint64_t process[16];
				uint8_t lastData[8];
				uint64_t length0;
				uint64_t length1;
				size_t stateM;
			public:
				XYO_EXPORT SHA512();
				XYO_EXPORT void processInit();
				XYO_EXPORT void hashBlock(uint64_t *w_);
				XYO_EXPORT void processU8(const uint8_t *toHash, size_t length);
				XYO_EXPORT void processDone();
				XYO_EXPORT String getHashHex();
				XYO_EXPORT static String getHashString(const String &toHash);
				XYO_EXPORT void toU8(uint8_t *buffer);
				XYO_EXPORT static void hashStringToU8(const String &toHash, uint8_t *buffer);
				XYO_EXPORT void copy(const SHA512 &in);
		};

	};
};

#endif
