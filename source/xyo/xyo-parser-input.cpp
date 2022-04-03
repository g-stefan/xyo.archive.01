//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-parser-input.hpp"

namespace XYO {
	namespace Parser {
		using namespace XYO::Stream;

		Input::Input() {
			iRead.pointerLink(this);
			iStackIndex = 0;
			iStackSize = 8;
			iStack = new char[iStackSize]();
			isEof_ = false;
		};

		Input::~Input() {
			delete[] iStack;
		};

		bool Input::open(IRead *iRead_, size_t iStackSize_) {
			iRead = iRead_;
			delete[] iStack;
			iStackIndex = 0;
			iStackSize = iStackSize_;
			iStack = new char[iStackSize]();
			isEof_ = false;
			return true;
		};

		void Input::close() {
			activeDestructor();
		};

		void Input::activeDestructor() {
			iRead.deleteMemory();
			delete[] iStack;
			iStackIndex = 0;
			iStack = new char[iStackSize]();
			isEof_ = false;
		};

		bool Input::isN(const char *name) {
			int k;
			for (k = 0; name[k] != 0; ++k) {
				if (inputChar == name[k]) {
					if (read()) {
						continue;
					};
				};
				break;
			};
			if (name[k] == 0) {
				return true;
			};
			for (--k; k >= 0; --k) {
				push();
				inputChar = name[k];
			};
			return false;
		};

	};
};
