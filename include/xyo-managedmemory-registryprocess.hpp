//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_REGISTRYPROCESS_HPP
#define XYO_MANAGEDMEMORY_REGISTRYPROCESS_HPP

#ifndef XYO_MANAGEDMEMORY_REGISTRYLEVEL_HPP
#include "xyo-managedmemory-registrylevel.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#include "xyo-managedmemory-tmemorysystem.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {
		namespace RegistryProcess {

			XYO_EXPORT void processBegin();
			XYO_EXPORT void processEnd();
			XYO_EXPORT bool checkAndRegisterKey(const char *registryKey, void *&registryLink, const std::function<bool()> &valueIsNullptr, const std::function<void(void *)> &setValue);
			XYO_EXPORT void setValue(void *registryLink, size_t categoryLevel, void *resourceThis, DeleteMemory deleteResource, FinalizeMemory finalizerResource);
			XYO_EXPORT void *getValue(void *registryLink);
			XYO_EXPORT void *getKey(const char *registryKey);

		};
	};
};

#endif
