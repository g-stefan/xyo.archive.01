//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-datastructures-json-vnull.hpp"

namespace XYO {
	namespace DataStructures {
		namespace JSON {

			XYO_DYNAMIC_TYPE_IMPLEMENT(VNull, "{2CF03903-E324-49DE-8B96-E3FF8526768E}");

			VNull::VNull() {
				XYO_DYNAMIC_TYPE_PUSH(VNull);
			};

			String VNull::toString() {
				return "null";
			};

		};
	};
};


