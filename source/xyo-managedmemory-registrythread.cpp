//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

#ifdef XYO_MULTI_THREAD

#include "xyo-managedmemory-registrydata.hpp"
#include "xyo-managedmemory-registrykey.hpp"
#include "xyo-managedmemory-registry.hpp"
#include "xyo-managedmemory-registrythread.hpp"

namespace XYO {
	namespace ManagedMemory {
		namespace RegistryThread {

			struct RegistryThreadData {
				RegistryDataNode *data[4];
			};

			typedef RegistryDataList List;

			static XYO_THREAD_LOCAL size_t fastTrackSize = 0;
			static XYO_THREAD_LOCAL RegistryThreadData *thisThread = nullptr;
			static XYO_THREAD_LOCAL void **fastTrack = nullptr;

			static void resizeFastTrack(size_t newSize) {

				if(newSize < fastTrackSize) {
					return;
				};

				size_t oldSize;
				void **fastTrackOld_;
				void **fastTrackNew_;

				oldSize = fastTrackSize;

				fastTrackSize = ((newSize / 8) + 1) * 8;

				fastTrackOld_ = fastTrack;

				fastTrackNew_ = new void *[fastTrackSize];
				memset(fastTrackNew_, 0, sizeof(void *)*fastTrackSize);
				memcpy(fastTrackNew_, fastTrack, sizeof(void *)*oldSize);
				fastTrack = fastTrackNew_;

				delete[] fastTrackOld_;
			};

			void processBegin() {

				fastTrackSize = 0;
				thisThread = nullptr;
				fastTrack = nullptr;

				threadBegin();
			};

			void processEnd() {
				threadEnd();
			};

			void threadBegin() {

				RegistryThreadData *this_ = new RegistryThreadData();

				List::constructor(this_->data[RegistryLevel::Singleton]);
				List::constructor(this_->data[RegistryLevel::Active]);
				List::constructor(this_->data[RegistryLevel::Static]);
				List::constructor(this_->data[RegistryLevel::System]);

				thisThread = this_;

				fastTrackSize = 8;
				fastTrack = new void *[fastTrackSize];
				memset(fastTrack, 0, sizeof(void *)*fastTrackSize);

			};

			void threadEnd() {

				RegistryThreadData *this_ = thisThread;

				RegistryData::finalizeResource(this_->data[RegistryLevel::Singleton]);
				RegistryData::finalizeResource(this_->data[RegistryLevel::Active]);
				RegistryData::finalizeResource(this_->data[RegistryLevel::Static]);
				RegistryData::finalizeResource(this_->data[RegistryLevel::System]);

				RegistryData::deleteResource(this_->data[RegistryLevel::Singleton]);
				RegistryData::deleteResource(this_->data[RegistryLevel::Active]);
				RegistryData::deleteResource(this_->data[RegistryLevel::Static]);
				RegistryData::deleteResource(this_->data[RegistryLevel::System]);

				List::destructor(this_->data[RegistryLevel::Singleton]);
				List::destructor(this_->data[RegistryLevel::Active]);
				List::destructor(this_->data[RegistryLevel::Static]);
				List::destructor(this_->data[RegistryLevel::System]);

				delete this_;

				thisThread = nullptr;

				delete[] fastTrack;
				fastTrack = nullptr;

				fastTrackSize = 0;
			};

			bool registerKey(const char *registryKey, size_t &registryLink) {
				Registry::registryInit();

				RegistryKeyNode *node;

				RegistryKey::checkAndRegisterKey(registryKey, node);

				registryLink = node->threadValue;
				if(fastTrackSize <= registryLink) {
					resizeFastTrack(registryLink);
				};

				if(fastTrack[registryLink] == nullptr) {
					// some value for recursive call protection, require setValue
					fastTrack[registryLink] = node;
					return true;
				};
				return false;
			};

			void setValue(size_t registryLink, size_t categoryLevel, void *resourceThis, DeleteMemory deleteResource, FinalizeMemory finalizeResource) {

				if(fastTrackSize <= registryLink) {
					resizeFastTrack(registryLink);
				};

				RegistryDataNode *node = List::newNode();
				List::push(thisThread->data[categoryLevel], node);
				node->resourceThis = resourceThis;
				node->deleteResource = deleteResource;
				node->finalizeResource = finalizeResource;
				fastTrack[registryLink] = resourceThis;
			};

			void *getValue(size_t registryLink) {

				if(fastTrackSize <= registryLink) {
					// Global initialization guard, registryLink == 0  , fastTrackSize == 0 , force initMemory
					if(registryLink == 0) {
						return nullptr;
					};
					resizeFastTrack(registryLink);
				};

				return fastTrack[registryLink];
			};

			size_t getKey(const char *registryKey) {

				RegistryKeyNode *node = RegistryKey::getKey(registryKey);
				if(node) {
					return node->threadValue;
				};

				return 0;
			};


		};
	};
};

#endif
