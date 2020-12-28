//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_TXREDBLACKTREE_HPP
#define XYO_DATASTRUCTURES_TXREDBLACKTREE_HPP

#ifndef XYO_DATASTRUCTURES_TCOMPARATOR_HPP
#include "xyo-datastructures-tcomparator.hpp"
#endif

#ifndef XYO_MANAGEDMEMORY_TMEMORYSYSTEM_HPP
#include "xyo-managedmemory-tmemorysystem.hpp"
#endif

namespace XYO {
	namespace DataStructures {
		using namespace XYO::ManagedMemory;

		template<typename TNode, typename TKey>
		struct TXRedBlackTreeNode {
			typedef TKey Key;

			enum Color : bool {
				Black = false,
				Red = true
			};

			TNode *parent;
			TNode *left;
			TNode *right;

			Color   color;
			Key     key;
		};

		template<typename TNode, template <typename U> class TNodeMemory = TMemorySystem>
		struct TXRedBlackTree {

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
				if (root) {
					destructor(root->left);
					destructor(root->right);
					deleteNode(root);
				};
			};

			static inline void empty(TNode *&root) {
				destructor(root);
				constructor(root);
			};

			static inline bool isBlack(const TNode *node) {
				if (node) {
					return (!node->color);
				};
				return true;
			};

			static inline bool isRed(const TNode *node) {
				if (node) {
					return node->color;
				};
				return false;
			};

			static inline void leftRotate(TNode *&root, TNode *x) {
				TNode *y;
				if (x) {
					y = x->right;
					if (y) {
						x->right = y->left;
						if (y->left) {
							y->left->parent = x;
						};
						y->parent = x->parent;
						if (!x->parent) {
							root = y;
						} else {
							if (x == x->parent->left) {
								x->parent->left = y;
							} else {
								x->parent->right = y;
							};
						};

						y->left = x;
						x->parent = y;
					};
				};
			};

			static inline void rightRotate(TNode *&root, TNode *x) {
				TNode *y;
				if (x) {
					y = x->left;
					if (y) {
						x->left = y->right;
						if (y->right) {
							y->right->parent = x;
						};
						y->parent = x->parent;
						if (!x->parent) {
							root = y;
						} else {
							if (x == x->parent->right) {
								x->parent->right = y;
							} else {
								x->parent->left = y;
							};
						};
						y->right = x;
						x->parent = y;
					};
				};
			};

			static inline void insertNode(TNode *&root, TNode *z) {
				TNode *x;
				TNode *y;
				if(!z) {
					return;
				};
				y = nullptr;
				x = root;
				while (x) {
					y = x;
					if (TComparator<typename TNode::Key>::isLess(z->key, x->key)) {
						x = x->left;
					} else {
						x = x->right;
					};
				};
				z->parent = y;
				if (!y) {
					root = z;
				} else if (TComparator<typename TNode::Key>::isLess(z->key, y->key)) {
					y->left = z;
				} else {
					y->right = z;
				};
				z->left = nullptr;
				z->right = nullptr;
				z->color = TNode::Red;
				while (isRed(z->parent)) {
					if (!z->parent) {
						break;
					};
					if (!z->parent->parent) {
						break;
					};
					if (z->parent == z->parent->parent->left) {
						y = z->parent->parent->right;
						if (isRed(y)) {
							z->parent->color = TNode::Black;
							y->color = TNode::Black;
							z->parent->parent->color = TNode::Red;
							z = z->parent->parent;
						} else {
							if (z == z->parent->right) {
								z = z->parent;
								leftRotate(root, z);
							};
							z->parent->color = TNode::Black;
							z->parent->parent->color = TNode::Red;
							rightRotate(root, z->parent->parent);
						};
					} else {
						y = z->parent->parent->left;
						if (isRed(y)) {
							z->parent->color = TNode::Black;
							y->color = TNode::Black;
							z->parent->parent->color = TNode::Red;
							z = z->parent->parent;
						} else {
							if (z == z->parent->left) {
								z = z->parent;
								rightRotate(root, z);
							};
							z->parent->color = TNode::Black;
							z->parent->parent->color = TNode::Red;
							leftRotate(root, z->parent->parent);
						};
					};
				};

				root->color = TNode::Black;
			};

			static inline void transplant(TNode *&root, TNode *x, TNode *y) {
				if (!x->parent) {
					root = y;
				} else {
					if (x == x->parent->left) {
						x->parent->left = y;
					} else {
						x->parent->right = y;
					};
				};
				if(y) {
					y->parent = x->parent;
				};
			};

			static inline void extract(TNode *&root, TNode *z) {
				TNode *x;
				TNode *y;
				TNode *w;
				typename TNode::Color yOriginalColor;
				y = z;
				yOriginalColor = y->color;
				if (!z->left) {
					x = z->right;
					transplant(root, z, z->right);
				} else if (!z->right) {
					x = z->left;
					transplant(root, z, z->left);
				} else {
					y = minimum(z->right);
					yOriginalColor = y->color;
					x = y->right;
					if (y->parent == z) {
						if (x) {
							x->parent = y;
						};
					} else {
						transplant(root, y, y->right);
						y->right = z->right;
						y->right->parent = y;
					};
					transplant(root, z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				};
				if (yOriginalColor == TNode::Black) {
					if(!x) {
						return;
					};
					while ((x != root) && (x->color == TNode::Black)) {
						if (x == x->parent->left) {
							w = x->parent->right;
							if (isRed(w)) {
								w->color = TNode::Black;
								x->parent->color = TNode::Red;
								leftRotate(root, x->parent);
								w = x->parent->right;
							};
							if (isBlack(w->left) &&
								isBlack(w->right)) {
								w->color = TNode::Red;
								x = x->parent;
							} else {
								if (isBlack(w->right)) {
									w->left->color = TNode::Black;
									w->color = TNode::Red;
									rightRotate(root, w);
									w = x->parent->right;
								};
								w->color = x->parent->color;
								x->parent->color = TNode::Black;
								w->right->color = TNode::Black;
								leftRotate(root, x->parent);
								x = root;
							};
						} else {
							w = x->parent->left;
							if (isRed(w)) {
								w->color = TNode::Black;
								x->parent->color = TNode::Red;
								rightRotate(root, x->parent);
								w = x->parent->left;
							};
							if (isBlack(w->right) &&
								isBlack(w->left)) {
								w->color = TNode::Red;
								x = x->parent;
							} else {
								if (isBlack(w->left)) {
									w->right->color = TNode::Black;
									w->color = TNode::Red;
									leftRotate(root, w);
									w = x->parent->left;
								};
								w->color = x->parent->color;
								x->parent->color = TNode::Black;
								w->left->color = TNode::Black;
								rightRotate(root, x->parent);
								x = root;
							};
						};
					};
					x->color = TNode::Black;
				};
			};

			static inline TNode *find(TNode *&root, const typename TNode::Key &key) {
				TNode *x;
				int compare;
				for(x = root; x;) {
					compare = TComparator<typename TNode::Key>::compare(key, x->key);
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

			static inline void remove(TNode *&root, TNode *node) {
				extract(root, node);
				deleteNode(node);
			};

			static inline bool remove(TNode *&root, const typename TNode::Key &key) {
				TNode *node = find(root, key);
				if (node) {
					remove(root, node);
					return true;
				};
				return false;
			};

			static inline TNode *minimum(TNode *node) {
				while (node->left) {
					node = node->left;
				};
				return node;
			};

			static inline TNode *maximum(TNode *node) {
				while (node->right) {
					node = node->right;
				};
				return node;
			};

			static inline TNode *successor(TNode *x) {
				TNode *y;

				if (x->right) {
					return minimum(x->right);
				};
				y = x->parent;
				while (y) {
					if (x == y->right) {
						x = y;
						y = y->parent;
					} else {
						break;
					};
				};
				return y;
			};

			static inline TNode *predecessor(TNode *x) {
				TNode *y;

				if (x->left) {
					return maximum(x->left);
				};
				y = x->parent;
				while (y) {
					if (x == y->left) {
						x = y;
						y = y->parent;
					} else {
						break;
					};
				};
				return y;
			};

			static inline TNode *begin(TNode *node) {
				if (node) {
					return minimum(node);
				};
				return nullptr;
			};

			static inline TNode *end(TNode *node) {
				if (node) {
					return maximum(node);
				};
				return nullptr;
			};

		};

	};
};

#endif
