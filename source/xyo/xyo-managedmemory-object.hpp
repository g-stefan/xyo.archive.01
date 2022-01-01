//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_OBJECT_HPP
#define XYO_MANAGEDMEMORY_OBJECT_HPP

#ifndef XYO_MANAGEDMEMORY_DELETEMEMORY_HPP
#include "xyo-managedmemory-deletememory.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_POINTERX_HPP
#include "xyo-managedmemory-pointerx.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		class Object {
			private:
				Object(const Object &) = delete;
				Object(Object &&) = delete;
				Object &operator = (const Object &) = delete;
				Object &operator = (Object &&) = delete;

			protected:

#ifdef XYO_MANAGEDMEMORY_64BIT
				int64_t referenceCounter_;
#else
				int32_t referenceCounter_;
#endif
				DeleteMemory deleteMemory_;
				void *memoryThis_;
				PointerX *pointerXHead_;

				void XYO_EXPORT referenceMarkAndSweep_();
				bool XYO_EXPORT referenceMarkIsDynamic_();
				bool XYO_EXPORT referenceMarkReset_();

			public:

				XYO_EXPORT Object();
				virtual XYO_EXPORT ~Object();

				bool referenceMark_;
				bool referenceIsBranch_;

				inline void incReferenceCount() {
#ifdef  XYO_OBJECT_REFERENCE_COUNT_INFO
					printf("%p: incReferenceCount %08d > %08d\n", this, referenceCounter_, referenceCounter_ + 1);
#endif
					++referenceCounter_;
				};

				void XYO_EXPORT decReferenceCount();

				inline void setDeleteMemory(DeleteMemory deleteMemory, void *memoryThis) {
#ifdef  XYO_OBJECT_REFERENCE_COUNT_INFO
					printf("%p: setDeleteMemory %p, %p\n", this, deleteMemory, memoryThis);
#endif
					deleteMemory_ = deleteMemory;
					memoryThis_ = memoryThis;
				};

				void XYO_EXPORT addPointerX(PointerX *value);
				void XYO_EXPORT removePointerX(PointerX *value);
				void XYO_EXPORT transferPointerX(PointerX *value, const Object *object, const void *object_);

				void decReferenceCountExecutive() {
					--referenceCounter_;
				};

				inline bool hasOneReference() const {
					if((referenceCounter_ <= 1) && (pointerXHead_ == nullptr)) {
						return true;
					};
					if((referenceCounter_ <= 0) && (pointerXHead_ != nullptr)) {
						if(pointerXHead_->next == nullptr) {
							return true;
						};
					};
					return false;
				};
		};

	};
};

#endif
