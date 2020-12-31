//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDTHREAD_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDTHREAD_HPP

#if defined(XYO_TMEMORYPOOL_SYSTEM) | defined(XYO_TMEMORYPOOL_UNIFIED_AS_SYSTEM)

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#include "xyo-managedmemory-tmemorysystem.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		struct TMemoryPoolUnifiedThread : TMemorySystem<T> {};

	};
};

#else

#ifdef XYO_SINGLE_THREAD

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDPROCESS_HPP
#include "xyo-managedmemory-tmemorypoolunifiedprocess.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		struct TMemoryPoolUnifiedThread : TMemoryPoolUnifiedProcess<T> {};

	};
};

#else

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#include "xyo-managedmemory-tmemorysystem.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_REGISTRYTHREAD_HPP
#include "xyo-managedmemory-registrythread.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TXLIST1_HPP
#include "xyo-datastructures-txlist1.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {
		using namespace XYO::DataStructures;

		template<size_t sizeOfT>
		class TMemoryPoolUnifiedThreadImplement {
			public:

				enum {
					NewElementCount = 8,
					FreeElementCountThreshold = 24,
					FreeElementCount = 16
				};

				struct Link : TXList1Node<Link> {

					uint8_t value[sizeOfT];
#ifdef XYO_TMEMORYPOOL_CHECK
					bool isDeleted;
#endif

				};

				typedef TXList1<Link, TMemorySystem> ListLink;

				Link *rootFreeLink;
				size_t rootFreeLinkCount;

#ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
				size_t checkCount;
#endif

				inline TMemoryPoolUnifiedThreadImplement() {
					ListLink::constructor(rootFreeLink);
					rootFreeLinkCount = 0;
#ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
					checkCount = 0;
#endif
#ifdef XYO_TMEMORYPOOL_CONSTRUCTOR_INFO
					printf("# Constructor  %s\n", registryKey());
#endif
				};

				inline ~TMemoryPoolUnifiedThreadImplement() {
#ifdef XYO_TMEMORYPOOL_DESTRUCTOR_INFO
					printf("# Destructor %s\n", registryKey());
#endif

#ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
					if(checkCount != 0) {
						printf("# Check Count Info: " XYO_FORMAT_SIZET " - %s\n", checkCount, registryKey());
						fflush(stdout);
					};
#endif
					ListLink::destructor(rootFreeLink);
				};

				inline void grow() {
					size_t k;
					Link *newItem;
					for (k = 0; k < NewElementCount; ++k) {
						newItem = ListLink::newNode();
#ifdef XYO_TMEMORYPOOL_CHECK
						newItem->isDeleted = true;
#endif
						++rootFreeLinkCount;
						ListLink::push(rootFreeLink, newItem);
					};
				};

				inline void *newMemory() {
					void *this_;
					if(!rootFreeLink) {
						grow();
					};
					this_ = (void *)(rootFreeLink->value);
#ifdef XYO_TMEMORYPOOL_CHECK
					rootFreeLink->isDeleted = false;
#endif
#ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
					checkCount++;
#endif
					--rootFreeLinkCount;
					ListLink::popUnsafeX(rootFreeLink);
					return this_;
				};

				static inline const std::string deleteMemoryOnAlreadyDeletedObject_() {
					std::string retV("deleteMemory on already deleted object ");
					retV += registryKey();
					return  retV;
				};

				inline void deleteMemory(void *this_) {
#ifdef XYO_TMEMORYPOOL_CHECK
					if((reinterpret_cast<Link *>( (reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value) ))->isDeleted) {
#ifdef XYO_TMEMORYPOOL_CHECK_INFO
						printf("# Double deleteMemory: %p - %s\n", this_, registryKey());
						fflush(stdout);
#endif
						throw std::runtime_error(deleteMemoryOnAlreadyDeletedObject_());
					};
					(reinterpret_cast<Link *>( (reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value) ))->isDeleted = true;
#endif
#ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
					checkCount--;
#endif

					++rootFreeLinkCount;
					this_ = (void *)( (reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value) );
					ListLink::push(rootFreeLink, reinterpret_cast<Link *>(this_));

					Link *itemListToFree = nullptr;
					if(rootFreeLinkCount == FreeElementCountThreshold) {
						Link *item;
						size_t k;
						for(k = 0; k < FreeElementCount; ++k) {
							if(rootFreeLink) {
								--rootFreeLinkCount;
								item = rootFreeLink;
								ListLink::popUnsafeX(rootFreeLink);
								ListLink::push(itemListToFree, item);
								continue;
							};
							rootFreeLinkCount = 0;
							break;
						};
					};


					if(itemListToFree) {
						ListLink::destructor(itemListToFree);
					};
				};

				static size_t registryLink;
				static const char *registryKey();
				static void resourceDelete(void *);
		};

		template<size_t sizeOfT>
		const char   *TMemoryPoolUnifiedThreadImplement<sizeOfT>::registryKey() {
			return typeid(TMemoryPoolUnifiedThreadImplement<sizeOfT>).name();
		};

		template<size_t sizeOfT>
		size_t TMemoryPoolUnifiedThreadImplement<sizeOfT>::registryLink = 0;

		template<size_t sizeOfT>
		void TMemoryPoolUnifiedThreadImplement<sizeOfT>::resourceDelete(void *this_) {
			delete (TMemoryPoolUnifiedThreadImplement<sizeOfT> *)this_;
		};

		//

		template<typename T>
		class TMemoryPoolUnifiedThreadRecursiveGuard {
			public:
				static size_t registryLink;
				static const char *registryKey();
				static void resourceDelete(void *);
		};

		template<typename T>
		const char   *TMemoryPoolUnifiedThreadRecursiveGuard<T>::registryKey() {
			return typeid(TMemoryPoolUnifiedThreadRecursiveGuard<T>).name();
		};

		template<typename T>
		size_t TMemoryPoolUnifiedThreadRecursiveGuard<T>::registryLink = 0;

		template<typename T>
		void TMemoryPoolUnifiedThreadRecursiveGuard<T>::resourceDelete(void *this_) {
			delete (TMemoryPoolUnifiedThreadRecursiveGuard<T> *)this_;
		};

		//

		template<typename T, bool hasInitMemory>
		struct TIfHasInitMemoryRecursiveGuardThreadBase {
			static inline void initMemory() {
			};
		};

		template<typename T>
		struct TIfHasInitMemoryRecursiveGuardThreadBase<T, true > {
			static inline void initMemory() {

				if(RegistryThread::registerKey(
						TMemoryPoolUnifiedThreadRecursiveGuard<T>::registryKey(),
						TMemoryPoolUnifiedThreadRecursiveGuard<T>::registryLink)) {

					TIfHasInitMemory<T>::initMemory();

					RegistryThread::setValue(
						TMemoryPoolUnifiedThreadRecursiveGuard<T>::registryLink,
						RegistryLevel::Static,
						new TMemoryPoolUnifiedThreadRecursiveGuard<T>(),
						TMemoryPoolUnifiedThreadRecursiveGuard<T>::resourceDelete,
						nullptr
					);
				};
			};
		};

		template<typename T>
		struct TIfHasInitMemoryRecursiveGuardThread : TIfHasInitMemoryRecursiveGuardThreadBase<T, THasInitMemory<T>::value> {
		};

		//

		template<typename T>
		class TMemoryPoolUnifiedThread {
			protected:

				static inline const std::string deleteMemoryWithoutInitialization_() {
					std::string retV("deleteMemory without initialization ");
					retV += TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryKey();
					return  retV;
				};

				static inline void deleteMemory_(T *this_) {
					TIfHasActiveDestructor<T>::activeDestructor(this_);
					TIfHasActiveFinalizer<T>::activeFinalizer(this_);
					TIfHasSetDeleteMemory<T>::setDeleteMemory(this_, nullptr, nullptr);
					this_->~T();

					//
					// dynamic link guard, can be multiple instances in different libraries
					// this will recover the original instance
					//
					if(!TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink) {
						TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink = RegistryThread::getKey(TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryKey());
						if(!TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink) {
							throw std::runtime_error(deleteMemoryWithoutInitialization_());
						};
					};
					//
					//
					//

					(
						(TMemoryPoolUnifiedThreadImplement<sizeof(T)> *)
						RegistryThread::getValue(TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink)
					)->deleteMemory(this_);
				};

				template<typename U, bool hasDecReferenceCount>
				struct TDeleteMemory {

					static inline void deleteMemory(U *this_) {
						deleteMemory_(this_);
					};

				};

				template<typename U>
				struct TDeleteMemory<U, true> {

					static inline void deleteMemory(U *this_) {
						this_->decReferenceCount();
					};

				};

			public:

				template<typename... Args>
				static inline T *newMemory(Args &&... args) {
					T *this_ = reinterpret_cast<T *>(RegistryThread::getValue(TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink));
					if(!this_) {
						initMemory();
						this_ = reinterpret_cast<T *>(RegistryThread::getValue(TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink));
					};
					this_ = new((reinterpret_cast<TMemoryPoolUnifiedThreadImplement<sizeof(T)> *>(this_))->newMemory()) T(std::forward<Args>(args)...);
					TIfHasSetDeleteMemory<T>::setDeleteMemory(this_, (DeleteMemory)deleteMemory_, this_);
					TIfHasActiveConstructor<T>::activeConstructor(this_);
					return this_;
				};

				static inline void deleteMemory(T *this_) {
					TDeleteMemory<T, THasDecReferenceCount<T>::value>::deleteMemory(this_);
				};

				static inline void initMemory() {
					Registry::registryInit();
					if(RegistryThread::registerKey(
							TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryKey(),
							TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink)) {

						TIfHasInitMemory<T>::initMemory();

						RegistryThread::setValue(
							TMemoryPoolUnifiedThreadImplement<sizeof(T)>::registryLink,
							RegistryLevel::Static,
							new TMemoryPoolUnifiedThreadImplement<sizeof(T)>(),
							TMemoryPoolUnifiedThreadImplement<sizeof(T)>::resourceDelete,
							nullptr
						);
					} else {
						TIfHasInitMemoryRecursiveGuardThread<T>::initMemory();
					};
				};
		};

	};
};

#endif

#endif

#endif

