//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_TSTATICCAST_HPP
#define XYO_DATASTRUCTURES_TSTATICCAST_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

namespace XYO {
	namespace DataStructures {
		using namespace XYO::ManagedMemory;

		template<typename T>
		T TStaticCast(Object *this_) {
			if(this_ == nullptr) {
				return nullptr;
			};
			return static_cast<T >(this_);
		};

		template<typename T>
		Object *TStaticCast(T this_) {
			if(this_ == nullptr) {
				return nullptr;
			};
			return static_cast<Object *>(this_);
		};

		template<Object *>
		Object *TStaticCast(Object *this_) {
			return this_;
		};

	};
};

#endif

