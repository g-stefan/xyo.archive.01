//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-system-compiler.hpp"
#include "xyo-system-shell.hpp"
#include "xyo-system-datetime.hpp"
#include "xyo-cryptography-md5.hpp"
#include "xyo-multithreading-workerqueue.hpp"
#include "xyo-datastructures-ini.hpp"
#include "xyo-system-util.hpp"
#include "xyo-encoding-string.hpp"

namespace XYO {
	namespace System {
		namespace Util {
			using namespace XYO::Cryptography;
			using namespace XYO::Multithreading;
			using namespace XYO::DataStructures;
			using namespace XYO::System;
			using namespace XYO::Encoding;

			bool fileToCpp(
				const char *stringName,
				const char *fileNameIn,
				const char *fileNameOut,
				bool append,
				bool isString) {

				FILE *input;
				FILE *output;
				uint8_t ch;
				int index;
				int first;

				input = fopen(fileNameIn, "rb");
				if (input != nullptr) {
					output = fopen(fileNameOut, append ? "ab" : "wb");
					if (output != nullptr) {
						if(isString) {
							fprintf(output, "static const char %s[]={", stringName);
						} else {
							fprintf(output, "static const uint8_t %s[]={", stringName);
						};

						ch = 0x00;
						index = 0;
						first = 1;
						while(fread(&ch, 1, 1, input) == 1) {

							if(first) {
								first = 0;
								fprintf(output, "\n\t");
							} else {
								fprintf(output, ",");
								if(index == 0) {
									fprintf(output, "\n\t");
								};
							};

							fprintf(output, "0x%02X", ch);

							++index;
							index %= 32;

							ch = 0;
						};

						if(index == 0) {
							fprintf(output, "\n\t");
						};

						++index;
						index %= 32;

						if(isString) {
							if(index > 0) {
								fprintf(output, ",0x00");
							};
						};

						fprintf(output, "\n};\n");
						fclose(output);
						fclose(input);
						return true;
					};
					fclose(input);
				};
				return false;
			};

			bool fileToJs(
				const char *stringName,
				const char *fileNameIn,
				const char *fileNameOut,
				bool append) {

				FILE *input;
				FILE *output;
				uint8_t ch;
				int index;
				int first;

				input = fopen(fileNameIn, "rb");
				if (input != nullptr) {
					output = fopen(fileNameOut, append ? "ab" : "wb");
					if (output != nullptr) {
						fprintf(output, "var %s=[", stringName);

						ch = 0x00;
						index = 0;
						first = 1;
						while(fread(&ch, 1, 1, input) == 1) {

							if(first) {
								first = 0;
								fprintf(output, "\n\t");
							} else {
								fprintf(output, ",");
								if(index == 0) {
									fprintf(output, "\n\t");
								};
							};

							fprintf(output, "0x%02X", ch);

							++index;
							index %= 32;

							ch = 0;
						};

						if(index == 0) {
							fprintf(output, "\n\t");
						};

						++index;
						index %= 32;

						fprintf(output, "\n];\n");
						fclose(output);
						fclose(input);
						return true;
					};
					fclose(input);
				};
				return false;
			};

			bool fileToRc(
				const char *stringName,
				const char *fileNameIn,
				const char *fileNameOut,
				bool append) {

				FILE *input;
				FILE *output;
				uint16_t ch;
				int flag;
				int k;

				input = fopen(fileNameIn, "rb");
				if (input != nullptr) {
					output = fopen(fileNameOut, append ? "ab" : "wb");
					if (output != nullptr) {

						fprintf(output, "%s RCDATA {", stringName);


						flag = 0;
						do {
							ch = 0x0A0A;
							k = fread(&ch, 1, 2, input);
							if (k == 2) {
								if (flag == 1) {
									fprintf(output, ",");
									flag = 0;
								};
								fprintf(output, "0x%04X", ch);
								flag = 1;
							};
						} while (k == 2);

						if (k == 1) {
							if (flag == 1) {
								fprintf(output, ",");
								flag = 0;
							};
							fprintf(output, "0x%04X}\n", ch);
						} else {
							fprintf(output, "}\n");
						};


						fclose(output);
						fclose(input);
						return true;
					};
					fclose(input);
				};
				return false;
			};

			bool pathToHtmlRc(
				const char *pathOrFileNameIn,
				const char *fileNameOut,
				bool append,
				const char *basePath) {

				int k;
				size_t index;
				TDynamicArray<String> fileList;
				FILE *output;
				String pathToSearch = pathOrFileNameIn;
				String line;
				String basePathX;
				String fileName;

				if(!(String::indexOf(pathToSearch, "*", 0, index) || String::indexOf(pathToSearch, "?", 0, index))) {
					pathToSearch += "/*";
				};

				if(basePath) {
					basePathX = basePath;
				} else {
					basePathX = Shell::getFilePathX(pathToSearch);
				};

				output = fopen(fileNameOut, append ? "ab" : "wb");
				if (output != nullptr) {

					Shell::getFileList(pathToSearch, fileList);
					for(k = 0; k < fileList.length(); ++k) {
						fileName = String::substring(fileList[k], basePathX.length());
						line = String::replace(fileName, "\\", "/") +
							" HTML \"" +
							String::replace(String::replace(fileList[k], "/", "\\"), "\\", "\\\\") +
							"\"\r\n";
						fwrite(line.value(), 1, line.length(), output);
					};
					fclose(output);

					fileList.empty();

					Shell::getDirList(pathToSearch, fileList);
					for(k = 0; k < fileList.length(); ++k) {
						if(!pathToHtmlRc(fileList[k], fileNameOut, true, basePathX)) {
							return false;
						};
					};

					return true;
				};
				return false;
			};

			bool fileToCString(
				const char *stringName,
				const char *fileNameIn,
				const char *fileNameOut) {

				String content;
				if(Shell::fileGetContents(fileNameIn, content)) {
					if(Shell::filePutContents(fileNameOut, "static const char *")) {
						if(Shell::filePutContentsAppend(fileNameOut, stringName)) {
							if(Shell::filePutContentsAppend(fileNameOut, "=")) {
								if(Shell::filePutContentsAppend(fileNameOut, String::encodeC(content))) {
									return Shell::filePutContentsAppend(fileNameOut, ";\r\n");
								};
							};
						};
					};
				};
				return false;
			};

			bool fileToCStringDirect(
				const char *fileNameIn,
				const char *fileNameOut) {

				String content;
				if(Shell::fileGetContents(fileNameIn, content)) {
					return Shell::filePutContents(fileNameOut, String::encodeC(content));
				};
				return false;
			};

		};
	};
};

