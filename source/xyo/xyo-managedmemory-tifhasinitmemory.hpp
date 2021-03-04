//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_TIFHASINITMEMORY_HPP
#define XYO_MANAGEDMEMORY_TIFHASINITMEMORY_HPP

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {

		template<typename T>
		class THasInitMemory {
			protected:

				template <typename U, void (*)()> struct TCheckMember;

				template <typename U>
				static char TTestMember(TCheckMember<U, &U::initMemory > *);

				template <typename U>
				static int TTestMember(...);

			public:

				static const bool value = sizeof(TTestMember<T>(nullptr)) == sizeof(char);
		};

		template<typename T, bool hasInitMemory>
		struct TIfHasInitMemoryBase {
			static inline void initMemory() {
			};
		};

		template<typename T>
		struct TIfHasInitMemoryBase<T, true > {
			static inline void initMemory() {
				T::initMemory();
			};
		};

		template<typename T>
		struct TIfHasInitMemory : TIfHasInitMemoryBase<T, THasInitMemory<T>::value> {
		};

	};
};

#endif

