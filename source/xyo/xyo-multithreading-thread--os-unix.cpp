//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

#ifdef XYO_OS_UNIX

#include <pthread.h>
#include <unistd.h>

#include "xyo-managedmemory-registrythread.hpp"
#include "xyo-multithreading-thread.hpp"

#ifdef XYO_SINGLE_THREAD
namespace XYO {
	namespace Multithreading {

		void Thread::sleep(int milliSeconds) {
			usleep(milliSeconds * 1000);
		};

	};
};
#endif

#ifdef XYO_MULTI_THREAD
namespace XYO {
	namespace Multithreading {
		using namespace XYO::ManagedMemory;

		class Thread_ {
			public:
				ThreadProcedure procedure;
				void *this_;
				//
				bool isValid;
				pthread_t thread;
		};

		static void *threadProcedure_(Thread_ *thread) {
			RegistryThread::threadBegin();
			(*thread->procedure)(thread->this_);
			RegistryThread::threadEnd();
			thread->isValid = false;
			return nullptr;
		};

		Thread::Thread() {
			thread = new Thread_();
			thread->procedure = nullptr;
			thread->this_ = nullptr;
			thread->isValid = false;
		};

		Thread::~Thread() {
			join();
			delete thread;
		};

		void Thread::join() {
			if(thread->isValid) {
				if(pthread_join(thread->thread, nullptr)) {
					throw std::runtime_error("pthread_join");
				};
				thread->isValid = false;
			};
		};

		bool Thread::start(ThreadProcedure procedure, void *this_) {
			join();

			thread->procedure = procedure;
			thread->this_ = this_;

			if(pthread_create(&thread->thread, nullptr, (void *( *)(void *))threadProcedure_, thread) == 0) {
				thread->isValid = true;
				return true;
			};
			return false;
		};

		bool Thread::isRunning() {
			if(thread->isValid) {
				return true;
			};
			return false;
		};

		void Thread::sleep(int milliSeconds) {
			usleep(milliSeconds * 1000);
		};

	};
};

#endif

#endif
