//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-datastructures-json-value.hpp"

namespace XYO {
	namespace DataStructures {
		namespace JSON {

			XYO_DYNAMIC_TYPE_IMPLEMENT(Value, "{9DBDCF12-76F4-4DCB-93D4-EED2DA017A4B}");

			Value::Value() {
				XYO_DYNAMIC_TYPE_PUSH(Value);
			};

		};
	};
};
