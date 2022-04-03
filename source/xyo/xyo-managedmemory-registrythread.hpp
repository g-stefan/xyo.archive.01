//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_REGISTRYTHREAD_HPP
#define XYO_MANAGEDMEMORY_REGISTRYTHREAD_HPP

#ifndef XYO_MANAGEDMEMORY_REGISTRYLEVEL_HPP
#	include "xyo-managedmemory-registrylevel.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#	include "xyo-managedmemory-tmemorysystem.hpp"
#endif

#ifdef XYO_MULTI_THREAD
namespace XYO {
	namespace ManagedMemory {
		namespace RegistryThread {

			XYO_EXPORT void processBegin();
			XYO_EXPORT void processEnd();
			XYO_EXPORT void threadBegin();
			XYO_EXPORT void threadEnd();
			XYO_EXPORT bool registerKey(const char *registryKey, size_t &registryLink);
			XYO_EXPORT void setValue(size_t registryLink, size_t categoryLevel, void *resourceThis, DeleteMemory deleteResource, FinalizeMemory finalizeResource);
			XYO_EXPORT void *getValue(size_t registryLink);
			XYO_EXPORT size_t getKey(const char *registryKey);

		};
	};
};
#endif

#endif
