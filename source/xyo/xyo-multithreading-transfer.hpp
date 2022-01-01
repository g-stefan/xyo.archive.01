//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MULTITHREADING_TRANSFER_HPP
#define XYO_MULTITHREADING_TRANSFER_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TSTATICCAST_HPP
#include "xyo-datastructures-tstaticcast.hpp"
#endif

#ifndef XYO_MULTITHREADING_TATOMIC_HPP
#include "xyo-multithreading-tatomic.hpp"
#endif

#ifndef XYO_MULTITHREADING_SEMAPHORE_HPP
#include "xyo-multithreading-semaphore.hpp"
#endif

namespace XYO {
	namespace Multithreading {
		using namespace XYO::ManagedMemory;

		typedef TPointer<Object> (*TransferProcedure)(Object *);

		template<typename T, TPointer<T> FunctionT(T &)>
		struct TGetTransferProcedure {
			static TPointer<Object> transferProcedure(Object *this_);
		};

		template<typename T, TPointer<T> FunctionT(T &)>
		TPointer<Object> TGetTransferProcedure<T, FunctionT>::transferProcedure(Object *this_) {
			if(this_ == nullptr) {
				return nullptr;
			};
			return TStaticCast<Object *>(FunctionT(*(static_cast<T *>(this_))));
		};

#ifdef XYO_MULTI_THREAD

		class Transfer : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(Transfer);

			protected:

				Transfer *thread1;
				Transfer *thread2;
				Object *value1;
				Object *value2;
				TAtomic<bool> hasValue1;
				TAtomic<bool> hasValue2;
				Semaphore sync1;
				Semaphore sync2;

			public:

				XYO_EXPORT Transfer();
				XYO_EXPORT ~Transfer();
				XYO_EXPORT void link(Transfer *this_);
				XYO_EXPORT void set(Object *value_);
				XYO_EXPORT TPointer<Object> get(TransferProcedure transferProc);
				XYO_EXPORT bool hasValue();
		};

#endif

	};
}

#endif
