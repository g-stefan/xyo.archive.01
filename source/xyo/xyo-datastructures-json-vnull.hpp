//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_JSON_VNULL_HPP
#define XYO_DATASTRUCTURES_JSON_VNULL_HPP

#ifndef XYO_DATASTRUCTURES_JSON_VALUE_HPP
#	include "xyo-datastructures-json-value.hpp"
#endif

#ifndef XYO_ENCODING_STRING_HPP
#	include "xyo-encoding-string.hpp"
#endif

namespace XYO {

	namespace DataStructures {
		namespace JSON {
			class VNull;
		}
	};

	namespace ManagedMemory {
		template <>
		struct TMemory<DataStructures::JSON::VNull> : TMemoryPoolActive<DataStructures::JSON::VNull> {};
	};

	namespace DataStructures {
		namespace JSON {
			using namespace XYO::DataStructures;
			using namespace XYO::Encoding;

			class VNull : public Value {
					XYO_DISALLOW_COPY_ASSIGN_MOVE(VNull);
					XYO_DYNAMIC_TYPE_DEFINE(XYO_EXPORT, VNull);

				public:
					XYO_EXPORT VNull();

					XYO_EXPORT String toString();
			};

		};
	};
};

#endif
