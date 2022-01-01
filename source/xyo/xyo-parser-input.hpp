//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_PARSER_INPUT_HPP
#define XYO_PARSER_INPUT_HPP

#ifndef XYO_STREAM_IREAD_HPP
#include "xyo-stream-iread.hpp"
#endif

namespace XYO {
	namespace Parser {
		using namespace XYO::Stream;

		class Input : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(Input);

			public:

				TPointerX<IRead> iRead;

				char *iStack;
				size_t iStackSize;
				size_t iStackIndex;
				char inputChar;
				bool isEof_;

				XYO_EXPORT Input();
				XYO_EXPORT ~Input();
				XYO_EXPORT void activeDestructor();
				XYO_EXPORT bool open(IRead *iRead_, size_t iStackSize_);
				XYO_EXPORT void close();

				inline bool push() {
					if(iStackIndex == iStackSize) {
						return false;
					};
					iStack[iStackIndex] = inputChar;
					++iStackIndex;
					return true;
				};

				inline bool pop() {
					if(iStackIndex == 0) {
						return false;
					};
					--iStackIndex;
					inputChar = iStack[iStackIndex];
					return true;
				};

				inline bool read() {
					if (iStackIndex) {
						return pop();
					};
					if (isEof_) {
						inputChar = 0;
						return false;
					};
					if (iRead->read(&inputChar, sizeof(char))) {
						return true;
					};
					inputChar = 0;
					isEof_ = true;
					return false;
				};

				inline bool isEof() {
					if (iStackIndex) {
						return false;
					};
					return isEof_;
				};

				inline bool is(const char inputChar_) {
					return (inputChar == inputChar_);
				};

				inline bool between(const char inputChar_A, const char inputChar_B) {
					return ((inputChar >= inputChar_A) && (inputChar <= inputChar_B));
				};

				inline void set(const char inputChar_) {
					inputChar = inputChar_;
				};

				inline bool is1(const char inputChar_) {
					if (inputChar == inputChar_) {
						read();
						return true;
					};
					return false;
				};

				XYO_EXPORT bool isN(const char *name);
		};

	};
};

#endif
