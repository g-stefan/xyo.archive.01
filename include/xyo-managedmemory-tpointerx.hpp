//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TPOINTERX_HPP
#define XYO_MANAGEDMEMORY_TPOINTERX_HPP

#ifndef XYO_MANAGEDMEMORY_POINTERX_HPP
#include "xyo-managedmemory-pointerx.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TPOINTER_HPP
#include "xyo-managedmemory-tpointer.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		//
		// Dynamic link - part of an object
		//
		template<typename T>
		class TPointerX: protected PointerX {
			public:

				TPointerX(const TPointerX &) = delete;
				TPointerX(TPointerX &&) = delete;

				inline TPointerX() {
					link = nullptr;
					object = nullptr;
				};

				inline ~TPointerX() {
					if (object) {
						(reinterpret_cast<T *>(object))->removePointerX(this);
					};
				};

				//

				inline TPointerX &operator=(const T *value) {
					if (object) {
						(reinterpret_cast<T *>(object))->transferPointerX(this, value, value);
						return *this;
					};
					object = const_cast<T *>(value);
					if (object) {
						(reinterpret_cast<T *>(object))->addPointerX(this);
					};
					return *this;
				};

				inline TPointerX &operator=(const TPointerX &value) {
					return operator=((const T *)value);
				};

				inline TPointerX &operator=(TPointerX &&value) {
					return operator=((T *)value);
				};

				inline TPointerX &operator=(const TTransfer<T> *value) {
					if (object) {
						(reinterpret_cast<T *>(object))->transferPointerX(this, (const_cast<TTransfer<T> *>(value))->value(), (const_cast<TTransfer<T> *>(value))->value());
						(*(const_cast<TTransfer<T> *>(value)))->decReferenceCount();
						return *this;
					};
					object = (const_cast<TTransfer<T> *>(value))->value();
					if (object) {
						(reinterpret_cast<T *>(object))->addPointerX(this);
						(reinterpret_cast<T *>(object))->decReferenceCount();
					};
					return *this;
				};

				inline TPointerX &operator=(std::nullptr_t) {
					if (object) {
						(reinterpret_cast<T *>(object))->removePointerX(this);
					};
					return *this;
				};

				//

				inline operator bool() const {
					return (object);
				};

				inline T *operator->() const {
					return (reinterpret_cast<T *>(object));
				};

				inline operator T *() const {
					return (reinterpret_cast<T *>(object));
				};

				inline T *value() const {
					return (reinterpret_cast<T *>(object));
				};

				//

				inline void pointerLink(Object *link_) {
					link = link_;
					if(link != nullptr) {
						link->referenceIsBranch_ = true;
					};
				};

				// Use this if pointer has a parent in executive, set without trigger mark and sweep
				inline void setExecutive(TPointer<T> &&value) {
					operator=((const T *)value);
					value.dropReference();
					(reinterpret_cast<T *>(object))->decReferenceCountExecutive();
				};

				//

				static inline void initMemory() {
					TMemory<T>::initMemory();
				};

				inline void newMemory() {
					operator=(TMemory<T>::newMemory());
				};

				inline void deleteMemory() {
					if (object) {
						(reinterpret_cast<T *>(object))->removePointerX(this);
					};
				};

				inline void activeDestructor() {
					deleteMemory();
				};

		};
	};
};

#ifndef XYO_MANAGEDMEMORY_TPOINTERX_X_TCOMPARATOR_HPP
#include "xyo-managedmemory-tpointerx-x-tcomparator.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TPOINTERTYPE_HPP
#include "xyo-managedmemory-tpointertype.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TPOINTERTYPEEXCLUDE_HPP
#include "xyo-managedmemory-tpointertypeexclude.hpp"
#endif

#endif
