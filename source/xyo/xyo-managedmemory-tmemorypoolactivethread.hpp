//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVETHREAD_HPP
#define XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVETHREAD_HPP

#ifdef XYO_TMEMORYPOOL_SYSTEM

#	ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#		include "xyo-managedmemory-tmemorysystem.hpp"
#	endif

namespace XYO {
	namespace ManagedMemory {

		template <typename T>
		struct TMemoryPoolActiveThread : TMemorySystem<T> {};

	};
};

#elif defined(XYO_TMEMORYPOOL_ACTIVE_AS_UNIFIED)

#	ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDTHREAD_HPP
#		include "xyo-managedmemory-tmemorypoolunifiedthread.hpp"
#	endif

namespace XYO {
	namespace ManagedMemory {

		template <typename T>
		struct TMemoryPoolActiveThread : TMemoryPoolUnifiedThread<T> {};

	};
};

#else

#	ifdef XYO_SINGLE_THREAD

#		ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLACTIVEPROCESS_HPP
#			include "xyo-managedmemory-tmemorypoolactiveprocess.hpp"
#		endif

namespace XYO {
	namespace ManagedMemory {

		template <typename T>
		struct TMemoryPoolActiveThread : TMemoryPoolActiveProcess<T> {};

	};
};

#	else

#		ifndef XYO_MANAGEDMEMORY_TMEMORYPOOLUNIFIEDTHREAD_HPP
#			include "xyo-managedmemory-tmemorypoolunifiedthread.hpp"
#		endif

#		ifndef XYO_DATASTRUCTURES_TXLIST1_HPP
#			include "xyo-datastructures-txlist1.hpp"
#		endif

#		ifndef XYO_MANAGEDMEMORY_REGISTRYTHREAD_HPP
#			include "xyo-managedmemory-registrythread.hpp"
#		endif

namespace XYO {
	namespace ManagedMemory {
		using namespace XYO::DataStructures;

		template <typename T>
		class TMemoryPoolActiveThreadImplement {
			public:
				enum {
					NewElementCount = 8,
					FreeElementCountThreshold = 24,
					FreeElementCount = 16
				};

				struct Link {
						Link *next;

						uint8_t value[sizeof(T)];
#		ifdef XYO_TMEMORYPOOL_CHECK
						bool isDeleted;
#		endif
				};

#		ifdef XYO_TMEMORYPOOL_ACTIVE_LEVEL_IS_SYSTEM
				typedef TXList1<Link, TMemorySystem> ListLink;
#		else
				typedef TXList1<Link, TMemoryPoolUnifiedThread> ListLink;
#		endif
				Link *poolFreeLink;
				size_t poolFreeLinkCount;
#		ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
				size_t checkCount;
#		endif

				inline TMemoryPoolActiveThreadImplement() {
					ListLink::constructor(poolFreeLink);
					poolFreeLinkCount = 0;
#		ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
					checkCount = 0;
#		endif
#		ifdef XYO_TMEMORYPOOL_CONSTRUCTOR_INFO
					printf("# Constructor  %s - " XYO_FORMAT_SIZET "\n", registryKey(), sizeof(T));
#		endif
				};

				inline ~TMemoryPoolActiveThreadImplement() {
#		ifdef XYO_TMEMORYPOOL_DESTRUCTOR_INFO
					printf("# Destructor %s - " XYO_FORMAT_SIZET "\n", registryKey(), sizeof(T));
#		endif

#		ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
					if (checkCount != 0) {
						printf("# Check Count Info: " XYO_FORMAT_SIZET " - %s\n", checkCount, registryKey());
						fflush(stdout);
					};
#		endif

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
						new (&this_->value[0]) T();
#		ifdef XYO_TMEMORYPOOL_CHECK
						this_->isDeleted = true;
#		endif
						++poolFreeLinkCount;
						ListLink::push(poolFreeLink, this_);
						TIfHasSetDeleteMemory<T>::setDeleteMemory(reinterpret_cast<T *>(&this_->value[0]), (DeleteMemory)deleteMemory_, reinterpret_cast<T *>(&this_->value[0]));
					};
				};

				inline T *newMemory() {
					T *this_;
					if (!poolFreeLink) {
						grow();
					};
					this_ = reinterpret_cast<T *>(&poolFreeLink->value[0]);
#		ifdef XYO_TMEMORYPOOL_CHECK
					poolFreeLink->isDeleted = false;
#		endif
					--poolFreeLinkCount;
					ListLink::popUnsafeX(poolFreeLink);
#		ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
					checkCount++;
#		endif

					TIfHasActiveConstructor<T>::activeConstructor(this_);
#		ifdef XYO_TMEMORYPOOL_NEW_MEMORY_INFO
					printf("# newMemory %p - %s\n", this_, registryKey());
#		endif
					return this_;
				};

				static inline const std::string deleteMemoryOnAlreadyDeletedObject_() {
					std::string retV("deleteMemory on already deleted object ");
					retV += registryKey();
					return retV;
				};

				inline void deleteMemory(T *this_) {
#		ifdef XYO_TMEMORYPOOL_DELETE_MEMORY_INFO
					printf("# deleteMemory %p - %s\n", this_, registryKey());
#		endif

#		ifdef XYO_TMEMORYPOOL_CHECK
					if ((reinterpret_cast<Link *>((reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value)))->isDeleted) {
#			ifdef XYO_TMEMORYPOOL_CHECK_INFO
						printf("# Double deleteMemory: %p - %s", this_, registryKey());
						fflush(stdout);
#			endif
						throw std::runtime_error(deleteMemoryOnAlreadyDeletedObject_());
					};
					(reinterpret_cast<Link *>((reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value)))->isDeleted = true;
#		endif
#		ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
					checkCount--;
#		endif

					TIfHasActiveDestructor<T>::activeDestructor(this_);
					this_ = reinterpret_cast<T *>((reinterpret_cast<uint8_t *>(this_)) - offsetof(Link, value));
					ListLink::push(poolFreeLink, reinterpret_cast<Link *>(this_));
					++poolFreeLinkCount;

					Link *itemListToFree = nullptr;

					if (poolFreeLinkCount == FreeElementCountThreshold) {
						Link *item;
						size_t k;
						for (k = 0; k < FreeElementCount; ++k) {
							if (poolFreeLink) {
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

					if (itemListToFree != nullptr) {
						Link *link_;
						while (itemListToFree) {
							link_ = itemListToFree;
							itemListToFree = itemListToFree->next;
							TIfHasActiveFinalizer<T>::activeFinalizer(reinterpret_cast<T *>(&link_->value[0]));
							TIfHasSetDeleteMemory<T>::setDeleteMemory(reinterpret_cast<T *>(&link_->value[0]), nullptr, nullptr);
							(reinterpret_cast<T *>(&link_->value[0]))->~T();
							ListLink::deleteNode(link_);
						};
					};
				};

				static inline void initMemory() {
					ListLink::initMemory();
				};

				static inline const std::string deleteMemoryWithoutInitialization_() {
					std::string retV("deleteMemory without initialization ");
					retV += registryKey();
					return retV;
				};

				static inline void deleteMemory_(T *this_) {

					//
					// dynamic link guard, can be multiple instances in different libraries
					// this will recover the original instance
					//
					if (!registryLink) {
						registryLink = RegistryThread::getKey(registryKey());
						if (!registryLink) {
							throw std::runtime_error(deleteMemoryWithoutInitialization_());
						};
					};
					//
					//
					//

					(
					    (TMemoryPoolActiveThreadImplement<T> *)
					        RegistryThread::getValue(registryLink))
					    ->deleteMemory(this_);
				};

				static size_t registryLink;
				static const char *registryKey();
				static void resourceDelete(void *);
				static void resourceFinalizer(void *);
		};

		template <typename T>
		const char *TMemoryPoolActiveThreadImplement<T>::registryKey() {
			return typeid(TMemoryPoolActiveThreadImplement<T>).name();
		};

		template <typename T>
		size_t TMemoryPoolActiveThreadImplement<T>::registryLink = 0;

		template <typename T>
		void TMemoryPoolActiveThreadImplement<T>::resourceDelete(void *this_) {
			delete (TMemoryPoolActiveThreadImplement<T> *)this_;
		};

		template <typename T>
		void TMemoryPoolActiveThreadImplement<T>::resourceFinalizer(void *this_) {
			TMemoryPoolActiveThreadImplement<T>::Link *scan = ((TMemoryPoolActiveThreadImplement<T> *)this_)->poolFreeLink;
			while (scan) {
				TIfHasActiveFinalizer<T>::activeFinalizer(reinterpret_cast<T *>(&scan->value[0]));
				scan = scan->next;
			};
		};

		template <typename T>
		class TMemoryPoolActiveThread {
			protected:
				template <typename U, bool hasDecReferenceCount>
				struct TDeleteMemory {

						static inline void deleteMemory(U *this_) {
							TMemoryPoolActiveThreadImplement<T>::deleteMemory_(this_);
						};
				};

				template <typename U>
				struct TDeleteMemory<U, true> {

						static inline void deleteMemory(U *this_) {
							this_->decReferenceCount();
						};
				};

			public:
				static inline T *newMemory() {
					T *this_ = reinterpret_cast<T *>(RegistryThread::getValue(TMemoryPoolActiveThreadImplement<T>::registryLink));
					if (!this_) {
						initMemory();
						this_ = reinterpret_cast<T *>(RegistryThread::getValue(TMemoryPoolActiveThreadImplement<T>::registryLink));
					};
					return (reinterpret_cast<TMemoryPoolActiveThreadImplement<T> *>(this_))->newMemory();
				};

				static inline void deleteMemory(T *this_) {
					TDeleteMemory<T, THasDecReferenceCount<T>::value>::deleteMemory(this_);
				};

				static inline void initMemory() {
					Registry::registryInit();
					TMemoryPoolActiveThreadImplement<T>::initMemory();

					if (RegistryThread::registerKey(
					        TMemoryPoolActiveThreadImplement<T>::registryKey(),
					        TMemoryPoolActiveThreadImplement<T>::registryLink)) {

						TIfHasInitMemory<T>::initMemory();

						RegistryThread::setValue(
						    TMemoryPoolActiveThreadImplement<T>::registryLink,
						    RegistryLevel::Active,
						    new TMemoryPoolActiveThreadImplement<T>(),
						    TMemoryPoolActiveThreadImplement<T>::resourceDelete,
						    (THasActiveFinalizer<T>::value) ? TMemoryPoolActiveThreadImplement<T>::resourceFinalizer : nullptr);
					};
				};
		};

	};
};

#	endif

#endif

#endif
