//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_JSON_VASSOCIATIVEARRAY_HPP
#define XYO_DATASTRUCTURES_JSON_VASSOCIATIVEARRAY_HPP

#ifndef XYO_DATASTRUCTURES_JSON_VALUE_HPP
#	include "xyo-datastructures-json-value.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TASSOCIATIVEARRAY_HPP
#	include "xyo-datastructures-tassociativearray.hpp"
#endif

#ifndef XYO_ENCODING_STRING_HPP
#	include "xyo-encoding-string.hpp"
#endif

namespace XYO {

	namespace DataStructures {
		namespace JSON {
			class VAssociativeArray;
		};
	};

	namespace ManagedMemory {
		template <>
		struct TMemory<DataStructures::JSON::VAssociativeArray> : TMemoryPoolActive<DataStructures::JSON::VAssociativeArray> {};
	};

	namespace DataStructures {
		namespace JSON {
			using namespace XYO::ManagedMemory;
			using namespace XYO::DataStructures;
			using namespace XYO::Encoding;

			typedef TAssociativeArray<String, TPointerX<Value>, 4, TMemoryPoolActive> AssociativeArrayT;

			class VAssociativeArray : public Value {
					XYO_DISALLOW_COPY_ASSIGN_MOVE(VAssociativeArray);
					XYO_DYNAMIC_TYPE_DEFINE(XYO_EXPORT, VAssociativeArray);

				public:
					TPointerX<AssociativeArrayT> value;

					XYO_EXPORT VAssociativeArray();

					inline void activeDestructor() {
						value->activeDestructor();
					};

					static inline void initMemory() {
						Value::initMemory();
						AssociativeArrayT::initMemory();
					};

					inline void set(const String &key, const Value *x) {
						value->set(key, x);
					};

					inline bool get(const String &key, TPointer<Value> &x) {
						return value->get(key, x);
					};

					inline bool get(const String &key, TPointerX<Value> &x) {
						return value->get(key, x);
					};
			};

		};
	};
};

#endif
