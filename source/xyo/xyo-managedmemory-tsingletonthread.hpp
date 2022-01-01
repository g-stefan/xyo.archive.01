//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TSINGLETONTHREAD_HPP
#define XYO_MANAGEDMEMORY_TSINGLETONTHREAD_HPP

#ifdef XYO_SINGLE_THREAD

#ifndef XYO_MANAGEDMEMORY_TSINGLETONPROCESS_HPP
#include "xyo-mangedmemory-tsingletonprocess.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		struct TSingletonThread : TSingletonProcess<T> {};

	};
};

#else

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#include "xyo-managedmemory-tmemorysystem.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_REGISTRYTHREAD_HPP
#include "xyo-managedmemory-registrythread.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		class TSingletonThread {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(TSingletonThread);

			protected:

				inline TSingletonThread() {
				};

			public:

				static size_t registryLink;
				static const char *registryKey();
				static void resourceDelete(void *);
				static void resourceFinalizer(void *);

				static inline T *getValue() {
					T *this_ = (T *)RegistryThread::getValue(registryLink);
					if(!this_) {
						initMemory();
						this_ = (T *)RegistryThread::getValue(registryLink);
					};
					return this_;
				};

				static inline void initMemory() {

					if(RegistryThread::registerKey(
							registryKey(),
							registryLink)) {

						TMemorySystem<T>::initMemory();

						T *this_ = TMemorySystem<T>::newMemory();
						TIfHasIncReferenceCount<T>::incReferenceCount(this_);

						RegistryThread::setValue(
							registryLink,
							RegistryLevel::Singleton,
							this_,
							resourceDelete,
							(THasActiveFinalizer<T>::value) ? resourceFinalizer : nullptr);
					};

				};
		};

		template<typename T>
		const char *TSingletonThread<T>::registryKey() {
			return typeid(TSingletonThread<T>).name();
		};

		template<typename T>
		size_t TSingletonThread<T>::registryLink = 0;

		template<typename T>
		void TSingletonThread<T>::resourceDelete(void *this_) {
			TMemorySystem<T>::deleteMemory(reinterpret_cast<T *>(this_));
		};

		template<typename T>
		void TSingletonThread<T>::resourceFinalizer(void *this_) {
			TIfHasActiveFinalizer<T>::activeFinalizer(reinterpret_cast<T *>(this_));
		};

	};
};

#endif

#endif
