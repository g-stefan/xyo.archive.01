//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-datastructures-json-varray.hpp"

namespace XYO {
	namespace DataStructures {
		namespace JSON {

			XYO_DYNAMIC_TYPE_IMPLEMENT(VArray, "{3ECCB902-C928-4DBD-AD23-815EF4BFA6AF}");

			VArray::VArray() {
				XYO_DYNAMIC_TYPE_PUSH(VArray);

				value.pointerLink(this);
				value.newMemory();
			};

		};
	};
};
