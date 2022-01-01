//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_TSTACK_HPP
#define XYO_DATASTRUCTURES_TSTACK_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TXLIST1_HPP
#include "xyo-datastructures-txlist1.hpp"
#endif

namespace XYO {
	namespace DataStructures {
		using namespace XYO::ManagedMemory;

		template<typename T>
		struct TStackNode : TXList1Node<TStackNode<T> > {
			typedef TStackNode TNode;

			T value;

			inline void activeConstructor() {
				TIfHasActiveConstructor<T>::activeConstructor(&value);
			};

			inline void activeDestructor() {
				TIfHasActiveDestructor<T>::activeDestructor(&value);
			};
		};

		template<typename T, template <typename U> class TNodeMemory = TMemory>
		class TStack : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(TStack);
			public:
				typedef TStackNode<T> TNode;
				typedef TXList1<TNode, TNodeMemory > TXStack;
				typedef TNode Node;

				typedef typename TPointerTypeExclude<T>::Type TType;
				typedef typename TPointerTypeExclude<T>::Pointer TPointerT;
				typedef typename TPointerTypeExclude<T>::PointerX TPointerXT;

				static inline TNode *newNode() {
					return TXStack::newNode();
				};

				static inline void deleteNode(TNode *this_) {
					return TXStack::deleteNode(this_);
				};

				static inline void initMemory() {
					TMemory<T>::initMemory();
					TXStack::initMemory();
				};

				TNode *head;

				inline TStack() {
					TXStack::constructor(head);
				};

				inline ~TStack() {
					TXStack::destructor(head);
				};

				inline void push(const T &value) {
					TNode *node = TXStack::newNode();
					TIfHasPointerLink<T>::pointerLink(&node->value, this);
					node->value = const_cast<T &>(value);
					TXStack::push(head, node);
				};

				inline void push(const TType *value) {
					TNode *node = TXStack::newNode();
					TIfHasPointerLink<T>::pointerLink(&node->value, this);
					node->value = value;
					TXStack::push(head, node);
				};

				inline bool pop(T &value) {
					TNode *node = TXStack::pop(head);
					if(node) {
						value = node->value;
						TXStack::deleteNode(node);
						return true;
					};
					return false;
				};

				inline bool pop(TPointerT &value) {
					TNode *node = TXStack::pop(head);
					if(node) {
						value = node->value;
						TXStack::deleteNode(node);
						return true;
					};
					return false;
				};

				inline bool pop(TPointerXT &value) {
					TNode *node = TXStack::pop(head);
					if(node) {
						value = node->value;
						TXStack::deleteNode(node);
						return true;
					};
					return false;
				};

				inline void empty() {
					TXStack::empty(head);
				};

				inline void activeDestructor() {
					empty();
				};

				inline bool isEmpty() const {
					return (head == nullptr);
				};

				inline bool duplicate() {
					if(head) {
						TNode *node = TXStack::newNode();
						TIfHasPointerLink<T>::pointerLink(&node->value, this);
						node->value = head->value;
						TXStack::push(head, node);
						return true;
					};
					return false;
				};

				inline bool swap() {
					return TXStack::swap(head);
				};

				inline void push() {
					TNode *node = TXStack::newNode();
					TIfHasPointerLink<T>::pointerLink(&node->value, this);
					TXStack::push(head, node);
				};

				inline bool pop() {
					TNode *node = TXStack::pop(head);
					if(node) {
						TXStack::deleteNode(node);
						return true;
					};
					return false;
				};

		};

	};
};

#endif

