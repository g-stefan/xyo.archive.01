//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TIFHASDECREFERENCECOUNT_HPP
#define XYO_MANAGEDMEMORY_TIFHASDECREFERENCECOUNT_HPP

#ifndef XYO_DATASTRUCTURES_TGETCLASSOFMEMBER_HPP
#include "xyo-datastructures-tgetclassofmember.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {
		using namespace XYO::DataStructures;

		template<typename T>
		class THasDecReferenceCount {
			protected:
				template <typename U, void (U::*)()> struct TCheckMember;

				template <typename U>
				static char TTestMember(TCheckMember<U, &U::decReferenceCount > *);

				template <typename U>
				static int TTestMember(...);

				template<typename U>
				struct THasMember {
					static const bool value = sizeof(TTestMember<U>(nullptr)) == sizeof(char);
				};

				template <typename U>
				static char TTestBaseMember(decltype(TGetClassOfMember(&U::decReferenceCount)) *);

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
					static const bool value = THasMember<decltype(TGetClassOfMember(&U::decReferenceCount))>::value;
				};

			public:

				static const bool value = THasMember<T>::value | TProcessBaseMember<T, THasBaseMember<T>::value>::value;
		};


		template<typename T, bool hasDecReferenceCount>
		struct TIfHasDecReferenceCountBase {
			static inline void decReferenceCount(T *) {
			};
		};

		template<typename T>
		struct TIfHasDecReferenceCountBase<T, true > {
			static inline void decReferenceCount(T *this_) {
				this_->decReferenceCount();
			};

		};

		template<typename T>
		struct TIfHasDecReferenceCount : TIfHasDecReferenceCountBase<T, THasDecReferenceCount<T>::value> {
		};

	};
};

#endif

