//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_JSON_VARRAY_HPP
#define XYO_DATASTRUCTURES_JSON_VARRAY_HPP

#ifndef XYO_DATASTRUCTURES_JSON_VALUE_HPP
#	include "xyo-datastructures-json-value.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TDYNAMICARRAY_HPP
#	include "xyo-datastructures-tdynamicarray.hpp"
#endif

namespace XYO {

	namespace DataStructures {
		namespace JSON {
			class VArray;
		};
	};

	namespace ManagedMemory {
		template <>
		struct TMemory<DataStructures::JSON::VArray> : TMemoryPoolActive<DataStructures::JSON::VArray> {};
	};

	namespace DataStructures {
		namespace JSON {
			using namespace XYO::ManagedMemory;
			using namespace XYO::DataStructures;

			typedef TDynamicArray<TPointerX<Value>, 4, TMemoryPoolActive> ArrayT;

			class VArray : public Value {
					XYO_DISALLOW_COPY_ASSIGN_MOVE(VArray);
					XYO_DYNAMIC_TYPE_DEFINE(XYO_EXPORT, VArray);

				public:
					TPointerX<ArrayT> value;

					XYO_EXPORT VArray();

					inline void activeDestructor() {
						value->activeDestructor();
					};

					static inline void initMemory() {
						Value::initMemory();
						ArrayT::initMemory();
					};

					inline size_t length() const {
						return value->length();
					};

					inline TPointerX<Value> &index(size_t idx) {
						return value->index(idx);
					};

					inline TPointerX<Value> &operator[](int idx) {
						return value->index((size_t)idx);
					};

					inline bool get(size_t idx, TPointer<Value> &x) {
						return value->get(idx, x);
					};

					inline bool get(size_t idx, TPointerX<Value> &x) {
						return value->get(idx, x);
					};
			};

		};
	};
};

#endif
