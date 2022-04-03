//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-managedmemory-registrydata.hpp"

namespace XYO {
	namespace ManagedMemory {
		using namespace XYO::DataStructures;

		namespace RegistryData {

			void finalizeResource(RegistryDataNode *this_) {
				RegistryDataNode *scan;
				for (scan = this_; scan; scan = scan->next) {
					if (scan->resourceThis) {
						if (scan->finalizeResource) {
							(*scan->finalizeResource)(scan->resourceThis);
						};
					};
				};
			};

			void deleteResource(RegistryDataNode *this_) {
				RegistryDataNode *scan;
				for (scan = this_; scan; scan = scan->next) {
					if (scan->resourceThis) {
						if (scan->deleteResource) {
							(*scan->deleteResource)(scan->resourceThis);
						};
					};
				};
			};

		};
	};
};
