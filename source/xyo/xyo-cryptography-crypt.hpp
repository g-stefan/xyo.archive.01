//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_CRYPTOGRAPHY_CRYPT_HPP
#define XYO_CRYPTOGRAPHY_CRYPT_HPP

#ifndef XYO_DATASTRUCTURES_BUFFER_HPP
#	include "xyo-datastructures-buffer.hpp"
#endif

namespace XYO {
	namespace Cryptography {
		namespace Crypt {
			using namespace XYO::DataStructures;

			XYO_EXPORT void passwordEncrypt(const uint8_t *password, size_t passwordSize, const uint8_t *data, size_t dataSize, Buffer &output);
			XYO_EXPORT bool passwordDecrypt(const uint8_t *password, size_t passwordSize, const uint8_t *data, size_t dataSize, Buffer &output);
			XYO_EXPORT bool passwordEncryptFile(const uint8_t *password, size_t passwordSize, const char *fileNameIn, const char *fileNameOut);
			XYO_EXPORT bool passwordDecryptFile(const uint8_t *password, size_t passwordSize, const char *fileNameIn, const char *fileNameOut);
			XYO_EXPORT bool checkIntegrity(const uint8_t *password, size_t passwordSize, const uint8_t *data, size_t dataSize_, const uint8_t *integrity);

		};
	};
};

#endif
