//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_JSON_VBOOLEAN_HPP
#define XYO_DATASTRUCTURES_JSON_VBOOLEAN_HPP

#ifndef XYO_DATASTRUCTURES_JSON_VALUE_HPP
#include "xyo-datastructures-json-value.hpp"
#endif

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {

	namespace DataStructures {
		namespace JSON {
			class VBoolean;
		};
	};

	namespace ManagedMemory {
		template<>
		struct TMemory<DataStructures::JSON::VBoolean> : TMemoryPoolActive<DataStructures::JSON::VBoolean> {};
	};

	namespace DataStructures {
		namespace JSON {
			using namespace XYO::ManagedMemory;
			using namespace XYO::DataStructures;
			using namespace XYO::Encoding;

			typedef bool BooleanT;

			class VBoolean : public Value {
					XYO_DISALLOW_COPY_ASSIGN_MOVE(VBoolean);
					XYO_DYNAMIC_TYPE_DEFINE(XYO_EXPORT, VBoolean);

				public:

					BooleanT value;

					XYO_EXPORT VBoolean();

					inline void activeDestructor() {
						value = false;
					};

					XYO_EXPORT String toString();
					XYO_EXPORT static TPointer<VBoolean> fromBoolean(BooleanT value);
					XYO_EXPORT static TPointer<VBoolean> fromString(const String &value);
			};

		};
	};
};

#endif
