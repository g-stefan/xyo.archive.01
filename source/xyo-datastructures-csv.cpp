//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-managedmemory-tmemory.hpp"
#include "xyo-datastructures-csv.hpp"
#include "xyo-system-file.hpp"
#include "xyo-stream-streamx.hpp"
#include "xyo-encoding-string.hpp"

namespace XYO {
	namespace DataStructures {
		namespace CSVFileX {
			using namespace XYO::ManagedMemory;
			using namespace XYO::Stream;
			using namespace XYO::System;
			using namespace XYO::Encoding;

			bool load(const char *fileName, CSVFile &csvFile) {
				File file;
				String line;
				String lineX;
				String trimElements = " \t\r\n";
				csvFile.empty();
				if(file.openRead(fileName)) {
					while(StreamX::readLn(file, line, 16384)) {
						lineX = String::trimWithElement(line, trimElements);
						if(!decode(lineX, csvFile.push())) {
							return false;
						};
					};
					file.close();
					return true;
				};
				return false;
			};

			bool save(const char *fileName, CSVFile &csvFile) {
				File file;
				String line;
				if(file.openWrite(fileName)) {
					size_t k;
					for(k = 0; k < csvFile.length(); ++k) {
						if(!encode(line, csvFile[k])) {
							return false;
						};
						StreamX::write(file, line);
						StreamX::write(file, "\r\n");
					};
					file.close();
					return true;
				};
				return false;
			};

			bool decode(const String csvLine, CSVRow &csvRow) {
				String out_;
				size_t k;
				size_t ln;

				csvRow.empty();
				out_ = "";
				ln = 0;
				for(k = 0; k < csvLine.length(); ++k) {
					if(csvLine[k] == ',') {
						csvRow[ln] = out_;
						ln++;
						out_ = "";
						continue;
					};
					if(csvLine[k] == '\"') {
						++k;
						for(; k < csvLine.length(); ++k) {
							if(csvLine[k] == '\"') {
								if(k + 1 < csvLine.length()) {
									if(csvLine[k + 1] == '\"') {
										out_ << '\"';
										++k;
										continue;
									};
								};
								break;
							};
							out_ << csvLine[k];
						};
						continue;
					};
					out_ << csvLine[k];
				};
				csvRow[ln] = out_;

				return true;
			};

			bool encode(String &csvLine, CSVRow &csvRow) {
				csvLine = "";

				bool useComa;
				bool useEscape;

				size_t k;
				size_t sz;

				useComa = false;
				for(k = 0; k < csvRow.length(); ++k) {
					if(useComa) {
						csvLine << ',';
					};
					useEscape = false;
					if(String::indexOf(csvRow[k], " ", 0, sz)) {
						useEscape = true;
					};
					if(String::indexOf(csvRow[k], "\t", 0, sz)) {
						useEscape = true;
					};
					if(String::indexOf(csvRow[k], ",", 0, sz)) {
						useEscape = true;
					};
					if(useEscape) {
						csvLine << '"';
					};
					if(String::indexOf(csvRow[k], "\"", 0, sz)) {
						useEscape = true;
						csvLine << String::replace(csvRow[k], "\"", "\"\"");
					} else {
						csvLine << csvRow[k];
					};
					if(useEscape) {
						csvLine << '"';
					};
					useComa = true;
				};

				return true;
			};

		};
	};
};

