//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_JSON_VSTRING_HPP
#define XYO_DATASTRUCTURES_JSON_VSTRING_HPP

#ifndef XYO_DATASTRUCTURES_JSON_VALUE_HPP
#	include "xyo-datastructures-json-value.hpp"
#endif

#ifndef XYO_ENCODING_STRING_HPP
#	include "xyo-encoding-string.hpp"
#endif

namespace XYO {

	namespace DataStructures {
		namespace JSON {

			class VString;
		};
	};

	namespace ManagedMemory {
		template <>
		struct TMemory<DataStructures::JSON::VString> : TMemoryPoolActive<DataStructures::JSON::VString> {};
	};

	namespace DataStructures {
		namespace JSON {
			using namespace XYO::ManagedMemory;
			using namespace XYO::DataStructures;
			using namespace XYO::Encoding;

			typedef String StringT;

			class VString : public Value {
					XYO_DISALLOW_COPY_ASSIGN_MOVE(VString);
					XYO_DYNAMIC_TYPE_DEFINE(XYO_EXPORT, VString);

				public:
					StringT value;

					XYO_EXPORT VString();

					inline void activeDestructor() {
						value.activeDestructor();
					};

					static inline void initMemory() {
						DynamicObject::initMemory();
						String::initMemory();
					};

					XYO_EXPORT String toString();
					XYO_EXPORT static TPointer<VString> fromString(const String &value);
			};

		};
	};

};

#endif
