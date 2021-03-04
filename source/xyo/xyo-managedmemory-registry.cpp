//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-managedmemory-registry.hpp"
#include "xyo-managedmemory-registryprocess.hpp"

namespace XYO {
	namespace ManagedMemory {
		namespace Registry {

			class RegistryInit {
				public:
					RegistryInit();
					~RegistryInit();
			};

			RegistryInit::RegistryInit() {
				RegistryProcess::processBegin();
			};

			RegistryInit::~RegistryInit() {
				RegistryProcess::processEnd();
			};

			void *registryInit() {
				static bool registryInitIsRecursive=false;
				if(registryInitIsRecursive) {
					return nullptr;
				};
				registryInitIsRecursive=true;
				static RegistryInit registryInitInstance;
				registryInitIsRecursive=false;
				return &registryInitInstance;
			};

		};
	};
};

