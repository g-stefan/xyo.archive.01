//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MANAGEDMEMORY_REGISTRYKEY_HPP
#define XYO_MANAGEDMEMORY_REGISTRYKEY_HPP

#ifndef XYO_DATASTRUCTURES_TXREDBLACKTREE_HPP
#include "xyo-datastructures-txredblacktree.hpp"
#endif

#ifndef XYO_MULTITHREADING_TATOMIC_HPP
#include "xyo-multithreading-tatomic.hpp"
#endif

namespace XYO {
	namespace ManagedMemory {
		using namespace XYO::DataStructures;
		using namespace XYO::Multithreading;

		struct RegistryKeyNode : TXRedBlackTreeNode<RegistryKeyNode, const char *> {
			TAtomic<void *> processValue;
			size_t threadValue;
		};

		typedef TXRedBlackTree<RegistryKeyNode> RegistryKeyRBTree;

		namespace RegistryKey {

			XYO_EXPORT bool checkAndRegisterKey(const char *key, RegistryKeyNode *&this_);
			XYO_EXPORT RegistryKeyNode *getKey(const char *key);

			XYO_EXPORT void processBegin();
			XYO_EXPORT void processEnd();

#ifdef XYO_MULTI_THREAD
			XYO_EXPORT void criticalEnter();
			XYO_EXPORT void criticalLeave();
#endif

#ifdef XYO_SINGLE_THREAD
			inline void criticalEnter() {
			};

			inline void criticalLeave() {
			};
#endif

		};

	};
};

#endif

