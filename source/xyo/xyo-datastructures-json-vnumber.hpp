//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_JSON_VNUMBER_HPP
#define XYO_DATASTRUCTURES_JSON_VNUMBER_HPP

#ifndef XYO_DATASTRUCTURES_JSON_VALUE_HPP
#include "xyo-datastructures-json-value.hpp"
#endif

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {

	namespace DataStructures {
		namespace JSON {
			class VNumber;
		};
	};

	namespace ManagedMemory {
		template<>
		struct TMemory<DataStructures::JSON::VNumber> : TMemoryPoolActive<DataStructures::JSON::VNumber> {};
	};

	namespace DataStructures {
		namespace JSON {
			using namespace XYO::ManagedMemory;
			using namespace XYO::DataStructures;
			using namespace XYO::Encoding;

			typedef double NumberT;

			class VNumber : public Value {
					XYO_DISALLOW_COPY_ASSIGN_MOVE(VNumber);
					XYO_DYNAMIC_TYPE_DEFINE(XYO_EXPORT, VNumber);

				public:

					NumberT value;

					XYO_EXPORT VNumber();

					inline void activeDestructor() {
						value = 0;
					};

					XYO_EXPORT String toString();
					XYO_EXPORT static TPointer<VNumber> fromNumber(NumberT value);
					XYO_EXPORT static TPointer<VNumber> fromString(const String &value);
			};

		};
	};

};

#endif
