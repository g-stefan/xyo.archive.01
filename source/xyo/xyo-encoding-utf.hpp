//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_ENCODING_UTF_HPP
#define XYO_ENCODING_UTF_HPP

#ifndef XYO_ENCODING_STRING_HPP
#	include "xyo-encoding-string.hpp"
#endif

#ifndef XYO_ENCODING_UTF8CORE_HPP
#	include "xyo-encoding-utf8core.hpp"
#endif

#ifndef XYO_ENCODING_UTF16CORE_HPP
#	include "xyo-encoding-utf16core.hpp"
#endif

#ifndef XYO_ENCODING_UTF32CORE_HPP
#	include "xyo-encoding-utf32core.hpp"
#endif

namespace XYO {
	namespace Encoding {

		typedef TStringCore<utf8> StringUtf8Core;
		typedef TStringReference<utf8> StringUtf8Reference;
		typedef TString<utf8> StringUtf8;

		typedef TStringCore<utf16> StringUtf16Core;
		typedef TStringReference<utf16> StringUtf16Reference;
		typedef TString<utf16> StringUtf16;

		typedef TStringCore<utf32> StringUtf32Core;
		typedef TStringReference<utf32> StringUtf32Reference;
		typedef TString<utf32> StringUtf32;

		namespace Utf {
			using namespace XYO::DataStructures;

			XYO_EXPORT extern const utf8 utf8StringQuestionMark[];
			XYO_EXPORT extern const utf16 utf16StringQuestionMark[];
			XYO_EXPORT extern const utf32 utf32StringQuestionMark[];

			XYO_EXPORT size_t elementUtf8FromUtf32Size(utf32 in);
			XYO_EXPORT size_t elementUtf8FromUtf32(utf8 *out, utf32 in);
			XYO_EXPORT size_t elementUtf8FromUtf16Size(const utf16 *in);
			XYO_EXPORT size_t elementUtf16FromUtf32Size(utf32 in);
			XYO_EXPORT size_t elementUtf16FromUtf32(utf16 *out, utf32 in);
			XYO_EXPORT size_t elementUtf32FromUtf8(utf32 *out, const utf8 *in);
			XYO_EXPORT size_t elementUtf32FromUtf16(utf32 *out, const utf16 *in);

			XYO_EXPORT String utf8FromUtf16(const utf16 *in, const utf8 *err = utf8StringQuestionMark);
			XYO_EXPORT String utf8FromUtf32(const utf32 *in, const utf8 *err = utf8StringQuestionMark);

			XYO_EXPORT StringUtf16 utf16FromUtf8(const utf8 *in, const utf16 *err = utf16StringQuestionMark);
			XYO_EXPORT StringUtf16 utf16FromUtf32(const utf32 *in, const utf16 *err = utf16StringQuestionMark);

			XYO_EXPORT StringUtf32 utf32FromUtf8(const utf8 *in, const utf32 *err = utf32StringQuestionMark);
			XYO_EXPORT StringUtf32 utf32FromUtf16(const utf16 *in, const utf32 *err = utf32StringQuestionMark);

			XYO_EXPORT size_t utf16FromUtf8Length(const utf8 *in, const utf16 *err = utf16StringQuestionMark);
			XYO_EXPORT size_t utf16FromUtf32Length(const utf32 *in, const utf16 *err = utf16StringQuestionMark);
			XYO_EXPORT size_t utf32FromUtf8Length(const utf8 *in, const utf32 *err = utf32StringQuestionMark);
			XYO_EXPORT size_t utf32FromUtf16Length(const utf16 *in, const utf32 *err = utf32StringQuestionMark);

			XYO_EXPORT bool fileGetContentsUtf8(const char *fileName, String &output, int mode);
			XYO_EXPORT bool filePutContentsUtf8(const char *fileName, const String &value, int mode);
		};

	};
};

#endif
