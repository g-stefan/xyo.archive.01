//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TIFHASPOINTERLINK_HPP
#define XYO_MANAGEDMEMORY_TIFHASPOINTERLINK_HPP

#ifndef XYO_DATASTRUCTURES_TGETCLASSOFMEMBER_HPP
#include "xyo-datastructures-tgetclassofmember.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {
		using namespace XYO::DataStructures;

		class Object;

		template<typename T>
		class THasPointerLink {
			protected:
				template <typename U, void (U::*)(Object *)> struct TCheckMember;

				template <typename U>
				static char TTestMember(TCheckMember<U, &U::pointerLink > *);

				template <typename U>
				static int TTestMember(...);

				template<typename U>
				struct THasMember {
					static const bool value = sizeof(TTestMember<U>(nullptr)) == sizeof(char);
				};

				template <typename U>
				static char TTestBaseMember(decltype(TGetClassOfMember(&U::pointerLink)) *);

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
					static const bool value = THasMember<decltype(TGetClassOfMember(&U::pointerLink))>::value;
				};

			public:

				static const bool value = THasMember<T>::value | TProcessBaseMember<T, THasBaseMember<T>::value>::value;
		};


		template<typename T, bool hasPointerLink>
		struct TIfHasPointerLinkBase {

			static inline void pointerLink(T *this_, Object *link_) {
			};

			static inline void pointerLinkArray(T *this_, Object *link_, size_t length) {
			};

		};

		template<typename T>
		struct TIfHasPointerLinkBase<T, true > {

			static inline void pointerLink(T *this_, Object *link_) {
				this_->pointerLink(link_);
			};

			static inline void pointerLinkArray(T *this_, Object *link_, size_t length) {
				size_t k;
				for(k = 0; k < length; ++k) {
					this_[k].pointerLink(link_);
				};
			};

		};

		template<typename T>
		struct TIfHasPointerLink : TIfHasPointerLinkBase<T, THasPointerLink<T>::value> {
		};

	};
};

#endif

