//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-datastructures-json-vassociativearray.hpp"

namespace XYO {
	namespace DataStructures {
		namespace JSON {

			XYO_DYNAMIC_TYPE_IMPLEMENT(VAssociativeArray, "{6D88E885-5D8E-4BB5-8EEC-32AAA4942359}");

			VAssociativeArray::VAssociativeArray() {
				XYO_DYNAMIC_TYPE_PUSH(VAssociativeArray);

				value.pointerLink(this);
				value.newMemory();
			};

		};
	};
};
