///
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_DYNAMICOBJECT_HPP
#define XYO_DATASTRUCTURES_DYNAMICOBJECT_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TXLIST1_HPP
#include "xyo-datastructures-txlist1.hpp"
#endif

namespace XYO {

	namespace DataStructures {
		class DynamicObject;
	}

	namespace ManagedMemory {
		template<>
		struct TMemory<DataStructures::DynamicObject> : TMemoryPoolActive<DataStructures::DynamicObject> {};
	}

	namespace DataStructures {
		using namespace XYO::ManagedMemory;

		struct DynamicTypeNode : TXList1Node<DynamicTypeNode> {
			const void *type;
		};

#define XYO_DYNAMIC_TYPE_DEFINE(EXPORT,T) \
protected:\
	EXPORT static const char *type##T##Key;\
	EXPORT static const void *type##T;\
public:\
	static inline const void *getType()\
	{\
		if(type##T==nullptr)\
		{\
			registerType(type##T,type##T##Key);\
		};\
		return type##T;\
	};\
private:

#define XYO_DYNAMIC_TYPE_IMPLEMENT(T,KEY) \
	const char *T::type##T##Key=KEY;\
	const void *T::type##T=nullptr;

#define XYO_DYNAMIC_TYPE_PUSH(T) \
	objectTypePush(type##T,type##T##Key);

		class DynamicObject : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(DynamicObject);
				XYO_DYNAMIC_TYPE_DEFINE(XYO_EXPORT, DynamicObject);

			protected:

				XYO_EXPORT static void registerType(const void *&type, const char *key);
				XYO_EXPORT void objectTypePush(const void *&type, const char *key);
				XYO_EXPORT bool objectTypeSearchNext(const void *type);
				DynamicTypeNode *objectType_;

			public:

				XYO_EXPORT DynamicObject();
				XYO_EXPORT ~DynamicObject();
				XYO_EXPORT static void initMemory();
				XYO_EXPORT static const char *getTypeKey(const void *type);
				XYO_EXPORT const char *getTypeKey();

				inline bool isType(const void *type) {
					if(objectType_->type == type) {
						return true;
					};
					return objectTypeSearchNext(type);
				};

				inline bool isTypeExact(const void *type) {
					if(objectType_->type == type) {
						return true;
					};
					return false;
				};

				inline bool isSameType(DynamicObject *dynamicObject) {
					return (objectType_->type == dynamicObject->objectType_->type);
				};
		};

		template<typename T>
		bool TIsType(DynamicObject *object) {
			return object->isType(T::getType());
		};

		template<typename T>
		bool TIsTypeExact(DynamicObject *object) {
			return object->isTypeExact(T::getType());
		};

		template<typename T>
		const char *TGetTypeKey() {
			return DynamicObject::getTypeKey(T::getType());
		};

		template<typename T>
		T TDynamicCast(DynamicObject *object) {
			typedef typename std::remove_pointer<T>::type TType;
			if(object == nullptr) {
				return nullptr;
			};
			if(object->isType(TType::getType())) {
				return static_cast<T>(object);
			};
			return nullptr;
		};

		template<typename T>
		DynamicObject *TDynamicCast(T this_) {
			if(this_ == nullptr) {
				return nullptr;
			};
			return static_cast<DynamicObject *>(this_);
		};

		template<DynamicObject *>
		DynamicObject *TDynamicCast(DynamicObject *this_) {
			return this_;
		};

	};
};

#endif
