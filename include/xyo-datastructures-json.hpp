//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_JSON_HPP
#define XYO_DATASTRUCTURES_JSON_HPP

#ifndef XYO_DATASTRUCTURES_JSON_VALUE_HPP
#include "xyo-datastructures-json-value.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_JSON_VNULL_HPP
#include "xyo-datastructures-json-vnull.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_JSON_VBOOLEAN_HPP
#include "xyo-datastructures-json-vboolean.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_JSON_VNUMBER_HPP
#include "xyo-datastructures-json-vnumber.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_JSON_VSTRING_HPP
#include "xyo-datastructures-json-vstring.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_JSON_VARRAY_HPP
#include "xyo-datastructures-json-varray.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_JSON_VASSOCIATIVEARRAY_HPP
#include "xyo-datastructures-json-vassociativearray.hpp"
#endif

#ifndef XYO_STREAM_IREAD_HPP
#include "xyo-stream-iread.hpp"
#endif

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

#ifndef XYO_PARSER_TOKEN_HPP
#include "xyo-parser-token.hpp"
#endif

namespace XYO {
	namespace DataStructures {
		namespace JSON {
			using namespace XYO::Stream;
			using namespace XYO::Parser;
			using namespace XYO::Encoding;

			XYO_EXPORT void initMemory();
			//
			XYO_EXPORT String encodeAssociativeArray(VAssociativeArray *vAssociativeArray);
			XYO_EXPORT String encodeArray(VArray *vArray);
			XYO_EXPORT String encodeString(VString *vString);
			XYO_EXPORT String encodeNumber(VNumber *vNumber);
			XYO_EXPORT String encodeBoolean(VBoolean *vBoolean);
			XYO_EXPORT String encodeNull(VNull *vNull);
			//---
			XYO_EXPORT bool decode(Token &token, TPointer<Value> &result);
			XYO_EXPORT bool decodeArray(Token &token, TPointer<Value> &result);
			XYO_EXPORT bool decodeAssociativeArray(Token &token, TPointer<Value> &result);
			//---
			XYO_EXPORT String encode(Value *value);
			XYO_EXPORT TPointer<Value> decode(IRead *iRead);
			XYO_EXPORT TPointer<Value> decode(const String &value);
			//---
			XYO_EXPORT String encodeAssociativeArrayWithIndentation(VAssociativeArray *vAssociativeArray, const String &indentation = "");
			XYO_EXPORT String encodeArrayWithIndentation(VArray *vArray, const String &indentation = "");
			XYO_EXPORT String encodeWithIndentation(Value *value, const String &indentation = "");

		};
	};
};

#endif

