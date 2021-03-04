//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_REGISTRYDATA_HPP
#define XYO_MANAGEDMEMORY_REGISTRYDATA_HPP

#ifndef XYO_DATASTRUCTURES_TXLIST2_HPP
#include "xyo-datastructures-txlist2.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {
		using namespace XYO::DataStructures;

		struct RegistryDataNode : TXList2Node<RegistryDataNode> {
			void *resourceThis;
			DeleteMemory deleteResource;
			FinalizeMemory finalizeResource;
		};

		typedef TXList2<RegistryDataNode> RegistryDataList;

		namespace RegistryData {

			XYO_EXPORT void finalizeResource(RegistryDataNode *this_);
			XYO_EXPORT void deleteResource(RegistryDataNode *this_);

		};

	};
};

#endif

