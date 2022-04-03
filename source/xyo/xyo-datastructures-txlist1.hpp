//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_TXLIST1_HPP
#define XYO_DATASTRUCTURES_TXLIST1_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#	include "xyo-managedmemory-tmemorysystem.hpp"
#endif

namespace XYO {
	namespace DataStructures {
		using namespace XYO::ManagedMemory;

		template <typename TNode>
		struct TXList1Node {
				TNode *next;
		};

		template <typename TNode, template <typename U> class TNodeMemory = TMemorySystem>
		struct TXList1 {

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

				static inline void constructor(TNode *&head) {
					head = nullptr;
				};

				static inline void destructor(TNode *head) {
					TNode *this_;
					while (head) {
						this_ = head;
						head = head->next;
						deleteNode(this_);
					};
				};

				static inline void empty(TNode *&head) {
					destructor(head);
					constructor(head);
				};

				static inline void push(TNode *&head, TNode *node) {
					node->next = head;
					head = node;
				};

				static inline void popUnsafeX(TNode *&head) {
					head = head->next;
				};

				static inline TNode *popUnsafe(TNode *&head) {
					TNode *node = head;
					popUnsafeX(head);
					return node;
				};

				static inline TNode *pop(TNode *&head) {
					if (head) {
						return popUnsafe(head);
					};
					return nullptr;
				};

				static inline bool swap(TNode *&head) {
					if (head) {
						if (head->next) {
							TNode *tmp1 = popUnsafe(head);
							TNode *tmp2 = popUnsafe(head);
							push(head, tmp1);
							push(head, tmp2);
							return true;
						};
					};
					return false;
				};

				static inline TNode *successor(TNode *node) {
					return node->next;
				};

				static inline TNode *predecessor(TNode *head, TNode *node) {
					TNode *scan;
					for (scan = head; scan != nullptr; scan = scan->back) {
						if (scan->next == node) {
							break;
						};
					};
					return scan;
				};

				static inline TNode *begin(TNode *head) {
					return head;
				};

				static inline TNode *end(TNode *node) {
					TNode *scan;
					for (scan = node; scan != nullptr; scan = scan->next) {
						if (scan->next == nullptr) {
							break;
						};
					};
					return scan;
				};
		};

	};
};

#endif
