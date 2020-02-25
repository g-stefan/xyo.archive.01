//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-managedmemory-tmemory.hpp"
#include "xyo-parser-token.hpp"
#include "xyo-stream-memoryread.hpp"
#include "xyo-datastructures-json.hpp"

namespace XYO {
	namespace DataStructures {
		namespace JSON {
			using namespace XYO::ManagedMemory;
			using namespace XYO::Stream;
			using namespace XYO::Parser;

			void initMemory() {
				TMemory<Value>::initMemory();
				TMemory<VNull>::initMemory();
				TMemory<VBoolean>::initMemory();
				TMemory<VNumber>::initMemory();
				TMemory<VString>::initMemory();
				TMemory<VArray>::initMemory();
				TMemory<VAssociativeArray>::initMemory();
			};

			String encodeAssociativeArray(VAssociativeArray *vAssociativeArray) {
				size_t index;
				String retV;
				retV << '{';
				for(index = 0; index < vAssociativeArray->value->length();) {
					retV << String::encodeC(vAssociativeArray->value->arrayKey->index(index));
					retV << ':';
					retV << encode((vAssociativeArray->value->arrayValue->index(index)).value());
					++index;
					if(index < vAssociativeArray->value->length()) {
						retV << ',';
					};
				};
				retV << '}';
				return retV;
			};

			String encodeArray(VArray *vArray) {
				size_t index;
				String retV;
				retV << '[';
				for(index = 0; index < vArray->value->length();) {
					retV << encode((vArray->value->index(index)).value());
					++index;
					if(index < vArray->value->length()) {
						retV << ',';
					};
				};
				retV << ']';
				return retV;
			};

			String encodeString(VString *vString) {
				return String::encodeC(vString->value);
			};

			String encodeNumber(VNumber *vNumber) {
				return vNumber->toString();
			};

			String encodeBoolean(VBoolean *vBoolean) {
				return vBoolean->toString();
			};

			String encodeNull(VNull *vNull) {
				return vNull->toString();
			};

			String encode(Value *value) {
				VNull *vNull = TDynamicCast<VNull *>(value);
				if(vNull) {
					return encodeNull(vNull);
				};
				VBoolean *vBoolean = TDynamicCast<VBoolean *>(value);
				if(vBoolean) {
					return encodeBoolean(vBoolean);
				};
				VNumber *vNumber = TDynamicCast<VNumber *>(value);
				if(vNumber) {
					return encodeNumber(vNumber);
				};
				VString *vString = TDynamicCast<VString *>(value);
				if(vString) {
					return encodeString(vString);
				};
				VArray *vArray = TDynamicCast<VArray *>(value);
				if(vArray) {
					return encodeArray(vArray);
				};
				VAssociativeArray *vAssociativeArray = TDynamicCast<VAssociativeArray *>(value);
				if(vAssociativeArray) {
					return encodeAssociativeArray(vAssociativeArray);
				};
				return "";
			};

			bool decodeArray(Token &token, TPointer<Value> &result) {
				token.ignoreSpaceOrComment();
				if (token.is1('[')) {
					size_t index = 0;
					TPointer<VArray> vArray;
					vArray.newMemory();
					result = vArray;
					while (!token.isEof()) {
						token.ignoreSpaceOrComment();
						if (token.is1(']')) {
							return true;
						};
						if (token.is1(',')) {
							continue;
						};
						TPointer<Value> value;
						if(decode(token, value)) {
							vArray->value->set(index++, value);
							continue;
						};
						break;
					};
				};
				return false;
			};

			bool decodeAssociativeArray(Token &token, TPointer<Value> &result) {
				token.ignoreSpaceOrComment();
				if (token.is1('{')) {
					String key;
					size_t index = 0;
					TPointer<VAssociativeArray> vAssociativeArray;
					vAssociativeArray.newMemory();
					result = vAssociativeArray;
					while (!token.isEof()) {
						token.ignoreSpaceOrComment();
						if (token.is1('}')) {
							return true;
						};
						if (token.is1(',')) {
							continue;
						};
						if (token.isString(key)) {
							token.ignoreSpaceOrComment();
							if (token.is1(':')) {
								token.ignoreSpaceOrComment();
								TPointer<Value> value;
								if(decode(token, value)) {
									vAssociativeArray->value->set(key, value);
									continue;
								};
							};
						};
						break;
					};
				};
				return false;
			};

			bool decode(Token &token, TPointer<Value> &result) {
				token.ignoreSpaceOrComment();
				String value;
				if(token.is('{')) {
					return decodeAssociativeArray(token, result);
				};
				if(token.is('[')) {
					return decodeArray(token, result);
				};
				if (token.isString(value)) {
					result = VString::fromString(value);
					return true;
				};
				if (token.isNumber(value)) {
					result = VNumber::fromString(value);
					return true;
				};
				if (token.isN("true")) {
					result = VBoolean::fromBoolean(true);
					return true;
				};
				if (token.isN("false")) {
					result = VBoolean::fromBoolean(false);
					return true;
				};
				if (token.isN("null")) {
					TPointer<VNull> value;
					value.newMemory();
					result = value;
					return true;
				};
				return false;
			};

			TPointer<Value> decode(IRead *iRead) {
				Input input;
				Token token;
				if(input.open(iRead, 16)) {
					if(token.open(&input)) {
						if(token.read()) {
							TPointer<Value> value;
							if(decode(token, value)) {
								return value;
							};
						};
					};
				};
				return nullptr;
			};

			TPointer<Value> decode(const String &value) {
				MemoryRead mRead;
				if(mRead.open(value.value(), value.length())) {
					return decode(&mRead);
				};
				return nullptr;
			};

			//---

			String encodeAssociativeArrayWithIndentation(VAssociativeArray *vAssociativeArray, const String &indentation) {
				size_t index;
				String retV;
				retV << '{';
				retV << '\n';
				for(index = 0; index < vAssociativeArray->value->length();) {
					retV << indentation;
					retV << '\t';
					retV << String::encodeC(vAssociativeArray->value->arrayKey->index(index));
					retV << ':';
					retV << ' ';
					retV << encode((vAssociativeArray->value->arrayValue->index(index)).value());
					++index;
					if(index < vAssociativeArray->value->length()) {
						retV << ',';
						retV << '\n';
					};
				};
				retV << '\n';
				retV << indentation;
				retV << '}';
				return retV;
			};

			String encodeArrayWithIndentation(VArray *vArray, const String &indentation) {
				size_t index;
				String retV;
				retV << '[';
				retV << '\n';
				for(index = 0; index < vArray->value->length();) {
					retV << indentation;
					retV << '\t';
					retV << encodeWithIndentation((vArray->value->index(index)).value(), indentation + '\t');
					++index;
					if(index < vArray->value->length()) {
						retV << ',';
						retV << '\n';
					};
				};
				retV << '\n';
				retV << indentation;
				retV << ']';
				return retV;
			};

			String encodeWithIndentation(Value *value, const String &indentation) {
				VNull *vNull = TDynamicCast<VNull *>(value);
				if(vNull) {
					return encodeNull(vNull);
				};
				VBoolean *vBoolean = TDynamicCast<VBoolean *>(value);
				if(vBoolean) {
					return encodeBoolean(vBoolean);
				};
				VNumber *vNumber = TDynamicCast<VNumber *>(value);
				if(vNumber) {
					return encodeNumber(vNumber);
				};
				VString *vString = TDynamicCast<VString *>(value);
				if(vString) {
					return encodeString(vString);
				};
				VArray *vArray = TDynamicCast<VArray *>(value);
				if(vArray) {
					return encodeArrayWithIndentation(vArray, indentation);
				};
				VAssociativeArray *vAssociativeArray = TDynamicCast<VAssociativeArray *>(value);
				if(vAssociativeArray) {
					return encodeAssociativeArrayWithIndentation(vAssociativeArray, indentation);
				};
				return "";
			};

		};
	};
};

