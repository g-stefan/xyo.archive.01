//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-encoding-utfstream.hpp"

namespace XYO {
	namespace Encoding {
		using namespace XYO::DataStructures;

		Utf8Read::Utf8Read() {
			input.pointerLink(this);
			mode = UtfStreamMode::None;
			index = 0;
			size = 0;
		};

		Utf8Read::~Utf8Read() {
		};

		bool Utf8Read::open(IRead *input_, int mode_) {
			input = input_;
			mode = mode_;
			index = 0;
			size = 0;
			return true;
		};

		size_t Utf8Read::read(void *output, size_t length) {
			switch(mode) {
				case UtfStreamMode::None:
				case UtfStreamMode::Utf8:
					return input->read(output, length);
				case UtfStreamMode::Utf16: {
						size_t readLn = 0;
						while(length > 0) {
							if(index == 0) {
								utf16 utf16Data[2];
								if(input->read(&utf16Data[0], sizeof(utf16)) != sizeof(utf16)) {
									return readLn;
								};
								size_t convertLn = 0;
								convertLn = Utf16Core::elementSize(utf16Data[0]);
								if(convertLn == 0) {
									return readLn;
								};
								if(convertLn == 2) {
									if(input->read(&utf16Data[1], sizeof(utf16)) != sizeof(utf16)) {
										return readLn;
									};
								};
								utf32 utf32Data;
								if(!Utf::elementUtf32FromUtf16(&utf32Data, &utf16Data[0])) {
									return readLn;
								};
								size = Utf::elementUtf8FromUtf32(&utf8Input[0], utf32Data);
								utf8Input[size] = 0;
							};
							((char *)output)[readLn] = utf8Input[index];
							index++;
							readLn++;
							--length;
							if(index >= size) {
								index = 0;
								size = 0;
							};
						};
						return readLn;
					};
				case UtfStreamMode::Utf32: {
						size_t readLn = 0;
						while(length > 0) {
							if(index == 0) {
								utf32 utf32Data;
								if(input->read(&utf32Data, sizeof(utf32)) != sizeof(utf32)) {
									return readLn;
								};
								size = Utf::elementUtf8FromUtf32(&utf8Input[0], utf32Data);
								utf8Input[size] = 0;
							};
							((char *)output)[readLn] = utf8Input[index];
							index++;
							readLn++;
							--length;
							if(index >= size) {
								index = 0;
								size = 0;
							};
						};
						return readLn;
					};
				default:
					break;
			};
			return 0;
		};

		void Utf8Read::close() {
			input.deleteMemory();
		};

		Utf8Write::Utf8Write() {
			output.pointerLink(this);
			mode = UtfStreamMode::None;
			index = 0;
			size = 0;
		};

		Utf8Write::~Utf8Write() {
		};

		bool Utf8Write::open(IWrite *output_, int mode_) {
			output = output_;
			mode = mode_;
			index = 0;
			size = 0;
			return true;
		};

		size_t Utf8Write::write(const void *input, size_t length) {
			switch(mode) {
				case UtfStreamMode::None:
				case UtfStreamMode::Utf8:
					return output->write(input, length);
				case UtfStreamMode::Utf16: {
						size_t writeLn = 0;
						while(length > 0) {
							if(index == 0) {
								size = Utf8Core::elementSize(((char *)input)[writeLn]);
							};
							utf8Output[index] = ((char *)input)[writeLn];
							index++;
							writeLn++;
							--length;
							if(index >= size) {
								utf32 utf32Data;
								size_t convertLn = 0;
								convertLn = Utf::elementUtf32FromUtf8(&utf32Data, &utf8Output[0]);
								if(convertLn == 0) {
									return writeLn;
								};
								utf16 utf16Data[2];
								convertLn = Utf::elementUtf16FromUtf32(&utf16Data[0], utf32Data);
								if(convertLn == 0) {
									return writeLn;
								};
								if(output->write(&utf16Data[0], sizeof(utf16)*convertLn) != sizeof(utf16)*convertLn) {
									return writeLn;
								};
								index = 0;
								size = 0;
							};
						};
						return writeLn;
					};
				case UtfStreamMode::Utf32: {
						size_t writeLn = 0;
						while(length > 0) {
							if(index == 0) {
								size = Utf8Core::elementSize(((char *)input)[writeLn]);
							};
							utf8Output[index] = ((char *)input)[writeLn];
							index++;
							writeLn++;
							--length;
							if(index >= size) {
								utf32 utf32Data;
								size_t convertLn = 0;
								convertLn = Utf::elementUtf32FromUtf8(&utf32Data, &utf8Output[0]);
								if(convertLn == 0) {
									return writeLn;
								};
								if(output->write(&utf32Data, sizeof(utf32Data)*convertLn) != sizeof(utf32Data)*convertLn) {
									return writeLn;
								};
								index = 0;
								size = 0;
							};
						};
						return writeLn;
					};
				default:
					break;
			};
			return 0;
		};

		void Utf8Write::close() {
			output.deleteMemory();
		};

	};
};


