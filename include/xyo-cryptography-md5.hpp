//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_CRYPTOGRAPHY_MD5_HPP
#define XYO_CRYPTOGRAPHY_MD5_HPP

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace Cryptography {
		using namespace XYO::Encoding;

		class MD5 : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(MD5);
			protected:

				XYO_EXPORT static const uint16_t r[];
				XYO_EXPORT static const uint32_t k[];

				uint32_t h0;
				uint32_t h1;
				uint32_t h2;
				uint32_t h3;

				uint32_t process[16];
				uint8_t lastData[4];
				uint64_t length;
				size_t stateM;
			public:
				XYO_EXPORT MD5();
				XYO_EXPORT void processInit();
				XYO_EXPORT void hashBlock(uint32_t *w);
				XYO_EXPORT void processU8(const uint8_t *toHash, size_t length);
				XYO_EXPORT void processDone();
				XYO_EXPORT String getHashHex();
				XYO_EXPORT static String getHashString(const String &toHash);
				XYO_EXPORT void toU8(uint8_t *buffer);
				XYO_EXPORT static void hashStringToU8(const String &toHash, uint8_t *buffer);
				XYO_EXPORT void copy(const MD5 &in);
		};

	};
};

#endif
