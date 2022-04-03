//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_TXLIST5_HPP
#define XYO_DATASTRUCTURES_TXLIST5_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#	include "xyo-managedmemory-tmemorysystem.hpp"
#endif

namespace XYO {
	namespace DataStructures {
		using namespace XYO::ManagedMemory;

		template <typename TNode>
		struct TXList5Node {
				TNode *back;
				TNode *next;
				TNode *childHead;
				TNode *childTail;
				TNode *parent;
		};

		template <typename TNode, template <typename U> class TNodeMemory = TMemorySystem>
		struct TXList5 {

				typedef TNode Node;

				static inline TNode *newNode() {
					return TNodeMemory<TNode>::newMemory();
				};

				static inline void deleteNode(TNode *this_) {
					return TNodeMemory<TNode>::deleteMemory(this_);
				};

				static inline void initMemory() {
					TNodeMemory<TNode>::initMemory();
				};

				static inline void constructor(TNode *&root) {
					root = nullptr;
				};

				static inline void destructor(TNode *root) {
					TNode *this_;
					while (root) {
						destructor(root->childHead);
						this_ = root;
						root = root->next;
						deleteNode(this_);
					};
				};

				static inline void empty(TNode *&root) {
					destructor(root);
					constructor(root);
				};

				static inline void push(TNode *root, TNode *node) {
					node->back = nullptr;
					node->next = root->childHead;
					if (root->childHead) {
						root->childHead->back = node;
					} else {
						root->childTail = node;
					};
					root->childHead = node;
					node->parent = root;
				};

				static inline void pushToTail(TNode *root, TNode *node) {
					node->back = root->childTail;
					node->next = nullptr;
					if (root->childTail) {
						root->childTail->next = node;
					} else {
						root->childHead = node;
					};
					root->childTail = node;
					node->parent = root;
				};

				static inline TNode *popUnsafe(TNode *root) {
					TNode *node = root->childHead;
					if (root->childHead->next) {
						root->childHead->next->back = nullptr;
					};
					if (root->childHead == root->childTail) {
						root->childTail = nullptr;
					};
					root->childHead = root->childHead->next;
					node->parent = nullptr;
					return node;
				};

				static inline TNode *pop(TNode *root) {
					if (root->childHead) {
						return popUnsafe(root);
					};
					return nullptr;
				};

				static inline TNode *popFromTailUnsafe(TNode *root) {
					TNode *node = root->childTail;
					if (root->childTail->back) {
						root->childTail->back->next = nullptr;
					};
					if (root->childTail == root->childHead) {
						root->childHead = nullptr;
					};
					root->childTail = root->childTail->back;
					node->parent = nullptr;
					return node;
				};

				static inline TNode *popFromTail(TNode *root) {
					if (root->childTail) {
						return popFromTailUnsafe(root);
					};
					return nullptr;
				};

				static inline void extractNode(TNode *node) {
					if (node->next) {
						node->next->back = node->back;
					};
					if (node->back) {
						node->back->next = node->next;
					};
					node->parent = nullptr;
				};

				static inline void extract(TNode *root, TNode *node) {
					if (root->childHead == node) {
						popUnsafe(root);
						return;
					};
					if (root->childTail == node) {
						popFromTailUnsafe(root);
						return;
					};
					extractNode(node);
				};

				static inline TNode *successor(TNode *node) {
					if (node->childHead) {
						return node->childHead;
					};
					return node->next;
				};

				static inline TNode *predecessor(TNode *node) {
					if (node->back) {
						if (node->back->childTail) {
							return node->back->childTail;
						};
						return node->back;
					};
					return node->parent;
				};

				static inline TNode *begin(TNode *node) {
					TNode *scan;
					for (scan = node; scan != nullptr; scan = scan->parent) {
						if (scan->parent == nullptr) {
							break;
						};
					};
					return scan;
				};

				static inline TNode *end(TNode *node) {
					TNode *scan;
					for (scan = begin(node); scan != nullptr; scan = scan->next) {
						if (scan->next == nullptr) {
							if (scan->childTail) {
								scan = scan->childTail;
							};
							break;
						};
					};
					return scan;
				};
		};

	};
};

#endif
