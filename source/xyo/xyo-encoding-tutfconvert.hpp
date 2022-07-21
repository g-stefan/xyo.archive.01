//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_ENCODING_TUTFCONVERT_HPP
#define XYO_ENCODING_TUTFCONVERT_HPP

#ifndef XYO_ENCODING_UTF_HPP
#	include "xyo-encoding-utf.hpp"
#endif

namespace XYO {
	namespace Encoding {

		template <typename TTo, typename TFrom>
		struct TUTFConvertNotImplemented : std::false_type {};

		template <typename TTo, typename TFrom>
		class TUTFConvert {
			public:
				inline static TString<TTo> from(const TString<TFrom> &) {
					static_assert(TUTFConvertNotImplemented<TTo, TFrom>::value, "UTFConvert not implemented for selected type");
				};
		};

		// utf8

		template <>
		class TUTFConvert<utf8, utf8> {
			public:
				inline static TString<utf8> from(const TString<utf8> &input) {
					return input;
				};
		};

		template <>
		class TUTFConvert<utf8, utf16> {
			public:
				inline static TString<utf8> from(const TString<utf16> &input) {
					return UTF::utf8FromUTF16(input);
				};
		};

		template <>
		class TUTFConvert<utf8, utf32> {
			public:
				inline static TString<utf8> from(const TString<utf32> &input) {
					return UTF::utf8FromUTF32(input);
				};
		};

		// utf16

		template <>
		class TUTFConvert<utf16, utf8> {
			public:
				inline static TString<utf16> from(const TString<utf8> &input) {
					return UTF::utf16FromUTF8(input);
				};
		};

		template <>
		class TUTFConvert<utf16, utf16> {
			public:
				inline static TString<utf16> from(const TString<utf16> &input) {
					return input;
				};
		};

		template <>
		class TUTFConvert<utf16, utf32> {
			public:
				inline static TString<utf16> from(const TString<utf32> &input) {
					return UTF::utf16FromUTF32(input);
				};
		};

		// utf32

		template <>
		class TUTFConvert<utf32, utf8> {
			public:
				inline static TString<utf32> from(const TString<utf8> &input) {
					return UTF::utf32FromUTF8(input);
				};
		};

		template <>
		class TUTFConvert<utf32, utf16> {
			public:
				inline static TString<utf32> from(const TString<utf16> &input) {
					return UTF::utf32FromUTF16(input);
				};
		};

		template <>
		class TUTFConvert<utf32, utf32> {
			public:
				inline static TString<utf32> from(const TString<utf32> &input) {
					return input;
				};
		};

	};
};

#endif
