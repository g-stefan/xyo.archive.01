//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_SYSTEM_UTIL_HPP
#define XYO_SYSTEM_UTIL_HPP

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TDYNAMICARRAY_HPP
#include "xyo-datastructures-tdynamicarray.hpp"
#endif

namespace XYO {
	namespace System {
		namespace Util {

			XYO_EXPORT bool fileToCpp(
				const char *stringName,
				const char *fileNameIn,
				const char *fileNameOut,
				bool append,
				bool isString);

			XYO_EXPORT bool fileToJs(
				const char *stringName,
				const char *fileNameIn,
				const char *fileNameOut,
				bool append);

			XYO_EXPORT bool fileToRc(
				const char *stringName,
				const char *fileNameIn,
				const char *fileNameOut,
				bool append);

			XYO_EXPORT bool pathToHtmlRc(
				const char *pathOrFileNameIn,
				const char *fileNameOut,
				bool append,
				const char *basePath = nullptr);

			XYO_EXPORT bool fileToCString(
				const char *stringName,
				const char *fileNameIn,
				const char *fileNameOut);

			XYO_EXPORT bool fileToCStringDirect(
				const char *fileNameIn,
				const char *fileNameOut);

			XYO_EXPORT bool fileHashSHA256(
				const char *fileName,
				String &hash);

			XYO_EXPORT bool fileHashSHA512(
				const char *fileName,
				String &hash);
		};
	};
};

#endif

