//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-stream-streamx.hpp"

namespace XYO {
	namespace Stream {
		namespace StreamX {
			using namespace XYO::ManagedMemory;
			using namespace XYO::DataStructures;

			bool read(IRead &iread, String &out, size_t size) {
				StringReference *retV = TMemory<StringReference>::newMemory();
				retV->init();
				out = retV;

				size_t readLn;
				size_t readX;
				size_t readTotal;
				char buffer[16384];

				if(size == 0) {
					return true;
				};

				readTotal = 0;
				readX = 16384;
				if(size < readX) {
					readX = size;
				};
				for(;;) {
					readLn = iread.read(buffer, readX);
					if(readLn > 0) {
						retV->concatenateX(buffer, readLn);
					};
					if(readLn == 0) {
						if(readTotal == 0) {
							return false;
						};
					};
					//end of file
					if(readLn < readX) {
						break;
					};
					//end of read
					readTotal += readLn;
					if(readTotal >= size) {
						break;
					};
					readX = size - readTotal;
					if(readX > 16384) {
						readX = 16384;
					};
				};

				return true;
			};

			bool readLn(IRead &iread, String &out, size_t size) {
				StringReference *retV = TMemory<StringReference>::newMemory();
				retV->init();
				out = retV;

				size_t readLn;
				size_t readTotal;
				char buffer;

				readTotal = 0;
				if(size == 0) {
					return true;
				};

				for(;;) {
					readLn = iread.read(&buffer, 1);
					if(readLn > 0) {
						if(buffer == '\r') {
							if(readTotal + 1 >= size) {
								retV->concatenateX('\r');
								return true;
							};

							readLn = iread.read(&buffer, 1);
							if(readLn > 0) {
								if(buffer == '\n') {
									retV->concatenateX('\r');
									retV->concatenateX('\n');
									return true;
								};
								retV->concatenateX(buffer);
								readTotal += 2;
								if(readTotal >= size) {
									return true;
								};
								continue;
							};

							retV->concatenateX('\r');
							//end of file
							return true;
						};

						if(buffer == '\n') {
							retV->concatenateX('\n');
							return true;
						};

						retV->concatenateX(buffer);
						readTotal++;
						if(readTotal >= size) {
							return true;
						};
						continue;
					};
					// end
					if(readTotal == 0) {
						break;
					};
					//end of file
					return true;
				};

				return false;
			};

			size_t write(IWrite &iwrite, const String &data) {
				return iwrite.write(data.value(), data.length());
			};

			size_t writeLn(IWrite &iwrite, const String &data) {
				String data_ = data;
				data_ += "\r\n";
				return iwrite.write(data_.value(), data_.length());
			};

			size_t readToBuffer(IRead &iread, Buffer &buffer, size_t ln) {
				size_t readLn;
				size_t readToLn;
				size_t readX;
				size_t readTotal;

				readToLn = ln;
				readTotal = 0;
				readX = readToLn;
				for(;;) {
					readLn = iread.read(&buffer.buffer[readTotal], readX);
					//end of transmision
					if(readLn == 0) {
						break;
					};
					readTotal += readLn;
					if(readTotal >= readToLn) {
						break;
					};
					readX = readToLn - readTotal;
				};
				buffer.length = readTotal;
				return buffer.length;
			};

			size_t writeFromBuffer(IWrite &iwrite, Buffer &buffer) {
				return iwrite.write(buffer.buffer, buffer.length);
			};

		};
	};
};

