//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-encoding-hex.hpp"
#include "xyo-encoding-string.hpp"
#include "xyo-encoding-base16.hpp"

//
// https://en.wikipedia.org/wiki/Hexadecimal
//

namespace XYO {
	namespace Encoding {
		namespace Base16 {
			using namespace XYO::DataStructures;
			using namespace XYO::Encoding;

			String encode(const String &toEncode) {
				TPointer<StringReference> retV(TMemory<StringReference>::newMemory());
				retV->init(toEncode.length() * 2);
				size_t k;
				const char *scan;
				scan = toEncode.value();
				for(k = 0; k < toEncode.length(); ++k, ++scan) {
					retV->concatenateX(Hex::encodeUppercase(((*scan) >> 4) & 0x0F));
					retV->concatenateX(Hex::encodeUppercase((*scan) & 0x0F));
				};
				return retV;
			};

			bool decode(const String &toDecode, String &out) {
				TPointer<StringReference > retV(TMemory<StringReference>::newMemory());
				retV->init((toDecode.length() / 2));
				size_t k;
				const char *scan;
				scan = toDecode.value();
				for(k = 0; k < toDecode.length() / 2; ++k, scan+=2) {
					retV->concatenateX(Hex::decode(*scan) << 4 | Hex::decode(*(scan+1)));
				};
				out = retV;
				return true;
			};

		};
	};
};

