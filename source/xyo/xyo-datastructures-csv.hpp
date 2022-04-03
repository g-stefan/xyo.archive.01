//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_CSV_HPP
#define XYO_DATASTRUCTURES_CSV_HPP

#ifndef XYO_DATASTRUCTURES_TDYNAMICARRAY_HPP
#	include "xyo-datastructures-tdynamicarray.hpp"
#endif

#ifndef XYO_ENCODING_STRING_HPP
#	include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace DataStructures {
		using namespace XYO::ManagedMemory;
		using namespace XYO::DataStructures;
		using namespace XYO::Encoding;

		typedef TDynamicArray<String> CSVRow;
		typedef TDynamicArray<CSVRow> CSVFile;

		namespace CSVFileX {

			XYO_EXPORT bool load(const char *fileName, CSVFile &csvFile);
			XYO_EXPORT bool save(const char *fileName, CSVFile &csvFile);
			XYO_EXPORT bool decode(const String csvLine, CSVRow &csvRow);
			XYO_EXPORT bool encode(String &csvLine, CSVRow &csvRow);

		};
	};
};

#endif
