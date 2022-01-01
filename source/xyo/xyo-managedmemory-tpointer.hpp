//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TPOINTER_HPP
#define XYO_MANAGEDMEMORY_TPOINTER_HPP

#ifndef XYO_MANAGEDMEMORY_OBJECT_HPP
#include "xyo-managedmemory-object.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TTRANSFER_HPP
#include "xyo-datastructures-ttransfer.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		struct TMemory;

		template<typename T>
		class TPointerX;

		//
		// Executive link - part of return/function parameter/function variable
		//
		template<typename T>
		class TPointer {
			protected:
				T *object;
			public:

				inline TPointer() {
					object = nullptr;
				};

				inline ~TPointer() {
					if (object) {
						object->decReferenceCount();
					};
				};

				//

				inline TPointer(const T *value) {
					object = const_cast<T *>(value);
					if (object) {
						object->incReferenceCount();
					};
				};

				inline TPointer(const TPointer &value) {
					object = (const_cast<TPointer &>(value)).object;
					if (object) {
						object->incReferenceCount();
					};
				};

				inline TPointer(TPointer &&value) {
					object = value.object;
					value.object = nullptr;
				};

				inline TPointer(const TTransfer<T> *value) {
					object = (const_cast<TTransfer<T> *>(value))->value();
				};

				inline TPointer(std::nullptr_t) {
					object = nullptr;
				};

				inline TPointer(const TPointerX<T> &value) {
					object = (const_cast<TPointerX<T> &>(value));
					if (object) {
						object->incReferenceCount();
					};
				};

				inline TPointer(TPointerX<T> &&value) {
					object = value;
					if (object) {
						object->incReferenceCount();
					};
				};

				//

				inline TPointer &operator=(const T *value) {
					if (value) {
						(const_cast<T *>(value))->incReferenceCount();
					};
					if (object) {
						object->decReferenceCount();
					};
					object = (const_cast<T *>(value));
					return *this;
				};

				inline TPointer &operator=(const TPointer &value) {
					if (object) {
						object->decReferenceCount();
					};
					object = const_cast<TPointer &>(value);
					if (object) {
						object->incReferenceCount();
					};
					return *this;
				};

				inline TPointer &operator=(TPointer &&value) {
					if (object) {
						object->decReferenceCount();
					};
					object = value.object;
					value.object = nullptr;
					return *this;
				};

				inline TPointer &operator=(const TTransfer<T> *value) {
					if (object) {
						object->decReferenceCount();
					};
					object = (const_cast<TTransfer<T> *>(value))->value();
					return *this;
				};

				inline TPointer &operator=(std::nullptr_t) {
					if (object) {
						object->decReferenceCount();
					};
					object = nullptr;
					return *this;
				};

				inline TPointer &operator=(const TPointerX<T> &value) {
					return operator=((const_cast<TPointerX<T> &>(value)).value());
				};

				inline TPointer &operator=(TPointerX<T> &&value) {
					return operator=(value.value());
				};

				//

				inline operator bool() const {
					return (object);
				};

				inline T *operator->() const {
					return object;
				};

				inline operator T *() const {
					return object;
				};

				inline T *value() const {
					return object;
				};

				//

				inline void swap(const TPointer<T> &value) {
					T *tmp = object;
					object = (const_cast<TPointer<T> &>(value)).object;
					(const_cast<TPointer<T> &>(value)).object = tmp;
				};

				inline void dropReference() {
					object = nullptr;
				};

				inline TTransfer<T> *transfer() {
					TTransfer<T> *retV = reinterpret_cast<TTransfer<T> *>(object);
					object = nullptr;
					return retV;
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
						object->decReferenceCount();
					};
					object = nullptr;
				};

				inline void activeDestructor() {
					deleteMemory();
				};

		};

	};
};

#ifndef XYO_MANAGEDMEMORY_TPOINTER_X_TCOMPARATOR_HPP
#include "xyo-managedmemory-tpointer-x-tcomparator.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TPOINTERTYPE_HPP
#include "xyo-managedmemory-tpointertype.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TPOINTERTYPEEXCLUDE_HPP
#include "xyo-managedmemory-tpointertypeexclude.hpp"
#endif

#endif

