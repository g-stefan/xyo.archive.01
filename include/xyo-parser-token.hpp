//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_PARSER_TOKEN_HPP
#define XYO_PARSER_TOKEN_HPP

#ifndef XYO_PARSER_INPUT_HPP
#include "xyo-parser-input.hpp"
#endif

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace Parser {
		using namespace XYO::DataStructures;
		using namespace XYO::Stream;
		using namespace XYO::Encoding;

		class Token : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(Token);

			public:

				TPointerX<Input> input;

				XYO_EXPORT Token();
				XYO_EXPORT ~Token();
				XYO_EXPORT void activeDestructor();
				XYO_EXPORT bool open(Input *input_);
				XYO_EXPORT void close();

				XYO_EXPORT bool isBOM();
				XYO_EXPORT bool isSpace();
				XYO_EXPORT bool isComment();
				XYO_EXPORT void ignoreSpaceOrComment();
				XYO_EXPORT bool isSymbol(String &token);
				XYO_EXPORT bool isString(String &token);
				XYO_EXPORT bool isNumber(String &token);

				inline bool is(const char inputChar) {
					return input->is(inputChar);
				};

				inline bool is1(const char inputChar) {
					return input->is1(inputChar);
				};

				inline bool isN(const char *token) {
					return input->isN(token);
				};

				inline bool read() {
					return input->read();
				};

				inline bool isEof() {
					return input->isEof();
				};
		};

	};
};

#endif
