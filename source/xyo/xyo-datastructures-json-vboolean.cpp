//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-datastructures-json-vboolean.hpp"

namespace XYO {
	namespace DataStructures {
		namespace JSON {

			XYO_DYNAMIC_TYPE_IMPLEMENT(VBoolean, "{FD507FEE-4FFC-47DB-89D7-A84020D58D9D}");

			VBoolean::VBoolean() {
				XYO_DYNAMIC_TYPE_PUSH(VBoolean);

				value = false;
			};

			String VBoolean::toString() {
				if(value) {
					return "true";
				};
				return "false";
			};

			TPointer<VBoolean> VBoolean::fromBoolean(BooleanT value) {
				TPointer<VBoolean> retV(TMemory<VBoolean>::newMemory());
				retV->value = value;
				return retV;
			};

			TPointer<VBoolean> VBoolean::fromString(const String &value) {
				TPointer<VBoolean> retV(TMemory<VBoolean>::newMemory());
				if(value == "true") {
					retV->value = true;
					return retV;
				};
				retV->value = false;
				return retV;
			};

		};
	};
};


