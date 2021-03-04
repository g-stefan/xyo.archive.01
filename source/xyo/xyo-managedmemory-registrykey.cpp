//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-managedmemory-registrykey.hpp"
#include "xyo-multithreading-criticalsection.hpp"

namespace XYO {
	namespace ManagedMemory {
		using namespace XYO::DataStructures;
		using namespace XYO::Multithreading;

		namespace RegistryKey {

			static RegistryKeyNode *root = nullptr;
			static size_t threadKey;

			typedef RegistryKeyRBTree RBTree;

#ifdef XYO_MULTI_THREAD
			static CriticalSection *criticalSection;
#endif


			bool checkAndRegisterKey(const char *key, RegistryKeyNode *&this_) {
#ifdef XYO_MULTI_THREAD
				criticalSection->enter();
				this_ = RBTree::find(root, key);
				if(this_ != nullptr) {
					criticalSection->leave();
					return false;
				};

				try {
					this_ = RBTree::newNode();
				} catch(...) {
					criticalSection->leave();
					throw;
				};

				this_->key = key;
				this_->processValue.set(nullptr);
				this_->threadValue = threadKey;

				threadKey++;

				RBTree::insertNode(root, this_);

				criticalSection->leave();

				return true;
#endif

#ifdef XYO_SINGLE_THREAD
				this_ = RBTree::find(root, key);
				if(this_ != nullptr) {
					return false;
				};

				this_ = RBTree::newNode();

				this_->key = key;
				this_->processValue.set(nullptr);
				this_->threadValue = threadKey;

				threadKey++;

				RBTree::insertNode(root, this_);

				return true;
#endif
			};

			RegistryKeyNode *getKey(const char *key) {
#ifdef XYO_MULTI_THREAD
				RegistryKeyNode *this_;
				criticalSection->enter();
				this_ = RBTree::find(root, key);
				criticalSection->leave();
				return this_;
#endif
#ifdef XYO_SINGLE_THREAD
				return RBTree::find(root, key);
#endif
			};

			void processBegin() {

#ifdef XYO_MULTI_THREAD
				criticalSection = new CriticalSection();
#endif

				RBTree::constructor(root);
				threadKey = 1;
			};

			void processEnd() {

				RBTree::destructor(root);

#ifdef XYO_MULTI_THREAD
				delete criticalSection;
#endif

			};


#ifdef XYO_MULTI_THREAD

			void criticalEnter() {
				criticalSection->enter();
			};

			void criticalLeave() {
				criticalSection->leave();
			};

#endif

		};
	};
};

