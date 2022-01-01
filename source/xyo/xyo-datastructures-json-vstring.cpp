//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-datastructures-json-vstring.hpp"

namespace XYO {
	namespace DataStructures {
		namespace JSON {

			XYO_DYNAMIC_TYPE_IMPLEMENT(VString, "{37AA6B34-DC44-446A-B425-601FF347C813}");

			VString::VString() {
				XYO_DYNAMIC_TYPE_PUSH(VString);
			};

			String VString::toString() {
				return value;
			};

			TPointer<VString> VString::fromString(const String &value) {
				TPointer<VString> retV(TMemory<VString>::newMemory());
				retV->value = value;
				return retV;
			};

		};
	};
};
