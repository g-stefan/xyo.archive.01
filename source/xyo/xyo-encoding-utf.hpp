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

		typedef TStringCore<utf8> StringUTF8Core;
		typedef TStringReference<utf8> StringUTF8Reference;
		typedef TString<utf8> StringUTF8;

		typedef TStringCore<utf16> StringUTF16Core;
		typedef TStringReference<utf16> StringUTF16Reference;
		typedef TString<utf16> StringUTF16;

		typedef TStringCore<utf32> StringUTF32Core;
		typedef TStringReference<utf32> StringUTF32Reference;
		typedef TString<utf32> StringUTF32;

		namespace UTF {
			using namespace XYO::DataStructures;

			XYO_EXPORT extern const utf8 utf8StringQuestionMark[];
			XYO_EXPORT extern const utf16 utf16StringQuestionMark[];
			XYO_EXPORT extern const utf32 utf32StringQuestionMark[];

			XYO_EXPORT size_t elementUTF8FromUTF32Size(utf32 in);
			XYO_EXPORT size_t elementUTF8FromUTF32(utf8 *out, utf32 in);
			XYO_EXPORT size_t elementUTF8FromUTF16Size(const utf16 *in);
			XYO_EXPORT size_t elementUTF16FromUTF32Size(utf32 in);
			XYO_EXPORT size_t elementUTF16FromUTF32(utf16 *out, utf32 in);
			XYO_EXPORT size_t elementUTF32FromUTF8(utf32 *out, const utf8 *in);
			XYO_EXPORT size_t elementUTF32FromUTF16(utf32 *out, const utf16 *in);

			XYO_EXPORT String utf8FromUTF16(const utf16 *in, const utf8 *err = utf8StringQuestionMark);
			XYO_EXPORT String utf8FromUTF32(const utf32 *in, const utf8 *err = utf8StringQuestionMark);

			XYO_EXPORT StringUTF16 utf16FromUTF8(const utf8 *in, const utf16 *err = utf16StringQuestionMark);
			XYO_EXPORT StringUTF16 utf16FromUTF32(const utf32 *in, const utf16 *err = utf16StringQuestionMark);

			XYO_EXPORT StringUTF32 utf32FromUTF8(const utf8 *in, const utf32 *err = utf32StringQuestionMark);
			XYO_EXPORT StringUTF32 utf32FromUTF16(const utf16 *in, const utf32 *err = utf32StringQuestionMark);

			XYO_EXPORT size_t utf16FromUTF8Length(const utf8 *in, const utf16 *err = utf16StringQuestionMark);
			XYO_EXPORT size_t utf16FromUTF32Length(const utf32 *in, const utf16 *err = utf16StringQuestionMark);
			XYO_EXPORT size_t utf32FromUTF8Length(const utf8 *in, const utf32 *err = utf32StringQuestionMark);
			XYO_EXPORT size_t utf32FromUTF16Length(const utf16 *in, const utf32 *err = utf32StringQuestionMark);

			XYO_EXPORT bool fileGetContentsUTF8(const char *fileName, String &output, int mode);
			XYO_EXPORT bool filePutContentsUTF8(const char *fileName, const String &value, int mode);
		};

	};
};

#endif
