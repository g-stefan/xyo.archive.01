//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_CRYPTOGRAPHY_SHA256_HPP
#define XYO_CRYPTOGRAPHY_SHA256_HPP

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace Cryptography {
		using namespace XYO::Encoding;

		class SHA256 : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(SHA256);
			protected:

				XYO_EXPORT static const uint32_t k_[];

				uint32_t h0, h1, h2, h3, h4, h5, h6, h7;

				uint32_t process[16];
				uint8_t lastData[4];
				uint64_t length;
				size_t stateM;
			public:
				XYO_EXPORT SHA256();
				XYO_EXPORT void processInit();
				XYO_EXPORT void hashBlock(uint32_t *w_);
				XYO_EXPORT void processU8(const uint8_t *toHash, size_t length);
				XYO_EXPORT void processDone();
				XYO_EXPORT String getHashHex();
				XYO_EXPORT static String getHashString(const String &toHash);
				XYO_EXPORT void toU8(uint8_t *buffer);
				XYO_EXPORT static void hashStringToU8(const String &toHash, uint8_t *buffer);
				XYO_EXPORT void copy(const SHA256 &in);
		};

	};
};

#endif
