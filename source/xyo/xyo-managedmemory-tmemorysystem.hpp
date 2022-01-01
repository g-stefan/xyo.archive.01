//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#define XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP

#ifndef XYO_MANAGEDMEMORY_DELETEMEMORY_HPP
#include "xyo-managedmemory-deletememory.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_FINALIZEMEMORY_HPP
#include "xyo-managedmemory-finalizememory.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_REGISTRY_HPP
#include "xyo-managedmemory-registry.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASINITMEMORY_HPP
#include "xyo-managedmemory-tifhasinitmemory.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASINCREFRENCECOUNT_HPP
#include "xyo-managedmemory-tifhasincreferencecount.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASDECREFRENCECOUNT_HPP
#include "xyo-managedmemory-tifhasdecreferencecount.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASSETDELETEMEMORY_HPP
#include "xyo-managedmemory-tifhassetdeletememory.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASPOINTERLINK_HPP
#include "xyo-managedmemory-tifhaspointerlink.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASACTIVECONSTRUCTOR_HPP
#include "xyo-managedmemory-tifhasactiveconstructor.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASACTIVEDESTRUCTOR_HPP
#include "xyo-managedmemory-tifhasactivedestructor.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TIFHASACTIVEFINALIZER_HPP
#include "xyo-managedmemory-tifhasactivefinalizer.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_OBJECT_HPP
#include "xyo-managedmemory-object.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TPOINTER_HPP
#include "xyo-managedmemory-tpointer.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TPOINTERX_HPP
#include "xyo-managedmemory-tpointerx.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		class TMemorySystem {
			protected:

				static inline void deleteMemory_(T *this_) {
					TIfHasActiveDestructor<T>::activeDestructor(this_);
					TIfHasActiveFinalizer<T>::activeFinalizer(this_);
					delete this_;
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
					T *this_ = new T(std::forward<Args>(args)...);
					TIfHasSetDeleteMemory<T>::setDeleteMemory(this_, (DeleteMemory)deleteMemory_, this_);
					TIfHasActiveConstructor<T>::activeConstructor(this_);
					return this_;
				};

				static inline void deleteMemory(T *this_) {
					TDeleteMemory<T, THasDecReferenceCount<T>::value>::deleteMemory(this_);
				};

				static inline void initMemory() {
					Registry::registryInit();
					TIfHasInitMemory<T>::initMemory();
				};
		};

	};
};

#endif

