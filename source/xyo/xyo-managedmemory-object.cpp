//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-managedmemory-object.hpp"
#include "xyo-datastructures-txlist2.hpp"

namespace XYO {
	namespace ManagedMemory {
		using namespace XYO::DataStructures;

		Object::Object() {
#ifdef  XYO_OBJECT_REFERENCE_COUNT_INFO
			printf("%p: Object()\n", this);
#endif
			referenceCounter_ = 0;
			deleteMemory_ = nullptr;
			pointerXHead_ = nullptr;
			referenceMark_ = false;
			referenceIsBranch_ = false;
		};

		Object::~Object() {
#ifdef  XYO_OBJECT_REFERENCE_COUNT_INFO
			printf("%p: ~Object()\n", this);
#endif
		};

		void Object::decReferenceCount() {
#ifdef XYO_OBJECT_REFERENCE_COUNT_INFO
			printf("%p: decReferenceCount %08d > %08d\n", this, referenceCounter_, referenceCounter_ - 1);
#endif
			--referenceCounter_;
			if (referenceCounter_ <= 0) {
				referenceCounter_ = 0;
				if (pointerXHead_ == nullptr) {
					if (deleteMemory_) {
#ifdef XYO_OBJECT_REFERENCE_COUNT_INFO
						printf("%p: deleteMemory #1\n", this);
						fflush(stdout);
#endif
						(*deleteMemory_)(memoryThis_);
					};
					return;
				};
				if(referenceIsBranch_) {
					referenceMarkAndSweep_();
				};
				return;
			};
		};

		void Object::addPointerX(struct PointerX *value) {
#ifdef XYO_OBJECT_REFERENCE_COUNT_INFO
			printf("%p: addPointerX %p\n", this, value);
			fflush(stdout);
#endif
			TXList2<PointerX>::push(pointerXHead_, value);
		};

		void Object::removePointerX(struct PointerX *value) {
#ifdef XYO_OBJECT_REFERENCE_COUNT_INFO
			printf("%p: removePointerX %p\n", this, value);
			fflush(stdout);
#endif
			value->object = nullptr;

			TXList2<PointerX>::extract(pointerXHead_, value);

			if (pointerXHead_ == nullptr) {
				if (referenceCounter_ <= 0) {
					referenceCounter_ = 0;
					if (deleteMemory_) {
#ifdef XYO_OBJECT_REFERENCE_COUNT_INFO
						printf("%p: deleteMemory #2\n", this);
						fflush(stdout);
#endif

						(*deleteMemory_)(memoryThis_);
					};
				};
				return;
			};

			if (referenceCounter_ <= 0) {
				referenceCounter_ = 0;
				if(referenceIsBranch_) {
					referenceMarkAndSweep_();
				};
			};
		};

		void Object::transferPointerX(struct PointerX *value, const Object *object, const void *object_) {
#ifdef XYO_OBJECT_REFERENCE_COUNT_INFO
			printf("%p: transferPointerX %p, %p, %p\n", this, value, object, object_);
			fflush(stdout);
#endif
			if(this == object) {
				return;
			};

			TXList2<PointerX>::extract(pointerXHead_, value);

			value->object = const_cast<void *>(object_);

			if(object) {
				(const_cast<Object *>(object))->addPointerX(value);
			};

			if (pointerXHead_ == nullptr) {
				if (referenceCounter_ <= 0) {
					referenceCounter_ = 0;
					if (deleteMemory_) {
#ifdef XYO_OBJECT_REFERENCE_COUNT_INFO
						printf("%p: deleteMemory #3\n", this);
						fflush(stdout);
#endif
						(*deleteMemory_)(memoryThis_);
					};
				};
				return;
			};

			if (referenceCounter_ <= 0) {
				referenceCounter_ = 0;
				if(referenceIsBranch_) {
					referenceMarkAndSweep_();
				};
			};
		};

		void Object::referenceMarkAndSweep_() {

			if(referenceMarkIsDynamic_()) {
				referenceMarkReset_();

				//
				// All pointers are dynamic - reclaim
				//
				struct PointerX *index;
				for (index = pointerXHead_; index; index = index->next) {
					index->object = nullptr;
				};
				pointerXHead_ = nullptr;
				if (deleteMemory_) {
#ifdef XYO_OBJECT_REFERENCE_COUNT_INFO
					printf("%p: deleteMemory #4\n", this);
					fflush(stdout);
#endif
					(*deleteMemory_)(memoryThis_);
				};
				return;
			};
			referenceMarkReset_();

		};

		bool Object::referenceMarkIsDynamic_() {
			struct PointerX *index;

			referenceMark_ = true;
			for (index = pointerXHead_; index; index = index->next) {
				if (index->link) {
					if(!index->link->deleteMemory_) {
						return false;
					};
					if (index->link->referenceCounter_) {
						return false;
					};
					if (index->link->referenceMark_) {
						continue;
					};
					if(!index->link->referenceMarkIsDynamic_()) {
						return false;
					};
				};
			};
			return true;
		};

		bool Object::referenceMarkReset_() {
			struct PointerX *index;

			referenceMark_ = false;
			for (index = pointerXHead_; index; index = index->next) {
				if (index->link) {
					if(!index->link->deleteMemory_) {
						return false;
					};
					if (index->link->referenceCounter_) {
						return false;
					};
					if (!index->link->referenceMark_) {
						continue;
					};
					if(!index->link->referenceMarkReset_()) {
						return false;
					};
				};
			};
			return true;
		};

	};
};


