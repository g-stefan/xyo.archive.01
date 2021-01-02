//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_JSON_VALUE_HPP
#define XYO_DATASTRUCTURES_JSON_VALUE_HPP

#ifndef XYO_DATASTRUCTURES_DYNAMICOBJECT_HPP
#include "xyo-datastructures-dynamicobject.hpp"
#endif

namespace XYO {

	namespace DataStructures {
		namespace JSON {
			class Value;
		}
	};

	namespace ManagedMemory {
		template<>
		struct TMemory<DataStructures::JSON::Value> : TMemoryPoolActive<DataStructures::JSON::Value> {};
	};

	namespace DataStructures {
		namespace JSON {
			using namespace XYO::DataStructures;

			class Value : public DynamicObject {
					XYO_DISALLOW_COPY_ASSIGN_MOVE(Value);
					XYO_DYNAMIC_TYPE_DEFINE(XYO_EXPORT, Value);
				public:
					XYO_EXPORT Value();
			};

		};
	};
};

#endif
