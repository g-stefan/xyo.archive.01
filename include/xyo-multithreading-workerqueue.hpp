//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MULTITHREADING_WORKERQUEUE_HPP
#define XYO_MULTITHREADING_WORKERQUEUE_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

#ifndef XYO_MULTITHREADING_THREAD_HPP
#include "xyo-multithreading-thread.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TDYNAMICARRAY_HPP
#include "xyo-datastructures-tdynamicarray.hpp"
#endif

#ifndef XYO_MULTITHREADING_CRITICALSECTION_HPP
#include "xyo-multithreading-criticalsection.hpp"
#endif

#ifndef XYO_MULTITHREADING_WORKER_HPP
#include "xyo-multithreading-worker.hpp"
#endif

namespace XYO {
	namespace Multithreading {
		using namespace XYO::ManagedMemory;
		using namespace XYO::DataStructures;

		class WorkerQueueNode : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(WorkerQueueNode);

			public:

#ifdef XYO_MULTI_THREAD
				Worker worker;
				bool started;
#endif
#ifdef XYO_SINGLE_THREAD
				TPointer<Object> returnValue;
				WorkerProcedure workerProcedure;
#endif
				TPointer<Object> parameter;

				inline WorkerQueueNode() {
#ifdef XYO_MULTI_THREAD
					started = false;
#endif
#ifdef XYO_SINGLE_THREAD
					workerProcedure = nullptr;
#endif
				};

				inline void activeDestructor() {
#ifdef XYO_MULTI_THREAD
					worker.endWork();
					started = false;
#endif
#ifdef XYO_SINGLE_THREAD
					returnValue.deleteMemory();
					workerProcedure = nullptr;
#endif
					parameter.deleteMemory();
				};
		};

		class WorkerQueue : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(WorkerQueue);

			protected:

				int numberOfThreads;
				TDynamicArray<WorkerQueueNode> queue;
				bool allDone;

			public:

				XYO_EXPORT WorkerQueue();
				XYO_EXPORT ~WorkerQueue();
				XYO_EXPORT void add(WorkerProcedure workerProcedure_,
					TransferProcedure transferReturnValue_,
					TransferProcedure transferParameter_,
					Object *parameter);
				XYO_EXPORT void setNumberOfThreads(int numberOfThreads_);
				XYO_EXPORT int getNumberOfThreads();
				XYO_EXPORT bool process();
				XYO_EXPORT TPointer<Object> getReturnValue(size_t index);
				XYO_EXPORT void setParameter(size_t index, Object *parameter);
				XYO_EXPORT void reset();
				XYO_EXPORT WorkerQueueNode &index(size_t index);

				size_t length() const {
					return queue.length();
				};

				bool isEmpty() const {
					return queue.isEmpty();
				};
		};

		template<typename ReturnT,
			typename ParameterT,
			TPointer<ReturnT> TransferReturnT(ReturnT &),
			TPointer<ParameterT> TransferParameterT(ParameterT &),
			TPointer<ReturnT> WorkerProcedureT(ParameterT *, TAtomic<bool> &)>
		struct TWorkerQueue {

			static inline void add(WorkerQueue &workerQueue, ParameterT *parameter) {
				workerQueue.add(
					TGetWorkerProcedure<ReturnT, ParameterT, WorkerProcedureT>::workerProcedure,
					TGetTransferProcedure<ReturnT, TransferReturnT>::transferProcedure,
					TGetTransferProcedure<ParameterT, TransferParameterT>::transferProcedure,
					TStaticCast<Object *>(parameter)
				);
			};

		};

	};
};

#endif
