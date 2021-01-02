//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_TTRANSFER_HPP
#define XYO_DATASTRUCTURES_TTRANSFER_HPP

namespace XYO {
	namespace DataStructures {

		struct TTransferNone;

		template<typename T, typename X = TTransferNone>
		struct TTransfer {
			static inline TTransfer<T> *transfer(const T *value_) {
				return reinterpret_cast<TTransfer<T> *>(const_cast<T *>(value_));
			};

			inline T *operator->() {
				return reinterpret_cast<T *>(this);
			};

			inline T *value() {
				return reinterpret_cast<T *>(this);
			};

			static inline TTransfer<T> *cast(TTransfer<X> *value_) {
				return reinterpret_cast<TTransfer<T> *>(static_cast<T *>(reinterpret_cast<X *>(value_)));
			};
		};

	};
};

#endif

