//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-multithreading-thread.hpp"
#include "xyo-managedmemory-registrydata.hpp"
#include "xyo-managedmemory-registrykey.hpp"
#include "xyo-managedmemory-registry.hpp"
#include "xyo-managedmemory-registrythread.hpp"
#include "xyo-managedmemory-registryprocess.hpp"

namespace XYO {
	namespace ManagedMemory {
		namespace RegistryProcess {
			using namespace XYO::Multithreading;

			typedef RegistryDataList List;

			static RegistryDataNode *data[4];

			void processBegin() {

				RegistryKey::processBegin();

				data[RegistryLevel::Singleton] = nullptr;
				data[RegistryLevel::Active] = nullptr;
				data[RegistryLevel::Static] = nullptr;
				data[RegistryLevel::System] = nullptr;

#ifdef XYO_MULTI_THREAD
				RegistryThread::processBegin();
#endif
			};

			void processEnd() {

#ifdef XYO_MULTI_THREAD
				RegistryThread::processEnd();
#endif
				RegistryData::finalizeResource(data[RegistryLevel::Singleton]);
				RegistryData::finalizeResource(data[RegistryLevel::Active]);
				RegistryData::finalizeResource(data[RegistryLevel::Static]);
				RegistryData::finalizeResource(data[RegistryLevel::System]);

				RegistryData::deleteResource(data[RegistryLevel::Singleton]);
				RegistryData::deleteResource(data[RegistryLevel::Active]);
				RegistryData::deleteResource(data[RegistryLevel::Static]);
				RegistryData::deleteResource(data[RegistryLevel::System]);

				List::empty(data[RegistryLevel::Singleton]);
				List::empty(data[RegistryLevel::Active]);
				List::empty(data[RegistryLevel::Static]);
				List::empty(data[RegistryLevel::System]);

				RegistryKey::processEnd();

			};

			bool checkAndRegisterKey(const char *registryKey, void *&registryLink, const std::function<bool()> &valueIsNullptr, const std::function<void(void *)> &setValue) {
				Registry::registryInit();

				if(RegistryKey::checkAndRegisterKey(registryKey, reinterpret_cast<RegistryKeyNode *&>(registryLink))) {
					return true;
				};

				setValue(reinterpret_cast<RegistryKeyNode *&>(registryLink)->processValue.get());

#ifdef XYO_MULTI_THREAD

				while(valueIsNullptr()) {
					Thread::sleep(1);
					setValue(reinterpret_cast<RegistryKeyNode *&>(registryLink)->processValue.get());
				};
#endif

				return false;
			};

			void setValue(void *registryLink, size_t categoryLevel, void *resourceThis, DeleteMemory deleteResource, FinalizeMemory finalizeResource) {
				RegistryDataNode *node = List::newNode();
				List::push(data[categoryLevel], node);
				node->resourceThis = resourceThis;
				node->deleteResource = deleteResource;
				node->finalizeResource = finalizeResource;
				(reinterpret_cast<RegistryKeyNode *>(registryLink))->processValue.set(resourceThis);
			};

			void *getValue(void *registryLink) {
				return (reinterpret_cast<RegistryKeyNode *>(registryLink))->processValue.get();
			};

			void *getKey(const char *registryKey) {
				RegistryKeyNode *node = RegistryKey::getKey(registryKey);
				if(node) {
					return node->processValue;
				};
				return nullptr;
			};

		};
	};
};


