//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_NETWORKING_URL_HPP
#define XYO_NETWORKING_URL_HPP

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace Networking {
		namespace URL {
			using namespace XYO::Encoding;

			XYO_EXPORT String decodeComponent(const String &value);
			XYO_EXPORT String encodeComponent(const String &value);
			XYO_EXPORT bool getSchemeName(const String &url, String &out);
			XYO_EXPORT bool getHostNameAndPort(const String &url, String &out);
			XYO_EXPORT bool getUsernameAndPassword(const String &url, String &out);
			XYO_EXPORT bool getPathAndFileName(const String &url, String &out);
			XYO_EXPORT bool getQuery(const String &url, String &out);

		};
	};
};

#endif

