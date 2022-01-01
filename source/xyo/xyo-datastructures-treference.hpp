//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_TREFERENCE_HPP
#define XYO_DATASTRUCTURES_TREFERENCE_HPP

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

namespace XYO {
	namespace DataStructures {

		template<typename T, void DeleteMemoryT(T *)>
		class TReference {
			protected:
				T *object;
			public:

				inline TReference() = delete;

				inline ~TReference() {
					DeleteMemoryT(object);
				};

				//

				inline TReference(const T *value) {
					object = const_cast<T *>(value);
				};

				inline TReference(const TReference &value) = delete;
				inline TReference(TReference &&value) = delete;

				//

				inline TReference &operator=(const TReference &value) = delete;
				inline TReference &operator=(TReference &&value) = delete;

				//

				inline T *operator->() const {
					return object;
				};

				inline operator T *() const {
					return object;
				};

				inline T *value() const {
					return object;
				};

		};

	};
};

#endif
