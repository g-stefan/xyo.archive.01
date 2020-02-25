//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-parser-token.hpp"

namespace XYO {
	namespace Parser {
		using namespace XYO::Stream;

		Token::Token() {
			input.pointerLink(this);
		};

		Token::~Token() {
		};

		void Token::activeDestructor() {
			input.deleteMemory();
		};

		bool Token::open(Input *input_) {
			input = input_;
			return true;
		};

		void Token::close() {
			activeDestructor();
		};

		bool Token::isBOM() {
			if(input->isN("\xEF\xBB\xBF")) {
				return true;
			};
			return false;
		};

		bool Token::isSpace() {
			bool isOk = false;
			while(!input->isEof()) {

				if(input->is1('\x20')) {
					isOk = true;
					continue;
				};

				if(input->is1('\x09')) {
					isOk = true;
					continue;
				};

				if(input->is1('\x0D')) {
					isOk = true;
					continue;
				};

				if(input->is1('\x0A')) {
					isOk = true;
					continue;
				};

				return isOk;
			};
			return false;
		};

		bool Token::isComment() {
			if (input->is('/')) {
				if (input->read()) {
					if (input->is('/')) {
						if (input->read()) {
							if (
								input->is('\x0D')
								|| input->is('\x0A')

							) {
								return isSpace();
							};
							while (input->read()) {
								if (
									input->is('\x0D')
									|| input->is('\x0A')

								) {
									return isSpace();
								};
							};
						};
						return true;
					} else if (input->is('*')) {
						while (input->read()) {
							if (input->is('*')) {
								if (input->read()) {
									if (input->is('/')) {
										input->read();
										return true;
									};
								};
							};
						};
						return true;
					} else {
						input->push();
						input->set('/');
					};
				};
			};
			return false;
		};

		void Token::ignoreSpaceOrComment() {
			while (isBOM() || isSpace() || isComment()) {
			};
		};

		bool Token::isSymbol(String &token) {
			if (input->is('_')
				|| input->between('A', 'Z')
				|| input->between('a', 'z')
			) {
				token.empty();
				token << input->inputChar;
				while (input->read()) {
					if (
						input->is('-')
						|| input->between('A', 'Z')
						|| input->between('a', 'z')
					) {
						token << input->inputChar;
					} else {
						ignoreSpaceOrComment();
						return true;
					};
				};
				return true;
			};
			return false;
		};

		bool Token::isString(String &token) {
			if (input->is('\"') || input->is('\'')) {
				token.empty();
				char strMark;
				strMark = input->inputChar;
				while (input->read()) {
					if (input->inputChar != strMark) {
						if (input->is('\\')) {
							if (input->read()) {
								if (input->is('\\')) {
									token << '\\';
									continue;
								};
								if (input->is('\"')) {
									token << '\"';
									continue;
								};
								if (input->is('\'')) {
									token << '\'';
									continue;
								};
								if (input->is('b')) {
									token << '\x08';
									continue;
								};
								if (input->is('t')) {
									token << '\x09';
									continue;
								};
								if (input->is('n')) {
									token << '\x0A';
									continue;
								};
								if (input->is('v')) {
									token << '\x0B';
									continue;
								};
								if (input->is('f')) {
									token << '\x0C';
									continue;
								};
								if (input->is('r')) {
									token << '\x0D';
									continue;
								};
								if (input->is('u')) {
									char code[5];
									String codeScan;
									unsigned int code4;
									if(!input->read()) {
										return false;
									};
									code[0] = input->inputChar;
									if(!input->read()) {
										return false;
									};
									code[1] = input->inputChar;
									if(!input->read()) {
										return false;
									};
									code[2] = input->inputChar;
									if(!input->read()) {
										return false;
									};
									code[3] = input->inputChar;
									code[4] = 0;
									if(sscanf(code, "%04X", &code4) != 1) {
										return false;
									};
									code[0] = (code4 >> 8) & 0xFF;
									code[1] = (code4) & 0xFF;
									code[2] = 0;
									token.concatenate(code, 2);
									continue;
								};
								if (input->is('U')) {
									char code[9];
									unsigned long int code8;
									if(!input->read()) {
										return false;
									};
									code[0] = input->inputChar;
									if(!input->read()) {
										return false;
									};
									code[1] = input->inputChar;
									if(!input->read()) {
										return false;
									};
									code[2] = input->inputChar;
									if(!input->read()) {
										return false;
									};
									code[3] = input->inputChar;
									if(!input->read()) {
										return false;
									};
									code[4] = input->inputChar;
									if(!input->read()) {
										return false;
									};
									code[5] = input->inputChar;
									if(!input->read()) {
										return false;
									};
									code[6] = input->inputChar;
									if(!input->read()) {
										return false;
									};
									code[7] = input->inputChar;
									code[8] = 0;
									if(sscanf(code, "%08lX", &code8) != 1) {
										return false;
									};
									code[0] = (code8 >> 24) & 0xFF;
									code[1] = (code8 >> 16) & 0xFF;
									code[2] = (code8 >> 8) & 0xFF;
									code[3] = (code8) & 0xFF;
									code[4] = 0;
									token.concatenate(code, 4);
									continue;
								};
								if (input->is('x')) {
									char code[3];
									unsigned int codeHex;
									if(!input->read()) {
										return false;
									};
									code[0] = input->inputChar;
									if(!input->read()) {
										return false;
									};
									code[1] = input->inputChar;
									code[2] = 0;
									if(sscanf(code, "%02X", &codeHex) != 1) {
										return false;
									};
									code[0] = (codeHex) & 0xFF;
									code[1] = 0;
									token.concatenate(code, 1);
									continue;
								};
								if (input->between('0', '3')) {
									char code[4];
									unsigned int codeOctal;
									code[0] = input->inputChar;
									if(!input->read()) {
										return false;
									};
									code[1] = input->inputChar;
									if(!input->read()) {
										return false;
									};
									code[2] = input->inputChar;
									code[3] = 0;
									if(sscanf(code, "%03o", &codeOctal) != 1) {
										return false;
									};
									code[0] = (codeOctal) & 0xFF;
									code[1] = 0;
									token.concatenate(codeOctal, 1);
									continue;
								};
								return false;
							} else {
								return false;
							};
						};

						token << input->inputChar;

					} else {
						input->read();
						ignoreSpaceOrComment();
						return true;
					};
				};
			};
			return false;
		};

		bool Token::isNumber(String &token) {
			if (input->is('-') || input->between('0', '9')) {
				token.empty();
				token << input->inputChar;
				while(input->read()) {
					if(input->between('0', '9')) {
						token << input->inputChar;
						continue;
					};
					break;
				};
				if (input->is('.')) {
					if(input->read()) {
						if(input->between('0', '9')) {
							token << '.';
							token << input->inputChar;
							while(input->read()) {
								if(input->between('0', '9')) {
									token << input->inputChar;
									continue;
								};
								break;
							};
							if(input->is('e') || input->is('E')) {
								token << input->inputChar;
								if(input->read()) {
									if(input->is('+') || input->is('-')) {
										token << input->inputChar;
										while(input->read()) {
											if(input->between('0', '9')) {
												token << input->inputChar;
												continue;
											};
											input->push();
											break;
										};
										return true;
									};
									input->push();
								};
								return true;
							};
							input->push();
							return true;
						};
						input->push();
						input->inputChar = '.';
					};
					input->push();
				};
				return true;
			};
			return false;
		};

	};

};
