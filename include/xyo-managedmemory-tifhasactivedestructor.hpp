//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TIFHASACTIVEDESTRUCTOR_HPP
#define XYO_MANAGEDMEMORY_TIFHASACTIVEDESTRUCTOR_HPP

#ifndef XYO_DATASTRUCTURES_TGETCLASSOFMEMBER_HPP
#include "xyo-datastructures-tgetclassofmember.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {
		using namespace XYO::DataStructures;

		template<typename T>
		class THasActiveDestructor {
			protected:

				template <typename U, void (U::*)()> struct TCheckMember;

				template <typename U>
				static char TTestMember(TCheckMember<U, &U::activeDestructor > *);

				template <typename U>
				static int TTestMember(...);

				template<typename U>
				struct THasMember {
					static const bool value = sizeof(TTestMember<U>(nullptr)) == sizeof(char);
				};

				template <typename U>
				static char TTestBaseMember(decltype(TGetClassOfMember(&U::activeDestructor)) *);

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
					static const bool value = THasMember<decltype(TGetClassOfMember(&U::activeDestructor))>::value;
				};

			public:
				static const bool value = THasMember<T>::value | TProcessBaseMember<T, THasBaseMember<T>::value>::value;
		};

		template<typename T, bool hasActiveDestructor>
		struct TIfHasActiveDestructorBase {

			static inline void activeDestructor(T *) {
			};

			static inline void activeDestructorArray(T *this_, size_t length) {
			};

		};

		template<typename T>
		struct TIfHasActiveDestructorBase<T, true > {

			static inline void activeDestructor(T *this_) {
				this_->activeDestructor();
			};

			static inline void activeDestructorArray(T *this_, size_t length) {
				size_t k;
				for(k = 0; k < length; ++k) {
					this_[k].activeDestructor();
				};
			};

		};

		template<typename T>
		struct TIfHasActiveDestructor : TIfHasActiveDestructorBase<T, THasActiveDestructor<T>::value> {
		};

	};
};

#endif

