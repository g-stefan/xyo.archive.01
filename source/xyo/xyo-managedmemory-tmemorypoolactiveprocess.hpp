//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVEPROCESS_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVEPROCESS_HPP

#ifdef XYO_TMEMORYPOOL_SYSTEM

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#include "xyo-managedmemory-tmemorysystem.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		struct TMemoryPoolActiveProcess : TMemorySystem<T> {};

	};
};

#elif defined(XYO_TMEMORYPOOL_ACTIVE_AS_UNIFIED)

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDPROCESS_HPP
#include "xyo-managedmemory-tmemorypoolunifiedprocess.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		struct TMemoryPoolActiveProcess: TMemoryPoolUnifiedProcess<T> {};

	};
};

#else

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDPROCESS_HPP
#include "xyo-managedmemory-tmemorypoolunifiedprocess.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TXLIST1_HPP
#include "xyo-datastructures-txlist1.hpp"
#endif

#ifdef XYO_MULTI_THREAD
#       ifndef XYO_MULTITHREADING_CRITICALSECTION_HPP
#       include "xyo-multithreading-criticalsection.hpp"
#       endif
#endif

#ifndef XYO_MULTITHREADING_TATOMIC_HPP
#include "xyo-multithreading-tatomic.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {
		using namespace XYO::DataStructures;
		using namespace XYO::Multithreading;

		template<typename T>
		class TMemoryPoolActiveProcessImplement {
			protected:
#ifdef XYO_MULTI_THREAD
				CriticalSection criticalSection;
#endif
			public:

				enum {
					NewElementCount = 8,
					FreeElementCountThreshold = 24,
					FreeElementCount = 16
				};

				struct Link {
					Link *next;

					uint8_t value[sizeof(T)];
#ifdef XYO_TMEMORYPOOL_CHECK
					bool isDeleted;
#endif

				};


#ifdef XYO_TMEMORYPOOL_ACTIVE_LEVEL_IS_SYSTEM
				typedef TXList1<Link, TMemorySystem> ListLink;
#else
				typedef TXList1<Link, TMemoryPoolUnifiedProcess> ListLink;
#endif
				Link *poolFreeLink;
				size_t poolFreeLinkCount;
#ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
				size_t checkCount;
#endif


				inline TMemoryPoolActiveProcessImplement() {
					ListLink::constructor(poolFreeLink);
					poolFreeLinkCount = 0;
#ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
					checkCount = 0;
#endif
#ifdef XYO_TMEMORYPOOL_CONSTRUCTOR_INFO
					printf("# Constructor  %s - " XYO_FORMAT_SIZET "\n", registryKey(), sizeof(T));
#endif
				};

				inline ~TMemoryPoolActiveProcessImplement() {
#ifdef XYO_TMEMORYPOOL_DESTRUCTOR_INFO
					printf("# Destructor %s - " XYO_FORMAT_SIZET "\n", registryKey(), sizeof(T));
#endif

#ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
					if(checkCount != 0) {
						printf("# Check Count Info: " XYO_FORMAT_SIZET " - %s\n", checkCount, registryKey());
						fflush(stdout);
					};
#endif

					Link *this_;
					while (poolFreeLink) {
						this_ = poolFreeLink;
						poolFreeLink = poolFreeLink->next;
						TIfHasActiveFinalizer<T>::activeFinalizer(reinterpret_cast<T *>(&this_->value[0]));
						TIfHasSetDeleteMemory<T>::setDeleteMemory(reinterpret_cast<T *>(&this_->value[0]), nullptr, nullptr);
						(reinterpret_cast<T *>(&this_->value[0]))->~T();
						ListLink::deleteNode(this_);
					};
				};

				inline void grow() {
					size_t k;
					Link *this_;
					for (k = 0; k < NewElementCount; ++k) {
						this_ = ListLink::newNode();
						new(&this_->value[0]) T();
#ifdef XYO_TMEMORYPOOL_CHECK
						this_->isDeleted = true;
#endif
						++poolFreeLinkCount;
						ListLink::push(poolFreeLink, this_);
						TIfHasSetDeleteMemory<T>::setDeleteMemory(reinterpret_cast<T *>(&this_->value[0]), (DeleteMemory)deleteMemory_, reinterpret_cast<T *>(&this_->value[0]));
					};
				};

				inline T *newMemory() {
					T *this_;
#ifdef XYO_MULTI_THREAD
					criticalSection.enter();
#endif
					if(!poolFreeLink) {
						grow();
					};
					this_ = reinterpret_cast<T *>(&poolFreeLink->value[0]);
#ifdef XYO_TMEMORYPOOL_CHECK
					poolFreeLink->isDeleted = false;
#endif
					--poolFreeLinkCount;
					ListLink::popUnsafeX(poolFreeLink);

#ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
					checkCount++;
#endif

#ifdef XYO_MULTI_THREAD
					criticalSection.leave();
#endif
					TIfHasActiveConstructor<T>::activeConstructor(this_);
					return this_;
				};

				static inline const std::string deleteMemoryOnAlreadyDeletedObject_() {
					std::string retV("deleteMemory on already deleted object ");
					retV += registryKey();
					return  retV;
				};

				inline void deleteMemory(T *this_) {
#ifdef XYO_TMEMORYPOOL_CHECK
					if((reinterpret_cast<Link *>( (reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value) ))->isDeleted) {
#ifdef XYO_TMEMORYPOOL_CHECK_INFO
						printf("# Double deleteMemory: %p - %s", this_, registryKey());
						fflush(stdout);
#endif
						throw std::runtime_error(deleteMemoryOnAlreadyDeletedObject_());
					};
					(reinterpret_cast<Link *>( (reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value) ))->isDeleted = true;
#endif
#ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
					checkCount--;
#endif

					TIfHasActiveDestructor<T>::activeDestructor(this_);

					Link *itemListToFree = nullptr;

#ifdef XYO_MULTI_THREAD
					criticalSection.enter();
#endif
					this_ = reinterpret_cast<T *>( (reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value) );
					ListLink::push(poolFreeLink, (reinterpret_cast<Link *>(this_)));
					++poolFreeLinkCount;

					if(poolFreeLinkCount == FreeElementCountThreshold) {
						Link *item;
						size_t k;
						for(k = 0; k < FreeElementCount; ++k) {
							if(poolFreeLink) {
								--poolFreeLinkCount;
								item = poolFreeLink;
								ListLink::popUnsafeX(poolFreeLink);
								ListLink::push(itemListToFree, item);
								continue;
							};
							poolFreeLinkCount = 0;
							break;
						};
					};


#ifdef XYO_MULTI_THREAD
					criticalSection.leave();
#endif

					if(itemListToFree != nullptr) {
						Link *this_;
						while (itemListToFree) {
							this_ = itemListToFree;
							itemListToFree = itemListToFree->next;
							TIfHasActiveFinalizer<T>::activeFinalizer(reinterpret_cast<T *>(&this_->value[0]));
							TIfHasSetDeleteMemory<T>::setDeleteMemory(reinterpret_cast<T *>(&this_->value[0]), nullptr, nullptr);
							(reinterpret_cast<T *>(&this_->value[0]))->~T();
							ListLink::deleteNode(this_);
						};
					};

				};

				static inline void initMemory() {
					ListLink::initMemory();
				};

				static inline const std::string deleteMemoryWithoutInitialization_() {
					std::string retV("deleteMemory without initialization ");
					retV += TMemoryPoolActiveProcessImplement<T>::registryKey();
					return  retV;
				};

				static inline void deleteMemory_(T *this_) {

					//
					// dynamic link guard, can be multiple instances in different libraries
					// this will recover the original instance
					//
					if(!memoryPool.get()) {
						memoryPool.set(reinterpret_cast<TMemoryPoolActiveProcessImplement<T> *>(
								RegistryProcess::getKey(TMemoryPoolActiveProcessImplement<T>::registryKey())
							));
						if(!memoryPool.get()) {
							throw std::runtime_error(deleteMemoryWithoutInitialization_());
						};
					};
					//
					//
					//

					(memoryPool.get())->deleteMemory(this_);
				};

				static TAtomic<TMemoryPoolActiveProcessImplement *> memoryPool;
				static const char *registryKey();
				static void resourceDelete(void *);
				static void resourceFinalizer(void *);
		};

		template<typename T>
		const char   *TMemoryPoolActiveProcessImplement<T>::registryKey() {
			return typeid(TMemoryPoolActiveProcessImplement<T>).name();
		};

		template<typename T>
		TAtomic<TMemoryPoolActiveProcessImplement<T> *> TMemoryPoolActiveProcessImplement<T>::memoryPool(nullptr);

		template<typename T>
		void TMemoryPoolActiveProcessImplement<T>::resourceDelete(void *this_) {
			delete (TMemoryPoolActiveProcessImplement<T> *)this_;
		};

		template<typename T>
		void TMemoryPoolActiveProcessImplement<T>::resourceFinalizer(void *this_) {
			TMemoryPoolActiveProcessImplement<T>::Link *scan = ((TMemoryPoolActiveProcessImplement<T> *)this_)->poolFreeLink;
			while (scan) {
				TIfHasActiveFinalizer<T>::activeFinalizer(reinterpret_cast<T *>(&scan->value[0]));
				scan = scan->next;
			};
		};

		template<typename T>
		class TMemoryPoolActiveProcess {
			protected:

				template<typename U, bool hasDecReferenceCount>
				struct TDeleteMemory {

					static inline void deleteMemory(U *this_) {
						TMemoryPoolActiveProcessImplement<T>::deleteMemory_(this_);
					};

				};

				template<typename U>
				struct TDeleteMemory<U, true> {

					static inline void deleteMemory(U *this_) {
						this_->decReferenceCount();
					};

				};

			public:

				static inline T *newMemory() {
					if(!TMemoryPoolActiveProcessImplement<T>::memoryPool.get()) {
						initMemory();
					};
					return (TMemoryPoolActiveProcessImplement<T>::memoryPool.get())->newMemory();
				};

				static inline void deleteMemory(T *this_) {
					TDeleteMemory<T, THasDecReferenceCount<T>::value>::deleteMemory(this_);
				};

				static inline void initMemory() {
					Registry::registryInit();
					TMemoryPoolActiveProcessImplement<T>::initMemory();
					void *registryLink;

					//
					if(RegistryProcess::checkAndRegisterKey(TMemoryPoolActiveProcessImplement<T>::registryKey(), registryLink, [] {
					return (TMemoryPoolActiveProcessImplement<T>::memoryPool.get() == nullptr);
					}
					, [](void *this__) {
						TMemoryPoolActiveProcessImplement<T>
						*this_ = reinterpret_cast<TMemoryPoolActiveProcessImplement<T> *>(this__);
						TMemoryPoolActiveProcessImplement<T>::memoryPool.set(this_);
					})) {
						TIfHasInitMemory<T>::initMemory();

						TMemoryPoolActiveProcessImplement<T>::memoryPool.set(new TMemoryPoolActiveProcessImplement<T>());

						RegistryProcess::setValue(
							registryLink,
							RegistryLevel::Active,
							TMemoryPoolActiveProcessImplement<T>::memoryPool.get(),
							TMemoryPoolActiveProcessImplement<T>::resourceDelete,
							(THasActiveFinalizer<T>::value) ? TMemoryPoolActiveProcessImplement<T>::resourceFinalizer : nullptr
						);
					};
				};

		};

	};
};
#endif

#endif
