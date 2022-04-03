//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_TREDBLACKTREEONE_HPP
#define XYO_DATASTRUCTURES_TREDBLACKTREEONE_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#	include "xyo-managedmemory-tmemory.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TXREDBLACKTREE_HPP
#	include "xyo-datastructures-txredblacktree.hpp"
#endif

namespace XYO {
	namespace DataStructures {
		using namespace XYO::ManagedMemory;

		template <typename TKey, template <typename U> class TNodeMemory>
		struct TRedBlackTreeNodeOne : TXRedBlackTreeNode<TRedBlackTreeNodeOne<TKey, TNodeMemory>, TKey> {
				typedef TRedBlackTreeNodeOne TNode;
				typedef TXRedBlackTree<TNode, TNodeMemory> TXRBTree;

				inline TNode *minimum() {
					return TXRBTree::minimum(this);
				};

				inline TNode *maximum() {
					return TXRBTree::maximum(this);
				};

				inline TNode *successor() {
					return TXRBTree::successor(this);
				};

				inline TNode *predecesor() {
					return TXRBTree::predecesor(this);
				};

				inline void activeConstructor() {
					TIfHasActiveConstructor<TKey>::activeConstructor(&this->key);
				};

				inline void activeDestructor() {
					TIfHasActiveDestructor<TKey>::activeDestructor(&this->key);
				};
		};

		template <typename TKey, template <typename U> class TNodeMemory = TMemory>
		class TRedBlackTreeOne : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(TRedBlackTreeOne);

			public:
				typedef TRedBlackTreeNodeOne<TKey, TNodeMemory> TNode;
				typedef TXRedBlackTree<TNode, TNodeMemory> TXRBTree;
				typedef TNode Node;

				typedef typename TPointerTypeExclude<TKey>::Type TKeyType;

				static inline TNode *newNode() {
					return TXRBTree::newNode();
				};

				static inline void deleteNode(TNode *this_) {
					return TXRBTree::deleteNode(this_);
				};

				static inline void initMemory() {
					TIfHasInitMemory<TKey>::initMemory();
					TXRBTree::initMemory();
				};

				TNode *root;

				inline TRedBlackTreeOne() {
					TXRBTree::constructor(root);
				};

				inline ~TRedBlackTreeOne() {
					TXRBTree::destructor(root);
				};

				inline void empty() {
					TXRBTree::empty(root);
				};

				inline TNode *find(const TKey &key) {
					return TXRBTree::find(root, key);
				};

				inline TNode *find(const TKeyType *key) {
					TNode *x;
					int compare;
					for (x = root; x;) {
						compare = TComparator<TKeyType>::compare(*key, *(x->key));
						if (compare == 0) {
							return x;
						};
						if (compare < 0) {
							x = x->left;
						} else {
							x = x->right;
						};
					};
					return x;
				};

				inline void set(const TKey &key) {
					TNode *node = TXRBTree::find(root, key);
					if (node) {
						return;
					};
					node = TXRBTree::newNode();
					TIfHasPointerLink<TKey>::pointerLink(&node->key, this);
					node->key = key;
					TXRBTree::insertNode(root, node);
				};

				inline void set(const TKeyType *key) {
					TNode *node = find(key);
					if (node) {
						return;
					};
					node = TXRBTree::newNode();
					TIfHasPointerLink<TKey>::pointerLink(&node->key, this);
					node->key = key;
					TXRBTree::insertNode(root, node);
				};

				inline bool has(const TKey &key) {
					TNode *node = TXRBTree::find(root, key);
					if (node) {
						return true;
					};
					return false;
				};

				inline bool has(const TKeyType *key) {
					TNode *node = find(key);
					if (node) {
						return true;
					};
					return false;
				};

				inline TNode *begin() {
					return TXRBTree::begin(root);
				};

				inline TNode *end() {
					return TXRBTree::end(root);
				};

				inline void activeDestructor() {
					empty();
				};

				inline bool remove(const TKey &key) {
					return TXRBTree::remove(root, key);
				};

				inline bool remove(const TKeyType *key) {
					TNode *node = find(key);
					if (node) {
						TXRBTree::remove(root, node);
						return true;
					};
					return false;
				};
		};

	};
};

#endif
