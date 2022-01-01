//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MULTITHREADING_WORKER_HPP
#define XYO_MULTITHREADING_WORKER_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

#ifndef XYO_MULTITHREADING_THREAD_HPP
#include "xyo-multithreading-thread.hpp"
#endif

#ifndef XYO_MULTITHREADING_TRANSFER_HPP
#include "xyo-multithreading-transfer.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TSTATICCAST_HPP
#include "xyo-datastructures-tstaticcast.hpp"
#endif

namespace XYO {
	namespace Multithreading {
		using namespace XYO::ManagedMemory;

		typedef TPointer<Object> (*WorkerProcedure)(Object *parameter, TAtomic<bool> &requestToTerminate);

		template<typename ReturnT, typename ParameterT, TPointer<ReturnT> FunctionT(ParameterT *, TAtomic<bool> &)>
		struct TGetWorkerProcedure {
			static TPointer<Object> workerProcedure(Object *parameter, TAtomic<bool> &requestToTerminate);
		};

		template<typename ReturnT, typename ParameterT, TPointer<ReturnT> FunctionT(ParameterT *, TAtomic<bool> &)>
		TPointer<Object> TGetWorkerProcedure<ReturnT, ParameterT, FunctionT>::workerProcedure(Object *parameter, TAtomic<bool> &requestToTerminate) {
			return TStaticCast<Object *>(FunctionT(TStaticCast<ParameterT *>(parameter), requestToTerminate));
		};

#ifdef XYO_MULTI_THREAD

		class Worker : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(Worker);

			protected:

				class Worker_ *worker;

			public:

				XYO_EXPORT Worker();
				XYO_EXPORT ~Worker();
				XYO_EXPORT void setProcedure(WorkerProcedure workerProcedure_);
				XYO_EXPORT void setTransferParameter(TransferProcedure transferParameter_);
				XYO_EXPORT void setTransferReturnValue(TransferProcedure transferReturnValue_);

				XYO_EXPORT bool beginWork();
				XYO_EXPORT void endWork();

				XYO_EXPORT bool start(Object *parameter);
				XYO_EXPORT void join();
				XYO_EXPORT bool isRunning();
				XYO_EXPORT void requestToTerminate();
				XYO_EXPORT TPointer<Object> getReturnValue();

				inline void activeDestructor() {
					endWork();
				};
		};

		template<typename ReturnT,
			typename ParameterT,
			TPointer<ReturnT> TransferReturnT(ReturnT &),
			TPointer<ParameterT> TransferParameterT(ParameterT &),
			TPointer<ReturnT> WorkerProcedureT(ParameterT *, TAtomic<bool> &)>
		struct TWorker {

			static inline void set(Worker &worker) {
				worker.setTransferReturnValue(TGetTransferProcedure<ReturnT, TransferReturnT>::transferProcedure);
				worker.setTransferParameter(TGetTransferProcedure<ParameterT, TransferParameterT>::transferProcedure);
				worker.setProcedure(TGetWorkerProcedure<ReturnT, ParameterT, WorkerProcedureT>::workerProcedure);
			};

			static inline bool start(Worker &worker, ParameterT *parameter) {
				return worker.start(TStaticCast<Object *>(parameter));
			};

			static inline TPointer<ReturnT> getReturnValue(Worker &worker) {
				return TStaticCast<ReturnT *>(worker.getReturnValue());
			};

		};

#endif

	};
};

#endif
