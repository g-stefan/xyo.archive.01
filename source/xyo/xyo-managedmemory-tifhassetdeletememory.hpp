//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TIFHASSETDELETEMEMORY_HPP
#define XYO_MANAGEDMEMORY_TIFHASSETDELETEMEMORY_HPP

#ifndef XYO_DATASTRUCTURES_TGETCLASSOFMEMBER_HPP
#include "xyo-datastructures-tgetclassofmember.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_DELETEMEMORY_HPP
#include "xyo-managedmemory-deletememory.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {
		using namespace XYO::DataStructures;

		template<typename T>
		class THasSetDeleteMemory {
			protected:
				template <typename U, void (U::*)(DeleteMemory deleteMemory, void *memoryThis)> struct TCheckMember;

				template <typename U>
				static char TTestMember(TCheckMember<U, &U::setDeleteMemory > *);

				template <typename U>
				static int TTestMember(...);

				template<typename U>
				struct THasMember {
					static const bool value = sizeof(TTestMember<U>(nullptr)) == sizeof(char);
				};

				template <typename U>
				static char TTestBaseMember(decltype(TGetClassOfMember(&U::setDeleteMemory)) *);

				template <typename U>
				static int TTestBaseMember(...);

				template<typename U>
				struct THasBaseMember {
					static const bool value = sizeof(TTestBaseMember<U>(nullptr)) == sizeof(char);
				};

				template<typename U, bool hasBase>
				struct TProcessBaseMember {
					static const bool value = false;
				};

				template<typename U>
				struct TProcessBaseMember<U, true> {
					static const bool value = THasMember<decltype(TGetClassOfMember(&U::setDeleteMemory))>::value;
				};

			public:

				static const bool value = THasMember<T>::value | TProcessBaseMember<T, THasBaseMember<T>::value>::value;
		};


		template<typename T, bool hasSetDeleteMemory>
		struct TIfHasSetDeleteMemoryBase {
			static inline void setDeleteMemory(T *, DeleteMemory deleteMemory, void *memoryThis) {
			};

		};

		template<typename T>
		struct TIfHasSetDeleteMemoryBase<T, true > {
			static inline void setDeleteMemory(T *this_, DeleteMemory deleteMemory, void *memoryThis) {
				this_->setDeleteMemory(deleteMemory, memoryThis);
			};

		};

		template<typename T>
		struct TIfHasSetDeleteMemory : TIfHasSetDeleteMemoryBase<T, THasSetDeleteMemory<T>::value> {
		};

	};
};

#endif

