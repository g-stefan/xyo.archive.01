//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_ENCODING_BASE64_HPP
#define XYO_ENCODING_BASE64_HPP

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace Encoding {
		namespace Base64 {
			using namespace XYO::DataStructures;
			using namespace XYO::Encoding;

			XYO_EXPORT String encode(const String &toEncode);
			XYO_EXPORT bool decode(const String &toDecode, String &out);

		};
	};
};

#endif
